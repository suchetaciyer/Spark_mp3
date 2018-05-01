///*
// * sem_example.cpp
// *
// *  Created on: Mar 20, 2018
// *      Author: Sucheta
// */
//
///*
// * main_another.cpp
// *
// *  Created on: Mar 18, 2018
// *      Author: Sucheta
// */
//
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
// *          FreeRTOS and stdio printf is pre-configured to use uart0_min.h before main() enters.
// *          @see L0_LowLevel/lpc_sys.h if you wish to override printf/scanf functions.
// *
// */
//#include "tasks.hpp"
//#include "io.hpp"
//#include "FreeRTOS.h"
//#include "printf_lib.h"
//#include "uart0_min.h"
//#include "stdio.h"
//#include "task.h"
//#include "utilities.h"
//#include "semphr.h"
//#include "lpc_rit.h"
//#include "queue.h"
//
//
//
////Precious resource to be accessed
//
//void user2task()
//{
//    puts("Doing Boss' Work...");
//}
//// Global Queue Handle
//SemaphoreHandle_t gatekeeper = 0;
//
//void timed_interrupt()
//{
//    long task_woken = 0;
//    xSemaphoreGiveFromISR(gatekeeper,&task_woken);
//    if(task_woken)
//    {
//        //vPortYieldFromISR();
//        portYIELD_FROM_ISR(gatekeeper);
//    }
//}
//void user2(void* p)
//{
//    while(1)
//    {
//        if(xSemaphoreTake(gatekeeper,portMAX_DELAY))
//        {
//            user2task();
//            puts("Employee has finished his task\n");
//        }
//    }
//    vTaskDelay(1000);
//}
//
//int main()
//{
//
//    vSemaphoreCreateBinary(gatekeeper);
//
//    rit_enable(timed_interrupt,1000);
//    //xTaskCreate(user1,"usr1", STACK_BYTES(2048), 0, 1, 0);
//    xTaskCreate(user2,"usr2", STACK_BYTES(2048), 0, 2, 0);
//    vTaskStartScheduler();
//
//    return -1;
//}
//
//
//
//
//
//
//
//
//
//
//
