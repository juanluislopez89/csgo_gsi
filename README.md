#CSGO GSI

## Requerimientos
### Arduino
Librerías de arduino:
- FastLED https://github.com/FastLED/FastLED
- TM1637 https://github.com/avishorp/TM1637

FastLED se emplea para la gestión de las tiras neopixel
TM1637 se emplea para la gastión de los displays con chip TM1637

### Python
- Python 2.7
- Librerías inclídas en requirements.txt

### Archivo de configuración gamestate_integration
[gamestate_integration_v1.cfg](https://github.com/juanluislopez89/csgo_gsi/blob/master/gamestate_integration_v1.cfg "gamestate_integration_v1.cfg")

Hay que colocarlo en la ruta de archivos de configuración de CSGO:

*C:\Program Files (x86)\Steam\steamapps\common\Counter-Strike Global Offensive\csgo\cfg*

Para hacerlo funcionar, ejecutar el archivo [csgo_gsi_connector.py](https://github.com/juanluislopez89/csgo_gsi/blob/master/python_connector/csgo_gsi_connector.py "csgo_gsi_connector.py")

El programa detectará la placa Arduino y se empezará a comunicar con ella.
Funciona en modo competitivo, tanto con bots en local como online contra niños rusos.

