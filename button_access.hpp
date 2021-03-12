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

  private:
    const unsigned int _port;
    const bool _reversed;

    State _last_state = State::Unactivated;

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
