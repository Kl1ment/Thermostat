#ifndef INFO_STAGE_H_
#define INFO_STAGE_H_

float display_temp = 0;
unsigned char enabled = 0;

void check_button_info() {
	if (PINB_low(SWITCH_MODE, &switch_mode_last)) {
		setup_settings_stage(1);
	}
}

void print_info_temp() {
	display_temp = temp;
	set_position(6, 0);
	LCD_print_float(display_temp, 10);
	LCD_print(" ");
}

void print_run() {
	enabled = ENABLED;
	set_position(12, 0);
	if (enabled) {
		LCD_print("RUN");
		} else {
		LCD_print("   ");
	}
}

void show_info() {
	clear_display();
	LCD_print("Temp: ");
	print_info_temp();
	set_position(0, 1);
	LCD_print(settings.is_heat ? "Heat" : "Cool");
	print_run();
}

void loop_info_stage() {
	check_button_info();
	
	if (temp != display_temp) {
		print_info_temp();
	}
	
	if (enabled != ENABLED) {
		print_run();
	}
}

void setup_info_stage() {
	show_info();
	loop_stage = loop_info_stage;
}

#endif