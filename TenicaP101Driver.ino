/*
  Blink
  Turns on an clk on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
#define V(var) var?LOW:HIGH
#define ON(var) digitalWrite(var,LOW);
#define OFF(var) digitalWrite(var,HIGH);
// Pin 13 has an clk connected on most Arduino boards.
// give it a name:
int CLK = 10;
int Y6 = 8;
int SIN = 9;
int clk = 0;
int xxx = 0;
boolean matrix[7][95];
int list[] = {2,3,4,5,6,7,8,9,10};

int listlen = 9;
int LED = 13;
int xdir = 1;
int ydir = 0;
int xmax = 94;
int ymax = 6;
int ymin = 1;
int xmin = 0;
int atX = 0;
int cnt = 0;
int atY = 0;
unsigned int i = 0;
unsigned int j = 0;
// the setup routine runs once when you press reset:
void setup() {
  for ( i = 0; i < listlen; i++) {
    pinMode(list[i], OUTPUT);
     OFF(list[i]);
  }
}

// the loop routine runs over and over again forever:
void loop() {
  cnt++;
  atX += xdir;
  atY += ydir;
  if (atX == xmax && xdir == 1) {
    xmax--;
    xdir = 0;
    ydir = 1;
  }
  if (atY == ymax && ydir == 1) {
    ymax--;
    ydir = 0;
    xdir = -1;
  }
  if (atY == ymin && ydir == -1) {
    ymin++;
    ydir = 0;
    xdir = 1;
  }
  if (atX == xmin && xdir == -1) {
    xmin++;
    xdir = 0;
    ydir = -1;
  }
  if (cnt >= 7*95) {
    xdir = 1;
    ydir = 0;
    cnt  =0;
    atY = 0;
    atX = 0;
    xmax = 94;
    ymax = 6;
    ymin = 1;
    xmin = 0;
  }
  matrix[atY][atX] = !matrix[atY][atX];
  for (int x = 0; x < 7; x++) {
    for (i = 0; i < 95; i++) {
      if (!matrix[x][i]) {
        ON(SIN);
      } else {
        OFF(SIN);
      }
      tick(0);
    }
    ON(list[x]);
    delayMicroseconds(500);
    OFF(list[x]);
  }
}
void sintick(int d) {
  digitalWrite(SIN,LOW);
  tick(d);
  digitalWrite(SIN,HIGH);
  delay(d);
}
void tick(int d) {
  digitalWrite(CLK,LOW);
  digitalWrite(CLK,HIGH);
}
