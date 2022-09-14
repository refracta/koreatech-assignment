/**
 * refracta - 마이크로프로세서및실습 (CSE124-02)
 * 과제 2 Joystick Module 소스 코드
 */

#include "SevSeg.h"

#define BUZZER_PIN 3

#define SEV_SEG_A_PIN 2
#define SEV_SEG_B_PIN 0
#define SEV_SEG_C_PIN 4
#define SEV_SEG_D_PIN 5
#define SEV_SEG_E_PIN 6
#define SEV_SEG_F_PIN 7
#define SEV_SEG_G_PIN 8
#define SEV_SEG_DP_PIN 9

#define SEV_SEG_D1_PIN 10
#define SEV_SEG_D2_PIN 11
#define SEV_SEG_D3_PIN 12
#define SEV_SEG_D4_PIN 13

#define JOY_X_PIN A0
#define JOY_Y_PIN A1

#define LED1_PIN A2
#define LED2_PIN A3
#define LED3_PIN A4
#define NUM_OF_LED 3
// LED 핀 배열 선언
const int LED_PINS[] = {A2, A3, A4};

#define SWITCH_PIN A5

// #define DEBUG_MODE

#ifdef DEBUG_MODE
	#define debug(log) Serial.println(log);
#else
	#define debug(log)
#endif

#define JOY_TRIGGER_VALUE 256
#define GET_JOY_X() map(analogRead(JOY_X_PIN), 0, 1023, -512, 512)
#define GET_JOY_Y() map(analogRead(JOY_Y_PIN), 0, 1023, -512, 512)

#define delay(ms) delayWithRefresh(ms)

SevSeg Display;

// 7 세그먼트 모듈의 디스플레이 출력을 유지하기 위해서 전용 delay 함수를 정의하고 매크로를 이용하여 바꿔치기한다.
void delayWithRefresh(long ms) {
	long start = millis();
	while(true) {
		Display.refreshDisplay();
		if(millis() - start >= ms){
			break;
		}
	}
}

// 7 세그먼트, 조이스틱, LED, 스위치의 핀과 설정들을 초기화한다.
void setup() {
	byte digitPins[] = {SEV_SEG_D1_PIN, SEV_SEG_D2_PIN, SEV_SEG_D3_PIN, SEV_SEG_D4_PIN};
	byte segmentPins[] = {SEV_SEG_A_PIN, SEV_SEG_B_PIN, SEV_SEG_C_PIN, SEV_SEG_D_PIN, SEV_SEG_E_PIN, SEV_SEG_F_PIN, SEV_SEG_G_PIN, SEV_SEG_DP_PIN};
	Display.begin(COMMON_ANODE, 4, digitPins, segmentPins, true);
	Display.setBrightness(100); 
	
	pinMode(JOY_X_PIN, INPUT);
	pinMode(JOY_Y_PIN, INPUT);
	
	pinMode(LED1_PIN, OUTPUT);
	pinMode(LED2_PIN, OUTPUT);
	pinMode(LED3_PIN, OUTPUT);
	
	pinMode(SWITCH_PIN, INPUT_PULLUP);

	#ifdef DEBUG_MODE
	Serial.begin(9600);
	#endif
	// 7 세그먼트 모듈이 0번핀을 사용하기 때문에 Serial 기능을 사용하면 해당 모듈의 출력에 영향이 있다.
}

/* 
 * data from https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
 * 아두이노 튜토리얼 문서의 헤더 파일을 배열 형태로 정리한 것, 각 음계의 진동수의 상수 정의이다.
 */
const int frequencies[] = 
{
	31,				 														// octave 0
	33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62,							// octave 1
	65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117, 123,						// octave 2
	131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247,				// octave 3
	262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,				// octave 4
	523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988,				// octave 5
	1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, // octave 6 
	2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951, // octave 7
	4186, 4435, 4699, 4978													// octave 8
};


