#include "TC_IS31FL3731.h"
#include "touch.h"
#include "buzzer.h"

#define INPIN 26
#define I2C_ADDR 0x74
#define I2C_SDA 23u
#define I2C_SCL 18u
#define LED_SDB 22u

TC_IS31FL3731 tcleds = TC_IS31FL3731();
bool isActive = false;

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
  clearBar();
  if(checkTouch(START_TOUCH, TOUCH_THRESH) == 1) {
    isActive = !isActive;
    delay(300);
  }

  if(!isActive) {
    tcleds.setDisplayMode(Display_Mode_Picture);
    return;
  }

  uint16_t drankLevel = analogRead(INPIN);
  if (drankLevel>2700) {
    setBar(0b1000000, 255, 0, 0);
    playBadBoys();
  }
  if (drankLevel>2650) {
    setBar(0b0100000, 255, 108, 0);
  }
  if (drankLevel>2600) {
    setBar(0b0010000, 255, 233, 0);
  }
  if (drankLevel>2550) {
    setBar(0b0001000, 200, 238, 0);
  }
  if (drankLevel>2500) {
    setBar(0b0000100, 151, 242 ,0);
  }
  if (drankLevel>2450) {
    setBar(0b0000010, 71, 249, 0);
  }
  setBar(0b0000001, 11, 255, 0);
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

void playBadBoys() {
  flashBar(tcleds);
  uint16_t len = sizeof(badBoys) / sizeof(Tone);
  for (uint16_t i=0; i<len; i++)
  {
    tone(BUZZER_PIN, badBoys[i].note, badBoys[i].hold*60, BUZZER_CHANNEL);
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
  }
}

void flashBar(TC_IS31FL3731 ledController) {
  ledController.setAutoPlayFrames(2);
  ledController.setAutoPlayLoops(0);
  ledController.setAutoPlayDelay(175);
  ledController.setAutoPlayStart(1);

  // these should already be 0'd if this is called on startup
  ledController.setAllLEDPWM(0, 1);
  ledController.setAllLEDPWM(0, 2);

  // prepare the show
  ledController.setTextTopColor(0b1110000, 255, 0, 0, 1);
  ledController.setTextBotColor(0b1110000, 255, 0, 0, 1);
  ledController.setTextTopColor(0b0000111, 0, 0, 0, 1);
  ledController.setTextBotColor(0b0000111, 0, 0, 0, 1);

  ledController.setTextTopColor(0b0000111, 0, 0, 255, 2);
  ledController.setTextBotColor(0b0000111, 0, 0, 255, 2);
  ledController.setTextTopColor(0b1110000, 0, 0, 0, 2);
  ledController.setTextBotColor(0b1110000, 0, 0, 0, 2);

  // showtime!
  ledController.setDisplayMode(Display_Mode_Auto_Play);
}
