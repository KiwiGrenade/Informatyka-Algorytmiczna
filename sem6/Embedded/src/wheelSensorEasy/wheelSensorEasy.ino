#define DECODE_NEC
#include <IRremote.hpp>
#include "Wheels.h"
//#include "PinChangeInterrupt.h"

#define IR_RECEIVE_PIN 2
#define INTINPUT0 A0
#define INTINPUT1 A1

Wheels w;
volatile int cnt0, cnt1;

void WH_setup() {
  w.attach(8,7,11,5,4,10);
  w.setSpeed(80);

  w.forward();

  Serial.begin(9600);

  pinMode(INTINPUT0, INPUT);
  pinMode(INTINPUT1, INPUT);

  cnt0=0;
  cnt1=0;

// attachPCINT(digitalPinToPCINT(INTINPUT0), increment, CHANGE);
// attachPCINT(digitalPinToPCINT(INTINPUT1), increment, CHANGE);
}

void IR_setup(){
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void setup(){
//  WH_setup();
  IR_setup();
}

void loop() {
  if(IrReceiver.decode()){
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
            // We have an unknown protocol here, print extended info
            IrReceiver.printIRResultRawFormatted(&Serial, true);
            IrReceiver.resume(); // Do it here, to preserve raw data for printing with printIRResultRawFormatted()
        } else {
            IrReceiver.resume(); // Early enable receiving of the next IR frame
            IrReceiver.printIRResultShort(&Serial);
            IrReceiver.printIRSendUsage(&Serial);
        }
        Serial.println();

        /*
         * Finally, check the received data and perform actions according to the received command
         */
        if (IrReceiver.decodedIRData.command == 0x10) {
            // do something
        } else if (IrReceiver.decodedIRData.command == 0x11) {
            // do something else
        }
  }
//  Serial.print(cnt0);
//  Serial.println(cnt1);
//  delay(250);
}

void increment() {
  if(digitalRead(INTINPUT0))
    cnt0++;
  else if(digitalRead(INTINPUT1))
    cnt1++;
}
