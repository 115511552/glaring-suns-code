#include "button_access.hpp"

Button::Button(int port, bool reverse) : _port(port), _reversed(reverse) {
  pinMode(this->_port, INPUT);
}

Button::Button(int port) : Button(port, false) { }

bool Button::state_changed() {
  auto current_state = this->get_state();
  if (current_state != this->_last_state) {    
    this->_debounce = 0;
    this->_last_state = current_state;
    return false;
  }

  if (current_state != this->_last_stable_state && this->_debounce >= Button::DEBOUNCE_MAX) {
    this->_last_stable_state = current_state;  
    return true;
  } else {
    this->_debounce++;
  }

  return false;
}

Button::State Button::get_state() const {
  auto current_status = digitalRead(this->_port);

  if (this->_reversed) {
    current_status = !current_status;
  }

  return static_cast<Button::State>(current_status);
}
