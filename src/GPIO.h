#pragma once
#include <Arduino.h>

// Sensor
#define PIN_THERMAL_SENSOR_5V -1    // Connected to 5V rail
#define PIN_THERMAL_SENSOR A0


#define PIN_LCD_SDA A4
#define PIN_LCD_SCL A5


// Stepper Motor Pins
#define PIN_MOTOR_1 10 // blue
#define PIN_MOTOR_2 11 // pink
#define PIN_MOTOR_3 12 // yellow
#define PIN_MOTOR_4 13 // orange

// Heater
#define PIN_HEATER 3

// LEDs
#define PIN_LED_MAIN_PWR 0
#define PIN_LED_HTR_WRN 1
#define PIN_LED_HTR_RDY 2

// Inputs
#define PIN_IN_HTR_SW 4

#define NUM_GPIOS 5


class GPIO
{
public:
    GPIO() {}
    void init()
    {
        // Outputs
        pinMode(PIN_LED_MAIN_PWR, OUTPUT);
        pinMode(PIN_LED_HTR_WRN, OUTPUT);
        pinMode(PIN_LED_HTR_RDY, OUTPUT);
        pinMode(PIN_HEATER, OUTPUT);

        // Inputs
        pinMode(PIN_IN_HTR_SW, INPUT);    

        // Default states
        digitalWrite(PIN_LED_MAIN_PWR, HIGH);
        digitalWrite(PIN_LED_HTR_WRN, LOW);
        digitalWrite(PIN_LED_MAIN_PWR, LOW);
        digitalWrite(PIN_HEATER, LOW);

        for(int i = 0; i < NUM_GPIOS; i++)
        {
            m_states[i] = digitalRead(i);
        }
    }

    void update()
    {
        bool old_states[NUM_GPIOS];
        memcpy(old_states, m_states,  sizeof(m_states[0]) * NUM_GPIOS);

        for(int i = 0; i < NUM_GPIOS; i++)
        {
            m_states[i] = digitalRead(i);

            // If state has changed
            if(m_states[i] != old_states[i])
            {
                Serial.print("GPIO ");
                Serial.print(i);
                Serial.print(" changed to ");
                Serial.println(m_states[i]);
            }
        }

    }

private:
    bool m_states[NUM_GPIOS];
};


GPIO gpio;
