#include <ESP8266WiFi.h>
 

const char* ssid     = "harsh@7";          //enter your server name 
const char* password = "12345678";                 // your server password

const char* host = "scriabin-searches.000webhostapp.com";  //website url


void setup() {
  Serial.begin(9600);
  delay(500);
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  randomSeed(10);
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected, well");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");          
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");          
  Serial.println(WiFi.gatewayIP());       
}

void loop() {
  
  Serial.print("connecting to "); 
  Serial.println(host);

  WiFiClient client; 
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  int device_id=123;
  String time_stamp="12:32:40";
  int no_sensors=4;
  int s[]={21000,12222,54666,43332,75224};
  
  String url = "/api/upload/insert.php?dev_id="+String(device_id);
  
  for(int i=0;i<4;i++)
    url+="&s"+String(i+1)+"="+String(s[i]);
  url+="&time="+time_stamp+"@";  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 

               "Connection: close\r\n\r\n");                  //uploading data to cloud
  delay(1000);


  
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();

  Serial.println("closing connection");
  delay(2000);


}
