#ifndef EDIT_SETTINGS_STAGE_H_
#define EDIT_SETTINGS_STAGE_H_

void increment() {
	Vector2 position = get_position(selector_pos);
	set_position(position.x + 3, position.y);
	switch (selector_pos) {
		case TARGET_TEMP:
			settings.target_temp++;
			LCD_print_int(settings.target_temp);
			LCD_print(" ");
			break;
		case DEVIATION:
			if (settings.deviation == 254) break;
			settings.deviation++;
			LCD_print_int(settings.deviation);
			break;
		case HEAT_COOL:
			settings.is_heat = (settings.is_heat + 1 + 2) % 2;
			LCD_print(settings.is_heat ? "Heat" : "Cool");
			break;
	}
}

void decrement() {
	Vector2 position = get_position(selector_pos);
	set_position(position.x + 3, position.y);
	switch (selector_pos) {
		case TARGET_TEMP:
			settings.target_temp--;
			LCD_print_int(settings.target_temp);
			LCD_print(" ");
			break;
		case DEVIATION:
			if (settings.deviation == 1) break;
			settings.deviation--;
			LCD_print_int(settings.deviation);
			LCD_print(" ");
			break;
		case HEAT_COOL:
			settings.is_heat = (settings.is_heat - 1 + 2) % 2;
			LCD_print(settings.is_heat ? "Heat" : "Cool");
			break;
	}
}

void check_button_edit_settings() {
	if (PINB_low(SWITCH_MODE, &switch_mode_last)) {
		setup_info_stage();
		return;
	}

	if (PINB_low(OK_BUTTON, &ok_last)) {
		setup_settings_stage(0);
		return;
	}

	if (PINB_low(INCREMENT, &incremet_last)) {
		increment();
		return;
	}

	if (PINB_low(DECREMENT, &decrement_last)) {
		decrement();
		return;
	}
}

void loop_edit_settings() {
	check_button_edit_settings();
}

void setup_edit_settings_stage() {
	Vector2 position = get_position(selector_pos);
	set_position(position.x, position.y);
	LCD_print("*");
	loop_stage = loop_edit_settings;
}

#endif