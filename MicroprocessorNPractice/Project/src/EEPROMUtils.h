/*! \file */
#ifndef EEPROMMANGER_H
#define EEPROMMANGER_H

#include <Arduino.h>
#include <EEPROM.h>

#define SCORE_START 0
#define CUSTOM_MUSIC_START 64
#define CUSTOM_MUSIC_DATA_START (CUSTOM_MUSIC_START + 2)

/*
 * 한 saveIndex당 3 바이트씩 처리
 * SAVE_INDEX=0 [ [SCORE_PART1] [SCORE_PART2] [MAX_COMBO] ]
 * SCORE는 2바이트 unsigned int
 * MAX_COMBO는 1바이트 unsigned char
 */

#define READ_SCORE(I) ((EEPROM.read(SCORE_START + I * 3 + 1) << 8) + EEPROM.read(SCORE_START + I * 3 + 0))
#define WRITE_SCORE(I, S) EEPROM.write(SCORE_START + I * 3 + 0, S & 0xFF); EEPROM.write(SCORE_START + I * 3 + 1, (S & 0xFF00) >> 8)
#define READ_COMBO(I) (EEPROM.read(SCORE_START + I * 3 + 2))
#define WRITE_COMBO(I, C) EEPROM.write(SCORE_START + I * 3 + 2, C)
#define READ_CUSTOM_MUSIC_LENGTH() ((EEPROM.read(CUSTOM_MUSIC_START + 1) << 8) + EEPROM.read(CUSTOM_MUSIC_START + 0))
#define WRITE_CUSTOM_MUSIC_LENGTH(L) EEPROM.write(CUSTOM_MUSIC_START + 0, L & 0xFF); EEPROM.write(CUSTOM_MUSIC_START + 1, (L & 0xFF00) >> 8)
#endif