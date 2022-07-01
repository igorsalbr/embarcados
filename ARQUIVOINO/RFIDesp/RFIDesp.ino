#include <Arduino.h>

// Programa : RFID - Controle de Acesso leitor RFID

#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#include <Arduino_JSON.h>

#define USE_SERIAL Serial

#define NUM_ESTADOS 2
#define NUM_EVENTOS 5
#define SS_PIN 21
#define RST_PIN 22
#define pinVerde 26
#define pinVermelho 32
#define PIN_PIR 35

Servo myservo;
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

WiFiMulti wifiMulti;

int pos = 180; // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
int servoPin = 13;

int statte = LOW; // by default, no motion detected
int val = 0;

unsigned long currentTime = 0;
unsigned long previousTime = 0;

char st[20];

// Enums

// Cria tipo de dado
enum state
{
    IDLEE,
    PORTA_ABERTA
};
state estado = IDLEE; // Cria variável do tipo de dado criado

enum event
{
    NENHUM_EVENTO = -1,
    CHECAGEM_OK,
    CHECAGEM_NOK,
    SAIU_PRESENCA,
    CONTINUA_PRESENCA,
    CONTINUA
};
event evento;

enum action
{
    NENHUMA_ACAO = -1,
    ABRE_PORTA,
    FECHA_PORTA,
    MANTEM_ABERTA,
    REJEITA_PESSOA
};
action acao;

// -------------------------------------------------------
// Structs

typedef struct transition // Cria tipo de dado
{
    state proximoEstado;
    action acao;
} transition;

// Cria variável do tipo de dado criado
transition matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS] = {
    {{PORTA_ABERTA, ABRE_PORTA}, {IDLEE, REJEITA_PESSOA}, {IDLEE, NENHUMA_ACAO}, {IDLEE, NENHUMA_ACAO}, {IDLEE, NENHUMA_ACAO}},
    {{PORTA_ABERTA, NENHUMA_ACAO}, {PORTA_ABERTA, NENHUMA_ACAO}, {IDLEE, FECHA_PORTA}, {PORTA_ABERTA, MANTEM_ABERTA}, {PORTA_ABERTA, NENHUMA_ACAO}}};

// -------------------------------------------------------
// Declara Funções (são definidas posteriormente)
event obterEvento();
action obterAcao(state estado, event evento);
state obterProximoEstado(state estado, event evento);
void executarAcao(action acao);
// Ao contrário de C, em arquivos .ino, isso não é necessário.

// =========================================================================================
// Setup

void setup()
{
    Serial.begin(115200); // Inicia a serial
    SPI.begin();          // Inicia  SPI bus
    mfrc522.PCD_Init();   // Inicia MFRC522
    pinMode(pinVerde, OUTPUT);
    pinMode(pinVermelho, OUTPUT);
    pinMode(PIN_PIR, INPUT);

    digitalWrite(pinVermelho, HIGH);
    digitalWrite(pinVerde, LOW);

    // Allow allocation of all timers
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    myservo.setPeriodHertz(50);          // standard 50 hz servo
    myservo.attach(servoPin, 500, 2400); // attaches the servo on pin 18 to the servo object
    // using default min/max of 1000us and 2000us
    // different servos may require different min/max settings
    // for an accurate 0 to 180 sweep

    // Mensagens iniciais no serial monitor
    Serial.println("Aproxime o seu cartao do leitor:");
    Serial.println();

    wifiMulti.addAP("LAPTOP-0VP6T15V 6682", "5S0[1v14");
}

// =========================================================================================
// Loop
void loop()
{
    evento = obterEvento();
    if (evento != NENHUM_EVENTO)
    {
        acao = obterAcao(estado, evento);
        estado = obterProximoEstado(estado, evento);
        executarAcao(acao);
        // Serial.println("Estado: %d Evento: %d Acao:%d\n", estado, evento, acao);
    }
}

// =========================================================================================
// Funções

