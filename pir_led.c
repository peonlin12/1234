#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sleep function

// Pin configuration
#define PIR_SENSOR_PIN 0  // PIR sensor (WiringPi GPIO 17)
#define LED_PIN 2         // LED pin (WiringPi GPIO 27)

int main(void) {
    // Initialize WiringPi
    if (wiringPiSetup() == -1) {
        printf("Failed to initialize WiringPi!\n");
        return 1;
    }

    // Set pin modes
    pinMode(PIR_SENSOR_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    printf("Initializing PIR sensor... Please wait\n");
    delay(2000); // Sensor stabilization time (2 seconds)
    printf("PIR sensor is ready!\n");

    while (1) {
        // Check PIR sensor signal
        if (digitalRead(PIR_SENSOR_PIN) == HIGH) {
            printf("Motion detected! Turning LED on\n");
            digitalWrite(LED_PIN, HIGH); // Turn on LED
            delay(10000); // Wait for 10 seconds
            digitalWrite(LED_PIN, LOW);  // Turn off LED
            printf("LED turned off\n");
        }
        delay(100); // Check sensor signal every 100ms
    }

    return 0;
}
