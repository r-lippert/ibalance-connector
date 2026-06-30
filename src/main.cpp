#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "config.h"

#define BAUD_RATE 2400

auto &usbSerial = Serial;
EspSoftwareSerial::UART testSerial;

WiFiClient espClient;
PubSubClient client(espClient);
char msg[10];

void setup_wifi()
{

  Serial.begin(9600);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSPHRASE);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Experience the magic of MQTT");
  delay(2000);
}
void setup()
{
  usbSerial.begin(9600);
  testSerial.begin(BAUD_RATE, EspSoftwareSerial::SWSERIAL_8O2, RX_PIN, TX_PIN, false, 95, 11);

  usbSerial.println(PSTR("\nSoftware serial test started"));
  setup_wifi();
  client.setServer(MQTT_HOST, MQTT_PORT);
}

int line = 0;
int column = 0;
char lineData[20];
char prevLine[2][20];
char prevState = 0;

void pubLine()
{
  lineData[column] = 0;
  if (line == 1)
  {
    if (strcmp(prevLine[0], lineData) != 0)
    {
      client.publish("ibalance/line1", lineData);
      strcpy(prevLine[0], lineData);
    }
  }
  else
  {
    if (strcmp(prevLine[1], lineData) != 0)
    {
      client.publish("ibalance/line2", lineData);
      strcpy(prevLine[1], lineData);
    }
  }
}

void pubState(char state)
{
  if (state != prevState)
  {
    snprintf(msg, 10, "%d", state);
    client.publish("ibalance/state", msg);
    prevState = state;
  }
}

void reconnect()
{

  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop()
{
  char myByte;

  while (testSerial.available() > 0)
  {
    myByte = testSerial.read();

    if (myByte < 32 && column > 0)
    {
      pubLine();
    }

    if (myByte == 26 || myByte == 27)
    {
      line = myByte - 25;
      column = 0;
    }
    if (myByte >= 32 && line > 0)
    {
      lineData[column] = myByte;
      column++;
    }
    if (myByte < 26)
    {
      pubState(myByte);
    }
    yield();
  }
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
}
