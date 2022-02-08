#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ESP32.h>

BLEMIDI_CREATE_INSTANCE("SpotiFruits",MIDI);  
int tempo = 280;

const int NUMBER_OF_TOUCH_PIN = 9;
const int touchPin[NUMBER_OF_TOUCH_PIN] = {4,2,15,13,12,14,27,33,32}; 
bool touchPinUnlock[NUMBER_OF_TOUCH_PIN];
int touchValue[NUMBER_OF_TOUCH_PIN];

const int threshold = 20;

void setup(){
  Serial.begin(9600);
  MIDI.begin(10);
}
void loop(){
  for(int i = 0; i < NUMBER_OF_TOUCH_PIN; i++){
    touchValue[i] = touchRead(touchPin[i]);
    if(touchValue[i] < threshold){
      if(touchPinUnlock[i] == true){
    
        MIDI.sendNoteOn(36, 100, 10);
        MIDI.sendNoteOff(36, 0, 10);
        MIDI.sendNoteOn(44, 100, 10);
        MIDI.sendNoteOff(44, 0, 10);
        delay(tempo);
    
        MIDI.sendNoteOn(44, 100, 10);
        MIDI.sendNoteOff(44, 0, 10);
        delay(tempo);
    
        MIDI.sendNoteOn(38, 100, 10);
        MIDI.sendNoteOff(38, 0, 10);
        MIDI.sendNoteOn(44, 100, 10);
        MIDI.sendNoteOff(44, 0, 10);
        delay(tempo);
    
        MIDI.sendNoteOn(44, 100, 10);
        MIDI.sendNoteOff(44, 0, 10);
        delay(tempo);

        Serial.print("detect on PIN ");
        Serial.println(touchPin[i]);
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

 
