#pragma once
#ifndef _MOTOR_CODE_H
#define _MOTOR_CODE_H

#include <Encoder.h>
#include <Servo.h>

class Motor {
  public:
    enum class Direction : bool {
      Upwards = true,
      Downwards = false,
    };

    enum class Max_Speed : int16_t {
      Forwards = 120,
      Backwards = 60
    };

    static constexpr long Max_Pos = 1500;

  private:
    const uint8_t _motor_port;

    bool _active = false;
    Direction _current_direction = Direction::Downwards;

    const Servo _motor_393;
    const Encoder _motor_393_enc;

  public:
    Motor(uint8_t, uint8_t, uint8_t);

    void setup();
    void on_loop();

    void begin_move_with_direction(Direction);
    void quick_stop();
    
    bool is_active() const;

    inline explicit operator bool() const {
        return this->is_active();
    }
};

#endif
