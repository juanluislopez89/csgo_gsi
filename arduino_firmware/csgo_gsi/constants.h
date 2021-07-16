//Posibles estado de la bomba durante el juego
const byte BOMB_STATUS_NOT_PLANTED = 0;
const byte BOMB_STATUS_PLANTED = 1;
const byte BOMB_STATUS_DEFUSED = 2;
const byte BOMB_STATUS_EXPLODED = 3;

//Representa (-- --) en un display TM1637Display
const uint8_t NO_BOMB_DISPLAY_TEXT[] = {
  SEG_G,
  SEG_G,
  SEG_G,    
  SEG_G
};
