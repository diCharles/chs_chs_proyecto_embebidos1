/*
 * SystemControl.c
 *
 *  Created on: 12/04/2019
 *      Author: Charles
 */


#include "SystemControl.h"

/********************************* GLOBAL VARIABLES *******************************************/
/**This is mail box to received the information from the serial port*/
extern uart_mail_box_t g_mail_box_uart_0;

/* this array has the corresponding function by index that the user can select from menu */
/* 1)   2)   3)  4)   5)   6)  7) */
void (* g_menu_options[MENU_OPTIONS])(void ) = { 0,0,0,0,0,0,0};





/**********************************************************************************/



void system_init()
{
	/* init uart0 for communication with terminal*/
	UART_init_terminal_with_k20(21000000, 115200);
	UART_init_UART4( 21000000, 115200);

}
uint8_t system_read_terminal_and_write_buffer( uint8_t * rx_buffer )
{
	static uint8_t rx_bufer_index = 0;
	/* if a  key has been pressed the flag will be set*/
	if(g_mail_box_uart_0.flag)
	{
		/*if the key was ENTER , jump a line, and write string end*/
		if(ENTER == g_mail_box_uart_0.mailBox )
		{
			UART_put_string(UART_0, "( ENTER )\n ") ;
			UART_put_char (UART_0, ENTER) ;
			rx_buffer[rx_bufer_index] = NULL_CHAR ;/* end of string into buffer . Writing null character*/
			rx_bufer_index = 0 ;
			g_mail_box_uart_0.flag = 0;
			return ( STRING_INGRESED ) ;
		}
		/* else if the key is  escape, the user wants to quit*/
		else if ( ESCAPE == g_mail_box_uart_0.mailBox)
		{
			UART_put_string(UART_0, "( ESC ) \n");
			UART_put_char (UART_0, ENTER);
			rx_bufer_index = 0 ;/* clearing buffer and his indexer*/
			system_clear_rx_buffer( rx_buffer ) ;
			system_print_menu();/* */
		}
		/* else the key is stored into rx buffer*/
		else
		{
			UART_put_char (UART_0, g_mail_box_uart_0.mailBox);
			rx_buffer[rx_bufer_index] = g_mail_box_uart_0.mailBox;/* write into buffer*/
			rx_bufer_index++;/* enables to  store a new character on buffer*/
			/* if the buffer has been filled*/
			if (RX_BUFFER_LENGTH <= rx_bufer_index )
			{
				/* clear buffer and reset his index*/
				rx_bufer_index = 0;
				system_clear_rx_buffer( rx_buffer ) ;
			}
		}
		g_mail_box_uart_0.flag = 0;/**/

	}
	return  (NO_STRING_INGRESED ) ;
}
void system_print_menu( void )
{
	/**The following sentences send strings to PC using the UART_put_string function. Also, the string
	 * is coded with terminal code*/

	/*VT100 command for clearing the screen*/
	UART_put_string(UART_0,"\033[2J");
	/** VT100 command for text in green and background in BLACK*/
	UART_put_string(UART_0,"\033[0;32;40m");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_put_string(UART_0,"\033[0;0H");
	UART_put_string(UART_0, "1) Establecer Hora\r");
	UART_put_string(UART_0,"\n");
	UART_put_string(UART_0, "2) Establecer minutos\r");
	UART_put_string(UART_0,"\n");
	UART_put_string(UART_0, "3) Leer hora\r");
	UART_put_string(UART_0,"\n");
	UART_put_string(UART_0, "4) Leer fecha\r");
	UART_put_string(UART_0,"\n");
	UART_put_string(UART_0, "5) Escribir mensaje en memoria I2C\r");
	UART_put_string(UART_0,"\n");
	UART_put_string(UART_0, "6) Mostrar hora en matriz de leds\r");
	UART_put_string(UART_0,"\n");
	UART_put_string(UART_0, "7) Mostrar mensaje en matriz de leds\r");
	UART_put_string(UART_0,"\n");

	UART_put_string(UART_4,"\033[2J");
	/** VT100 command for text in green and background in BLACK*/
	UART_put_string(UART_4,"\033[0;32;40m");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_put_string(UART_4,"\033[0;0H");
	UART_put_string(UART_4, "1) Establecer Hora\r");
	UART_put_string(UART_4,"\n");
	UART_put_string(UART_4, "2) Establecer minutos\r");
	UART_put_string(UART_4,"\n");
	UART_put_string(UART_4, "3) Leer hora\r");
	UART_put_string(UART_4,"\n");
	UART_put_string(UART_4, "4) Leer fecha\r");
	UART_put_string(UART_4,"\n");
	UART_put_string(UART_4, "5) Escribir mensaje en memoria I2C\r");
	UART_put_string(UART_4,"\n");
	UART_put_string(UART_4, "6) Mostrar hora en matriz de leds\r");
	UART_put_string(UART_4,"\n");
	UART_put_string(UART_4, "7) Mostrar mensaje en matriz de leds\r");
	UART_put_string(UART_4,"\n");
}

void system_clear_rx_buffer( uint8_t * rx_buffer )
{
	uint8_t iterator ;
	for(iterator = 0 ; ( RX_BUFFER_LENGTH -1 ) > iterator ;  iterator ++ )
	{
		rx_buffer[iterator] = 0;
	}
}

uint8_t system_decode_string_on_buffer( uint8_t * rx_buffer)
{
	uint8_t rx_buffer_had_a_string= FALSE ;
	uint8_t index = 0 ;
	while( (  NULL_CHAR != rx_buffer[index] ) && (  (RX_BUFFER_LENGTH-1)  > index))
	{
		index++;
	}
	if( NULL_CHAR == rx_buffer[index])
	{
		UART_put_string(UART_0,(char *) rx_buffer);
		UART_put_string(UART_0,"\n");
		UART_put_char (UART_0, ENTER);
		UART_put_string(UART_4,(char *) rx_buffer);
		UART_put_string(UART_4,"\n");
		UART_put_char (UART_4, ENTER);
	}
	return 0;
}
void system_exe_current_app(  ){}
