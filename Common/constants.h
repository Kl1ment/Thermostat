
#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// BUTTONS
#define SWITCH_MODE (1 << PORTD0)
#define OK_BUTTON (1 << PORTD1)
#define INCREMENT (1 << PORTD2)
#define DECREMENT (1 << PORTD3)

// SETTINGS
#define SETTINGS_COUNT 3
#define TARGET_TEMP 0
#define DEVIATION 1
#define HEAT_COOL 2

// MANAGEMET
#define TERN_ON PORTD &= ~(1 << PORTD7)
#define TERN_OFF PORTD |= (1 << PORTD7)
#define ENABLED !(PORTD & (1 << PORTD7))

#endif