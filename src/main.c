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
/*Control del tiempo - Delays:*/
#define Ticks5Seg 20

/*Parametros de configuración del TIM3 para actualizar el LCD cada 250mseg:*/
#define Freq 	 4
#define TimeBase 200e3

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

/*Variables para controlar los menues:*/
uint32_t WindowA 	= 1;
uint32_t WindowB 	= 0;
uint32_t WindowC 	= 0;
uint32_t WindowC1 	= 0;
uint32_t WindowC2 	= 0;
uint32_t WindowC21 	= 0;
uint32_t WindowC3 	= 0;
uint32_t WindowC4 	= 0;
uint32_t WindowC41 	= 0;
uint32_t WindowC5 	= 0;
uint32_t WindowC6 	= 0;

/*Varibales del Systick:*/
uint32_t Cont5Seg  	= 0;

/*Variables para controlar el tiempo:*/
uint32_t Flag5Seg 	= 0;

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

	/*Inicialización del TIM3:*/
	INIT_TIM3();
	SET_TIM3(TimeBase, Freq);

/*------------------------------------------------------------------------------
BUCLE PRINCIPAL:
------------------------------------------------------------------------------*/
    while(1)
    {

    }
}
/*------------------------------------------------------------------------------
INTERRUPCIONES:
------------------------------------------------------------------------------*/
/*Interrupcion al vencimiento de cuenta de TIM3 cada 250mseg/4Hz:*/
void TIM3_IRQHandler(void)
{
	/*Conteo de tiempo:*/
	if(Flag5Seg == 1)
		Cont5Seg++;

	/*Bienvenida - Pantalla A:*/
	if (WindowA == 1) {
		/*Imprime mensaje de bienvenida inicial:*/
		PRINT_LCD_2x16(LCD_2X16, 5, 0, "ESTACION");
		PRINT_LCD_2x16(LCD_2X16, 5, 1, "Cube Sat");

		/*Habilita el conteo de 5 segundos:*/
		Flag5Seg = 1;

		if (Cont5Seg == Ticks5Seg) {
			/*Desabilita el flag de la Pantalla A y de conteo de 5 segundos:*/
			WindowA  = 0;
			Flag5Seg = 0;
			/*Se habilita la siguiente Pantalla B:*/
			WindowB  = 1;
		}
	}
	/*Inicio - Pantalla B:*/
	else if (WindowB == 1) {
		/*Imprime mensaje inicial:*/
		PRINT_LCD_2x16(LCD_2X16, 3, 0, "VER  MENU:#");
		PRINT_LCD_2x16(LCD_2X16, 3, 1, "CODIGO:");

		/*Se habilita la opcion para que se ingrese alguno de los codigos:*/
		GPIOSetBits(R1_Port, R1);
		GPIOSetBits(R2_Port, R2);
		GPIOSetBits(R3_Port, R3);

		/*Se habilita la opcion para que se presione #:*/
		GPIOSetBits(R4_Port, R4);
	}
	/*Menu principal - Pantalla C:*/
	else if (WindowC == 1) {
		/*Se muestran las opciones del menu:*/
		PRINT_LCD_2x16(LCD_2X16, 0, 0, "1 RECIBIR DATOS");
		PRINT_LCD_2x16(LCD_2X16, 0, 1, "2 DATOS -> SD");
	}
	/*Recibir Datos - Pantalla C1:*/
	else if (WindowC1 == 1) {
		/*Se muestra el mensaje:*/
		PRINT_LCD_2x16(LCD_2X16, 0, 0, "  TEMPERATURA");
		PRINT_LCD_2x16(LCD_2X16,11, 1, "^C");

		/*Se esperan 5 segundos:*/
		Flag5Seg = 1;

		if (Cont5Seg == Ticks5Seg) {
			/*Desabilita el flag de la Pantalla C1 y de conteo de 5 segundos:*/
			WindowC1 = 0;
			Flag5Seg = 0;
			/*Se habilita la siguiente Pantalla B:*/
			WindowB = 1;
		}
	}
	/*Datos SD - Pantalla C2:*/
	else if (WindowC2 == 1) {
		/*Se muestra el mensaje:*/
		PRINT_LCD_2x16(LCD_2X16, 0, 0, " T:");
		PRINT_LCD_2x16(LCD_2X16,10, 1, "^C");
		PRINT_LCD_2x16(LCD_2X16, 0, 1, " GUARDAR?");
		PRINT_LCD_2x16(LCD_2X16,12, 0, "SI:1");
		PRINT_LCD_2x16(LCD_2X16,12, 1, "NO:2");

		/*Se habilita la opcion para que se pulse 1 o 2:*/
		GPIOSetBits(R1_Port, R1);
	}
	/*Confirmacion Datos SD - Pantalla C21:*/
	else if (WindowC21 == 1) {
		/*Se muestra el mensaje:*/
		PRINT_LCD_2x16(LCD_2X16, 0, 0, " DATOS GUARDADOS");
		PRINT_LCD_2x16(LCD_2X16, 4, 1, "CON EXITO");

		/*Se esperan 5 segundos:*/
		Flag5Seg = 1;

		if (Cont5Seg == Ticks5Seg) {
			/*Desabilita el flag de la Pantalla C1 y de conteo de 5 segundos:*/
			WindowC21 = 0;
			Flag5Seg = 0;
			/*Se habilita la siguiente Pantalla B:*/
			WindowB = 1;
		}
	}
	/*Mostrar SD - Pantalla C3:*/
	else if (WindowC3 == 1) {
		/*Se muestra el mensaje:*/
		PRINT_LCD_2x16(LCD_2X16, 0, 0, "T1:");
		PRINT_LCD_2x16(LCD_2X16, 9, 0, "T2:");
		PRINT_LCD_2x16(LCD_2X16, 0, 1, "T3:");
		PRINT_LCD_2x16(LCD_2X16, 9, 1, "ESC:*");

		/*Se habilita la opcion para que se pulse *:*/
		GPIOSetBits(R4_Port, R4);
	}
	/*Borrar SD - Pantalla C4:*/
	else if (WindowC4 == 1) {
		/*Se muestra el mensaje:*/
		PRINT_LCD_2x16(LCD_2X16, 2, 0, "DESEA");
		PRINT_LCD_2x16(LCD_2X16, 0, 1, "CONTINUAR?");
		PRINT_LCD_2x16(LCD_2X16, 12, 0, "SI:1");
		PRINT_LCD_2x16(LCD_2X16, 12, 1, "NO:2");

		/*Se habilita la opcion para que se pulse 1 o 2:*/
		GPIOSetBits(R1_Port, R1);
	}
	/*Confirmacion Borrar SD - Pantalla C41:*/
	else if (WindowC41 == 1) {
		/*Se muestra el mensaje:*/
		PRINT_LCD_2x16(LCD_2X16, 0, 0, " DATOS BORRADOS");
		PRINT_LCD_2x16(LCD_2X16, 4, 1, "CON EXITO");

		/*Se esperan 5 segundos:*/
		Flag5Seg = 1;

		if (Cont5Seg == Ticks5Seg) {
			/*Desabilita el flag de la Pantalla C41 y de conteo de 5 segundos:*/
			WindowC41 = 0;
			Flag5Seg = 0;
			/*Se habilita la siguiente Pantalla B:*/
			WindowB = 1;
		}
	}
	/*Desplegar Antena - Pantalla C5:*/
	else if (WindowC5 == 1) {
		/*Se muestra el mensaje:*/
		PRINT_LCD_2x16(LCD_2X16, 0, 0, "ANT. DESPLEGADA");
		PRINT_LCD_2x16(LCD_2X16, 4, 1, "CON EXITO");

		/*Se esperan 5 segundos:*/
		Flag5Seg = 1;

		if (Cont5Seg == Ticks5Seg) {
			/*Desabilita el flag de la Pantalla C5 y de conteo de 5 segundos:*/
			WindowC5 = 0;
			Flag5Seg = 0;
			/*Se habilita la siguiente Pantalla B:*/
			WindowB = 1;
		}
	}
	/*Retraer Antena - Pantalla C6:*/
	else if (WindowC6 == 1) {
		/*Se muestra el mensaje:*/
		PRINT_LCD_2x16(LCD_2X16, 0, 0, "ANTENA RETRAIDA");
		PRINT_LCD_2x16(LCD_2X16, 4, 1, "CON EXITO");

		/*Se esperan 5 segundos:*/
		Flag5Seg = 1;

		if (Cont5Seg == Ticks5Seg) {
			/*Desabilita el flag de la Pantalla C6 y de conteo de 5 segundos:*/
			WindowC6 = 0;
			Flag5Seg = 0;
			/*Se habilita la siguiente Pantalla B:*/
			WindowB = 1;
		}
	}
	else
		WindowA = 1;
}

