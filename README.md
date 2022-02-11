![enter image description here](https://github.com/clemeverger/SpotiFruits/blob/main/Fichier%204.png?raw=true)

# Spotifruits

**Spotifruits** est un projet réalisé dans le cadre du M1 Développement Web à l'ECV Nantes. Clément Verger, Alexis Grenier et Douglas Ancelin ont participé à sa réalisation. 

### Concept

Grâce au micro-controlleur **ESP32** nous avons mis en place un moyen de jouer de la musique à partir de fruits (ou tout autre objet conducteur).



# Détails techniques

### Équipements utilisés

 - ESP32-WROOM-32
 - 7 résistances 1000 ohms
 - Afficheur led 1-digit 7 segments
 - 1 potentiomètre
 - Une imprimante 3D 
 - Un Mac avec GarageBand installé
 - Beaucoup de câbles...
 - Des fruits 

### Logiciels utilisés

 - Arduino IDE
 - GarageBand
 

## Utilisation du projet

L'ESP-32 devra être alimenté via USB. Pour ce qui est des branchements voici un schéma présentant les pins utilisés.

![enter image description here](https://github.com/clemeverger/SpotiFruits/blob/main/Fichier%204.png?raw=true)



## Fonctionnement interne du contrôleur 

Le contrôleur a été programmé en C++ via ArduinoIDE. Il présente quelques parties niveau code pour son bon fonctionnement qui méritent d'être éclaircies.

### Gestion de l'instance Bluetooth Low Energy (BLE) 
Afin de pouvoir envoyer des notes MIDI depuis le contrôleur vers l'ordinateur, nous les avons connecté en Bluetooth grâce à la librairie de @lathoub BLEMIDI_Transport (*https://github.com/lathoub/Arduino-BLE-MIDI*).

Une seule ligne de code suffit à instancier le contrôleur 

    BLEMIDI_CREATE_INSTANCE("ESPotifruit",MIDI);
### Gestion des notes, octaves et envoi vers GarageBand

    const int DO = 36;
    const int RE = 38;
    const int MI = 40;
    const int FA = 41;
    const int SOL = 43;
    const int LA = 45;
    const int SI = 47;
    
     MIDI.sendNoteOn(DO, 100, 10); // MIDI note, velocité, channel
     MIDI.sendNoteOn(RE, 100, 10);

## Impression 3D d'une boîte 

Afin de stocker le micro-controlleur ainsi que tous les câbles nous avons en parallèle modélisé puis imprimé une boîte. Voici quelques screenshot de la modélisation.

![enter image description here](https://github.com/clemeverger/SpotiFruits/blob/main/Capture%20d%E2%80%99e%CC%81cran%202022-02-11%20a%CC%80%2009.33.30.png?raw=true)


![enter image description here](https://github.com/clemeverger/SpotiFruits/blob/main/faceprint.jpeg?raw=true)

![enter image description here](https://github.com/clemeverger/SpotiFruits/blob/main/sideprint.jpeg?raw=true)
