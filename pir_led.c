#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <softPwm.h>

// Pin configuration
#define PIR_SENSOR_PIN 0  // PIR sensor (WiringPi GPIO 17)
#define CDS_SENSOR_PIN 2  // CDS sensor (WiringPi GPIO 27)
#define LED_PIN 1         // LED pin (WiringPi GPIO 18)

int main(void) {
    // Initialize WiringPi
    if (wiringPiSetup() == -1) {
        printf("Failed to initialize WiringPi!\n");
        return 1;
    }

    // Set pin modes
    pinMode(PIR_SENSOR_PIN, INPUT);
    pinMode(CDS_SENSOR_PIN, INPUT);
    softPwmCreate(LED_PIN, 0, 100); // Create software PWM for LED (0-100 range)

    printf("Initializing PIR and CDS sensors... Please wait\n");
    delay(2000); // Sensor stabilization time
    printf("Sensors are ready!\n");

    while (1) {
        if (digitalRead(PIR_SENSOR_PIN) == HIGH) { // Motion detected
            printf("Motion detected! Checking light level...\n");

            int lightLevel = digitalRead(CDS_SENSOR_PIN); // Read CDS sensor
            int brightness;

            // Determine LED brightness based on light level
            if (lightLevel == HIGH) { // Bright environment
                brightness = 30; // Dim LED
                printf("Bright environment detected. LED dimmed.\n");
            } else { // Dark environment
                brightness = 100; // Bright LED
                printf("Dark environment detected. LED at full brightness.\n");
            }

            // Set LED brightness
            softPwmWrite(LED_PIN, brightness);

            // Wait for 10 seconds
            delay(10000);

            // Turn off LED
            softPwmWrite(LED_PIN, 0);
            printf("LED turned off.\n");
        }
        delay(100); // Check PIR sensor every 100ms
    }

    return 0;
}
