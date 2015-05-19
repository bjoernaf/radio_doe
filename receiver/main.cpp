/**
* Receiver
*
*
*/

#include <Arduino.h>
#include <SPI.h>

#define SPI_DAC_SELECT_PIN (3)
#define SPI_ADC_SELECT_PIN (2)
#define DELAY (0)
#define COUNT_UP (true)
#define COUNT_DOWN (false)

void transferDataToDac(int DacSelectPin, int outputValue) {

    // Select the DAC on the SPI bus
    digitalWrite(DacSelectPin, LOW);
    
    // Send the data in two bytes.
    char data = 0;
    data = highByte(outputValue);
    data = 0b00001111 & data;
    data = 0b00110000 | data;
    SPI.transfer(data);
    data = lowByte(outputValue);
    SPI.transfer(data);
    
    // Deselect the DAC on the SPI bus
    digitalWrite(DacSelectPin, HIGH);
    
    delay(DELAY);

}

unsigned int transferDataFromAdc(int AdcSelectPin) {

    // Select the ADC on the SPI bus.
    digitalWrite(AdcSelectPin, LOW);
    
    // Send the correct code to initialize the transfer, and then transfer
    // both bytes back. We do not care what we send the second time.
    byte request = 208; // http://www.farnell.com/datasheets/1669376.pdf
    byte responseHigh = SPI.transfer(request);
    byte responseLow  = SPI.transfer((char) 0);
    byte responseLSB  = SPI.transfer((char) 0);

    /*Serial.write("*** responseHigh (<<8)=");
    Serial.write((unsigned int) responseHigh << 8);
    Serial.write(" responseLow=");
    Serial.write((unsigned int) responseLow);
    Serial.write("\n\r");*/

    //unsigned int response = ((responseHigh << 8) & 3840);
    unsigned int response = (((unsigned int) responseHigh & 7) << 9) | (((unsigned int)responseLow) << 1) | (responseLSB >> 7);
    //unsigned int response = responseLow;

    // Deselect the ADC on the SPI bus.
    digitalWrite(AdcSelectPin, HIGH);

    return response;

}

void setup() {

    Serial.begin(4800);

    //set pin(s) to input and output
    pinMode(SPI_ADC_SELECT_PIN, OUTPUT);
    pinMode(SPI_DAC_SELECT_PIN, OUTPUT);
    SPI.begin(); // wake up the SPI bus.
    SPI.setBitOrder(MSBFIRST);
}    


void loop() {
/*
    while(!Serial.available())
        continue;

    byte check = Serial.read();

    // We have received the initialization.
    if (check == 100) {
        
        // Wait until we can read two variables.
        while(Serial.available() < 2)
            continue;

        byte valHigh = Serial.read();
        byte valLow  = Serial.read();
        unsigned int val = (((unsigned int) valHigh) << 8) | valLow;
        Serial.print("Read: ");
        Serial.print(val);
        Serial.print(" (");
        Serial.print(valHigh);
        Serial.print(", ");
        Serial.print(valLow);
        Serial.print(")");
        Serial.print("\n\r");

        transferDataToDac(SPI_DAC_SELECT_PIN, val);
    }
    */

    transferDataToDac(SPI_DAC_SELECT_PIN, Serial.read());
}

/**
 * Program entry point. Required when using arduino-mk instead of the official
 *   IDE.
 */
int main(int argc, char * argv[]) {
    init();
    setup();
    for(;;) {
        loop();
    }
}
