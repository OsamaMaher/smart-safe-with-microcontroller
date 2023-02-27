/*
 * EVM.c
 *
 * Created: 11/22/2022 11:32:16 PM
 * Author : osama
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "Keypad_my.h"
#include "LCD_test.h"
#include "EEPROM_drive.h"
#define PASS_SET 0x20
#define PASSWORD1 0x21
#define PASSWORD2 0x22
#define PASSWORD3 0x23
#define PASSWORD4 0x24
#define TRIES 2

int main(void)
{
    LCD_init();
	Keypad_vinit();
	char flag=0;
	if (EEPROM_Read(PASS_SET) == 0xff)
	{
		LCD_send_string("PASS SET:");
		char i, value;
		for (i=0 ; i<=3 ; i++)
		{
			do 
			{
				value = Keypad_vRead();
			} while (value == 0xff);
			EEPROM_Write(PASSWORD1+i, value);
			LCD_send_char(value);
			_delay_ms(500);
			LCD_move_cursor(1,10+i);
			LCD_send_char('*');
			
		}
		EEPROM_Write(PASS_SET, 0x00);
	}
	char tries=TRIES;
    while (flag==0) 
    {
		char arr[4];
		LCD_clear_screen();
		LCD_send_string("ENTER PASS:");
		char i, value;
		for (i=0 ; i<=3 ; i++)
		{
			do
			{
				value = Keypad_vRead();
			} while (value == 0xff);
			arr[i] = value;
			LCD_send_char(value);
			_delay_ms(500);
			LCD_move_cursor(1,12+i);
			LCD_send_char('*');
			
		}
		if (arr[0]==EEPROM_Read(PASSWORD1) && arr[1]==EEPROM_Read(PASSWORD2) && arr[2]==EEPROM_Read(PASSWORD3) && arr[3]==EEPROM_Read(PASSWORD4))
		{
			LCD_clear_screen();
			LCD_send_string("RIGHT PASS");
			LCD_move_cursor(2,1);
			LCD_send_string("SAFE IS OPENED");
			flag=1;
		} 
		else
		{
			if (tries>0)
			{
				tries--;
				LCD_clear_screen();
				LCD_send_string("WRONG PASSWORD");
				_delay_ms(1000);
				LCD_move_cursor(2,1);
				LCD_send_string("NUM OF TRIE:");
				LCD_send_char(tries+48);
				_delay_ms(1000);
				
			} 
			else
			{
				LCD_clear_screen();
				LCD_send_string("WRONG PASSWORD");
				LCD_move_cursor(2,1);
				LCD_send_string("SAFE CLOSED");
				_delay_ms(1000);
				flag=1;
			}
			
		}
	}
}

