/*
 * VS1053B.h
 *
 *  Created on: Apr 24, 2018
 *      Author: Sneha
 */

#ifndef VS1053B_HPP_
#define VS1053B_HPP_
#include "stdio.h"
#include "VS1053B_memmap.h"
#include "tasks.hpp"

void mp3_cs();
void mp3_ds();
void mp3_data_cs();
void mp3_data_ds();
void mp3_reset();
void mp3_dreq_init();
void mp3_hardwareReset();
bool mp3_dreq_getLevel();
bool mp3_initDecoder();
extern void mp3_writeRequest(uint8_t address, uint16_t data);
extern uint16_t mp3_readRequest(uint8_t address);
void refresh_params();

/**
 * Start/Stop/Pause based on Command
 */
bool mp3_stop();
bool mp3_pause();
bool mp3_start();
bool mp3_fast_forward();

/**
 * Volume max = 0000
 * Volume min = FEFE
 * XXYY where XX is left channel and YY is right channel
 */
bool mp3_dec_vol();
bool mp3_inc_vol();

extern TaskHandle_t playSongTaskHandle;
extern unsigned long song_offset;
#endif /* VS1053B_HPP_ */
