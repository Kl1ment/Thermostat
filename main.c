#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd_display.h"
#include "DS18B20.h"
#include "Common/main_common.h"
#include "Stages/stage_machine.h"

unsigned char should_get_temp = 0;

void port_init() {
	DDRD = 0x00; // Кнопки
	PORTD = 0x0F;
	
	DDRD |= (1 << DDRD7); // Управление реле
	PORTD |= (1 << PORTD7);
}

void timer_init() {
	// ------|---- Делитель 1024 ----|------ CTC ----
	TCCR1B = (1 << CS12) | (1 << CS10) | (1 << WGM12);
	TIMSK |= (1 << OCIE1A); // Прерывание по совпадению
	
	OCR1AH = 0b00000011;
	OCR1AL = 0b11010001;
}

ISR (TIMER1_COMPA_vect) {
	should_get_temp = 1;
}

int main(void)
{
	timer_init();
	port_init();
	LCD_init();
	setup_info_stage();
	
	sei();
		
	switch_mode_last = (PIND & SWITCH_MODE);
	ok_last = (PIND & OK_BUTTON);
	incremet_last = (PIND & INCREMENT);
	decrement_last = (PIND & DECREMENT);
	
    while(1)
    {
		if (should_get_temp) {
			temp = get_temperature();
			should_get_temp = 0;
		}
		
		loop_stage();
		
		if (temp <= settings.target_temp - settings.deviation) {
			if (settings.enabled && settings.is_heat && !ENABLED) {
				TERN_ON;
			} else if (!settings.is_heat && ENABLED) {
				TERN_OFF;
			}
		} else if (temp >= settings.target_temp + settings.deviation) {
			if (settings.is_heat && ENABLED) {
				TERN_OFF;
			} else if (settings.enabled && !settings.is_heat && !ENABLED) {
				TERN_ON;
			}
		}
    }
}