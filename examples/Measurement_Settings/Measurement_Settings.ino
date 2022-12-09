/**
 **************************************************
 *
 * @file        Measurement_Settings.ino
 * @brief       Demonstration of various custom settings for using the TMP117 sensor.
 *              Here you can see how to set the measurement mode, add a temperature offset, set the average sample count
 *              and a minimum delay between temperature reads. For more info, visit solde.red/333175
 *
 *
 *
 * @authors     Robert Soric @ soldered.com
 ***************************************************/

#include "TMP117-SOLDERED.h" // Include sensor library

TMP117 tempSensor; // Create sensor object

// Set an arbitrary temperature offset value
// This value can be positive or negative and will be summed with the final temperature reading
float offsetVal = 10.52;

void setup()
{
    Serial.begin(115200); // Begin serial communication for output

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
    /**
     * It's possible to take multiple individual measurements and then calculate the average from them
     * This way you can make them less sensitive to quick changes
     */

    // Setting the sample count to 8 samples
    tempSensor.setAveragedSampleCount(TMP117_AVERAGE_8X);

    Serial.print("Temperature averaged from ");
    switch (tempSensor.getAveragedSampleCount())
    {
    case TMP117_AVERAGE_1X:
        Serial.print(" 1");
        break;
    case TMP117_AVERAGE_8X:
        Serial.print(" 8");
        break;
    case TMP117_AVERAGE_32X:
        Serial.print(" 32");
        break;
    case TMP117_AVERAGE_64X:
        Serial.print(" 64");
        break;
    }
    Serial.println(" samples.");
    delay(1000);

    /**
     * Adjusting read delay shortens minimum time between readings
     * A smaller read delay means you will be able to detect quicker changes in temperature and determine when exactly
     * they happened.
     */

    // Setting the read delay to 125 ms
    tempSensor.setReadDelay(TMP117_DELAY_125_MS);

    Serial.print("Interval between reads is at least ");
    switch (tempSensor.getReadDelay())
    {
    case TMP117_DELAY_0_MS:
        Serial.print(0);
        break;
    case TMP117_DELAY_125_MS:
        Serial.print(125);
        break;
    case TMP117_DELAY_250_MS:
        Serial.print(250);
        break;
    case TMP117_DELAY_500_MS:
        Serial.print(500);
        break;
    case TMP117_DELAY_1000_MS:
        Serial.print(1000);
        break;
    case TMP117_DELAY_4000_MS:
        Serial.print(4000);
        break;
    case TMP117_DELAY_8000_MS:
        Serial.print(8000);
        break;
    case TMP117_DELAY_16000_MS:
        Serial.print(16000);
        break;
    }
    Serial.println(" ms.");
    delay(1000);

    /**
     * The TMP117 operates under 3 different measurement modes:
     *
     * TMP117_MODE_CONTINUOUS - New measurements are constantly made according to the interval determined by the sample
     * count and read delay
     *
     * TMP117_MODE_SHUTDOWN - Sensor is placed in a low power state and won't take measurements
     * until a different mode is set, lowers power consumption
     *
     * TMP117_MODE_ONE_SHOT - One single measurement is made in
     * the shortest time possible, then the sensor goes to shutdown
     */

    // Setting the measurement mode to one shot
    tempSensor.setMeasurementMode(TMP117_MODE_ONE_SHOT);
    Serial.print("Measurement mode: ");
    switch (tempSensor.getMeasurementMode())
    {
    case TMP117_MODE_SHUTDOWN:
        Serial.println("Shut down.");
        break;
    case TMP117_MODE_ONE_SHOT:
        Serial.println("One shot.");
        break;
    case TMP117_MODE_CONTINUOUS:
        Serial.println("Continuous.");
        break;
    }
    delay(1000);

    /**
     * TMP117 supports setting a temperature offset which then affects future measurements
     * It can be positive or negative, useful for adjusting for bias
     */

    // Set offset to custom value
    tempSensor.setOffset(offsetVal);
    Serial.print("Offset: ");
    Serial.print(offsetVal);
    Serial.println(" degrees C.");
    delay(1000);

    sensors_event_t temp;       // For storing measurement data
    tempSensor.getEvent(&temp); // Make measurement and store data
    Serial.print("Measured temperature with offset and custom settings: ");
    Serial.print(temp.temperature); // Print measurement
    Serial.println(" degrees C.");
}
