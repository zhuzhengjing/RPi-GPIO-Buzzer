
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

