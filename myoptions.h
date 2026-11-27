#ifndef myoptions_h
#define myoptions_h

/*        ************************************************************************      */
/*        *        This file must be in the root folder of the sketch !!!        *      */
/*        ************************************************************************      */
/*        . . .  CHECK options.h for full options, examples, and overrides   . . .      */

// ESP32-S3-DevKitC-1 N8R8 (8MB Flash 8MB PSRAM)
// Display: Dummy (no physical display)
// Audio Decoder: I2S (PCM I2S Decoder)
//
//             |----------|
//         3V3 |          | G
//         3V3 |          | 43
//          -1 |          | 44
//  BTN_DOWN 4 |          | 1
//    BTN_UP 5 |          | 2
//  BTN_NEXT 6 |          | 42
//           7 |          | 41
//  I2S_LRC 15 |          | 40
// I2S_DOUT 16 |          | 39
//          17 |          | 38
//          18 |          | 37
//           8 |          | 36
//           3 |          | 35
//          46 |          | 0 BTN_PLAY
//           9 |          | 45 MUTE_PIN
//          10 |          | 48 RGB_LED_PIN
//          11 |          | 47
//          12 |          | 21
//          13 |          | 20
// I2S_BCLK 14 |          | 19
//          5V |          | G
//           G |          | G
//             |----------|


/* --- Firmware File --- */
#define FIRMWARE_NAME        "PetRonics Webradio"        /* your ehRadio's name */

/* --- Display --- */
#define DSP_MODEL            DSP_DUMMY

/* --- Audio Decoder --- */
#define I2S_DOUT             16
#define I2S_BCLK             14
#define I2S_LRC              15
#define MUTE_PIN             45        /* pin MUTE is attached to (255 for unused) */

/* --- Inputs --- */
#define BTN_PLAY             0
#define BTN_PLAY_PULLUP      false     /* use internal pullup on button (default true) */
#define BTN_NEXT             6
#define BTN_NEXT_PULLUP      true      /* use internal pullup on button (default true) */
#define BTN_UP               5
#define BTN_UP_PULLUP        true      /* use internal pullup on button (default true) */
#define BTN_DOWN             4
#define BTN_DOWN_PULLUP      true      /* use internal pullup on button (default true) */

/* --- Peripherals and Build Options --- */
#define RGB_LED_PIN          48
#define LED_PIN              2

/* --- User Defaults --- */
#define DSP_LOCALE           "nl_NL"
#define TIMEZONE_NAME        "Europe/Amsterdam"
#define TIMEZONE_POSIX       "CET-1CEST,M3.5.0,M10.5.0/3"
#define ONE_CLICK_SWITCH     true
#define SMART_START          true

/* --- Extra defines --- */
/* RGB1: R=12, G=11, B=13 */
#define DISCRETE_RGB1_R      12
#define DISCRETE_RGB1_G      11
#define DISCRETE_RGB1_B      13
/* RGB2: R=38, G=39, B=40 */
#define DISCRETE_RGB2_R      38
#define DISCRETE_RGB2_G      39
#define DISCRETE_RGB2_B      40
/* RGB3: R=41, G=42, B=44 */
#define DISCRETE_RGB3_R      41
#define DISCRETE_RGB3_G      42
#define DISCRETE_RGB3_B      44
/* RGB4: R=43, G=18, B=1 */
#define DISCRETE_RGB4_R      43
#define DISCRETE_RGB4_G      18
#define DISCRETE_RGB4_B       1

#endif // myoptions_h