// "도 도# 레 레# 미 파 파# 솔 솔# 라 라# 시" 순의 출력 처리용 character 배열
const char notes[] = {'c', 'C', 'd', 'D', 'e', 'f', 'F', 'g', 'G', 'a', 'A', 'b'}; // length = 12

// note에 해당하는 notes의 index를 반환한다.
int getNoteIndex(char note) {
	for(int i = 0; i < 12; i++){
		if(notes[i] == note) {
			return i;
		}
	}
	return -1;
}

// note, octave의 출력으로 duration 동안 부저에 소리를 출력하는 함수
void playTone(char note, int octave, int duration){
	int frequency = frequencies[getNoteIndex(note) - 11 + octave * 12];
	tone(BUZZER_PIN, frequency, duration);
	delay(duration);
	noTone(BUZZER_PIN);
}

// 현재 스위치의 눌림 여부를 반환한다.
bool isSwitchActive() {
	return digitalRead(SWITCH_PIN) == LOW;
}

void loop() {
	if(isSwitchActive()){
		startGame();
	}
}

// 모든 LED의 상태를 설정한다.
void setAllLED(bool status) {
	for(int j = 0; j < NUM_OF_LED; j++) {
		digitalWrite(LED_PINS[j], status ? HIGH : LOW);
	}
}

// 빵빠레 음을 재생한다. (게임 승리시 재생)
void playFanfare() {
	playTone('a', 5, 200);
	playTone('a', 5, 100);
	playTone('a', 5, 300);
	playTone('b', 5, 200);
	playTone('a', 5, 200);
	playTone('b', 5, 200);
	playTone('c', 6, 200);
	playTone('c', 6, 100);
	playTone('c', 6, 700);
}

void startGame() {
	randomSeed(millis());
	// 사용자가 버튼을 누른 시점의 millis() 함수 값을 이용하여 의사난수 시드를 초기화한다.

	// 대기 및 시작
	Display.setChars("REDY");
	for(int i = 0; i < 3; i++) {
		playTone('g', 5, 200);
		setAllLED(true);
		delay(1000);
		setAllLED(false);
		delay(1000);
	}
	Display.setChars("STAT");
	playTone('g', 7, 600);

	// 본 게임 시작 1초 대기
	setAllLED(true);
	delay(1000);
	setAllLED(false);
	
	// 참참참 시작
	Display.setChars("CHA1");
	digitalWrite(LED2_PIN, HIGH);
	playTone('f', 4, 250);
	Display.blank();
	digitalWrite(LED2_PIN, LOW);
	delay(50);

	Display.setChars("CHA2");
	digitalWrite(LED2_PIN, HIGH);
	playTone('f', 4, 250);
	Display.blank();
	digitalWrite(LED2_PIN, LOW);
	delay(50);
	
	// 조이스틱 방향 결정과 그에 따른 처리
	int randomLR = random(2);
	if(randomLR == 0) {
		Display.setChars("LEFT");
		digitalWrite(LED1_PIN, HIGH);
	} else {
		Display.setChars("RIGT");
		digitalWrite(LED3_PIN, HIGH);
	}
	playTone('f', 6, 300);
	
	// 사용자 입력 처리
	long waitInput = millis();
	bool selected = false;
	int joy;
	while(millis() - waitInput <= 10) {
		joy = GET_JOY_Y();
		if(abs(joy) > JOY_TRIGGER_VALUE) {
			selected = true;
		}
	}
	joy = joy < 0 ? 0 : 1;
	
	// 최종 결과 출력
	if(selected && joy == randomLR) {
		Display.setChars("COOL");
		playFanfare();
		for(int k = 0; k < 3; k++){
			setAllLED(true);
			delay(500);
			setAllLED(false);
			delay(500);
		}
	} else {
		Display.setChars("LOSE");
		digitalWrite(LED2_PIN, HIGH);
		playTone('F', 6, 100);
		playTone('F', 6, 100);
		delay(2000);
	}
	
	// 시각 피드백 초기화
	Display.blank();
	setAllLED(false);
}