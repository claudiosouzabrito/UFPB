#include "Wire.h"
 
const int MPU_addr=0x68; // I2C address of the MPU-6050
 
int16_t AcX,AcY,AcZ;
 
void setup() {
Wire.begin();
Serial.begin(9600);
 
//check_I2c(MPU_addr); // Check that there is an MPU
 
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B); // PWR_MGMT_1 register
Wire.write(0); // set to zero (wakes up the MPU-6050)
Wire.endTransmission(true);
}
 
void loop() {
 
Wire.beginTransmission(MPU_addr);
Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
Wire.endTransmission(false);
Wire.requestFrom(MPU_addr,14,true); // request a total of 14 registers
AcX=Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
AcY=Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
AcZ=Wire.read()<<8|Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
Serial.print("AcX = "); Serial.print(AcX/16384.0);
Serial.print(" | AcY = "); Serial.print(AcY/16384.0);
Serial.print(" | AcZ = "); Serial.println(AcZ/16384.0);

 
delay(500); // Wait 0.5 seconds and scan again
}
 
