//https://github.com/FastLED/FastLED
#include <FastLED.h>
//https://github.com/avishorp/TM1637
#include <TM1637Display.h>

//Tiras de led Neopixel conectadas
int NEOPIXEL_BRIGHTNESS = 50;
CRGB BOMB_NEOPIXEL_STRIP[BOMB_NEOPIXEL_STRIP_LED_COUNT];
CRGB HEALTH_NEOPIXEL_STRIP[HEALTH_NEOPIXEL_STRIP_LED_COUNT];
CRGB AMMO_NEOPIXEL_STRIP[AMMO_NEOPIXEL_STRIP_LED_COUNT];
CRGB ARMOR_NEOPIXEL_STRIP[ARMOR_NEOPIXEL_STRIP_LED_COUNT];
CRGB ROUND_PERCENT_SCORE_NEOPIXEL_STRIP[ROUND_PERCENT_SCORE_NEOPIXEL_STRIP_LED_COUNT];

//Displays TM1637 conectados
TM1637Display BOMB_TIMER_DISPLAY(DISPLAY_CLOCK, BOMB_TIMER_DISPLAY_PIN); //CLK, DIO
TM1637Display WEAPON_AMMO_CLIP_DISPLAY(DISPLAY_CLOCK, WEAPON_AMMO_CLIP_DISPLAY_PIN); //CLK, DIO
TM1637Display PLAYER_STATE_HEALTH_DISPLAY(DISPLAY_CLOCK, PLAYER_STATE_HEALTH_DISPLAY_PIN); //CLK, DIO
TM1637Display PLAYER_STATE_ARMOR_DISPLAY(DISPLAY_CLOCK, PLAYER_STATE_ARMOR_DISPLAY_PIN); //CLK, DIO
TM1637Display PLAYER_STATE_HELMET_DISPLAY(DISPLAY_CLOCK, PLAYER_STATE_HELMET_DISPLAY_PIN); //CLK, DIO
TM1637Display PLAYER_STATE_MONEY_DISPLAY(DISPLAY_CLOCK, PLAYER_STATE_MONEY_DISPLAY_PIN); //CLK, DIO
TM1637Display PLAYER_STATE_ROUND_KILLS_DISPLAY(DISPLAY_CLOCK, PLAYER_STATE_ROUND_KILLS_DISPLAY_PIN); //CLK, DIO
TM1637Display PLAYER_STATE_ROUND_KILLHS_DISPLAY(DISPLAY_CLOCK, PLAYER_STATE_ROUND_KILLHS_DISPLAY_PIN); //CLK, DIO
TM1637Display PLAYER_STATE_EQUIP_VALUE_DISPLAY(DISPLAY_CLOCK, PLAYER_STATE_EQUIP_VALUE_DISPLAY_PIN); //CLK, DIO
TM1637Display PLAYER_MATCH_STATS_KILLS_DISPLAY(DISPLAY_CLOCK, PLAYER_MATCH_STATS_KILLS_DISPLAY_PIN); //CLK, DIO
TM1637Display PLAYER_MATCH_STATS_ASSISTS_DISPLAY(DISPLAY_CLOCK, PLAYER_MATCH_STATS_ASSISTS_DISPLAY_PIN); //CLK, DIO
TM1637Display PLAYER_MATCH_STATS_DEATHS_DISPLAY(DISPLAY_CLOCK, PLAYER_MATCH_STATS_DEATHS_DISPLAY_PIN); //CLK, DIO
TM1637Display PLAYER_MATCH_STATS_MVPS_DISPLAY(DISPLAY_CLOCK, PLAYER_MATCH_STATS_MVPS_DISPLAY_PIN); //CLK, DIO
TM1637Display PLAYER_MATCH_STATS_SCORE_DISPLAY(DISPLAY_CLOCK, PLAYER_MATCH_STATS_SCORE_DISPLAY_PIN); //CLK, DIO
TM1637Display MAP_TEAM_CT_SCORE_DISPLAY(DISPLAY_CLOCK, MAP_TEAM_CT_SCORE_DISPLAY_PIN); //CLK, DIO
TM1637Display MAP_TEAM_T_SCORE_DISPLAY(DISPLAY_CLOCK, MAP_TEAM_T_SCORE_DISPLAY_PIN); //CLK, DIO
TM1637Display MAP_ROUND_DISPLAY(DISPLAY_CLOCK, MAP_ROUND_DISPLAY_PIN); //CLK, DIO

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

//Globales de estad??sticas de partida del jugador
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
