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
