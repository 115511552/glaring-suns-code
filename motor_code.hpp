#pragma once
#ifndef _MOTOR_CODE_H
#define _MOTOR_CODE_H

#include <Encoder.h>
#include <Servo.h>

class Motor {
  public:
    enum Direction : bool {
      Upwards = true,
      Downwards = false,
    };

    enum Max_Speed : unsigned int {
      Forwards = 160,
      Backwards = 20
    };

    static constexpr long Max_Pos = 2000;

  private:
    const unsigned int _motor_port;

    bool _active = false;
    Direction _current_direction = Direction::Downwards;

    Servo _motor_393;
    Encoder _motor_393_enc;

  public:
    Motor(int, int, int);

    void setup();
    void on_loop();

    void begin_move_with_direction(Direction);
    void quick_stop();
};

#endif
