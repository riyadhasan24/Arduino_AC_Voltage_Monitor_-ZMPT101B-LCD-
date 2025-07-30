/* The source Code from : https://github.com/riyadhasan24
 * By Md. Riyad Hasan
 */
 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int Sensor_Pin = A0;
const int Button_Pin = 2;
const int Relay_Pin = 13;

const float Reference_Voltage = 3.3;
const int Sample_Count = 1000;

float Calibration_Factor = 240.0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  
  pinMode(Relay_Pin, OUTPUT);
  pinMode(Button_Pin, INPUT_PULLUP);

  digitalWrite(Relay_Pin, LOW);

  // LCD Setup
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("AC:        V");
}

void loop() 
{
  long Sum = 0;

  for (int i = 0; i < Sample_Count; i++) 
  {
    int Value = analogRead(Sensor_Pin);
    float Centered = (Value - 512) * (Reference_Voltage / 1023.0);
    Sum += (long)(Centered * Centered * 1000000);
    delayMicroseconds(300);
  }

  float Mean = Sum / (float)Sample_Count / 1000000.0;
  float RMS = sqrt(Mean);

  // Button-based calibration
  if (digitalRead(Button_Pin) == LOW) 
  {
    Calibration_Factor = 220.0 / RMS;
    Serial.print("Recalibrated: ");
    Serial.println(Calibration_Factor);
    lcd.setCursor(0, 1);
    lcd.print("Calibrating...  ");
    delay(2000);
  }

  float AC_Voltage = RMS * Calibration_Factor;

  // Format voltage string
  char Volt_Str[12];
  dtostrf(AC_Voltage, 7, 2, Volt_Str);

  lcd.setCursor(0, 0);
  lcd.print("AC:        V");
  lcd.setCursor(4, 0);
  lcd.print(Volt_Str);

  // Status Display and Relay Control
  lcd.setCursor(0, 1);
  lcd.print("                ");
  
  if (AC_Voltage > 230.0) 
  {
    digitalWrite(Relay_Pin, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Over Voltage");
  } 
  
  else if (AC_Voltage < 210.0) 
  {
    digitalWrite(Relay_Pin, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Low Voltage ");
  } 
  
  else 
  {
    digitalWrite(Relay_Pin, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Normal Voltage");
  }

  Serial.print("AC Voltage: ");
  Serial.println(AC_Voltage, 2);

  delay(1000);
}
