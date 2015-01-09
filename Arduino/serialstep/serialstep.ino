
#include <TimerThree.h>
#include <IntSingleAxisTrapezGenerator.h>
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
IntSingleAxisTrapezGenerator gen;
long resolution = 10000;
double axisPos = 0.0;

void tick(void) {
  counter++;
  if (gen.MotionInProgress()) {
    gen.NextStep();
    long pos = gen.GetCurrentPosition();
    double newPos = ((double) pos) / resolution;
    
  };
  
  steppo.makeStep(-1);
  //steppo.tick();
};




unsigned int t = 0;





void setup()
{
  Serial.begin(9600);
  Serial.println("hello\n");
  int prescale = TCCR1B & 0x7;
  Serial.print("prescale:");
  Serial.println(prescale);
  for (int i=0; i<sizeof(pins) / sizeof(unsigned int); i++) {
    pinMode(i, OUTPUT); 
  };
  cli();
  Timer3.initialize(100000);
  Timer3.attachInterrupt(tick);
  
  //motion path gen
  gen.SetCurrentPosition(0);
  gen.SetAcceleration(0.002 * resolution);
  gen.SetMaxVelocity(0.03 * resolution);
  gen.SetTargetPosition(4L * resolution);

  gen.PrepareTrajectory();
  Serial.print("dest: ");
  Serial.print(gen.GetTargetPosition());
   Serial.print(",maxvel: ");
  Serial.print(gen.GetCurrentVelocity());
  Serial.print(",dec: ");
  Serial.print(gen.GetDeceleration());  
  Serial.println("");

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
  Serial.print("step:");
  Serial.print(gen.GetStepCount());
  Serial.print("/");
  Serial.print(gen.GetMotionEndStep() - gen.GetStepCount());
  Serial.print(", pos:");
  Serial.print(gen.GetCurrentPosition());
    Serial.print("/");
  Serial.print(gen.GetTargetPosition() - gen.GetCurrentPosition());
  
  Serial.print(", vel:");
  Serial.print(gen.GetCurrentVelocity());
    Serial.print(", dec:");
  Serial.print(gen.GetDeceleration());
  Serial.println("");
  Serial.print(" ");

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
 
