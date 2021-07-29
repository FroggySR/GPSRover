#include <Arduino.h>

#include <WiFi.h>

const char *ssid = "UniFi";
//const char *ssid = "SRiPhone";
const char *password = "Logitech";

const IPAddress serverIP(192, 168, 0, 200); //Address to visit
//const IPAddress serverIP(85, 191, 171, 18); //Address to visit External IP
uint16_t serverPort = 200; //Server port number

WiFiClient client; //Declare a client object to connect to the server

String readString;
char c;
char sendBuffer[1024];
int i;
int indexSend = 2;
int lengthRctm = 0;

void setup()
{
    Serial.begin(115200);
    Serial1.begin(115200);

    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false); //Turn off wifi sleep in STA mode to improve response speed
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected!");
    Serial.print("IP address:      ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC address:     ");
    Serial.println(WiFi.macAddress());
    Serial.print("Gateway address: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("Subnet address:  ");
    Serial.println(WiFi.subnetMask());
    Serial.print("SSID Power:      ");
    Serial.println(WiFi.getTxPower());
    Serial.println("");
    delay(100);
}

void loop()
{

    /*
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

*/
    Serial.println("Try to access the server");
    if (client.connect(serverIP, serverPort)) //Try to access the target address
    {
        Serial.println("Visit successful");
        delay(2000);
        //client.print("X");                    //Send data to the server
        while (client.connected() || client.available()) //If it is connected or has received unread data
        {
            //delay(2000);
            //Serial.println("Visit successful");
            //Serial.print("Connected: ");
            //Serial.println(client.connected());
            //Serial.print("Avalible: ");
            //Serial.println(client.available());
            // Earlierer program
            while (client.available()) //If there is data to read
            {

                sendBuffer[indexSend] = client.read();

                if (sendBuffer[indexSend - 1] == 0xd3 && sendBuffer[indexSend] == 0x00 && indexSend != 1) // Find beginning of message
                {
                    sendBuffer[0] = 0xd3;
                    sendBuffer[1] = 0x00;
                    indexSend = 1;
                }

                lengthRctm = (int)sendBuffer[2] + 5; // Get lenght of RCTM message

                if (indexSend > 1023 || indexSend < 0) // Overflow send buffer
                {
                    indexSend = 0;
                    Serial.println("Overflow");
                }

                if (indexSend == lengthRctm && indexSend > 10 && lengthRctm > 10)
                {
                    Serial.print("lengthRctm: ");
                    Serial.println(lengthRctm);

                    if (client.connected() == true)
                    {
                        Serial1.write(sendBuffer, lengthRctm);
                    }
                    /*
    for (int i = 0; i <= lengthRctm; i++)
    {
      if (client.connected() == true)
      {
        client.write(sendBuffer[i]);
      }
      //Serial.print(sendBuffer[i]);
    }
    */

                    Serial1.flush();
                    delay(10);
                }
                // serverBytesSent++;
                //lastSentRTCM_ms = millis();
                indexSend++;
                /*
                if (client.peek() == 0xD3)
                {
                    delay(500);
                    while (client.available()) //If there is data to read
                    {
                        
                        char line = client.read();
                        //Serial.print("Read data:");
                        readString += line;
                        
                          if (readString.length()<1023)
                          {
                            Serial1.print(readString);
                            readString = "";
                          }
                    }
                        Serial1.print(readString);
                        readString = "";
                }
                else
                {
                    while (client.available()) //If there is data to read
                    {

                        client.read();
                      
                    }
                }
                //client.write(line.c_str()); //Send the received data back
                
            }
            


            delay(5);
            */
            }
            //Serial.println("Close the current connection");
            //client.write("X");
            //delay(900);
            //client.stop(); //Close the client
        }
    }
    else
    {
        Serial.println("Access failed");
        client.stop(); //Close the client
    }
}
