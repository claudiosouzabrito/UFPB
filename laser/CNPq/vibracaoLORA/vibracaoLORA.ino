
#include <ESP8266HTTPClient.h>
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
//#include "arduinoFFT.h"
#include "LoRaMESH.h"

uint16_t id;
uint8_t payload[31], payloadSize;

/* Local device ID */
uint16_t localId;

/* Remote device ID */
uint16_t remoteId;

/* Local device Unique ID */
uint32_t localUniqueId;

/* Local device Net */
uint16_t localNet;

/* Remote device ID to communicate with */
uint16_t ID = 20;

/* Payload buffer */
uint8_t bufferPayload[MAX_PAYLOAD_SIZE] = {0};

/* Values read on each analog inputs */
uint16_t AdcIn[2];

/* SoftwareSerial handles */
SoftwareSerial* hSerialCommands = NULL;

/* Received command */
uint8_t command;

/* Variables to gateway function
HTTPClient http;
String message;
const size_t capacity = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3);
DynamicJsonDocument doc(capacity);
JsonObject values = doc.createNestedObject("values");
*/
MeshStatus_Typedef LocalWriteConfig(uint16_t id, uint16_t net,
                                    uint32_t uniqueId) {
    uint8_t crc = 0;
    uint8_t bufferPayload[31];
    uint8_t payloadSize;
    uint8_t i = 0;
    uint8_t command;
    uint16_t idRead = 0;

    /* Asserts parameters */
    if (uniqueId == 0) {
        Serial.println("ERRO UniqueID");
        return MESH_ERROR;
    }

    if (hSerialCommands == NULL) {
        Serial.println("ERRO hSerialCommands");
        return MESH_ERROR;
    }

    /*Creating the payload with
    the passed NET and UniqueID and then,
    call the function with the ID passed*/

    bufferPayload[0] = net & 0xFF;
    bufferPayload[1] = (net >> 8) & 0xFF;
    bufferPayload[2] = uniqueId & 0xFF;
    bufferPayload[3] = (uniqueId >> 8) & 0xFF;
    bufferPayload[4] = (uniqueId >> 16) & 0xFF;
    bufferPayload[5] = (uniqueId >> 24) & 0xFF;

    /* Loads dummy bytes */
    for (i = 6; i < 11; i++) bufferPayload[i] = 0x00;

    PrepareFrameCommand(id, CMD_WRITECONFIG, &bufferPayload[0], i);

    /* Sends packet */
    SendPacket();

    /* Flush serial input buffer */
    // SerialFlush(hSerialCommand);
    // To not make modifications on the original library
    // I copied the content of the SerialFlush function
    while (hSerialCommands->available() > 0) {
        hSerialCommands->read();
    }

    /* Waits for response */
    if (ReceivePacketCommand(&idRead, &command, &bufferPayload[0], &payloadSize,
                             5000) != MESH_OK) {
        Serial.println("Erro de pacote recebido");
        return MESH_ERROR;
    }

    /* Checks command */
    if (command != CMD_WRITECONFIG) {
        Serial.print("Erro! Commando recebido: ");
        Serial.println(command, HEX);
        return MESH_ERROR;
    } else {
        Serial.print("ID: ");
        Serial.print("NET: ");
        Serial.println((uint32_t)bufferPayload[0] |
                       ((uint32_t)(bufferPayload[1]) << 8));
        Serial.print("UID: ");
        Serial.println((uint32_t)bufferPayload[2] |
                       ((uint32_t)(bufferPayload[3]) << 8) |
                       ((uint32_t)(bufferPayload[4]) << 16) |
                       ((uint32_t)(bufferPayload[5]) << 24));
        Serial.print("Versão de HW: ");
        Serial.println((uint32_t)bufferPayload[6]);
        Serial.print("RSD: ");
        Serial.println((uint32_t)bufferPayload[7]);
        Serial.print("Rev de FW: ");
        Serial.println((uint32_t)bufferPayload[8]);
        Serial.print("RSD: ");
        Serial.println((uint32_t)bufferPayload[9] |
                       ((uint32_t)(bufferPayload[10]) << 8) |
                       ((uint32_t)(bufferPayload[11]) << 16));
    }

    return MESH_OK;
}

#define velo 13

// ADXL345 I2C address is 0x53(83)
#define Addr 0x53


#define FIREBASE_HOST "teste-f83e2.firebaseio.com"
#define FIREBASE_AUTH "fqdzDP3KM2kG14tDnQgE0s5ORc3jYKo9cmq9TwRT"

