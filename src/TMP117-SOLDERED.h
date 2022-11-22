/**
 **************************************************
 *
 * @file        Generic-easyC-SOLDERED.h
 * @brief       Header file for sensor specific code.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     @ soldered.com
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
};

#endif //!_TMP117_
