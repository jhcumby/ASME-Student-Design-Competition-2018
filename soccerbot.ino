/*
 Example sketch for the Xbox Wireless Reciver library - developed by Kristian Lauszus
 It supports up to four controllers wirelessly
 For more information see the blog post: http://blog.tkjelectronics.dk/2012/12/xbox-360-receiver-added-to-the-usb-host-library/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <XBOXRECV.h>


// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
XBOXRECV Xbox(&Usb);

#define dir_1 2
#define pwm_1 3
#define dir_2 4
#define pwm_2 5
#define dir_3 7
#define pwm_3 6
#define dir_4 8
#define pwm_4 A1
#define RELAY A0


void setup() {
  Serial.begin(115200);

pinMode(pwm_1,OUTPUT);
pinMode(dir_1,OUTPUT);
pinMode(pwm_2,OUTPUT);
pinMode(dir_2,OUTPUT);
pinMode(pwm_3,OUTPUT);
pinMode(dir_3,OUTPUT);
pinMode(pwm_4,OUTPUT);
pinMode(dir_4,OUTPUT);
pinMode(RELAY,OUTPUT);


#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.println(F("\r\nXbox Wireless Receiver Library Started"));
}

void loop() {
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 4; i++) {
      if (Xbox.Xbox360Connected[i]) {

        long LSx = Xbox.getAnalogHat(LeftHatX, i);
        long LSy = Xbox.getAnalogHat(LeftHatY, i);
        long RSx = Xbox.getAnalogHat(RightHatX, i);
        long RSy = Xbox.getAnalogHat(RightHatY, i);
               
        if (Xbox.getButtonPress(L2, i) || Xbox.getButtonPress(R2, i)) {
          Serial.print("L2: ");
          Serial.print(Xbox.getButtonPress(L2, i));
          Serial.print("\tR2: ");
          Serial.println(Xbox.getButtonPress(R2, i)); 
          //Xbox.setRumbleOn(Xbox.getButtonPress(L2, i), Xbox.getButtonPress(R2, i), i);
          }
          
          //For when the left joystick is directionless:
          analogWrite(pwm_1, 0);
          analogWrite(pwm_2, 0);
          analogWrite(pwm_3, 0);
          analogWrite(pwm_4, 0);
          digitalWrite(dir_1, LOW);
          digitalWrite(dir_2, LOW);
          digitalWrite(dir_3, LOW);
          digitalWrite(dir_4, LOW);
          digitalWrite(RELAY,LOW);
          
          //If any joystick value is received
          if (Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500 || Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500 || Xbox.getAnalogHat(RightHatX, i) > 7500 || Xbox.getAnalogHat(RightHatX, i) < -7500 || Xbox.getAnalogHat(RightHatY, i) > 7500 || Xbox.getAnalogHat(RightHatY, i) < -7500) {
            /*float LStheta = degrees(atan2(LSy,LSx));
            float LSmag = sqrt(sq(LSx)+sq(LSy));

            if (LSmag > 32767){
              LSmag = 32767;
            }
        
            Serial.print("Left Stick Magnitude: ");
            Serial.println(LSmag);
            Serial.print("Left Stick Angle: ");
            Serial.println(LStheta);
            Serial.println(" ");
            */
            
            //Move Forward:
            if (Xbox.getAnalogHat(LeftHatY, i) > 7500 && Xbox.getAnalogHat(LeftHatX, i) > -7500 && Xbox.getAnalogHat(LeftHatX, i) < 7500){
              Serial.print(F("LeftHatY: "));
              Serial.print(Xbox.getAnalogHat(LeftHatY, i));
              Serial.print("\t");
              Serial.print(F("LeftHatX: "));
              Serial.println(Xbox.getAnalogHat(LeftHatX, i));

             /* int fwd = map(Xbox.getAnalogHat(LeftHatY, i), 7500, 32767, 0, 255);*/

            //At full speed
             digitalWrite(dir_1, LOW);
             analogWrite(pwm_1, 255);
             digitalWrite(dir_2, HIGH);
             analogWrite(pwm_2, 255);
             digitalWrite(dir_3, LOW);
             analogWrite(pwm_3, 255);
             digitalWrite(dir_4, HIGH);
             analogWrite(pwm_4, 255);
             delay(10);
             }
             
