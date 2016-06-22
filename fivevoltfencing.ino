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

#define EPEE_LEFTPLAYER_IN 5
#define EPEE_RIGHTPLAYER_IN 6
// EPEE inputs are pull-downed, and are followed by a 1k resistor, so current should flow to opponents! guard
#define LEFTPLAYER_OUT 9
#define RIGHTPLAYER_OUT 8
#define LEFTPLAYER_OFF 10
#define RIGHTPLAYER_OFF 11

#define BEEP_OUT 12

#define VOLT_ON 600
//times ( all in ms)
#define DOUBLE_TIME 100
// ms of a double hit (usually 40-50)
#define LIGHTON 1700
// ms of how long the light will stay on (may be ~60ish ms off but who cares
#define PAUSETIME 100
// ms of how long the pause is
#define BEEPLENGTH 800
// lenght of beep
#define CHANGETIME 1000
// time before the box starts working again  after weapon is changed :)


#define LEFT 'L'
#define RIGHT 'R'


// GLOBAL VARS

int lameRightRead=1024;
int lameLeftRead=1024;
bool weapon_change = false;
unsigned long mic = micros();




//0 = foil, 1 = saber, 2 = Epee

// protoypes
void sabre(void);
void foil(void);
void epee(void);
void update_both_lane(void);



void turn_off(void) {
  elapsedMillis sleeptime = 0;
  // keep lights on for sleeptime amount
  while (LIGHTON >= sleeptime){
    update_both_lame();
    if (sleeptime > BEEPLENGTH){
      digitalWrite(BEEP_OUT, LOW);
    }
    if (digitalRead(SWORDINTERRUPT)==0){
      weapon_change = true;
      digitalWrite(LEFTPLAYER_OUT, LOW);
      digitalWrite(RIGHTPLAYER_OUT, LOW);
      digitalWrite(LEFTPLAYER_OFF, LOW);
      digitalWrite(RIGHTPLAYER_OFF, LOW);
      return;
    }
    }
  // turn off all the lights
  digitalWrite(LEFTPLAYER_OUT, LOW);
  digitalWrite(RIGHTPLAYER_OUT, LOW);
  digitalWrite(LEFTPLAYER_OFF, LOW);
  digitalWrite(RIGHTPLAYER_OFF, LOW);
  // pause for 
  sleeptime = 0;
  while (PAUSETIME >= sleeptime){
    update_both_lame();
    if (digitalRead(SWORDINTERRUPT)==0){
      weapon_change = true;
      return;
    }
}

  


}

void setup() {

  pinMode(SWORDINTERRUPT, INPUT_PULLUP);


  pinMode(RIGHTPLAYER_OUT, OUTPUT);
  pinMode(LEFTPLAYER_OUT, OUTPUT);

  pinMode(RIGHTPLAYER_OFF, OUTPUT);
  pinMode(LEFTPLAYER_OFF, OUTPUT);
  foil_pin();



  Serial.begin(9600);
  Serial.print("Hello world.BOOLSIZE:");
  Serial.println(sizeof (bool));


 
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


void update_lame_l(void){
  if (!detect_hit(RIGHTPLAYER_WEAPON)){
      lameLeftRead = analogRead(LEFTPLAYER_LAME);
      //Serial.println("UPDATINGLEFT");
      
      }
}
void update_lame_r(void){
    if (!detect_hit(LEFTPLAYER_WEAPON)){
      lameRightRead = analogRead(RIGHTPLAYER_LAME);
  }
}

void update_both_lame(void){
  update_lame_l();
  update_lame_r();
}


void foil_pin(void){
  pinMode(LEFTPLAYER_WEAPON, INPUT_PULLUP);
  pinMode(RIGHTPLAYER_WEAPON, INPUT_PULLUP);

  pinMode(LEFTPLAYER_LAME, INPUT_PULLUP);
  pinMode(RIGHTPLAYER_LAME, INPUT_PULLUP);
}

void foil(void) {
  
  elapsedMillis timer0;
  
  while (1) {
    //time_tester();
    
    
    if (digitalRead(SWORDINTERRUPT)==0||(weapon_change)){
      delay(CHANGETIME);
      weapon_change = false;
      return;
    }
    update_both_lame(); 

    if (detect_hit(LEFTPLAYER_WEAPON)) {// Leftplayer hit something
      if (lameRightRead < VOLT_ON) {
        Serial.println(lameRightRead);
        digitalWrite(LEFTPLAYER_OUT, HIGH);
      }
      else {
        digitalWrite(LEFTPLAYER_OFF, HIGH);
      }

      // wait for a hit from rightplayer_
      timer0 = 0;
      while (timer0 <= DOUBLE_TIME) {
        update_lame_l();
        if (detect_hit(RIGHTPLAYER_WEAPON)) {
          if (lameLeftRead < VOLT_ON)
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
    
  if (detect_hit(RIGHTPLAYER_WEAPON)) { //RIghtplayer hit somting
      if (lameLeftRead < VOLT_ON) {digitalWrite(RIGHTPLAYER_OUT, HIGH);}
      else {digitalWrite(RIGHTPLAYER_OFF, HIGH);}
      
      // wait for a hit from left_player
      timer0 = 0;
      while (timer0 <= DOUBLE_TIME) {
        update_lame_r();
        if (detect_hit(LEFTPLAYER_WEAPON)) {
          // if the hit is on
          if (lameRightRead < 900)
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

  }
  
  
}
void sabre(void) {
  //
  foil();
}


bool epeeRead(int pin){
  // reads in an epee-style
  
}

// connect A to 5v, (WAS LAME BEFORE)
// B to an epee input before (WAS WEAPON BEFORE)
void epee_pins(void){
  // voltage pins: Throguh line A
  pinMode(LEFTPLAYER_LAME,OUTPUT);
  pinMode(RIGHTPLAYER_LAME,OUTPUT);
  
  // disable these pins cuz they might be interferring
  pinMode(RIGHTPLAYER_WEAPON,INPUT);
  pinMode(LEFTPLAYER_WEAPON,INPUT);

  // GROUND PINS- ALSO ABLE TO READ

  
}

void epee(void) {
  epee_pins();
  while (1) {
    if (digitalRead(SWORDINTERRUPT)==0||weapon_change){
      delay(CHANGETIME);
      return;
    }
    Serial.println(digitalRead(6));

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
