#pragma once
#ifndef _VEML_ACCESS_H
#define _VEML_ACCESS_H

#include <Adafruit_VEML7700.h>

class VemlSensor {
  public:
    enum State : bool {
      AboveThreshold = true,
      BelowThreshold = false,
    };

    static constexpr float Threshold = 100.0f;

  private:
    Adafruit_VEML7700 _sensor = Adafruit_VEML7700();
    State _last_state;

  public:
    void setup();

    /** determines if the value that is read can be determined as accurate */
    bool is_safe();

    /** checks threshold and determines if action should be taken based on if threshold has changed since last read */
    bool should_activate();

    const State get_state();
};

#endif
