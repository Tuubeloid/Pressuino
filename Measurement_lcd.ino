#include <DFRobot_LWLP.h>
#include <LiquidCrystal.h>

// Initialize the LCD with the numbers of the interface pins
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);

// Pressure sensor setup
DFRobot_LWLP lwlp;

void setup() {
  // Initialize Serial communication for debugging purposes
  Serial.begin(9600);

  // Initialize the pressure sensor
  while (lwlp.begin() != 0) {
    Serial.println("Failed to initialize the chip, please confirm the chip connection");
    delay(1000);
  }

  // Initialize the LCD with 16 columns and 2 rows
  lcd.begin(16, 2);
}

void loop() {
  DFRobot_LWLP::sLwlp_t data;

  // Get the data from the sensor
  data = lwlp.getData();

  // Clear the LCD before displaying new data
  lcd.clear();

  // Display temperature on the first row of the LCD
  lcd.setCursor(0, 0);  // Set cursor to the first row
  lcd.print("Temp C°: ");
  lcd.print(data.temperature, 2);  // Print temperature with 2 decimal places

  // Display pressure on the second row of the LCD
  lcd.setCursor(0, 1);  // Set cursor to the second row
  lcd.print("Pa: ");
  lcd.print(data.presure, 2);  // Print pressure with 2 decimal places

  // Debugging via Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(data.temperature);
  Serial.println(" C");
  Serial.print("Differential Pressure: ");
  Serial.print(data.presure);
  Serial.println(" pa");

  delay(2000);  // Wait 2 second before updating again
}
