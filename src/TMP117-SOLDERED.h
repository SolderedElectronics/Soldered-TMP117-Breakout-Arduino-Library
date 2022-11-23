/**
 **************************************************
 *
 * @file        TMP117-SOLDERED.h
 * @brief       Header file for TMP117 library.
 *              For more info, visit solde.red/333175
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Robert Soric @ soldered.com
 ***************************************************/

#ifndef __TMP117__
#define __TMP117__

#include "Arduino.h"
#include "libs/Adafruit_TMP117.h"

class TMP117 : public Adafruit_TMP117
{
  public:
    TMP117() : Adafruit_TMP117()
    {
    }
    bool begin();
    bool begin(uint8_t _i2c_addr);
};

#endif //!_TMP117_
