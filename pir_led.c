#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sleep function
#include <softPwm.h> // For PWM control

// Pin configuration
#define PIR_SENSOR_PIN 0  // PIR sensor (WiringPi GPIO 17)
#define LDR_CHANNEL 0     // MCP3008 channel 0 (LDR)
#define LED_PIN 1         // LED pin (WiringPi GPIO 18)

// MCP3008 SPI configuration
#define SPI_CHANNEL 0     // SPI channel for MCP3008
#define SPI_CLOCK 1000000 // SPI clock speed

// Function to read from MCP3008 ADC
int readADC(int channel) {
    unsigned char buffer[3];
    buffer[0] = 1;  // Start bit
    buffer[1] = (8 + channel) << 4;  // SGL/Diff + Channel
    buffer[2] = 0;

    wiringPiSPIDataRW(SPI_CHANNEL, buffer, 3);

    int result = ((buffer[1] & 3) << 8) + buffer[2];  // 10-bit result
    return result;
}

int main(void) {
    // Initialize WiringPi
    if (wiringPiSetup() == -1) {
        printf("Failed to initialize WiringPi!\n");
        return 1;
    }

    if (wiringPiSPISetup(SPI_CHANNEL, SPI_CLOCK) == -1) {
        printf("Failed to initialize SPI!\n");
        return 1;
    }

    // Set pin modes
    pinMode(PIR_SENSOR_PIN, INPUT);
    softPwmCreate(LED_PIN, 0, 100); // Create software PWM for LED (0-100 range)

    printf("Initializing PIR sensor... Please wait\n");
    delay(2000); // Sensor stabilization time
    printf("PIR sensor is ready!\n");

    while (1) {
        if (digitalRead(PIR_SENSOR_PIN) == HIGH) { // Motion detected
            printf("Motion detected! Checking light level...\n");

            int lightValue = readADC(LDR_CHANNEL); // Read light value from LDR
            int brightness;

            // Determine LED brightness based on light level
            if (lightValue > 512) { // Bright environment
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
