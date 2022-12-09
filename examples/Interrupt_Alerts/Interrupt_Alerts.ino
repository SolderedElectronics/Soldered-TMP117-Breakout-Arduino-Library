/**
 **************************************************
 *
 * @file        Interrupt_Alerts.ino
 * @brief       Demonstration of reading high/low temperature alerts on the TMP117 via interrupt. 
 *              For more info visit solde.red/333175
 *
 *
 *
 * @authors     Robert Soric @ soldered.com
 ***************************************************/

#include "TMP117-SOLDERED.h" // Include sensor library

TMP117 tempSensor; // Create sensor object

// Important: connect to interrupt TODO todo

volatile bool isTempAlert = false;

void setup()
{
    Serial.begin(115200);    // Begin serial communication for output
    if (!tempSensor.begin(0x48)) // Sensor initialization, specify the sensor address here if not default
    {
        while (true)
        {
            Serial.println("Failed to find TMP117");
            delay(100);
        }
    }
    Serial.println("TMP117 found!");

    // High temp and low temp alert are available
    tempSensor.setHighThreshold(30.0);
    tempSensor.setLowThreshold(24.00);

    // This function enables or disables THERM mode on the device
    // In THERM mode, the low temp alert limit can be used as a hysteresis value
    // In other words, the high temperature alert stays triggered until a temperature below the low threshold is
    // measured Disabled by default
    tempSensor.thermAlertModeEnabled(false);

    pinMode(5, INPUT);
    attachInterrupt(5,ISR_tempAlert,CHANGE);
}

void ISR_tempAlert()
{
    Serial.println("Temp alert!");
    delay(100);
}

void loop()
{
    tmp117_alerts_t alerts; // Object to save and read alerts
    sensors_event_t temp;   // For storing measurement data

    // Note: Always read alerts before the temperature, as reading the temperature clears alerts
    tempSensor.getAlerts(&alerts); // Read alerts
    tempSensor.getEvent(&temp);    // Read temperature
    Serial.print("Measured  ");
    Serial.print(temp.temperature); // Print measurement
    Serial.println(" degrees C.");

    delay(1500);
}
