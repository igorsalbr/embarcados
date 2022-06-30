//Programa : RFID - Controle de Acesso leitor RFID
//Autor : Julia e Igor





#include <Arduino_JSON.h>




/**
 * BasicHTTPClient.ino
 *
 *  C")ated on: 24.05.2015
 *
 */

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial



/*
const char* ca = \ 
"-----BEGIN CERTIFICATE-----\n" \  
"MIIEkjCCA3qgAwIBAgIQCgFBQgAAAVOFc2oLheynCDANBgkqhkiG9w0BAQsFADA/\n" \  
"MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n" \  
"DkRTVCBSb290IENBIFgzMB4XDTE2MDMxNzE2NDA0NloXDTIxMDMxNzE2NDA0Nlow\n" \  
"SjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUxldCdzIEVuY3J5cHQxIzAhBgNVBAMT\n" \  
"GkxldCdzIEVuY3J5cHQgQXV0aG9yaXR5IFgzMIIBIjANBgkqhkiG9w0BAQEFAAOC\n" \  
"AQ8AMIIBCgKCAQEAnNMM8FrlLke3cl03g7NoYzDq1zUmGSXhvb418XCSL7e4S0EF\n" \  
"q6meNQhY7LEqxGiHC6PjdeTm86dicbp5gWAf15Gan/PQeGdxyGkOlZHP/uaZ6WA8\n" \  
"SMx+yk13EiSdRxta67nsHjcAHJyse6cF6s5K671B5TaYucv9bTyWaN8jKkKQDIZ0\n" \  
"Z8h/pZq4UmEUEz9l6YKHy9v6Dlb2honzhT+Xhq+w3Brvaw2VFn3EK6BlspkENnWA\n" \  
"a6xK8xuQSXgvopZPKiAlKQTGdMDQMc2PMTiVFrqoM7hD8bEfwzB/onkxEz0tNvjj\n" \  
"/PIzark5McWvxI0NHWQWM6r6hCm21AvA2H3DkwIDAQABo4IBfTCCAXkwEgYDVR0T\n" \  
"AQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8EBAMCAYYwfwYIKwYBBQUHAQEEczBxMDIG\n" \  
"CCsGAQUFBzABhiZodHRwOi8vaXNyZy50cnVzdGlkLm9jc3AuaWRlbnRydXN0LmNv\n" \  
"bTA7BggrBgEFBQcwAoYvaHR0cDovL2FwcHMuaWRlbnRydXN0LmNvbS9yb290cy9k\n" \  
"c3Ryb290Y2F4My5wN2MwHwYDVR0jBBgwFoAUxKexpHsscfrb4UuQdf/EFWCFiRAw\n" \  
"VAYDVR0gBE0wSzAIBgZngQwBAgEwPwYLKwYBBAGC3xMBAQEwMDAuBggrBgEFBQcC\n" \  
"ARYiaHR0cDovL2Nwcy5yb290LXgxLmxldHNlbmNyeXB0Lm9yZzA8BgNVHR8ENTAz\n" \  
"MDGgL6AthitodHRwOi8vY3JsLmlkZW50cnVzdC5jb20vRFNUUk9PVENBWDNDUkwu\n" \  
"Y3JsMB0GA1UdDgQWBBSoSmpjBH3duubRObemRWXv86jsoTANBgkqhkiG9w0BAQsF\n" \  
"AAOCAQEA3TPXEfNjWDjdGBX7CVW+dla5cEilaUcne8IkCJLxWh9KEik3JHRRHGJo\n" \  
"uM2VcGfl96S8TihRzZvoroed6ti6WqEBmtzw3Wodatg+VyOeph4EYpr/1wXKtx8/\n" \  
"wApIvJSwtmVi4MFU5aMqrSDE6ea73Mj2tcMyo5jMd6jmeWUHK8so/joWUoHOUgwu\n" \  
"X4Po1QYz+3dszkDqMp4fklxBwXRsW10KXzPMTZ+sOPAveyxindmjkW8lGy+QsRlG\n" \  
"PfZ+G6Z6h7mjem0Y+iWlkYcV4PIWL1iwBi8saCbGS5jN2p8M+X+Q7UNKEkROb3N6\n" \  
"KOqkqm57TH2H3eDJAkSnh6/DNFu0Qg==\n" \  
"-----END CERTIFICATE-----\n";
*/













 
#include <SPI.h>
#include <MFRC522.h>



 
#define SS_PIN 21
#define RST_PIN 22
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#define pinVerde     32
#define pinVermelho  12

