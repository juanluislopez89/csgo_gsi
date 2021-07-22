# encoding: utf-8
###################################################################
#
#					LIBRERIAS PYTHON
#
###################################################################
from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
import sys
import os
import time
import json
import serial.tools.list_ports
from colorama import init, Fore, Back, Style


# Server GSI
class GsiServer(HTTPServer):
    def init_state(self):
        self.player_state_health = None
        self.player_state_armor = None
        self.player_state_helmet = None
        self.player_state_flashed = None
        self.player_state_smoked = None
        self.player_state_burning = None
        self.player_state_money = None
        self.player_state_round_kills = None
        self.player_state_round_killhs = None
        self.player_state_equip_value = None
        self.weapon_ammo_clip = None
        self.player_match_stats_kills = None
        self.player_match_stats_assists = None
        self.player_match_stats_deaths = None
        self.player_match_stats_mvps = None
        self.player_match_stats_score = None
        self.round_phase = None
        self.round_bomb = None
        self.round_win_team = None
        self.map_team_ct_score = None
        self.map_team_t_score = None
        self.map_mode = None
        self.map_name = None
        self.map_round = None


# Requets handler para el server GSI
class GsiRequestHandler(BaseHTTPRequestHandler):

    def log_message(self, format, *args):
        # esto evita que muestre el log todo el rato
        return

    def do_POST(self):
        length = int(self.headers['Content-Length'])
        body = self.rfile.read(length).decode('utf-8')

        self.parse_gsi_json(json.loads(body))
        self.send_header('Content-type', 'text/html')
        self.send_response(200)
        self.end_headers()

    def parse_gsi_json(self, gsi_json):
        weapon_ammo_clip = self.get_weapon_ammo_clip(gsi_json)
        weapon_ammo_clip_max = self.get_weapon_ammo_clip_max(gsi_json)
        player_state_health = self.get_player_state_health(gsi_json)
        player_state_armor = self.get_player_state_armor(gsi_json)
        player_state_helmet = int(self.get_player_state_helmet(gsi_json))
        player_state_flashed = self.get_player_state_flashed(gsi_json)
        player_state_smoked = self.get_player_state_smoked(gsi_json)
        player_state_burning = self.get_player_state_burning(gsi_json)
        player_state_money = self.get_player_state_money(gsi_json)
        player_state_round_kills = self.get_player_state_round_kills(gsi_json)
        player_state_round_killhs = self.get_player_state_round_killhs(gsi_json)
        player_state_equip_value = self.get_player_state_equip_value(gsi_json)
        player_match_stats_kills = self.get_player_match_stats_kills(gsi_json)
        player_match_stats_assists = self.get_player_match_stats_assists(gsi_json)
        player_match_stats_deaths = self.get_player_match_stats_deaths(gsi_json)
        player_match_stats_mvps = self.get_player_match_stats_mvps(gsi_json)
        player_match_stats_score = self.get_player_match_stats_score(gsi_json)
        round_phase = self.get_round_phase(gsi_json)
        round_bomb = self.get_round_bomb(gsi_json)
        round_win_team = self.get_round_win_team(gsi_json)
        map_team_ct_score = self.get_map_team_ct_score(gsi_json)
        map_team_t_score = self.get_map_team_t_score(gsi_json)
        map_mode = self.get_map_mode(gsi_json)
        map_name = self.get_map_name(gsi_json)
        map_round = self.get_map_round(gsi_json)

        self.player_state_health = player_state_health
        self.player_state_armor = player_state_armor
        self.player_state_helmet = player_state_helmet
        self.player_state_flashed = player_state_flashed
        self.player_state_smoked = player_state_smoked
        self.player_state_burning = player_state_burning
        self.player_state_money = player_state_money
        self.player_state_round_kills = player_state_round_kills
        self.player_state_round_killhs = player_state_round_killhs
        self.player_state_equip_value = player_state_equip_value
        self.weapon_ammo_clip = weapon_ammo_clip
        self.weapon_ammo_clip_max = weapon_ammo_clip_max
        self.player_match_stats_kills = player_match_stats_kills
        self.player_match_stats_assists = player_match_stats_assists
        self.player_match_stats_deaths = player_match_stats_deaths
        self.player_match_stats_mvps = player_match_stats_mvps
        self.player_match_stats_score = player_match_stats_score
        self.round_phase = round_phase
        self.round_bomb = round_bomb
        self.round_win_team = round_win_team
        self.map_team_ct_score = map_team_ct_score
        self.map_team_t_score = map_team_t_score
        self.map_mode = map_mode
        self.map_name = map_name
        self.map_round = map_round

        welcome_message()
        player_state_packet = str(weapon_ammo_clip) + ',' + str(weapon_ammo_clip_max) + ',' + str(
            player_state_health) + ',' + str(player_state_armor) + ',' + str(player_state_helmet) + ',' + str(
            player_state_flashed) + ',' + str(player_state_smoked) + ',' + str(player_state_burning) + ',' + str(
            player_state_money) + ',' + str(player_state_round_kills) + ',' + str(
            player_state_round_killhs) + ',' + str(player_state_equip_value)
        send_player_state_packet(player_state_packet)

        round_packet = str(round_phase) + ',' + str(round_bomb) + ',' + str(round_win_team)
        send_round_packet(round_packet)

        player_match_stats_packet = str(player_match_stats_kills) + ',' + str(player_match_stats_assists) + ',' + str(
            player_match_stats_deaths) + ',' + str(player_match_stats_mvps) + ',' + str(player_match_stats_score)
        send_player_match_stats_packet(player_match_stats_packet)

        map_packet = str(map_team_ct_score) + ',' + str(map_team_t_score) + ',' + str(map_mode) + ',' + str(
            map_name) + ',' + str(map_round)
        send_map_packet(map_packet)

    #	PLAYER STATE (CURRENT ROUND)
    def get_player_state_health(self, gsi_json):
        try:
            return gsi_json['player']['state']['health']
        except KeyError:
            return 0

    def get_player_state_armor(self, gsi_json):
        try:
            return gsi_json['player']['state']['armor']
        except KeyError:
            return 0

    def get_player_state_helmet(self, gsi_json):
        try:
            return gsi_json['player']['state']['helmet']
        except KeyError:
            return 0

    def get_player_state_flashed(self, gsi_json):
        try:
            return gsi_json['player']['state']['flashed']
        except KeyError:
            return 0

    def get_player_state_smoked(self, gsi_json):
        try:
            return gsi_json['player']['state']['smoked']
        except KeyError:
            return 0

    def get_player_state_burning(self, gsi_json):
        try:
            return gsi_json['player']['state']['burning']
        except KeyError:
            return 0

    def get_player_state_money(self, gsi_json):
        try:
            return gsi_json['player']['state']['money']
        except KeyError:
            return 0

    def get_player_state_round_kills(self, gsi_json):
        try:
            return gsi_json['player']['state']['round_kills']
        except KeyError:
            return 0

    def get_player_state_round_killhs(self, gsi_json):
        try:
            return gsi_json['player']['state']['round_killhs']
        except KeyError:
            return 0

    def get_player_state_equip_value(self, gsi_json):
        try:
            return gsi_json['player']['state']['equip_value']
        except KeyError:
            return 0

    def get_weapon_ammo_clip(self, gsi_json):
        if 'player' in gsi_json and 'weapons' in gsi_json['player']:
            if 'weapon_1' in gsi_json['player']['weapons'] and 'state' in gsi_json['player']['weapons']['weapon_1']:
                if gsi_json['player']['weapons']['weapon_1']['state'] == 'active':
                    if 'ammo_clip' in gsi_json['player']['weapons']['weapon_1']:
                        return gsi_json['player']['weapons']['weapon_1']['ammo_clip']
                    else:
                        return 0;
            if 'weapon_2' in gsi_json['player']['weapons'] and 'state' in gsi_json['player']['weapons']['weapon_2']:
                if gsi_json['player']['weapons']['weapon_2']['state'] == 'active':
                    if 'ammo_clip' in gsi_json['player']['weapons']['weapon_2']:
                        return gsi_json['player']['weapons']['weapon_2']['ammo_clip']
                    else:
                        return 0;
            if 'weapon_3' in gsi_json['player']['weapons'] and 'state' in gsi_json['player']['weapons']['weapon_3']:
                if gsi_json['player']['weapons']['weapon_3']['state'] == 'active':
                    if 'ammo_clip' in gsi_json['player']['weapons']['weapon_3']:
                        return gsi_json['player']['weapons']['weapon_3']['ammo_clip']
                    else:
                        return 0;
            else:
                return 0
        else:
            return 0

    def get_weapon_ammo_clip_max(self, gsi_json):
        if 'player' in gsi_json and 'weapons' in gsi_json['player']:
            if 'weapon_1' in gsi_json['player']['weapons'] and 'state' in gsi_json['player']['weapons']['weapon_1']:
                if gsi_json['player']['weapons']['weapon_1']['state'] == 'active':
                    if 'ammo_clip' in gsi_json['player']['weapons']['weapon_1']:
                        return gsi_json['player']['weapons']['weapon_1']['ammo_clip_max']
                    else:
                        return 0;
            if 'weapon_2' in gsi_json['player']['weapons'] and 'state' in gsi_json['player']['weapons']['weapon_2']:
                if gsi_json['player']['weapons']['weapon_2']['state'] == 'active':
                    if 'ammo_clip' in gsi_json['player']['weapons']['weapon_2']:
                        return gsi_json['player']['weapons']['weapon_2']['ammo_clip_max']
                    else:
                        return 0;
            if 'weapon_3' in gsi_json['player']['weapons'] and 'state' in gsi_json['player']['weapons']['weapon_3']:
                if gsi_json['player']['weapons']['weapon_3']['state'] == 'active':
                    if 'ammo_clip' in gsi_json['player']['weapons']['weapon_3']:
                        return gsi_json['player']['weapons']['weapon_3']['ammo_clip_max']
                    else:
                        return 0;
            else:
                return 0
        else:
            return 0

    #	PLAYER MATCH STATS
    def get_player_match_stats_kills(self, gsi_json):
        try:
            return gsi_json['player']['match_stats']['kills']
        except KeyError:
            return 0

    def get_player_match_stats_assists(self, gsi_json):
        try:
            return gsi_json['player']['match_stats']['assists']
        except KeyError:
            return 0

    def get_player_match_stats_deaths(self, gsi_json):
        try:
            return gsi_json['player']['match_stats']['deaths']
        except KeyError:
            return 0

    def get_player_match_stats_mvps(self, gsi_json):
        try:
            return gsi_json['player']['match_stats']['mvps']
        except KeyError:
            return 0

    def get_player_match_stats_score(self, gsi_json):
        try:
            return gsi_json['player']['match_stats']['score']
        except KeyError:
            return 0

    #	CURRENT ROUND
    def get_round_phase(self, gsi_json):
        try:
            round_phase = gsi_json['round']['phase']

            if round_phase == 'freezetime':
                return 'f'
            elif round_phase == 'warmup':
                return 'w'
            elif round_phase == 'over':
                return 'o'
            elif round_phase == 'live':
                return 'l'
            else:
                return 'n'

        except KeyError:
            return 'n'

    def get_round_bomb(self, gsi_json):
        try:
            round_bomb = gsi_json['round']['bomb']

            if round_bomb == 'planted':
                return 'p'
            elif round_bomb == 'defused':
                return 'd'
            elif round_bomb == 'exploded':
                return 'e'
            else:
                return 'n'

        except KeyError:
            return 'n'

    def get_round_win_team(self, gsi_json):
        try:
            return gsi_json['round']['win_team']
        except KeyError:
            return 'n'

    #	MAP
    def get_map_team_ct_score(self, gsi_json):
        try:
            return gsi_json['map']['team_ct']['score']
        except KeyError:
            return None

    def get_map_team_t_score(self, gsi_json):
        try:
            return gsi_json['map']['team_t']['score']
        except KeyError:
            return None

    def get_map_mode(self, gsi_json):
        try:
            return gsi_json['map']['mode']
        except KeyError:
            return None

    def get_map_name(self, gsi_json):
        try:
            return gsi_json['map']['name']
        except KeyError:
            return None

    def get_map_round(self, gsi_json):
        try:
            return gsi_json['map']['round']
        except KeyError:
            return None


