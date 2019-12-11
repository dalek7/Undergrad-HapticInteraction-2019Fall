#include <math.h>

int pwmPin = 5; // PWM output pin for motor 1
int dirPin = 8; // direction output pin for motor 1

#define SAMPLE_PERIOD  (double)0.0004 // 0.4ms sample period

void setup() {
  // put your setup code here, to run once:
  // Set up serial communication
  Serial.begin(38400);

  // Set PWM frequency
  setPwmFrequency(pwmPin, 1);

  // Output pins
  pinMode(pwmPin, OUTPUT);  // PWM pin for motor A
  pinMode(dirPin, OUTPUT);  // dir pin for motor A

  // Initialize motor
  analogWrite(pwmPin, 0);     // set to not be spinning (0/255)
  digitalWrite(dirPin, LOW);  // set direction


  //initialize output compare
  InitOC();
}

// Force output variables
double force = 0;           // force at the handle
double duty = 0;            // duty cylce (between 0 and 255)
int dirFlag = 0;
unsigned int output = 0;    // output command to the motor

void loop() {

  force = 1.0;
  
  if (dirFlag == 1)
  {
    digitalWrite(dirPin, HIGH);
  }
  else
  {
    digitalWrite(dirPin, LOW);
  }

  // Compute the duty cycle required to generate Tp (torque at the motor pulley)c
  duty = force;

  // Make sure the duty cycle is between 0 and 100%
  if (duty > 1)
  {
    duty = 1;
  }
  else if (duty < 0)
  {
    duty = 0;
  }
  output = (int)(duty * 255);  // convert duty cycle to output signal
  analogWrite(pwmPin, output); // output the signal
}

// --------------------------------------------------------------
// Function to set PWM Freq -- DO NOT EDIT
// --------------------------------------------------------------
void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if (pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch (divisor)
    {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if (pin == 5 || pin == 6)
    {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    }
    else
    {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  }
  else if (pin == 3 || pin == 11)
  {
    switch (divisor)
    {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

//initializes the output compare on timer 1 for performing calculations
void InitOC()
{
  //*******OUTPUT COMPARE ON CHANNEL 1******

  //see section 15.7: of ATmega328 datasheet
  //register descriptions section 17.11, page 158

  //  DDRB |= _BV(1); //set bit 5 as output direction, OC1A debug pin (Pin 9) ---> PIN 9 IS DIRECTION
  //B5 (11) will oscillate at half the freq

  //WGM3:0 set to 0,1,0,0 for output compare (clear timer on compare)
  //CTC mode, TOP = OCR1A, update immediate, TOV flag set on MAX
  //from table 15-4
  TCCR1A &= ~_BV(WGM11) & ~_BV(WGM10);
  TCCR1B &= ~_BV(WGM13);
  TCCR1B |= _BV(WGM12);

  //debug output
  //COM1A1:0 set to 0,1 for toggle --> set OC1A (B1) bit high (will clear at end of calculation) --> just toggle instead
  //from table 15-1 on page 134
  TCCR1A |= _BV(COM1A1) | _BV(COM1A0);
  TCCR1A &= ~_BV(COM1A1);

  //CS12:0 set to 1,0,0 for clk/256 prescaling: runs on 16MHz clock
  //table 15-5
  TCCR1B &= ~_BV(CS10) & ~_BV(CS11);
  TCCR1B |= _BV(CS12);

  //****CHANGE OCR1A TO MODULATE FREQUENCY
  //page 126: freq = f_clk / (N * (1 + OCR1A)), N = 256, f_clk = 16MHz (the 2 in the equation is because of toggling)
  //want period of 400us --> 2.5kHz
  //2.5kHz = 16 MHz / (256 * (1 + OCR1A)) --> OCR1A = 24
  OCR1A = 24;

  //interrupt enable

  TIMSK1 |= _BV(OCIE1A); //output compare interrupt timer 1A

}

long int cnt = 0;
//Timer 1 interrupt for performing position calculations
ISR(TIMER1_COMPA_vect)
{
  PORTB |= B00100000;

  cnt++;
  if (cnt % (2500/2) == 0)
  {
    if (dirFlag == 0)
    {
      dirFlag = 1;
    
      Serial.println('1');
    }
    else
    {
      dirFlag = 0;
      Serial.println('0');
    }
  }

PORTB &= ~B00100000;
//PORTB &= ~B00000001; //clear bit B1
}
