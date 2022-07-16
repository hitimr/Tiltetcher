#pragma once



// Stepper Motor Pins
#define PIN_MOTOR_1 10 // blue
#define PIN_MOTOR_2 11 // pink
#define PIN_MOTOR_3 12 // yellow
#define PIN_MOTOR_4 13 // orange

// Sensor
#define PIN_SENS A1

// Heater
#define PIN_HEATER 3
#define PIN_HEATER_LED 4
#define TEMP_CUTOFF_HIGH 45
#define TEMP_CUTOFF_LOW 42

// Misc
#define PRECISION 4
#define SERIAL_BAUD_RATE 115200

#define ON 1
#define OFF 0

#include <arduino.h>
#include <assert.h>

#include "timer.h"
#include "heater.h"
#include "motor.h"
