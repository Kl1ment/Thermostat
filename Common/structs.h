#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct Settings {
	char target_temp;
	unsigned char deviation;
	unsigned char is_heat;
} Settings;

typedef struct {
	char x;
	char y;
} Vector2;

#endif