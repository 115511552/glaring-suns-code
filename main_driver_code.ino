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
  VemlSensor lux_sensor;
  Motor main_motor(2, 3, 7);

  Button on_btn(12, true);
  Button off_btn(11, true);

  constexpr bool serial_output = true;
  bool use_lux = true;
}

void setup() {
  if (Global::serial_output) {
    Serial.begin(9600);
    Serial.println("~~~~");
  }

  if (Global::use_lux) {
    if (!Global::lux_sensor.setup()) {
      Global::use_lux = false;
      Serial.println("Veml has failed to initialize");
    }
  }

  Global::main_motor.setup();

  if (Global::serial_output) {
    Serial.println("setup");
  }
}

void loop() {
  if (Global::use_lux) {
    if (!Global::on_btn && !Global::off_btn) {
      /* if no buttons are active, use the automatic mode */
  
      if (Global::lux_sensor.is_safe()) {
        if (Global::lux_sensor.should_activate()) {  
          auto state = Global::lux_sensor.get_state();

          if (Global::serial_output) {
            Serial.print("State change: ");
            Serial.print(state);
            Serial.print(" <read at ");
            Serial.print(Global::lux_sensor.get_lux());
            Serial.println("f>");
          }
    
          /* below -> downwards. might need to fix this at some point */
          auto new_direction = static_cast<Motor::Direction>(state);
          Global::main_motor.begin_move_with_direction(new_direction);
        }
      }
    }
  }

  /* buttons should be never on and off but whatever */
  if (Global::on_btn.state_changed() && Global::on_btn) {
      Global::main_motor.begin_move_with_direction(Motor::Direction::Upwards);      
  }

  if (Global::off_btn.state_changed() && Global::off_btn) {
      Global::main_motor.begin_move_with_direction(Motor::Direction::Downwards);
  }

  Global::main_motor.on_loop();
}
