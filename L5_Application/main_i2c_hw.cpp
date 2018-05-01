///*
// * main_i2c_hw.cpp
// *
// *  Created on: Mar 27, 2018
// *      Author: Sucheta
// */
//
//
//#include "tasks.hpp"
//#include "FreeRTOS.h"
//#include "printf_lib.h"
//#include "uart0_min.h"
//#include "stdio.h"
//#include "utilities.h"
//#include "semphr.h"
//#include "lpc_rit.h"
//
//
//
//#if 0
//#include "I2C2.hpp"
//void vSendMsgToSlave(void* param)
//{
//   const char my_dev_addr = 0x68; // Your device address
//   const char my_dev_reg  = 0x01; // Write to 1st register of your device
//   const char my_dev_data = 0xAB; // Write 0xAB to reg 0x01
//   I2C2::getInstance().writeReg(my_dev_addr, my_dev_reg, my_dev_data);
//
//}
//int main(void)
//{
//    xTaskCreate(vSendMsgToSlave, "MasterTask", 1024, (void *) 0, PRIORITY_MEDIUM, NULL);
//    vTaskStartScheduler();
//    return -1;
//}
//
//#endif
//
//#if 0       //Master Write-Slave Read - LED Glow
//#include "i2c2_slave.hpp"
//#include "io.hpp"
//
//
//void vRecMsgFromMaster(void* param)
//{
//   //uint8_t LED = LE.getInstance();
//   const uint32_t SIZEOF_SlaveData = 4;
//   uint8_t SlaveBuffer[SIZEOF_SlaveData] = {0x00,0x00,0x00,0x00};
//   i2c2_slave::getInstance().init(100,SlaveBuffer,SIZEOF_SlaveData );
//   while (1)
//   {
//       for(int  i=0;i<SIZEOF_SlaveData;i++)
//           LE.set(i+1,SlaveBuffer[i]);
//
//       vTaskDelay(1000);
//   }
//}
//int main(void)
//{
//    xTaskCreate(vRecMsgFromMaster, "Slave Task", 1024, (void *) 0, PRIORITY_MEDIUM, NULL);
//    vTaskStartScheduler();
//    return -1;
//}
//
//#endif
//
//
//#if 0       //Master Read-Slave Write - LED Glow
//#include "i2c2_slave.hpp"
//#include "io.hpp"
//
//
//void vRecMsgFromMaster(void* param)
//{
//   //uint8_t LED = LE.getInstance();
//   const uint32_t SIZEOF_SlaveData = 4;
//   uint8_t SlaveBuffer[SIZEOF_SlaveData] = {0x00,0x00,0x00,0x00};
//   i2c2_slave::getInstance().init(100,SlaveBuffer,SIZEOF_SlaveData );
//   while (1)
//   {
//       //bool temp=false;
//       for (unsigned int i=0;i<(SIZEOF_SlaveData/2);i++)
//       {
//           SlaveBuffer[i] = 0;
//           SlaveBuffer[i+2] = 1;
//       }
//       vTaskDelay(1000);
//       for (unsigned int i=0;i<(SIZEOF_SlaveData/2);i++)
//       {
//           SlaveBuffer[i] = 1;
//           SlaveBuffer[i+2] = 0;
//       }
//      vTaskDelay(1000);
//
//
//   }
//}
//int main(void)
//{
//    xTaskCreate(vRecMsgFromMaster, "Slave Task", 1024, (void *) 0, PRIORITY_MEDIUM, NULL);
//    vTaskStartScheduler();
//    return -1;
//}
//
//#endif
//
//
//#if 1       //Master is writing and reading back
//#include "i2c2_slave.hpp"
//#include "io.hpp"
//
//
//void vRecMsgFromMaster(void* param)
//{
//   const uint32_t SIZEOF_SlaveData = 4;
//   uint8_t SlaveBuffer[SIZEOF_SlaveData] = {0,0,0,0};
//   //no of lED, num of times, freq in sec.
//
//   i2c2_slave::getInstance().init(100,SlaveBuffer,SIZEOF_SlaveData );
//   while (1)
//   {
//       //LD.init();
//
//
//      for(int  i=0;i<SIZEOF_SlaveData;i++)
//          {
//              LE.set(i+1,SlaveBuffer[i]);
//              u0_dbg_printf("Slave Rec Data: %d\n",SlaveBuffer[i]);
//         }
//      //vTaskDelay(1000);
//
//      /* int freq_in_ms = (1/SlaveBuffer[2]) * 1000;
//       //u0_dbg_printf("freq=%d",freq_in_ms);
//
//       for (int i = 0; i< int(SlaveBuffer[1]);i++)
//       {
//           // Blink only 1 LED
//           if (SlaveBuffer[0] == 1)
//           {
//               LE.set(1,1);
//               vTaskDelay(freq_in_ms/2);
//               LE.set(1,0);
//               vTaskDelay(freq_in_ms/2);
//           }
//           //Blink 2 LEDS
//           else if (SlaveBuffer[0] == 2)
//           {
//              LE.set(1,1);
//              LE.set(2,1);
//              vTaskDelay(freq_in_ms/2);
//              LE.set(1,0);
//              LE.set(2,0);
//              vTaskDelay(freq_in_ms/2);
//           }
//           //Blink 3 LEDS
//           else if (SlaveBuffer[0] == 3)
//           {
//             LE.set(1,1);
//             LE.set(2,1);
//             LE.set(3,1);
//             vTaskDelay(freq_in_ms/2);
//             LE.set(1,0);
//             LE.set(2,0);
//             LE.set(3,0);
//             vTaskDelay(freq_in_ms/2);
//           }
//           //Blink 4 LEDs
//           else if (SlaveBuffer[0] == 4)
//           {
//               LE.set(1,1);
//               LE.set(2,1);
//               LE.set(3,1);
//               LE.set(4,1);
//               vTaskDelay(freq_in_ms/2);
//               LE.set(1,0);
//               LE.set(2,0);
//               LE.set(3,0);
//               LE.set(4,0);
//               vTaskDelay(freq_in_ms/2);
//           }
//           else
//               LE.set(1,0);
//               LE.set(2,0);
//               LE.set(3,0);
//               LE.set(4,0);
//               vTaskDelay(freq_in_ms);
//       }*/
//   }
//}
//
//int main(void)
//{
//    xTaskCreate(vRecMsgFromMaster, "Slave Task", 1024, (void *) 0, PRIORITY_MEDIUM, NULL);
//
//    vTaskStartScheduler();
//    return -1;
//}
//
//#endif
//
//#if 0  //Master main
//
//#include "tasks.hpp"
//#include "examples/examples.hpp"
//
///**
// * The main() creates tasks or "threads".  See the documentation of scheduler_task class at scheduler_task.hpp
// * for details.  There is a very simple example towards the beginning of this class's declaration.
// *
// * @warning SPI #1 bus usage notes (interfaced to SD & Flash):
// *      - You can read/write files from multiple tasks because it automatically goes through SPI semaphore.
// *      - If you are going to use the SPI Bus in a FreeRTOS task, you need to use the API at L4_IO/fat/spi_sem.h
// *
// * @warning SPI #0 usage notes (Nordic wireless)
// *      - This bus is more tricky to use because if FreeRTOS is not running, the RIT interrupt may use the bus.
// *      - If FreeRTOS is running, then wireless task may use it.
// *        In either case, you should avoid using this bus or interfacing to external components because
// *        there is no semaphore configured for this bus and it should be used exclusively by nordic wireless.
// */
//
//#include "I2C2.hpp"
//#include "I2C2_slave.hpp"
//#include "printf_lib.h"
//#include "io.hpp"
//
//uint8_t myData[4] = { 1, 0, 1, 0 };
//uint8_t myData_alt1[4] = { 1, 1, 0, 0 };
//uint8_t myData_alt2[4] = { 0, 1, 0, 1 };
//uint8_t myData_alt3[4] = { 0, 0, 1, 1 };
//uint8_t myRecdData[4];
//
//const char my_dev_addr = (0x1F << 1); // Your slave's address
//const char my_dev_reg = 0x00; // Write to 1st register of your device
//uint32_t transferSize = 4; // (valid: 1-4)
//void readDataSetLED()
//{
//    I2C2::getInstance().readRegisters(my_dev_addr, my_dev_reg, myRecdData, transferSize);
//    for (unsigned int i = 0; i < transferSize; i++) {
//       LE.set(i+1,myRecdData[i]);
//    }
//}
//void vSendMsgToSlave(void* param)
//{
//    while (1) {
//        I2C2::getInstance().init(100); //initializing I2C master
//        /*bool response = I2C2::getInstance().checkDeviceResponse(my_dev_addr);
//         u0_dbg_printf("resp %d\n", response);*/
//
//       /* //write single data
//        const char my_dev_data = 0x11; // Write 0xAB to reg 0x01
//        I2C2::getInstance().writeReg(my_dev_addr,my_dev_reg,my_dev_data);
//        //read single data
//         myData = I2C2::getInstance().readReg(my_dev_addr, my_dev_reg);
//         u0_dbg_printf("recd %x", myData);*/
//
//        //write multiple data - for leds
//        I2C2::getInstance().writeRegisters(my_dev_addr, my_dev_reg, myData, transferSize);
//        vTaskDelay(1000);
//        readDataSetLED();
//        vTaskDelay(2000);
//
//        I2C2::getInstance().writeRegisters(my_dev_addr, my_dev_reg, myData_alt1, transferSize);
//        vTaskDelay(1000);
//        readDataSetLED();
//        vTaskDelay(2000);
//
//        I2C2::getInstance().writeRegisters(my_dev_addr, my_dev_reg, myData_alt2, transferSize);
//        vTaskDelay(1000);
//        readDataSetLED();
//        vTaskDelay(2000);
//
//        I2C2::getInstance().writeRegisters(my_dev_addr, my_dev_reg, myData_alt3, transferSize);
//        vTaskDelay(1000);
//        readDataSetLED();
//        vTaskDelay(2000);
//    }
//}
//
//
//void vSlaveReceiveMsg(void* param)
//{
//    I2C2_slave::getInstance().init(100); //slave mode initialized.
//
//}
//int main(void)
//{
//    xTaskCreate(vSendMsgToSlave, "MasterTask", 1024, (void *) 0, PRIORITY_MEDIUM, NULL);
//    vTaskStartScheduler();
//    return -1;
//}
//
//
//#endif
