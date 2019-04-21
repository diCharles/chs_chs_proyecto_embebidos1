/**
	\file
	\brief: IMPLEMENTATION OF " PRACTICA 3 "  FOR MICROCONTROLLERS BASED EMBEDDED SYSTEMS ASIGNATURE

	\authors: Ruben Charles Suárez & Diego Charles Suárez
	\date	05/03/2019
	\to do

 */


#include "SystemControl.h"

extern uart_mail_box_t g_mail_box_uart_4;
int main(void)
{

	system_init();/* initialize UART0 TO 115200 BAUDS*/
	system_print_menu();/* PRINT MENU ON VITUAL TERMINAL*/
	uint8_t rx_buffer[RX_BUFFER_LENGTH] = {0};/* THIS BUFFER WILL STORE VIRTUAL TERMINAL INPUT*/
	uint8_t a_string_and_enter = NO_STRING_INGRESED ;/* THIS FLAG WILL BE SET WHEN A STRING AND THEN ENTER WHERE INTRODUCED ON VIRTUAL TERMINAL*/
	for(;;)
	{
		a_string_and_enter = system_read_terminal_and_write_buffer( rx_buffer );/* READ TERMINAL INPUT*/
		 if( STRING_INGRESED == a_string_and_enter )
		 {
			 system_decode_string_on_buffer(rx_buffer);/* READ STRING WRTIEN ON VIRTUAL TERMINAL*/
			 a_string_and_enter = NO_STRING_INGRESED;
		 }
		 if(g_mail_box_uart_4.flag)
		 {
			 UART_put_char (UART_0, g_mail_box_uart_4.mailBox ) ;
			 g_mail_box_uart_4.flag = 0 ;
		 }

	}
	return 0;
}
