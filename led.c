#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <softPwm.h>

// Pin configuration
#define PIR_SENSOR_PIN 0  // PIR sensor (WiringPi GPIO 17)
#define CDS_SENSOR_PIN 2  // CDS sensor (WiringPi GPIO 27)
#define LED_PIN 1         // LED pin (WiringPi GPIO 18)

int main(void) {
    if (wiringPiSetup() == -1) {
        printf("Failed to initialize WiringPi!\n");
        return 1;
    }

    pinMode(PIR_SENSOR_PIN, INPUT);
    pinMode(CDS_SENSOR_PIN, INPUT);
    softPwmCreate(LED_PIN, 0, 100); // Create software PWM for LED (0-100 range)

    printf("Initializing PIR sensor... Please wait\n");
    delay(3000); // PIR stabilization time
    printf("PIR sensor is ready!\n");

    while (1) {
        int pirValue = digitalRead(PIR_SENSOR_PIN); // Read PIR sensor value
        int lightLevel = digitalRead(CDS_SENSOR_PIN); // Read CDS sensor value

        printf("PIR Sensor Value: %d, CDS Sensor Value: %d\n", pirValue, lightLevel);

        if (pirValue == HIGH) { // Motion detected
            printf("Motion detected! Checking light level...\n");

            int brightness;
            if (lightLevel == LOW) { // Dark environment
                brightness = 100;
                printf("Dark environment detected. LED at full brightness.\n");
            } else { // Bright environment
                brightness = 30;
                printf("Bright environment detected. LED dimmed.\n");
            }

            softPwmWrite(LED_PIN, brightness);
            delay(10000); // Keep LED on for 10 seconds
            softPwmWrite(LED_PIN, 0);
            printf("LED turned off.\n");
        } else {
            softPwmWrite(LED_PIN, 0); // Ensure LED is off
        }

        delay(500); // Delay for sensor check
    }

    return 0;
}
