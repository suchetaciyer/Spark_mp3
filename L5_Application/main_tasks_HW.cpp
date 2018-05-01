//
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
//#include "command_handler.hpp"
//
//
//QueueHandle_t q;
//
//typedef enum
//    { invalid,
//        up,
//        down,
//        left,
//        right
//    } orientation_t;
//
//orientation_t ori;
//
//orientation_t read_accelerometer()
//{
//    int tilt_x = AS.getX();
//    int tilt_y = AS.getY();
//    int tilt_z = AS.getZ();
//
//    if((tilt_x >-150 && tilt_x < 150) && (tilt_y >-150 && tilt_y < 150) && (tilt_z > 924))
//    {
//        ori = up;
//    }
//    else if ((tilt_x >-150 && tilt_x < 150) && (tilt_y >-150 && tilt_y < 150) && (tilt_z < -924))
//    {
//       ori = down;
//    }
//    else if ((tilt_x < -924) && (tilt_y >-150 && tilt_y < 150) && (tilt_z >-150 && tilt_z < 150))
//    {
//        ori = right;
//    }
//    else if ((tilt_x > 924) && (tilt_y >-150 && tilt_y < 150) && (tilt_z >-150 && tilt_z < 150))
//    {
//        ori = left;
//    }
//    else
//    {
//        ori = invalid;
//    }
//    //u0_dbg_printf("%4i %4i %4i\n",AS.getX(),AS.getY(),AS.getZ());
//
//    return ori;
//}
//
//
//void producer(void *p) /* LOW priority */
//{
//    orientation_t prod_ori = invalid;
//    while (1)
//    {
//        prod_ori = read_accelerometer();
//        u0_dbg_printf("             Before Send\n");
//        if (xQueueSend(q, &prod_ori, 0))
//        {
//            u0_dbg_printf("             After Send\n");
//        }
//        else
//        {
//            u0_dbg_printf("             Sending Failed!!\n");
//        }
//        vTaskDelay(1000);
//    }
//}
//
//void consumer(void *p) /* HIGH priority */
//{
//  orientation_t cons_ori = invalid;
//  while (1)
//  {
//    if(xQueueReceive(q, &cons_ori, portMAX_DELAY))
//    {
//        if(cons_ori == 1)
//        {
//            u0_dbg_printf("up\n");
//        }
//        else if(cons_ori == 2)
//        {
//            u0_dbg_printf("down\n");
//        }
//        else if(cons_ori == 3)
//        {
//            u0_dbg_printf("left\n");
//        }
//        else if(cons_ori == 4)
//        {
//            u0_dbg_printf("right\n");
//        }
//        else
//        {
//            u0_dbg_printf("invalid\n");
//        }
//    }
//    else
//    {
//        u0_dbg_printf("Receive Failed !!\n");
//    }
//  }
//}
//
//TaskHandle_t producer_task_handle, consumer_task_handle;
//
//int main(void)
//{
//    q = xQueueCreate(10, sizeof(int));
//    scheduler_add_task(new terminalTask(PRIORITY_HIGH));
//    xTaskCreate(producer ,"producer_task", STACK_BYTES(2048), 0, 1, &producer_task_handle);
//    xTaskCreate(consumer,"consumer_task", STACK_BYTES(2048), 0, 1, &consumer_task_handle);
//    //vTaskStartScheduler();
//    scheduler_start();
//    return -1;
//}
//
//CMD_HANDLER_FUNC(orientationCmdHandler)
//{
//    if(cmdParams == "off")
//    {
//        vTaskSuspend(producer_task_handle);
//        vTaskSuspend(consumer_task_handle);
//    }
//    else if(cmdParams == "on")
//    {
//        vTaskResume(producer_task_handle);
//        vTaskResume(consumer_task_handle);
//
//    }
//    else
//    {
//        output.printf("ERROR for my command\n");
//    }
//
//    /* return false will display command's help to the user */
//    return true; /* return true if command was successful */
//}
//
//
//
//
//
//
//
