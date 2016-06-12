#include <elapsedMillis.h>

// the library for timings


/* pinout: TODO FINISH THIS CUZ ITS REALLY BORING!
NOT ALL PINS ARE THE SAME! try find one with less resistance so i chose 2,4,A5 amd A3
PWM ONES(THE ONES WITH A ~) are particularily bad in this regard








*/
// pins
#define SWORDINTERRUPT 7
// i ran out of pins but analog pins can output voltage soooo.... :)

#define LEFTPLAYER_WEAPON 2
#define RIGHTPLAYER_WEAPON 4
#define LEFTPLAYER_LAME A2
#define RIGHTPLAYER_LAME A5
//
#define LEFTPLAYER_OUT 9
#define RIGHTPLAYER_OUT 8
#define LEFTPLAYER_OFF 10
#define RIGHTPLAYER_OFF 11


//times ( all in ms)
#define DOUBLE_TIME 100
// ms of a double hit (usually 40-50)
#define LIGHTON 2000
// ms of how long the light will stay on (may be ~60ish ms off but who cares
#define PAUSETIME 100
// ms of how long the pause is
#define BEEPLENGTH 1500
// lenght of beep
#define CHANGETIME 1000
// time before the box starts working again  after weapon is changed :)


#define LEFT 'L'
#define RIGHT 'R'


// GLOBAL VARS
elapsedMillis timer0;
elapsedMillis sleeptime = 0;
int lameRightRead;
int lameLeftRead;

bool lockoutR = false;
bool lockoutL = false;
volatile bool weapon_change = false;
unsigned long mic = micros();



volatile int weapon_type = 0;

//0 = foil, 1 = saber, 2 = Epee

// protoypes
void sabre(void);
void foil(void);
void epee(void);


void turn_off(void) {
  bool skip_pause = false;
  int templ;
  int tempr;
  sleeptime = 0;
  while (LIGHTON >= sleeptime){
    templ = analogRead(LEFTPLAYER_LAME);
    tempr = analogRead(RIGHTPLAYER_LAME);
    
    if (!detect_hit(LEFTPLAYER_WEAPON) && !skip_pause){
      lockoutR = false;
    }
    if (!detect_hit(RIGHTPLAYER_WEAPON) && !skip_pause){
      lockoutL = false;
    }
    if (detect_hit(RIGHTPLAYER_WEAPON) && lockoutL == false){
      skip_pause = true;
      lockoutL = true;
      lameLeftRead = templ;
      
    }
    if (detect_hit(LEFTPLAYER_WEAPON) && lockoutR == false){
      skip_pause = true;
      lockoutR = true;
      lameRightRead = tempr;
      
    }
    
  }
  digitalWrite(LEFTPLAYER_OUT, LOW);
  digitalWrite(RIGHTPLAYER_OUT, LOW);
  digitalWrite(LEFTPLAYER_OFF, LOW);
  digitalWrite(RIGHTPLAYER_OFF, LOW);
  
  sleeptime = 0;
  if (!skip_pause){
  while (PAUSETIME >= sleeptime){
    if (!detect_hit(LEFTPLAYER_WEAPON)){
      lockoutR = false;
    }
    if (!detect_hit(RIGHTPLAYER_WEAPON)){
      lockoutL = false;
    }
  }
  }
  else{
    delay(PAUSETIME);
  }
    
  

  Serial.println("offlights");
}

void setup() {
  pinMode(LEFTPLAYER_WEAPON, INPUT_PULLUP);
  pinMode(RIGHTPLAYER_WEAPON, INPUT_PULLUP);
  pinMode(SWORDINTERRUPT, INPUT_PULLUP);

  pinMode(LEFTPLAYER_LAME, INPUT_PULLUP);
  pinMode(RIGHTPLAYER_LAME, INPUT_PULLUP);

  pinMode(RIGHTPLAYER_OUT, OUTPUT);
  pinMode(LEFTPLAYER_OUT, OUTPUT);

  pinMode(RIGHTPLAYER_OFF, OUTPUT);
  pinMode(LEFTPLAYER_OFF, OUTPUT);



  Serial.begin(9600);
  Serial.print("Hello world.");


 
}


