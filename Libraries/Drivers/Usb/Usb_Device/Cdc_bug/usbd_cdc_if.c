/**
  ******************************************************************************
  * @file    USB_Device/CDC_Standalone/USB_Device/App/usbd_cdc_if.c
  * @author  MCD Application Team
  * @brief   Source file for USBD CDC interface
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------ */
#include "main.h"
#include "usbd_cdc.h"

/* Private typedef ----------------------------------------------------------- */
/* Private define ------------------------------------------------------------ */


/* Private macro ------------------------------------------------------------- */
/* Private variables --------------------------------------------------------- */
USBD_CDC_LineCodingTypeDef LineCoding = {
  115200,                       /* baud rate */
  0x00,                         /* stop bits-1 */
  0x00,                         /* parity - none */
  0x08                          /* nb. of bits 8 */
};

/* Prescaler declaration */
uint32_t uwPrescalerValue = 0;

uint8_t UserRxBuffer[CDC_RX_DATA_SIZE]; /* Received Data over USB are stored in
                                         * this buffer */
uint8_t UserTxBuffer[CDC_TX_DATA_SIZE]; /* Received Data over UART (CDC
                                         * interface) are stored in this buffer
                                         */

uint32_t UserTxBufPtrIn = 0;    /* Increment this pointer or roll it back to
                                 * start address when data are received over
                                 * USART */
uint32_t UserTxBufPtrOut = 0;   /* Increment this pointer or roll it back to
                                 * start address when data are sent over USB */

/* TIM handler declaration */
TIM_HandleTypeDef TimHandle;
/* USB handler declaration */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* Private function prototypes ----------------------------------------------- */
static int8_t CDC_Itf_Init(void);
static int8_t CDC_Itf_DeInit(void);
static int8_t CDC_Itf_Control(uint8_t cmd, uint8_t * pbuf, uint16_t length);
static int8_t CDC_Itf_Receive(uint8_t * pbuf, uint32_t * Len);
static int8_t CDC_TransmitCplt(uint8_t *pbuf, uint32_t *Len, uint8_t epnum);
static void ComPort_Config(void);

USBD_CDC_ItfTypeDef USBD_CDC_fops = {
  CDC_Itf_Init,
  CDC_Itf_DeInit,
  CDC_Itf_Control,
  CDC_Itf_Receive,
  CDC_TransmitCplt
};

/* Private functions --------------------------------------------------------- */

/**
  * @brief  Initializes the CDC media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_Init(void)
{

  /* ##-1- Put UART peripheral in IT reception process ######################## */
  /* Any data received will be stored in "UserTxBuffer" buffer */
  if (HAL_UART_Receive_IT(&SERIAL_PORT, (uint8_t *) UserTxBuffer, 1) != HAL_OK)
  {
    /* Transfer error in reception process */
    Error_Handler();
  }

  /* ##-2- Start the TIM Base generation in interrupt mode #################### */
  /* Start Channel1 */
  if (HAL_TIM_Base_Start_IT(&CDC_TIMER) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }

  /* ##-3- Set Application Buffers ############################################ */
  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, UserTxBuffer, 0);
  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, UserRxBuffer);

  return (USBD_OK);
}

/**
  * @brief  CDC_Itf_DeInit
  *         DeInitializes the CDC media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_DeInit(void)
{
  /* DeInitialize the UART peripheral */
  if (HAL_UART_DeInit(&SERIAL_PORT) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  return (USBD_OK);
}

/**
  * @brief  CDC_Itf_Control
  *         Manage the CDC class requests
  * @param  Cmd: Command code
  * @param  Buf: Buffer containing command data (request parameters)
  * @param  Len: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_Control(uint8_t cmd, uint8_t * pbuf, uint16_t length)
{
  switch (cmd)
  {
  case CDC_SEND_ENCAPSULATED_COMMAND:
    /* Add your code here */
    break;

  case CDC_GET_ENCAPSULATED_RESPONSE:
    /* Add your code here */
    break;

  case CDC_SET_COMM_FEATURE:
    /* Add your code here */
    break;

  case CDC_GET_COMM_FEATURE:
    /* Add your code here */
    break;

  case CDC_CLEAR_COMM_FEATURE:
    /* Add your code here */
    break;

  case CDC_SET_LINE_CODING:
    LineCoding.bitrate = (uint32_t) (pbuf[0] | (pbuf[1] << 8) |
                                     (pbuf[2] << 16) | (pbuf[3] << 24));
    LineCoding.format = pbuf[4];
    LineCoding.paritytype = pbuf[5];
    LineCoding.datatype = pbuf[6];

    /* Set the new configuration */
    ComPort_Config();
    break;

  case CDC_GET_LINE_CODING:
    pbuf[0] = (uint8_t) (LineCoding.bitrate);
    pbuf[1] = (uint8_t) (LineCoding.bitrate >> 8);
    pbuf[2] = (uint8_t) (LineCoding.bitrate >> 16);
    pbuf[3] = (uint8_t) (LineCoding.bitrate >> 24);
    pbuf[4] = LineCoding.format;
    pbuf[5] = LineCoding.paritytype;
    pbuf[6] = LineCoding.datatype;
    break;

  case CDC_SET_CONTROL_LINE_STATE:
    /* Add your code here */
    break;

  case CDC_SEND_BREAK:
    /* Add your code here */
    break;

  default:
    break;
  }

  return (USBD_OK);
}

