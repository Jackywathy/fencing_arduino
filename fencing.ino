#include <elapsedMillis.h>

// the library for timings


/* pinout:
 *  
 *  
 *  
 *  
 *  
 *  
 *  
 *  
 *  
 *  
 */
#define LEFTPLAYER_IN 6
#define RIGHTPLAYER_IN 7
#define LEFTPLAYER_OUT 12
#define RIGHTPLAYER_OUT 11
#define DOUBLE_TIME 100
// ms of a double hit (usually 40-50)
#define LIGHTON 2400
// ms of how long the light will stay on (may be ~60ish ms off but who cares
#define PAUSETIME 400
// ms of how long the pause is
#define TRUE 1
#define FALSE 0
#define BEEPLENGTH 3000
// lenght of beep in ms
#define LEFT 'L'
#define RIGHT 'R'
elapsedMillis timer0;

int detect_player(int pin){
  // detects if the player given was hit
  if (digitalRead(pin) == LOW){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

int wait_hit(int player){
  // returns true if both sides got hit in DOUBLE_TIME time
  int test;
  if (player == LEFT){
    test = RIGHTPLAYER_IN;
  }
  else{
    test = LEFTPLAYER_IN;
  }

 
  timer0 = 0;
  while (timer0 <= DOUBLE_TIME){
    if (detect_player(test) == TRUE){
      Serial.print(test);
      return TRUE;
    }
  }
  return FALSE;
  
}

void turn_off(void){
  delay(LIGHTON);
  digitalWrite(LEFTPLAYER_OUT, LOW);
  digitalWrite(RIGHTPLAYER_OUT, LOW);
  Serial.println("offlights");
  delay(PAUSETIME);
}


void setup() {
  pinMode(LEFTPLAYER_OUT, OUTPUT);
  pinMode(LEFTPLAYER_IN, INPUT);
  pinMode(RIGHTPLAYER_OUT, OUTPUT);
  pinMode(RIGHTPLAYER_IN, INPUT);
  
  
  Serial.begin(9600);
  Serial.print("Hello world.");
  
}

void loop() {
  if (detect_player(LEFTPLAYER_IN)){
    Serial.print("UNPLUGEDLET");
    digitalWrite(LEFTPLAYER_OUT, HIGH);

    if (wait_hit(LEFT) == TRUE){
      digitalWrite(RIGHTPLAYER_OUT, HIGH);}
 
    
    turn_off();
    
  }
  else if(detect_player(RIGHTPLAYER_IN)){
    Serial.print("UNPLUGEDRIT");
    digitalWrite(RIGHTPLAYER_OUT, HIGH);
    
    if (wait_hit(RIGHT) == TRUE){
      digitalWrite(LEFTPLAYER_OUT, HIGH);}
    turn_off();
  }

  }

  /*
  // will become left player hit soon!
  buttonState = digitalRead(7);
  Serial.print(buttonState);

  if (buttonState == LOW) {
    digitalWrite(LEFTPLAYER_OUT, HIGH);
  } 
  else {
    digitalWrite(LEFTPLAYER_OUT, LOW);
  }
}
*/
