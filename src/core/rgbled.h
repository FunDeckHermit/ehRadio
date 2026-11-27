#ifndef rgbled_h
#define rgbled_h
#pragma once
#include "options.h"
#include <Arduino.h>

#if defined(RGB_LED_PIN) && (RGB_LED_PIN!=255)
#include <Adafruit_NeoPixel.h>

#ifndef RGB_LED_ORDER
  #define RGB_LED_ORDER NEO_GRB
#endif
#define NUM_RGB_LEDS 1

class RgbLed {
public:
  RgbLed();
  void init();
  bool isInitialized();
  void set(uint8_t r, uint8_t g, uint8_t b);
  void playing(uint16_t stationId = 0);
  void stopped();
  void trackChange();
  void loop();
private:
  enum rgb_state_e { RGB_OFF=0, RGB_PLAYING=1, RGB_STOPPED=2 };
  Adafruit_NeoPixel strip;
  uint8_t flashCount;
  unsigned long lastFlash;
  bool inited;
  bool cycle;
  unsigned long lastCycle;
  uint8_t cycleState;
  rgb_state_e state;
  bool stationAnimationActive;
  uint16_t animationStationId;
  uint16_t lastStationId;
  uint8_t animationHue;
  unsigned long stationAnimationStart;
  unsigned long lastAnimationChange;
  void setStationColors(uint16_t stationId);
  void setAnimationColor(uint8_t hue);
};

#else

class RgbLed {
public:
  void init() {}
  bool isInitialized() { return false; }
  void set(uint8_t, uint8_t, uint8_t) {}
  void playing(uint16_t = 0) {}
  void stopped() {}
  void trackChange() {}
  void loop() {}
};

#endif // defined(RGB_LED_PIN) && (RGB_LED_PIN!=255)

extern RgbLed rgbled;

#endif // rgbled_h
