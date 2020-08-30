#include <ESP8266WiFi.h>
#include <EEPROM.h>

// ESP8266WebServer server(80);

const char* ssid     = "";
const char* password = "";

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
  
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  /**
  server.on("/index.html", handleHomepage);
  server.on("/well.html", handleWell);

  server.begin();
  */
}

/**
void handleHomepage() {
  String result = "";
  result += generateHTMLHead();
  result += generateHTMLBody(false);
  result += generateHTMLFooter();

  server.send(200, "text/html", result);
}

void handleWell() {
  String result = "";
  for (int i = 0; i < server.args(); i++) {
    Serial.println("");
    Serial.println("Received arg: ");
    Serial.print(server.argName(i));
    Serial.print(", ");
    Serial.print(server.arg(i));


    if (server.argName(i) == "diameter") {
      EEPROM.write(1, server.arg(i).toInt());
      diameter = server.arg(i).toInt();
    }

    if (server.argName(i) == "depth") {
      EEPROM.write(2, server.arg(i).toInt());
      depth = server.arg(i).toInt();
    }

    if (server.argName(i) == "distance") {
      EEPROM.write(3, server.arg(i).toInt());
      distance = server.arg(i).toInt();
      EEPROM.commit();
    }
  }

  result += generateHTMLHead();
  result += generateHTMLBody(true);
  result += generateHTMLFooter();

  server.send(200, "text/html", result);
}

String generateHTMLHead() {
  return "<!DOCTYPE html><html class=\"h-100\"><head> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css\" integrity=\"sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm\" crossorigin=\"anonymous\"> <link rel=\"stylesheet\" href=\"https://use.fontawesome.com/releases/v5.8.2/css/all.css\" integrity=\"sha384-oS3vJWv+0UjzBfQzYUhtDYW+Pj2yciDJxpsK1OYPAYjqT085Qq/1cq5FLXAZQ7Ay\" crossorigin=\"anonymous\"> <link href=\"https://fonts.googleapis.com/css?family=Nunito:200,200i,300,300i,400,400i,600,600i,700,700i,800,800i,900,900i\" rel=\"stylesheet\"> <style> body { font-family: Nunito, -apple-system, BlinkMacSystemFont, \"Segoe UI\", Roboto, \"Helvetica Neue\", Arial, sans-serif, \"Apple Color Emoji\", \"Segoe UI Emoji\", \"Segoe UI Symbol\", \"Noto Color Emoji\"; } .bg-main { background-color: #4e73df; } .sidebar-divider { border-top: 1px solid rgba(255, 255, 255, .15); } .text-decoration-none:hover { text-decoration: none; } .sidebar-heading { color: rgba(255, 255, 255, .4); font-weight: 800; font-size: .65rem; text-transform: uppercase; } .text-sidebar { color: rgba(255, 255, 255, .8); } .text-gray-800 { color: #5a5c69 !important; } </style></head><body class=\"h-100\"> <div class=\"container-fluid h-100\"> <div class=\"row \"> <div class=\"col-2 text-left bg-main my-auto pt-2 text-center\"> <svg height=\"50\" aria-hidden=\"true\" focusable=\"false\" data-prefix=\"fas\" data-icon=\"water\" class=\"svg-inline--fa fa-water fa-w-18\" role=\"img\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 576 512\"><path fill=\"currentColor\" d=\"M562.1 383.9c-21.5-2.4-42.1-10.5-57.9-22.9-14.1-11.1-34.2-11.3-48.2 0-37.9 30.4-107.2 30.4-145.7-1.5-13.5-11.2-33-9.1-46.7 1.8-38 30.1-106.9 30-145.2-1.7-13.5-11.2-33.3-8.9-47.1 2-15.5 12.2-36 20.1-57.7 22.4-7.9.8-13.6 7.8-13.6 15.7v32.2c0 9.1 7.6 16.8 16.7 16 28.8-2.5 56.1-11.4 79.4-25.9 56.5 34.6 137 34.1 192 0 56.5 34.6 137 34.1 192 0 23.3 14.2 50.9 23.3 79.1 25.8 9.1.8 16.7-6.9 16.7-16v-31.6c.1-8-5.7-15.4-13.8-16.3zm0-144c-21.5-2.4-42.1-10.5-57.9-22.9-14.1-11.1-34.2-11.3-48.2 0-37.9 30.4-107.2 30.4-145.7-1.5-13.5-11.2-33-9.1-46.7 1.8-38 30.1-106.9 30-145.2-1.7-13.5-11.2-33.3-8.9-47.1 2-15.5 12.2-36 20.1-57.7 22.4-7.9.8-13.6 7.8-13.6 15.7v32.2c0 9.1 7.6 16.8 16.7 16 28.8-2.5 56.1-11.4 79.4-25.9 56.5 34.6 137 34.1 192 0 56.5 34.6 137 34.1 192 0 23.3 14.2 50.9 23.3 79.1 25.8 9.1.8 16.7-6.9 16.7-16v-31.6c.1-8-5.7-15.4-13.8-16.3zm0-144C540.6 93.4 520 85.4 504.2 73 490.1 61.9 470 61.7 456 73c-37.9 30.4-107.2 30.4-145.7-1.5-13.5-11.2-33-9.1-46.7 1.8-38 30.1-106.9 30-145.2-1.7-13.5-11.2-33.3-8.9-47.1 2-15.5 12.2-36 20.1-57.7 22.4-7.9.8-13.6 7.8-13.6 15.7v32.2c0 9.1 7.6 16.8 16.7 16 28.8-2.5 56.1-11.4 79.4-25.9 56.5 34.6 137 34.1 192 0 56.5 34.6 137 34.1 192 0 23.3 14.2 50.9 23.3 79.1 25.8 9.1.8 16.7-6.9 16.7-16v-31.6c.1-8-5.7-15.4-13.8-16.3z\"></path></svg> <hr class=\"sidebar-divider my-0\"> </div> <div class=\"col-10 d-flex justify-content-between\" style=\"z-index: 1;box-shadow: 0 .15rem 1.75rem 0 rgba(58,59,69,.15)!important;\"> <span class=\"pt-4 font-weight-bold\" style=\"font-size: 22px;\">V 0.1 (ALPHA)</span> <a href=\"https://github.com/taurgis/waterwell-monitor\" target=\"_blank\" style=\"font-size: 22px;\" class=\"text-decoration-none d-inline pt-4\"> <span class=\"mr-2 d-none d-lg-inline text-gray-600 small\">View on GitHub</span> <i class=\"fab fa-github\"></i> </a> </div> </div> <div class=\"row\" style=\"height: calc(100% - 95.5px);\"> <div class=\"col-md-2 bg-main pt-2\"> <a class=\"text-white text-decoration-none\" href=\"index.html\"> <i class=\"fas fa-fw fa-tachometer-alt\"></i> <span class=\"ml-1\">Dashboard</span> </a> <hr class=\"sidebar-divider my-2\"> <div class=\"sidebar-heading\"> Configuration </div> <a class=\"text-decoration-none d-block mt-2 text-sidebar\" href=\"well.html\"> <i class=\"fas fa-fw fa-cog\"></i> <span class=\"ml-1 \">Well</span> </a> <a class=\"text-decoration-none d-block mt-2 text-sidebar\" href=\"measurements.html\"> <i class=\"fas fa-fw fa-chart-area\"></i> <span class=\"ml-1 \">Measurements</span> </a> </div>";
}

String generateHTMLBody(boolean isWellPage) {
  if (isWellPage == true) {
    String body = "<div class=\"col-md-10\" style=\"background-color: #f8f9fc;\"> <h1 class=\"h3 mb-0 text-gray-800 mt-3\">Well settings</h1> <p class=\"mt-3\"> Here the well settings need to be configured to do a correct calculation of the volume of water present. </p> <div class=\"container-fluid\"> <div class=\"row\"> <div class=\"col-12 col-md-6 col-lg-4\"> <p> <form class=\"w-100\" method=\"GET\" action=\"/well.html\"> <div class=\"form-group\"> <label for=\"diameter\" class=\"font-weight-bold\">Well diameter</label> <input value=";
    body += diameter;
    body += " required type=\"text\" class=\"form-control\" name=\"diameter\" aria-describedby=\"diameterHelp\" placeholder=\"e.g. 250\"> <small id=\"diameterHelp\" class=\"form-text text-muted\">The diameter of the well in CM.</small> </div> <div class=\"form-group\"> <label for=\"depth\" class=\"font-weight-bold\">Well depth</label> <input value=";
    body += depth;
    body += " required type=\"text\" class=\"form-control\" name=\"depth\" placeholder=\"e.g. 200\" aria-describedby=\"depthHelp\"> <small id=\"depthHelp\" class=\"form-text text-muted\">The depth of the well in CM.</small> </div> <div class=\"form-group\"> <label for=\"distance\" class=\"font-weight-bold\">Meter distance</label> <input value=";
    body += distance;
    body += " required type=\"text\" class=\"form-control\" name=\"distance\" placeholder=\"e.g. 40\" aria-describedby=\"distanceHelp\"> <small id=\"distanceHelp\" class=\"form-text text-muted\">The distance of the meter above the well in CM. (For example if you put it in the shaft above it).</small> </div> <button type=\"submit\" class=\"btn btn-primary w-100\">Save</button> </form> </p> </div> </div> </div> </div>";

    return body;
  } else {
    return "<div class=\"col-md-10\" style=\"background-color: #f8f9fc;\"> <h1 class=\"h3 mb-0 text-gray-800 mt-3\">Dashboard</h1> <p class=\"mt-3\"> Thank you for using the Water Well Monitor which is currently under development. </p> <p> To get started go to the well settings to configure your well configuration (height, diameter, ...). <br />After this has been done please configure when measurements need to be taken in the measurements setting. </p> </div>";
  }
}

String generateHTMLFooter() {
  return "</div> <div class=\"row \"> <div class=\"col-md-2 bg-main pt-2\"> </div> <div class=\"col-10\"> <footer class=\"sticky-footer bg-white\"> <div class=\"container\"> <div class=\"copyright text-center my-auto\"> <a href=\"https://www.thomastheunen.eu\" class=\"text-decoration-none text-secondary\"><span>Copyright © Thomas Theunen 2019</span></a> </div> </div> </footer> </div> </div> </div></body></html>";
}

void handleRequests() {
  server.handleClient();
}

*/
