/**
 **************************************************
 *
 * @file        TMP117-SOLDERED.cpp
 * @brief       Functions file for TMP117.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Robert Soric @ soldered.com
 ***************************************************/


#include "TMP117-SOLDERED.h"

/**
 * @brief           Begin at default i2c address for Soldered TMP117 breakout
 *
 * @return          True if successful, false if not
 */
bool TMP117::begin()
{
    return this->Adafruit_TMP117::begin(0x49);
}

/**
 * @brief           Begin at custom address, in case one has been set using the jumpers.
 *
 * @note            For more info, see example Custom_Address.ino
 *
 * @return          True if successful, false if not
 */
bool TMP117::begin(uint8_t _i2c_addr)
{
    return this->Adafruit_TMP117::begin(_i2c_addr);
}