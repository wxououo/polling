#define C3  131
#define CS3 139
#define D3  147
#define DS3 156
#define E3  165
#define F3  175
#define FS3 185
#define G3  196
#define GS3 208
#define A3  220
#define AS3 233
#define B3  247
#define C4  262
#define CS4 277
#define D4  294
#define DS4 311
#define E4  330
#define F4  349
#define FS4 370
#define G4  392
#define GS4 415
#define A4  440
#define AS4 466
#define B4  494
#define C5  523
#define CS5 554
#define D5  587
#define DS5 622
#define E5  659
#define F5  698
#define FS5 740
#define G5  784
#define GS5 831
#define A5  880

byte i = 0, j = 0;
byte pins[] = {13, 12, 11, 10, 9, 8, 7};
byte show[10][7] = {
  {0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 1, 1, 1, 1},
  {0, 0, 1, 0, 0, 1, 0},
  {0, 0, 0, 0, 1, 1, 0},
  {1, 0, 0, 1, 1, 0, 0},
  {0, 1, 0, 0, 1, 0, 0},
  {1, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0},
};
int melody1[] = {FS5,G5,FS5,E5,D5,E5,D5,C5,B4,D5,B4,C5,A4,B4,G4,A4,0,E4,E4,FS4,G4,FS4,G4,FS4,E4,0};
int melody2[] = {
E5,D5,A4,F4,E5,D5,A4,F4,0,C5,AS4,F4,D4,C5,AS4,F4,AS4,A4,F4,D4,AS3,A3,AS3,C4,D4,E4,F4,G4,A4,0};
int noteDur1[] = {4,8,12,16,12,8,8,8,8,8,8,8,8,8,8,8,32,8,12,4,8,4,4,8,4,2};
int noteDur2[] = {4,8,4,4,4,8,4,4,16,4,8,4,4,4,8,2,4,4,4,4,4,6,4,4,4,4,4,4
};
int thisNote1 = 0, thisNote2 = 0, thisNum = -1;
long t1lastTime = 0, t1nowTime = 0, t1pauseTime = 0;
long t2lastTime = 0, t2nowTime = 0, t2pauseTime = 0;
long clastTime = 0, cnowTime = 0, cpauseTime = 0;

void setup() {
  for(i = 0; i < 7; i++) {
    pinMode(pins[i], OUTPUT);
  }
  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  for(j = 0; j < 7; j++) {
      digitalWrite(pins[j], show[0][j]);
  }
}

void checkToPlay() {
  if(digitalRead(4)) {
    t1nowTime = millis();
    if(t1nowTime - t1lastTime >= t1pauseTime) {
      if(thisNote1 > 26) {
        thisNote1 = 0;
      }
      tone(6, melody1[thisNote1], 1000 / noteDur1[thisNote1]);
      t1pauseTime = 1000 / noteDur1[thisNote1] * 1.2;
      t1lastTime = millis();
      thisNote1++;
    }
  }
  else {
    t2nowTime = millis();
    if(t2nowTime - t2lastTime >= t2pauseTime) {
      if(thisNote2 > 28) {
        thisNote2 = 0;
      }
      tone(6, melody2[thisNote2], 1000 / noteDur2[thisNote2]);
      t2pauseTime = 1000 / noteDur2[thisNote2] * 1.2;
      t2lastTime = millis();
      thisNote2++;
    }
  }
}

void counting() {
  cnowTime = millis();
  if(cnowTime - clastTime >= 500) {
    thisNum += digitalRead(5) + (digitalRead(5) - 1);
    if(thisNum > 9) {
      thisNum = 0;
    }
    else if(thisNum < 0) {
      thisNum = 9;
    }
    for(j = 0; j < 7; j++) {
      digitalWrite(pins[j], show[thisNum][j]);
    }
    clastTime = millis();
  }
}

void loop() {
  counting();
  checkToPlay();
}
