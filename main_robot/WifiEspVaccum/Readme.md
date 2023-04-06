# Librairie Connexion wifi

## Materiel

Pour arduino Mega
A utiliser avec module wifi esp8266 et adapteur wifi esp01

## Explication

Librairie utilisée : WiFiEsp

Les fonctions se trouvent dans :

WifiEspVaccum.ccp
WifiEspVaccum.h

Tous les autres fichiers (y compris dans le dossier utility) sont necessaires

## Exemple d'utilisation à mettre dans le main

Placer le dossier "WifiEspVaccum" dans le sous dossier arduino "librairies"

Dans Arduino IDE :

1. Cliquer sur Croquis
2. Inclure une bibliothèque
3. choisir WifiEspVaccum

`#include <WifiEspVaccum.h> `

`void setup() {`

`// setup_wifiEspVaccum(String ssidName, String ssidPassword, int rx, int tx)`

`setup_wifiEspVaccum("testnewbiblioName","testnewbiblioPass",12,50);`

`}`

`void loop() {`

`// put your main code here, to run repeatedly:`

`wifiEspVaccum()`

`}`