/**
 * Main code for Glaring Suns
 * Originally wrriten in March 2021
 * Designed for Arduino Uno
 * 
 * Requirements:
 * Adafruit VEML7700 on serial ports
 * 2 Buttons plugged into ports 11 and 12
 * A Vex Quadrature Encoder plugged into ports 2/3
 * A Vex 393 Motor plugged into port 7
 * 
 * Libraries:
 * Adafruit VEML 7700
 * Encoder
 */

#include "veml_access.hpp"
#include "motor_code.hpp"
#include "button_access.hpp"

namespace Global {
  auto lux_sensor = new VemlSensor();
  auto main_motor = new Motor(2, 3, 7);

  auto on_btn = new Button(12, true);
  auto off_btn = new Button(11, true);

  constexpr bool use_lux = false;
}

void setup() {
  Serial.begin(9600);
  Serial.println("~~~~");

  if (Global::use_lux) {
    Global::lux_sensor->setup();
  }

  Global::main_motor->setup();

  Serial.println("setup");
}

void loop() {
  if (Global::use_lux) {
    if (!Global::on_btn && !Global::off_btn) {
      /* if no buttons are active, use the automatic mode */
  
      if (Global::lux_sensor->is_safe()) {
        if (Global::lux_sensor->should_activate()) {
  
          auto state = Global::lux_sensor->get_state();
  
          /* below -> downwards. might need to fix this at some point */
          auto new_direction = static_cast<Motor::Direction>(state);
          Global::main_motor->begin_move_with_direction(new_direction);
        }
      }
    }
  }

  /* buttons should be never on and off but whatever */
  if (Global::on_btn->state_changed() && *Global::on_btn) {
      Global::main_motor->begin_move_with_direction(Motor::Direction::Upwards);      
  }

  if (Global::off_btn->state_changed() && *Global::off_btn) {
      Global::main_motor->begin_move_with_direction(Motor::Direction::Downwards);
  }

  Global::main_motor->on_loop();
}