/*Interrupcion al pulso por PD0-C1:*/
void EXTI0_IRQHandler(void) {
	/*Si la interrupcion fue por linea 0 (PD0 - C1):*/
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
	/*Si ademas de estar C1 en 1 tambien esta R1 en 1, entonces el switch pulsado es S1:*/

		/*Caso: Pantalla B y se pulsa 1:*/
		if (WindowB == 1 && GPIO_ReadInputDataBit(R1_Port, R1)) {
			/*Se habilita la Pantalla C1*/
			WindowC1 = 1;
			WindowB = 0;
			/*Se deshabilita la opcion para pulsar 1:*/
			GPIOResetBits(R1_Port, R1);
		}
		/*Caso: Pantalla C2 y se pulsa 1:*/
		else if (WindowC2 == 1 && GPIO_ReadInputDataBit(R1_Port, R1)) {
			/*Se habilita la Pantalla C21*/
			WindowC21 = 1;
			WindowC2 = 0;
			/*Se deshabilita la opcion para pulsar 1:*/
			GPIOResetBits(R1_Port, R1);
		}
		/*Caso: Pantalla C4 y se pulsa 1:*/
		else if (WindowC4 == 1 && GPIO_ReadInputDataBit(R1_Port, R1)) {
			/*Se habilita la Pantalla C41*/
			WindowC41 = 1;
			WindowC4 = 0;
			/*Se deshabilita la opcion para pulsar 1:*/
			GPIOResetBits(R1_Port, R1);
		}

	/*Si ademas de estar C1 en 1 tambien esta R2 en 1, entonces el switch pulsado es S4:*/

		/*Caso: Pantalla B y se pulsa 4:*/
		else if (WindowB == 1 && GPIO_ReadInputDataBit(R2_Port, R2)) {
			/*Se habilita la Pantalla C4*/
			WindowC4 = 1;
			WindowB = 0;
			/*Se deshabilita la opcion para pulsar 4:*/
			GPIOResetBits(R2_Port, R2);
		}

	/*Si ademas de estar C1 en 1 tambien esta R3 en 1, entonces el switch pulsado es S7:*/

	/*Si ademas de estar C1 en 1 tambien esta R4 en 1, entonces el switch pulsado es Sast:*/

		/*Caso: Pantalla C3 y se pulsa *:*/
		else if (WindowC3 == 1 && GPIO_ReadInputDataBit(R4_Port, R4)) {
			/*Se habilita la Pantalla B*/
			WindowC3 = 0;
			WindowB = 1;
			/*Se deshabilita la opcion para pulsar *:*/
			GPIOResetBits(R4_Port, R4);
		}

		/*Clear the EXTI line 0 pending bit:*/
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

/*Interrupcion al pulso por PD1-C2:*/
void EXTI1_IRQHandler(void) {
	/*Si la interrupcion fue por linea 1 (PD1 - C2):*/
	if (EXTI_GetITStatus(EXTI_Line1) != RESET) {
	/*Si ademas de estar C2 en 1 tambien esta R1 en 1, entonces el switch pulsado es S2:*/

		/*Caso: Pantalla B y se pulsa 2:*/
		if (WindowB == 1 && GPIO_ReadInputDataBit(R1_Port, R1)) {
			/*Se habilita la Pantalla C2*/
			WindowC2 = 1;
			WindowB = 0;
			/*Se deshabilita la opcion para pulsar 2:*/
			GPIOResetBits(R1_Port, R1);
		}
		/*Caso: Pantalla C2 y se pulsa 2:*/
		else if (WindowC2 == 1 && GPIO_ReadInputDataBit(R1_Port, R1)) {
			/*Se habilita la Pantalla B*/
			WindowB = 1;
			WindowC2 = 0;
			/*Se deshabilita la opcion para pulsar 2:*/
			GPIOResetBits(R1_Port, R1);
		}
		/*Caso: Pantalla C4 y se pulsa 2:*/
		else if (WindowC4 == 1 && GPIO_ReadInputDataBit(R1_Port, R1)) {
			/*Se habilita la Pantalla B*/
			WindowB = 1;
			WindowC4 = 0;
			/*Se deshabilita la opcion para pulsar 2:*/
			GPIOResetBits(R1_Port, R1);
		}

	/*Si ademas de estar C2 en 1 tambien esta R2 en 1, entonces el switch pulsado es S5:*/

		/*Caso: Pantalla B y se pulsa 5:*/
		else if (WindowB == 1 && GPIO_ReadInputDataBit(R2_Port, R2)) {
			/*Se habilita la Pantalla C5*/
			WindowC5 = 1;
			WindowB = 0;
			/*Se deshabilita la opcion para pulsar 5:*/
			GPIOResetBits(R2_Port, R2);
		}

	/*Si ademas de estar C2 en 1 tambien esta R3 en 1, entonces el switch pulsado es S8:*/

	/*Si ademas de estar C2 en 1 tambien esta R4 en 1, entonces el switch pulsado es S0:*/

		/*Clear the EXTI line 1 pending bit:*/
		EXTI_ClearITPendingBit(EXTI_Line1);
	}

}

/*Interrupcion al pulso por PE2-C3:*/
void EXTI2_IRQHandler(void) {
	/*Si la interrupcion fue por linea 2 (PD2 - C3):*/
	if (EXTI_GetITStatus(EXTI_Line2) != RESET) {
	/*Si ademas de estar C3 en 1 tambien esta R1 en 1, entonces el switch pulsado es S3:*/

		/*Caso: Pantalla B y se pulsa 3:*/
		if (WindowB == 1 && GPIO_ReadInputDataBit(R1_Port, R1)) {
			/*Se habilita la Pantalla C3*/
			WindowC3 = 1;
			WindowB = 0;
			/*Se deshabilita la opcion para pulsar 3:*/
			GPIOResetBits(R1_Port, R1);
		}

	/*Si ademas de estar C3 en 1 tambien esta R2 en 1, entonces el switch pulsado es S6:*/

		/*Caso: Pantalla B y se pulsa 6:*/
		else if (WindowB == 1 && GPIO_ReadInputDataBit(R2_Port, R2)) {
			/*Se habilita la Pantalla C6*/
			WindowC6 = 1;
			WindowB = 0;
			/*Se deshabilita la opcion para pulsar 6:*/
			GPIOResetBits(R2_Port, R2);
		}

	/*Si ademas de estar C3 en 1 tambien esta R3 en 1, entonces el switch pulsado es S9:*/

	/*Si ademas de estar C3 en 1 tambien esta R4 en 1, entonces el switch pulsado es Snum:*/

		/*Caso: Pantalla B y se pulsa #:*/
		else if (WindowB == 1 && GPIO_ReadInputDataBit(R4_Port, R4)) {
			/*Se habilita la Pantalla C*/
			WindowC = 1;
			WindowB = 0;
			/*Se deshabilita la opcion para pulsar #:*/
			GPIOResetBits(R4_Port, R4);
		}

		/*Clear the EXTI line 2 pending bit:*/
		EXTI_ClearITPendingBit(EXTI_Line2);
	}

}

/*Interrupcion al pulso por PE3-C4:*/
void EXTI3_IRQHandler(void) {
	/*Si la interrupcion fue por linea 3 (PE3 - C4):*/
	if (EXTI_GetITStatus(EXTI_Line3) != RESET) {
	/*Si ademas de estar C4 en 1 tambien esta R1 en 1, entonces el switch pulsado es SA:*/

	/*Si ademas de estar C4 en 1 tambien esta R2 en 1, entonces el switch pulsado es SB:*/

	/*Si ademas de estar C4 en 1 tambien esta R3 en 1, entonces el switch pulsado es SC:*/

	/*Si ademas de estar C4 en 1 tambien esta R4 en 1, entonces el switch pulsado es SD:*/

		/*Clear the EXTI line 3 pending bit:*/
		EXTI_ClearITPendingBit(EXTI_Line3);
	}

}
