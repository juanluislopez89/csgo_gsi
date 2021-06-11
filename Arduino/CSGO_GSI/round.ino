//PARSEO DE DATOS DE LA RONDA
void readRoundData(String command) {
  //Si recibimos que la ronda está en freezetime (comprando)
   if (command.charAt(1) == 'f') {  //round freezetime
    bomb_status = BOMB_STATUS_NOT_PLANTED; //Marcamos la bomba como desactivada
  }

  //Si recibimos que la ronda está en warmup (en un competitivo, antes de la primera ronda)
  else if (command.charAt(1) == 'w') {  //round warmup ()
   bomb_status = BOMB_STATUS_NOT_PLANTED; //Marcamos la bomba como desactivada
  }
  //Si recibimos que la ronda está en over (finalizada)
  else if (command.charAt(1) == 'o') { // round over
    //Comprobamos si la bomba está defusada o ha explotado
    if( bomb_status == BOMB_STATUS_EXPLODED){
      //Explotó la bomba
    }
    else if(bomb_status == BOMB_STATUS_DEFUSED){
      //Bomba defusada
    }
  }
  //Si recibimos que la ronda está en live (en marcha)
  else if (command.charAt(1) == 'l') { //round live
    //no hacemos nada
  }
  Serial.print("OK");
  Serial.flush();
}
