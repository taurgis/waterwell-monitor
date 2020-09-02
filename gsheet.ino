#include "HTTPSRedirect.h"

const char* host = "script.google.com";
const char *GScriptId = "";
const int httpsPort = 443; //the https port is same
String url = String("/macros/s/") + GScriptId + "/exec?value=Temperature";
String payload_base =  "{\"command\": \"appendRow\", \
                    \"sheet_name\": \"Gegevens\", \
                       \"values\": ";
String payload = "";

HTTPSRedirect* client = nullptr;

void addRowToSheet(int litersRemaining) {
  payload = payload_base + "\"" + litersRemaining + "\"}";

  client = new HTTPSRedirect(httpsPort);
  client->setInsecure();
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");
  Serial.print("Connecting to ");
  Serial.println(host);          //try to connect with "script.google.com"

  if (client != nullptr) {
    if (!client->connected()) {
      client->connect(host, httpsPort);
      client->POST(url, host, payload, false);
      Serial.println("Sent");
    }
  }

  delete client;
}
