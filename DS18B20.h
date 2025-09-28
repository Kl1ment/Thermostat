#ifndef DS18B20_H_
#define DS18B20_H_

#define ONE_WIRE_DDR DDRB
#define ONE_WIRE_PIN PINB
#define DQ PINB0

#include "one_wire.h"

char rom[8];

void read_rom() {
	check_present();
	send_bite(0x33);
	
	for (int i = 0; i < 8; i++) {
		char data = read_byte();
		rom[i] = data;
	}
}

void match_rom(char* rom) {
	check_present();
	send_bite(0x55);
	for (int i = 0; i < 8; i++) {
		send_bite(rom[i]);
	}
}

void skip_rom() {
	check_present();
	send_bite(0xCC);
}

float get_temperature() {
	skip_rom();
	send_bite(0x44);
	while (!(ONE_WIRE_PIN & (1 << DQ))) {}
	skip_rom();
	send_bite(0xBE);
	unsigned char lb = read_byte();
	unsigned char hb = read_byte();
	float integer = ((hb << 8) | lb) >> 4;
	float float_part = (lb & 0x0F) * 0.0625;
	return integer + float_part;
}
#endif