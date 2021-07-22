// CONFIG.H -> En este archivo se establecen los pines en los que se conectan los módulos y sus propiedades
#include "config.h"
// DECLARATIONS.H -> En este archivo están las variables globales del sketch
#include "declarations.h"
// CONSTANTS.H -> En este archivo están las constantes del sketch
#include "constants.h"
// Dato curioso #include "config.h" busca en la carpeta del sketch y #include <config.h> busca en la carpeta libraries de Arduino

// Estas variables se emplean para controlar el estado de la bomba.
byte bomb_status;
// Estas variables se emplean para controlar los timings del parpadeo de la bomba activada.
// El parpadeo consta de 2 timings, el que separa los parpadeos y el que separa el encendido y apagado en un parpadeo
unsigned long bomb_start_millis;             //marca temporal de recepcion de inicio de bomba
unsigned long bomb_end_millis;               //marca temporal de finalización de bomba

unsigned long bomb_last_beep = 0;           //marca temporal de la ultima vez que se encendió
unsigned long bomb_next_beep = 0;           //cuando debería ser el siguiente beep
unsigned long bomb_beep_duration = 15;      //Tiempo que debe estar encendia la tira cada beep

boolean bomb_led_is_on = false;
int bomb_beep_count = 0;  //how many beeps have the bomb emitted


