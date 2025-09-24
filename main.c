#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd_display.h"
#include "DS18B20.h"
#include "Common/main_common.h"
#include "Stages/stage_machine.h"


void port_init() {
	DDRB = 0x00;
	PORTB = 0x0F;
	
	DDRC |= (1 << DDRC2);
	PORTC &= ~(1 << PORTC2);
}

void timer_init() {
	// ------|---- Делитель 1024 ----|------ CTC ----
	TCCR1B = (1 << CS12) | (1 << CS10) | (1 << WGM12);
	TIMSK |= (1 << OCIE1A); // Прерывание по совпадению
	
	OCR1AH = 0b00000011;
	OCR1AL = 0b11010001;
}

ISR (TIMER1_COMPA_vect) {
	temp = get_temperature();
}

int main(void)
{
	timer_init();
	port_init();
	LCD_init();
	setup_info_stage();
	
	sei();
		
	switch_mode_last = (PINB & SWITCH_MODE);
	ok_last = (PINB & OK_BUTTON);
	incremet_last = (PINB & INCREMENT);
	decrement_last = (PINB & DECREMENT);
	
    while(1)
    {
		loop_stage();
			
		if (temp <= settings.target_temp - settings.deviation) {
			if (settings.is_heat && !ENABLED) {
				TERN_ON;
			} else if (!settings.is_heat && ENABLED) {
				TERN_OFF;
			}
		} else if (temp >= settings.target_temp + settings.deviation) {
			if (settings.is_heat && ENABLED) {
				TERN_OFF;
			} else if (!settings.is_heat && !ENABLED) {
				TERN_ON;
			}
		}
    }
}