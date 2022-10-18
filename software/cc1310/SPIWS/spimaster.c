/*
 * Copyright (c) 2018-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


/*
 *  ======== spimaster.c ========
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* POSIX Header files */
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/SPI.h>
#include <ti/display/Display.h>

/* Example/Board Header files */
#include "Board.h"
#include "WS2812.h"

#define THREADSTACKSIZE (1024)

#define SPI_MSG_LENGTH  (30)
#define MASTER_MSG      ("Hello from master, msg#: ")

#define MAX_LOOP        (10)

/**************************************************************************
 * Manifest Constants
 **************************************************************************/

//TODO : ADD limitation on NB_PIXELS
#ifndef NB_PIXELS
#define NB_PIXELS 46U
#endif

#define NB_SPI_BYTES_PER_PIXEL 9U

/** Get SPI value corresponding to a bit at index n in a grb color on 24 bits
 *  1 bit is 0b110
 *  0 bit is 0b100
 */
#define GRB_BIT_TO_SPI_BITS(val, bitPos) ((1 << bitPos & val) ? 0x06 : 0x04)

static Display_Handle display;

unsigned char masterRxBuffer[NB_SPI_BYTES_PER_PIXEL*NB_PIXELS];
unsigned char masterTxBuffer[NB_SPI_BYTES_PER_PIXEL*NB_PIXELS];

static uint8_t _au8_spiLedBuffer[NB_SPI_BYTES_PER_PIXEL*NB_PIXELS] = {0};


#include <ti/drivers/SPI.h>
#include <ti/drivers/GPIO.h>


/**************************************************************************
 * Macros
 **************************************************************************/

/**************************************************************************
 * Local Functions Declarations
 **************************************************************************/

/**************************************************************************
 * Global Functions Defintions
 **************************************************************************/

/* Semaphore to block master until slave is ready for transfer */
sem_t masterSem;

/*
 *  ======== slaveReadyFxn ========
 *  Callback function for the GPIO interrupt on Board_SPI_SLAVE_READY.
 */
void slaveReadyFxn(uint_least8_t index)
{
    sem_post(&masterSem);
}

/*
 *  ======== masterThread ========
 *  Master SPI sends a message to slave while simultaneously receiving a
 *  message from the slave.
 */
void *masterThread(void *arg0)
{
    SPI_Handle      masterSpi;
    SPI_Params      spiParams;
    SPI_Transaction transaction;
    bool            transferOK;
    uint16_t loc_u16_pixelIndex;

    GPIO_setConfig(Board_SPI_MASTER_READY, GPIO_CFG_OUTPUT | GPIO_CFG_OUT_LOW);
    GPIO_write(Board_SPI_MASTER_READY, 1);

    SPI_Params_init(&spiParams);
    spiParams.frameFormat = SPI_POL0_PHA1;
    spiParams.bitRate = 2400000;
    masterSpi = SPI_open(Board_SPI_MASTER, &spiParams);
    if (masterSpi == NULL) {
        Display_printf(display, 0, 0, "Error initializing master SPI\n");
        while (1);
    }
    else {
        Display_printf(display, 0, 0, "Master SPI initialized\n");
    }

    //masterTxBuffer[sizeof(NB_SPI_BYTES_PER_PIXEL*NB_PIXELS) - 1] = '0';

    //memset((void *) _au8_spiLedBuffer, 0, NB_SPI_BYTES_PER_PIXEL*NB_PIXELS);
    /** Put all led to 0 */
    for(loc_u16_pixelIndex = 0; loc_u16_pixelIndex < NB_PIXELS; loc_u16_pixelIndex++)
    {
        WS2812_setPixelColor(loc_u16_pixelIndex, 0, 0, 0);
    }

    for(loc_u16_pixelIndex = 0; loc_u16_pixelIndex < NB_PIXELS; loc_u16_pixelIndex++)
    {
        WS2812_setPixelColor(loc_u16_pixelIndex, 0x00, 0xFF, 0x00);
    }

    transaction.count = sizeof(_au8_spiLedBuffer);
    transaction.txBuf = _au8_spiLedBuffer;
    transaction.rxBuf = NULL;

    transferOK = SPI_transfer(masterSpi, &transaction);
    if(transferOK)
    {
        Display_printf(display, 0, 0, "SPI worked!");
    }

    GPIO_write(Board_SPI_MASTER_READY, 0);


    return (NULL);
}

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    pthread_t           thread0;
    pthread_attr_t      attrs;
    struct sched_param  priParam;
    int                 retc;
    int                 detachState;

    /* Call driver init functions. */
    Display_init();
    GPIO_init();
    SPI_init();

    /* Configure the LED pins */
    GPIO_setConfig(Board_GPIO_LED0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO_LED1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /* Open the display for output */
    display = Display_open(Display_Type_UART, NULL);
    if (display == NULL) {
        /* Failed to open display driver */
        while (1);
    }

    /* Turn on user LED */
    GPIO_write(Board_GPIO_LED0, Board_GPIO_LED_ON);

    Display_printf(display, 0, 0, "Starting the SPI master example");
    Display_printf(display, 0, 0, "This example requires external wires to be "
        "connected to the header pins. Please see the Board.html for details.\n");

    /* Create application threads */
    pthread_attr_init(&attrs);

    detachState = PTHREAD_CREATE_DETACHED;
    /* Set priority and stack size attributes */
    retc = pthread_attr_setdetachstate(&attrs, detachState);
    if (retc != 0) {
        /* pthread_attr_setdetachstate() failed */
        while (1);
    }

    retc |= pthread_attr_setstacksize(&attrs, THREADSTACKSIZE);
    if (retc != 0) {
        /* pthread_attr_setstacksize() failed */
        while (1);
    }

    /* Create master thread */
    priParam.sched_priority = 1;
    pthread_attr_setschedparam(&attrs, &priParam);

    retc = pthread_create(&thread0, &attrs, masterThread, NULL);
    if (retc != 0) {
        /* pthread_create() failed */
        while (1);
    }

    return (NULL);
}

void WS2812_setPixelColor(uint16_t arg_u16_ledIndex, uint8_t arg_u8_red, uint8_t arg_u8_green, uint8_t arg_u8_blue)
{
    uint8_t loc_u8_currIndex = 3;

    /** Position of current led data in SPI buffer */
    uint16_t loc_u16_ledOffset = arg_u16_ledIndex*9;

    /** Concatenate color on a 32bit word */
    uint32_t loc_u32_grb = arg_u8_green << 16 | arg_u8_red << 8 | arg_u8_blue;

    /** Concatenate two bytes of SPI buffer in order to always transfer blocks of 3 bits
     * to SPI buffer corresponding to a single grb bit*/
    uint16_t loc_u16_currVal = 0;

    int8_t loc_u8_bitIndex;

    for(loc_u8_bitIndex = 23; loc_u8_bitIndex >= 0; loc_u8_bitIndex--)
    {
        loc_u16_currVal |= GRB_BIT_TO_SPI_BITS(loc_u32_grb, loc_u8_bitIndex) << (16 + 8*((loc_u8_currIndex - 3)/8) - loc_u8_currIndex);

        if((loc_u8_currIndex)/8 > (loc_u8_currIndex-3)/8) /** some bits have been written to byte at index 1 in  loc_u16_currVal*/
        {
            /** it's time to shift buffers */
            _au8_spiLedBuffer[loc_u16_ledOffset + loc_u8_currIndex /8 - 1] = loc_u16_currVal >> 8;
            loc_u16_currVal = loc_u16_currVal << 8;
        }
        loc_u8_currIndex += 3;
    }
}
