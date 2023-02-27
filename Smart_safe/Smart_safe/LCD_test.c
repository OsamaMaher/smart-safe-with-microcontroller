/*
 * LCD_test.c
 *
 * Created: 11/21/2022 8:46:35 PM
 *  Author: osama
 */ 
#define F_CPU 800000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_test.h"
#include "DIO.h"


void LCD_init(void)
{
	_delay_ms(200);
	#if defined eight_bit
	DIO_SET_PORT_DIR('A',1);
	DIO_SETPINDIR('B',0,1);
	DIO_SETPINDIR('B',1,1);
	DIO_SETPINDIR('B',2,1);
	DIO_WRITE('B',2,0);
	LCD_send_cmd(EIGHT_BIT_MODE);
	_delay_ms(1);
	LCD_send_cmd(CURSOR_ON_DESPLAY_ON);
	_delay_ms(1);
	LCD_send_cmd(CLEAR_SCREEN);
	_delay_ms(10);
	LCD_send_cmd(ENTERY_MODE);
	_delay_ms(1);
	#elif defined four_bit
	DIO_SETPINDIR('A',4,1);
	DIO_SETPINDIR('A',5,1);
	DIO_SETPINDIR('A',6,1);
	DIO_SETPINDIR('A',7,1);
	DIO_SETPINDIR('B',0,1);
	DIO_SETPINDIR('B',1,1);
	DIO_SETPINDIR('B',2,1);
	DIO_WRITE('B',2,0);
	LCD_send_cmd(RETURN_HOME);
	_delay_ms(10);
	LCD_send_cmd(FOUR_BIT_MODE);
	_delay_ms(1);
	LCD_send_cmd(CURSOR_ON_DESPLAY_ON);
	_delay_ms(1);
	LCD_send_cmd(CLEAR_SCREEN);
	_delay_ms(10);
	LCD_send_cmd(ENTERY_MODE);
	_delay_ms(1);
	#endif
}

static void send_falling_edge(void)
{
	DIO_WRITE('B',EN,1);
	_delay_ms(2);
	DIO_WRITE('B',EN,0);
	_delay_ms(2);
}

void LCD_send_cmd(char cmd)
{
	#if defined eight_bit
	DIO_PORT_WRITE('A', cmd);
	DIO_WRITE('B',RS,0);
	send_falling_edge();
	#elif defined four_bit
	DIO_WRITE_HIGHNIBBLE('A', cmd>>4);
	DIO_WRITE('B', RS, 0);
	send_falling_edge();
	DIO_WRITE_HIGHNIBBLE('A', cmd);
	DIO_WRITE('B', RS, 0);
	send_falling_edge();
	#endif
	_delay_ms(1);
}

void LCD_send_char(char data)
{
	#if defined eight_bit
	DIO_PORT_WRITE('A', data);
	DIO_WRITE('B',RS,1);
	send_falling_edge();
	#elif defined four_bit
	DIO_WRITE_HIGHNIBBLE('A', data>>4);
	DIO_WRITE('B', RS, 1);
	send_falling_edge();
	DIO_WRITE_HIGHNIBBLE('A', data);
	DIO_WRITE('B', RS, 1);
	send_falling_edge();
	#endif
}

void LCD_send_string(char* data)
{
	while ((*data) != '\0')
	{
		LCD_send_char(*data);
		data++;
	}
}

void LCD_clear_screen(void)
{
	LCD_send_cmd(CLEAR_SCREEN);
	_delay_ms(10);
}

void LCD_move_cursor(char row, char column)
{
	char data=0;
	if (row>2 || row<1 || column>16 || column<1)
	{
		data=0x80;
	}
	else if (row==1)
	{
		data = 0x80 + column - 1;
	}
	else if (row==2)
	{
		data = 0xC0 + column - 1;
	}
	LCD_send_cmd(data);
	_delay_ms(1);
}