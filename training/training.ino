#include "Gesture Recognition_v1/user_app.h"

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
Adafruit_MPU6050 mpu;
#define NUM_SAMPLES     50
#define NUM_GESTURES    30
#define G               9.80665f
#define ACC_THRESHOLD   (2.5f*G)
#define GESTURE_ARRAY_SIZE  (6*NUM_SAMPLES+1) 

#define GESTURE_0       0
#define GESTURE_1       1
// #define GESTURE_TARGET  GESTURE_0
#define GESTURE_TARGET  GESTURE_1 
int samplesRead   = NUM_SAMPLES;
int gesturesRead  = 0;

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
  if (!model_init()) {
      Serial.print("Failed to initialize Neuton model!");
      while (1) {
        delay(10);
      }
   }
  
  // for (int i=0; i<NUM_SAMPLES; i++) {
  //   Serial.print("aX");
  //   Serial.print(i);
  //   Serial.print(",aY");
  //   Serial.print(i);
  //   Serial.print(",aZ");
  //   Serial.print(i);
  //   Serial.print(",gX");
  //   Serial.print(i);
  //   Serial.print(",gY");
  //   Serial.print(i);
  //   Serial.print(",gZ");
  //   Serial.print(i);
  //   Serial.print(",");
  // }
  // Serial.println("target");
}
void loop() {
  sensors_event_t a, g, temp;
  
  while(gesturesRead < NUM_GESTURES) {
    // wait for significant motion
    while (samplesRead == NUM_SAMPLES) {
      // read the acceleration data
      mpu.getEvent(&a, &g, &temp);
      
      // sum up the absolutes
      float aSum = fabs(a.acceleration.x) + 
                   fabs(a.acceleration.y) + 
                   fabs(a.acceleration.z);
      
      // check if it's above the threshold
      if (aSum >= ACC_THRESHOLD) {
        // reset the sample read count
        samplesRead = 0;
        break;
      }
    }
  
    // read samples of the detected motion
    while (samplesRead < NUM_SAMPLES) {
        // read the acceleration and gyroscope data
        mpu.getEvent(&a, &g, &temp);
  
        samplesRead++;
  
        // print the sensor data in CSV format
        Serial.print(a.acceleration.x, 3);
        Serial.print(',');
        Serial.print(a.acceleration.y, 3);
        Serial.print(',');
        Serial.print(a.acceleration.z, 3);
        Serial.print(',');
        Serial.print(g.gyro.x, 3);
        Serial.print(',');
        Serial.print(g.gyro.y, 3);
        Serial.print(',');
        Serial.print(g.gyro.z, 3);
        Serial.print(',');
        // print target at the end of samples acquisition
        if (samplesRead == NUM_SAMPLES) {
          Serial.println(GESTURE_TARGET);
        }
        
        delay(10);
    }
    gesturesRead++;
  }
}