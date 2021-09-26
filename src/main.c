/********************************************************************************
  * @file    main.c
  * @author  G. Garcia & A. Riedinger
  * @version 0.1
  * @date    08-07-21
  * @brief   PR - Estacion.

  * SALIDAS:
  	  *	LCD  Conexion Estandar TPs

  * ENTRADAS:
  	  * TEC-MAT
********************************************************************************/

/*------------------------------------------------------------------------------
LIBRERIAS:
------------------------------------------------------------------------------*/
#include "mi_libreria.h"

/*------------------------------------------------------------------------------
DEFINICIONES:
------------------------------------------------------------------------------*/
/*Pines de conexion del teclado matricial: */
#define C1_Port	GPIOD
#define C2_Port	GPIOD
#define C3_Port	GPIOE
#define C4_Port	GPIOE
#define R1_Port	GPIOE
#define R2_Port	GPIOE
#define R3_Port	GPIOE
#define R4_Port	GPIOF
#define C1		GPIO_Pin_0
#define C2		GPIO_Pin_1
#define C3		GPIO_Pin_2
#define C4		GPIO_Pin_3
#define R1		GPIO_Pin_4
#define R2		GPIO_Pin_5
#define R3		GPIO_Pin_6
#define R4		GPIO_Pin_9

/*------------------------------------------------------------------------------
VARIABLES GLOBALES:
------------------------------------------------------------------------------*/
/*Definicion de los pines del LCD: */
LCD_2X16_t LCD_2X16[] = {
			// Name  , PORT ,   PIN      ,         CLOCK       ,   Init
			{ TLCD_RS, GPIOC, GPIO_Pin_10, RCC_AHB1Periph_GPIOC, Bit_RESET },
			{ TLCD_E,  GPIOC, GPIO_Pin_11, RCC_AHB1Periph_GPIOC, Bit_RESET },
			{ TLCD_D4, GPIOC, GPIO_Pin_12, RCC_AHB1Periph_GPIOC, Bit_RESET },
			{ TLCD_D5, GPIOD, GPIO_Pin_2,  RCC_AHB1Periph_GPIOD, Bit_RESET },
			{ TLCD_D6, GPIOF, GPIO_Pin_6,  RCC_AHB1Periph_GPIOF, Bit_RESET },
			{ TLCD_D7, GPIOF, GPIO_Pin_7,  RCC_AHB1Periph_GPIOF, Bit_RESET }, };


int main(void)
{
/*------------------------------------------------------------------------------
CONFIGURACION DEL MICRO:
------------------------------------------------------------------------------*/
	SystemInit();

	/*Inicializacion del DISPLAY LCD: */
	INIT_LCD_2x16(LCD_2X16);

	/*Inicializacion de la interrupcion por pulso externo en los pines de lecura del teclado:*/
	INIT_EXTINT(C1_Port, C1);
	INIT_EXTINT(C2_Port, C2);
	INIT_EXTINT(C3_Port, C3);
	INIT_EXTINT(C4_Port, C4);
	/*Inicializacion de los pines de escirura del teclado como salidas digitales: */
	INIT_DO(R1_Port, R1);
	INIT_DO(R2_Port, R2);
	INIT_DO(R3_Port, R3);
	INIT_DO(R4_Port, R4);


/*------------------------------------------------------------------------------
BUCLE PRINCIPAL:
------------------------------------------------------------------------------*/
    while(1)
    {

    }
}

/*Interrupcion al pulso por PD0-C1:*/
void EXTI0_IRQHandler(void)
{
  /*Si la interrupcion fue por linea 0 (PD0 - C1):*/
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {

    /*Clear the EXTI line 0 pending bit:*/
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}

/*Interrupcion al pulso por PD1-C2:*/
void EXTI1_IRQHandler(void)
{
  /*Si la interrupcion fue por linea 1 (PD1 - C2):*/
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {

    /*Clear the EXTI line 1 pending bit:*/
    EXTI_ClearITPendingBit(EXTI_Line1);
  }

}

/*Interrupcion al pulso por PE2-C3:*/
void EXTI2_IRQHandler(void)
{
  /*Si la interrupcion fue por linea 2 (PD2 - C3):*/
  if(EXTI_GetITStatus(EXTI_Line2) != RESET)
  {

    /*Clear the EXTI line 2 pending bit:*/
    EXTI_ClearITPendingBit(EXTI_Line2);
  }

}

/*Interrupcion al pulso por PE3-C4:*/
void EXTI3_IRQHandler(void)
{
  /*Si la interrupcion fue por linea 3 (PE3 - C4):*/
  if(EXTI_GetITStatus(EXTI_Line3) != RESET)
  {

    /*Clear the EXTI line 3 pending bit:*/
    EXTI_ClearITPendingBit(EXTI_Line3);
  }

}
