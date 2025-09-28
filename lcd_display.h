#ifndef LCD_DISPLAY_H_
#define LCD_DISPLAY_H_

#include <avr/io.h>
#include <util/delay.h>

#ifndef LCD_INTERFACE
#define LCD_INTERFACE 4
#endif

#ifndef LCD_PORT
#define LCD_PORT PORTC
#endif

#ifndef LCD_DDR
#define LCD_DDR DDRC
#endif

#ifndef LCD_CONTROL_PORT
#define LCD_CONTROL_PORT PORTC
#endif

#ifndef LCD_CONTROL_DDR
#define LCD_CONTROL_DDR DDRC
#endif

#ifndef RS
#define RS PORTC0
#endif

#ifndef E
#define E PORTC1
#endif

void lcd_port_init() {
	#if LCD_INTERFACE == 4
	LCD_DDR |= 0b00111100;
	LCD_PORT &= 0b11000011;
	#else
	LCD_DDR |= 0b11111111;
	LCD_PORT &= 0b00000000;
	#endif
	
	LCD_CONTROL_DDR |= (1 << E) | (1 << RS);
	LCD_CONTROL_PORT &= ~((1 << E) | (1 << RS));
}

void push_byte() {
	LCD_CONTROL_PORT |= (1 << E);
	_delay_us(50);
	LCD_CONTROL_PORT &= ~(1 << E);
	_delay_us(50);
}

void send_half_byte(unsigned char hb) {
	hb <<= 2;
	LCD_PORT &= 0b11000011;
	LCD_PORT |= hb;
	push_byte();
}

void send_full_byte(unsigned char b) {
	LCD_PORT = b;
	push_byte();
}

void send_byte(unsigned char b, unsigned char mode) {
	if (mode == 0) {
		LCD_CONTROL_PORT &= ~(1 << RS); // Команда
		} else {
		LCD_CONTROL_PORT |= (1 << RS); // Данные
	}
	#if LCD_INTERFACE == 4
	unsigned char hb = b >> 4;
	send_half_byte(hb);
	send_half_byte(b);
	#else
	send_full_byte(b);
	#endif	
}

void send_command(unsigned char command) {
	send_byte(command, 0);
}

void send_data(unsigned char data) {
	send_byte(data, 1);
}

void LCD_init() {
	lcd_port_init();
	_delay_ms(20);
	send_half_byte(0b00000011);
	_delay_ms(5);
	send_half_byte(0b00000011);
	_delay_us(120);
	send_half_byte(0b00000011);
	_delay_ms(1);
	
	#if LCD_INTERFACE == 4
	send_half_byte(0b00000010); // Установка 4 битного интерфейса
	_delay_ms(1);
	send_command(0b00101000);
	_delay_ms(1);
	#else
	send_command(0b00111000);
	_delay_ms(1);
	#endif
	send_command(0b00001100);
	_delay_ms(1);
	send_command(0b00000110);
	_delay_ms(1);
}

void LCD_print(const char str[]) {
	int i = 0;
	while (str[i]) {
		send_data(str[i]);
		i++;
	}
}

int int_len(int n) {
	char count = 0;
	if (n < 0) {
		count++;
		n = -n;
	}
	
	while (n > 0) {
		count++;
		n /= 10;
	}
	return count;
}

void int_to_str(char *str, int n) {
	char is_negative = n < 0;
	if (is_negative) {
		n = -n;
	}
	
	int i = 0;
	do {
		str[i++] = n % 10 + '0';
		n /= 10;
	} while (n > 0);
	
	if (is_negative) {
		str[i++] = '-';
	}
	
	str[i] = '\0';
	for (int j = 0; j < i / 2; j++) {
		char temp = str[j];
		str[j] = str[i - j - 1];
		str[i - j - 1] = temp;
	}
}

void LCD_print_int(int number) {
	char str[int_len(number) + 1];
	int_to_str(str, number);
	LCD_print(str);
}

void LCD_print_float(float number, int accurancy) {
	LCD_print_int(number);
	send_data('.');
	int float_part = (number - (int)number) * accurancy;
	LCD_print_int(float_part);
}

void clear_display() {
	send_command(1);
	_delay_ms(2);
}

void return_home() {
	send_command((1 << 1));
	_delay_ms(2);
}

// Direction 1 - right
// Direction 0 - left
// Установить режим ввода
void entry_mode_set(int direction) {
	send_command((1 << 2) | (direction << 1));
	_delay_us(50);
}

// Set right direction
// Установить направление вправо
void right_derection() {
	entry_mode_set(1);
}

// Set left direction
// Установить направление влево
void left_derection() {
	entry_mode_set(0);
}

// turn on/off display, cursor, blinking of cursor
// Включить/выключить дисплей, курсор, мигание курсора
void display_control(int display, int cursor, int cursor_blink) {
	send_command((1 << 3) | (display << 2) | (cursor << 1) | (cursor_blink << 0));
	_delay_us(50);
}

// Direction 1 - right
// Direction 0 - left
// Сдвинуть курсор
void cursor_shift(int direction) {
	send_command((1 << 4) | (direction << 2));
	_delay_us(50);
}

// Direction 1 - right
// Direction 0 - left
// Сдвинуть дисплей
void display_shift(int direction) {
	send_command((1 << 4) | (1 << 3) | (direction << 2));
	_delay_us(50);
}

// x - from 0 to 15
// y - from 0 to 1
// Установить положение курсора
void set_position(char x, char y) {
	if (x < 0 || x > 15) return;
	if (y < 0 || y > 1) return;
	
	char pos = (y << 6) | (x);
	send_command((1 << 7) | pos);
	_delay_us(50);
}


#endif