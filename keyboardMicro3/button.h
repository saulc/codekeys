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
    int tap(){
      long temp  = millis() - lastClick; 
      if(temp  > clickDelay){ 
        lastClick = millis();   
          if(temp  < doubleTapDelay)  return 2;
        return 1;
      }
      return 0; 
    } 
    
  private:
    int pin = 0;
    long lastClick = 0; // for 3 interupt micros.
    long clickDelay = 50;  
    bool isInterupt;
    void* clickCallback; 
    long doubleTapDelay = 250;  
};    
#endif