#define TAM_MEDIA 100

const char* ssid = "Ladcsbesc2019";
const char* password = "Ladcsbesc2019";
//static float xAccl, yAccl, zAccl;
uint8_t ADXL345 = 0x53; // The ADXL345 sensor I2C address
int16_t X_out2 = 0, Y_out2 = 0, Z_out2 = 0;
float  X_out0 = 0, Y_out0 = 0, Z_out0 = 0, X_out1 = 0, Y_out1 = 0, Z_out1 = 0;
float razaopicoX = 0, razaopicoY = 0, razaopicoZ = 0;
float numpicoX = 0, numpicoY = 0, numpicoZ = 0, j = 0, tam_razao = 10;
float tol = 1.2;
float tol2 = 1.5;
size_t byte6 = 6;

int i2 = 0, i = 0, i3 = 0;
float densidades_x[TAM_MEDIA];
float densidades_y[TAM_MEDIA];
float densidades_z[TAM_MEDIA];
float media_x = 0;
float media_y = 0;
float media_z = 0;
float desvio_x = 0;
float desvio_y = 0;
float desvio_z = 0;
const int num_picos = 50;
float picosx[num_picos], picosy[num_picos], picosz[num_picos];
int k = 0;
int u = 0;
unsigned long t = 0;
unsigned long microseconds;


ESP8266WebServer server(80);
Servo ESC;     // create servo object to control the ESC
int potValue = 0;  // value from the analog pin
int potValueAnt = 0; // valor anterior;


float calc_media (float* arr, int n)  //FUNCAO QUE CUIDA DO CALCULO DA MEDIA ENTRE AS RAZOES DE PICO
{
  float media = 0.0;
  for  (int i = 0; i<n ; i++)
    media += arr[i];
    media = media/n;

  return media;
}

void setup()
{
  pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);  // turn the LED on (HIGH is the voltage level)
    // Configurando o módulo LoRaMesh
    delay(1000);
    Serial.begin(9600); /* Initialize monitor serial */

    /* Initialize SoftwareSerial */
    // Pinos:
    // D6(12)->Lora TX
    // D5(14)-> Lora RX
    hSerialCommands = SerialCommandsInit(12, 14, 9600);
    // Pinos:
    // D2(4)->Lora TX
    // D7(13)-> Lora RX
    // hSerialTransparent = SerialTranspInit(4, 13, 9600);

    /* Gets the local device ID*/
    if (LocalRead(&localId, &localNet, &localUniqueId) != MESH_OK)
        Serial.print("Couldn't read local ID\n\n");
    else {
        Serial.print("Local ID: ");
        Serial.println(localId);
        Serial.print("Local NET: ");
        Serial.println(localNet);
        Serial.print("Local Unique ID: ");
        Serial.println(localUniqueId, HEX);
        Serial.print("\n");
    }

//    WiFi.begin("MBEZERRIL", "mcb3z3rr1l!");
/*
    while (WiFi.status() !=
           WL_CONNECTED) {  // Wait for the WiFI connection completion
        delay(500);
        Serial.println("Waiting for connection");
    }
    /*
    http.begin("http://192.168.0.17:9627/samples/insert");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization",
                   "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9."
                   "eyJ1c2VybmFtZSI6ImFkbWluIiwiaWF0IjoxNTc0MTMzMjU3LCJleHAiOjE"
                   "1NzQyMTk2NTd9.9vTmuqr8wTAn1WlhbLTt8XoIlnZJcgjEyJaF7iFR_nE");
    // Teste para configurar o ID
    */
    if (localNet == 0) {
        Serial.println("Sending master configurations...");
        LocalWriteConfig(0x00, 0x25, localUniqueId);
    } else {
        Serial.println("The node is a master!");
    }
    if (LocalRead(&localId, &localNet, &localUniqueId) != MESH_OK)
        Serial.print("Couldn't read local ID\n\n");
    else {
        Serial.print("Local ID: ");
        Serial.println(localId);
        Serial.print("Local NET: ");
        Serial.println(localNet);
        Serial.print("Local Unique ID: ");
        Serial.println(localUniqueId, HEX);
        Serial.print("\n");
    }
    delay(500);



  ESC.attach(0,1000,2000); // (PINO, LARGURA DE PULSO MINIMA, LARGURA DE PULSO MAXIMO EM MICRO SEGUNDOS)// D3 = 0
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

  // PEGAR ENDERECO IP DO ESP8266
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.begin(9600); 
  Wire.begin(); // INICIANDO A BIBLIOTECA WIRE
  // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345); // COMECANDO A COMUNICACAO
  Wire.write(0x2D); // ACESSO COM POWER_CTL Register - 0x2D
  // Enable measurement
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High PARA MEDICAO ENABLE
  Wire.endTransmission();

   Wire.beginTransmission(ADXL345);
                                    // sELECIONANDO BANDWIDTH RATE REGISTRADOR
  Wire.write(0x2C);
                                     // MODO NORMAL, Output data rate = 800 Hz
  Wire.write(0x0D);
                                    // PARE TRANSMISSAO I2C
  Wire.endTransmission();

                                    // COMECE TRANSMISSAO I2C
  Wire.beginTransmission(ADXL345);
                                     // SELECIONANDO REGISTRADOR DE FORMATO DE DATA 
  Wire.write(0x31);
                                     // DESABILITANDO TESTE SOZINHO, 4-wire interface, Full RESOLUCION, Range = +/-4g
  Wire.write(0x09);
  
  Wire.endTransmission();            // PARE TRANSMISSAO I2C

  delay(10);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); //INICIANDO TRANSMISSAO COM FIREBASE
  
  media_x = 0.454;
  media_y = 0.464;           //VALORES INICIAIS ALCANCADOS POR MEIO DE TESTES PRATICOS
  media_z = 0.512;
