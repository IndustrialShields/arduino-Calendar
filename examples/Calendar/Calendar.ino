// Calendar library example
// by Industrial Shields

#include <Calendar.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600UL);

  Calendar.setTime(1597318649UL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  Calendar.update();

  static uint32_t lastTimestamp = Calendar.getTime();
  uint32_t timestamp = Calendar.getTime();
  if (lastTimestamp != timestamp) {
    lastTimestamp = timestamp;

    Serial.print("Date: ");
    Serial.print(Calendar.getYear());
    Serial.print('-');
    Serial.print(Calendar.getMonth());
    Serial.print('-');
    Serial.print(Calendar.getMonthDay());
    Serial.print(' ');
    Serial.print(Calendar.getHour());
    Serial.print(':');
    Serial.print(Calendar.getMinute());
    Serial.print(':');
    Serial.println(Calendar.getSecond());
  }
}
