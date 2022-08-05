#ifndef button_h
#define button_h
#include "Arduino.h"
#include "PinChangeInterrupt.h"

class Button{
  public: 
     Button(int p, void* callback, bool isinterupt){
      pin = p;
      clickCallback = callback; 
      isInterupt = isinterupt;
     }
    ~Button(){}
    
    void ini(){
      pinMode(pin, INPUT_PULLUP); 
      if(isInterupt) attachInterrupt(digitalPinToInterrupt(pin), clickCallback, LOW );  
      else attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(pin), clickCallback, FALLING); 
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
    long clickDelay = 50;  //reduce for "gaming" response, false/extra key taps ok.
    bool isInterupt;    //3 buttons isn't enough.....this may not work
    void* clickCallback; //just need to save a pointer and the int lib will do the rest
    long doubleTapDelay = 250;  
};    
#endif
