/*
 *  ======== StartBIOS.c ========
 */
#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_memmap.h>

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/I2C.h>

/* Currently unused RTOS headers that are needed
 * for advanced features like IPC. */
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Mailbox.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/hal/Timer.h>

/* Driverlib headers */
#include <driverlib/gpio.h>

/* Board Header files */
#include <Board.h>
#include <EK_TM4C1294XL.h>
#include <Poll_Task.h>

/* Application headers */
#include <UART_Task.h>
#include <HTUTask.h>
#include <Poll_Task.h>

int main(void)
{
    uint32_t ui32SysClock;
    ui32SysClock = Board_initGeneral(120000000);

    //Init I2C
    Board_initGPIO();
    Board_initI2C();

    //(void) COMMTASK();
   // System_printf("Created COM Task\n");
    //System_flush();

    System_printf("Poll Task setup\n");
    setup_Poll_Task();

    /*Initialize+start UART Task*/
    (void)setup_UART_Task();
    System_printf("Created UART Task\n");

    /* Start BIOS */
    System_printf("Start BIOS\n");
    System_flush();
    BIOS_start();
}
