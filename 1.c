#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define PIR_SENSOR_PIN 0  // PIR 센서 (WiringPi GPIO 17)
#define LED_PIN 1         // LED (WiringPi GPIO 18)

int main(void) {
    if (wiringPiSetup() == -1) {
        printf("Failed to initialize WiringPi!\n");
        return 1;
    }

    pinMode(PIR_SENSOR_PIN, INPUT);  // PIR 센서 입력
    softPwmCreate(LED_PIN, 0, 100);  // LED 제어용 PWM 생성

    printf("Initializing PIR sensor... Please wait\n");
    delay(5000); // 안정화 시간
    printf("PIR sensor is ready!\n");

    int prevState = LOW; // 이전 PIR 센서 상태
    while (1) {
        int currentState = digitalRead(PIR_SENSOR_PIN); // 현재 PIR 상태 읽기

        if (currentState == HIGH && prevState == LOW) {
            // 새로운 움직임 감지
            printf("Motion detected! Turning LED on.\n");
            softPwmWrite(LED_PIN, 100); // LED 켜기
            delay(10000);              // 10초 대기
            softPwmWrite(LED_PIN, 0);  // LED 끄기
            printf("LED turned off.\n");
        }

        prevState = currentState; // 상태 갱신
        delay(500); // 0.5초 대기
    }

    return 0;
}
