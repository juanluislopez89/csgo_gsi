//Mostrar el tiempo que queda de la bomba
void display_bomb_timer(){
    if(bomb_status == BOMB_STATUS_PLANTED){
        BOMB_TIMER_DISPLAY.showNumberDecEx(bomb_seconds_left, 0b11100000, true);
    }
    else
    {
        BOMB_TIMER_DISPLAY.setSegments(NO_BOMB_DISPLAY_TEXT);
    }
}    

void display_ct_score(){
     MAP_TEAM_CT_SCORE_DISPLAY.showNumberDecEx(map_team_ct_score);
}

void display_t_score(){
     MAP_TEAM_T_SCORE_DISPLAY.showNumberDecEx(map_team_t_score);
}

void display_map_round(){
     MAP_ROUND_DISPLAY.showNumberDecEx(map_round);
}

void display_player_state_health(){
     PLAYER_STATE_HEALTH_DISPLAY.showNumberDecEx(player_state_health);
}

void display_player_state_armor(){
     PLAYER_STATE_ARMOR_DISPLAY.showNumberDecEx(player_state_armor);
}

void display_player_state_helmet(){
     PLAYER_STATE_HELMET_DISPLAY.showNumberDecEx(player_state_helmet);
}

void display_player_state_money(){
     PLAYER_STATE_MONEY_DISPLAY.showNumberDecEx(player_state_money);
}

void display_player_state_round_kills(){
     PLAYER_STATE_ROUND_KILLS_DISPLAY.showNumberDecEx(player_state_round_kills);
}

void display_player_state_round_killhs(){
     PLAYER_STATE_ROUND_KILLHS_DISPLAY.showNumberDecEx(player_state_round_killhs);
}

void display_player_state_equip_value(){
     PLAYER_STATE_EQUIP_VALUE_DISPLAY.showNumberDecEx(player_state_equip_value);
}

void display_weapon_ammo_clip(){
     WEAPON_AMMO_CLIP_DISPLAY.showNumberDecEx(weapon_ammo_clip);
}

void display_player_match_stats_kills(){
     PLAYER_MATCH_STATS_KILLS_DISPLAY.showNumberDecEx(player_match_stats_kills);
}

void display_player_match_stats_assists(){
     PLAYER_MATCH_STATS_ASSISTS_DISPLAY.showNumberDecEx(player_match_stats_assists);
}

void display_player_match_stats_deaths(){
     PLAYER_MATCH_STATS_DEATHS_DISPLAY.showNumberDecEx(player_match_stats_deaths);
}

void display_player_match_stats_mvps(){
     PLAYER_MATCH_STATS_MVPS_DISPLAY.showNumberDecEx(player_match_stats_mvps);
}

void display_player_match_stats_score(){
     PLAYER_MATCH_STATS_SCORE_DISPLAY.showNumberDecEx(player_match_stats_score);
}
