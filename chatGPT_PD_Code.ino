#include <Servo.h>

Servo blueServo;
Servo redServo;

const int blueTButton = 7;
const int bothTButton = 6;
const int redTButton = 5;

unsigned long blueEndTime = 0;
unsigned long redEndTime = 0;

bool blueSpinning = false;
bool redSpinning = false;

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600);

  pinMode(blueTButton, INPUT_PULLUP);
  pinMode(bothTButton, INPUT_PULLUP);
  pinMode(redTButton, INPUT_PULLUP);

  blueServo.attach(10);
  redServo.attach(11);

  blueServo.write(88);
  redServo.write(90);
}

void loop() {
  int blueButtonRead = digitalRead(blueTButton);
  int redButtonRead = digitalRead(redTButton);
  int bothButtonRead = digitalRead(bothTButton);
  unsigned long now = millis();

  // If any button is pressed and the corresponding servo is not already spinning
  if (blueButtonRead == LOW && !blueSpinning && bothButtonRead == HIGH) {
    int bRandSpin = random(0, 849);
    Serial.print("Blue only spin: ");
    Serial.println(bRandSpin);
    blueServo.write(180);
    blueEndTime = now + 850 + bRandSpin;
    blueSpinning = true;
  }

  if (redButtonRead == LOW && !redSpinning && bothButtonRead == HIGH) {
    int rRandSpin = random(0, 719);
    Serial.print("Red only spin: ");
    Serial.println(rRandSpin);
    redServo.write(180);
    redEndTime = now + 720 + rRandSpin;
    redSpinning = true;
  }

  if (bothButtonRead == LOW && !blueSpinning && !redSpinning) {
    int bRandSpin = random(0, 849);
    int rRandSpin = random(0, 719);
    Serial.print("Blue + Red spin: ");
    Serial.println(bRandSpin);
    Serial.print("Red + Blue spin: ");
    Serial.println(rRandSpin);

    blueServo.write(180);
    redServo.write(180);
    blueEndTime = now + 850 + bRandSpin;
    redEndTime = now + 720 + rRandSpin;
    blueSpinning = true;
    redSpinning = true;
  }

  // Stop servos when time is up
  if (blueSpinning && now >= blueEndTime) {
    blueServo.write(88);
    blueSpinning = false;
    Serial.println("Blue done");
  }

  if (redSpinning && now >= redEndTime) {
    redServo.write(90);
    redSpinning = false;
    Serial.println("Red done");
  }
}
