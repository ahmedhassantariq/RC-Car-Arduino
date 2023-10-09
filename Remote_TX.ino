#include "SPI.h"
#include "NRFLite.h"

const static uint8_t RADIO_ID = 1; 
const static uint8_t DESTINATION_RADIO_ID = 0;
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
    if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN))
    {
        Serial.println("Error");
        while (1);
    }
    
}

void loop()
{
    _radioData.throttle = analogRead(A0);
    _radioData.steering = analogRead(A1);
    _radio.send(DESTINATION_RADIO_ID, &_radioData, sizeof(_radioData),NRFLite::NO_ACK); 
    
}
