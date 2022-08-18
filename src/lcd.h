#pragma once
#include "thermal_sensor.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

#define NO_SCREEN 0
#define SCREEN_WARMUP 1
#define SCREEN_TEMPERATURE_INVALID 2
#define SCREEN_DEFAULT 3

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

#define SYMBOL_DEGREE 0
byte degree_symbol[] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};


class Display
{
public:
  Display() {}

  void init()
  {
    lcd.init();
    lcd.backlight();

    lcd.createChar(SYMBOL_DEGREE, degree_symbol);

    
    lcd.clear();
    last_screen = NO_SCREEN;
  }

  void screen_warm_up()
  {
    if (last_screen == SCREEN_WARMUP)
      return;

    lcd.clear();
    lcd.print("Warming up...");

    last_screen = SCREEN_WARMUP;
  }

  void screen_invalid_temp()
  {
    if( last_screen == SCREEN_TEMPERATURE_INVALID)
      return;

    lcd.setCursor(0, 0);
    lcd.print("ERR invalid temp");
    lcd.setCursor(0, 1);
    lcd.print("Heater disabled");

    last_screen = SCREEN_TEMPERATURE_INVALID;
  }

  void screen_default()
  {
     
    lcd.clear();
    lcd.print("Temp.    ");
    lcd.print(thermal_sensor.get_temperature());
    lcd.setCursor(14, 0);
    lcd.write(SYMBOL_DEGREE);
    lcd.print("C");	
    last_screen = SCREEN_DEFAULT;
  }

  void update()
  {
    if (millis() < WARMUP_TIME_MS)
    {
      screen_warm_up();
    }

    if (!thermal_sensor.is_valid())
    {
      screen_invalid_temp();
      return;
    }

    screen_default();
  }

private:
  int last_screen = NO_SCREEN;

};

Display display;