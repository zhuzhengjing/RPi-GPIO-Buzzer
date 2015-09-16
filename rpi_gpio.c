
#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <unistd.h>


#define BUZZER_GPIO_NUM     5

void buzzer_on(int gpio, int on_time)
{
    digitalWrite (gpio, 0);
    usleep(on_time*1000);
    digitalWrite (gpio, 1);
}

int main (void)
{
    int i, led;
    time_t now;

    printf ("RPi GPIO Buzzer\n");

    wiringPiSetup();

    // use GPIO5
    pinMode(BUZZER_GPIO_NUM, OUTPUT);

    // test buzzer
    buzzer_on(BUZZER_GPIO_NUM, 1000);

    for (;;) {

        time(&now);
        struct tm *current_time = localtime(&now);
        //printf("%d:%d:%d\n", current_time->tm_hour, current_time->tm_min, current_time->tm_sec);

        // 6:00 - 22:00
        if (current_time->tm_hour >= 6 && current_time->tm_hour <= 22) {
            if (current_time->tm_min == 0 &&
                current_time->tm_sec == 0) {            // 整点报时
                buzzer_on(BUZZER_GPIO_NUM, 1000);
            } else if (current_time->tm_min == 30 &&
                       current_time->tm_sec == 0) {     // 半点报时
                buzzer_on(BUZZER_GPIO_NUM, 100);
                usleep(500*1000);
            }
        }

        usleep(500*1000);
    }
}

