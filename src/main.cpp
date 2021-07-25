#include <Arduino.h>

#include <WiFi.h>

const char *ssid = "UniFi";
const char *password = "Logitech";

const IPAddress serverIP(192,168,0,200); //Address to visit
uint16_t serverPort = 200;         //Server port number

WiFiClient client; //Declare a client object to connect to the server

void setup()
{
    Serial.begin(115200);
    Serial1.begin(115200, SERIAL_8N1, 16, 17);

    Serial.println();

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false); //Turn off wifi sleep in STA mode to improve response speed
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected");
    Serial.print("IP Address:");
    Serial.println(WiFi.localIP());
    delay(1000);
    Serial1.print("Test");
    Serial.print("Test");
}

void loop()
{


while(Serial.available())
{
Serial1.print((char)Serial.read());

}
Serial1.flush();



while(Serial1.available())
{
Serial.print((char)Serial1.read());

}

//Serial.println(millis());
//Serial1.println(millis());
//delay(1000);
/*

    Serial.println("Try to access the server");
    if (client.connect(serverIP, serverPort)) //Try to access the target address
    {
        Serial.println("Visit successful");
        delay(100);
        //client.print("X");                    //Send data to the server
        while (client.connected()||client.available()) //If it is connected or has received unread data
        {
            if (client.available()) //If there is data to read
            {
                String line = client.readString();
                //Serial.print("Read data:");
                Serial1.println(line);
                Serial.println(line.length());
                //client.write(line.c_str()); //Send the received data back
            }
        }
        Serial.println("Close the current connection");
        client.write("X");
        delay(900);
        client.stop(); //Close the client
    }
    else
    {
        Serial.println("Access failed");
        client.stop(); //Close the client
    }
    delay(2000);

    */
}
