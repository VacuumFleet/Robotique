# Librairie wifi hotspot

## Materiel

Pour arduino Mega
A utiliser avec module wifi esp8266 et adapteur wifi esp01

## Explication

Les fonctions se trouvent dans :

hotspotWifi.ccp
hotspotWifi.h

Tous les autres fichiers (y compris dans le dossier utility) sont necessaires

## Exemple d'utilisation à mettre dans le main

Placer le dossier "hotspotWifi" dans le sous dossier arduino "librairies"

Dans Arduino IDE :

1. Cliquer sur Croquis
2. Inclure une bibliothèque
3. choisir hotspotWifi

`#include <hotspotWifi.h> `

`void setup() {`

`// setupHotspot(String ssidName, String ssidPassword, int rx, int tx);`

`setupHotspot("testnewbiblioName","testnewbiblioPass",12,50);`

`}`

`void loop() {`

`// put your main code here, to run repeatedly:`

`hotspotLoop()`

`}`
