/**
 * refracta - 마이크로프로세서및실습 (CSE124-02)
 * 과제 2 Ultrasonic Sensor 소스 코드
 */

#define DEBUG_MODE true
// 디버그 플래그

#if DEBUG_MODE
  #define debug(log) Serial.println(log);
#else
  #define debug(log)
#endif

#define LED1_PIN 5
#define LED2_PIN 6
#define LED3_PIN 9
#define LED4_PIN 10
#define LED5_PIN 11
#define NUMBER_OF_LED 5
// LED 핀 배열 선언
const int LED_PINS[] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN, LED5_PIN};

#define USS_TRIGGER_PIN 12
#define USS_ECHO_PIN 13

#define L293D_ENABLE_PIN 3
#define L293D_IN1_PIN 4
#define L293D_IN2_PIN 2

#define USE_MOTOR
#define MOTOR_SPEED_MIN 130
#define SOUND_SPEED 0.0343

#define GET_INTENSITY(DELTA) ((int) ((distance - DELTA) / 5 * 255))

// LED, 조이스틱, 초음파 센서, 모터 드라이버의 핀을 초기화한다.
void setup() {
  Serial.begin (9600);
  
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  pinMode(LED5_PIN, OUTPUT);

  pinMode(USS_TRIGGER_PIN, OUTPUT);
  pinMode(USS_ECHO_PIN, INPUT);

  pinMode(L293D_ENABLE_PIN, OUTPUT);   
  pinMode(L293D_IN1_PIN, OUTPUT);     
  pinMode(L293D_IN2_PIN, OUTPUT);     
}

// 초음파 센서로부터 현재 거리 값을 읽는다. (cm)
double getDistance() {
  digitalWrite(USS_TRIGGER_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(USS_TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(USS_TRIGGER_PIN, LOW);
  return (pulseIn(USS_ECHO_PIN, HIGH) * SOUND_SPEED) / 2;
}

// LED 세기 배열
int intensities[NUMBER_OF_LED];

// LED의 세기를 설정한다.
void setIntensities(int i1, int i2, int i3, int i4, int i5) {
  intensities[0] = i1;
  intensities[1] = i2;
  intensities[2] = i3;
  intensities[3] = i4;
  intensities[4] = i5;
}

// 모든 LED의 세기를 LED 세기 배열에 있는 값으로 설정한다.
void setLED() {
  for(int i = 0; i < NUMBER_OF_LED; i++) {
    analogWrite(LED_PINS[i], intensities[i]);
  }
}

// 속도와 회전 방향을 매개변수로 받아 모터 동작을 설정한다.
void setMotor(int speed, boolean reverse) {                                         
  analogWrite(L293D_ENABLE_PIN, speed);         
  digitalWrite(L293D_IN1_PIN, reverse);      
  digitalWrite(L293D_IN2_PIN, !reverse); 
}

// 모터를 작동시킨다.
bool isMotorDown = true;
void runMotor(int speed) {
  #ifdef USE_MOTOR
  if(isMotorDown && speed > 0) {
	// 저출력으로 모터 사용 시, 작동하지 않는 경우 잠시 역방향 출력을 걸어주었다. 정방향 출력을 걸어주면 원활한 작동에 도움이 되는 것을 관찰하고 정지 후 모터 구동시 모터에게 역방향 출력을 가하는 부분을 추가하였다.
    debug("Motor init");
    setMotor(255, true);
    delay(250);
    setMotor(255, false);
    delay(250);
    isMotorDown = false;
  }
  setMotor(speed, false);
  if(speed == 0){
    isMotorDown = true;
  }
  #endif
}

#define SAMPLE_LENGTH 10
double dataArray[SAMPLE_LENGTH] = {0, };
// 최근 10개 초음파 센서 거리 센싱 결과의 평균을 구한다. (이동 평균 필터)
double getAverageDistance() {
  for(int i = 0; i < SAMPLE_LENGTH - 1; i ++){
    dataArray[i] = dataArray[i + 1];
  }
  dataArray[SAMPLE_LENGTH - 1] = getDistance();
  double distance = 0;
  for(int i = 0; i < SAMPLE_LENGTH; i ++){
    distance += dataArray[i];
  }
  distance /= SAMPLE_LENGTH;
  return distance;
}

#define BASE_DISTANCE 40
void loop() {
  double distance = getAverageDistance();
  
  // 거리에 따라 LED를 제어한다.
  if(distance <= BASE_DISTANCE) {
    setIntensities(0, 0, 0, 0, 0);
  } else if (distance <= BASE_DISTANCE + 5) {
    setIntensities(GET_INTENSITY(BASE_DISTANCE), 0, 0, 0, 0);
  } else if(distance <= BASE_DISTANCE + 10) {
    setIntensities(255, GET_INTENSITY(BASE_DISTANCE + 5), 0, 0, 0);
  } else if(distance <= BASE_DISTANCE + 15) {
    setIntensities(255, 255, GET_INTENSITY(BASE_DISTANCE + 10), 0, 0);
  } else if(distance <= BASE_DISTANCE + 20) {
    setIntensities(255, 255, 255, GET_INTENSITY(BASE_DISTANCE + 15), 0);
  } else {
    int intensity = GET_INTENSITY(BASE_DISTANCE + 20);
    intensity = intensity > 255 ? 255 : intensity;
    setIntensities(255, 255, 255, 255, intensity);
  }
  setLED();

// 거리에 따라 모터를 제어한다.
  if(distance < 10) {
    runMotor(255);
  } else if(60 <= distance) {
    runMotor(0);
  } else {
    double motorSpeed = (distance - 10) / (60 - 10);
    motorSpeed = MOTOR_SPEED_MIN + (1 - motorSpeed) * (255 - MOTOR_SPEED_MIN);
    runMotor((int) motorSpeed);
    // 10cm ~ 60cm을 255 ~ 120 모터 강도로 변환
  }
  
  delay(100);
  debug(distance);
}
