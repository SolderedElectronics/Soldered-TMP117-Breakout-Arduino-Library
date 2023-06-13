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
 * TMP117                       Dasduino
 * ALR------------------------->INT_PIN (set by user)
 */

#define INT_PIN 2 // Change interrupt pin here, it has to be a pin which supports interrupts

TMP117 tempSensor; // Create sensor object

volatile bool isTempAlert = false;

void setup()
{
    Serial.begin(115200);        // Begin serial communication for output
    if (!tempSensor.begin()) // Sensor initialization, specify the sensor address here if not default
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

    // Attatch the interrupt
    pinMode(INT_PIN, INPUT);
    attachInterrupt(INT_PIN, ISR_tempAlert, CHANGE);
}

void ISR_tempAlert()
{
    // The temp. threshold has been reached!
    // Set the flag!
    isTempAlert = true;
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

    // Print the alert message if there was an interrupt
    if (isTempAlert)
    {
        Serial.println("Temp. alert!");

        // Clear the flag back to it's default state
        isTempAlert = false;
    }

    delay(1500);
}
