/*
 * blink8.c:
 *	Simple sequence over the first 8 GPIO pins - LEDs
 *	Aimed at the Gertboard, but it's fairly generic.
 *
 * Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <stdio.h>
#include <wiringPi.h>
#include <time.h>

#define BUZZER_GPIO_NUM     5

void buzzer_on(int gpio, int on_time)
{
    digitalWrite (gpio, 1);
    delay(on_time);
    digitalWrite (gpio, 0);
}

int main (void)
{
    int i, led;
    time_t now;

    printf ("RPi GPIO Buzzer\n");

    wiringPiSetup();

    // use GPIO5
    pinMode(i, BUZZER_GPIO_NUM);

    for (;;) {
        time(&now);

        struct tm *current_time = gmtime(&now);
        printf("time h = %d, m = %d, s = %d\n",
               current_time->tm_hour,
               current_time->tm_min,
               current_time->tm_sec);

        // 6:00 - 22:00
        if (current_time->tm_hour >= 6 && current_time->tm_hour <= 22) {
            if (current_time->tm_min == 0 &&
                current_time->tm_sec == 0) {            // 整点报时
                buzzer_on(BUZZER_GPIO_NUM, 1000);
            } else if (current_time->tm_min == 30 &&
                       current_time->tm_sec == 0) {     // 半点报时
                buzzer_on(BUZZER_GPIO_NUM, 100);
                delay(500);
            }
        }

        delay(500);
    }
}

