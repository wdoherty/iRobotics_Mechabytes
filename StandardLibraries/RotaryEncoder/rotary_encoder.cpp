#include <iostream>

#include "../wiringPiLib/wiringPi/wiringPi.h"

#include "rotary_encoder.hpp"

/*

             +---------+         +---------+      0
             |         |         |         |
   A         |         |         |         |
             |         |         |         |
   +---------+         +---------+         +----- 1

       +---------+         +---------+            0
       |         |         |         |
   B   |         |         |         |
       |         |         |         |
   ----+         +---------+         +---------+  1

*/

void re_decoder::_pulse(int gpio, int level, uint32_t tick)
{
   if (gpio == mygpioA) levA = level; else levB = level;

   if (gpio != lastGpio) /* debounce */
   {
      lastGpio = gpio;

      if ((gpio == mygpioA) && (level == 1))
      {
         if (levB) (mycallback_up)();
      }
      else if ((gpio == mygpioB) && (level == 1))
      {
         if (levA) (mycallback_down)();
      }
   }
}

void re_decoder::_pulseEx(int gpio, int level, uint32_t tick, void *user)
{
   /*
      Need a static callback to link with C.
   */

   re_decoder *mySelf = (re_decoder *) user;

   mySelf->_pulse(gpio, level, tick); /* Call the instance callback. */
}

re_decoder::re_decoder(int gpioA, int gpioB, re_decoderCB_t callback_up, re_decoderCB_t callback_down)
{
   mygpioA = gpioA;
   mygpioB = gpioB;

   mycallback = callback;

   levA=0;
   levB=0;

   lastGpio = -1;

   pinMode(gpioA, INPUT);
   pinMode(gpioB, INPUT);

   /* pull up is needed as encoder common is grounded */

   pullUpDnControl(gpioA, PUD_UP);
   pullUpDnControl(gpioB, PUD_UP);

   /* monitor encoder level changes */

   gpioSetAlertFuncEx(gpioA, _pulseEx, this);
   gpioSetAlertFuncEx(gpioB, _pulseEx, this);
   /*
   wiringPiISR(gpioA, INT_EDGE_BOTH, _pulseEx);
   wiringPiISR(gpioB, INT_EDGE_BOTH, _pulseEx);
   */

}

void re_decoder::re_cancel(void)
{
   gpioSetAlertFuncEx(mygpioA, 0, this);
   gpioSetAlertFuncEx(mygpioB, 0, this);
   /*
   wiringPiISR(gpioA, INT_EDGE_BOTH, 0);
   wiringPiISR(gpioB, INT_EDGE_BOTH, 0);
   */
}
