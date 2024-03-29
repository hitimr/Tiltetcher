/****************************************************************************************************************************
  ISR_16_Timers_Array_Complex.ino
  For Arduino and Adadruit AVR 328(P) and 32u4 boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/TimerInterrupt
  Licensed under MIT license

  Now we can use these new 16 ISR-based timers, while consuming only 1 hardware Timer.
  Their independently-selected, maximum interval is practically unlimited (limited only by unsigned
long miliseconds) The accuracy is nearly perfect compared to software timers. The most important
feature is they're ISR-based timers Therefore, their executions are not blocked by bad-behaving
functions / tasks. This important feature is absolutely necessary for mission-critical tasks.

  Notes:
  Special design is necessary to share data between interrupt code and the rest of your program.
  Variables usually need to be "volatile" types. Volatile tells the compiler to avoid optimizations
that assume variable can not spontaneously change. Because your function may change variables while
your program is using them, the compiler needs this hint. But volatile alone is often not enough.
  When accessing shared variables, usually interrupts must be disabled. Even with volatile,
  if the interrupt changes a multi-byte variable between a sequence of instructions, it can be read
incorrectly. If your data is multiple variables, such as an array and a count, usually interrupts
need to be disabled or the entire sequence of your code which accesses the data.
*****************************************************************************************************************************/

// These define's must be placed at the beginning before #include "TimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the
// system.

#include "heater.h"
#include "thermal_sensor.h"
#include "motor.h"
#include "lcd.h"

#define TIMER_INTERRUPT_DEBUG 0
#define _TIMERINTERRUPT_LOGLEVEL_ 0

#if (defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) ||   \
     defined(__AVR_ATmega644PA__) || defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO) ||      \
     defined(ARDUINO_AVR_MINI) || defined(ARDUINO_AVR_ETHERNET) || defined(ARDUINO_AVR_FIO) ||     \
     defined(ARDUINO_AVR_BT) || defined(ARDUINO_AVR_LILYPAD) || defined(ARDUINO_AVR_PRO) ||        \
     defined(ARDUINO_AVR_NG) || defined(ARDUINO_AVR_UNO_WIFI_DEV_ED) ||                            \
     defined(ARDUINO_AVR_DUEMILANOVE) || defined(ARDUINO_AVR_FEATHER328P) ||                       \
     defined(ARDUINO_AVR_METRO) || defined(ARDUINO_AVR_PROTRINKET5) ||                             \
     defined(ARDUINO_AVR_PROTRINKET3) || defined(ARDUINO_AVR_PROTRINKET5FTDI) ||                   \
     defined(ARDUINO_AVR_PROTRINKET3FTDI))
#define USE_TIMER_1 true
//#warning Using Timer1
#else
#define USE_TIMER_3 true
#warning Using Timer3
#endif

#include "ISR_Timer_Generic.h"
#include "TimerInterrupt_Generic.h"

ISR_Timer ISR_timer;

// You have to use longer time here if having problem because Arduino AVR clock is low, 16MHz =>
// lower accuracy. Tested OK with 1ms when not much load => higher accuracy.
#define TIMER_INTERVAL_MS 5L

volatile uint32_t startMillis = 0;

void TimerHandler() { ISR_timer.run(); }

/////////////////////////////////////////////////

#define NUMBER_ISR_TIMERS 16

typedef void (*irqCallback)(void);

/////////////////////////////////////////////////

#define USE_COMPLEX_STRUCT false

#if USE_COMPLEX_STRUCT

typedef struct
{
  irqCallback irqCallbackFunc;
  uint32_t TimerInterval;
  unsigned long deltaMillis;
  unsigned long previousMillis;
} ISRTimerData;

// In NRF52, avoid doing something fancy in ISR, for example Serial.print()
// The pure simple Serial.prints here are just for demonstration and testing. Must be eliminate in
// working environment Or you can get this run-time error / crash

void doingSomething(int index);

#else

volatile unsigned long deltaMillis[NUMBER_ISR_TIMERS] = {0, 0, 0, 0, 0, 0, 0, 0,
                                                         0, 0, 0, 0, 0, 0, 0, 0};
volatile unsigned long previousMillis[NUMBER_ISR_TIMERS] = {0, 0, 0, 0, 0, 0, 0, 0,
                                                            0, 0, 0, 0, 0, 0, 0, 0};

// You can assign any interval for any timer here, in milliseconds
uint32_t TimerInterval[NUMBER_ISR_TIMERS] = {5000L,  10000L, 15000L, 20000L, 25000L, 30000L,
                                             35000L, 40000L, 45000L, 50000L, 55000L, 60000L,
                                             65000L, 70000L, 75000L, 80000L};

