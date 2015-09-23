/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#include "Copter.h"
using namespace Linux;

bool was_batt_low;
bool was_armed;

#ifdef USERHOOK_INIT
void Copter::userhook_init()
{
    // put your initialisation code here
    // this will be called once at start-up
    was_batt_low = false;
    was_armed = false;
    //testing HAL version of gpio
    hal.gpio->pinMode(17, HAL_GPIO_OUTPUT);
    hal.gpio->pinMode(18, HAL_GPIO_OUTPUT);
    hal.gpio->write(17, LOW);
    hal.gpio->write(18, LOW);
}
#endif

#ifdef USERHOOK_FASTLOOP
void Copter::userhook_FastLoop()
{
    // put your 100Hz code here
}
#endif

#ifdef USERHOOK_50HZLOOP
void Copter::userhook_50Hz()
{
    // put your 50Hz code here
}
#endif

#ifdef USERHOOK_MEDIUMLOOP
void Copter::userhook_MediumLoop()
{
    // put your 10Hz code here
}
#endif

#ifdef USERHOOK_SLOWLOOP
void Copter::userhook_SlowLoop()
{
     // put your 3.3Hz code here

     // *** need to catch signal 17 (SIGCHLD) in libraries/AP_HAL_Linux/RCInput_Navio.cpp - see https://github.com/lowflyerUK/ardupilot/commit/04aefb66ea76dc83fb1a139a2fac2b871655d15a
     // *** need to initialise the gpios before running ArduCopter - do this in /etc/rc.local

     // latches gpio17 whenever battery voltage is low
     if ( battery.voltage() < g.fs_batt_voltage && !was_batt_low ) {
       // system("echo '1' > /sys/class/gpio/gpio17/value");
        hal.gpio->write(17, HIGH);
        was_batt_low = true;
     }

   // on change from not armed to armed
   if ( motors.armed() && !was_armed) {
      // switch on gpio18
     // system("echo '1' > /sys/class/gpio/gpio18/value");
      hal.gpio->write(18, HIGH);
      was_armed = true;
      // start script as use 'pi'
      system("start-stop-daemon --start -b --exec /home/pi/run_while_armed.sh --chuid pi");
      // reset battery low indication on gpio17
     // system("echo '0' > /sys/class/gpio/gpio17/value");
      hal.gpio->write(17, LOW);
      was_batt_low = false;
   }

   // on change from armed to not armed
   if ( !motors.armed() && was_armed) {
      // switch off gpio18
      //system("echo '0' > /sys/class/gpio/gpio18/value");
      hal.gpio->write(18, LOW);
      // kill script and all child processes
      system("pkill -P $(pidof -x /home/pi/run_while_armed.sh)");
      was_armed = false;
   }
}
#endif

#ifdef USERHOOK_SUPERSLOWLOOP
void Copter::userhook_SuperSlowLoop()
{
    // put your 1Hz code here
}
#endif
