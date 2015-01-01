#include <TimerThree.h>

#include <sysint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <SoftwareSerial.h>


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

class MotionCalculatorBase
{
  protected:
    double _masterFreq;
  public:
    MotionCalculatorBase(double masterFrequency) {
      _masterFreq = masterFrequency;
    };
    
    virtual unsigned int getSequenceLength() {
      return 0;
    };
    
    virtual double getPosition(unsigned int t) {
      return 0;
    };
    
    virtual long getStepPosition(unsigned int t) {
      return (long) (getPosition(t));
    };
    
    virtual int getStepValue(unsigned int t) {
      long p1 = getStepPosition(t);
      long p2 = t == 0 ? 0 : getStepPosition(t - 1);
      return p1 > p2 ? 1 : p1 < p2 ? -1 : 0;
    };
};

//constant speed motion
class ConstVMotionCalculator : public MotionCalculatorBase
{
  private:
    double _spd;
  public:
    ConstVMotionCalculator(double freq) :MotionCalculatorBase(freq) {

    };
    
    virtual void setSpeed(double spd) {
      _spd = spd;
    };
    
    virtual double getPosition(unsigned int t) {
      return _spd * t / _masterFreq;  
    };
};

class TrapezoidalMotionCalculator : MotionCalculatorBase
{
  protected:
    double _maxV;
    double _accel;
    int _targetPos;
    int _curPos;
    int _phase;
    
    
    
  public:
    TrapezoidalMotionCalculator(double freq) : MotionCalculatorBase(freq) {
    };
    
    void setMotionParams(int destinationPosition, double maxVelocity, double maxAccel)
    {
      
    }
    
    
    
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
unsigned int pins[] = {4, 5, 6, 7};

SteppoState steppo(phases8, sizeof(phases8) / sizeof(unsigned int), pins, sizeof(pins) / sizeof(unsigned int));

void tick(void) {
  counter++;
  steppo.makeStep(-1);
  //steppo.tick();
};



ConstVMotionCalculator calc(20000);
unsigned int t = 0;





void setup()
{
  calc.setSpeed(5000);

  Serial.begin(9600);
  Serial.println("hello\n");
  int prescale = TCCR1B & 0x7;
  Serial.print("prescale:");
  Serial.println(prescale);
  for (int i=0; i<sizeof(pins) / sizeof(unsigned int); i++) {
    pinMode(i, OUTPUT); 
  };
  cli();
  Timer3.initialize(2000);
  Timer3.attachInterrupt(tick);
  //SetupTimer2(40000);
  //TCNT1 = 20000;
  //TIMSK1 |= (1 << TOIE1);
  //TCCR1B = (TCCR1B & ~0x7) | 0x1;
//  TCCR1B |= 0x1; //timer 1 prescale 8
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
//digitalWrite(LEDPIN, !digitalRead(LEDPIN));
// or use: PORTB ^= _BV(PB5);// PB5 =pin 19 is digitalpin 13
}

void loop()
{
  delay(1000);
  Serial.print("pos:");
  Serial.print(calc.getPosition(t));
  Serial.print(" ");
        Serial.println(calc.getStepValue(t));
    t++;
/*  Serial.print("counter:");
  Serial.println(counter);
  Serial.print("steppo: ");
  Serial.print(steppo.getCurOutputs());
  Serial.print(" ");
  Serial.println(steppo.getCurPhase());
  counter = 0;
  */
}
 
