#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sleep function

// 핀 번호 설정
#define PIR_SENSOR_PIN 0  // PIR 센서 (WiringPi 기준 GPIO 17)
#define LED_PIN 2         // LED 핀 (WiringPi 기준 GPIO 27)

int main(void) {
    // WiringPi 초기화
    if (wiringPiSetup() == -1) {
        printf("WiringPi 초기화 실패!\n");
        return 1;
    }

    // 핀 모드 설정
    pinMode(PIR_SENSOR_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    printf("PIR 센서 초기화 중... 대기하세요\n");
    delay(2000); // 센서 안정화 시간 (2초)
    printf("PIR 센서 준비 완료!\n");

    while (1) {
        // PIR 센서 감지 확인
        if (digitalRead(PIR_SENSOR_PIN) == HIGH) {
            printf("움직임 감지됨! LED 켜짐\n");
            digitalWrite(LED_PIN, HIGH); // LED 켜기
            delay(10000); // 10초 대기
            digitalWrite(LED_PIN, LOW);  // LED 끄기
            printf("LED 꺼짐\n");
        }
        delay(100); // 100ms 주기로 센서 상태 확인
    }

    return 0;
}