//Funcion que extrae el valor almacenado en un String @csv_line separado por @separator colocado en la posición @index (la empleamos para desglosar el chunk de datos que se nos manda por puerto serie)
String get_csv_value(String csv_line, char separator, int index){
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = csv_line.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(csv_line.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? csv_line.substring(strIndex[0], strIndex[1]) : "";
}


//Recepción de paquetes de  datos por puerto serie. Almacena los datos extraídos en las variables globales
void readSerialData() {
  String command = Serial.readString();

//Recepción del paquete player_state
  //p,[ weapon_ammo_clip, weapon_ammo_clip_max, player_state_health, player_state_armor, player_state_helmet, player_state_flashed, player_state_smoked, player_state_burning, player_state_money, player_state_round_kills, player_state_round_killhs, player_state_equip_value]
  if (command.charAt(0) == 'p') {
    weapon_ammo_clip            = get_csv_value(command, ',',1).toInt();
    weapon_ammo_clip_max        = get_csv_value(command, ',',2).toInt();
    player_state_health         = get_csv_value(command, ',',3).toInt();
    player_state_armor          = get_csv_value(command, ',',4).toInt();
    player_state_helmet         = get_csv_value(command, ',',5).toInt();
    player_state_flashed        = get_csv_value(command, ',',6).toInt();
    player_state_smoked         = get_csv_value(command, ',',7).toInt();
    player_state_burning        = get_csv_value(command, ',',8).toInt();
    player_state_money          = get_csv_value(command, ',',9).toInt();
    player_state_round_kills    = get_csv_value(command, ',',10).toInt();
    player_state_round_killhs   = get_csv_value(command, ',',11).toInt();
    player_state_equip_value    = get_csv_value(command, ',',12).toInt();

    Serial.print("OK");
    Serial.flush(); 
  }

  //Recepción del paquete player_match_stats
  //x,[player_match_stats_kills, player_match_stats_assists, player_match_stats_deaths, player_match_stats_mvps, player_match_stats_score]
  else if (command.charAt(0) == 'x') {
    player_match_stats_kills    = get_csv_value(command, ',',1).toInt();
    player_match_stats_assists  = get_csv_value(command, ',',2).toInt();
    player_match_stats_deaths   = get_csv_value(command, ',',3).toInt();
    player_match_stats_mvps     = get_csv_value(command, ',',4).toInt();
    player_match_stats_score    = get_csv_value(command, ',',5).toInt();

    Serial.print("OK");
    Serial.flush(); 
  }
  
  //Recepción del paquete map
  //m,[map_team_ct_score, map_team_t_score, map_mode, map_name, map_round]
  else if (command.charAt(0) == 'm') {
    map_team_ct_score       = get_csv_value(command, ',',1).toInt();
    map_team_t_score        = get_csv_value(command, ',',2).toInt();
    map_mode                = get_csv_value(command, ',',3).toInt();
    map_name                = get_csv_value(command, ',',4).toInt();
    map_round               = get_csv_value(command, ',',5).toInt();

    Serial.print("OK");
    Serial.flush(); 
  }

  //Recepción del paquete round
  //r,[round_phase, round_bomb, round_win_team]
  else if (command.charAt(0) == 'r') {
    round_phase                 = get_csv_value(command, ',',1);
    round_bomb                  = get_csv_value(command, ',',2);
    round_win_team              = get_csv_value(command, ',',3);

    Serial.print("OK");
    Serial.flush(); 

    //Estado de la bomba en función del caracter recibido en ese parámetro
    if(round_bomb == "p"){
        //Si la bomba está plantada y antes no, activamos el timer (se acaba de plantar)
        if(bomb_status != BOMB_STATUS_PLANTED){
            bomb_status = BOMB_STATUS_PLANTED;
            //Almacenamos el momento de recepcion de la activación
            bomb_start_millis = millis();
            //Calculamos cuando explotará
            bomb_end_millis = bomb_start_millis + 40000;
            //Reiniciamos todas las variables que controlan la bomba, podemos meterlo en una función reset_bomb_status()
            bomb_last_beep = 0;
            bomb_next_beep = 0;
            bomb_beep_duration = 15;
            bomb_led_is_on = false;
            bomb_beep_count = 0;
        }
           
    }else if(round_bomb == "d"){
         bomb_status = BOMB_STATUS_DEFUSED;       
    }else if (round_bomb == "e"){
         bomb_status = BOMB_STATUS_EXPLODED;
    }else {
         bomb_status = BOMB_STATUS_NOT_PLANTED;
    }   
  }
}

void setup() {
    // Iniciamos el puerto serie a 115200 de baudrate
    Serial.begin(250000);
    // Tiempo de espera del puerto serie para recibir datos (en base al baudrate)
    Serial.setTimeout(60);

    //Creamos la instancia neopixel de la tira LED de SALUD
    FastLED.addLeds<NEOPIXEL, HEALTH_NEOPIXEL_STRIP_PIN>(HEALTH_NEOPIXEL_STRIP, HEALTH_NEOPIXEL_STRIP_LED_COUNT);
    //Creamos la instancia neopixel de la tira LED de BOMBA
    FastLED.addLeds<NEOPIXEL, BOMB_NEOPIXEL_STRIP_PIN>(BOMB_NEOPIXEL_STRIP, BOMB_NEOPIXEL_STRIP_LED_COUNT);
    //Creamos la instancia neopixel de la tira LED de MUNICIÓN
    FastLED.addLeds<NEOPIXEL, AMMO_NEOPIXEL_STRIP_PIN>(AMMO_NEOPIXEL_STRIP, AMMO_NEOPIXEL_STRIP_LED_COUNT);
    //Creamos la instancia neopixel de la tira LED de ARMADURA
    FastLED.addLeds<NEOPIXEL, ARMOR_NEOPIXEL_STRIP_PIN>(ARMOR_NEOPIXEL_STRIP, ARMOR_NEOPIXEL_STRIP_LED_COUNT);
    //Creamos la instancia neopixel de la tira LED de PORCENTAJE DE RONDAS
    FastLED.addLeds<NEOPIXEL, ROUND_PERCENT_SCORE_NEOPIXEL_STRIP_PIN>(ROUND_PERCENT_SCORE_NEOPIXEL_STRIP, ROUND_PERCENT_SCORE_NEOPIXEL_STRIP_LED_COUNT);

    //Establecemos la luminosidad de las tiras de led
    FastLED.setBrightness(NEOPIXEL_BRIGHTNESS);

    //Establecemos la luminosidad de las pantallas TM1637
    BOMB_TIMER_DISPLAY.setBrightness(0x0f);
    WEAPON_AMMO_CLIP_DISPLAY.setBrightness(0x0f);
    PLAYER_STATE_HEALTH_DISPLAY.setBrightness(0x0f);
    PLAYER_STATE_ARMOR_DISPLAY.setBrightness(0x0f);
    PLAYER_STATE_HELMET_DISPLAY.setBrightness(0x0f);
    PLAYER_STATE_MONEY_DISPLAY.setBrightness(0x0f);
    PLAYER_STATE_ROUND_KILLS_DISPLAY.setBrightness(0x0f);
    PLAYER_STATE_ROUND_KILLHS_DISPLAY.setBrightness(0x0f);
    PLAYER_STATE_EQUIP_VALUE_DISPLAY.setBrightness(0x0f);
    PLAYER_MATCH_STATS_KILLS_DISPLAY.setBrightness(0x0f);
    PLAYER_MATCH_STATS_ASSISTS_DISPLAY.setBrightness(0x0f);
    PLAYER_MATCH_STATS_DEATHS_DISPLAY.setBrightness(0x0f);
    PLAYER_MATCH_STATS_MVPS_DISPLAY.setBrightness(0x0f);
    PLAYER_MATCH_STATS_SCORE_DISPLAY.setBrightness(0x0f);
    MAP_TEAM_CT_SCORE_DISPLAY.setBrightness(0x0f);
    MAP_TEAM_T_SCORE_DISPLAY.setBrightness(0x0f);
    MAP_ROUND_DISPLAY.setBrightness(0x0f);

    //INICIAMOS EL PRGRAMA CON LA BOMBA "NO PLANTADA"
    bomb_status = BOMB_STATUS_NOT_PLANTED;
}

void loop() {
    //Establecemos el el brillo de las tiras en función del valor del potenciómetro conectado en NEOPOIXEL_BRIGHTNESS_POTENTIOMETER_PIN
    NEOPIXEL_BRIGHTNESS = analogRead(NEOPOIXEL_BRIGHTNESS_POTENTIOMETER_PIN);
    NEOPIXEL_BRIGHTNESS = map(NEOPIXEL_BRIGHTNESS,0,1024,0,255);
    FastLED.setBrightness(NEOPIXEL_BRIGHTNESS);

    //Leemos los chunks recibidos por puerto serie
    readSerialData();

    //Renderizamos las tiras de led
    display_bomb_status_rgb();
    display_player_state_health_rgb();
    display_player_state_armor_rgb();
    display_weapon_ammo_clip_rgb();
    display_round_percent_score();

    FastLED.show();

    //Renderizamos los displays
    //display_bomb_timer();
    //display_weapon_ammo_clip();
    //display_player_state_health();
    //display_player_state_armor();
    //display_player_state_helmet();
    //display_player_state_money();
    //display_player_state_round_kills();
    //display_player_state_round_killhs();
    //display_player_state_equip_value();
    //display_player_match_stats_kills();
    //display_player_match_stats_assists();
    //display_player_match_stats_deaths();
    //display_player_match_stats_mvps();
    //display_player_match_stats_score();
    //display_ct_score();
    //display_t_score();
    //display_map_round();
}
