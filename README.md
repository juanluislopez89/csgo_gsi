# CSGO GSI

![](https://media3.giphy.com/media/Qs75BqLW44RrP0x6qL/200.gif)
## Requerimientos
### Arduino
Librerías de arduino:
- FastLED https://github.com/FastLED/FastLED
- TM1637 https://github.com/avishorp/TM1637

FastLED se emplea para la gestión de las tiras neopixel
TM1637 se emplea para la gastión de los displays con chip TM1637

### Python
- Python 2.7
- Librerías includas en [requirements.txt](https://github.com/juanluislopez89/csgo_gsi/blob/master/python_connector/requirements.txt "requirements.txt")

Para instalar las librerías con el gestor pip abrimos la linea de comandos en el directorio de requirements.txt y ejecutamos:

`pip install -r requirements.txt`

***Es probable que os pida actualizar pip antes de hacer este último paso.***

### Archivo de configuración gamestate_integration
[gamestate_integration_v1.cfg](https://github.com/juanluislopez89/csgo_gsi/blob/master/gamestate_integration_v1.cfg "gamestate_integration_v1.cfg")

Hay que colocarlo en la ruta de archivos de configuración de CSGO:

*C:\Program Files (x86)\Steam\steamapps\common\Counter-Strike Global Offensive\csgo\cfg*

Para hacerlo funcionar, ejecutar el archivo [csgo_gsi_connector.py](https://github.com/juanluislopez89/csgo_gsi/blob/master/python_connector/csgo_gsi_connector.py "csgo_gsi_connector.py")

El programa detectará la placa Arduino y se empezará a comunicar con ella.
Funciona en modo competitivo, tanto con bots en local como online contra niños rusos.

## Funcionamiento
CSGO se conecta a nuestro server http en python. La url se especifica en el archivo [gamestate_integration_v1.cfg](https://github.com/juanluislopez89/csgo_gsi/blob/master/gamestate_integration_v1.cfg "gamestate_integration_v1.cfg") y en el propio código de [csgo_gsi_connector.py](https://github.com/juanluislopez89/csgo_gsi/blob/master/python_connector/csgo_gsi_connector.py "csgo_gsi_connector.py").

A lo largo de la partida, CSGO envía peticiones POST al server con un JSON que contiene los parámetros de la partida, el jugador, estadísticas...

Una vez recibida la petición, se parsea la info y se envía un paquete separado por comas a través del puerto serie a la placa Arduino.

La placa arduino mostrará la info a través de los periféricos que estén conectados a ella. (tiras neopixel y displays TM1637).
