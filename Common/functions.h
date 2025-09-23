#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

Vector2 get_position(char pos) {
	Vector2 res = {
		x: ((pos >> 1) & 0x01) * 8,
		y: pos & 0x01
	};
	return res;
}

int PINB_low(char pin, char* last_value) {
	if ((PINB & pin) != *last_value) {
		*last_value = (PINB & pin);
		if (!(PINB & pin)) {
			return 1;
		}
	}
	return 0;
}



#endif