#include <Adafruit_NeoPixel.h>

#define  LED_PIN   6
#define LED_COUNT 66

#define BUTTON 10

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);



uint32_t green = strip.Color(100, 0, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t red = strip.Color(0, 255, 0);
uint32_t white = strip.Color(255, 255, 255);

int val;
int oldModus;
bool anzeige;
int buttonState = 0;
int n = 1;
int positionLED = 0;
int blockLED = 5;


int count;
int speedDelay;

void setup() {
  strip.begin();
  strip.clear();
  Serial.begin(9600);

  pinMode(BUTTON, INPUT_PULLUP);

randomSeed(analogRead(A0));

}


void loop() {



  int vorwahl = ButtonState();
  if (oldModus != vorwahl) {
    oldModus = vorwahl;
    anzeige = true;
  }
  else {
    anzeige = false;
  }

  switch (vorwahl) {

    case 1:
      ModusChange(vorwahl);
      Modus1();
      //Serial.println("Case1");
      break;

    case 2:
      ModusChange(vorwahl);
      Modus2();
      //Serial.println("Case2");
      break;

    case 3:
      ModusChange(vorwahl);
      Modus3();
      //Serial.println("Case3");
      break;

    default:
      strip.clear();
      //Serial.println("Default");
      break;
  }
}

void Modus1() {

  strip.fill(green);
  strip.show();
  count = 20;
  speedDelay = 50;
  for (int i = 0; i < count; i++) {
    strip.setPixelColor(random(LED_COUNT), random(0, 255), random(0, 255), random(0, 255));
    strip.show();
    delay(speedDelay);
  }
  delay(speedDelay);
}

void Modus2() {

  strip.fill(green);
  strip.show();
  count = 20;
  speedDelay = random(150,400);
  int pixel = random(LED_COUNT);
  strip.setPixelColor(pixel,255,255,255);
  strip.show();
  delay(speedDelay);
  

  
}
void Modus3() {

  strip.fill(green);
  //strip.show();
  blockLED=positionLED+5;
  for(int k=positionLED;k<=blockLED;k++){
    Serial.print("k= ");
    Serial.println(k);
    strip.setPixelColor(k,255,0,0);
  }
  strip.show();
  positionLED++;
  if(positionLED>LED_COUNT){
    positionLED=0;
  }
  Serial.println(positionLED);
  delay(25
  );
}


void ModusChange(int i) {
  int j = 1;
  if (anzeige) {
    while (j <= i) {
      strip.fill(white);
      strip.show();
      delay(250);
      strip.clear();
      strip.show();
      delay(250);
      j++;
    }
  }
}


int ButtonState () {

  if (digitalRead(BUTTON) == LOW) {
    n++;
  }
  if (n > 3) {
    n = 1;
  }
  //Serial.println(n);
  return n;

}
