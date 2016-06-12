#include <elapsedMillis.h>

// the library for timings


/* pinout: TODO FINISH THIS CUZ ITS REALLY BORING!
NOT ALL PINS ARE THE SAME! try find one with less resistance so i chose 2,4,A5 amd A3
AVOID PINS WITH PWM CONTROL WHEN READING, CUZ THEY have slightly more resistance/








*/
// pin-ins
#define SWORDINTERRUPT 7

#define LEFTPLAYER_WEAPON 2
#define RIGHTPLAYER_WEAPON 4
#define LEFTPLAYER_LAME A2
#define RIGHTPLAYER_LAME A5


// pin-outs
#define LEFTPLAYER_OUT 9
#define RIGHTPLAYER_OUT 8
#define LEFTPLAYER_OFF 10
#define RIGHTPLAYER_OFF 11



//times
#define DOUBLE_TIME 100
// ms of a double hit (usually 40-50)
#define LIGHTON 2000
// ms of how long the light will stay on (may be ~60ish ms off but who cares
#define PAUSETIME 250
// ms of how long the pause is
#define BEEPLENGTH 1500
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


void turn_off(void) {
  delay(LIGHTON);
  digitalWrite(LEFTPLAYER_OUT, LOW);
  digitalWrite(RIGHTPLAYER_OUT, LOW);
  digitalWrite(LEFTPLAYER_OFF, LOW);
  digitalWrite(RIGHTPLAYER_OFF, LOW);

  Serial.println("offlights");
  delay(PAUSETIME);
}

void sword_choose(void) {
  if (weapon_type < 3) {
    weapon_type++;
  }
  else if (weapon_type == 3) {
    weapon_type = 0;
  }

  if (weapon_type == 0) {
    foil();
  }
  else if (weapon_type == 1) {
    sabre();
  }
  else {
    epee();
  }

}
volatile bool weapon_change = false;
unsigned long mic = micros();

void setup() {
  pinMode(LEFTPLAYER_WEAPON, INPUT_PULLUP);
  pinMode(RIGHTPLAYER_WEAPON, INPUT_PULLUP);

  pinMode(LEFTPLAYER_LAME, INPUT_PULLUP);
  pinMode(RIGHTPLAYER_LAME, INPUT_PULLUP);

  pinMode(RIGHTPLAYER_OUT, OUTPUT);
  pinMode(LEFTPLAYER_OUT, OUTPUT);

  pinMode(RIGHTPLAYER_OFF, OUTPUT);
  pinMode(LEFTPLAYER_OFF, OUTPUT);



  Serial.begin(9600);
  Serial.print("Hello world.");

  //attachInterrupt(digitalPinToInterrupt(SWORDINTERRUPT), sword_choose, RISING);

  


}


bool detect_hit(int pin) {
  if (digitalRead(pin) == HIGH) {
    return true;
  }
  return false;
}

int lameRightRead;
int lameLeftRead;
elapsedMillis sleeptime = 0;


bool lockoutR = false;
bool lockoutL = false;
// if the button is held down

void foil(void) {
  while (1) {
    //whSerial.println((micros() - mic));
    //mic = micros();
    if (weapon_change){
      weapon_change=false;
      return;
    }

    
    if (!lockoutL){
      lameLeftRead = analogRead(LEFTPLAYER_LAME);
      Serial.print("READING");
    }
    if (!lockoutR){
      
      lameRightRead = analogRead(RIGHTPLAYER_LAME);
    }
    if (detect_hit(LEFTPLAYER_WEAPON) && 0) {
      lockoutL = false;
      lockoutR = true;
      Serial.print("UNPLUGEDLET");
      // if smaller than 900, means that lame is being touched......
      if (lameRightRead < 900) {
        digitalWrite(LEFTPLAYER_OUT, HIGH);
      }
      // else it is off target
      else {
        digitalWrite(LEFTPLAYER_OFF, HIGH);
        Serial.println(lameRightRead);
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
      Serial.print("UNPLUGEDRIGET");
      Serial.println(lameLeftRead);
      lockoutL = true;
      lockoutR = false;
      
      // if smaller than 900, means that lame is being touched......
      if (lameLeftRead < 900) {
        Serial.println("HERER");
        digitalWrite(RIGHTPLAYER_OUT, HIGH);
      }
      // else it is off target
      else {
        digitalWrite(RIGHTPLAYER_OFF, HIGH);
        Serial.println(lameLeftRead);
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
  }
  
}
void sabre(void) {
  ;
}
void epee(void) {
  ;
}


void loop(void) {
  Serial.println("ENTERINGLOOP");
  if (weapon_type==0){
    foil();
  }
  else if (weapon_type == 1){
    sabre();
  }
  else{
    epee();
  }
}
