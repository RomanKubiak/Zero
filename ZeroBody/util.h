#ifndef __ZERO_UTIL_H__
#define __ZERO_UTIL_H__
#include <Arduino.h>
#include "../shared/config.h"
class Servo;
Servo *get_servo_by_function(servo_function f);
void initialize_servos();
static struct current_status_t body_health;
#endif