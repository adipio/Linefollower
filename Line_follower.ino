
//Line following robot code Arduino UNO
//Ask speed pwd if it clears?
//run camands?

#include <Servo.h>
#define Stop 0 //pwm
#define slow 10 //pwm
#define normal 15 //pwm
#define fast 20 //pwm

#define turnOnSwitch 12 //pin

Servo leftMotor, rightMotor;

void setup() {
  leftMotor.attach(10);
  rightMotor.attach(11);
  leftMotor.write(0);
  rightMotor.write(0);
  DDRD = 0;
  Serial.begin(9600);
  pinMode(turnOnSwitch,INPUT_PULLUP);
  
}

void loop() {
  if (digitalRead(turnOnSwitch)==HIGH){
    byte IRArray = PIND; //values of pins of port D into IRArray
    IRArray = IRArray >> 2; //move the bits so that the leftmost sensor is in bit 0
    //IRArray = ~IRArray; //if doesnt work uncomment line
    IRArray = IRArray & 0x1f; //mask out unused bits
    Serial.println(IRArray);
    
    switch (IRArray){
      case 1: //leftmost sensor
      rightMotor.write(normal);
      leftMotor.write(Stop);
      break;
      
      case 2: //middle-left sensor
      rightMotor.write(fast);
      leftMotor.write(normal);
      break;
      
      case 4: //middle sensor
      rightMotor.write(fast);
      leftMotor.write(fast);
      break;
      
      case 8: //middle-right sensor
      rightMotor.write(normal);
      leftMotor.write(fast);
      break;
      
      case 16://rightmost sensor
      rightMotor.write(Stop);
      leftMotor.write(normal);
      break;
      
      default:
      // do nothing if multiple sensors are active or no sensors are active
      break;
    }
    delay(25); //give the arduino a chance to generate the waveform before changing again
  }
}
