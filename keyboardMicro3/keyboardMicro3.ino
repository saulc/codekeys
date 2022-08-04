/*
                        
*/ 
#include "Keyboard.h"
#include "button.h"
 void mclick();
 void aclick();
 void bclick();
 
Button x(2, aclick, true);
Button c(3, bclick, true);
Button v(7, mclick, true);

void mclick(){ if(v.tap())  commandKey(2); }
void aclick(){ if(x.tap())  commandKey(0); }
void bclick(){ if(c.tap())  commandKey(1); }

void setup() { 
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

   //setup interupts for buttons
   v.ini();  
   c.ini(); 
   x.ini(); 

  // initialize control over the keyboard:
  Keyboard.begin();
}

int t = 0;
void loop() {  
  
//  if(t++ > 1000)    Keyboard.releaseAll(); //fixes command click after wake.!
}

void commandKey(int a){
  char c = 'x';
    switch(a){
      case 0: c = 'x';
        break;
      case 1: c = 'c';
        break;
      case 2: c = 'v';
        break;
    }
    
//    Keyboard.press(KEY_LEFT_CTRL);  // press and hold control windoz
//    Keyboard.press(KEY_LEFT_SHIFT);  //  hold Shift for testing. lol
    Keyboard.press(KEY_LEFT_GUI);  // press and hold command macos not X
    Keyboard.press(c);          // press and hold F2
    delay(11);  //fixes command click after wake.!
    Keyboard.releaseAll(); 
}
 
