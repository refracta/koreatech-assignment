/**
 * refracta - 마이크로프로세서및실습 (CSE124-02)
 * 과제 1 소스 코드
 */

#define DEBUG_MODE true
// 디버그 플래그

#if DEBUG_MODE
  #define debug(log) Serial.println(log);
#else
  #define debug(log)
#endif

#define LED_PIN 2
#define BUZZER_PIN 3
#define SWITCH_PIN 4
// 핀 상수 설정

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  // LED, BUZZER, SWITCH의 pinMode를 설정
  // Serial 통신을 위해 9600 Baud Rate 설정
}

const int frequencies[] = 
{
	31,                                                                     // octave 0
	33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62,                         // octave 1
	65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117, 123,                     // octave 2
	131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247,             // octave 3
	262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,             // octave 4
	523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988,             // octave 5
	1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, // octave 6 
	2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951, // octave 7
	4186, 4435, 4699, 4978                                                  // octave 8
};
/* 
 * data from https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
 * 아두이노 튜토리얼 문서의 헤더 파일을 배열 형태로 정리한 것, 각 음계의 진동수의 상수 정의이다.
 */
const char notes[] = {'c', 'C', 'd', 'D', 'e', 'f', 'F', 'g', 'G', 'a', 'A', 'b'}; // length = 12
// "도 도# 레 레# 미 파 파# 솔 솔# 라 라# 시" 순의 출력 처리용 character 배열

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

/* 간이 음악 문자열 포맷을 출력해주는 함수이다.
 *  "c=도, C=도#, d=레, D=레#, e=미, f=파, F=파#, g=솔, G=솔#, a=라, A=라#, b=시, P=쉼표"를 출력
 *  S%숫자%: Tempo(Bit per minute)를 숫자으로 설정
 *  숫자: 현재 옥타브를 숫자로 설정
 *  example) 6S100abc7abc => 6 옥타브 설정, Tempo=100, 라, 시, 도, 7 옥타브 설정, 라, 시, 도
 */
void playMusic(String music) {
  int musicLength = music.length();
  int currentOctave = 4;
  int currentSpeed = 250;
  for(int i = 0; i < musicLength; i++) {
    char m = music.charAt(i);
    if(m == 'S' || m == 's') {
      String sb = "";
      for(i = i + 1; i < musicLength; i++){
        char c = music.charAt(i);
        if('0' <= c && c <= '9') {
          sb += c;
        } else {
          i--;
          break;
        }
      }
      currentSpeed = (60.0 / sb.toInt()) * 1000;
    } else if (m == 'P' || m == 'p'){
      delay(currentSpeed);
    } else if ('0' <= m && m <= '9') {
      currentOctave = m - '0';
    } else {
      playTone(m, currentOctave, currentSpeed);
    }
  }
}

// LED의 상태를 변경한다.
void setLED(bool status) {
   digitalWrite(LED_PIN, status ? HIGH : LOW);
}

// 현재 스위치가 눌림 여부를 반환한다.
bool isSwitchActive() {
  return digitalRead(SWITCH_PIN) == LOW;
}

// 버튼 트리거시 재생되는 간이 음악 문자열 (Indiana Jones, Take On Me, Star Wars)
String currentMusic = "5S250eS500pfgp6S63c5S333pS250dS500peS63fS167pS250gS500pabp6S63f5S250paS500pb6S125cde5S250eS500pfgp6S63c5S250p6d5S500p6eS42f5S250gS500pg6S167e5S500p6S250d5S500pg6S167e5S500p6S250d5S500pg6S167f5S500p6S250e5S500p6dS125c5S320FFFd4pbp5e4p5e4p5eGGabaaae4p5d4p5F4p5F4p5FeeFeFFFd4pbp5e4p5e4p5eGGabaaae4p5d4p5F4p5F4p5Fee5S360pFFFS60b6FS360eDCS60bS120FS360eDCS60bS120FS360eDeS60C5S360FFFS60b6FS360eDCS60bS120FS360eDCS60bS120FS360eDeS90C";

// 직렬 통신으로 간이 음악 문자열 수신 처리
void handleSerialRequest(){
  if(Serial.available()){
    currentMusic = Serial.readString();
    Serial.println("Received successfully.");
  }
}

// 코어 로직 루프
void loop() {
  if(isSwitchActive()){
    setLED(true);
    playMusic(currentMusic); 
    setLED(false);
  }
  handleSerialRequest();
}