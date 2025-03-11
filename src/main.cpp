#include <BluetoothSerial.h>
#include <WiFi.h>
#include <unordered_set>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <Arduino.h>
#include <Vector>


BluetoothSerial SerialBT;


void connectToNetwork(const String& ssid, const String& password) 
{
  if (WiFi.SSID() == ssid) 
  {
    Serial.println("Already connected to the specified network.");
    return;
  }

  WiFi.disconnect(true);

  WiFi.begin(ssid.c_str(), password.c_str());

  int tries = 0;
        while (WiFi.status() != WL_CONNECTED && tries < 5) 
        {
          Serial.print(".");
          delay(1000);
          tries++;
        }

  Serial.println();
  if(WiFi.status() == WL_CONNECTED)
  Serial.println("Connected!");
  else
  Serial.println("Couldn't connect to the specified network!");

}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT_Serial");
  WiFi.mode(WIFI_STA);
}

void loop() 
{

  while (!SerialBT.available()) 
  {
    delay(10);
  }

  String input = SerialBT.readString();

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, input);


  if (!error) 
  {
    String action = doc["action"];

      DynamicJsonDocument received_doc(1024);
      JsonObject received = received_doc.to<JsonObject>();
      received["action"] = action;
      received["teamId"] = "B03";

      String received_json;
      serializeJson(received, received_json);

      Serial.println(received_json);

    
    if (action == "getNetworks")
    {
    int num_networks = WiFi.scanNetworks();
    DynamicJsonDocument network_doc(4096);

    std::vector<String>network_ssid;


    for (int i = 0; i < num_networks; i++) 
    {
      
      JsonObject network = network_doc.createNestedObject();

      network_ssid.push_back(WiFi.SSID(i));


      if(count(network_ssid.begin(), network_ssid.end(),WiFi.SSID(i))>1)
      {
        continue;
      }


      network["ssid"] = WiFi.SSID(i);
      network["strength"] = WiFi.RSSI(i);
      network["encryption"] = WiFi.encryptionType(i);
      network["teamId"] = "B03";

      String network_json;
      serializeJson(network, network_json);

      SerialBT.println(network_json);
      Serial.println(network_json);
    }

      network_ssid.clear();

    }


    if (action == "connect") 
    {
      String ssid = doc["ssid"];
      String password = doc["password"];

      connectToNetwork(ssid, password);

      DynamicJsonDocument status_doc(1024);
      JsonObject status = status_doc.to<JsonObject>();
      status["ssid"] = ssid;

      if(WiFi.status() == WL_CONNECTED)
      status["connected"] = true;
      else
      status["connected"]=false;
      status["teamId"] = "B03";

      String status_json;
      serializeJson(status, status_json);

      SerialBT.println(status_json);
      Serial.println(status_json);
    }


    if (action == "getData") 
    {
      HTTPClient http;
      http.begin("http://proiectia.bogdanflorea.ro/api/the-wolf-among-us/characters");

      int httpCode = http.GET();
      if (httpCode == HTTP_CODE_OK) 
      {
        String api_response = http.getString();
        DynamicJsonDocument api_doc(15000);

        DeserializationError error = deserializeJson(api_doc, api_response);

        if (error) 
        {
          Serial.print("deserializeJson() failed: ");
          Serial.println(error.c_str());
          return;
        }

        JsonArray objects = api_doc.as<JsonArray>();
        for (JsonObject obj : objects) 
        {
          int id = obj["id"];
          const char* name = obj["name"];
          const char* imagePath = obj["imagePath"];

          JsonObject newObject = doc.to<JsonObject>();
          newObject["id"] = id;
          newObject["name"] = name;
          newObject["image"] = imagePath;
          newObject["teamId"] = "B03";  

          String result;
          serializeJson(newObject, result);

          Serial.println(result);
          SerialBT.println(result);
        }
        http.end();
      }
    }

    if(action=="getDetails")
    {
      String ID=doc["id"];
      HTTPClient http;
      http.begin("http://proiectia.bogdanflorea.ro/api/the-wolf-among-us/character?id="+ID);

      int httpCode = http.GET();
      if (httpCode == HTTP_CODE_OK) {
        String api_response = http.getString();
        DynamicJsonDocument api_doc(15000);

        DeserializationError error = deserializeJson(api_doc, api_response);

        if (error) {
          Serial.print("deserializeJson() failed: ");
          Serial.println(error.c_str());
          return;
        }

        JsonObject object = api_doc.as<JsonObject>();
      
          int id = object["id"];
          const char* name = object["name"];
          String species=object["species"];
          String gender=object["gender"];
          String occupation=object["occupation"];
          String hairColour=object["hairColour"];
          String eyeColour=object["eyeColour"];
          String description=object["description"];
          const char* imagePath = object["imagePath"];
          String type=object["type"];

          JsonObject newObject = doc.to<JsonObject>();
          newObject["id"] = id;
          newObject["name"] = name;
          newObject["image"] = imagePath;
          newObject["description"]="Species: "+species+"\n"+"Gender: "+gender+"\n"+"Occupation: "+occupation+"\n"+"Hair Colour: "+hairColour+"\n"+"Eye Colour: "+eyeColour+"\n"+"Type: "+type+"\n"+"Description:\n"+description;
          newObject["teamId"] = "B03";  

          String result;
          serializeJson(newObject, result);

          Serial.println(result);
          SerialBT.println(result);
        
        http.end();
      }
    }
  }
}