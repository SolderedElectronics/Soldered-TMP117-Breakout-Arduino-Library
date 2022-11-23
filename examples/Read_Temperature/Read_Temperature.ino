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

#include "TMP117-SOLDERED.h"

TMP117 tempSensor; // Create sensor object

void setup()
{
    Serial.begin(115200);    // Begin serial communication for output
    if (!tempSensor.begin()) // Sensor initialization, specify the sensor address here if not default
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
    sensors_event_t temp;       // Create an empty sensors_event_t object, used to store data made from measurements
    tempSensor.getEvent(&temp); // Make measurement in degrees celsius and store data
    Serial.print("Temperature: ");
    Serial.print(temp.temperature); // Print the measurement
    Serial.println(" degrees C.");
    delay(1000);
}
