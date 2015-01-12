
#include <TimerThree.h>
#include <sysint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <SoftwareSerial.h>
#include <math.h>
#include <stdio.h>

typedef void (*parametricCurve)(double t, void* state, double* values);

class CirclePrm
{
    public:
    
    double r;
};


void pcircle(double t, void* state, double* values)
{
    CirclePrm *cp = (CirclePrm*) state;
    values[0] = cp->r * cos(t * 2 * M_PI) - cp->r;
    values[1] = cp->r * sin(t * 2 * M_PI);
};

void roundCoords(double* coords, int len, long* rounded) {
    for(int i=0; i<len; i++) {
        rounded[i] = lround(coords[i]);
    }
};




class SteppoState
{
private:
    unsigned int *_phaseTable;
    unsigned int *_pinTable;
    unsigned int _phaseTableLen;
    unsigned int _curPhase;

public:
    SteppoState(unsigned int *phaseTable, int tableLength, unsigned int *pinsTable, int pinsTableLength = 4) {
        _phaseTable = phaseTable;
        _phaseTableLen = tableLength;
        _pinTable = pinsTable;
        _curPhase = 0;
    };

    void makeStep(int dir) {
        if (dir > 0) {
            _curPhase = (_curPhase + 1) % _phaseTableLen;
        }
        else if (dir < 0) {
            _curPhase = (_curPhase - 1) % _phaseTableLen;
        }
        uint32_t pt = _phaseTable[_curPhase];

        for (int pin=0; pin<4; pin++) {
            uint32_t v = pt & (1 << pin);
            setPinState(pin, v == 0 ? 0 : 1);
        }
    };  


    virtual void setPinState(int pin, int state) {
        digitalWrite(_pinTable[pin], state ? HIGH : LOW);
    };

    unsigned int getCurPhase() {
        return _curPhase; 
    };

    unsigned int getCurOutputs() {
        return _phaseTable[_curPhase];
    };

};






uint32_t volatile counter = 0;
//AB-BC-CD-DA
unsigned int phases[] = {
    1 << 0 | 1 << 1,
    1 << 1 | 1 << 2,
    1 << 2 | 1 << 3,
    1 << 3 | 1 << 0
};
unsigned int phases8[] = {
    1 << 0,
    1 << 0 | 1 << 1,
    1 << 1, 
    1 << 1 | 1 << 2,
    1 << 2,
    1 << 2 | 1 << 3,
    1 << 3,
    1 << 3 | 1 << 0
};
unsigned int pins[] = {
    4, 5, 6, 7};
unsigned int pins2[] = {
    8, 9, 10, 11};

SteppoState steppo1(phases, sizeof(phases) / sizeof(unsigned int), pins, sizeof(pins) / sizeof(unsigned int));
SteppoState steppo2(phases, sizeof(phases) / sizeof(unsigned int), pins2, sizeof(pins2) / sizeof(unsigned int));
CirclePrm cp;

double res = 0.00001; //resolution

volatile double t = 0;
parametricCurve crv = pcircle;
double funVal[2];
long funInt[2];
long prevFunInt[2];
long difz[2];
volatile unsigned int faults = 0;
volatile unsigned long nstep = 0;


void tick(void) {
    nstep++;
    crv(t, &cp, funVal);
    roundCoords(funVal, sizeof(funVal) / sizeof(double), funInt);
    for (int i=0; i<2; i++) {
        difz[i] = funInt[i] - prevFunInt[i];
        if (abs(difz[i]) > 1) {
            faults++;
            //printf("RESOLUTION too low: %d, %f\n", i, difz[i]);
            //return;
        }
    }
    memcpy(prevFunInt, funInt, sizeof(funInt));
    if (difz[0] != 0) steppo1.makeStep(difz[0]);
    if (difz[1] != 0) steppo2.makeStep(difz[1]);
    //printf("%d. %f\t->\t%d, %d\n", step, t, difz[0], difz[1]);
    t+= res;
};





void setup()
{
    Serial.begin(9600);
    Serial.println("hello\n");
    int prescale = TCCR1B & 0x7;
    Serial.print("prescale:");
    Serial.println(prescale);
    for (int i=0; i<sizeof(pins) / sizeof(unsigned int); i++) {
        pinMode(pins[i], OUTPUT); 
    };
    for (int i=0; i<sizeof(pins2) / sizeof(unsigned int); i++) {
        pinMode(pins[i], OUTPUT); 
    };
    cli();
    Timer3.initialize(200); //us
    Timer3.attachInterrupt(tick);
    
    memset(difz, 0, sizeof(difz));
    cp.r = 2500;
    nstep = 0;
    t = 0;
    res = 0.00001;
    crv(t, &cp, funVal);
    roundCoords(funVal, sizeof(funVal) / sizeof(double), prevFunInt);

    sei();
}

#define TIMER_CLOCK_FREQ 2000000.0 //2MHz for /8 prescale from 16MHz

//Setup Timer2.
//Configures the ATMega168 8-Bit Timer2 to generate an interrupt
//at the specified frequency.
//Returns the timer load value which must be loaded into TCNT2
//inside your ISR routine.
//See the example usage below.
unsigned char SetupTimer2(float timeoutFrequency){
    unsigned char result; //The timer load value.

    //Calculate the timer load value
    result=(int)((65536.0-(TIMER_CLOCK_FREQ / timeoutFrequency))+0.5);
    //The 257 really should be 256 but I get better results with 257.

    //Timer2 Settings: Timer Prescaler /8, mode 0
    //Timer clock = 16MHz/8 = 2Mhz or 0.5us
    //The /8 prescale gives us a good range to work with
    //so we just hard code this for now.
    TCCR2A = 0;
    TCCR2B = 0<<CS22 | 1<<CS21 | 0<<CS20;

    //Timer2 Overflow Interrupt Enable
    TIMSK2 = 1<<TOIE2;

    //load the timer for its first cycle
    TCNT2=result;

    return(result);
}




ISR(TIMER2_OVF_vect)
{
    tick();
}

void loop()
{
    char buf[100];
    delay(1000);
    sprintf(buf, "step: %d, t: %f, pos: %f,%f, faults: %d", nstep, t, prevFunInt[0], prevFunInt[1], faults);
    Serial.println(buf);
    faults = 0;
}



