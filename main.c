#include <mcs51/8051.h>

#define FOSC 11059200
#define BAUD 9600

void uart_init(void) {
	SCON = 0x50;	/* 8-vit variable baud UART */
	TMOD = 0x20;	/* Timer1 in 8 bit auto reload mode */
	TH1 = TL1 = -(FOSC/12/32/BAUD);	/* auto-reload value */
	TR1 = 1;		/* Timer1 start to run */
	ES = 1;			/* Enable UART interrupt */
}

void uart_tx(char c) {
	SBUF = c;
	while(!TI);
	TI = 0;
}

char uart_rx(void) {
	while(!RI);
	RI = 0;
	return SBUF;
}

void puts(char *s) {
	while (*s != '\0') {
		uart_tx(*s);
		s++;
	}
}

void main(void) {
	uart_init();
	puts("Hello World\n\r");
	
	char c;
	while(1) {
		c = uart_rx();
		uart_tx(c);
		uart_tx(c);
	}
}
