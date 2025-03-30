#include <LiquidCrystal.h>

LiquidCrystal lcd(4, 6, 10, 11, 12, 13);

const int potMinPin = A0;
const int potMaxPin = A1;
const int buzzerPin = 7;

float minPressure = 0;
float maxPressure = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(buzzerPin, OUTPUT);
  lcd.print("Waiting data...");
}

void loop() {
  minPressure = map(analogRead(potMinPin), 0, 1023, 0, 100000);
  maxPressure = map(analogRead(potMaxPin), 0, 1023, 0, 100000);

  // Ensure min is always lower than max
  if (minPressure > maxPressure) {
    float temp = minPressure;
    minPressure = maxPressure;
    maxPressure = temp;
  }

  static String input = "";

  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      processData(input);
      input = "";
    } else {
      input += c;
    }
  }

  delay(200);
}

void processData(String line) {
  int tIndex = line.indexOf("T:");
  int pIndex = line.indexOf(",P:");

  if (tIndex != -1 && pIndex != -1) {
    String tempStr = line.substring(tIndex + 2, pIndex);
    String presStr = line.substring(pIndex + 3);

    float temp = tempStr.toFloat();
    float pressure = presStr.toFloat();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp C°: ");
    lcd.print(temp, 1);

    lcd.setCursor(0, 1);
    lcd.print("Pa: ");
    lcd.print(pressure, 0);

    if (pressure < minPressure || pressure > maxPressure) {
      digitalWrite(buzzerPin, HIGH);
    } else {
      digitalWrite(buzzerPin, LOW);
    }
  }
}
