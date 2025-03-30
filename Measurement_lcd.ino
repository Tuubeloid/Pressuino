#include <DFRobot_LWLP.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(4, 6, 10, 11, 12, 13);

DFRobot_LWLP lwlp;

void setup() {
  Serial.begin(9600);

  while (lwlp.begin() != 0) {
    Serial.println("Failed to initialize the chip, please confirm the chip connection");
    delay(1000);
  }

  lcd.begin(16, 2);
}

void loop() {
  DFRobot_LWLP::sLwlp_t data;

  data = lwlp.getData();

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Temp C°: ");
  lcd.print(data.temperature, 2);

  lcd.setCursor(0, 1);
  lcd.print("Pa: ");
  lcd.print(data.presure, 2);

  Serial.print("Temperature: ");
  Serial.print(data.temperature);
  Serial.println(" C");
  Serial.print("Differential Pressure: ");
  Serial.print(data.presure);
  Serial.println(" pa");

  delay(2000);
}