#define PIN_PIR 35 
int led = 12;                // the pin that the LED is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;   
WiFiMulti wifiMulti;  // dafine classe do wifi

unsigned long currentTime=0;
unsigned long previousTime=0;
 
char st[20];
 
void setup() 
{
  Serial.begin(115200);   // Inicia a serial
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  pinMode(pinVerde, OUTPUT);
  pinMode(pinVermelho, OUTPUT);
  pinMode(PIN_PIR, INPUT);
  // Mensagens iniciais no serial monitor
  Serial.println("Aproxime o seu cartao do leitor:");
  Serial.println();

  for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }

  wifiMulti.addAP("APEZINHO-2.4G", "zerobreid98");  // Tenta conectar no wifi (nome, senha)

}

 
void loop() 
{ 
  
  digitalWrite(pinVermelho, HIGH);
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  conteudo.replace(" ","");
  USE_SERIAL.print("not connected");
    if((wifiMulti.run() == WL_CONNECTED)) { // se o wifi esta conectado...

        HTTPClient http; // cria o carinha que consegue fzer requisicoes

        USE_SERIAL.print("[HTTP] begin...\n");
        USE_SERIAL.print(conteudo); // TAG LIDA

        // parte de entrada

        http.begin("https://project-rfid-embarcados.herokuapp.com/update/active"); // Cria comunicacao com back end
        

        USE_SERIAL.print("[HTTP] PUT TRUE...\n");
        std::string falsePut = std::string(conteudo.c_str())+std::string("\", \"active\":false }"); // cria meio body da requisicao pra deixar INATIVO com a tag lida
        std::string truePut = std::string(conteudo.c_str())+std::string("\", \"active\":true }"); // cria meio body da requisicao pra deixar ATIVO com a tag lida

        // start connection and send HTTP header
         std::string bode1 = "{\"id_tag\":\"" + std::string(falsePut); // body inteiro
         std::string bode2 = "{\"id_tag\":\"" + std::string(truePut); //body inteiro
        Serial.print(bode1.c_str());
        Serial.print(bode2.c_str());
        
        http.addHeader("Content-Type", "application/json"); //  tipo de conteudo q enviaremos no body 
        int httpCode = http.PUT(bode2.c_str()); // REQUISICAO PUT - altera estado no Banco de dados da tag lida, caso a tag n exista, retorna um objeto vazio
        // o objeto é do tipo {"update":[--> INFO DO USER SE EXISTIR <--]}
        // httpCode will be negative on error
        if(httpCode > 0) {// se consegui conectar com o banco
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] put... code: %d\n", httpCode); // codigo da resposta da requisicao

            // file found at server
            if(httpCode == HTTP_CODE_OK) { // se a req deu certo
                String payload = http.getString(); // pega o objeto de retorno mostrado acima
                JSONVar entrada = JSON.parse(payload); // transforma esse objeto em manipulavel 

                // JSON.typeof(jsonVar) can be used to get the type of the var
                if (JSON.typeof(entrada) == "undefined") { // testa a lib de parseJSON
                  Serial.println("Parsing input failed!");
                  return;
                }
                
                Serial.print("JSON object = ");
                Serial.println(entrada); //JSON RECEBIDO JA MANIPULAVEL
                
                JSONVar keysaux = entrada.keys(); // pega key do objeto no caso é "update" se quiser printar pra ver
                JSONVar usuario = entrada[keysaux[0]][0]; // extrair os dados do usuario de dentro do json, como vem em uma lista, eu acrescentei esse segundo [0] pra ver se printa o prox for no monitor
                JSONVar keys = usuario.keys();

                for (int i = 0; i < keys.length(); i++) { // for pra printar chave e valor com igual no meio
                  JSONVar value = usuario[keys[i]];
                  Serial.print(keys[i]);
                  Serial.print(" = ");
                  Serial.println(value);
     
                }
                Serial.print("===/n ");
                Serial.print(usuario); // ve se tem uma lista com dados
                Serial.print("===/n  USUARIO ZERO");
                Serial.print(usuario[0]); // ve se o primeiro dado existe

                  if (usuario[0]) //UID 1 - Chaveiro  // SE EXISTIR dados dentro da lista de usuario, a requisicao deu certo e existe usuario cadastrado com essa tag -> ja ta mostrando no front vc passando
          {
            Serial.println("   Ola!!");
            Serial.println(usuario[2]);
        
            digitalWrite(pinVerde, HIGH); // funcionou -> led verde
            digitalWrite(pinVermelho, LOW);
            delay(9000); 
            Serial.println("Não acaba!!");
            func_leituraPIR(); // func sensor presenca
        
            digitalWrite(pinVerde, LOW);
            digitalWrite(pinVermelho, HIGH);
            
          }
                
                               
        
            }
      
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str()); // else da requisicao nao conseguir chegar no back (problema no back end)
        }
 





      // tentativa do segundo put - o que transforma active em false, nao esta dando certo e no monitor deveria vir um onjeto com os mesmos dados de usuario como em cima
      //nao sei pq parou de funcionar
      //minha teoria é da um http.end() aqui e depois http.begin() dnv com a mesma rota de la de cima caso de certo essa segunda requisicao



     // nao vou comentar essa parte pq eh igual em cimaa eh nois valeu

           USE_SERIAL.print("[HTTP] PUT FALSE...\n");
        USE_SERIAL.print("======================/n");
         delay(3000); 
         http.addHeader("Content-Type", "application/json");

         int httpCode2 = http.PUT(bode1.c_str());
         if(httpCode2 > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] put... code: %d\n", httpCode2);

            // file found at server
            if(httpCode2 == HTTP_CODE_OK) {
                String payload2 = http.getString();
                JSONVar entrada2 = JSON.parse(payload2);

                // JSON.typeof(jsonVar) can be used to get the type of the var
                if (JSON.typeof(entrada2) == "undefined") {
                  Serial.println("Parsing input failed!");
                  return;
                }
                
                Serial.print("JSON object = ");
                Serial.println(entrada2);
                
                // myObject.keys() can be used to get an array of all the keys in the object
                JSONVar usuario2 = entrada2["update"][0];
                JSONVar keys2 = usuario2.keys();

                for (int i = 0; i < keys2.length(); i++) {
                  JSONVar value2 = usuario2[keys2[i]];
                  Serial.print(keys2[i]);
                  Serial.print(" = ");
                  Serial.println(value2);                  
                }
                Serial.print("===/n ");
                
                               
        
            }
      
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        
        http.end();
        
     




        
    }

  

 }


void func_leituraPIR()
{
  int leituraPIR = digitalRead(PIN_PIR);  // read sensor value
  
  if (leituraPIR == HIGH) {           // check if the sensor is HIGH
     delay(500); 
    if (state == LOW) {
      state = HIGH;       // update variable state to HIGH 
      Serial.println("Identificação de Movimento"); 
   }
   Serial.println("Alguém está passando");
   func_leituraPIR();
   } 
    
    else {
        currentTime = millis();
        if (state == LOW){ //falta o timeout
            if((currentTime-previousTime)>3000){
                previousTime=currentTime;
            }
            else{
              delay(100);
              Serial.println("oi");
              func_leituraPIR();
            }
        }             
        else{
          Serial.println("Motion stopped!");
          state = LOW;       // update variable state to LOW
        } 
        
    delay(2000);
    return;
   }

}
