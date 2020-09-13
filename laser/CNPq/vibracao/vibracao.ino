

#include <ArduinoJson.h>
#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Servo.h>

#define velo 13

// ADXL345 I2C address is 0x53(83)
const int MPU_addr=0x68; // I2C address of the MPU-6050


#define FIREBASE_HOST "teste-f83e2.firebaseio.com"
#define FIREBASE_AUTH "fqdzDP3KM2kG14tDnQgE0s5ORc3jYKo9cmq9TwRT"

#define N_AMOSTRAS 40

const char* ssid = "CREO";
const char* password = "CREO960507";
//static float xAccl, yAccl, zAccl;
//uint8_t ADXL345 = 0x53; // The ADXL345 sensor I2C address
int16_t X_out2 = 0, Y_out2 = 0, Z_out2 = 0;
float  X_out0 = 0, Y_out0 = 0, Z_out0 = 0, X_out1 = 0, Y_out1 = 0, Z_out1 = 0;
float razaopicoX, razaopicoY, razaopicoZ;
float numpicoX = 0, numpicoY = 0, numpicoZ = 0, i = 0, j = 0, tam = 40;
float tol = 1.2;
float tol2_x = 2, tol2_y = 3.4, tol2_z = 2.67;
bool alarmex = false, alarmey = false , alarmez = false;
int lx = 0, ly = 0, lz = 0;
int a_consecutivosX = 5, a_consecutivosY = 5, a_consecutivosZ = 5; 
//size_t byte6 = 6;
float media_x = 0.14;
float media_y = 0.05;
float media_z = 0.03;
int n_amostras = 0;
float densidades_x[N_AMOSTRAS];
float densidades_y[N_AMOSTRAS];
float densidades_z[N_AMOSTRAS];


ESP8266WebServer server(80);
//Servo ESC;     // create servo object to control the ESC
//int potValue = 0;  // value from the analog pin
//int potValueAnt = 0; // valor anterior;


float calc_media (float* arr, int n)
{
  float media = 0.0;
  for  (int i = 0; i<n ; i++)
    media += arr[i]/n;

  return media;
}

void setup()
{
  //ESC.attach(0,1000,2000); // (pin, min pulse width, max pulse width in microseconds)// D3 = 0
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.begin(9600);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);

  // Get the IP address of ESP8266
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.begin(9600); // Initiate serial communication for printing the results on the Serial monitor
  
  Wire.begin();    //inicializacao do I2C
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
}

