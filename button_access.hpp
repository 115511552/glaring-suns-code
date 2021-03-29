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

    static constexpr auto DEBOUNCE_MAX = 100;
  private:
    const unsigned int _port;
    const bool _reversed;

    State _last_state = State::Unactivated;
    State _last_stable_state = State::Unactivated;

    int _debounce = 0;

  public:
    Button(int port, bool reversed);
    Button(int port);

    bool state_changed();
    State get_state() const;

    explicit operator bool() const {
        return static_cast<Button::State>(this->get_state());
    }
};

#endif
