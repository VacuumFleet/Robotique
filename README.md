# Robotique

## Getting started

You need the [Arduino IDE](https://www.arduino.cc/en/software).
Right now, this code depends on the library NewPing, which you can install through the Arduino IDE.

## choix du mode wifi hotspot ou client

Dans le mainRobot.ino, dans le setup(), modifier le parametre setIsHotspot(param).
param = true : on active le hotspot
param = false : on active le mode client

Egalement, on définit le ssidName, password, ainsi que rx, tx du module esp01
