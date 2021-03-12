#include "button_access.hpp"

Button::Button(int port, bool reverse) : _port(port), _reversed(reverse) {
  pinMode(this->_port, INPUT);
}

Button::Button(int port) : Button(port, false) { }

bool Button::state_changed() {
  auto current_state = this->get_state();
  if (current_state != this->_last_state) {
    this->_last_state = current_state;
    return true;
  }

  return false;
}

Button::State Button::get_state() const {
  auto current_status = digitalRead(this->_port);

  if (this->_reversed) {
    ~current_status;
  }
  return static_cast<Button::State>(current_status);
}
