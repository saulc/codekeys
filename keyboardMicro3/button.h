#ifndef button_h
#define button_h
#include "Arduino.h"

class Button{
  public: 
     Button(int p, void* callback, bool isinterupt=false){
      pin = p;
      clickCallback = callback;
      isInterupt = isinterupt;
     }
    ~Button(){}
    
    void ini(){
      pinMode(pin, INPUT_PULLUP); 
      if(isInterupt) attachInterrupt(digitalPinToInterrupt(pin), clickCallback, LOW );  
      else  attachInterrupt( pin, clickCallback, LOW );  
    }
    //basic debounce//maybe add a double tap?
    bool tap(){
      long temp  = millis(); 
      if(temp - lastClick > clickDelay){ //if(temp-lastClick < doubleTapDelay) ? that easy?
        lastClick = millis();   
        return true;
      }
      return false; 
    }
  
  private:
    int pin = 0;
    long lastClick = 0; // for 3 interupt micros.
    long clickDelay = 50;  
    bool isInterupt;
    void* clickCallback;

};    
#endif
