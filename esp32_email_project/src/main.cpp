#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>
#include <HTTPClient.h>
// put function declarations here:

const int dataPin = 1;
DHT dhtClass(dataPin, DHT11);
HTTPClient http;

#define DHTTYPE DHT11
#define wifiName "wifi账号"
#define PassWord "wifi密码"
#define HttpGet "http://本机ip地址:端口号（9090）/demo"

void Wifi_Coonect()
{
  WiFi.begin(wifiName, PassWord);
  while (WiFi.isConnected())
  {
    Serial.print("正在连接wifi中!");
  }
  Serial.print("连接成功");
}

void send_Message()
{
  http.begin(HttpGet);
  int httpCode = http.GET();
  Serial.print(httpCode);
  if (httpCode == 200)
  {
    Serial.print("请求成功");
  }
}

void setup()
{
  // 开始串行通信
  Serial.begin(9600);
  Wifi_Coonect();        // 连接wifi
  dhtClass.begin(DHT11); // 初始化dht
}

void loop()
{
  // 读取温度值
  float dhtTemperature = dhtClass.readTemperature();

  // 读取湿度值
  float dhtHumidity = dhtClass.readHumidity();
  if (isnan(dhtTemperature) || isnan(dhtHumidity))   // 如果读取错误
  {                                  
    Serial.println("读取传感器失败"); // 读取失败提示
    return;
  }
  while (dhtTemperature > 20)  //判断是否超过指定的阈值
  {
    send_Message();   // 发送请求
    break;
  }
  delay(10000);
  Serial.print("我是温度");
  Serial.print(dhtTemperature);
  Serial.print("我是湿度");
  Serial.print(dhtHumidity);
  Serial.print("\n");
}

// put function definitions here:
