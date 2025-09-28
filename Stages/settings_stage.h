#ifndef SETTINGS_STAGE_H_
#define SETTINGS_STAGE_H_

unsigned char selector_pos = 0;

void move_selector(unsigned char pos) {
	Vector2 position = get_position(selector_pos);
	set_position(position.x, position.y);
	LCD_print(" ");
	selector_pos = pos;
	position = get_position(selector_pos);
	set_position(position.x, position.y);
	LCD_print(">");
}

void selector_inc() {
	int new_pos = (selector_pos + 1 + SETTINGS_COUNT) % SETTINGS_COUNT;
	move_selector(new_pos);
}

void selector_dec() {
	int new_pos = (selector_pos - 1 + SETTINGS_COUNT) % SETTINGS_COUNT;
	move_selector(new_pos);
}

void check_button_settings() {
	if (PIND_low(SWITCH_MODE, &switch_mode_last)) {
		setup_info_stage();
		return;
	}
	
	if (PIND_low(OK_BUTTON, &ok_last)) {
		setup_edit_settings_stage();
		return;
	}
	
	if (PIND_low(INCREMENT, &incremet_last)) {
		selector_inc();
		return;
	}
	
	if (PIND_low(DECREMENT, &decrement_last)) {
		selector_dec();
		return;
	}
}

void show_settings() {
	clear_display();
	LCD_print(" T:");
	LCD_print_int(settings.target_temp);
	set_position(0, 1);
	LCD_print(" D:");
	LCD_print_int(settings.deviation);
	set_position(8, 0);
	LCD_print(" M:");
	LCD_print(settings.is_heat ? "Heat" : "Cool");
	move_selector(0);
}

void loop_settings_stage() {
	check_button_settings();
}

void setup_settings_stage(unsigned char reset) {
	if (reset) {
		show_settings();
	} else {
		Vector2 position = get_position(selector_pos);
		set_position(position.x, position.y);
		LCD_print(">");
	}
	loop_stage = loop_settings_stage;
}

#endif