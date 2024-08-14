#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "src/Gesture Recognition_v1/user_app.h"

#define NUM_SAMPLES         50
#define G                   9.80665f
#define ACC_THRESHOLD       (2.5f*G)        
#define GESTURE_ARRAY_SIZE  (6*NUM_SAMPLES+1) 

int   samplesRead                       = NUM_SAMPLES;
float gestureArray[GESTURE_ARRAY_SIZE]  = {0};

Adafruit_MPU6050 mpu;
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup(void) {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Hello World!");
  while (!Serial) {
    delay(10);
  }
  if (!mpu.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  if (!model_init()) {
    Serial.print("Failed to initialize Neuton model!");
    while (1) {
      delay(10);
    }
  }
}

void loop() {
sensors_event_t a, g, temp;
  while (samplesRead == NUM_SAMPLES) {
    mpu.getEvent(&a, &g, &temp);
    
    float aSum = fabs(a.acceleration.x) + fabs(a.acceleration.y) + fabs(a.acceleration.z);
    
    if (aSum >= ACC_THRESHOLD) {
      samplesRead = 0;
      break;
    }
  }

  while (samplesRead < NUM_SAMPLES) {
    mpu.getEvent(&a, &g, &temp);

    gestureArray[samplesRead*6 + 0] = a.acceleration.x;
    gestureArray[samplesRead*6 + 1] = a.acceleration.y;
    gestureArray[samplesRead*6 + 2] = a.acceleration.z;
    gestureArray[samplesRead*6 + 3] = g.gyro.x;
    gestureArray[samplesRead*6 + 4] = g.gyro.y;
    gestureArray[samplesRead*6 + 5] = g.gyro.z;
    
    samplesRead++;
    
    delay(10);

    if (samplesRead == NUM_SAMPLES) {
      uint32_t size_out = 0;
      
      float* result = model_run_inference(gestureArray, GESTURE_ARRAY_SIZE, &size_out);

      if (result && size_out) {
        if (size_out >= 2) { 
          Serial.println("yup");
          if (result[0] > result[1]) {
            Serial.print("Punch");
            Serial.print("[Accuracy: ");
            Serial.print(result[0]);
            Serial.println("]");
          } else if (result[0] < result[1]) {
            Serial.print("Violin");
            Serial.print("[Accuracy: ");
            Serial.print(result[1]);
            Serial.println("]");
          }  else {
            Serial.print("nuh uh");
            
          }
        } else {
          Serial.println("not valid");
        }
      } else {
        Serial.println("fail to execute");
      }
    }
  }
}