/*  
  Firebase.setFloat("media_x", media_x);      //ENVIANDO PARA FIREBASE
  Firebase.setFloat("media_y", media_y);
  Firebase.setFloat("media_z", media_z);
*/

  t = millis();   
}
MeshStatus_Typedef SendDatatest() {
    uint8_t i = 0, command, payloadSize;
    uint16_t idRead = 0;
    uint8_t bufferPayload[31];

    /*Creating the payload with
    the passed NET and UniqueID and then,
    call the function with the ID passed*/

    bufferPayload[0] = 0x01;
    bufferPayload[1] = 0x02;
    bufferPayload[2] = 0x03;

    if (PrepareFrameCommand(0x00, 0x10, &bufferPayload[0], 3) != MESH_OK) {
        Serial.println("Erro de mensagem enviada");
        return MESH_ERROR;
    }

    /* Sends packet */
    SendPacket();

    return MESH_OK;
}
void loop()
{
  if(millis() - t < 10000)
  {
    potValue = 15;   //FASE DE INICIALIZACAO DO MOTOR, 15 SEGUNDOS ATE INICIAR
    Serial.print("Pot = ");
    Serial.println(potValue);
    
  }
  
   else
   {
    potValue = 60;
    Serial.print("Pot = ");     //FASE DE DISPARO DO MOTOR
    Serial.println(potValue);
   }
    /*
  if(i2 != TAM_MEDIA){   //ESSA PARTE DEVE SER DESCOMENTADA DURANTE A FASE DE ANALISE
      densidades_x[i2] = razaopicoX;
      densidades_y[i2] = razaopicoY;
      densidades_z[i2] = razaopicoZ;
    
      media_x = calc_media(densidades_x, TAM_MEDIA);
      media_y = calc_media(densidades_y, TAM_MEDIA);
      media_z = calc_media(densidades_z, TAM_MEDIA);            
  
      Firebase.setFloat("media_x", media_x);
      Firebase.setFloat("media_y", media_y);
      Firebase.setFloat("media_z", media_z);
      
  }
  */
 
  potValue = map(potValue, 0, 1023, 0, 180);   
  ESC.write(potValue);    // ENVIA O SINAL PARA A ESC
   
  
    // === Read acceleromter data === //
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); // INICIALIZA O REGISTRADOR 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, byte6, true); // LE 6 REGISTRADORES, CADA COORDENADA PRECISA DE 2 REGISTRADORES
  
  microseconds = micros();
   
  X_out2 = ( Wire.read()| Wire.read() << 8); // X-axis value
  float X_out2f = X_out2/256.0; //UM ALCANDE DE -2G ATE +2G, PRECISAMOS DIVIDIR O VALOR POR 256, DE ACORDO COM O DATASHEET
  
  Y_out2 = ( Wire.read()| Wire.read() << 8); // Y-axis value
  float Y_out2f = Y_out2/256.0; //UM ALCANDE DE -2G ATE +2G, PRECISAMOS DIVIDIR O VALOR POR 256, DE ACORDO COM O DATASHEET

  Z_out2 = ( Wire.read()| Wire.read() << 8); // Z-axis value
  float Z_out2f = Z_out2/256.0; //UM ALCANDE DE -2G ATE +2G, PRECISAMOS DIVIDIR O VALOR POR 256, DE ACORDO COM O DATASHEET

  while( micros() < microseconds + 1000000*(1/800));
  
  
  if(i < tam_razao){                 //TRATANDO OS VALORES LIDOS
    if(X_out2f < 0) X_out2f = -1*X_out2f;
    if(Y_out2f < 0) Y_out2f = -1*Y_out2f;
    if(Z_out2f < 0) Z_out2f = -1*Z_out2f;
    /*
    Firebase.setFloat("acc_x", X_out2f);
    Firebase.setFloat("acc_y", Y_out2f);
    Firebase.setFloat("acc_z", Z_out2f);
    */
    i++;
  }

  // =============== DETECCAO DE PICOS ======================//
  if(i >= 3 && i < tam_razao){
    if((X_out1 > tol*X_out0 && X_out1 > tol*X_out2f) || (X_out1 < tol*X_out0 && X_out1 < tol*X_out2f)) numpicoX++;
    if((Y_out1 > tol*Y_out0 && Y_out1 > tol*Y_out2f) || (Y_out1 < tol*Y_out0 && Y_out1 < tol*Y_out2f)) numpicoY++;
    if((Z_out1 > tol*Z_out0 && Z_out1 > tol*Z_out2f) || (Z_out1 < tol*Z_out0 && Z_out1 < tol*Z_out2f)) numpicoZ++;
  }

  if(i == tam_razao){                //APOS UM NUMERO X DE AMOSTRAS, EH CALCULADO UMA RAZAO DE PICO PARA CADA COORDENADA
      razaopicoX = numpicoX/tam_razao;
      razaopicoY = numpicoY/tam_razao;
      razaopicoZ = numpicoZ/tam_razao;
     /* 
      if(razaopicoX <= tol2*media_x && razaopicoX >= media_x/tol2) Firebase.setFloat("flagx", 1); //SE A RAZAO ESTIVER DENTRO DO PADRAO, FLAG=
      else Firebase.setFloat("flagx", 0); // SE NAO, FLAG = 0
  
      if(razaopicoY <= media_y*tol2 && razaopicoY >= media_y/tol2) Firebase.setFloat("flagy", 1);
      else Firebase.setFloat("flagy", 0);
  
      if(razaopicoZ <= media_z*tol2 && razaopicoZ >= media_z/tol2) Firebase.setFloat("flagz", 1);
      else Firebase.setFloat("flagz", 0);
        
      Firebase.setFloat("razao de pico X",razaopicoX);
      Firebase.setFloat("razao de pico Y",razaopicoY);
      Firebase.setFloat("razao de pico Z",razaopicoZ);
      */
      i = 0;
      i2++;
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
  if (ReceivePacketCommand(&id, &command, &bufferPayload[0], &payloadSize,
                             10000) == MESH_OK) {
        digitalWrite(LED_BUILTIN, HIGH);
        /* Sends to monitor */
        // Serial.print("\nID: ");
        // Serial.print(id);
        // Serial.println(" Dado recebido: ");
        if (command == 0x11 && bufferPayload[0]==0x23) {
            //for (int i = 0; i < payloadSize; i++)
            //    Serial.println(bufferPayload[i], HEX);
            
            razaopicoX = (((uint32_t)(bufferPayload[1])) | ((uint32_t)(bufferPayload[2]) << 8));
            razaopicoY = (((uint32_t)(bufferPayload[3])) | ((uint32_t)(bufferPayload[4]) << 8));
            razaopicoZ = (((uint32_t)(bufferPayload[5])) | ((uint32_t)(bufferPayload[6]) << 8));
            Firebase.setFloat("razao de pico X",razaopicoX);
            Firebase.setFloat("razao de pico Y",razaopicoY);
            Firebase.setFloat("razao de pico Z",razaopicoZ);
            /*
            doc["collectionid"] = 65;
            serializeJson(doc, message);
            Serial.println(message);
            int httpCode = http.POST(message);
            message = "";
            Serial.println(httpCode);
            */
        }else{
            Serial.print("Comando não aceito: ");
            Serial.println(command);
            Serial.print("do ID: ");
            Serial.print(id);
        }
    } else {
        Serial.println("Nenhum pacote recebido");
    }
}
  

 
