/**
 @file beeputils.h
 @brief Beep 함수를 쉽게 사용 할 수 있게 래핑한 매크로가 정의된 헤더 파일
*/
#ifndef BEEPUTILS_H
#define BEEPUTILS_H

#include <Windows.h>
#include <math.h>

#define OCTAVE_0 16
#define OCTAVE_1 33
#define OCTAVE_2 65
#define OCTAVE_3 131
#define OCTAVE_4 262
#define OCTAVE_5 523
#define OCTAVE_6 1047
#define OCTAVE_7 2093
#define OCTAVE_8 4186

#define VALUE_DO 0
#define VALUE_DO_S 1
#define VALUE_RE 2
#define VALUE_RE_S 3
#define VALUE_MI 4
#define VALUE_FA 5
#define VALUE_FA_S 6
#define VALUE_SOL 7
#define VALUE_SOL_S 8
#define VALUE_RA 9
#define VALUE_RA_S 10
#define VALUE_SI 11

#define PLAY_BEEP(o, v, t) Beep((int)((o) * pow(1.06f, v)), t)

#define DO(o, t) PLAY_BEEP(o, VALUE_DO, t)
#define DO_S(o, t) PLAY_BEEP(o, VALUE_DO_S, t)
#define RE(o, t) PLAY_BEEP(o, VALUE_RE, t)
#define RE_S(o, t) PLAY_BEEP(o, VALUE_RE_S, t)
#define MI(o, t) PLAY_BEEP(o, VALUE_MI, t)
#define FA(o, t) PLAY_BEEP(o, VALUE_FA, t)
#define FA_S(o, t) PLAY_BEEP(o, VALUE_FA_S, t)
#define SOL(o, t) PLAY_BEEP(o, VALUE_SOL, t)
#define SOL_S(o, t) PLAY_BEEP(o, VALUE_SOL_S, t)
#define RA(o, t) PLAY_BEEP(o, VALUE_RA, t)
#define RA_S(o, t) PLAY_BEEP(o, VALUE_RA_S, t)
#define SI(o, t) PLAY_BEEP(o, VALUE_SI, t)
#endif

#define PLAY_VICTORY_FANFARE() \
RA(OCTAVE_5, 200); \
RA(OCTAVE_5, 100); \
RA(OCTAVE_5, 300); \
SI(OCTAVE_5, 200); \
RA(OCTAVE_5, 200); \
SI(OCTAVE_5, 200); \
DO(OCTAVE_6, 200); \
DO(OCTAVE_6, 100); \
DO(OCTAVE_6, 700);

#define PLAY_EXIT_SOUND() \
FA_S(OCTAVE_6, 20); \
FA_S(OCTAVE_6, 20);

#define PLAY_FAIL_SOUND() \
FA_S(OCTAVE_6, 20);       \

#define PLAY_SELECTION_SOUND1() \
RA(OCTAVE_4, 20);