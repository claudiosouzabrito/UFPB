
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
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


unsigned long timee;
unsigned long timesec, timemin;
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

void setup() {
    // initialize digital pin LED_BUILTIN as an output.
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
    if (LocalRead(&localId, &localNet, &localUniqueId) != MESH_OK) int variavel = 0;
      //  Serial.print("Couldn't read local ID\n\n");
    else {
        Serial.print("Local ID: ");
        Serial.println(localId);
        Serial.print("Local NET: ");
        Serial.println(localNet);
        Serial.print("Local Unique ID: ");
        Serial.println(localUniqueId, HEX);
        Serial.print("\n");
    }
    /*
    WiFi.persistent(false);
    WiFi.disconnect(true);
    WiFi.begin("eduroam", "claudiosouzabrito", "Weaponx-25");
    //WiFi.begin("CREO", "CREO960507");
    //WiFi.begin("MBEZERRIL", "mcb3z3rr1l!");
    while (WiFi.status() !=
           WL_CONNECTED) {  // Wait for the WiFI connection completion
        delay(500);
        Serial.println("Waiting for connection");
    }
    if(WiFi.status() == WL_CONNECTED) Serial.println("connected");
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
    if (LocalRead(&localId, &localNet, &localUniqueId) != MESH_OK) int variavel = 0;
     //   Serial.print("Couldn't read local ID\n\n");
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

void loop() {
    timee = millis();
    if ( ReceivePacketCommand(&id, &command, &bufferPayload[0], &payloadSize,
                             1000) == MESH_OK) {
        digitalWrite(2, HIGH);
        /* Sends to monitor */
        // Serial.print("\nID: ");
        // Serial.print(id);
        // Serial.println(" Dado recebido: ");
        if (command == 0x10) {
            timesec = timee/1000;
            timemin = timesec/60;
            timesec = timesec - 60*timemin;
            for (int i = 3; i < payloadSize; i++) {
              Serial.print(timemin); Serial.print(":"); Serial.print(timesec); Serial.print(" -> "); Serial.println(bufferPayload[i]);
            }
            /*
            values["valuex"] = (((uint32_t)(bufferPayload[1])) | ((uint32_t)(bufferPayload[2]) << 8));
            values["valuey"] = (((uint32_t)(bufferPayload[3])) | ((uint32_t)(bufferPayload[4]) << 8));
            values["valuez"] = (((uint32_t)(bufferPayload[5])) | ((uint32_t)(bufferPayload[6]) << 8));
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
