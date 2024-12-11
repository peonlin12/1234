#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// GPIO pin numbers
#define PIR_PIN 0   // PIR sensor OUT pin (wiringPi pin 0)
#define LED_PIN 1   // LED pin (wiringPi pin 1)

int main(void)
{
    // Initialize wiringPi
    if (wiringPiSetup() == -1) {
        printf("wiringPi initialization failed\n");
        return -1;
    }

    // Set pin modes
    pinMode(PIR_PIN, INPUT);  // Set PIR sensor as input
    pinMode(LED_PIN, OUTPUT);  // Set LED as output

    printf("PIR sensor test started...\n");

    while (1) {
        if (digitalRead(PIR_PIN) == HIGH) {  // If PIR sensor detects motion
            printf("Motion detected!\n");
            digitalWrite(LED_PIN, HIGH);  // Turn on LED
            sleep(5);  // Keep LED on for 5 seconds
            digitalWrite(LED_PIN, LOW);  // Turn off LED
        } else {
            usleep(100000);  // Check sensor status every 0.1 seconds
        }
    }

    return 0;
}
