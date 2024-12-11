#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// GPIO 핀 번호 설정
#define PIR_PIN 0   // PIR 센서 OUT 핀 (wiringPi의 0번 핀)
#define LED_PIN 1   // LED 핀 (wiringPi의 1번 핀)

int main(void)
{
    // wiringPi 초기화
    if (wiringPiSetup() == -1) {
        printf("wiringPi 초기화 실패\n");
        return -1;
    }

    // 핀 모드 설정
    pinMode(PIR_PIN, INPUT);  // PIR 센서를 입력으로 설정
    pinMode(LED_PIN, OUTPUT);  // LED를 출력으로 설정

    printf("PIR 센서 테스트 시작...\n");

    while (1) {
        if (digitalRead(PIR_PIN) == HIGH) {  // PIR 센서가 동작을 감지하면
            printf("움직임 감지됨!\n");
            digitalWrite(LED_PIN, HIGH);  // LED 켜기
            sleep(5);  // 5초 동안 LED 유지
            digitalWrite(LED_PIN, LOW);  // LED 끄기
        } else {
            usleep(100000);  // 센서 상태 확인 주기 (0.1초)
        }
    }

    return 0;
}
