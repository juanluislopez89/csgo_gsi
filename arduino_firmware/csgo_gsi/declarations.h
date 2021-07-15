//https://github.com/FastLED/FastLED
#include <FastLED.h>
//https://github.com/ArduinoGetStarted/output
//#include <ezOutput.h>
//https://github.com/avishorp/TM1637
#include <TM1637Display.h>
//https://github.com/adafruit/Adafruit_NeoPixel
//#include <Adafruit_NeoPixel.h> //Más lenta, no la uso ya


//Displays TM1637 conectados
TM1637Display display1(DSPLAY_CLOCK,DISPLAY1_PIN); //CLK, DIO
TM1637Display display2(DSPLAY_CLOCK,DISPLAY2_PIN); //CLK, DIO
TM1637Display display3(DSPLAY_CLOCK,DISPLAY3_PIN); //CLK, DIO
TM1637Display display4(DSPLAY_CLOCK,DISPLAY4_PIN); //CLK, DIO
TM1637Display display5(DSPLAY_CLOCK,DISPLAY5_PIN); //CLK, DIO
TM1637Display display6(DSPLAY_CLOCK,DISPLAY6_PIN); //CLK, DIO

//Tiras de led Neopixel conectadas
CRGB BOMB_NEOPIXEL_STRIP[BOMB_NEOPIXEL_STRIP_LED_COUNT];
CRGB HEALTH_NEOPIXEL_STRIP[HEALTH_NEOPIXEL_STRIP_LED_COUNT];
CRGB AMMO_NEOPIXEL_STRIP[AMMO_NEOPIXEL_STRIP_LED_COUNT];
//Adafruit_NeoPixel BOMB_NEOPIXEL_STRIP = Adafruit_NeoPixel(BOMB_NEOPIXEL_STRIP_LED_COUNT, 10, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel neopixel2 = Adafruit_NeoPixel(NEOPIXEL2_LED_COUNT, 10, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel neopixel3 = Adafruit_NeoPixel(NEOPIXEL3_LED_COUNT, 10, NEO_GRB + NEO_KHZ800);

//Globales de estado y estadisticas de ronda del jugador
byte player_state_health;
byte player_state_armor;
byte player_state_helmet;
byte player_state_flashed;
byte player_state_smoked;
byte player_state_burning;
byte player_state_money;
byte player_state_round_kills;
byte player_state_round_killhs;
int player_state_equip_value;
int weapon_ammo_clip;
int weapon_ammo_clip_max;

//Globales de estadísticas de partida del jugador
byte player_match_stats_kills;
byte player_match_stats_assists;
byte player_match_stats_deaths;
byte player_match_stats_mvps;
int player_match_stats_score;

//Globales de la ronda
String round_phase;
String round_bomb;
String round_win_team;

//Globales del mapa
byte map_team_ct_score;
byte map_team_t_score;
String map_mode;
String map_name;
byte map_round;

byte bomb_seconds_left;
