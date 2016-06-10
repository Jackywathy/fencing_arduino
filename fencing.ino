#include <elapsedMillis.h>

// the library for timings


/* pinout: TODO FINISH THIS CUZ ITS REALLY BORING!
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
// pins
#define SWORDINTERRUPT 3

#define LEFTPLAYER_IN 5
#define RIGHTPLAYER_IN 6

#define LEFTPLAYER_OUT 8
#define RIGHTPLAYER_OUT 9

#define LEFTPLAYER_LAME 11
#define RIGHTPLAYER_LAME 12



//times
#define DOUBLE_TIME 100
// ms of a double hit (usually 40-50)
#define LIGHTON 2000
// ms of how long the light will stay on (may be ~60ish ms off but who cares
#define PAUSETIME 400
// ms of how long the pause is
#define BEEPLENGTH 3000
// lenght of beep in ms


#define LEFT 'L'
#define RIGHT 'R'


// GLOBAL VARS
elapsedMillis timer0;
volatile int weapon_type = 0;
//0 = foil, 1 = saber, 2 = Epee

// protoypes
void sabre(void);
void foil(void);
void epee(void);


int detect_player(int pin){
  // detects if the player given was hit
  if (digitalRead(pin) == LOW){
    return true;
  }
  else{
    return false;
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
    if (detect_player(test) == true){
      Serial.print(test);
      return true;
    }
  }
  return false;
  
}

void turn_off(void){
  delay(LIGHTON);
  digitalWrite(LEFTPLAYER_OUT, LOW);
  digitalWrite(RIGHTPLAYER_OUT, LOW);
  Serial.println("offlights");
  delay(PAUSETIME);
}

void sword_choose(void){
  if (weapon_type < 3){
    weapon_type++;}
  else if (weapon_type == 3){
    weapon_type = 0;
  }
  
  if (weapon_type == 0){
    foil();
  }
  else if (weapon_type == 1){
    sabre();
  }
  
}


void setup() {
  pinMode(LEFTPLAYER_OUT, OUTPUT);
  pinMode(LEFTPLAYER_IN, INPUT);
  pinMode(RIGHTPLAYER_OUT, OUTPUT);
  pinMode(RIGHTPLAYER_IN, INPUT);
  
  
  Serial.begin(9600);
  Serial.print("Hello world.");
  
  attachInterrupt(digitalPinToInterrupt(SWORDINTERRUPT),sword_choose,RISING);
  foil();// TEMP! TODO REMOVE
  
}


void foil(void){
  if (detect_player(LEFTPLAYER_IN)){
    Serial.print("UNPLUGEDLET");
    digitalWrite(LEFTPLAYER_OUT, HIGH);
    if (wait_hit(LEFT) == true){
      digitalWrite(RIGHTPLAYER_OUT, HIGH);}
 
    
    turn_off();
    
  }
  else if(detect_player(RIGHTPLAYER_IN)){
    Serial.print("UNPLUGEDRIT");
    digitalWrite(RIGHTPLAYER_OUT, HIGH);
    
    if (wait_hit(RIGHT) == true){
      digitalWrite(LEFTPLAYER_OUT, HIGH);}
    turn_off();
  }
  
}
void sabre(void){
  ;
}


void loop(){;}