//Move Backward:
          if (Xbox.getAnalogHat(LeftHatY, i) < -7500 && Xbox.getAnalogHat(LeftHatX, i) > -7500 && Xbox.getAnalogHat(LeftHatX, i) < 7500){
            Serial.print(F("LeftHatY: "));
            Serial.print(Xbox.getAnalogHat(LeftHatY, i));
            Serial.print("\t");
            Serial.print(F("LeftHatX: "));
            Serial.println(Xbox.getAnalogHat(LeftHatX, i));

            /*int bckwd = map(Xbox.getAnalogHat(LeftHatY, i),-7500,-32768,0,255);*/
            
            //At full speed
             digitalWrite(dir_1, HIGH);
             analogWrite(pwm_1, 255);
             digitalWrite(dir_2, LOW);
             analogWrite(pwm_2, 255);
             digitalWrite(dir_3, HIGH);
             analogWrite(pwm_3, 255);
             digitalWrite(dir_4, LOW);
             analogWrite(pwm_4, 255);
             delay(10);
             }

//Move Right:
          if (Xbox.getAnalogHat(LeftHatX, i) > 7500 && Xbox.getAnalogHat(LeftHatY, i) > -7500 && Xbox.getAnalogHat(LeftHatY, i) < 7500){
            Serial.print(F("LeftHatY: "));
            Serial.print(Xbox.getAnalogHat(LeftHatY, i));
            Serial.print("\t");
            Serial.print(F("LeftHatX: "));
            Serial.println(Xbox.getAnalogHat(LeftHatX, i));

            /*int right = map(Xbox.getAnalogHat(LeftHatX, i), 7500, 32767, 0, 255);*/
            
            //At full speed
             digitalWrite(dir_1, LOW);
             analogWrite(pwm_1, 255);
             digitalWrite(dir_2, LOW);
             analogWrite(pwm_2, 255);
             digitalWrite(dir_3, HIGH);
             analogWrite(pwm_3, 255);
             digitalWrite(dir_4, HIGH);
             analogWrite(pwm_4, 255);
             delay(10);
             }

//Move Left:
         if (Xbox.getAnalogHat(LeftHatX, i) < -7500 && Xbox.getAnalogHat(LeftHatY, i) > -7500 && Xbox.getAnalogHat(LeftHatY, i) < 7500) {
            Serial.print(F("LeftHatY: "));
            Serial.print(Xbox.getAnalogHat(LeftHatY, i));
            Serial.print("\t");
            Serial.print(F("LeftHatX: "));
            Serial.println(Xbox.getAnalogHat(LeftHatX, i));

            /*int left = map(Xbox.getAnalogHat(LeftHatX, i), -7500, -32768, 0, 255);*/

          //At full speed
            digitalWrite(dir_1, HIGH);
            analogWrite(pwm_1, 255);
            digitalWrite(dir_2, HIGH);
            analogWrite(pwm_2, 255);
            digitalWrite(dir_3, LOW);
            analogWrite(pwm_3, 255);
            digitalWrite(dir_4, LOW);
            analogWrite(pwm_4, 255);
            delay(10);
            }



//Move 45 degrees 
//Figure out HIGH's and LOW's
         if (Xbox.getAnalogHat(LeftHatX, i) > 15000 && Xbox.getAnalogHat(LeftHatY, i) > 7500) {
            Serial.print(F("LeftHatY: "));
            Serial.print(Xbox.getAnalogHat(LeftHatY, i));
            Serial.print("\t");
            Serial.print(F("LeftHatX: "));
            Serial.println(Xbox.getAnalogHat(LeftHatX, i));

            //At full speed
            digitalWrite(dir_1, LOW);
            analogWrite(pwm_1, 255);
            digitalWrite(dir_2, LOW);
            analogWrite(pwm_2, 0);
            digitalWrite(dir_3, HIGH);
            analogWrite(pwm_3, 0);
            digitalWrite(dir_4, HIGH);
            analogWrite(pwm_4, 255);
            delay(10);
            }


