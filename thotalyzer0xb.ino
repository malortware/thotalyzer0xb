#include "TC_IS31FL3731.h"

#define INPIN 26
#define I2C_ADDR 0x74
#define I2C_SDA 23u
#define I2C_SCL 18u
#define LED_SDB 22u

TC_IS31FL3731 tcleds = TC_IS31FL3731();

void setup() {
  // put your setup code here, to run once:
  pinMode(I2C_SDA, OUTPUT);
  pinMode(I2C_SCL, OUTPUT);
  pinMode(LED_SDB, OUTPUT);
  digitalWrite(LED_SDB, HIGH);

  tcleds.begin(I2C_SDA, I2C_SCL);
  
  pinMode(INPIN, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t drankLevel = analogRead(INPIN);
  clearBar();
  if (drankLevel>2700)
  {
    setBar(0b1111111, 255, 0, 0);
  } else if (drankLevel>2650)
  {
    setBar(0b0111111, 250, 150, 0);
  } else if (drankLevel>2600)
  {
    setBar(0b0011111, 150, 150, 0);
  } else if (drankLevel>2550)
  {
    setBar(0b0001111, 150, 150, 0);
  } else if (drankLevel>2500)
  {
    setBar(0b0000111, 150, 150, 0);
  } else if (drankLevel>2450)
  {
    setBar(0b0000011, 150, 150, 0);
  } else
  {
    setBar(0b0000001, 250, 150, 0);
  }
  Serial.println(drankLevel);
  delay(10);
}

void setBar(uint8_t level, uint8_t redColor, uint8_t greenColor, uint8_t blueColor)
{
  tcleds.setTextBotColor(level, redColor, greenColor, blueColor);
  tcleds.setTextTopColor(level, redColor, greenColor, blueColor);
}

void clearBar()
{
  tcleds.setTextBotColor(0x7F, 0, 0, 0);
  tcleds.setTextTopColor(0x7F, 0, 0, 0);
}
