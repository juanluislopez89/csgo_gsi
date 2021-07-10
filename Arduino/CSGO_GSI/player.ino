
void display_player_state_health(TM1637Display display){
     display.showNumberDecEx(player_state_health);
}

void display_player_state_armor(TM1637Display display){
     display.showNumberDecEx(player_state_armor);
}

void display_player_state_helmet(TM1637Display display){
     display.showNumberDecEx(player_state_helmet);
}

void display_player_state_flashed(TM1637Display display){
     display.showNumberDecEx(player_state_flashed);
}

void display_player_state_smoked(TM1637Display display){
     display.showNumberDecEx(player_state_smoked);
}

void display_player_state_burning(TM1637Display display){
     display.showNumberDecEx(player_state_burning);
}

void display_player_state_money(TM1637Display display){
     display.showNumberDecEx(player_state_money);
}

void display_player_state_round_kills(TM1637Display display){
     display.showNumberDecEx(player_state_round_kills);
}

void display_player_state_round_killhs(TM1637Display display){
     display.showNumberDecEx(player_state_round_killhs);
}

void display_player_state_equip_value(TM1637Display display){
     display.showNumberDecEx(player_state_equip_value);
}

void display_weapon_ammo_clip(TM1637Display display){
     display.showNumberDecEx(weapon_ammo_clip);
}


void display_player_match_stats_kills(TM1637Display display){
     display.showNumberDecEx(player_match_stats_kills);
}

void display_player_match_stats_assists(TM1637Display display){
     display.showNumberDecEx(player_match_stats_assists);
}

void display_player_match_stats_deaths(TM1637Display display){
     display.showNumberDecEx(player_match_stats_deaths);
}

void display_player_match_stats_mvps(TM1637Display display){
     display.showNumberDecEx(player_match_stats_mvps);
}

void display_player_match_stats_score(TM1637Display display){
     display.showNumberDecEx(player_match_stats_score);
}


void display_player_state_health_rgb(){
    //Calculamos la proporcion de leds en funcion de la salud del jugador con map
    byte health_led_count = map(player_state_health,0,100,0,HEALTH_NEOPIXEL_STRIP_LED_COUNT);
    //Recorremos todos los leds de la tira, pintando de verde los correspondientes a salud y de negro los vacíos
    for (byte n = 0; n < HEALTH_NEOPIXEL_STRIP_LED_COUNT; n++){
        n < health_led_count ?  HEALTH_NEOPIXEL_STRIP[n] = CRGB::Green : HEALTH_NEOPIXEL_STRIP[n] = CRGB::Black;
    }
    FastLED.show();
}

void display_weapon_ammo_clip_rgb(){
    //Calculamos el porcentaje ocupado en el cargador
    byte ammo_percent = weapon_ammo_clip_max > 0 ? weapon_ammo_clip * 100 / weapon_ammo_clip_max : 0;
    //Calculamos la proporcion de leds en funcion del porcentaje del cargador ocupado
    byte ammo_led_count = map(ammo_percent, 0, 100, 0, AMMO_NEOPIXEL_STRIP_LED_COUNT);
    //Recorremos todos los leds de la tira, pintando de azul los correspondientes a municion y de negro los vacíos
    for (byte n = 0; n < AMMO_NEOPIXEL_STRIP_LED_COUNT; n++){
        n < ammo_led_count ?  AMMO_NEOPIXEL_STRIP[n] = CRGB::Blue : AMMO_NEOPIXEL_STRIP[n] = CRGB::Black;
    }
    FastLED.show();
}
