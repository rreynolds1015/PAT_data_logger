// Defines
// Cursor positions for date and time
#define DATE_ROW 0
#define DATE_COL 11
#define TIME_ROW 0
#define TIME_COL 0

// Pins
#define BUTTON_ADC      A0
#define BACKLIGHT       10

// Define button pushes
#define RIGHT_10BIT      0
#define UP_10BIT       145
#define DOWN_10BIT     329
#define LEFT_10BIT     505
#define SELECT_10BIT   741
#define HYSTERESIS      15

// Define button values
#define BUTTON_NONE      0
#define RIGHT            1
#define UP               2
#define DOWN             3
#define LEFT             4
#define SELECT           5

// Fancy macros
#define BACKLIGHT_OFF()    digitalWrite( BACKLIGHT, LOW)
#define BACKLIGHT_ON()     digitalWrite( BACKLIGHT, HIGH)
