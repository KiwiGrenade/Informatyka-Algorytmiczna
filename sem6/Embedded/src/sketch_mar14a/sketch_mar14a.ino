//#include <LiquidCrystal_I2C.h>
#include "Wheels.h"
#include <Servo.h>
// #include <IRemote.hpp>

// SONAR
#define TRIG A4
#define ECHO A5
// SERVO
#define SERVO 3

Servo serwo;
Wheels w;
volatile char cmd;

void setup() {
  pinMode(TRIG, OUTPUT);    // TRIG startuje sonar
  pinMode(ECHO, INPUT);     // ECHO odbiera powracający impuls

  w.attach( 7,8,5,    // right
            12,4,6);  // left
  Serial.begin(9600);
  Serial.println("Forward: WAD");
  Serial.println("Back: ZXC");
  Serial.println("Stop: S");


  serwo.attach(SERVO);

}
// Remember about w.setSpeed on the wheels. Otherwise they won't turn!
void loop() {
  while(Serial.available())
  {
    cmd = Serial.read();
    switch(cmd)
    {
      case 'w': {
        w.forward();
        break;
      }
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
  serwo.write(90);
}

int getDistance() {
  unsigned long tot;      // czas powrotu (time-of-travel)
  unsigned int distance;
  digitalWrite(TRIG, HIGH);
  delay(10);
  digitalWrite(TRIG, LOW);
  tot = pulseIn(ECHO, HIGH);

/* prędkość dźwięku = 340m/s => 1 cm w 29 mikrosekund
 * droga tam i z powrotem, zatem:
 */
  distance = tot/58;
  return distance;
}

void lookAndTellDistance(byte angle) {


  Serial.print("Patrzę w kącie ");
  Serial.print(angle);
  serwo.write(angle);
  
/* uruchamia sonar (puls 10 ms na `TRIGGER')
 * oczekuje na powrotny sygnał i aktualizuje
 */
  Serial.print(": widzę coś w odległości ");
  Serial.println(getDistance());
}

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