###################################################################
#
#					CONFIGURACION DE INICIO
#
###################################################################
serial_connected = False


# Header amarillo
def welcome_message():
    # Mensaje de inicio del programa
    os.system('cls')
    print (Style.BRIGHT + Fore.YELLOW + "************************************************************")
    print (Style.BRIGHT + Fore.YELLOW + "*                                                          *")
    print (Style.BRIGHT + Fore.YELLOW + "*             ARDUINO CSGO GAMESTATE INTEGRATION           *")
    print (Style.BRIGHT + Fore.YELLOW + "*                                                          *")
    print (Style.BRIGHT + Fore.YELLOW + "************************************************************")


#	PLAYER STATE (CURRENT ROUND)
def send_player_state_packet(packet):
    arduino.write('p,' + packet + '#')
    print(Style.BRIGHT + Fore.CYAN + ' > p,' + packet)
    time.sleep(0.15)
    response = arduino.read(2)
    print(Style.BRIGHT + Fore.GREEN + ' < ' + response)
    return True


def send_round_packet(packet):
    arduino.write('r,' + packet)
    print(Style.BRIGHT + Fore.CYAN + ' > r,' + packet)
    time.sleep(0.15)
    response = arduino.read(2)
    print(Style.BRIGHT + Fore.GREEN + ' < ' + response)
    return True


