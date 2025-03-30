#include <LiquidCrystal.h>

LiquidCrystal lcd(4, 6, 10, 11, 12, 13);

void setup() {
  Serial.begin(9600);  // Match baud rate with the transmitter
  lcd.begin(16, 2);
  lcd.print("Waiting data...");
}

void loop() {
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
}

void processData(String line) {
  // Expecting format like: T:23.45,P:101325.00
  int tIndex = line.indexOf("T:");
  int pIndex = line.indexOf(",P:");

  if (tIndex != -1 && pIndex != -1) {
    String temp = line.substring(tIndex + 2, pIndex);
    String pres = line.substring(pIndex + 3);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp C°: ");
    lcd.print(temp);

    lcd.setCursor(0, 1);
    lcd.print("Pa: ");
    lcd.print(pres);
  }
}