void doingSomething(int index)
{
  unsigned long currentMillis = millis();

  deltaMillis[index] = currentMillis - previousMillis[index];
  previousMillis[index] = currentMillis;
}

#endif

////////////////////////////////////
// Shared
////////////////////////////////////

void doingSomething0() { doingSomething(0); }

void proc_100ms()
{
  gpio.update();
}

void proc_25ms()
{
  thermal_sensor.update();
  doingSomething(2);
}

void proc_500ms()
{
  heater.update();  
  display.update();
  doingSomething(3);
}

void doingSomething4() { doingSomething(4); }

void doingSomething5() { doingSomething(5); }

void doingSomething6() { doingSomething(6); }

void doingSomething7() { doingSomething(7); }

void doingSomething8() { doingSomething(8); }

void doingSomething9() { doingSomething(9); }

void doingSomething10() { doingSomething(10); }

void doingSomething11() { doingSomething(11); }

void doingSomething12() { doingSomething(12); }

void doingSomething13() { doingSomething(13); }

void doingSomething14() { doingSomething(14); }

void doingSomething15() { doingSomething(15); }

#if USE_COMPLEX_STRUCT

ISRTimerData curISRTimerData[NUMBER_ISR_TIMERS] = {
    // irqCallbackFunc, TimerInterval, deltaMillis, previousMillis
    {doingSomething0, 500L, 0, 0},    {proc_100ms, 10000L, 0, 0},
    {proc_25ms, 15000L, 0, 0},  {proc_500ms, 20000L, 0, 0},
    {doingSomething4, 25000L, 0, 0},  {doingSomething5, 30000L, 0, 0},
    {doingSomething6, 35000L, 0, 0},  {doingSomething7, 40000L, 0, 0},
    {doingSomething8, 45000L, 0, 0},  {doingSomething9, 50000L, 0, 0},
    {doingSomething10, 55000L, 0, 0}, {doingSomething11, 60000L, 0, 0},
    {doingSomething12, 65000L, 0, 0}, {doingSomething13, 70000L, 0, 0},
    {doingSomething14, 75000L, 0, 0}, {doingSomething15, 80000L, 0, 0}};

void doingSomething(int index)
{
  unsigned long currentMillis = millis();

  curISRTimerData[index].deltaMillis = currentMillis - curISRTimerData[index].previousMillis;
  curISRTimerData[index].previousMillis = currentMillis;

  Serial.print("Timer called\n");
}

#else

irqCallback irqCallbackFunc[NUMBER_ISR_TIMERS] = {
    doingSomething0,  proc_100ms,  proc_25ms,  proc_500ms,
    doingSomething4,  doingSomething5,  doingSomething6,  doingSomething7,
    doingSomething8,  doingSomething9,  doingSomething10, doingSomething11,
    doingSomething12, doingSomething13, doingSomething14, doingSomething15};

#endif

void init_timer()
{

  // Timer0 is used for micros(), millis(), delay(), etc and can't be used
  // Select Timer 1-2 for UNO, 1-5 for MEGA, 1,3,4 for 16u4/32u4
  // Timer 2 is 8-bit timer, only for higher frequency
  // Timer 4 of 16u4 and 32u4 is 8/10-bit timer, only for higher frequency

#if USE_TIMER_1

  ITimer1.init();

  // Using ATmega328 used in UNO => 16MHz CPU clock ,

  if (ITimer1.attachInterruptInterval(TIMER_INTERVAL_MS, TimerHandler))
  {
    Serial.print(F("Starting  ITimer1 OK, millis() = "));
    Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer1. Select another freq. or timer"));

#elif USE_TIMER_3

  ITimer3.init();

  if (ITimer3.attachInterruptInterval(TIMER_INTERVAL_MS, TimerHandler))
  {
    Serial.print(F("Starting  ITimer3 OK, millis() = "));
    Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer3. Select another freq. or timer"));

#endif

  ISR_timer.setInterval(1000L, proc_100ms);
  ISR_timer.setInterval(25L, proc_25ms);
  ISR_timer.setInterval(500, proc_500ms);
  // Just to demonstrate, don't use too many ISR Timers if not absolutely necessary
  // You can use up to 16 timer for each ISR_Timer
  for (uint16_t i = 0; i < NUMBER_ISR_TIMERS; i++)
  {
#if USE_COMPLEX_STRUCT
    curISRTimerData[i].previousMillis = startMillis;
    ISR_timer.setInterval(curISRTimerData[i].TimerInterval, curISRTimerData[i].irqCallbackFunc);
#else
    previousMillis[i] = startMillis;
    ISR_timer.setInterval(TimerInterval[i], irqCallbackFunc[i]);
#endif
  }
}