def send_player_match_stats_packet(packet):
    arduino.write('x,' + packet )
    print(Style.BRIGHT + Fore.CYAN + ' > x,' + packet)
    time.sleep(0.15)
    response = arduino.read(2)
    print(Style.BRIGHT + Fore.GREEN + ' < ' + response)
    return True


def send_map_packet(packet):
    arduino.write('m,' + packet)
    print(Style.BRIGHT + Fore.CYAN + ' > m,' + packet)
    time.sleep(0.15)
    response = arduino.read(2)
    print(Style.BRIGHT + Fore.GREEN + ' < ' + response)
    return True


# ----------------------------------------------------
def send_player_state_health(player_state_health):
    arduino.write('h' + str(player_state_health))
    print(Style.BRIGHT + Fore.CYAN + ' > h' + str(player_state_health))
    response = arduino.read(2)
    print(Style.BRIGHT + Fore.GREEN + ' < ' + response)
    return True


def send_weapon_ammo_clip(weapon_ammo_clip):
    arduino.write('a' + str(weapon_ammo_clip))
    print(Style.BRIGHT + Fore.CYAN + ' > a' + str(weapon_ammo_clip))
    response = arduino.read(2)
    print(Style.BRIGHT + Fore.GREEN + ' < ' + response)
    return True


