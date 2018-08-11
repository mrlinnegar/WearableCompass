#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include "Display.h"
#include "Direction.h"
#include <math.h>

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055();
Display ledMatrix = Display();
Direction direction = Direction();


void displayCalStatus(void)
{
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */
  /* 3 means 'fully calibrated" */
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);

  /* The data should be ignored until the system calibration is > 0 */
  Serial.print("\t");
  if (!system)
  {
    Serial.print("! ");
  }

  /* Display the individual values */
  Serial.print("Sys:");
  Serial.print(system, DEC);
  Serial.print(" G:");
  Serial.print(gyro, DEC);
  Serial.print(" A:");
  Serial.print(accel , DEC);
  Serial.print(" M:");
  Serial.println(mag, DEC);
}

void waitForCalibration(void){
  uint8_t system, gyro, accel, mag;

  while(system < 3 || mag < 3){
    system = gyro = accel = mag = 0;
    bno.getCalibration(&system, &gyro, &accel, &mag);

    Serial.print("Sys:");
    Serial.print(system, DEC);
    Serial.print(" G:");
    Serial.print(gyro, DEC);
    Serial.print(" A:");
    Serial.print(accel , DEC);
    Serial.print(" M:");
    Serial.println(mag, DEC);

    delay(100);
  };
}

void setup(){
  Serial.begin(9600);
  Serial.println("Wearable Compass"); Serial.println("");

  /* Initialise the sensor */
  if(!bno.begin(Adafruit_BNO055::OPERATION_MODE_COMPASS))
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  ledMatrix.on();
  waitForCalibration();
  ledMatrix.off();

  bno.setExtCrystalUse(true);
}


void loop(){
  sensors_event_t event;                   // Read 9DOF Sensor
  bno.getEvent(&event);
  Serial.print("Direction integer: ");
  ledMatrix.update(direction.directionToInteger(event.orientation.x));
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
