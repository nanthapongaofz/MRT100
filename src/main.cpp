#include <YK04_Module.h>
#include <avr/wdt.h>
#define A_PIN 5
#define B_PIN 4
#define C_PIN 2
#define D_PIN 3
#define soft_restart()
int counter = 0; int LED1 = 8; int LED2 = 9;
int ledState1 = LOW; int buttonState1 = LOW; int lastButtonState1 = HIGH; long lastDebounceTime1 = 0; long debounceDelay1 = 50;
int ledState2 = LOW; int buttonState2 = LOW; int lastButtonState2 = HIGH; long lastDebounceTime2 = 0; long debounceDelay2 = 50;
int ledState3 = LOW; int buttonState3 = LOW; int lastButtonState3 = HIGH; long lastDebounceTime3 = 0; long debounceDelay3 = 50;
YK04_Module* module;

void setup() {
  Serial.begin(9600);
  MCUSR = 0;
  pinMode(LED1, OUTPUT); pinMode(LED2, OUTPUT);
  module = new YK04_Module(A_PIN, B_PIN, C_PIN, D_PIN);
}

void Restart(){
  wdt_enable(WDTO_15MS);
  for(;;) {
  }
}

void LEDloops(){
  digitalWrite (LED2, LOW); delay(5000); digitalWrite (LED2, HIGH); delay(5);
  digitalWrite (LED1, LOW); delay(3500); digitalWrite (LED1, HIGH); delay(5);
}


void ButtonA(){
  if (module->isA() != lastButtonState1) {
    lastDebounceTime1 = millis();
    lastButtonState1 = module->isA();
  }
  if ((millis() - lastDebounceTime1) > debounceDelay1) {
    if (buttonState1 != lastButtonState1) {
      buttonState1 = lastButtonState1;
      if (buttonState1 == HIGH) {
        ledState1 = !ledState1;
        digitalWrite(LED1, ledState1);
      }
    }
  }
}

void ButtonB(){
  if (module->isB() != lastButtonState2) {
    lastDebounceTime2 = millis();
    lastButtonState2 = module->isB();
  }
  if ((millis() - lastDebounceTime2) > debounceDelay2) {
    if (buttonState2 != lastButtonState2) {
      buttonState2 = lastButtonState2;
      if (buttonState2 == HIGH) {
        ledState2 = !ledState2;
        digitalWrite(LED2, ledState2);
      }
    }
  }
}



void ButtonC(){
  if ((module->isC() == 1) && (counter <= 1)) {
    for(int ii = 0; ii <= 10000; ii++) {
      LEDloops(); delay(50); counter++;
    }
  }
}

void ButtonD(){
  if (module->isD() == 1) {
    Restart();
  }
}


void loop() {
    ButtonA(); ButtonB(); ButtonC(); ButtonD();
}
