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
