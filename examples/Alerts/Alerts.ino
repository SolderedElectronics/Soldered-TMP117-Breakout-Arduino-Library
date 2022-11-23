/**
 **************************************************
 *
 * @file        Alerts.ino
 * @brief       Demonstration of alerts on TMP117
 *              For more info, visit solde.red/333175
 *
 *
 *
 * @authors     Robert Soric @ soldered.com
 ***************************************************/

#include "TMP117-SOLDERED.h"

TMP117 tempSensor;

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

    // High temp and low temp alert are available
    tempSensor.setHighThreshold(30.0);
    tempSensor.setLowThreshold(27.00);

    // This function enables or disables THERM mode on the device
    // In THERM mode, the low temp alert limit can be used as a hysteresis value
    // In other words, the high temperature alert stays triggered until a temperature below the low threshold is
    // measured Disabled by default
    tempSensor.thermAlertModeEnabled(false);
}

void loop()
{
    tmp117_alerts_t alerts; // Object to save and read alerts
    sensors_event_t temp;   // For storing measurement data

    // Note: Always read alerts before the temperature, as reading the temperature clears alerts
    tempSensor.getAlerts(&alerts); // Read alerts
    tempSensor.getEvent(&temp);    // Read temperature

    Serial.print("Temperature: ");
    Serial.print(temp.temperature); // Print measurement
    Serial.println(" degrees C.");

    Serial.print("High temperature alert active:");
    if (alerts.high) // Is true if the temperature is higher than the high threshold
    {
        Serial.println("True");
    }
    else
    {
        Serial.println("False");
    }

    Serial.print("Low temperature alert active:");
    if (alerts.low) // Is true if the temperature is higher than the high threshold
    {
        Serial.println("True");
    }
    else
    {
        Serial.println("False");
    }
    Serial.println("");

    delay(1500);
}
