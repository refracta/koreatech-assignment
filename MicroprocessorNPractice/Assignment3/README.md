# README

IRremote 라이브러리에서 IR 수신과 tone 함수를 동시에 쓰지 못하는 문제가 있어 IRremote 라이브러리의 사용 타이머를 1번으로 변경 처리하였습니다. 첨부한 라이브러리 폴더는 해당 내용이 수정된 IRremote 라이브러리입니다.

# src/private/IRTimer.hpp
```
/***************************************
 * Plain AVR CPU's, no boards
 ***************************************/
// Arduino Duemilanove, Diecimila, LilyPad, Mini, Fio, Nano, etc
// ATmega328
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328PB__) || defined(__AVR_ATmega168__)
#  if !defined(IR_USE_AVR_TIMER1) && !defined(IR_USE_AVR_TIMER2)
#define IR_USE_AVR_TIMER1   // send pin = pin 9
// IR_USE_AVR_TIMER1을 사용하도록 변경
//#define IR_USE_AVR_TIMER2     // send pin = pin 3
#  endif
```