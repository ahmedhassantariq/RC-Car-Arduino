#include "SPI.h"
#include "NRFLite.h"
#include <SunFounder_TB6612_Motor_Driver.h>
#include <Servo.h>
Servo myservo;
TB6612 motorA (5,6);
TB6612 motorB(9,10);
const static uint8_t RADIO_ID = 0;
const static uint8_t PIN_RADIO_CE = 10;
const static uint8_t PIN_RADIO_CSN = 9;

struct RadioPacket
{
    uint16_t throttle;
    uint16_t steering;
};

NRFLite _radio;
RadioPacket _radioData;

void setup()
{
    Serial.begin(115200);
    myservo.attach(2);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    
    if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN))
    {
        Serial.println("Error");
        while (1);
    }
}

void loop()
{
    while (_radio.hasData())
    {
        _radio.readData(&_radioData);

          String msg = "";
          msg += "Throttle ";
          msg += _radioData.throttle;
          msg += ", Steering";
          msg += _radioData.steering;
          Serial.println(msg);

          myservo.write(map(_radioData.steering,0,1023,0,255));
          
          if(_radioData.throttle>600){
            digitalWrite(4, LOW);
            digitalWrite(5, HIGH);
            digitalWrite(6, LOW);
            digitalWrite(7, HIGH);
          } else if(_radioData.throttle<400){
            digitalWrite(4, HIGH);
            digitalWrite(5, LOW);
            digitalWrite(6, HIGH);
            digitalWrite(7, LOW);
          } else {
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
            digitalWrite(6, LOW);
            digitalWrite(7, LOW);
          }
    }
}
