#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <Servo.h> // library servo
#include "DHT.h" // library dht

// Wifi network station credentials
#define WIFI_SSID "Internet"
#define WIFI_PASSWORD "!@#$%12345"

// Telegram BOT Token (Get from Botfather)
// Username: @JemOto_bot
#define BOT_TOKEN "2042997576:AAEo01Cp6dD2rb9-wn-MdNivdqfAeBydyto"

const unsigned long BOT_MTBS = 1000; // mean time between scan messages

unsigned long bot_lasttime; // last time messages' scan has been done
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

// Inisialisasi servo
static const int servoPin = 2;  // pin servo di D4 atau GPIO2
Servo myservo; 
int kondisi = 0;
int sudut = 0;
int sudut_min = 0;
int sudut_max = 160;
int sudut_step = 2;
String pos_jemuran;

// Inisialisasi DHT 11
#define DHTPIN 15 // pin dht11 di D8 atau GPIO15
#define DHTTYPE DHT11 // tipe DHT 11
DHT dht(DHTPIN, DHTTYPE);
String temp;

// Inisialisasi LDR sensor
#define LDRPIN A0 //pin LDR sensor di A0
int ldr;
String intensitas;
String cahaya;

// Inisialisasi sensor hujan
#define sensorHujan 14 // pin sensor hujan di D5 atau GPIO14
int dataAir;
String cuaca;

// Inisialisasi buzzer
#define buzzer 4 // pin buzzer di D2 atau GPO4

void keluarkan_jemuran(){
  if(kondisi == 0){
    for(sudut = 0; sudut <= sudut_max; sudut += sudut_step){
      myservo.write(sudut);
      delay(50);
      kondisi = 1;
    }
  }
}

void masukkan_jemuran(){
  if(kondisi == 1){
    for(sudut = 160; sudut >= sudut_min; sudut -= sudut_step){
      myservo.write(sudut);
      delay(50);
      kondisi = 0;
    }
  }
}

void cek_temperature(){
  float t = dht.readTemperature()-2;
  temp = "Suhu saat ini : ";
  temp += (t);
  temp +=" °C\n";
}

void cek_intensitas_cahaya(){
  ldr = analogRead(LDRPIN);
  intensitas = "Intensitas cahaya : ";
  intensitas += (ldr);
  if (ldr <= 120) {
    cahaya = " (Terang)";
  } else {
    cahaya = " (Gelap)";
  }
}

void cek_cuaca(){
  dataAir = digitalRead(sensorHujan);
  if (dataAir == LOW) {
    cuaca = "Hujan";
  } else { 
    cuaca = "Tidak Hujan";
  }
}

void cek_pos_jemuran(){
  if (myservo.read() == sudut_min){
    pos_jemuran = "Jemuran di dalam";
  } else if (myservo.read() == sudut_max){
    pos_jemuran = "Jemuran di luar";
  }
}

void buzzer_on(){
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
}

void jalankan_otomatis(){
  // jika hujan
  if (dataAir == LOW){
    buzzer_on();
  }
  //jika tidak hujan dan intensitas <= 120 (terang)
  if ((dataAir == HIGH) && (ldr <= 120)) { 
    keluarkan_jemuran();
  }
    //jika hujan dan intensitas >= 120 (gelap)
  else {
    masukkan_jemuran();
  }
}

void handleNewMessages(int numNewMessages)
{
  String answer;
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);
  
  for (int i = 0; i < numNewMessages; i++)
  {
    telegramMessage &msg = bot.messages[i];
    Serial.println("Received " + msg.text);
    if (msg.text == "/start"){
      myservo.write(sudut);
      answer = "Selamat datang *" + msg.from_name + "* di JemOto (Jemuran Otomatis), silahkan gunakan perintah /bantuan untuk melanjutkan! :)";      
    }
    else if (msg.text == "/masukkan"){
      buzzer_on();
      masukkan_jemuran();
      buzzer_on();
      answer = "Jemuran telah dimasukkan";
    }
    else if (msg.text == "/keluarkan"){
      buzzer_on();
      keluarkan_jemuran();
      buzzer_on();
      answer = "Jemuran telah dikeluarkan";
    }
    else if (msg.text == "/info"){
      cek_temperature();
      cek_intensitas_cahaya();
      cek_cuaca();
      cek_pos_jemuran();

      bot.sendMessage(msg.chat_id, temp, "");
      bot.sendMessage(msg.chat_id, intensitas + cahaya, "");
      bot.sendMessage(msg.chat_id, cuaca, "");
      bot.sendMessage(msg.chat_id, pos_jemuran, "");
      answer = "Itu saja informasi yang dapat diberikan untuk sekarang";
    }
    else if (msg.text == "/bantuan"){
      answer = "Butuh bantuan? Kamu bisa mencoba perintah dibawah ini!\n"
      "/keluarkan untuk mengeluarkan jemuran\n"
      "/masukkan untuk memasukkan jemuran\n"
      "/info untuk mendapatkan informasi suhu, intensitas cahaya, keadaan cuaca, dan keadaan jemuran\n"
      "/bantuan untuk mendapakan bantuan dari bot\n";
    }
    else{
      answer = "Kata kunci salah, coba ketikkan /bantuan";
    }
    bot.sendMessage(msg.chat_id, answer, "Markdown");
  }
}

void bot_setup()
{
  const String commands = F(
    "["
    "{\"command\":\"start\", \"description\":\"Mulai bot!\"},"
    "{\"command\":\"masukkan\", \"description\":\"Memasukkan jemuran\"},"
    "{\"command\":\"keluarkan\", \"description\":\"Mengeluarkan jemuran\"},"
    "{\"command\":\"info\",  \"description\":\"Mendapatkan informasi terkini\"},"
    "{\"command\":\"bantuan\",\"description\":\"Mendapat bantuan dari bot\"}" // no comma on last command
    "]");
  bot.setMyCommands(commands);
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  pinMode(LDRPIN, INPUT);
  pinMode(sensorHujan, INPUT);
  pinMode(buzzer, OUTPUT);
  myservo.attach(servoPin);

  // attempt to connect to Wifi network:
  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  secured_client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  // Check NTP/Time, usually it is instantaneous and you can delete the code below.
  Serial.print("Retrieving time: ");
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  bot_setup();
  
  dht.begin();
}

void loop()
{ 
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  } 
  ldr = analogRead(LDRPIN);
  dataAir = digitalRead(sensorHujan);
  
  jalankan_otomatis();
}
