#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ESP32.h>
#include <MIDI.h>

BLEMIDI_CREATE_INSTANCE("Spotifruits", MIDI);

const int NUMBER_OF_TOUCH_PIN = 7;
const int touchPin[NUMBER_OF_TOUCH_PIN] = {15, 13, 12, 14, 27, 33, 32};
bool touchPinUnlock[NUMBER_OF_TOUCH_PIN];
int touchValue[NUMBER_OF_TOUCH_PIN];

const int threshold = 20;

const int POTENTIOMETER = 35;
int valuePotentiometer = 0;
int octave;

unsigned long t0 = millis();

//NOTE MIDI
const int DO = 36;
const int RE = 38;
const int MI = 40;
const int FA = 41;
const int SOL = 43;
const int LA = 45;
const int SI = 47;

//LCD
const int A = 16; //YELLOW
const int B = 17;
const int C = 18;
const int D = 19;
const int E = 25;
const int F = 26;
const int G = 22;

void setup()
{
  //Initialisation
  Serial.begin(9600);
  MIDI.begin(10);

  //Définition des broches du LCD en sortie
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  //Définition de la broche du potentiomètre en entrée
  pinMode(POTENTIOMETER, INPUT);

  // Initialisation du LCD : (HIGH = ETEINDRE, LOW = ALLUMER)
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
void loop()
{
  //Récupération de l'octave sélectionné sur le potentiomètre
  valuePotentiometer = analogRead(POTENTIOMETER);
  octave = round(((7 * valuePotentiometer) / 4096) + 1);

  //Affichage de l'octave sélectionné sur le LCD
  writeOnLCD(octave);

  //Pour toutes les entrées capacitive, si l'entrée est supérieur au seuil de détection (threshold) : --> Note MIDI
  for (int i = 0; i < NUMBER_OF_TOUCH_PIN; i++)
  {
    touchValue[i] = touchRead(touchPin[i]);
    if (touchValue[i] < threshold)
    {
      if (touchPinUnlock[i] == true)
      {
        Serial.print("detect on PIN ");
        Serial.println(touchPin[i]);

        switch (touchPin[i])
        {
        case 12:
          if ((millis() - t0) > 150)
          {
            t0 = millis();
            MIDI.sendNoteOn(getNote(DO, octave), 100, 10);
          }
          break;
        case 13:
          if ((millis() - t0) > 150)
          {
            t0 = millis();
            MIDI.sendNoteOn(getNote(RE, octave), 100, 10);
          }
          break;
        case 14:
          if ((millis() - t0) > 150)
          {
            t0 = millis();
            MIDI.sendNoteOn(getNote(MI, octave), 100, 10);
          }
          break;
        case 15:
          if ((millis() - t0) > 150)
          {
            t0 = millis();
            MIDI.sendNoteOn(getNote(FA, octave), 100, 10);
          }
          break;
        case 27:
          if ((millis() - t0) > 150)
          {
            t0 = millis();
            MIDI.sendNoteOn(getNote(SOL, octave), 100, 10);
          }
          break;
        case 32:
          if ((millis() - t0) > 150)
          {
            t0 = millis();
            MIDI.sendNoteOn(getNote(LA, octave), 100, 10);
          }
          break;
        case 33:
          if ((millis() - t0) > 150)
          {
            t0 = millis();
            MIDI.sendNoteOn(getNote(SI, octave), 100, 10);
          }
          break;
        default:
          break;
        }
      }
      else
      {
        touchPinUnlock[i] = true;
      }
    }
    else
    {
      touchPinUnlock[i] = false;
    }
  }
}

//Récupère la note en fonction de l'octave sélectionné
int getNote(int baseNote, int octave)
{
  return baseNote + 12 * octave;
}

//Map les octaves sur le LCD
void writeOnLCD(int octave)
{
  switch (octave)
  {
  case 1:
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, HIGH);
    break;
  case 2:
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, HIGH);
    digitalWrite(G, LOW);
    break;
  case 3:
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    digitalWrite(E, HIGH);
    digitalWrite(F, HIGH);
    digitalWrite(G, LOW);
    break;
  case 4:
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
    break;
  case 5:
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    digitalWrite(E, HIGH);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
    break;
  case 6:
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
    break;
  case 7:
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
    break;
  default:
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
    break;
  }
}
