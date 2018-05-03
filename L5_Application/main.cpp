/*
 *     SocialLedge.com - Copyright (C) 2013
 *
 *     This file is part of free software framework for embedded processors.
 *     You can use it and/or distribute it as long as this copyright header
 *     remains unmodified.  The code is free for personal use and requires
 *     permission to use in a commercial product.
 *
 *      THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 *      OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 *      MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 *      I SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 *      CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *     You can reach the author of this software at :
 *          p r e e t . w i k i @ g m a i l . c o m
 */

/**
 * @file
 * @brief This is the application entry point.
 *          FreeRTOS and stdio printf is pre-configured to use uart0_min.h before main() enters.
 *          @see L0_LowLevel/lpc_sys.h if you wish to override printf/scanf functions.
 *
 */
#include "tasks.hpp"
#include "examples/examples.hpp"

#include "LabSPI.hpp"
#include "printf_lib.h"

#include "semphr.h"
#include "VS1053B_memmap.h"
#include "VS1053B.hpp"
#include "song.hpp"
#include "storage.hpp"
#include "string.h"

uint8_t COUNT = READ_BYTES_FROM_FILE / TRANSMIT_BYTES_TO_DECODER;  //Divided by 128 because the decoder decodes only if maximum bytes are 128.

LabSPI decoderSPI;

QueueHandle_t musicQueue;
TaskHandle_t bufferTaskHandle;

//Read the 16-bit value of a VS10xx register
extern uint16_t mp3_readRequest(uint8_t address)
{
    uint16_t result = 0;
    while (!mp3_dreq_getLevel())
        ;
    mp3_cs(); //do a chip select
    decoderSPI.transfer(READ);
    decoderSPI.transfer(address);

    uint8_t highbyte = decoderSPI.transfer(0xFF);
    uint8_t lowbyte = decoderSPI.transfer(0xFF);
    result = (highbyte << 8) | lowbyte;
    while (!mp3_dreq_getLevel())
        ; // dreq should go high indicating transfer complete
    mp3_ds(); // Assert a HIGH signal to de-assert the CS

    return result;
}

extern void mp3_writeRequest(uint8_t address, uint16_t data)
{
    while (!mp3_dreq_getLevel())
        ;
    mp3_cs(); //do a chip select
    decoderSPI.transfer(WRITE);
    decoderSPI.transfer(address);
    uint8_t dataUpper = (data >> 8 & 0xFF);
    uint8_t dataLower = (data & 0xFF);
    decoderSPI.transfer(dataUpper);
    decoderSPI.transfer(dataLower);
    while (!mp3_dreq_getLevel())
        ; // dreq should go high indicating transfer complete
    mp3_ds(); // Assert a HIGH signal to de-assert the CS

}

void vinitCheck(void * pvParameters)
{
    static int count;
    while (1) {
        if (xSemaphoreTake(LabSPI::spi_mutex, 1000)) {
            if (mp3_dreq_getLevel()) {
                mp3_cs(); //do a chip select

                count++;
                if (count % 2 == 0) {

//                    uint16_t res = mp3_readRequest(SCI_MODE);
//                    u0_dbg_printf("MODE is %x\n", res);
//                    res = mp3_readRequest(SCI_CLOCKF);
//                    u0_dbg_printf("SCI_CLOCKF is %x\n", res);
//                    res = mp3_readRequest(SCI_VOL);
//                    u0_dbg_printf("SCI_VOL is %x\n", res);
//                    res = mp3_readRequest(SCI_BASS);
//                    u0_dbg_printf("SCI_BASS is %x\n", res);

//                      uint16_t sample = mp3_readRequest(SCI_HDAT1);
//                      u0_dbg_printf("SCI_HDAT1 is %x\n", sample);
//                      sample = mp3_readRequest(SCI_HDAT0);
//                      u0_dbg_printf("SCI_HDAT0 is %x\n", sample);
                }

                mp3_ds(); // Assert a HIGH signal to de-assert the CS
            }
            xSemaphoreGive(LabSPI::spi_mutex);
        }

        vTaskDelay(1000);

    }
}

void vplayHello(void * pvParameters)
{

    unsigned char *p;

    for (int x = 0; x < 4; x++) {
        if (xSemaphoreTake(LabSPI::spi_mutex, 1000)) {
            p = &HelloMP3[0]; // Point "p" to the beginning of array
            while (p <= &HelloMP3[sizeof(HelloMP3) - 1]) {
                while (!mp3_dreq_getLevel()) {
                    //DREQ is low while the receive buffer is full
                    //You can do something else here, the bus is free...
                    //Maybe set the volume or whatever...
                }

                //Once DREQ is released (high) we can now send 32 bytes of data
                mp3_data_cs(); //Select Data
                decoderSPI.transfer(*p++); // Send SPI byte
                mp3_data_ds(); //Deselect Data
            }

            //End of file - send 2048 zeros before next file
            mp3_data_cs(); //Select Data//Select Data
            for (int i = 0; i < 2048; i++) {
                while (!mp3_dreq_getLevel())
                    ; //If we ever see DREQ low, then we wait here
                decoderSPI.transfer(0);
            }
            while (!mp3_dreq_getLevel())
                ; //Wait for DREQ to go high indicating transfer is complete
            mp3_data_ds(); //Deselect Data
            xSemaphoreGive(LabSPI::spi_mutex);
        }
    }

    u0_dbg_printf("Done!");
    while (1)
        ;

}

unsigned char song[5000];

