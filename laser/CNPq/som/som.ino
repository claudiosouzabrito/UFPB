
#include <ArduinoJson.h>


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


#include <FirebaseError.h>
#include <Firebase.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseArduino.h>
#define N_AMOSTRAS 40
int n_amostras = 0;
float razoes[N_AMOSTRAS];
int pin0, pin1, pin2;
//  int freq = 1000;//(Hz)
double numSample = 40;
int numPico = 0;
double tol = 1.2;
double tol2 = 8.0;
int i = 0;
double razaoDePico;
double media = 0.018;
bool alarme = false;
int a_consecutivos = 10;
int l = 0;

const char* ssid = "CREO";
const char* password = "CREO960507";
ESP8266WebServer server(80);


#define FIREBASE_HOST "sac-dm-som-f2846.firebaseio.com"
#define FIREBASE_AUTH "3Unl0uuGanxqHWGxFNc6QHW8OB1B7Fy2d4FnSrqx"

float calc_media(float* arr){
  float media = 0.0;
  for (int i = 0; i < N_AMOSTRAS; i++){
    media += arr[i];
  }
  media = media/N_AMOSTRAS;
  return media;
}

void setup() {
  Serial.begin(9600);

  
  WiFi.begin(ssid, password);
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

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  if (Firebase.failed()) {
  Serial.print("Error connecting to Firebase");
  Serial.println(Firebase.error());
  }
  else {
  Serial.println("Firebase connection established");
  }
  
  delay(2000);
}


void loop() {
//  unsigned long startMillis= millis();
  while(1){
    if(i >= numSample) break;
    pin0 = analogRead(A0); 
    if(i >= 3 && i < numSample){
      Firebase.setFloat("valor", pin1);
      if(pin1 > tol*pin0 && pin1 > tol*pin2){
        numPico++;
        
        Serial.println("pico");
        
      }
    }
    Serial.println(pin0);
    pin2 = pin1;
    pin1 = pin0; 
    i++;
  }
  Serial.print("--------numPico: ");
  Serial.print(numPico);

  
  Firebase.setFloat("numero de pico", numPico);
  if (Firebase.failed()) {
    Serial.println("erro");
  }
    
  razaoDePico = numPico/numSample;
  Serial.print("-------razaoDePico:");
  Serial.print(razaoDePico);

  
  Firebase.setFloat("razao",razaoDePico);
 
  
  Serial.println("--------");
  numPico = 0;
  i = 0;
  if(n_amostras < N_AMOSTRAS){
    Serial.print("-------media num:");
    Serial.println(n_amostras);
    razoes[n_amostras] = razaoDePico;
    n_amostras++;
  }
  else{
    media = calc_media(razoes);
    Serial.print("-------mudanca na media:");
    Serial.println(media);
    Firebase.setFloat("media", media);
    n_amostras = 0;
  }

  if(razaoDePico > media*tol2){
    Serial.print("---------alarme crescendo:");
    Serial.print(razaoDePico);
    Serial.print(" vs ");
    Serial.print(media);
    Serial.print("*");
    Serial.print(tol2);
    l += 1;
  }
  else{
    Serial.println("---------alarme morto");
    alarme = false;
    Firebase.setBool("alarme", alarme);
    l = 0;
  }
  if(l >= a_consecutivos){
    Serial.println("---------ALERTA");
    alarme = true;
    Firebase.setBool("alarme", alarme);
  }

}
