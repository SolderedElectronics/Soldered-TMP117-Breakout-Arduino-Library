/**
 **************************************************
 *
 * @file        Read_Temperature.ino
 * @brief       Demonstration on how to read temperature on the TMP117 brekaout
 *              For more info, visit solde.red/333175
 *
 *
 *
 * @authors     Robert Soric @ soldered.com
 ***************************************************/

#include "TMP117-SOLDERED.h" // Include sensor library

/**
 * Connecting diagram:
 *
 * TMP117                       Dasduino Core / Connect / ConnectPlus
 * VCC------------------------->VCC
 * GND------------------------->GND
 * SCL------------------------->A5/IO5/IO22
 * SDA------------------------->A4/IO4/IO21
 * 
 * Or, simply use an easyC cable!
 * 
 */

TMP117 tempSensor; // Create sensor object

void setup()
{
    Serial.begin(115200);    // Begin serial communication for output
    if (!tempSensor.begin(0x48)) // Sensor initialization, specify the sensor address here if not default
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
    sensors_event_t temp;       // Create an empty sensors_event_t struct, used to store data made from measurements
    tempSensor.getEvent(&temp); // Make measurement in degrees celsius and store data
    Serial.print("Temperature: ");
    Serial.print(temp.temperature); // Print the measurement
    Serial.println(" degrees C.");
    delay(1000);
}
