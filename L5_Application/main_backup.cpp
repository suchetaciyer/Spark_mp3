///*
// *     SocialLedge.com - Copyright (C) 2013
// *
// *     This file is part of free software framework for embedded processors.
// *     You can use it and/or distribute it as long as this copyright header
// *     remains unmodified.  The code is free for personal use and requires
// *     permission to use in a commercial product.
// *
// *      THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// *      OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// *      MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// *      I SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
// *      CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
// *
// *     You can reach the author of this software at :
// *          p r e e t . w i k i @ g m a i l . c o m
// */
//
///**
// * @file
// * @brief This is the application entry point.
// * 			FreeRTOS and stdio printf is pre-configured to use uart0_min.h before main() enters.
// * 			@see L0_LowLevel/lpc_sys.h if you wish to override printf/scanf functions.
// *
// */
//#include "tasks.hpp"
//#include "examples/examples.hpp"
//#include "io.hpp"
////#include "L4_IO/FAT/disk/sd.h"
////#include "L4_IO/src/FileSystemObject.hpp"
//#include <fstream>
//#include <storage.hpp>
//#include "stdio.h"
//#include "printf_lib.h"
//#include "LabSPI.hpp"
//#include "stdio.h"
//#include "semphr.h"
//
//
//void mytask(void* param){
//    while(1){
//        uint8_t current_byte;
//        static int offset=0;
//        Storage::read("1:amb.mp3", &current_byte,1, offset);
//        u0_dbg_printf("%x ", current_byte);
//        offset+=8;
//        vTaskDelay(500);
//    }
//}
//int main(void)
//{
//    scheduler_add_task(new terminalTask(PRIORITY_HIGH));
//
//    char read_buff[30];
//
//    char write_buff[15]="Sucheta Rocks";
//    char write_buff1[16]="and Sneha Rocks";
//    Storage::write("1:abc.txt", &write_buff, 13,0);
//
//    Storage::append("1:abc.txt",write_buff1,15,15);
//
//    xTaskCreate(mytask,"songread",1024,NULL,1,NULL);
//    //
//    // TODO: Initialize your SPI
//    mySPI.init(mySPI.SSP1, 8, mySPI.Mode_SPI, 4);
//    // The simplest test is to try to read the signature of the Adesto flash and print it out
//    // Assert a LOW signal on the CS signal connected to Adesto
//
//   // spi_mutex = xSemaphoreCreateMutex();
//    xTaskCreate(vReadManuandDeviceID, "task_manuid", 1024, (void *) 1, 1, NULL);
//
//    /* Start Scheduler - This will not return, and your tasks will start to run their while(1) loop */
//    vTaskStartScheduler();
//    return 0;
//
//
//
//
//    vTaskStartScheduler();
//
//
//
//    scheduler_start(); ///< This shouldn't return
//    return -1;
//}