bool detect_hit(int pin) {
  if (digitalRead(pin) == HIGH) {
    return true;
  }
  return false;
}

void time_tester(){
    Serial.println((micros() - mic));
    mic = micros();

}


// if the button is held down

void foil(void) {
  while (1) {
    
    
    if (digitalRead(SWORDINTERRUPT)==0){
      delay(CHANGETIME);
      return;
    }

    
    if (!lockoutL){
      lameLeftRead = analogRead(LEFTPLAYER_LAME);
    }
    if (!lockoutR){
      
      lameRightRead = analogRead(RIGHTPLAYER_LAME);
    }
    if (detect_hit(LEFTPLAYER_WEAPON) && 0) {
      lockoutL = false;
      lockoutR = true;
      // if smaller than 900, means that lame is being touched......
      if (lameRightRead < 900) {
        digitalWrite(LEFTPLAYER_OUT, HIGH);
      }
      // else it is off target
      else {
        digitalWrite(LEFTPLAYER_OFF, HIGH);
      }

      // wait for a hit
      timer0 = 0;
      while (timer0 <= DOUBLE_TIME) {
        if (detect_hit(RIGHTPLAYER_WEAPON)) {
          lockoutL = true;
          // if the hit is on
          if (analogRead(LEFTPLAYER_LAME) < 900)
          {
            digitalWrite(RIGHTPLAYER_OUT, HIGH);
            break;
          }
          else
          {
            digitalWrite(RIGHTPLAYER_OFF, HIGH);
            break;
          }
        }
      }
      turn_off();
      continue;
    }
    
  if (detect_hit(RIGHTPLAYER_WEAPON)) {
      lockoutL = true;
      lockoutR = false;
      
      // if smaller than 900, means that lame is being touched......
      if (lameLeftRead < 900) {
        digitalWrite(RIGHTPLAYER_OUT, HIGH);
      }
      // else it is off target
      else {
        digitalWrite(RIGHTPLAYER_OFF, HIGH);
      }

      // wait for a hit
      timer0 = 0;
      while (timer0 <= DOUBLE_TIME) {
        if (detect_hit(LEFTPLAYER_WEAPON)) {
          // if the hit is on
          lockoutR = true;
          if (analogRead(RIGHTPLAYER_LAME) < 900)
          {
            digitalWrite(LEFTPLAYER_OUT, HIGH);
            break;
          }
          else
          {
            digitalWrite(LEFTPLAYER_OFF, HIGH);
            break;
          }
        }
      }
      turn_off();
      continue;
    }
  lockoutL = false;
  lockoutR = false;
  //return; // TODO REMOVE
  }
  
  
}
void sabre(void) {
  foil();
}


bool epeeRead(int pin){
  // reads in an epee-style
  
}

// connect A to 5v, (WAS LAME BEFORE)
// B to an input before (WAS WEAPON BEFORE)

void epee(void) {

  pinMode(LEFTPLAYER_LAME,OUTPUT);
  pinMode(RIGHTPLAYER_LAME,OUTPUT);
  pinMode(RIGHTPLAYER_WEAPON,INPUT);
  pinMode(LEFTPLAYER_WEAPON,INPUT);
  
  while (1) {
    if (digitalRead(SWORDINTERRUPT)==0){
      delay(CHANGETIME);
      return;
    }
    Serial.println(analogRead(A4));

}
}

void loop(void) {
  Serial.println("foil");
  foil();
  Serial.println("saber");
  sabre();
  Serial.println("epee");
  epee();
  pinMode(LEFTPLAYER_LAME,INPUT_PULLUP);
  pinMode(RIGHTPLAYER_LAME,INPUT_PULLUP);
    pinMode(LEFTPLAYER_WEAPON,INPUT_PULLUP);
   pinMode(RIGHTPLAYER_WEAPON,INPUT_PULLUP);
  
  
  
}
