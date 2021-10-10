#ifndef _BUZZER_H_
#define _BUZZER_H_

#include <Tone32.h>

#define BUZZER_PIN      5
#define BUZZER_CHANNEL  0

typedef struct {
  uint16_t note;
  uint8_t hold;
} Tone;

static Tone badBoys[] = {
  {NOTE_C6,  8},
  {NOTE_A5,  8},
  {NOTE_C6,  8},
  {NOTE_A5,  8},
  {NOTE_B0,  2},
  
  {NOTE_A5,  3},
  {NOTE_B0,  1},
  {NOTE_A5,  3},
  {NOTE_B0,  1},
  {NOTE_A5,  3},
  {NOTE_B0,  1},
  {NOTE_A5,  3},
  {NOTE_B0,  1},
  {NOTE_C6,  12},
  
  {NOTE_C6,  3},
  {NOTE_B0,  1},
  {NOTE_C6,  3},
  {NOTE_B0,  1},
  {NOTE_C6,  3},
  {NOTE_B0,  1},
  {NOTE_C6,  3},
  {NOTE_B0,  1},
  {NOTE_C6,  8},
  {NOTE_C6,  4},
  {NOTE_D6,  4},
  {NOTE_C6,  8},
  {NOTE_A5,  8},
  {NOTE_A5,  8}
  
};

#endif // _BUZZER_H_
