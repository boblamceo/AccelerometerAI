#include "Gesture Recognition/user_app.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#define GESTURE_ARRAY_SIZE  (6*NUM_SAMPLES+1) 

Adafruit_MPU6050 mpu;

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup(void) {
  Serial.begin(9600);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hello World!");
  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
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

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(100);
}

void loop() {
sensors_event_t a, g, temp;
   float gestureArray[GESTURE_ARRAY_SIZE]  = {0};
   // waiting
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
      
         float* result = model_run_inference(gestureArray,  
                                             GESTURE_ARRAY_SIZE, 
                                             &size_out);
         if (result && size_out) {
            if (size_out >= 2) { 
               if (result[0] > 0.5) {
                  Serial.print("Violin"); 
               } else if (result[1] > 0.5) {
                  Serial.print("Angry"); 
               } else { 
                  Serial.println("sleep");
               } 
            }
         }
     }
   }
}