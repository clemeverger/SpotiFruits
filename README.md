![enter image description here](https://github.com/clemeverger/SpotiFruits/blob/main/logo.png?raw=true)

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

![enter image description here](https://github.com/clemeverger/SpotiFruits/blob/main/DOCUMENTATION/SCHEMATICS.png?raw=true)


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
    case 13:
	    if ((millis() - t0) > 150){ // on gère le temps à partir du moment où la touche est jouée afin de la conserver au maximum
	     t0 = millis(); // on redéclare t0 dans le cas où la touche est rejouée par l'utilisateur
	     MIDI.sendNoteOn(getNote(RE, octave), 100, 10); // on envoit la note midi au player, avec l'id MIDI, son volume et son channel
	    }

### Gestion des pins, potentiomètre et écran digit 7-segments

    const int NUMBER_OF_TOUCH_PIN = 7;
    const int touchPin[NUMBER_OF_TOUCH_PIN] = {15, 13, 12, 14, 27, 33, 32}; // pins où les instruments sont branchés 
    bool touchPinUnlock[NUMBER_OF_TOUCH_PIN];
    int touchValue[NUMBER_OF_TOUCH_PIN];
    
    const int threshold = 20; //Pour toutes les entrées capacitive, si l'entrée est supérieure au seuil de détection (threshold) : --> on envoit donc la Note MIDI
    
    const int POTENTIOMETER = 35; // pin où est connecté le potentiomètre
    int valuePotentiometer = 0

    //Récupère la note en fonction de l'octave sélectionné
    int getNote(int baseNote, int octave) // l'octave envoyée provient de la valeur du potentiomètre
    {
      return baseNote + 12 * octave;
    }


;
## Impression 3D d'une boîte 

Afin de stocker le micro-controlleur ainsi que tous les câbles nous avons en parallèle modélisé puis imprimé une boîte. Voici quelques screenshot de la modélisation.

![enter image description here](https://github.com/clemeverger/SpotiFruits/blob/main/BOITIER%203D/Capture%20d%E2%80%99e%CC%81cran%202022-02-11%20a%CC%80%2009.33.30.png?raw=true)

![enter image description here](https://github.com/clemeverger/SpotiFruits/blob/main/BOITIER%203D/Capture%20d%E2%80%99e%CC%81cran%202022-02-11%20a%CC%80%2009.34.13.png?raw=true)

![enter image description here](https://github.com/clemeverger/SpotiFruits/blob/main/BOITIER%203D/faceprint.jpeg?raw=true)
