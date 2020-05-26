

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
#define Addr 0x53


#define FIREBASE_HOST "teste-f83e2.firebaseio.com"
#define FIREBASE_AUTH "fqdzDP3KM2kG14tDnQgE0s5ORc3jYKo9cmq9TwRT"

#define N_AMOSTRAS 1000

const char* ssid = "Moto G (5S) 6261";
const char* password = "123oliveira4";
//static float xAccl, yAccl, zAccl;
uint8_t ADXL345 = 0x53; // The ADXL345 sensor I2C address
int16_t X_out2 = 0, Y_out2 = 0, Z_out2 = 0;
float  X_out0 = 0, Y_out0 = 0, Z_out0 = 0, X_out1 = 0, Y_out1 = 0, Z_out1 = 0;
float razaopicoX, razaopicoY, razaopicoZ;
float numpicoX = 0, numpicoY = 0, numpicoZ = 0, i = 0, j = 0, tam = 800;
float tol = 1.5;
size_t byte6 = 6;

int n_amostras = 0;
float densidades_x[N_AMOSTRAS];
float densidades_y[N_AMOSTRAS];
float densidades_z[N_AMOSTRAS];
float media_x = 0;
float media_y = 0;
float media_z = 0;
float desvio_x = 0;
float desvio_y = 0;
float desvio_z = 0;

ESP8266WebServer server(80);
Servo ESC;     // create servo object to control the ESC
int potValue = 0;  // value from the analog pin
int potValueAnt = 0; // valor anterior;


float calc_media (float* arr, int n)
{
  float media = 0.0;
  for  (int i = 0; i<n ; i++)
    media += arr[i]/n;

  return media;
}

float calc_desvio (float* arr, float media, int n)
{
  float somatorio = 0;
  float desvio = 0;
  for(int i = 0; i<n; i++)
    somatorio += (arr[i] - media)*(arr[i] - media);
    
  desvio = sqrt(somatorio/n);
  return desvio;
}

void setup()
{
  ESC.attach(0,1000,2000); // (pin, min pulse width, max pulse width in microseconds)// D3 = 0
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
  Wire.begin(); // Initiate the Wire library
  // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345); // Start communicating with the device 
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  // Enable measurement
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable
  Wire.endTransmission();

   Wire.beginTransmission(ADXL345);
  // Select bandwidth rate register
  Wire.write(0x2C);
  // Normal mode, Output data rate = 800 Hz
  Wire.write(0x0D);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(ADXL345);
  // Select data format register
  Wire.write(0x31);
  // Self test disabled, 4-wire interface, Full resolution, Range = +/-4g
  Wire.write(0x09);
  // Stop I2C transmission
  Wire.endTransmission();

  delay(10);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
   
}

