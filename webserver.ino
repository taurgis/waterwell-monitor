#include <ESP8266WiFi.h>

const char* ssid     = "";
const char* password = "";

WiFiServer server(80);
WiFiClient client;

String header;

/**
   Initializes the WIFI connection, once that succeeds the server is started and the local IP is given.
*/
void initializeServer() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

/**
   Generates the HEAD part of the standard page.

   NOTE: This contains an external Bootstrap 4.00 css file, so the client needs internet access for this to work.
*/
void generateHTMLHead() {
  client.println("<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css\" integrity=\"sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm\" crossorigin=\"anonymous\"></head>");
}

void generateHTMLBody() {
  client.println("<body><div class=\"container\">");
  client.println("<div class =\"row\"><div class=\"col-12 mt-4\"><h1>Water Well Monitor 0.1</h1></div></div>");
  client.println("<div class=\"row\"><div class=\"col-12 mt-4\"></div></div>");
  client.println("</div></body></html>");
}

/**
   Handles all incoming requests if a client is present. If no client is present, just continue on.
*/
void handleRequests() {
  client = server.available();

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {

          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Display the HTML web page
            generateHTMLHead();
            generateHTMLBody();


            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
