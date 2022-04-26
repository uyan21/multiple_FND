#include <stdint.h>
#include <Arduino.h>
#include "FndDisplay.h"
uint8_t dec[] = {
  0x3f,//0
  0x06,//1
  0x5b,//2
  0x4f,//3
  0x66,//4
  0x6d,//5
  0x7d,//6
  0x07,//7
  0x7f,//8
  0x6f,//9
};

FndDisplay::FndDisplay(uint8_t clk, uint8_t dio) {
  m_clk = clk;
  m_dio = dio;
}
void FndDisplay::start() {
  pinMode(m_dio, OUTPUT);
  delayMicroseconds(50);
}
void FndDisplay::stop() {
  pinMode(m_dio, OUTPUT);
  delayMicroseconds(50);
  pinMode(m_clk, INPUT);
  delayMicroseconds(50);
  pinMode(m_dio, INPUT);
  delayMicroseconds(50);
}
bool FndDisplay::writeByte(uint8_t b) {
  uint8_t data = b;
  for (uint8_t i = 0; i < 8; i++) {
    pinMode(m_clk, OUTPUT);
    delayMicroseconds(50);
    if (data & 0x01)
      pinMode(m_dio, INPUT);
    else
      pinMode(m_dio, OUTPUT);

    delayMicroseconds(50);
    pinMode(m_clk, INPUT);
    delayMicroseconds(50);
    data >>= 1;

  }
  pinMode(m_clk, OUTPUT);
  pinMode(m_dio, INPUT);
  delayMicroseconds(50);

  pinMode(m_clk, INPUT);
  delayMicroseconds(50);

  uint8_t ack = digitalRead(m_dio);
  if (ack == 0)
    pinMode(m_dio, OUTPUT);
  delayMicroseconds(50);
  pinMode(m_clk, OUTPUT);
  delayMicroseconds(50);
  return ack;
}
int FndDisplay::writeNumber(int number) {
  uint8_t pos[] = { 0, 0, 0, 0 };
  start();
  writeByte(0x40);
  stop();

  start();
  writeByte(0xC0);
  pos[3] = round(number / 1000);
  pos[2] = round((number % 1000) / 100);
  pos[1] = round((number % 100) / 10);
  pos[0] = round((number % 10));
  for (int n = 0; n < 4; n++) {
    writeByte(dec[pos[n]]);
  }
  stop();

  start();
  writeByte(0x80 + 0x0f);
  stop();
  return 0;
}
