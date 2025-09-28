#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

Vector2 get_position(char pos) {
	Vector2 res = {
		x: ((pos >> 1) & 0x01) * 8,
		y: pos & 0x01
	};
	return res;
}

int PIND_low(char pin, char* last_value) {
	if ((PIND & pin) != *last_value) {
		*last_value = (PIND & pin);
		if (!(PIND & pin)) {
			return 1;
		}
	}
	return 0;
}



#endif