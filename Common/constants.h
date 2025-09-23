
#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// BUTTONS
#define SWITCH_MODE (1 << PORTB0)
#define OK_BUTTON (1 << PORTB1)
#define INCREMENT (1 << PORTB2)
#define DECREMENT (1 << PORTB3)

// MODES
#define MODE_COUNT 2
#define INFO_MODE 0
#define SETTINGS_MODE 1

// SETTINGS
#define SETTINGS_COUNT 3
#define TARGET_TEMP 0
#define DEVIATION 1
#define HEAT_COOL 2

// MANAGEMET
#define TERN_ON PORTC |= (1 << PORTC2)
#define TERN_OFF PORTC &= ~(1 << PORTC2)
#define ENABLED (PORTC & (1 << PORTC2))

#endif