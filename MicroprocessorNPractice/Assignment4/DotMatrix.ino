#define DS_PIN A2
#define ST_CP_PIN A3
#define SH_CP_PIN A4
#define SWITCH_PIN 2

#define NUM_OF_PIN 17
#define AUTO_PLAY_MODE true

// 빨강, 초록 도트 매트릭스 이미지 구조체
typedef struct RGDotMatrixImage {
    unsigned long long redImage;
    unsigned long long greenImage;

    RGDotMatrixImage operator<<(const int shift) {
        return {redImage << shift, greenImage << shift};
    }

    RGDotMatrixImage operator>>(const int shift) {
        return {redImage >> shift, greenImage >> shift};
    }

    RGDotMatrixImage operator|(const RGDotMatrixImage &image) {
        return {redImage | image.redImage, greenImage | image.greenImage};
    }
} DMImage;


#define NUM_OF_PIN 16
int PINS[NUM_OF_PIN] = {0, 1, A5, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1};
int GREEN_COLS[] = {PINS[0], PINS[1], PINS[2], PINS[3], PINS[4], PINS[5], PINS[6], PINS[7]};
int RED_COLS[] = {PINS[8], PINS[9], PINS[10], PINS[11], PINS[12], PINS[13], PINS[14], PINS[15]};

// 숫자 폰트
#define FONT_0 0x003e676f7b73633e
#define FONT_1 0x003f0c0c0c0c0e0c
#define FONT_2 0x003f33061c30331e
#define FONT_3 0x001E33301C30331E
#define FONT_4 0x0078307f33363c38
#define FONT_5 0x001e3330301f033f
#define FONT_6 0x001e33331f03061c
#define FONT_7 0x000c0c0c1830333f
#define FONT_8 0x001e33331e33331e
#define FONT_9 0x000e18303e33331e

#define NUM_OF_IMAGE 14
DMImage IMAGES[NUM_OF_IMAGE] =
        {{0,                  0},
         {FONT_2,             0},
         {FONT_0,             0},
         {FONT_2,  FONT_2},
         {FONT_0,  FONT_0},
         {0,       FONT_1},
         {0,       FONT_3},
         {~FONT_6,            0},
         {~FONT_1,            ~FONT_1},
         {~FONT_1,            0},
         {~FONT_0, FONT_0},
         {0x81423c0000000000, 0x0000008142244281},
         {0x3c243c7edbdb7e3c, 0x3c243c7effff7e3c},
         {0x3c42818181815a24, 0x0000182400240000}};

#define ANIMATION_DELAY 50
#define STOP_DELAY 600

// Shift register를 이용한 출력 조작
void shiftRegister(unsigned char data) {
    digitalWrite(ST_CP_PIN, LOW);
    for (int i = 0; i < 8; i++) {
        digitalWrite(SH_CP_PIN, LOW);
        digitalWrite(DS_PIN, (data & (0x80 >> i)) ? HIGH : LOW);
        digitalWrite(SH_CP_PIN, HIGH);
    }
    digitalWrite(ST_CP_PIN, HIGH);
}

// Shift register를 이용하여 열을 컨트롤한다.
inline void controlRowPulse(unsigned char data) {
    shiftRegister(0x80 >> data);
}

// DMImage를 디스플레이에 출력한다.
void displayDMImage(DMImage image, int illuminance) {
    for (int r = 0; r < 8; r++) {
        unsigned char redRow = (image.redImage >> r * 8) & 0xFF;
        unsigned char greenRow = (image.greenImage >> r * 8) & 0xFF;

        for (int c = 0; c < 8; c++) {
            digitalWrite(RED_COLS[c], ((redRow >> c) & 1) ? LOW : HIGH);
            digitalWrite(GREEN_COLS[c], ((greenRow >> c) & 1) ? LOW : HIGH);
            controlRowPulse(r);
            delay(illuminance);
            controlRowPulse(-1);
        }
        for (int c = 0; c < 8; c++) {
            digitalWrite(RED_COLS[c], HIGH); // LED OFF
            digitalWrite(GREEN_COLS[c], HIGH); // LED OFF
        }
    }
}

// LED를 모두 지운다.
void clearAllLED() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            digitalWrite(RED_COLS[j], HIGH);
            digitalWrite(GREEN_COLS[j], HIGH);
            controlRowPulse(i);
        }
    }
}


boolean isPressing = false;
int switchCount = 0;

// 스위치 상태를 확인하고, 스위치 카운트를 증가시킨다.
void switchHandler() {
    int switchStatus = !digitalRead(SWITCH_PIN);
    if (switchStatus && !isPressing) {
        isPressing = true;
        switchCount++;
    } else if (!switchStatus && isPressing) {
        isPressing = false;
    }
}

void setup() {
    for (int i = 0; i < NUM_OF_PIN; i++) {
        pinMode(PINS[i], OUTPUT);
    }
    // Red, Green 핀 설정
    pinMode(SH_CP_PIN, OUTPUT);
    pinMode(ST_CP_PIN, OUTPUT);
    pinMode(DS_PIN, OUTPUT);
    // Shift Register 핀 설정
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    // 스위치 핀 설정
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), switchHandler, CHANGE);
    // 스위치 인터럽트 설정
    clearAllLED();
}

int lastIndex = 0;

void loop() {
    int index = (switchCount) % NUM_OF_IMAGE;
    if (switchCount != 0 && index != lastIndex) {
        DMImage previous = IMAGES[lastIndex];
        DMImage current = IMAGES[index];
        for (int i = 1; i < 8; i++) {
            long time = millis();
            while (millis() - time < ANIMATION_DELAY) {
                displayDMImage((previous >> (i * 8)) | (current << ((8 - i) * 8)), 0);
                // 8칸씩 Shifting 하여 상하로 이동된 이전, 현재 이미지를 만들고 OR(|) 연산하여 합성된 전환 애니메이션 이미지 상을 얻는다.
            }
        }
        lastIndex = index;
    } else {
        // 자동 재생 모드 처리
        if (AUTO_PLAY_MODE) {
            if (switchCount > 0 && switchCount % NUM_OF_IMAGE == 0) {
                switchCount = 0;
            } else if (switchCount != 0) {
                switchCount++;
            }
        }
        long time = millis();
        while (millis() - time < STOP_DELAY) {
            displayDMImage(IMAGES[lastIndex], 0);
        }
    }
}