event obterEvento()
{
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())
    {
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

        Serial.println();
        Serial.print("Mensagem : ");
        conteudo.toUpperCase();
        conteudo.replace(" ", "");
        USE_SERIAL.print("not connected");
        if ((wifiMulti.run() == WL_CONNECTED))
        {

            HTTPClient http;

            USE_SERIAL.print("[HTTP] begin...\n");
            USE_SERIAL.print(conteudo);

            // parte de entrada

            // configure traged server and url
            // http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
            http.begin("https://project-rfid-embarcados.herokuapp.com/update/active"); // HTTP

            USE_SERIAL.print("[HTTP] PUT TRUE...\n");
            std::string falsePut = std::string(conteudo.c_str()) + std::string("\", \"active\":false }");
            std::string truePut = std::string(conteudo.c_str()) + std::string("\", \"active\":true }");

            // start connection and send HTTP header
            std::string bode1 = "{\"id_tag\":\"" + std::string(falsePut);
            std::string bode2 = "{\"id_tag\":\"" + std::string(truePut);
            Serial.print(bode1.c_str());
            Serial.print(bode2.c_str());
            http.addHeader("Content-Type", "application/json");
            int httpCode = http.PUT(bode2.c_str());

            // httpCode will be negative on error
            if (httpCode > 0)
            {
                // HTTP header has been send and Server response header has been handled
                USE_SERIAL.printf("[HTTP] put... code: %d\n", httpCode);

                // file found at server
                if (httpCode == HTTP_CODE_OK)
                {
                    String payload = http.getString();
                    JSONVar entrada = JSON.parse(payload);

                    // JSON.typeof(jsonVar) can be used to get the type of the var

                    Serial.print("JSON object = ");
                    Serial.println(entrada);

                    // myObject.keys() can be used to get an array of all the keys in the object
                    JSONVar usuario = entrada["update"];

                    JSONVar keys = usuario[0].keys();

                    for (int i = 0; i < keys.length(); i++)
                    {
                        JSONVar value = usuario[0][keys[i]];
                        Serial.print(keys[i]);
                        Serial.print(" = ");
                        Serial.println(value);
                    }
                    Serial.print("===/n ");
                    Serial.print(usuario[0]["id_tag"]);
                    if (usuario[0]["id_tag"] == conteudo) // UID 1 - Chaveiro
                    {

                        Serial.print("/n VAMO LA /n");

                        Serial.print("/n É IGUAL A /n");
                        Serial.print(conteudo);

                        USE_SERIAL.print("[HTTP] PUT FALSE...\n");
                        USE_SERIAL.print("======================/n");
                        delay(3000);
                        http.end();

                        http.begin("https://project-rfid-embarcados.herokuapp.com/update/active"); // HTTP
                        http.addHeader("Content-Type", "application/json");
                        Serial.print("oiii");
                        delay(6000);
                        int httpCode2 = http.PUT(bode1.c_str());
                        if (httpCode2 > 0)
                        {
                            Serial.print("false");
                            // HTTP header has been send and Server response header has been handled
                            USE_SERIAL.printf("[HTTP] put... code: %d\n", httpCode2);

                            // file found at server
                            if (httpCode2 == HTTP_CODE_OK)
                            {
                                String payload2 = http.getString();
                                JSONVar entrada2 = JSON.parse(payload2);

                                // JSON.typeof(jsonVar) can be used to get the type of the var

                                Serial.print("JSON object = ");
                                Serial.println(entrada2);

                                // myObject.keys() can be used to get an array of all the keys in the object
                                JSONVar usuario2 = entrada2["update"];
                                JSONVar keys2 = usuario2.keys();

                                for (int i = 0; i < keys2.length(); i++)
                                {
                                    JSONVar value2 = usuario2[keys2[i]];
                                    Serial.print(keys2[i]);
                                    Serial.print(" = ");
                                    Serial.println(value2);
                                }
                                Serial.print("===/n ");

                                http.end();
                            }
                        }
                        else
                        {
                            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
                        }

                        return CHECAGEM_OK;
                    }
                    else
                    {
                        return CHECAGEM_NOK;
                    }
                }
            }
            else
            {
                USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
            }
        }
    };

    int leitura = digitalRead(PIN_PIR);
    if (leitura)
    {
        return CONTINUA_PRESENCA;
    }

    if (!leitura)
    {
        return SAIU_PRESENCA;
    }

    return CONTINUA;
};

action obterAcao(state estado, event evento)
{
    return matrizTransicaoEstados[estado][evento].acao;
};

state obterProximoEstado(state estado, event evento)
{
    return matrizTransicaoEstados[estado][evento].proximoEstado;
};

void executarAcao(action acao)
{
    if (acao == NENHUMA_ACAO)
        return;

    switch (acao)
    {
    case ABRE_PORTA:
        Serial.println("Ola cartão !");
        digitalWrite(pinVerde, HIGH);
        digitalWrite(pinVermelho, LOW);
        Serial.println("Você tem permissão!");
        for (pos = 0; pos <= 90; pos += 1)
        { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            myservo.write(pos); // tell servo to go to position in variable 'pos'
            delay(15);          // waits 15ms for the servo to reach the position
        }
        delay(3000);
        break;
    case FECHA_PORTA:
        digitalWrite(pinVermelho, HIGH);
        digitalWrite(pinVerde, LOW);
        Serial.println("Fechou porta");
        for (pos = 90; pos >= 0; pos -= 1)
        {                       // goes from 180 degrees to 0 degrees
            myservo.write(pos); // tell servo to go to position in variable 'pos'
            delay(15);          // waits 15ms for the servo to reach the position
        }
        break;
    case MANTEM_ABERTA:
        digitalWrite(pinVermelho, LOW);
        digitalWrite(pinVerde, HIGH);
        Serial.println("Mantém aberto");
        break;
    case REJEITA_PESSOA:
        digitalWrite(pinVermelho, HIGH);
        digitalWrite(pinVerde, LOW);
        delay(1000);
        Serial.println("Rejeitou pessoa");
        break;
    };
};
