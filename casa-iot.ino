#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

//wi-fi e autenticação no Firebase
#define FIREBASE_HOST "https://casa-50f22.firebaseio.com/"
#define FIREBASE_AUTH "AIzaSyCQ9fHKQyWYD3vzCGb8qtwPVk0ijAItqZk"
#define WIFI_SSID "ifdoce" 
#define WIFI_PASSWORD "10tifsul"

#define LED_AZUL 2
#define LED_VERMELHO 16

voi firebaseAut(){
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void conectarWiFi(){
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("\nconnecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("conected: ");
    Serial.println(WiFi.localIP());
    firebaseAut();
}

void setup() {
  Serial.begin(9600);
  
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  conectarWiFi();
}

void setLampada(boolean state) {
  Serial.println(state);
  if(state){
    digitalWrite(LED_VERMELHO, LOW);
    Serial.println("Lâmpada Ligada - LED VERMELHO");
  }
  else{
    digitalWrite(LED_VERMELHO, HIGH);
    Serial.println("Lâmpada Desligada - LED VERMELHO");
  }
}

void setArCond(boolean state) {
  if(state){
    digitalWrite(LED_AZUL, LOW);
    Serial.println("Ar Condicionado Ligado - LED AZUL");
  }
    
  else{ 
    digitalWrite(LED_AZUL, HIGH);
    Serial.println("Ar Condicionado Desligado - LED AZUL");
  }
    
}

void loop() {
  if(WiFi.status() == WL_CONNECTED){
    if(Firebase.success()) {
      FirebaseObject casa = Firebase.get("casa");

      // ÁREA DE SERVIÇO
      if(casa.getBool("/areaServicoLampada"))
        setLampada(true);
      else
        setLampada(false);

      //AREA DE CIRCULACAO
      if(casa.getBool("/circulacaoLampada"))
        setLampada(true);
      else
        setLampada(false);

      //COZINHA
      if(casa.getBool("/cozinhaLampada"))
        setLampada(true);
      else
        setLampada(false);

      //GARAGEM
      if(casa.getBool("/garagmLampada"))
        setLampada(true);
      else
        setLampada(false);

      //QUARTO 1
      if(casa.getBool("/quarto1Lampada"))
        setLampada(true);
      else
        setLampada(false);
      if(casa.getBool("/quarto1ArCond"))
        setArCond(true);
      else
        setArCond(false);

      //QUARTO 2
      if(casa.getBool("/quarto2Lampada"))
        setLampada(true);
      else
        setLampada(false);
      if(casa.getBool("/quarto2ArCond"))
        setArCond(true);
      else
        setArCond(false);

      //SALA DE ESTAR
      if(casa.getBool("/salaEstarLampada"))
        setLampada(true);
      else
        setLampada(false);

      //SALA DE JANTAR
      if(casa.getBool("/salaJantarLampada"))
        setLampada(true);
      else
        setLampada(false);
      
      //SUITE
      if(casa.getBool("/suiteLampada"))
        setLampada(true);
      else
        setLampada(false);
      if(casa.getBool("/suiteArCond"))
        setArCond(true);
      else
        setArCond(false);
      
      //WC1
      if(casa.getBool("/wc1Lampada"))
        setLampada(true);
      else
        setLampada(false);
      
      //WC2
      if(casa.getBool("/wc2Lampada"))
        setLampada(true);
      else
        setLampada(false);
      
    }
    else {
    Serial.println("Erro na autenticão com o Firebase");
    }
  }else{
    conectarWiFi();
  }
  
  delay(500);

}