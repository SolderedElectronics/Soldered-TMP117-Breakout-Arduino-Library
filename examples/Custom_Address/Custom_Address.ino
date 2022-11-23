/**
 **************************************************
 *
 * @file        Custom_Address.ino
 * @brief       Demonstration on how to use custom addressing on TMP117
 *
 *
 *
 * @authors     Robert Soric @ soldered.com
 ***************************************************/

/**
 * The TMP117 breakout board can be connected to 4 different addresses via I2C.
 * This means you can use 4 TMP117 boards in the same project, but each one has to have a unique address.
 * To change the address, short only one of the jumper pins on the board:
 * 0x49: JP2 (comes shorted by default)
 * 0x48: JP7
 * 0x4A: JP6
 * 0x4B: JP5
 *
 * For more info, check TMP117 datasheet Table 7-2.
 */

#include "TMP117-SOLDERED.h"

TMP117 tempSensor;

void setup()
{
    Serial.begin(115200);        // Begin serial communication for output
    if (!tempSensor.begin(0x49)) // Sensor initialization, specify the sensor address here if not default
    {
        Serial.println("Failed to find TMP117");
        while (true)
        {
            delay(100);
        }
    }
    Serial.println("TMP117 found!");
}

void loop()
{
    sensors_event_t temp;
    tempSensor.getEvent(&temp); // Make measurement and store data
    Serial.print("Temperature: ");
    Serial.print(temp.temperature); // Print measurement
    Serial.println(" degrees C.");
    delay(1000);
}
