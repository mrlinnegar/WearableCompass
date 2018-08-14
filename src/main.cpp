#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include "Display.h"
#include "Direction.h"
#include <math.h>

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS  100

Adafruit_BNO055 bno = Adafruit_BNO055();
Display ledMatrix = Display();
Direction direction = Direction();
unsigned long last_update = 0;

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

boolean isCalibrated(void){
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);
  return (system == 3 && mag == 3);
}

void waitForCalibration(void){
  ledMatrix.update(255);
  ledMatrix.display();
  digitalWrite(13, HIGH);
  while(!isCalibrated()){};
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
  pinMode(13, OUTPUT);
  ledMatrix.on();
  waitForCalibration();
  ledMatrix.off();

  bno.setExtCrystalUse(true);
}


void loop(){
  if(last_update + BNO055_SAMPLERATE_DELAY_MS <  millis()){
    sensors_event_t event;                   // Read 9DOF Sensor
    bno.getEvent(&event);
    digitalWrite(13, !isCalibrated());
    ledMatrix.update(direction.directionToInteger(event.orientation.x));
    last_update = millis();
  }
  ledMatrix.display();
}
