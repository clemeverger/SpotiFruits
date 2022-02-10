#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ESP32.h>
#include <MIDI.h>


BLEMIDI_CREATE_INSTANCE("ESPotifruit",MIDI);

const int NUMBER_OF_TOUCH_PIN = 9;
const int touchPin[NUMBER_OF_TOUCH_PIN] = {15,13,12,14,27,33,32};
bool touchPinUnlock[NUMBER_OF_TOUCH_PIN];
int touchValue[NUMBER_OF_TOUCH_PIN];

const int threshold = 20;

unsigned long t0 = millis();



const int DO = 36;
const int RE = 38;
const int MI = 40;
const int FA = 41;
const int SOL = 43;
const int LA = 45;
const int SI = 47;

 //MIDI_CREATE_DEFAULT_INSTANCE();

 //Please name your piezo.
 //The piezo named snare is connected to the A0 pin

void setup(){
  
  Serial.begin(9600);
  MIDI.begin(10);
}


int getNote(int baseNote, int octave){
  //Serial.println(baseNote, "With octave : ", octave, " returns : ",  baseNote + 12 * octave);
  return baseNote + 12 * octave;
}

void loop(){
  for(int i = 0; i < NUMBER_OF_TOUCH_PIN; i++){
    touchValue[i] = touchRead(touchPin[i]);
    if(touchValue[i] < threshold){
      if(touchPinUnlock[i] == true){

        Serial.print("detect on PIN ");
        Serial.println(touchPin[i]);

        switch(touchPin[i]) {
          case 12:
           if ((millis() - t0) > 150)
            {
               t0 = millis();
               MIDI.sendNoteOn(DO, 100, 10);
            }
           break;
           
           case 13:
           if ((millis() - t0) > 150)
            {
               t0 = millis();
               MIDI.sendNoteOn(RE, 100, 10);
            }
           break;
           
          
          case 14:
          if((millis() - t0) > 150) {
            t0 = millis();
            MIDI.sendNoteOn(MI, 100, 10);
          }
          break;
          
          case 15:
            if ((millis() - t0) > 150)
            {
              t0 = millis();
              MIDI.sendNoteOn(FA, 100, 10);
            }
           break;
          
          case 27:
           if ((millis() - t0) > 150)
            {
               t0 = millis();
               MIDI.sendNoteOn(SOL, 100, 10);
            }
           break;

       
            case 32:
              if ((millis() - t0) > 150)
               {
               t0 = millis();
               MIDI.sendNoteOn(LA, 100, 10);
              // MIDI.sendNoteOff(LA, 0, 10);
              }
           break;          


            case 33:
              if ((millis() - t0) > 150)
              {
               t0 = millis();
               MIDI.sendNoteOn(SI, 100, 10);
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
    else{
      touchPinUnlock[i] = false;
    }
  }
}
