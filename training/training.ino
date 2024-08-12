#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define NUM_SAMPLES 50
Adafruit_MPU6050 mpu;
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(10);
  }
  if (!mpu.begin()) {
    while (1) {
      delay(10);
    }
  }
  
  for (int i=0; i<NUM_SAMPLES; i++) {
    Serial.print("aX");
    Serial.print(i);
    Serial.print(",aY");
    Serial.print(i);
    Serial.print(",aZ");
    Serial.print(i);
    Serial.print(",gX");
    Serial.print(i);
    Serial.print(",gY");
    Serial.print(i);
    Serial.print(",gZ");
    Serial.print(i);
    Serial.print(",");
  }
  Serial.println("target");
}