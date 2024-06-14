//#include <LiquidCrystal_I2C.h>
#include "Wheels.h"
#include "MyServo.h"
#include <TimerOne.h>
// #include <IRemote.hpp>

// pin 9 and 10 is taken by TimerOne

#define BEEPER_PIN              13

// wheels
#define MOTOR_LEFT_EN            3  // bialy
#define MOTOR_LEFT_IN1           4  // szary
#define MOTOR_LEFT_IN2           2  // bordowy
#define MOTOR_LEFT_SENSOR       14  // to be discovered

#define MOTOR_RIGHT_EN           6  // żółty
#define MOTOR_RIGHT_IN1          7  // zielony
#define MOTOR_RIGHT_IN2          5  // niebieski
#define MOTOR_RIGHT_SENSOR      15  // to be discovered

Wheels w;
volatile char cmd;

long int beeperPeriod = 50000000;

void setup() {
  // servo
  servo_initialize();
  
  // beeper
  // pinMode(BEEPER_PIN, OUTPUT);
  // Timer1.initialize();
  // TimerUpdate();
  // distanceUpdate();

  w.attach( MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2, MOTOR_RIGHT_EN, // right
            MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, MOTOR_LEFT_EN);   // left
  Serial.begin(9600);
  Serial.println("Forward: WAD");
  Serial.println("Back: ZXC");
  Serial.println("Stop: S");
}
// Remember about w.setSpeed on the wheels. Otherwise they won't turn!
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
      case 'p': scan(); break;
    }
  }
}

void scan() {
  for(byte angle = 0; angle < 180; angle+= 20) {
    lookAndTellDistance(angle);
    delay(500);
  }
  servo_set(90);
}


void lookAndTellDistance(byte angle) {
  Serial.print("Patrzę w kącie ");
  Serial.print(angle);
  servo_set(angle);
  
/* uruchamia sonar (puls 10 ms na `TRIGGER')
 * oczekuje na powrotny sygnał i aktualizuje
 */
  Serial.print(": widzę coś w odległości ");
  Serial.println(getDistance());
}

// void doBeep() {
//   digitalWrite(BEEPER_PIN, digitalRead(BEEPER_PIN) ^ 1);
// }

// void TimerUpdate() {
//   Timer1.detachInterrupt();
//   Timer1.attachInterrupt(doBeep, beeperPeriod);
// }

// void distanceUpdate() {
//   Timer1.detachInterrupt();
//   Timer1.attachInterrupt(scan, beeperPeriod);
// }

// byte LCDAddress = 0x27;

//LiquidCrystal_I2C lcd(LCDAddress, 16, 2);
  
// uint8_t arrowRight[8] =
// {
//     0b01000,
//     0b01100,
//     0b00110,
//     0b11111,
//     0b11111,
//     0b00110,
//     0b01100,
//     0b01000
// };

// int argIn = 0;

// void setup() {

//   Serial.begin(9600);
//   Serial.setTimeout(200);

//   lcd.init();
//   lcd.backlight();

//   lcd.createChar(0, arrowRight);
// }

// void loop() {

//   uint8_t barPos = 0;
  
//   argIn = Serial.parseInt(SKIP_ALL);
//   if(argIn <= 0) return;

//   lcd.clear();
//   lcd.setCursor(barPos, 1);
//   lcd.write(0);

//   for(int val=0;val<=argIn; val++) {
//     lcd.setCursor(0,0);
//     lcd.print(val);
//     barPos = map(val, 0, argIn, 0, 16);
//     lcd.setCursor(barPos, 1);
//     lcd.print('=');
//     lcd.write(0);
//     delay(20);
//   }
// }
