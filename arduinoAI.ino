#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#define GESTURE_ARRAY_SIZE  (6*NUM_SAMPLES+1) 
#include <neuton/neuton.h>
Adafruit_MPU6050 mpu;

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup(void) {
  Serial.begin(9600);
  neuton_nn_setup();
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
   neuton_input_t gestureArray[GESTURE_ARRAY_SIZE] = {
};
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
         neuton_inference_input_t* p_input;
p_input = neuton_nn_feed_inputs(gestureArray, neuton_nn_uniq_inputs_num() * neuton_nn_input_window_size());
if (p_input)
{
    neuton_u16_t predicted_target;
    neuton_output_t* probabilities;
    neuton_i16_t outputs_num = neuton_nn_run_inference(p_input, &predicted_target, &probabilities);

    if (outputs_num > 0)
    {
        Serial.println("Predicted target %d with probability %f\r\n", predicted_target, probabilities[predicted_target]);

        Serial.println("All probabilities:\r\n");
        for (size_t i = 0; i < outputs_num; i++)
            Serial.println("%f," probabilities[i]);
    }
}

     }
   }
}