#	PLAYER MATCH STATS
def send_player_match_stats_score(player_match_stats_score):
    arduino.write('p' + str(player_match_stats_score))
    print(Style.BRIGHT + Fore.CYAN + ' > p' + str(player_match_stats_score))
    response = arduino.read(2)
    print(Style.BRIGHT + Fore.GREEN + ' < ' + response)
    return True


def send_player_match_stats_kills(player_match_stats_kills):
    arduino.write('p' + str(player_match_stats_kills))
    print(Style.BRIGHT + Fore.CYAN + ' > p' + str(player_match_stats_kills))
    response = arduino.read(2)
    print(Style.BRIGHT + Fore.GREEN + ' < ' + response)
    return True


#	CURRENT ROUND
def send_round_bomb(round_bomb):
    if (round_bomb == 'defused'):
        arduino.write('bd')
        print(Style.BRIGHT + Fore.CYAN + ' > bd')

    elif (round_bomb == 'planted'):
        arduino.write('bp')
        print(Style.BRIGHT + Fore.CYAN + ' > bp')

    elif (round_bomb == 'exploded'):
        arduino.write('be')
        print(Style.BRIGHT + Fore.CYAN + ' > be')

    else:
        arduino.write('bn')
        print(Style.BRIGHT + Fore.CYAN + ' > bn')

    response = arduino.read(2)
    print(Style.BRIGHT + Fore.GREEN + ' < ' + response)
    return True


