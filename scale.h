#include <18F26K22.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#fuses INTRC_IO,NOWDT,NOPUT,NOBROWNOUT,NOLVP,NOPROTECT
#use delay(clock=16M) // 4xPLL setting 
#use rs232(uart1, baud = 19200, bits=8, PARITY=N, STOP=1, stream = TS02)                // Initialize UART module
#use rs232(uart2, baud = 9600,bits=8, PARITY=N, STOP=1, stream = scale)
#priority  INT_RDA2, INT_RDA, INT_TIMER0

//PORTA
union ra_pin_union{
	struct ra_pin_map{
		boolean IO0			:1;			//RA0		0
		boolean IO1			:1;			//RA1		0
		boolean IO2			:1;			//RA2		0
		boolean IO3			:1;			//RA3		0
		boolean IO4			:1;			//RA4		0
		boolean IO5			:1;			//RA5		0
		boolean noused6		:1;			//			0
		boolean noused7		:1;			//			0
	}RA;
	int8 si8_PORTA;
}PORTA;
union ra_pin_union LATA;
union ra_pin_union TRISA;
#byte PORTA		= 0x0F80
#byte TRISA		= 0x0F92
#byte LATA		= 0x0F89
#byte ANSELA	= 0x0F38

#define def_TRIS_A		0b00001000		// all output
#define def_WPUA		0b00000000		//no pull up

//PORTB
union rb_pin_union{
	struct rb_pin_map{
		boolean IO6			:1;			//RB0		0
		boolean IO7			:1;			//RB1		0
		boolean IO8			:1;			//RB2		0
		boolean IO9			:1;			//RB3		0
		boolean IO10		:1;			//RB4		0
		boolean IO11		:1;			//RB5		0
		boolean noused6		:1;			//RB6		0
		boolean noused7		:1;			//RB7		0
	}RB;
	int8 si8_PORTB;
}PORTB;
union rb_pin_union LATB;
union rb_pin_union TRISB;
#byte PORTB		= 0x0F81
#byte TRISB		= 0x0F93
#byte LATB		= 0x0F8A
#byte ANSELB	= 0x0F39

#define def_TRIS_B		0b00000000		//all output
#define def_WPUB		0b00000000		//no pull up

//PORTC
union rc_pin_union{
	struct rc_pin_map{
		boolean IO12		:1;			//RC0		0
		boolean IO13		:1;			//RC1		0
		boolean IO14		:1;			//RC2		0
		boolean IO15		:1;			//RC3		0
		boolean IO16		:1;			//RC4		0
		boolean IO17		:1;			//RC5		0
		boolean TX1			:1;			//RC6		0
		boolean RX1			:1;			//RC7		0
	}RC;
	int8 si8_PORTC;
}PORTC;
union rc_pin_union LATC;
union rc_pin_union TRISC;
#byte PORTC		= 0x0F82
#byte TRISC		= 0x0F94
#byte LATC		= 0x0F8B
#byte ANSELC	= 0x0F3A

#define	def_TRIS_C		0b00000000		//all output
#define WPUC			0b00000000		//no pull up

//PORTD
union rd_pin_union{
	struct rd_pin_map{
		boolean IO22		:1;			//RD0		0
		boolean IO23		:1;			//RD1		0
		boolean IO24		:1;			//RD2		0
		boolean IO25		:1;			//RD3		0
		boolean IO26		:1;			//RD4		0
		boolean IO27		:1;			//RD5		0
		boolean IO28		:1;			//RD6		0
		boolean IO29		:1;			//RD7		0
	}RD;
	int8 si8_PORTD;
}PORTD;
union rd_pin_union LATD;
union rd_pin_union TRISD;
#byte PORTD		= 0x0F83
#byte TRISD		= 0x0F95
#byte LATD		= 0x0F8C
#byte ANSELD	= 0x0F3B

#define def_TRIS_D		0b00000000		//all output
#define	WPUD			0b00000000		//no pull up

//PORTE
union re_pin_union{
	struct re_pin_map{
		boolean IO18		:1;			//RE0		0
		boolean IO19		:1;			//RE1		0
		boolean IO20		:1;			//RE2		0
		boolean noused3		:1;			//RE3
		boolean noused4		:1;			//RE4
		boolean noused5		:1;			//RE5
		boolean noused6		:1;			//RE6
		boolean noused7		:1;			//RE7
	}RE;
	int8 si8_PORTE;
}PORTE;
union re_pin_union LATE;
union re_pin_union TRISE;
#byte PORTE		= 0x0F84
#byte TRISE		= 0x0F96
#byte LATE		= 0x0F8D
#byte ANSELE	= 0x0F3C

#define def_TRIS_E		0b00000000		//all output
#define WUPE			0b00000000		//no pull up

#define RDY PIN_C1
#define SET3 PIN_A4
#byte OSCCON = 0x0FD3
#byte OSCTUNE = 0x0F9B
#byte OSCCON2 = 0x0FD2

#define C6   237 
#define D6   211 
#define E6   188 
#define F6   177 
#define G6   158 
#define A6   141 
#define B6   125 
#define C7   118
#define D7   105 
#define E7   94 
#define F7   88 
#define G7   78 
#define A7   70 
#define B7   62 