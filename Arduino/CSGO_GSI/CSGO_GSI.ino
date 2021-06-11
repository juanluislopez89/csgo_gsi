#include "config.h"
#include "declarations.h"
#include "constants.h"

// Dato curioso #include "config.h" busca en la carpeta del sketch y #include <config.h> busca en la carpeta librearies de Arduino

uint8_t brillo = 210;


// Estas variables se emplean para controlar el estado de la bomba.

byte bomb_status;

// Estas variables se emplean para controlar los timings del parpadeo de la bomba activada.
// El parpadeo consta de 2 timings, el que separa los parpadeos y el que separa el encendido y apagado en un parpadeo


unsigned long bomb_start_millis;             //marca temporal de recepcion de inicio de bomba
unsigned long bomb_end_millis;               //marca temporal de finalización de bomba


unsigned long bomb_last_beep = 0;           //marca temporal de la ultima vez que se encendió
unsigned long bomb_next_beep = 0;           //cuando debería ser el siguiente beep
unsigned long bomb_beep_duration = 15;      //Tiempo que debe estar encendia la tira cada beep
unsigned int bomb_beep_delay = 16;

boolean bomb_led_is_on = false;
int bomb_beep_count = 0;  //how many beeps have the bomb emitted



String getValue(String data, char separator, int index){
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


//Recepción de paquetes de  datos por puerto serie. Almacena los datos extraídos en las variables globales
void readSerialData() {
  String command = Serial.readString();

//Recepción del paquete player_state
  //p[ weapon_ammo_clip, player_state_health, player_state_armor, player_state_helmet, player_state_flashed, player_state_smoked, player_state_burning, player_state_money, player_state_round_kills, player_state_round_killhs, player_state_equip_value]
  if (command.charAt(0) == 'p') {
    weapon_ammo_clip            = getValue(command, ',',1).toInt();
    player_state_health         = getValue(command, ',',2).toInt();
    player_state_armor          = getValue(command, ',',3).toInt();
    player_state_helmet         = getValue(command, ',',4).toInt();
    player_state_flashed        = getValue(command, ',',5).toInt();
    player_state_smoked         = getValue(command, ',',6).toInt();
    player_state_burning        = getValue(command, ',',7).toInt();
    player_state_money          = getValue(command, ',',8).toInt();
    player_state_round_kills    = getValue(command, ',',9).toInt();
    player_state_round_killhs   = getValue(command, ',',10).toInt();
    player_state_equip_value    = getValue(command, ',',11).toInt();

    Serial.print("OK");
    Serial.flush(); 
  }

  //Recepción del paquete player_match_stats
  //x[player_match_stats_kills, player_match_stats_assists, player_match_stats_deaths, player_match_stats_mvps, player_match_stats_score]
  else if (command.charAt(0) == 'x') {
    player_match_stats_kills    = getValue(command, ',',1).toInt();
    player_match_stats_assists  = getValue(command, ',',2).toInt();
    player_match_stats_deaths   = getValue(command, ',',3).toInt();
    player_match_stats_mvps     = getValue(command, ',',4).toInt();
    player_match_stats_score    = getValue(command, ',',5).toInt();

    Serial.print("OK");
    Serial.flush(); 
  }
  
  //Recepción del paquete map
  //m[map_team_ct_score, map_team_t_score, map_mode, map_name, map_round]
  else if (command.charAt(0) == 'm') {
    map_team_ct_score       = getValue(command, ',',1).toInt();
    map_team_t_score        = getValue(command, ',',2).toInt();
    map_mode                = getValue(command, ',',3).toInt();
    map_name                = getValue(command, ',',4).toInt();
    map_round               = getValue(command, ',',5).toInt();

    Serial.print("OK");
    Serial.flush(); 
  }

  //Recepción del paquete round
  //r[round_phase, round_bomb, round_win_team]
  else if (command.charAt(0) == 'r') {
    round_phase                 = getValue(command, ',',1);
    round_bomb                  = getValue(command, ',',2);
    round_win_team              = getValue(command, ',',3);

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
            //Establecemos el delay de parpadeo inicial de la bomba
            bomb_beep_delay = 1000;
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
    Serial.begin(115200);
    Serial.setTimeout(3);

    FastLED.addLeds<NEOPIXEL, 10>(BOMB_NEOPIXEL_STRIP, BOMB_NEOPIXEL_STRIP_LED_COUNT);


    display1.setBrightness(0x0f);
    display2.setBrightness(0x0f);
    display3.setBrightness(0x0f);
    display4.setBrightness(0x0f);
    display5.setBrightness(0x0f);
    display6.setBrightness(0x0f);
  
    bomb_status = BOMB_STATUS_NOT_PLANTED;
}

void loop() {
    readSerialData();
    handle_bomb(); 
    bomb_blink();
    display_bomb_timer(display1);
    display_map_round(display2);
    
    display_player_state_health(display3);
    display_weapon_ammo_clip(display4);
    
    display_player_match_stats_kills(display5);
    display_player_match_stats_score(display6);
}
