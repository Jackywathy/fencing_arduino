#include <elapsedMillis.h>

// the library for timings


/* pinout: TODO FINISH THIS CUZ ITS REALLY BORING!

  Connect A to Lame
  Connect B to 5v
  Connect C to Input






*/



// pins
// L IS SMALLER THAN R!
#define SWORDINTERRUPT 7

// WEAPON READINS
#define LEFT_WEAPON 2
#define RIGHT_WEAPON 3
// pulldowned

// LAME READINS
#define LEFT_LAME A0
#define RIGHT_LAME A1
// pulldowned

#define VOLT_ON 800 // 800/1024 voltage is the limit for a true read.


// LED OUTS
#define L_OUT 8
#define R_OUT 9
#define L_OFF 10
#define R_OFF 11
#define BEEP_OUT 12

//times ( all in ms)
#define DOUBLE_TIME 100 // time for a double hit
#define LIGHTON 1700    // length of light will stay on, may be 100ish ms off but who cares
#define PAUSETIME 100   // length of pause time between hits
#define BEEPLENGTH 800  // length of beep
#define CHANGETIME 1000 // length of time after change weapon before starts to work

// button- pressed times:
#define FOIL_DWELL 15 // ms required to be a valid hit
#define FOIL_LOCK 300 // ms of time for the second person to hit

#define LEFT 'L'
#define RIGHT 'R'


// GLOBAL VARS
bool weapon_change = false;
unsigned long mic = micros();
elapsedMillis m_timer = 0;




//0 = foil, 1 = saber, 2 = Epee

// protoypes
void sabre(void);
void foil(void);
void epee(void);
void update_both_lane(void);




void setup() {
  pinMode(SWORDINTERRUPT, INPUT_PULLUP);

  foil_pin();



  Serial.begin(9600);
  Serial.print("Hello world.BOOLSIZE:");



}


bool detect_hit(int pin) {
  if (digitalRead(pin) == LOW) {
    return true;
  }
  return false;
}

void time_tester() {
  Serial.println((micros() - mic));
  mic = micros();

}


void foil_pin(void) {
  pinMode(LEFT_WEAPON, INPUT);
  pinMode(RIGHT_WEAPON, INPUT);

  pinMode(LEFT_LAME, INPUT);
  pinMode(RIGHT_LAME, INPUT);
}

int left_hit_time;

void foil(void) {
  // USING ALL LOCAL VARS FOR SLIGHT SPEED BOOST
  int lameR, lameL;
  bool hit_r = false, hit_l = false;   // if a hit is registered
  int left_hit_ts, right_hit_ts;       // Millisc that the sword hit (ts = timestap)
  int left_stop_ts, right_stop_ts;    // Millisec that the sword was released
  bool reset = true;
  bool lockl=false, lockr=false;
  elapsedMillis timer, temp;
  while (1) { // void loop() has extra overhead due to arduino main() also calling additional funcs.
   
    if (reset){timer = 0;} // reset the timer to prevent int. overflow
    else {reset = true;}    // a button was not pressed long enough so we have to skip the reset once.
    

    //time_tester();
    if (digitalRead(SWORDINTERRUPT) == 0) {
      delay(CHANGETIME);
      return;
    }
    if (detect_hit(RIGHT_WEAPON)) {// rplayer hit something
      //left_hit_ts = timer;
      //hit_l = true;

      if (analogRead(LEFT_LAME) > 800){digitalWrite(R_OUT, HIGH);}
      else{digitalWrite(R_OFF, HIGH);}
      
      temp = 0;
      while (temp <= FOIL_LOCK){
        if (detect_hit(LEFT_WEAPON)){
          if (analogRead(RIGHT_LAME) > 800){
            digitalWrite(L_OUT, HIGH);
            break;
          }
          else{
            digitalWrite(L_OFF, HIGH);
            break;
          }
      }
      
    }
    }

    else if (detect_hit(LEFT_WEAPON)) {// RIGHPLAYER hit something
      //right_hit_ts = timer;
      //hit_r = true;


      if (analogRead(RIGHT_LAME) > 800){digitalWrite(L_OUT, HIGH);}
      else{digitalWrite(L_OFF, HIGH);}
      
      temp = 0;
      while (temp <= FOIL_LOCK){
        if (detect_hit(RIGHT_WEAPON)){
          if (analogRead(LEFT_LAME) > 800){
            digitalWrite(R_OUT, HIGH);
            break;
          }
          else{
            digitalWrite(R_OFF, HIGH);
            break;
          }
      }
      
    }
    }
    


      /*
      right_stop_ts = left_hit + FOIL_DWELL; // make it so if button is not released, it will be equal to FOIL_PRESSED
      while (1){ // wait for FOIL_DWELL time to ensure that the hit lasts for that long 
        if(!hit_l && detect_hit(LEFT_WEAPON))){  //  if the other manages to hit, dont overright if already created
            left_hit_ts = timer;
            left_stop_ts = timer + FOIL_DWELL;
            hit_l = true;
        }

        if (!detect_hit(R_WEAPON)&&(temp < FOIL_DWELL)&&(!lockr)){// not pressed, time is smaller than ts+Foil_Dwell, no lockout
          right_stop_ts = timer;
          lockr = true;
        }

        if (hit_l && !detect_hit(L_WEAPON) && (temp < left_hit_ts + FOIL_DWELL)&&(!lockl)){
          left_stop_ts = timer;
          lockl = true;
        }
        // check that the loop still needs to run
        if (hit_l){
          if (timer >= left_hit_ts + FOIL_DWELL){break;}
        }
        else {
          if (timer >= right_hit_ts + FOIL_DWELL){break;}
        }
      }
      while (temp <= FOIL_LOCK){ // 300ms to get another hit
        if (!lockl){
          break;
        }
        if (!hit_l && detect_hit(LEFT_WEAPON)){ // iniatize hit_l
          left_hit_ts = timer;
          left_stop_ts = timer + FOIL_DWELL;
        }
        if (hit_l && !detect_hit(L_WEAPON) && (temp < left_hit_ts + FOIL_DWELL) && (!lockl)){
          left_stop_ts = timer;
          break;
        }
        if (hit_l && (temp > left_hit_ts + FOIL_DWELL)){
          break;
        }
      }

      if (right_hit_ts - right_stop_ts < FOIL_DWELL){
          hit_r = false;
      }
      if (left_hit_ts - left_stop_ts < FOIL_DWELL){
        hit_l = false;
      }
    
    */
     
      

    

}


}

void sabre(void) {
  //
  foil();
}


bool epeeRead(int pin) {
  // reads in an epee-style

}

// connect A to 5v, (WAS LAME BEFORE)
// B to an epee input before (WAS WEAPON BEFORE)
void epee_pins(void) {
  // voltage pins: Throguh line A



  // GROUND PINS- ALSO ABLE TO READ


}

void epee(void) {
  epee_pins();
  while (1) {
    if (digitalRead(SWORDINTERRUPT) == 0 || weapon_change) {
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




}
