#ifndef SPELLING_H_INCLUDED
#define SPELLING_H_INCLUDED

#include "stype.h"

uint32_t SpellingSampleSize(int8_t *text, uint32_t text_len, uint32_t s_char_space, uint32_t s_word_space);
uint32_t CreateSpellingSamples(wav_t *wav_p, int8_t *text, uint32_t text_len, double t_space, uint16_t Fs);

#endif // SPELLING_H_INCLUDED
