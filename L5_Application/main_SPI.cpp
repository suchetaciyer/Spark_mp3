//#include "tasks.hpp"
//#include "examples/examples.hpp"
//#include "io.hpp"
//#include "FreeRTOS.h"
//#include "printf_lib.h"
//#include "uart0_min.h"
//#include "task.h"
//#include "utilities.h"
//#include "LabGPIO_0.hpp"
//#include "LabGPIOInterrupts.hpp"
//#include "semphr.h"
//#include "LabSPI.hpp"
////void print_details();
//SemaphoreHandle_t spi_bus_lock;
//LabSPI SPExample;
//status_reg_t DataRead;
//status_reg_t DataWrite;
//
//uint8_t data_msb;
//uint8_t data_lsb;
//uint8_t manufacturer_id;
//uint8_t device_id_1;
//uint8_t device_id_2;
//LabGPIO CS(2,6); // Select GPIO pin 2.6 for ChipSelect
//void music_decoder_cs()
//{
//CS.setAsOutput();
//CS.setLow();
//}
//void music_decoder_ds()
//{
//CS.setHigh();
//}
//int main(void)
//{
//
//scheduler_add_task(new terminalTask(PRIORITY_HIGH));
////void print_details();
//u0_dbg_printf("Read SPI Flash\n");
//
//
////select SPI0, 8-bit mode, frame mode format - SPI, clock divide
//spi_bus_lock = xSemaphoreCreateMutex();
//SPExample.init(LabSPI::SSP1,8,LabSPI::SPI,8);
//
//
//// Read the signature of the Adesto flash and print it out
//xSemaphoreTake(spi_bus_lock,portMAX_DELAY);
//music_decoder_cs(); // Chip Selected
//SPExample.transfer(0x03); //Opcode to read
//
////SPExample.transfer(0x02); //Opcode to write
//
////data_msb = SPExample.transfer(0xAA); //MSB of status register, dummy bit tx
////data_lsb = SPExample.transfer(0xAA); //LSB of status register, dummy bit tx
//vTaskDelay(2000);
//music_decoder_ds(); // Chip De-selected
//xSemaphoreGive(spi_bus_lock);
//
//
////DataRead.decimal_value = (data_msb << 8) | (data_lsb & 0xff);
////adesto_cs(); // Chip Selected
////SPExample.transfer(0x9F); //Opcode
////manufacturer_id = SPExample.transfer(0xAA);//dummy bit tx
////device_id_1 = SPExample.transfer(0xAA);//dummy bit tx
////device_id_2 = SPExample.transfer(0xAA);//dummy bit tx
////adesto_ds();
////u0_dbg_printf("SPI Flash Manufacturer ID: %#x and Device ID:%#x%#x\n", manufacturer_id, device_id_1, device_id_2);
////u0_dbg_printf("SPI Status Register First Byte : %#x, Second Byte: %#x\n", data_msb, data_lsb);
////u0_dbg_printf("===========Byte One===========\n");
////u0_dbg_printf("Rdy/Busy: %x\n", DataRead.ready_b1);
////u0_dbg_printf("Compare Result: %x\n", DataRead.compare);
////char buffer[4];
////itoa(DataRead.density,buffer, 2); // (value to be converted, destination, numerical base)
////u0_dbg_printf("Density Code: %s\n", buffer);
////u0_dbg_printf("Sector Protection Status: %x\n", DataRead.sector_protect);
////u0_dbg_printf("Page Size Configuration: %x\n\n", DataRead.page_size);
////u0_dbg_printf("(===========Byte One===========\n");
////u0_dbg_printf("Rdy/Busy: %x\n", DataRead.ready_b2);
////u0_dbg_printf("Reserved: %x\n", DataRead.reserved);
////u0_dbg_printf("Erase/Program Error: %x\n", DataRead.erase_prog_error);
////u0_dbg_printf("Reserved: %x\n", DataRead.reserved2);
////u0_dbg_printf("Sector Lockdown Enabled: %x\n", DataRead.lock_enabled);
////u0_dbg_printf("Prog Suspend Status(Buffer 2): %x\n", DataRead.buff_suspend_2);
////u0_dbg_printf("Prog Suspend Status(Buffer 1): %x\n", DataRead.buff_suspend_1);
////u0_dbg_printf("Erase Suspend: %x\n\n\n", DataRead.erase_suspend);
//
//vTaskStartScheduler();
////scheduler_start(); ///< This shouldn't return
//return -1;
//}
