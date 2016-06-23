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
#define FOIL_PRESSED 14 // ms required to be a valid hit

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



void turn_off(void) {
  elapsedMillis sleeptime = 0;
  // keep lights on for sleeptime amount
  while (LIGHTON >= sleeptime) {
    update_both_lame();
    if (sleeptime > BEEPLENGTH) {
      digitalWrite(BEEP_OUT, LOW);
    }
    if (digitalRead(SWORDINTERRUPT) == 0) {
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
  while (PAUSETIME >= sleeptime) {
    update_both_lame();
    if (digitalRead(SWORDINTERRUPT) == 0) {
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
  pinMode(LEFTPLAYER_WEAPON, INPUT);
  pinMode(RIGHTPLAYER_WEAPON, INPUT);

  pinMode(LEFTPLAYER_LAME, INPUT);
  pinMode(RIGHTPLAYER_LAME, INPUT);
}

int left_hit_time;

void foil(void) {

  int lameR, lameL;
  elapsedMillis timer;
  while (1) {
    timer = 0;
    lameR = analogRead(RIGHT_LAME);
    lameL = analogRead(LEFT_LAME);
    //time_tester();
    if (digitalRead(SWORDINTERRUPT) == 0) {
      delay(CHANGETIME);
      return;
    }
    if (detect_hit(LEFTPLAYER_WEAPON)) {// Leftplayer hit something
      left_hit =

    }
    turn_off();
    continue;
  }

  if (detect_hit(RIGHTPLAYER_WEAPON)) { //RIghtplayer hit somting
    if (lameLeftRead < VOLT_ON) {
      digitalWrite(RIGHTPLAYER_OUT, HIGH);
    }
    else {
      digitalWrite(RIGHTPLAYER_OFF, HIGH);
    }

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


bool epeeRead(int pin) {
  // reads in an epee-style

}

// connect A to 5v, (WAS LAME BEFORE)
// B to an epee input before (WAS WEAPON BEFORE)
void epee_pins(void) {
  // voltage pins: Throguh line A
  pinMode(LEFTPLAYER_LAME, OUTPUT);
  pinMode(RIGHTPLAYER_LAME, OUTPUT);

  // disable these pins cuz they might be interferring
  pinMode(RIGHTPLAYER_WEAPON, INPUT);
  pinMode(LEFTPLAYER_WEAPON, INPUT);

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
  pinMode(LEFTPLAYER_LAME, INPUT_PULLUP);
  pinMode(RIGHTPLAYER_LAME, INPUT_PULLUP);
  pinMode(LEFTPLAYER_WEAPON, INPUT_PULLUP);
  pinMode(RIGHTPLAYER_WEAPON, INPUT_PULLUP);



}
