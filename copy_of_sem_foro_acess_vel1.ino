#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo servoBase;
LiquidCrystal_I2C lcd(0x27, 16, 2); 

int carRed = 12;
int carYellow = 11;
int carGreen = 10;

int pedRed = 9;
int pedGreen = 8;

int button = 2;
int crossTime = 5000;
unsigned long changeTime;

int pinBuzzer = 4;

int gateOpenAngle = 0;
int gateClosedAngle = 90;

void setup() {
  servoBase.attach(5);
  servoBase.write(gateOpenAngle);

  pinMode(pinBuzzer, OUTPUT);

  pinMode(carRed, OUTPUT);
  pinMode(carYellow, OUTPUT);
  pinMode(carGreen, OUTPUT);

  pinMode(pedRed, OUTPUT);
  pinMode(pedGreen, OUTPUT);

  pinMode(button, INPUT);

  digitalWrite(carGreen, HIGH);
  digitalWrite(pedRed, HIGH);

  lcd.init();
  lcd.backlight(); 
  lcd.clear();
  lcd.print("AGUARDE...");
}

void loop() {
  int state = digitalRead(button);
  if (state == HIGH && (millis() - changeTime) > 5000) {
    changeLights();
  }
}

void beep(int freq, int onTime, int offTime) {
  tone(pinBuzzer, freq);
  delay(onTime);
  noTone(pinBuzzer);
  delay(offTime);
}

void changeLights() {
  digitalWrite(carGreen, LOW);
  digitalWrite(carYellow, HIGH);
  delay(2000);

  digitalWrite(carYellow, LOW);
  digitalWrite(carRed, HIGH);
  servoBase.write(gateClosedAngle);
  delay(1000);

  digitalWrite(pedRed, LOW);
  digitalWrite(pedGreen, HIGH);

  for (int i = crossTime / 1000; i > 0; i--) {
    lcd.clear();
    lcd.print("TRAVESSIA LIVRE");
    lcd.setCursor(0, 1);
    lcd.print("TEMPO: ");
    lcd.print(i);
    lcd.print("s");
    beep(5000, 150, 850);
  }

  for (int x = 0; x < 10; x++) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ATENCAO!");
    lcd.setCursor(0, 1);
    lcd.print("FECHANDO...");
    digitalWrite(pedGreen, HIGH);
    beep(5000, 60, 140);
    digitalWrite(pedGreen, LOW);
    delay(100);
  }

  digitalWrite(pedRed, HIGH);
  lcd.clear();
  lcd.print("PARE!");
  lcd.setCursor(0, 1);
  lcd.print("NAO ATRAVESSE");
  delay(500);

  digitalWrite(carYellow, HIGH);
  digitalWrite(carRed, LOW);
  delay(1000);

  digitalWrite(carGreen, HIGH);
  digitalWrite(carYellow, LOW);
  servoBase.write(gateOpenAngle);

  lcd.clear();
  lcd.print("AGUARDE...");

  changeTime = millis();
}