//Move 135 degrees 
//Figure out HIGH's and LOW's
         if (Xbox.getAnalogHat(LeftHatX, i) < -7500 && Xbox.getAnalogHat(LeftHatY, i) > 7500) {
            Serial.print(F("LeftHatY: "));
            Serial.print(Xbox.getAnalogHat(LeftHatY, i));
            Serial.print("\t");
            Serial.print(F("LeftHatX: "));
            Serial.println(Xbox.getAnalogHat(LeftHatX, i));

            //At full speed
            digitalWrite(dir_1, LOW);
            analogWrite(pwm_1, 0);
            digitalWrite(dir_2, HIGH);
            analogWrite(pwm_2, 255);
            digitalWrite(dir_3, LOW);
            analogWrite(pwm_3, 255);
            digitalWrite(dir_4, HIGH);
            analogWrite(pwm_4, 0);
            delay(10);
            }


//Move 255 degrees 
//Figure out HIGH's and LOW's
      if (Xbox.getAnalogHat(LeftHatX, i) < -7500 && Xbox.getAnalogHat(LeftHatY, i) < -7500) {
            Serial.print(F("LeftHatY: "));
            Serial.print(Xbox.getAnalogHat(LeftHatY, i));
            Serial.print("\t");
            Serial.print(F("LeftHatX: "));
            Serial.println(Xbox.getAnalogHat(LeftHatX, i));

            //At full speed
      digitalWrite(dir_1, HIGH);
      analogWrite(pwm_1, 255);
      digitalWrite(dir_2, LOW);
      analogWrite(pwm_2, 0);
      digitalWrite(dir_3, HIGH);
      analogWrite(pwm_3, 0);
      digitalWrite(dir_4, LOW);
      analogWrite(pwm_4, 255);
      delay(10);
    }

//Move 315 degrees 
//Figure out HIGH's and LOW's
 if (Xbox.getAnalogHat(LeftHatX, i) > 7500 && Xbox.getAnalogHat(LeftHatY, i) < -7500) {
            Serial.print(F("LeftHatY: "));
            Serial.print(Xbox.getAnalogHat(LeftHatY, i));
            Serial.print("\t");
            Serial.print(F("LeftHatX: "));
            Serial.println(Xbox.getAnalogHat(LeftHatX, i));

            //At full speed
      digitalWrite(dir_1, LOW);
      analogWrite(pwm_1, 0);
      digitalWrite(dir_2, LOW);
      analogWrite(pwm_2, 255);
      digitalWrite(dir_3, HIGH);
      analogWrite(pwm_3, 255);
      digitalWrite(dir_4, HIGH);
      analogWrite(pwm_4, 0);
      delay(10);
    }

//Counterclockwise Movement

          if (Xbox.getAnalogHat(RightHatX, i) < -7500 /*&& Xbox.getAnalogHat(RightHatY, i) > -7500 && Xbox.getAnalogHat(RightHatY, i) < 7500*/){
            Serial.print(F("RightHatX: "));
            Serial.print(Xbox.getAnalogHat(RightHatX, i));
            Serial.print("\t");
            Serial.print(F("RightHatY: "));
            Serial.println(Xbox.getAnalogHat(RightHatY, i));
            
            int rotateccw = map(Xbox.getAnalogHat(RightHatX, i),-7500,-32768,0,255);
            Serial.print("CCW rotation speed: ");
            Serial.println(rotateccw);
        
            
            //variable speed
            digitalWrite(dir_1, HIGH);
            analogWrite(pwm_1, rotateccw);
            digitalWrite(dir_2, HIGH);
            analogWrite(pwm_2, rotateccw);
            digitalWrite(dir_3, HIGH);
            analogWrite(pwm_3, rotateccw);
            digitalWrite(dir_4, HIGH);
            analogWrite(pwm_4, rotateccw);
            delay(10);
          }
              
             /* else {
                digitalWrite(dir_1, HIGH);
                analogWrite(pwm_1, 0);
                digitalWrite(dir_2, HIGH);
                analogWrite(pwm_2, 0);
                digitalWrite(dir_3, HIGH);
                analogWrite(pwm_3, 0);
                digitalWrite(dir_4, HIGH);
                analogWrite(pwm_4, 0);
              }
              */