/**
  * @brief  CDC_Itf_DataRx
  *         Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  * @param  Buf: Buffer of data to be transmitted
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_Receive(uint8_t * Buf, uint32_t * Len)
{
  HAL_UART_Transmit_DMA(&SERIAL_PORT, Buf, *Len);
  return (USBD_OK);
}


/**
  * @brief  CDC_TransmitCplt
  *         Data transmitted callback
  *
  *         @note
  *         This function is IN transfer complete callback used to inform user that
  *         the submitted Data is successfully sent over USB.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_TransmitCplt(uint8_t *Buf, uint32_t *Len, uint8_t epnum)
{
  UNUSED(Buf);
  UNUSED(Len);
  UNUSED(epnum);

  return (0);
}

/**
  * @brief  ComPort_Config
  *         Configure the COM Port with the parameters received from host.
  * @param  None.
  * @retval None
  * @note   When a configuration is not supported, a default value is used.
  */
static void ComPort_Config(void)
{
  if (HAL_UART_DeInit(&SERIAL_PORT) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* set the Stop bit */
  switch (LineCoding.format)
  {
  case 0:
    SERIAL_PORT.Init.StopBits = UART_STOPBITS_1;
    break;
  case 2:
    SERIAL_PORT.Init.StopBits = UART_STOPBITS_2;
    break;
  default:
    SERIAL_PORT.Init.StopBits = UART_STOPBITS_1;
    break;
  }

  /* set the parity bit */
  switch (LineCoding.paritytype)
  {
  case 0:
    SERIAL_PORT.Init.Parity = UART_PARITY_NONE;
    break;
  case 1:
    SERIAL_PORT.Init.Parity = UART_PARITY_ODD;
    break;
  case 2:
    SERIAL_PORT.Init.Parity = UART_PARITY_EVEN;
    break;
  default:
    SERIAL_PORT.Init.Parity = UART_PARITY_NONE;
    break;
  }

  /* set the data type : only 8bits and 9bits is supported */
  switch (LineCoding.datatype)
  {
  case 0x07:
    /* With this configuration a parity (Even or Odd) must be set */
    SERIAL_PORT.Init.WordLength = UART_WORDLENGTH_8B;
    break;
  case 0x08:
    if (SERIAL_PORT.Init.Parity == UART_PARITY_NONE)
    {
      SERIAL_PORT.Init.WordLength = UART_WORDLENGTH_8B;
    }
    else
    {
      SERIAL_PORT.Init.WordLength = UART_WORDLENGTH_9B;
    }

    break;
  default:
    SERIAL_PORT.Init.WordLength = UART_WORDLENGTH_8B;
    break;
  }

  SERIAL_PORT.Init.BaudRate = LineCoding.bitrate;
  SERIAL_PORT.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  SERIAL_PORT.Init.Mode = UART_MODE_TX_RX;
  SERIAL_PORT.Init.OverSampling = UART_OVERSAMPLING_16;

  if (HAL_UART_Init(&SERIAL_PORT) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* Start reception: provide the buffer pointer with offset and the buffer
   * size */
  HAL_UART_Receive_IT(&SERIAL_PORT, (uint8_t *) (UserTxBuffer + UserTxBufPtrIn),
                      1);
}

uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len)
{
  uint8_t result = USBD_OK;
  /* USER CODE BEGIN 12 */
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
  if ( hcdc == NULL )
	    return USBD_BUSY;
  if (hcdc->TxState != 0){
    return USBD_BUSY;
  }
  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
  result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);
  /* USER CODE END 12 */
  return result;
}


