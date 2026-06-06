#pragma once

#include <Arduino.h>
#include <helpers/ESP32Board.h>

// LilyGo LoRa32 T3 V1.6.1 (ESP32 + SX1276/SX1278)
class LilyGoLoRa32T3V161Board : public ESP32Board {
public:
  void begin() {
    // Deselect LoRa and SD before any SPI/I2C init. An inserted SD card can
    // otherwise interfere with boot when CS is not driven.
    pinMode(P_LORA_NSS, OUTPUT);
    digitalWrite(P_LORA_NSS, HIGH);
    pinMode(P_BOARD_SPI_CS, OUTPUT);
    digitalWrite(P_BOARD_SPI_CS, HIGH);

    ESP32Board::begin();
  }

  const char* getManufacturerName() const override {
    return "LilyGo LoRa32 T3 V1.6.1";
  }

  uint16_t getBattMilliVolts() override {
    analogReadResolution(12);

    uint32_t raw = 0;
    for (int i = 0; i < 8; i++) {
      raw += analogReadMilliVolts(PIN_VBAT_READ);
    }
    raw = raw / 8;

    return (2 * raw);
  }
};
