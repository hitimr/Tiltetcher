#pragma once

#define V_SOURCE 5.0 // Source Voltage (5V from Arduino)
#define R1 3000.0    // Resistor for Temperature sensor

// Sensor data sheet:
// https://media.digikey.com/pdf/Data%20Sheets/Infineon%20PDFs/KT,KTY.pdf
#define ALPHA (0.00788)   // from data sheet
#define BETA (0.00001937) // from data sheet
#define R25 (1970.0)      // Sensor impedance at 25°C

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
#define SERIAL_BAUD_RATE 9600

#define ON 1
#define OFF 0

#include <arduino.h>
#include <assert.h>

#include "heater.h"
