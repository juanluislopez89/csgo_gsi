// Pin del potenciómetro que gestiona el brillo de las tiras de led
#define NEOPOIXEL_BRIGHTNESS_POTENTIOMETER_PIN A3

// Configuraciones de las tiras de led
// Los pines reservados van del 2 al 11
#define BOMB_NEOPIXEL_STRIP_PIN 2
#define BOMB_NEOPIXEL_STRIP_LED_COUNT 20

#define HEALTH_NEOPIXEL_STRIP_PIN 3
#define HEALTH_NEOPIXEL_STRIP_LED_COUNT 20

#define ARMOR_NEOPIXEL_STRIP_PIN 4
#define ARMOR_NEOPIXEL_STRIP_LED_COUNT 20

#define AMMO_NEOPIXEL_STRIP_PIN 5
#define AMMO_NEOPIXEL_STRIP_LED_COUNT 20

#define ROUND_PERCENT_SCORE_NEOPIXEL_STRIP_PIN 6
#define ROUND_PERCENT_SCORE_NEOPIXEL_STRIP_LED_COUNT 20

#define NFI1_NEOPIXEL_STRIP_PIN 7
#define NFI1_NEOPIXEL_STRIP_LED_COUNT 20

#define NFI2_NEOPIXEL_STRIP_PIN 8
#define NFI2_NEOPIXEL_STRIP_LED_COUNT 20

#define NFI3_NEOPIXEL_STRIP_PIN 9
#define NFI3_NEOPIXEL_STRIP_LED_COUNT 20

#define NFI4_NEOPIXEL_STRIP_PIN 10
#define NFI4_NEOPIXEL_STRIP_LED_COUNT 20

#define NFI5_NEOPIXEL_STRIP_PIN 11
#define NFI5_NEOPIXEL_STRIP_LED_COUNT 20

//Conexión de los pines referentes a los displays TM1637Display
// Los pines reservados van del 12 (CLK) al 29
#define DISPLAY_CLOCK 12

#define BOMB_TIMER_DISPLAY_PIN 13
#define WEAPON_AMMO_CLIP_DISPLAY_PIN 14
#define PLAYER_STATE_HEALTH_DISPLAY_PIN 15
#define PLAYER_STATE_ARMOR_DISPLAY_PIN 16
#define PLAYER_STATE_HELMET_DISPLAY_PIN 17
//Tiene que ser display de 5 digitos
#define PLAYER_STATE_MONEY_DISPLAY_PIN 18    
#define PLAYER_STATE_ROUND_KILLS_DISPLAY_PIN 19
#define PLAYER_STATE_ROUND_KILLHS_DISPLAY_PIN 20
//Tiene que ser display de 5 digitos
#define PLAYER_STATE_EQUIP_VALUE_DISPLAY_PIN 21
#define PLAYER_MATCH_STATS_KILLS_DISPLAY_PIN 22
#define PLAYER_MATCH_STATS_ASSISTS_DISPLAY_PIN 23
#define PLAYER_MATCH_STATS_DEATHS_DISPLAY_PIN 24
#define PLAYER_MATCH_STATS_MVPS_DISPLAY_PIN 25
#define PLAYER_MATCH_STATS_SCORE_DISPLAY_PIN 26
#define MAP_TEAM_CT_SCORE_DISPLAY_PIN 27
#define MAP_TEAM_T_SCORE_DISPLAY_PIN 28
#define MAP_ROUND_DISPLAY_PIN 29
