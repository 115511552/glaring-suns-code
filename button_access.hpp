#pragma once
#ifndef _BUTTON_ACCESS_H
#define _BUTTON_ACCESS_H

#include "Arduino.h"

class Button {
  public:
    enum State : bool {
      Activated = true,
      Unactivated = false,
    };

    static constexpr uint8_t DEBOUNCE_MAX = 6;
  private:
    const uint8_t _port;
    const bool _reversed;

    State _last_state = State::Unactivated;
    State _last_stable_state = State::Unactivated;

    uint8_t _debounce = 0;

  public:
    Button(uint8_t port, bool reversed);
    Button(uint8_t port);

    bool state_changed();
    State get_state() const;

    inline explicit operator bool() const {
        return static_cast<Button::State>(this->get_state());
    }
};

#endif
