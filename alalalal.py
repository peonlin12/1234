import time
import RPi.GPIO as GPIO
from adafruit_ads1x15.analog_in import AnalogIn
from adafruit_ads1x15.ads1115 import ADS1115
import board
import busio

# GPIO 핀 설정
PIR_PIN = 17  # PIR 센서
LED_PIN = 18  # 발광 다이오드

# GPIO 초기화
GPIO.setmode(GPIO.BCM)
GPIO.setup(PIR_PIN, GPIO.IN)
GPIO.setup(LED_PIN, GPIO.OUT)

# I2C 버스 및 ADS1115 설정
i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS1115(i2c)
current_channel = AnalogIn(ads, ADS1115.P0)  # ACS712 OUT 연결된 A0 핀

# LED 제어 함수
def turn_on_led():
    GPIO.output(LED_PIN, GPIO.HIGH)
    print("LED 켜짐")

def turn_off_led():
    GPIO.output(LED_PIN, GPIO.LOW)
    print("LED 꺼짐")

# PIR 센서 움직임 감지 함수
def detect_motion():
    if GPIO.input(PIR_PIN):
        print("움직임 감지됨!")
        return True
    else:
        return False

# 전류 센서 데이터 읽기 함수 (ACS712)
def read_current():
    voltage = current_channel.voltage
    current = (voltage - 2.5) / 0.185  # ACS712-05B 기준 (185mV/A)
    print(f"전류 측정값: {current:.2f} A")
    return current

# 메인 루프
try:
    print("시스템 시작")
    time.sleep(2)
    while True:
        # PIR 센서로 LED 제어
        if detect_motion():
            turn_on_led()
        else:
            turn_off_led()

        # 전류 센서 데이터 읽기
        current = read_current()

        # 2초 대기
        time.sleep(2)

except KeyboardInterrupt:
    print("프로그램 종료")
finally:
    GPIO.cleanup()
