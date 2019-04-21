/*
 * SystemControl.h
 *
 *  Created on: 12/04/2019
 *      Author: Charles
 */

#ifndef SYSTEMCONTROL_H_
#define SYSTEMCONTROL_H_
/***************************** INCLUDES ******************************************************/

#include "MK64F12.h" /* include peripheral declarations */
#include "UART.h"/**UART device driver*/

/*****************************  MACROS ******************************************************/
#define STRING_INGRESED 1
#define NO_STRING_INGRESED 0
#define ENTER 0x0DU
#define ESCAPE 0x1B
#define NULL_CHAR 0U
#define MENU_OPTIONS  7U
#define RX_BUFFER_LENGTH 30U

/****************************  GLOBAL VARIABLES **********************************************/



/**************************** FUNCTION PROTOTIPES *******************************************/

/********************************/
/* 	!!!!! brief
 *  this function intializes UART 0 for vitual terminal
 * */
void system_init( void );
/********************************/
/* 	!!!!! brief
 *  this function receives input characters from terminal
 *  returns  1 when  a string was written  and enter was pressed, otherwise zero
  * */
uint8_t system_read_terminal_and_write_buffer(  uint8_t * rx_buffer  );
/********************************/
/* 	!!!!! brief
 *  this function prints menu on pc virtual terminal
 * */
void system_print_menu( void );
/********************************/
/* 	!!!!! brief
 *  this function clears rx buffer and his static and global index
 * */
void system_clear_rx_buffer( uint8_t * rx_buffer );
/********************************/
/* 	!!!!! brief
 *  this function decodes rx buffer and determines
 *  if the string wrotten into terminal by  user has a meaning to the system
 *  (return) : if the string contained into buffer has a meaning, the function
 *  returns a number related to that string
 * */
uint8_t system_decode_string_on_buffer( uint8_t * rx_buffer);
/********************************/
/* 	!!!!! brief
 *  this function executes current  or default application of the system
 *  the current app is determined by system_decode_rx_buffer
 * */
void system_exe_current_app( void );

#endif /* SYSTEMCONTROL_H_ */
