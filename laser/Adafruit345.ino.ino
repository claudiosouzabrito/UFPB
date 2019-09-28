#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Servo.h>
 
/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

/* Set servo Motor */
Servo ServoMotor;
 
void displaySensorDetails(void)
{
   sensor_t sensor;
   accel.getSensor(&sensor);
   Serial.println("------------------------------------");
   Serial.print ("Sensor: "); Serial.println(sensor.name);
   Serial.print ("Driver Ver: "); Serial.println(sensor.version);
   Serial.print ("Unique ID: "); Serial.println(sensor.sensor_id);
   Serial.print ("Max Value: "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
   Serial.print ("Min Value: "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
   Serial.print ("Resolution: "); Serial.print(sensor.resolution); Serial.println(" m/s^2"); 
   Serial.println("------------------------------------");
   Serial.println("");
   delay(500);
}
 
void displayDataRate(void)
{
 Serial.print ("Data Rate: "); 
 
 switch(accel.getDataRate())
 {
   case ADXL345_DATARATE_3200_HZ:
   Serial.print ("3200 "); 
   break;
   case ADXL345_DATARATE_1600_HZ:
   Serial.print ("1600 "); 
   break;
   case ADXL345_DATARATE_800_HZ:
   Serial.print ("800 "); 
   break;
   case ADXL345_DATARATE_400_HZ:
   Serial.print ("400 "); 
   break;
   case ADXL345_DATARATE_200_HZ:
   Serial.print ("200 "); 
   break;
   case ADXL345_DATARATE_100_HZ:
   Serial.print ("100 "); 
   break;
   case ADXL345_DATARATE_50_HZ:
   Serial.print ("50 "); 
   break;
   case ADXL345_DATARATE_25_HZ:
   Serial.print ("25 "); 
   break;
   case ADXL345_DATARATE_12_5_HZ:
   Serial.print ("12.5 "); 
   break;
   case ADXL345_DATARATE_6_25HZ:
   Serial.print ("6.25 "); 
   break;
   case ADXL345_DATARATE_3_13_HZ:
   Serial.print ("3.13 "); 
   break;
   case ADXL345_DATARATE_1_56_HZ:
   Serial.print ("1.56 "); 
   break;
   case ADXL345_DATARATE_0_78_HZ:
   Serial.print ("0.78 "); 
   break;
   case ADXL345_DATARATE_0_39_HZ:
   Serial.print ("0.39 "); 
   break;
   case ADXL345_DATARATE_0_20_HZ:
   Serial.print ("0.20 "); 
   break;
   case ADXL345_DATARATE_0_10_HZ:
   Serial.print ("0.10 "); 
   break;
   default:
   Serial.print ("???? "); 
   break;
 } 
   Serial.println(" Hz"); 
}
 
void displayRange(void)
{
 Serial.print ("Range: +/- "); 
 
 switch(accel.getRange())
 {
   case ADXL345_RANGE_16_G:
   Serial.print ("16 "); 
   break;
   case ADXL345_RANGE_8_G:
   Serial.print ("8 "); 
   break;
   case ADXL345_RANGE_4_G:
   Serial.print ("4 "); 
   break;
   case ADXL345_RANGE_2_G:
   Serial.print ("2 "); 
   break;
   default:
   Serial.print ("?? "); 
   break;
 } 
   Serial.println(" g"); 
}

#define servo1Pin D3
#define USE_SERIAL Serial
int potServor;

void setup(void) 
{
  
 Serial.begin(460800);
 Serial.println("Accelerometer Test"); Serial.println("");
 
 /* Initialise the sensor */
 if(!accel.begin())
 {
 /* There was a problem detecting the ADXL345 ... check your connections */
 Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
 while(1);
 }
 
 /* Set the range to whatever is appropriate for your project */
 accel.setRange(ADXL345_RANGE_8_G);
 // displaySetRange(ADXL345_RANGE_16_G);
 // displaySetRange(ADXL345_RANGE_8_G);
 // displaySetRange(ADXL345_RANGE_4_G);
 // displaySetRange(ADXL345_RANGE_2_G);

 
 accel.setDataRate(ADXL345_DATARATE_3200_HZ);
 
 /* Display some basic information on this sensor */
 displaySensorDetails();
 
 /* Display additional settings (outside the scope of sensor_t) */
 displayDataRate();
 displayRange();
 Serial.println("");


  //  Servor 
  ServoMotor.attach(servo1Pin);

  Serial.println("Waiting to command turn the engine on!");

  while (USE_SERIAL.available() <= 0) {
    delay(1000); 
    ServoMotor.write(0); 
    Serial.println("Aguardando potência:");        
  }
 
  potServor = USE_SERIAL.parseInt();

  USE_SERIAL.println("Turning engine on ...");
  ServoMotor.write(0);  delay(10000);
  ServoMotor.write(20); delay(2000);
  ServoMotor.write(0);  delay(5000); 
  ServoMotor.write(potServor);  
  //
 
}
 
void loop(void) 
{
 /* Get a new sensor event */ 
 sensors_event_t event; 
 char cMsg[254]; 
 accel.getEvent(&event);
 
 /* Display the results (acceleration is measured in m/s^2) 
 Serial.print(event.acceleration.x); Serial.print(", ");
 Serial.print(event.acceleration.y); Serial.print(", ");
 Serial.print(event.acceleration.z); Serial.print(", ");
 Serial.print(potServor); Serial.print(", ");
 Serial.print(millis()); Serial.println(" "); */

 sprintf(cMsg,"%0.2f , %0.2f, %0.2f, %d, %d", event.acceleration.x, event.acceleration.y, event.acceleration.z, potServor, millis() );
 Serial.println(cMsg); 
 
 if(USE_SERIAL.available() > 0) {
   potServor = USE_SERIAL.parseInt();
   ServoMotor.write(potServor);   
  }
}
