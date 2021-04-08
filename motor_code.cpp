#include "motor_code.hpp"

Motor::Motor(int enc_port_1, int enc_port_2, int motor_port) :
  _motor_393_enc(Encoder(enc_port_1, enc_port_2)),
  _motor_port(motor_port) { }

void Motor::setup() {
  this->_motor_393_enc.write(0);
  this->_motor_393.attach(_motor_port);
}

void Motor::on_loop() {
  if (!this->_active) {
    return;
  }

  long newPos = this->_motor_393_enc.read();

  if (abs(newPos) >= Motor::Max_Pos) {
    this->_motor_393.write(90);
    this->_active = false;
  }
}

void Motor::begin_move_with_direction(Motor::Direction n_direction) {
  if (this->_current_direction == n_direction) {
    /*
       proceeds to move twice
    */
    return;
  }

  if (this->_active) {
    this->quick_stop();
  }

  this->_current_direction = n_direction;
  this->_motor_393_enc.write(0);

  auto motor_speed = static_cast<bool>(this->_current_direction) ? Motor::Max_Speed::Forwards : Motor::Max_Speed::Backwards;

  this->_motor_393.write(motor_speed);
  this->_active = true;
}

bool Motor::is_active() const {
  return this->_active;
}

void Motor::quick_stop() {
  this->_motor_393.write(90);
  this->_active = false;
}
