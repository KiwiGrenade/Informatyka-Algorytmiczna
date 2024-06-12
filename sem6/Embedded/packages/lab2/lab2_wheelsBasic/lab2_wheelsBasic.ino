#include "Wheels.h"



Wheels w;
volatile char cmd;



// wheels
#define MOTOR_LEFT_EN            3  // bialy
#define MOTOR_LEFT_IN1           4  // szary
#define MOTOR_LEFT_IN2           2  // bordowy
#define MOTOR_LEFT_SENSOR       14  // to be discovered

#define MOTOR_RIGHT_EN           6  // żółty
#define MOTOR_RIGHT_IN1          7  // zielony
#define MOTOR_RIGHT_IN2          5  // niebieski
#define MOTOR_RIGHT_SENSOR      15  // to be discovered

void setup() {
  // put your setup code here, to run once:
  
  w.attach( MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2, MOTOR_RIGHT_EN, // right
            MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, MOTOR_LEFT_EN);   // left
  
  Serial.begin(9600);
  Serial.println("Forward: WAD");
  Serial.println("Back: ZXC");
  Serial.println("Stop: S");

}

void loop() {
  while(Serial.available())
  {
    cmd = Serial.read();
    switch(cmd)
    {
      case 'w': w.forward(); break;
      case 'x': w.back(); break;
      case 'a': w.forwardLeft(); break;
      case 'd': w.forwardRight(); break;
      case 'z': w.backLeft(); break;
      case 'c': w.backRight(); break;
      case 's': w.stop(); break;
      case '1': w.setSpeedLeft(75); break;
      case '2': w.setSpeedLeft(200); break;
      case '9': w.setSpeedRight(75); break;
      case '0': w.setSpeedRight(200); break;
      case '5': w.setSpeed(100); break;
    }
  }
}