void vbufferSong(void * pvParameters)
{
    uint16_t BYTES_TO_RETRIEVE = 256;
    //Song buffer:
    FRESULT readResult;
    bool ret_val = 0;
    static unsigned long sz = Storage::getfileinfo("1:ambhalf.mp3");

    static uint16_t offset = 0;

    while (1) {

        if ((sz - offset) > BYTES_TO_RETRIEVE) {
            if (xSemaphoreTake(LabSPI::spi_mutex, 1000)) {
                readResult = Storage::read("1:ambhalf.mp3", &song[offset], BYTES_TO_RETRIEVE, offset);
                offset += BYTES_TO_RETRIEVE;
                xSemaphoreGive(LabSPI::spi_mutex);
                u0_dbg_printf("%d  ", offset);
            }
        }
        else {
            if (xSemaphoreTake(LabSPI::spi_mutex, 1000)) {
                readResult = Storage::read("1:ambhalf.mp3", &song[offset], (sz - offset), offset);
                offset = 0;
                xSemaphoreGive(LabSPI::spi_mutex);
                u0_dbg_printf("@");
            }
            u0_dbg_printf("retval = %d  first %x \n", ret_val, song[0]);
            //vTaskSuspend(bufferTaskHandle);
        }
    }
}


void vgetSong(void * pvParameters)
{
    unsigned char current_byte[READ_BYTES_FROM_FILE];  //static unsigned char *p; p = &HelloMP3[0];
    static unsigned long offset = 0;
    // int i;
    //unsigned long sz = Storage::getfileinfo("1:perfect.mp3");
    //u0_dbg_printf("%lu ", sz);
    while (1) {
        //current_byte = *p; p++;
        if (xSemaphoreTake(LabSPI::spi_mutex, portMAX_DELAY)) {
            Storage::read("1:perfect.mp3", &current_byte[0], READ_BYTES_FROM_FILE, offset);
            xSemaphoreGive(LabSPI::spi_mutex);
            bool sent = xQueueSend(musicQueue, &current_byte, portMAX_DELAY);
            if (!sent) u0_dbg_printf("sf");
            offset += READ_BYTES_FROM_FILE;
        }
    }

}

void vplaySong(void * pvParameters)
{

    static uint8_t current_count = 0;
    //static int recoffset = 0;
    //unsigned char current_byte;  //static unsigned char *p; p = &HelloMP3[0];
    //static int offset = 0;
    uint8_t receivedByte[READ_BYTES_FROM_FILE];
    //uint8_t transmitByte[READ_BYTES_FROM_FILE];
    uint32_t j=0;
    while (1) {

        if (current_count == 0) {
            xQueueReceive(musicQueue, &receivedByte[0], portMAX_DELAY);
            //memcpy(&transmitByte, receivedByte,READ_BYTES_FROM_FILE );
            //u0_dbg_printf("rec q");
        }

        while (!mp3_dreq_getLevel()) {
            //DREQ is low while the receive buffer is full
            //You can do something else here, the bus is free...
            //Maybe set the volume or whatever...

        }


        //Once DREQ is released (high) we can now send 32 bytes of data

        uint8_t i_plus_one = current_count + 1;

        if (xSemaphoreTake(LabSPI::spi_mutex, portMAX_DELAY)) {
            mp3_data_cs();                //Select Data
            uint32_t j_init = (current_count * TRANSMIT_BYTES_TO_DECODER);
            uint32_t j_max = (i_plus_one * TRANSMIT_BYTES_TO_DECODER);
            //u0_dbg_printf("jinit is %d\n jmax is %d\n", j_init,j_max); vTaskDelay(2000);

            for (j = j_init; j < j_max; j++) {
                decoderSPI.transfer(receivedByte[j]); // Send SPI byte
                //Used below line to check if file is being read properly... OK!!
                //Storage::append("1:myrec.mp3", &receivedByte[j], 1, recoffset);
                //u0_dbg_printf("%x ", receivedByte[j]);
                //recoffset += 1;
            }

            mp3_data_ds(); //Deselect Data
            xSemaphoreGive(LabSPI::spi_mutex);

            if (current_count == (COUNT-1)) {
                current_count = 0;
                j=0;
            }
            else {
                current_count += 1;
            }
        }

    }
}
int main(void)
{

    // Initialize MP3 decoder's SPI
    decoderSPI.init(decoderSPI.SSP1, 8, decoderSPI.Mode_SPI, 16);                //plck by 48 is passed (2MHz) (3,4 MHz sometimes works, no more)
    musicQueue = xQueueCreate(1, sizeof(char[READ_BYTES_FROM_FILE]));
    /*inits for the mp3 decoder*/
    mp3_dreq_init(); //setting dreq as an input pin
    mp3_hardwareReset();
    mp3_initDecoder();
    /*inits for the mp3 decoder END*/

    //Buffer the song
    //vbufferSong();
    //xTaskCreate(vinitCheck, "initCheckTask", 1024, (void *) 1, 1, NULL);
    //xTaskCreate(vplayHello, "playHelloTask", 1024, (void *) 1, 2, NULL);
    xTaskCreate(vgetSong, "getSongTask", 3072, (void *) 1, 1, NULL);
    //xTaskCreate(vbufferSong, "bufferSongTask", 4096, (void *) 1, 2, &bufferTaskHandle);
    xTaskCreate(vplaySong, "playSongTask", 3072, (void *) 1, 1, NULL);

    /* Start Scheduler - This will not return, and your tasks will start to run their while(1) loop */
    vTaskStartScheduler();
    return 0;
}
