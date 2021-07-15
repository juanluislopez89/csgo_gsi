void handle_bomb(){
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
            
        break;
    }
}

//Parpadeo de la bomba en la tira de LED de la bomba
void bomb_blink(){
    if(bomb_status == BOMB_STATUS_PLANTED){
        unsigned long curr_millis = millis();
        unsigned long elapsed_millis = bomb_end_millis - curr_millis;

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
    }
}

void bomb_strip_red(){
    for (byte n = 0; n < BOMB_NEOPIXEL_STRIP_LED_COUNT; n++){
        BOMB_NEOPIXEL_STRIP[n] = CRGB::Red;
    }
    FastLED.show();
}

void bomb_strip_black(){
    for (byte n = 0; n < BOMB_NEOPIXEL_STRIP_LED_COUNT; n++){
        BOMB_NEOPIXEL_STRIP[n] = CRGB::Black;
    }
    FastLED.show();
}

void bomb_strip_white(){
    for (byte n = 0; n < BOMB_NEOPIXEL_STRIP_LED_COUNT; n++){
        BOMB_NEOPIXEL_STRIP[n] = CRGB::White;
    }
    FastLED.show();
}

//Mostrar el tiempo que queda de la bomba
void display_bomb_timer(TM1637Display display){
    if(bomb_status == BOMB_STATUS_PLANTED){
        display.showNumberDecEx(bomb_seconds_left, 0b11100000, true);
    }
    else
    {
         display.setSegments(NO_BOMB_DISPLAY_TEXT);
    }
}    
