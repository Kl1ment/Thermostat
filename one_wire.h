#ifndef ONE_WIRE_H_
#define ONE_WIRE_H_

#ifndef ONE_WIRE_DDR
#define ONE_WIRE_DDR DDRC
#endif

#ifndef ONE_WIRE_PIN
#define ONE_WIRE_PIN PINC
#endif

#ifndef DQ
#define DQ PINC0
#endif

#define SET_BIT_0 ONE_WIRE_DDR |= (1 << DQ);
#define SET_BIT_1 ONE_WIRE_DDR &= ~(1 << DQ);

#include <avr/io.h>
#include <util/delay.h>

void reset() {
	SET_BIT_0;
	_delay_us(480);
	SET_BIT_1;
}

int check_present() {
	reset();
	_delay_us(80);
	char presence = ONE_WIRE_PIN & (1 << DQ);
	_delay_us(160);
	return !presence;
}

void send_bite(unsigned char b) {
	for (unsigned char i = 0; i < 8; i++) {
		SET_BIT_0;
		_delay_us(5);
		ONE_WIRE_DDR &= ~(b & 0x01) << DQ;
		b >>= 1;
		_delay_us(60);
		SET_BIT_1;
		_delay_us(1);
	}
}

unsigned char read_byte() {
	char data = 0x00;
	for (int i = 0; i < 8; i++) {
		SET_BIT_0;
		_delay_us(5);
		SET_BIT_1;
		_delay_us(15);
		data |= ((ONE_WIRE_PIN & (1 << DQ)) >> DQ) << i;
		_delay_us(45);
	}
	
	return data;
}
#endif