//Clockwise movement
         if (Xbox.getAnalogHat(RightHatX, i) > 7500 /*&& Xbox.getAnalogHat(RightHatY, i) > -7500 && Xbox.getAnalogHat(RightHatY, i) < 7500*/){
             Serial.print(F("RightHatX: "));
            Serial.print(Xbox.getAnalogHat(RightHatX, i));
            Serial.print("\t");
            Serial.print(F("RightHatY: "));
            Serial.println(Xbox.getAnalogHat(RightHatY, i));

            int rotatecw = map(Xbox.getAnalogHat(RightHatX, i),7500,32767,0,255);
            Serial.print("CW rotation speed: ");
            Serial.println(rotatecw);
            
            //Variable speed 
            digitalWrite(dir_1, LOW);
            analogWrite(pwm_1, rotatecw);
            digitalWrite(dir_2, LOW);
            analogWrite(pwm_2, rotatecw);
            digitalWrite(dir_3, LOW);
            analogWrite(pwm_3, rotatecw);
            digitalWrite(dir_4, LOW);
            analogWrite(pwm_4, rotatecw);
            delay(10);
         }
              else {
                digitalWrite(dir_1, LOW);
                analogWrite(pwm_1, 0);
                digitalWrite(dir_2, LOW);
                analogWrite(pwm_2, 0);
                digitalWrite(dir_3, LOW);
                analogWrite(pwm_3, 0);
                digitalWrite(dir_4, LOW);
                analogWrite(pwm_4, 0);
              }  
        }
       

        if (Xbox.getButtonClick(UP, i)) {
          Xbox.setLedOn(LED1, i);
          Serial.println(F("Up"));
        }
        if (Xbox.getButtonClick(DOWN, i)) {
          Xbox.setLedOn(LED4, i);
          Serial.println(F("Down"));
        }
        if (Xbox.getButtonClick(LEFT, i)) {
          Xbox.setLedOn(LED3, i);
          Serial.println(F("Left"));
        }
        if (Xbox.getButtonClick(RIGHT, i)) {
          Xbox.setLedOn(LED2, i);
          Serial.println(F("Right"));
        }

        if (Xbox.getButtonClick(START, i)) {
          Xbox.setLedMode(ALTERNATING, i);
          Serial.println(F("Start"));
        }
        if (Xbox.getButtonClick(BACK, i)) {
          Xbox.setLedBlink(ALL, i);
          Serial.println(F("Back"));
        }
        if (Xbox.getButtonClick(L3, i))
          Serial.println(F("L3"));
        if (Xbox.getButtonClick(R3, i))
          Serial.println(F("R3"));

        if (Xbox.getButtonClick(L1, i))
          Serial.println(F("L1"));
        if (Xbox.getButtonClick(R1, i))
          Serial.println(F("R1"));
        if (Xbox.getButtonClick(XBOX, i)) {
          Xbox.setLedMode(ROTATING, i);
          Serial.print(F("Xbox (Battery: "));
          Serial.print(Xbox.getBatteryLevel(i)); // The battery level in the range 0-3
          Serial.println(F(")"));
        }
        if (Xbox.getButtonClick(SYNC, i)) {
          Serial.println(F("Sync"));
          Xbox.disconnect(i);
          }
        
        if (Xbox.getButtonClick(A, i)) {
          Serial.println(F("A"));
          digitalWrite(RELAY,HIGH);
          delay(100);
            }
        if (Xbox.getButtonClick(B, i))
          Serial.println(F("B"));
        if (Xbox.getButtonClick(X, i))
          Serial.println(F("X"));
        if (Xbox.getButtonClick(Y, i))
          Serial.println(F("Y"));
      
   }
  }
 }
}