void loop()
{
  
  potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  
 // Serial.print(potValue);
 // Serial.print(" ");
  potValue = map(potValue, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
  //Serial.println(potValue);
  ESC.write(potValue);    // Send the signal to the ESC
   
  
    // === Read acceleromter data === //
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, byte6, true); // Read 6 registers total, each axis value is stored in 2 registers
  
  X_out2 = ( Wire.read()| Wire.read() << 8); // X-axis value
  float X_out2f = X_out2/256.0; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
  
  Y_out2 = ( Wire.read()| Wire.read() << 8); // Y-axis value
  float Y_out2f = Y_out2/256.0; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet

  Z_out2 = ( Wire.read()| Wire.read() << 8); // Z-axis value
  float Z_out2f = Z_out2/256.0; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
  delay(1);

  //Serial.println(potValue);

  
  if(i < tam){
    if(X_out2f < 0) X_out2f = -1*X_out2f;
    if(Y_out2f < 0) Y_out2f = -1*Y_out2f;
    if(Z_out2f < 0) Z_out2f = -1*Z_out2f;
    /*Serial.print("X0: ");
    Serial.print(X_out0);
    Serial.print(" ");
    Serial.print("X1: ");
    Serial.print(X_out1);
    Serial.print(" ");
    Serial.print("X2: ");
    Serial.print(X_out2f);
    Serial.println(" ");
    Serial.print("Y0: ");
    Serial.print(Y_out0);
    Serial.print(" ");
    Serial.print("Y1: ");
    Serial.print(Y_out1);
    Serial.print(" ");
    Serial.print("Y2: ");
    Serial.print(Y_out2f);
    Serial.println(" ");
    Serial.print("Z0: ");
    Serial.print(Z_out0);
    Serial.print(" ");
    Serial.print("Z1: ");
    Serial.print(Z_out1);
    Serial.print(" ");
    Serial.print("Z2: ");
    Serial.print(Z_out2f);
    Serial.println(" ");
    Serial.println("....................");
 //   Firebase.pushFloat("X-axis",X_out2f);
 //   Firebase.pushFloat("Y-axis",Y_out2f);
 //   Firebase.pushFloat("Z-axis",Z_out2f);
 */
    i++;
  }

  // =============== DETECCAO DE PICOS ======================//
  if(i >= 3 && i < tam){
    if(X_out1 > tol*X_out0 && X_out1 > tol*X_out2f) numpicoX++;
    if(Y_out1 > tol*Y_out0 && Y_out1 > tol*Y_out2f) numpicoY++;
    if(Z_out1 > tol*Z_out0 && Z_out1 > tol*Z_out2f) numpicoZ++;
  }
 
  /*Serial.print("x0: ");
  Serial.print(X_out0);
  Serial.print("x1: ");
  Serial.print(X_out1);
  Serial.print("x2: ");
  Serial.println(X_out2f);
  */
   

  
  //delay(10);

  if(i == tam){
     /* Serial.print("numpicoX: ");
      Serial.print(numpicoX);
      Serial.print(" ");
      Serial.print("numpicoY ");
      Serial.print(numpicoY);
      Serial.print(" ");
      Serial.print("numpicoZ ");
      Serial.print(numpicoZ);
      Serial.println(" ");
      */
      
      razaopicoX = numpicoX/tam;
      razaopicoY = numpicoY/tam;
      razaopicoZ = numpicoZ/tam;
      
     /* Serial.print("razao de pico X: ");
      Serial.print(razaopicoX);
      Serial.print(" ");
      Serial.print("razao de pico Y");
      Serial.print(razaopicoY);
      Serial.print(" ");
      Serial.print("razao de pico Z ");
      Serial.print(razaopicoZ);
      Serial.println(" ");*/
 //   Firebase.pushInt("Numero de picoX",numpicoX);
  //  Firebase.pushInt("Numero de picoY",numpicoY);
 //   Firebase.pushInt("Numero de picoZ",numpicoZ);
    Firebase.setFloat("razao de pico X",X_out2f);
    Firebase.setFloat("razao de pico Y",Y_out2f);
    Firebase.setFloat("razao de pico Z",Z_out2f);
    Serial.print("razao de pico X");
    Serial.println(razaopicoX);
    i = 0;
  numpicoX = 0;
  numpicoY = 0;
  numpicoZ = 0;
  }

  X_out0 = X_out1;
  X_out1 = X_out2f;
  Y_out0 = Y_out1;
  Y_out1 = Y_out2f;
  Z_out0 = Z_out1;
  Z_out1 = Z_out2f;
  
  //delay(1);

  // ============ CALCULO DA MEDIA E DESVIO PADRAO ========================//
  
    potValueAnt = potValue;
    
    if(n_amostras < N_AMOSTRAS)
    {
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

      desvio_x = calc_desvio(densidades_x, media_x, N_AMOSTRAS);
      desvio_y = calc_desvio(densidades_y, media_y, N_AMOSTRAS);
      desvio_z = calc_desvio(densidades_z, media_z, N_AMOSTRAS);

      Firebase.setFloat("media_x", media_x);
      Firebase.setFloat("media_y", media_y);
      Firebase.setFloat("media_z", media_z);

      Firebase.setFloat("desvio_x", desvio_x);
      Firebase.setFloat("desvio_y", desvio_y);
      Firebase.setFloat("desvio_z", desvio_z);

      n_amostras = 0;
      /*
      media_x = 0;
      media_y = 0;
      media_z = 0;
      desvio_x = 0;
      desvio_y = 0;
      desvio_z = 0;
//      */
    }    
  

 

}