void loop()
{
  
  //potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  
 // Serial.print(potValue);
 // Serial.print(" ");
  //potValue = map(potValue, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
  //Serial.println(potValue);
  //ESC.write(potValue);    // Send the signal to the ESC
    while(1){
      // === Read acceleromter data === //
      Wire.beginTransmission(MPU_addr);
      Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
      Wire.endTransmission(false);
      Wire.requestFrom(MPU_addr,14,true); // request a total of 14 registers
      X_out2 =Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
      float X_out2f = X_out2/16384.0; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
      Y_out2 =Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
      float Y_out2f = Y_out2/16384.0; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
      Z_out2 =Wire.read()<<8|Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
      float Z_out2f = Z_out2/16384.0; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
      if(i >= tam) break;
      if(X_out2f < 0) X_out2f = -1*X_out2f;
      if(Y_out2f < 0) Y_out2f = -1*Y_out2f;
      if(Z_out2f < 0) Z_out2f = -1*Z_out2f;
      i++;
      // =============== DETECCAO DE PICOS ======================//
      if(i >= 3 && i < tam){
        Serial.print(X_out1);
        Serial.print("---");
        Serial.print(Y_out1);
        Serial.print("---");
        Serial.println(Z_out1);
        Firebase.setFloat("valor_x",X_out1);
        Firebase.setFloat("valor_y",Y_out1);
        Firebase.setFloat("valor_z",Z_out1);
        if(X_out1 > tol*X_out0 && X_out1 > tol*X_out2f){
          numpicoX++;
          Serial.println("picoX---");
        }
        if(Y_out1 > tol*Y_out0 && Y_out1 > tol*Y_out2f){
          numpicoY++;
          Serial.println("picoY---");
        }
        if(Z_out1 > tol*Z_out0 && Z_out1 > tol*Z_out2f){
          numpicoZ++;
          Serial.println("picoZ");
        }
      }
      X_out0 = X_out1;
      X_out1 = X_out2f;
      Y_out0 = Y_out1;
      Y_out1 = Y_out2f;
      Z_out0 = Z_out1;
      Z_out1 = Z_out2f;
    }
    if(i == tam){
      razaopicoX = numpicoX/tam;
      razaopicoY = numpicoY/tam;
      razaopicoZ = numpicoZ/tam;
      Serial.print("---------razaoX: ");
      Serial.print(razaopicoX);
      Serial.print("---");
      Serial.print("razaoY: ");
      Serial.print(razaopicoY);
      Serial.print("---");
      Serial.print("razaoZ: ");
      Serial.println(razaopicoZ);
      Firebase.setFloat("razao de pico X",razaopicoX);
      Firebase.setFloat("razao de pico Y",razaopicoY);
      Firebase.setFloat("razao de pico Z",razaopicoZ);
      i = 0;
      numpicoX = 0;
      numpicoY = 0;
      numpicoZ = 0;
    }
  //delay(1);

  // ============ CALCULO DA MEDIA ========================//
  
//    potValueAnt = potValue;
    
    if(n_amostras < N_AMOSTRAS)
    {
      Serial.print("---------amostra: ");
      Serial.println(n_amostras);
      densidades_x[n_amostras] = razaopicoX;
      densidades_y[n_amostras] = razaopicoY;
      densidades_z[n_amostras] = razaopicoZ;
      n_amostras++;
    }
    else
    {
      media_x = calc_media(densidades_x, N_AMOSTRAS);
      media_y = calc_media(densidades_y, N_AMOSTRAS);
      media_z = calc_media(densidades_z, N_AMOSTRAS);
      Serial.print("---------nova media X: ");
      Serial.print(media_x);
      Serial.print("---");
      Serial.print("nova media Y: ");
      Serial.print(media_y);
      Serial.print("---");
      Serial.print("nova media Z: ");
      Serial.println(media_z);
      Firebase.setFloat("media_x", media_x);
      Firebase.setFloat("media_y", media_y);
      Firebase.setFloat("media_z", media_z);
      n_amostras = 0;
    
    }    
///////////////////////////////////////////ALARMES//////////////////////////////////////
    
    
    if(razaopicoX > media_x*tol2_x){
      Serial.print("---------alarmeX crescendo:");
      Serial.print(razaopicoX);
      Serial.print(" vs ");
      Serial.print(media_x);
      Serial.print("*");
      Serial.println(tol2_x);
      lx += 1;
    }
    else{
      Serial.println("---------alarmeX morto");
      alarmex = false;
      Firebase.setBool("alarme_x", alarmex);
      lx = 0;
    }
    if(lx >= a_consecutivosX){
      Serial.println("---------ALERTA X");
      alarmex = true;
      Firebase.setBool("alarme_x", alarmex);
    }
////////////////////////////////////////////////////////////////////////
    if(razaopicoY > media_y*tol2_y){
      Serial.print("---------alarmeY crescendo:");
      Serial.print(razaopicoY);
      Serial.print(" vs ");
      Serial.print(media_y);
      Serial.print("*");
      Serial.println(tol2_y);
      ly += 1;
    }
    else{
      Serial.println("---------alarmeY morto");
      alarmey = false;
      Firebase.setBool("alarme_y", alarmey);
      ly = 0;
    }
    if(ly >= a_consecutivosY){
      Serial.println("---------ALERTA Y");
      alarmey = true;
      Firebase.setBool("alarme_y", alarmey);
    }
//////////////////////////////////////////////////////////////////////////
    if(razaopicoZ > media_z*tol2_z){
      Serial.print("---------alarmeZ crescendo:");
      Serial.print(razaopicoZ);
      Serial.print(" vs ");
      Serial.print(media_z);
      Serial.print("*");
      Serial.println(tol2_z);
      lz += 1;
    }
    else{
      Serial.println("---------alarmeZ morto");
      alarmez = false;
      Firebase.setBool("alarme_z", alarmez);
      lz = 0;
    }
    if(lz >= a_consecutivosZ){
      Serial.println("---------ALERTA Z");
      alarmez = true;
      Firebase.setBool("alarme_z", alarmez);
    }

}
