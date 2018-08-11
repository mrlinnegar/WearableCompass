#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "Display.h";
#include <math.h>

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

/*
   Connections
   ===========
   BNO055
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3V DC
   Connect GROUND to common ground
*/

Adafruit_BNO055 bno = Adafruit_BNO055();
Display ledMatrix = Display();
imu::Vector<3> vector;


void displaySensorDetails(void)
{
  sensor_t sensor;
  bno.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" xxx");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" xxx");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" xxx");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void displayTemperature(void)
{

  /* Display the current temperature */
  int8_t temp = bno.getTemp();
  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println("");
}

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
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);
  while(system < 3 && mag < 3){};
}

void setup(){

void setup(){
  Serial.begin(9600);
  Serial.println("Wearable Compass"); Serial.println("");
  ledMatrix.off();
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
  displaySensorDetails();
  displayTemperature();
  displayCalStatus();


  bno.setExtCrystalUse(true);
}

// N = 338 to 22 = 22
// NE = 23 to 67 = 67
// E = 68 to 112 = 112
// SE = 113 to 157 = 157
// S = 158 to 212 = 212
// SW = 213 to 247 = 247
// W = 248 to 292 = 292
// NW = 293 to 337 = 337

// N 1 - NE 2 - E 4 - SE 8 - S 16 - SW 32 - W 64 - NW 128


int RANGE = 22;

int directionToInteger(double direction) {
  if((direction > 360 - RANGE || direction <= 0 + RANGE) && (direction > 0)) {
    return 1;
  } else if(direction >= 45 - RANGE && direction < 45 + RANGE) {
    return 2;
  } else if(direction >= 90 - RANGE && direction < 90 + RANGE) {
    return 4;
  } else if(direction >= 135 - RANGE && direction < 135 + RANGE) {
    return 8;
  } else if(direction >= 180 - RANGE && direction < 180 + RANGE) {
    return 16;
  } else if(direction >= 225 - RANGE && direction < 225 + RANGE) {
    return 32;
  } else if(direction >= 270 - RANGE && direction < 270 + RANGE) {
    return 64;
  } else if(direction >= 315 - RANGE && direction < 315 + RANGE) {
    return 128;
  } else {
    return 0;
  }
}

void loop(){
  sensors_event_t event;                   // Read 9DOF Sensor
  bno.getEvent(&event);
  Serial.print("Direction integer: ");
  Serial.println(directionToInteger(event.orientation.x), DEC);
  // displayCalStatus();
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
