#include <U8g2lib.h>

#define RT0 10000   // Ω
#define B 3950      // K
#define VCC 5       // Supply voltage
#define R 10000     // R=10KΩ

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

float T0 = 25 + 273.15; // Temperature T0 from datasheet, conversion from Celsius to Kelvin

float readTemperature() {
  float Read = analogRead(A0);              // Acquisition analog value Read
  float ReadVoltage = (5.00 / 1023.00) * Read; // Conversion to voltage
  float VR = VCC - ReadVoltage;
  float RT = ReadVoltage / (VR / R);               // Resistance of RT

  float ln = log(RT / RT0);
  float Temp = (1 / ((ln / B) + (1 / T0))); // Temperature from sensor

  return Temp - 273.15; // Conversion to Celsius
}

void drawTemperature(float temp) {
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB10_tr); // choose a suitable font
  u8g2.setCursor(0, 20);       // set the cursor position
  u8g2.println("Temp: ");
  u8g2.println(temp);
  u8g2.println(" C");
  u8g2.sendBuffer();           // transfer internal memory to the display
}

void setup() {
  Serial.begin(9600);
  u8g2.begin();
}

void loop() {
  float Temp = readTemperature();
  drawTemperature(Temp);

  Serial.print("Temperature:");
  Serial.print("\t");
  Serial.print(Temp);       // Conversion to c
  Serial.print("C\t\t");
  Serial.print(Temp + 273.15);        // Conversion to Kelvin
  Serial.print("K\t\t");
  Serial.print((Temp * 1.8) + 32);    // Conversion to Fahrenheit
  Serial.println("F");

  delay(1000);
}