def send_round_phase(round_phase):
    if (round_phase == 'over'):
        arduino.write('ro')
        print(Style.BRIGHT + Fore.CYAN + ' > ro')

    elif (round_phase == 'freezetime'):
        arduino.write('rf')
        print(Style.BRIGHT + Fore.CYAN + ' > rf')

    elif (round_phase == 'warmup'):
        arduino.write('rw')
        print(Style.BRIGHT + Fore.CYAN + ' > rw')

    else:
        arduino.write('rl')
        print(Style.BRIGHT + Fore.CYAN + ' > rl')

    response = arduino.read(2)
    print(Style.BRIGHT + Fore.GREEN + ' < ' + response)
    return True


#	MAP
def send_map_team_ct_score(map_team_ct_score):
    arduino.write('c' + str(map_team_ct_score))
    print(Style.BRIGHT + Fore.CYAN + ' > c' + str(map_team_ct_score))
    response = arduino.read(2)
    print(Style.BRIGHT + Fore.GREEN + ' < ' + response)
    return True


def send_map_team_t_score(map_team_t_score):
    arduino.write('t' + str(map_team_t_score))
    print(Style.BRIGHT + Fore.CYAN + ' > t' + str(map_team_t_score))
    response = arduino.read(2)
    print(Style.BRIGHT + Fore.GREEN + ' < ' + response)
    return True


#########################################################
#
#			FLUJO PRINCIPAL DEL PROGRAMA
#
#########################################################
# Redimensionado de la ventana
os.system('mode con: cols=60 lines=15')
os.system("title " + "CSGO Gamestate Integration v1")
# Conexion a la placa arduino
while serial_connected == False:
    # Mensaje de inicio del programa
    welcome_message()

    # Buscamos placas Arduino conectadas al equipo
    time.sleep(0.5)
    print (Style.BRIGHT + Fore.CYAN + "Buscando placas Arduino conectadas al equipo...")

    # Metemos en una tupla los puertos serie que tengan conectada una placa Arduino
    arduino_ports = [
        p.device
        for p in serial.tools.list_ports.comports()
        # if 'Arduino' in p.description
    ]

    # Mostramos la cantidad de placas encontradas
    print (Style.BRIGHT + Fore.GREEN + "Encontradas " + str(len(arduino_ports)) + " placas conectadas =)")

    # S i no se encuentra ninguna, salimos del while y como serial_connected esta en false, el programa ira al inicio
    if not arduino_ports:
        print (Style.BRIGHT + Fore.RED + "No hay ninguna placa Arduino conectada =(")
        time.sleep(2)
        continue
    # Si hay mas de 1 placa arduino conectada, seleccionaremos la primera
    if len(arduino_ports) > 1:
        print (Style.BRIGHT + Fore.RED + "He encontrado varias placas Arduino conectadas, usare " + arduino_ports[0])

    # Nos conectamos a la placa seleccionada
    try:
        print (Style.BRIGHT + Fore.CYAN + "Conectando a " + arduino_ports[0])
        arduino = serial.Serial(arduino_ports[0], 250000, timeout=0.2)
        time.sleep(2)
        print (Style.BRIGHT + Fore.GREEN + "Conectado! =)")
        serial_connected = True
        time.sleep(1)
        welcome_message()

    # Si se produce algun error al intentar conectarnos cerramos el puerto serie donde se encuentre la placa seleccionada
    except:
        print (Style.BRIGHT + Fore.RED + "Se produjo un error al conectar =(")
        print (Style.BRIGHT + Fore.CYAN + "Reintentando conectar...")
        serial_connected = False
        try:
            serial.Serial(arduino_ports[0]).close()
        except:
            pass

# Una vez conectados a una placa arduino, nos quedamos a la escucha
while serial_connected == True:
    print (Style.BRIGHT + Fore.CYAN + "Iniciando CSGO Gamestate Server...")
    server = GsiServer(('localhost', 3002), GsiRequestHandler)  # make sure cfg's and this port is same
    server.init_state()
    print (Style.BRIGHT + Fore.GREEN + "CSGO Gamestate Server Escuchando =)")

    try:
        server.serve_forever()
    except (KeyboardInterrupt, SystemExit):
        pass
    server.server_close()
    serial.Serial(arduino_ports[0]).close()
    serial_connected = False
