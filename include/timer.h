#pragma once

// These define's must be placed at the beginning before #include "TimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the
// system.
#define TIMER_INTERRUPT_DEBUG 2
#define _TIMERINTERRUPT_LOGLEVEL_ 4

#define USE_TIMER_1 false

#if (defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) ||   \
     defined(__AVR_ATmega644PA__) || defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO) ||      \
     defined(ARDUINO_AVR_MINI) || defined(ARDUINO_AVR_ETHERNET) || defined(ARDUINO_AVR_FIO) ||     \
     defined(ARDUINO_AVR_BT) || defined(ARDUINO_AVR_LILYPAD) || defined(ARDUINO_AVR_PRO) ||        \
     defined(ARDUINO_AVR_NG) || defined(ARDUINO_AVR_UNO_WIFI_DEV_ED) ||                            \
     defined(ARDUINO_AVR_DUEMILANOVE) || defined(ARDUINO_AVR_FEATHER328P) ||                       \
     defined(ARDUINO_AVR_METRO) || defined(ARDUINO_AVR_PROTRINKET5) ||                             \
     defined(ARDUINO_AVR_PROTRINKET3) || defined(ARDUINO_AVR_PROTRINKET5FTDI) ||                   \
     defined(ARDUINO_AVR_PROTRINKET3FTDI))
#define USE_TIMER_2 true
#warning Using Timer1
#else
#define USE_TIMER_3 true
#warning Using Timer3
#endif

#include "TimerInterrupt_Generic.h"

#if !defined(LED_BUILTIN)
#define LED_BUILTIN 13
#endif

#if USE_TIMER_1

void TimerHandler1(unsigned int outputPin = LED_BUILTIN)
{
  static bool toggle1 = false;

#if (TIMER_INTERRUPT_DEBUG > 1)
  Serial.print("ITimer1 called, millis() = ");
  Serial.println(millis());
#endif

  // timer interrupt toggles pin LED_BUILTIN
  digitalWrite(outputPin, toggle1);
  toggle1 = !toggle1;
}

#endif

unsigned int outputPin1 = LED_BUILTIN;
unsigned int outputPin = A0;

#define TIMER1_INTERVAL_MS 10000
#define TIMER1_FREQUENCY (float)(1000.0f / TIMER1_INTERVAL_MS)
#define TIMER1_DURATION_MS 0 //(10 * TIMER1_INTERVAL_MS)

#define TIMER_INTERVAL_MS 13000
#define TIMER_FREQUENCY (float)(1000.0f / TIMER_INTERVAL_MS)
#define TIMER_DURATION_MS 0 //(20 * TIMER_INTERVAL_MS)

#if (USE_TIMER_2 || USE_TIMER_3)

void TimerHandler(unsigned int outputPin = LED_BUILTIN)
{
  static bool toggle = false;

#if (TIMER_INTERRUPT_DEBUG > 1)
#if USE_TIMER_2
  Serial.print("ITimer2 called, millis() = ");
#elif USE_TIMER_3
  Serial.print("ITimer3 called, millis() = ");
#endif

  Serial.println(millis());
#endif

  // timer interrupt toggles outputPin
  digitalWrite(outputPin, toggle);
  toggle = !toggle;
}

#endif