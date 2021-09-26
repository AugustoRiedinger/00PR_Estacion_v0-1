/********************************************************************************
  * @file    main.c
  * @author  G. Garcia & A. Riedinger
  * @version 0.1
  * @date    08-07-21
  * @brief   PR - Estacion.
  	  	  	 Prueba de comunicacion inalambrica de dato analogico convertido a digital.

  * SALIDAS:
  	  *	LCD  Conexion Estandar TP - Mostrar dato analogico como prueba.
  	  * LED	 PB0 - Indicacion de recepcion de datos.

  * ENTRADAS:
  	  * RX   PD6 - DATA-RX modulo FS1000A. Recepcion de datos digitales.
********************************************************************************/

/*------------------------------------------------------------------------------
LIBRERIAS:
------------------------------------------------------------------------------*/
#include "mi_libreria.h"

/*------------------------------------------------------------------------------
DEFINICIONES:
------------------------------------------------------------------------------*/
#define DELAY_LCD_REF 100e5
#define DELAY_LCD_ON  100e6
#define DELAY_LED	  100e5

int main(void)
{
/*------------------------------------------------------------------------------
DECLARACION DE VARIABLES:
------------------------------------------------------------------------------*/
	LCD_2X16_t LCD_2X16[] = {
	 // Name   ,PORT , PIN         , CLOCK              , Init
	  {TLCD_RS ,GPIOC,GPIO_Pin_10 ,RCC_AHB1Periph_GPIOC,Bit_RESET},
	  {TLCD_E  ,GPIOC,GPIO_Pin_11 ,RCC_AHB1Periph_GPIOC,Bit_RESET},
	  {TLCD_D4 ,GPIOC,GPIO_Pin_12 ,RCC_AHB1Periph_GPIOC,Bit_RESET},
	  {TLCD_D5 ,GPIOD,GPIO_Pin_2  ,RCC_AHB1Periph_GPIOD,Bit_RESET},
	  {TLCD_D6 ,GPIOF,GPIO_Pin_6  ,RCC_AHB1Periph_GPIOF,Bit_RESET},
	  {TLCD_D7 ,GPIOF,GPIO_Pin_7  ,RCC_AHB1Periph_GPIOF,Bit_RESET},};


/*------------------------------------------------------------------------------
CONFIGURACION DEL MICRO:
------------------------------------------------------------------------------*/
	//Inicializacion del DISPLAY LCD:
	SystemInit();
	INIT_LCD_2x16(LCD_2X16);
	//Versionado:
	PRINT_LCD_2x16(LCD_2X16, 0, 0, "PR - Estacion");
	PRINT_LCD_2x16(LCD_2X16, 0, 1, "ver. 0.1");
	DELAY(DELAY_LCD_ON);

	//Inicializacion del LED como SALIDA DIGITAL:
	INIT_DO(GPIOB, GPIO_Pin_7);

	//Inicializacion del RX-DATA como ENTRADA DIGITAL:
	INIT_DI(GPIOD, GPIO_Pin_6);

/*------------------------------------------------------------------------------
BUCLE PRINCIPAL:
------------------------------------------------------------------------------*/
    while(1)
    {
    	//Refresco del LCD:
    	DELAY(DELAY_LCD_REF);
    	CLEAR_LCD_2x16(LCD_2X16);
    	GPIO_SetBits(GPIOB, GPIO_Pin_7);

    	//Recepcion de datos:
    	while(READ_DI(GPIOD, GPIO_Pin_6))
    	{
    		PRINT_LCD_2x16(LCD_2X16, 0, 0, "RCV ACK");
    	}
    }
}
