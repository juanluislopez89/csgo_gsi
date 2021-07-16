//Parpadeo de la bomba en la tira LED de la bomba
void display_bomb_status_rgb(){
    switch(bomb_status){
        case BOMB_STATUS_NOT_PLANTED:
        
        break;

        case BOMB_STATUS_DEFUSED:
            bomb_strip_black();
        break;
  
        case BOMB_STATUS_EXPLODED:
            bomb_strip_black();
        break;

        case BOMB_STATUS_PLANTED:
            bomb_seconds_left = (bomb_end_millis - millis())/1000;
            //Si nos pasamos de timepo (aunque no hayamos recibido el comando por serial, marcamos la bomba como explotada)
            if(bomb_end_millis < millis()){
                bomb_status = BOMB_STATUS_EXPLODED;
                bomb_strip_black();
            }

            unsigned long curr_millis = millis();
            unsigned long elapsed_millis = bomb_end_millis - curr_millis;
            //Cuanddo queden menos de 3 segundos para la explosión, ponemos la tira en blanco
            if(elapsed_millis < 3000){
                bomb_strip_white();
            }
            else
            {
                //Si alcanzamos el final de un ciclo
                if(curr_millis > bomb_next_beep){
                    //Serial.println("ON");
                    if(!bomb_led_is_on){
                        bomb_strip_red();
                        bomb_led_is_on = true;
                    }
                    
                    //Ponemos como ultimo pitido dado, en que acabamos de alcanzar
                    bomb_last_beep = bomb_next_beep;
                    //Calculamos el inicio del siguiente cicleo
                    bomb_next_beep = curr_millis + (0.13*sq(bomb_beep_count)-20*bomb_beep_count+990);
        
                    bomb_beep_count++;
                }
                    
                //Si dentro del beep estamos en el período de encencido
                else if(curr_millis > bomb_last_beep + bomb_beep_duration){
                    //OFF
                    //Serial.println("OFF");
                    if(bomb_led_is_on == true){
                        bomb_strip_black();
                        bomb_led_is_on = false;
                    }
                }
            }
         break;
     }
}

//Coloca toda la tira de led de la bomba en rojo
void bomb_strip_red(){
    for (byte n = 0; n < BOMB_NEOPIXEL_STRIP_LED_COUNT; n++){
        BOMB_NEOPIXEL_STRIP[n] = CRGB::Red;
    }
    FastLED.show();
}

//Coloca toda la tira de led de la bomba en negro
void bomb_strip_black(){
    for (byte n = 0; n < BOMB_NEOPIXEL_STRIP_LED_COUNT; n++){
        BOMB_NEOPIXEL_STRIP[n] = CRGB::Black;
    }
    FastLED.show();
}

//Coloca toda la tira de led de la bomba en blanco
void bomb_strip_white(){
    for (byte n = 0; n < BOMB_NEOPIXEL_STRIP_LED_COUNT; n++){
        BOMB_NEOPIXEL_STRIP[n] = CRGB::White;
    }
    FastLED.show();
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

void display_player_state_armor_rgb(){
    //Calculamos la proporcion de leds en funcion de la armadura del jugador con map
    byte armor_led_count = map(player_state_health,0,100,0,ARMOR_NEOPIXEL_STRIP_LED_COUNT);
    //Recorremos todos los leds de la tira, pintando de verde los correspondientes a armadura y de negro los vacíos
    for (byte n = 0; n < ARMOR_NEOPIXEL_STRIP_LED_COUNT; n++){
        n < armor_led_count ?  ARMOR_NEOPIXEL_STRIP[n] = CRGB::Green : ARMOR_NEOPIXEL_STRIP[n] = CRGB::Black;
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

//Función que renderiza el porcentaje derondas ganadas en la tira de rondas ganadas.
//Se muestra el porcentaje de cada equio de rondas ganadas, de modo que si van ganando CT's un 80% de las rondas
//Se verá un 80% de la tira encendida en azul(CT) y el otro 20 en amarillo (T).
void display_round_percent_score(){
    if(map_round > 1){
        //Calculamos el porcentaje de rondas ganadas por CTs
        byte ct_percent = map_team_ct_score * 100 / (map_round - 1);
        Serial.println(ct_percent);
        //Calculamos la proporcion de leds ct en funcion del porcentaje ct de rondas ganadas
        byte ct_led_count = map(ct_percent,0,100,0, ROUND_PERCENT_SCORE_NEOPIXEL_STRIP_LED_COUNT);
        //Recorremos todos los leds de la tira, pintando de azul los correspondientes al porcentaje CT y de amarillo el resto (T)
        for (byte n = 0; n < ROUND_PERCENT_SCORE_NEOPIXEL_STRIP_LED_COUNT; n++){
            n < ct_led_count ?  ROUND_PERCENT_SCORE_NEOPIXEL_STRIP[n] = CRGB::Blue : ROUND_PERCENT_SCORE_NEOPIXEL_STRIP[n] = CRGB::Yellow;
        }
        FastLED.show();
    }
    else
    {
         for (byte n = 0; n < ROUND_PERCENT_SCORE_NEOPIXEL_STRIP_LED_COUNT; n++){
            ROUND_PERCENT_SCORE_NEOPIXEL_STRIP[n] = CRGB::Black;
         }
         FastLED.show();
    } 
}
