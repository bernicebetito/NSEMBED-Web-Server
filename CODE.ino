/*
BETITO, Bernice Marie M.
NSEMBED - S11
MAJOR PROJECT
*/

#include <WiFi.h>

int led_pin = 2;
WiFiServer wifiServer(80);

String str_blink_pattern = "";
int int_blink_pattern = 0;

static SemaphoreHandle_t bin_sem;

// Give the Binary Semaphore in case client sent a new request
void checkClient(){
  xSemaphoreGive(bin_sem);
  vTaskDelay(100 / portTICK_PERIOD_MS);
  xSemaphoreTake(bin_sem, portMAX_DELAY);
}

// Long spaces between the dashes and dots
int long_spaces(int current) {
  int curr_blink_pattern = 0;
  checkClient();
  
  digitalWrite(led_pin, LOW);
  vTaskDelay(200 / portTICK_PERIOD_MS);

  checkClient();
  curr_blink_pattern = int_blink_pattern;
  if(current == curr_blink_pattern){return current;}
  return 0;
}

// Short spaces between the dashes and dots
int short_spaces(int current) {
  int curr_blink_pattern = 0;
  checkClient();
  
  digitalWrite(led_pin, LOW);
  vTaskDelay(100 / portTICK_PERIOD_MS);

  checkClient();
  curr_blink_pattern = int_blink_pattern;
  if(current == curr_blink_pattern){return current;}
  return 0;
}

// Dashes in the pattern ( - )
int dashes(int current) {
  int curr_blink_pattern = 0;
  checkClient();
  
  digitalWrite(led_pin, HIGH);
  vTaskDelay(2400 / portTICK_PERIOD_MS);

  checkClient();
  curr_blink_pattern = int_blink_pattern;
  if(current == curr_blink_pattern){return short_spaces(current);}
  return 0;
}

// Dots in the pattern ( . )
int dots(int current) {
  int curr_blink_pattern = 0;
  checkClient();
  
  digitalWrite(led_pin, HIGH);
  vTaskDelay(500 / portTICK_PERIOD_MS);

  checkClient();
  curr_blink_pattern = int_blink_pattern;
  if(current == curr_blink_pattern){return short_spaces(current);}
  return 0;
}

// Blink Patterns
void blink_pattern(void *parameters) {
  int chosen_pattern = *(int *)parameters;
  int ctr = 0, curr_pattern = 0;

  // Wait until a valid pattern has been chosen
  while (chosen_pattern <=0 || chosen_pattern > 4){
    xSemaphoreTake(bin_sem, portMAX_DELAY);
    chosen_pattern = *(int *)parameters;
    xSemaphoreGive(bin_sem);
  }

  xSemaphoreTake(bin_sem, portMAX_DELAY);
  while (1) {
    // Reset Button was clicked
    // Wait until a new pattern has been chosen
    if (chosen_pattern == 4 || curr_pattern == 4) {
      xSemaphoreGive(bin_sem);
      while (chosen_pattern == 4 || curr_pattern == 4) {
        chosen_pattern = *(int *)parameters;
        curr_pattern = chosen_pattern;
        digitalWrite(led_pin, LOW);
        vTaskDelay(100 / portTICK_PERIOD_MS);
      }
      xSemaphoreTake(bin_sem, portMAX_DELAY);
    }

    // Five second light, signify start of pattern
    if (chosen_pattern > 0 && chosen_pattern <= 3){
      digitalWrite(led_pin, HIGH);
      vTaskDelay(4900 / portTICK_PERIOD_MS);
      chosen_pattern = short_spaces(chosen_pattern);
    }
    
    if (chosen_pattern == 1) {  // Chosen pattern is #1 (NSEMBED)
      // NSEMBED = -. ... . -- -... . -..
      // START
      curr_pattern = dashes(1);
      if(curr_pattern == chosen_pattern){
        curr_pattern = dots(1);
        if(curr_pattern == chosen_pattern){
          curr_pattern = long_spaces(1);
          if(curr_pattern == chosen_pattern){
            for (ctr = 0; ctr < 3 && curr_pattern == chosen_pattern; ctr++){
              curr_pattern = dots(1);
              if (curr_pattern != chosen_pattern){
                ctr = 5;
              }
            }
            if(curr_pattern == chosen_pattern){
              curr_pattern = long_spaces(1);
              if(curr_pattern == chosen_pattern){
                curr_pattern = dots(1);
                if(curr_pattern == chosen_pattern){
                  curr_pattern = long_spaces(1);
                  if(curr_pattern == chosen_pattern){
                    for (ctr = 0; ctr < 2 && curr_pattern == chosen_pattern; ctr++){
                      curr_pattern = dashes(1);
                      if(curr_pattern != chosen_pattern){
                        ctr = 5;
                      }
                    }
                    if(curr_pattern == chosen_pattern) {
                      curr_pattern = dashes(1);
                      if(curr_pattern == chosen_pattern) {
                        for (ctr = 0; ctr < 3 && curr_pattern == chosen_pattern; ctr++){
                          curr_pattern = dots(1);
                          if (curr_pattern != chosen_pattern){
                            ctr = 5;
                          }
                        }
                        if(curr_pattern == chosen_pattern){
                          curr_pattern = long_spaces(1);
                          if(curr_pattern == chosen_pattern){
                            curr_pattern = dots(1);
                            if(curr_pattern == chosen_pattern){
                              curr_pattern = long_spaces(1);
                              if(curr_pattern == chosen_pattern){
                                curr_pattern = dashes(1);
                                if(curr_pattern == chosen_pattern){
                                  for (ctr = 0; ctr < 2 && curr_pattern == chosen_pattern; ctr++){
                                    curr_pattern = dots(1);
                                    if (curr_pattern != chosen_pattern){
                                      ctr = 5;
                                    }
                                  }
                                  // END
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    } else if (chosen_pattern == 2) { // Chosen pattern is #2 (Bernice)
      // Bernice = -... . .-. -. .. -.-. .
      // START
      curr_pattern = dashes(2);
      if(curr_pattern == chosen_pattern){
        for (ctr = 0; ctr < 3 && curr_pattern == chosen_pattern; ctr++){
          curr_pattern = dots(2);
          if (curr_pattern != chosen_pattern){
            ctr = 5;
          }
        }
        if(curr_pattern == chosen_pattern){
          curr_pattern = long_spaces(2);
          if(curr_pattern == chosen_pattern){
            curr_pattern = dots(2);
            if(curr_pattern == chosen_pattern){
              curr_pattern = long_spaces(2);
              if(curr_pattern == chosen_pattern){
                curr_pattern = dots(2);
                if(curr_pattern == chosen_pattern){
                  curr_pattern = dashes(2);
                  if(curr_pattern == chosen_pattern){
                    curr_pattern = dots(2);
                    if(curr_pattern == chosen_pattern){
                      curr_pattern = long_spaces(2);
                      if(curr_pattern == chosen_pattern){
                        curr_pattern = dashes(2);
                        if(curr_pattern == chosen_pattern){
                          curr_pattern = dots(2);
                          if(curr_pattern == chosen_pattern){
                            curr_pattern = long_spaces(2);
                            if(curr_pattern == chosen_pattern){
                              for (ctr = 0; ctr < 2 && curr_pattern == chosen_pattern; ctr++){
                                curr_pattern = dots(2);
                                if (curr_pattern != chosen_pattern){
                                  ctr = 5;
                                }
                              }
                              if(curr_pattern == chosen_pattern){
                                curr_pattern = long_spaces(2);
                                if(curr_pattern == chosen_pattern){
                                  curr_pattern = dashes(2);
                                  if(curr_pattern == chosen_pattern){
                                    curr_pattern = dots(2);
                                    if(curr_pattern == chosen_pattern){
                                      curr_pattern = dashes(2);
                                      if(curr_pattern == chosen_pattern){
                                        curr_pattern = dots(2);
                                        if(curr_pattern == chosen_pattern){
                                          curr_pattern = long_spaces(2);
                                          if(curr_pattern == chosen_pattern){
                                            curr_pattern = dots(2);
                                          }
                                          // END
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    } else if (chosen_pattern == 3) { // Chosen pattern is #3 (Betito)
      // Betito = -... . - .. - ---
      // START
      curr_pattern = dashes(3);
      if(curr_pattern == chosen_pattern){
        for (ctr = 0; ctr < 3 && curr_pattern == chosen_pattern; ctr++){
          curr_pattern = dots(3);
          if (curr_pattern != chosen_pattern){
            ctr = 5;
          }
        }
        if(curr_pattern == chosen_pattern){
          curr_pattern = long_spaces(3);
          if(curr_pattern == chosen_pattern){
            curr_pattern = dots(3);
            if(curr_pattern == chosen_pattern){
              curr_pattern = long_spaces(3);
              if(curr_pattern == chosen_pattern){
                curr_pattern = dashes(3);
                if(curr_pattern == chosen_pattern){
                  curr_pattern = long_spaces(3);
                  if(curr_pattern == chosen_pattern){
                    for (ctr = 0; ctr < 2 && curr_pattern == chosen_pattern; ctr++){
                      curr_pattern = dots(3);
                      if (curr_pattern != chosen_pattern){
                        ctr = 5;
                      }
                    }
                    if(curr_pattern == chosen_pattern){
                      curr_pattern = long_spaces(3);
                      if(curr_pattern == chosen_pattern){
                        curr_pattern = dashes(3);
                        if(curr_pattern == chosen_pattern){
                          curr_pattern = long_spaces(3);
                          if(curr_pattern == chosen_pattern){
                            for (ctr = 0; ctr < 3 && curr_pattern == chosen_pattern; ctr++){
                              curr_pattern = dashes(3);
                              if (curr_pattern != chosen_pattern){
                                ctr = 5;
                              }
                            }
                            // END
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    // Five seconds off, signify end of pattern
    digitalWrite(led_pin, LOW);
    vTaskDelay(4900 / portTICK_PERIOD_MS);
    checkClient();
    chosen_pattern = *(int *)parameters;
    curr_pattern = chosen_pattern;
  }
}

// Setup the server
void setup() {
  String temp_ssid, temp_password;
  unsigned int len_ssid, len_password;
  
  Serial.begin(115200);
  delay(1000);
  WiFi.mode(WIFI_AP_STA);

  // Ask for the SSID
  Serial.println("Enter the SSID");
  while(Serial.available() <= 0);
  temp_ssid = Serial.readString();
  len_ssid = temp_ssid.length();

  // Ask for the password
  Serial.println("Enter the password");
  while(Serial.available() <= 0);
  temp_password = Serial.readString();
  len_password = temp_password.length();

  char ssid[len_ssid];
  char password[len_password];
  
  temp_ssid.toCharArray(ssid, len_ssid);
  temp_password.toCharArray(password, len_password);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.print("\nConnected to the WiFi network\nIP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  
  wifiServer.begin();
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);

  // Create the Binary Semaphore and start the Blink Pattern task
  bin_sem = xSemaphoreCreateBinary();
  xSemaphoreGive(bin_sem);
  xTaskCreate(blink_pattern,"Blink Pattern", 1024,(void *)&int_blink_pattern, 1, NULL);
}

// Continuously check if there is a client
void loop() {
  WiFiClient client = wifiServer.available();
  String current_string = "";
  if (client) {
    char previous_one, previous_two;
    while (client.connected()) {
      if (client.available()) {
        char current_char = client.read();
        Serial.write(current_char);

        // Check if end of HTTP message
        if (previous_two == '\n' && previous_one == '\r' && current_char == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println("<!DOCTYPE html>");
          client.println("<html>");
          client.println("    <head>");
          client.println("        <title>MAJOR PROJECT</title>");
          client.println("        <meta charset=\"UTF-8\">");
          client.println("        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("        <link rel=\"preconnect\" href=\"https://fonts.googleapis.com\">");
          client.println("        <link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin>");
          client.println("        <link href=\"https://fonts.googleapis.com/css2?family=Barlow&display=swap\" rel=\"stylesheet\">");
          client.println("        <style>");
          client.println("            /*----- Scrollbar -----*/");
          client.println("            ::-webkit-scrollbar {");
          client.println("                width: 10px;");
          client.println("            }");
          client.println("            ::-webkit-scrollbar-track {");
          client.println("                background-color: #191919;");
          client.println("            }");
          client.println("            ::-webkit-scrollbar-thumb {");
          client.println("                background: #191919;");
          client.println("                border: 2px solid #4B4BE2;");
          client.println("                border-radius: 10px;");
          client.println("            }");
          client.println("            ::-webkit-scrollbar-thumb:hover {");
          client.println("                background: #4B4BE2;");
          client.println("                border: 2px solid #191919;");
          client.println("            }");
          
          client.println("            html {");
          client.println("                position: relative;");
          client.println("                min-height: 100%;");
          client.println("            }");
          client.println("            body {");
          client.println("                background-color: #FFFFFF;");
          client.println("                color: #FFFFFF;");
          client.println("                font-family: 'Barlow', sans-serif;");
          client.println("                align-items: center;");
          client.println("                justify-content: center;");
          client.println("                text-align: center;");
          client.println("                margin: 0px;");
          client.println("                padding: 0px;");
          client.println("            }");
          
          client.println("            /*----- Header and Task -----*/");
          client.println("            header {");
          client.println("                display: flex;");
          client.println("                background-color: #000000;");
          client.println("                height: 125px;");
          client.println("            }");
          client.println("            #header-p {");
          client.println("                align-self: flex-end;");
          client.println("                margin: 0px auto 15px auto;");
          client.println("                font-size: 30px;");
          client.println("                letter-spacing: 5px;");
          client.println("            }");
          client.println("            #task {");
          client.println("                background-color: #191919;");
          client.println("                margin: 0px;");
          client.println("                padding: 5px;");
          client.println("            }");
          client.println("            #task-header {");
          client.println("                margin: 5px 0px;");
          client.println("                padding: 0px;");
          client.println("                letter-spacing: 2px;");
          client.println("            }");
          client.println("            #task-p {");
          client.println("                background-color: #191919;");
          client.println("                font-size: 13px;");
          client.println("                max-width: 80%;");
          client.println("                margin: 5px auto 10px auto;");
          client.println("            }");
          
          client.println("            /*----- Grid Container -----*/");
          client.println("            .grid-container {");
          client.println("                display: grid;");
          client.println("                grid-template-columns: auto auto auto;");
          client.println("                grid-gap: 0px 30px;");
          client.println("                align-items: center;");
          client.println("                justify-content: center;");
          client.println("                margin-top: 50px;");
          client.println("            }");
          client.println("            .grid-item-p {");
          client.println("                display: flex;");
          client.println("                align-content: center;");
          client.println("                justify-content: center;");
          client.println("            }");
          client.println("            .grid-item-instructions, .grid-item-current, .grid-item-guide {");
          client.println("                grid-column: 1 / span 3;");
          client.println("                background-color: #FFFFFF;");
          client.println("                border-radius: 4px;");
          client.println("            }");
          client.println("            .grid-item-instructions, .grid-item-guide {");
          client.println("                color: #191919;");
          client.println("                border: 2px solid #191919;");
          client.println("            }");
          client.println("            .grid-item-current {");
          client.println("                color: #E6E6E6;");
          client.println("                border: 2px solid #E6E6E6;");
          client.println("            }");
          
          client.println("            /*----- Gaps between rows -----*/");
          client.println("            .gap-top {");
          client.println("                grid-column: 1 / span 3;");
          client.println("                height: 50px;");
          client.println("            }");
          client.println("            .gap-mid {");
          client.println("                grid-column: 1 / span 3;");
          client.println("                height: 5px;");
          client.println("            }");
          client.println("            .gap-bottom {");
          client.println("                grid-column: 1 / span 3;");
          client.println("                height: 15px;");
          client.println("            }");
          
          client.println("            /*----- Instructions / Guide -----*/");
          client.println("            #instructions-header {");
          client.println("                font-weight: bolder;");
          client.println("                font-size: 12px;");
          client.println("                margin-bottom: 5px;");
          client.println("            }");
          client.println("            #instructions-body {");
          client.println("                font-size: 15px;");
          client.println("                margin: 5px 15px 10px 15px;");
          client.println("            }");
          client.println("            #instructions-body em, #guide-p em {");
          client.println("                font-style: normal;");
          client.println("                color: #4B4BE2;");
          client.println("                font-weight: bolder;");
          client.println("            }");
          client.println("            #guide-p  {");
          client.println("                font-size: 13px;");
          client.println("                max-width: 575px;");
          client.println("            }");
          
          client.println("            /*----- Pattern Buttons -----*/");
          client.println("            .patternbutton {");
          client.println("                font-family: 'Barlow', sans-serif;");
          client.println("                font-weight: bolder;");
          client.println("                font-size: 12px;");
          client.println("                text-decoration: none;");
          client.println("                outline: none;");
          client.println("                color: #FFFFFF;");
          client.println("                background-color: #191919;");
          client.println("                border: 2px solid #191919;");
          client.println("                border-radius: 8px;");
          client.println("                height: 50px;");
          client.println("                width: 150px;");
          client.println("                transition: 0.5s;");
          client.println("                cursor: pointer;");
          client.println("            }");
          client.println("            .patternbutton:hover {");
          client.println("                background-color: #FFFFFF;");
          client.println("                color: #191919;");
          client.println("                transition: 0.5s;");
          client.println("            }");
          
          client.println("            /*----- Reset Button -----*/");
          client.println("            #resetbutton {");
          client.println("                font-family: 'Barlow', sans-serif;");
          client.println("                font-weight: bolder;");
          client.println("                text-decoration: none;");
          client.println("                outline: none;");
          client.println("                color: #FFFFFF;");
          client.println("                background-color: #FF460E;");
          client.println("                border: 2px solid #FF460E;");
          client.println("                border-radius: 8px;");
          client.println("                height: 40px;");
          client.println("                width: 150px;");
          client.println("                transition: 0.5s;");
          client.println("                cursor: pointer;");
          client.println("            }");
          client.println("            #resetbutton:hover {");
          client.println("                background-color: #FFFFFF;");
          client.println("                color: #FF460E;");
          client.println("                transition: 0.5s;");
          client.println("            }");
          client.println("            #resetbutton:disabled {");
          client.println("                background-color: #EE8D6F;");
          client.println("                border: 2px solid #EE8D6F;");
          client.println("                cursor: not-allowed;");
          client.println("                transition: 0.5s;");
          client.println("            }");
          
          client.println("            /*----- Caption -----*/");
          client.println("            .caption {");
          client.println("                display: table-cell;");
          client.println("                vertical-align: middle;");
          client.println("                width: 150px;");
          client.println("                height: 20px;");
          client.println("                color: #191919;");
          client.println("                font-size: 13px;");
          client.println("                margin: 5px;");
          client.println("                padding: 0px;");
          client.println("                border: 2px solid #191919;");
          client.println("                border-radius: 4px;");
          client.println("            }");
          
          client.println("            /*----- Current Chosen Pattern -----*/");
          client.println("            #curr-header {");
          client.println("                font-size: 13px;");
          client.println("                font-weight: bolder;");
          client.println("            }");
          client.println("            #curr-pattern {");
          client.println("                font-size: 20px;");
          client.println("                font-weight: bolder;");
          client.println("                letter-spacing: 2px;");
          client.println("            }");
          client.println("            .chosen-button {");
          client.println("                background-color: #4B4BE2;");
          client.println("                border: 2px solid #4B4BE2;");
          client.println("                color: #FFFFFF;");
          client.println("                box-shadow: 0 10px 14px 0 rgba(0, 0, 0, 0.527), 0 15px 48px 0 rgba(0, 0, 0, 0.514);");
          client.println("            }");
          client.println("            .chosen-p {");
          client.println("                border: 2px solid #FFFFFF;");
          client.println("                background-color: #FFFFFF;");
          client.println("                box-shadow: 0 10px 14px 0 rgba(0, 0, 0, 0.527), 0 15px 48px 0 rgba(0, 0, 0, 0.514);");
          client.println("            }");
          
          client.println("            /*----- Footer -----*/");
          client.println("            footer {");
          client.println("                position: absolute;");
          client.println("                bottom: 0;");
          client.println("                left: 0;");
          client.println("                height: 100px;");
          client.println("                width: 100%;");
          client.println("                background-color: #191919;");
          client.println("                letter-spacing: 2px;");
          client.println("            }");
          client.println("        </style>");
          client.println("    </head>");
          client.println("    <body>");
          client.println("        <header>");
          client.println("            <b id=\"header-p\">NSEMBED - S11 MAJOR PROJECT</b>");
          client.println("        </header>");
          
          client.println("        <div id=\"task\">");
          client.println("            <p id=\"task-header\">Task:</p>");
          client.println("            <p id=\"task-p\">");
          client.println("                A web server can be programmed on the ESP32 board that can show a web page. The web page on the ESP32");
          client.println("                board should allow a user to command the ESP32 board to change the blinking pattern of the built-in by clicking");
          client.println("                on a link. There should be three blinking pattern on the ESP32 board.");
          client.println("            </p>");
          client.println("        </div>");
          client.println("        ");
          client.println("        <div style=\"margin-bottom: 150px;\">");
          client.println("            <div class=\"grid-container\">");
          client.println("                <div id=\"instructions-div\" class=\"grid-item-instructions\">");
          client.println("                    <p id=\"instructions-header\">Morse Code</p>");
          client.println("                    <p id=\"instructions-body\">Choose a word and see the <em>blue LED</em> light up according to its morse code equivalent!</p>");
          client.println("                    <p id=\"guide-p\">");
          client.println("                        Before the pattern starts, the LED will be <em> lit up </em> for <em>five seconds</em>. After the pattern, the LED will be <em> off </em> for <em>five");
          client.println("                        seconds </em>. In a pattern, the LED will be lit up for <em>3 seconds</em> to signify <em> dashes ( - ) </em> while for <em>dots ( . )</em>, the LED will");
          client.println("                        be lit up for <em>a second</em>.");
          client.println("                    </p>");
          client.println("                </div>");
          client.println("                <div class=\"gap-top\"></div>");
          client.println("                <div class=\"grid-item-button\">");
          client.println("                    <a href=\"button1\"><button id=\"button1\" class=\"patternbutton\" onclick=\"changePattern(1)\" onmouseover=\"morseText(1)\"");
          client.println("                            onmouseout=\"regText(1)\">NSEMBED</button></a>");
          client.println("                </div>");
          client.println("                <div class=\"grid-item-button\">");
          client.println("                    <a href=\"button2\"><button id=\"button2\" class=\"patternbutton\" onclick=\"changePattern(2)\" onmouseover=\"morseText(2)\"");
          client.println("                            onmouseout=\"regText(2)\">Bernice</button></a>");
          client.println("                </div>");
          client.println("                <div class=\"grid-item-button\">");
          client.println("                    <a href=\"button3\"><button id=\"button3\" class=\"patternbutton\" onclick=\"changePattern(3)\" onmouseover=\"morseText(3)\"");
          client.println("                            onmouseout=\"regText(3)\">Betito</button></a>");
          client.println("                </div>");
          client.println("                <div class=\"gap-mid\"></div>");
          client.println("                <div class=\"grid-item-p\">");
          client.println("                    <p id=\"p1\" class=\"caption\">Subject / Course</p>");
          client.println("                </div>");
          client.println("                <div class=\"grid-item-p\">");
          client.println("                    <p id=\"p2\" class=\"caption\">First name of developer</p>");
          client.println("                </div>");
          client.println("                <div class=\"grid-item-p\">");
          client.println("                    <p id=\"p3\" class=\"caption\">Last name of developer</p>");
          client.println("                </div>");
          client.println("                <div class=\"gap-bottom\"></div>");
          client.println("                <div id=\"current\" class=\"grid-item-current\">");
          client.println("                    <p id=\"curr-header\">Current Pattern</p>");
          client.println("                    <p id=\"curr-pattern\">No Pattern Chosen</p>");
          client.println("                </div>");
          client.println("                <div class=\"gap-bottom\"></div>");
          client.println("                <div class=\"grid-item-filler\"></div>");
          client.println("                <div class=\"grid-item-reset\">");
          client.println("                    <a id=\"resetlink\" href=\"resetbutton\"><button id=\"resetbutton\" onclick=\"changePattern(4)\" disabled>Reset</button></a>");
          client.println("                </div>");
          client.println("                <div class=\"grid-item-filler\"></div>");
          client.println("            </div>");
          client.println("        </div>");
          
          client.println("        <footer>");
          client.println("            <p class=\"footer-p\">Bernice Marie M. Betito</p>");
          client.println("            <p class=\"footer-p\">NSEMBED - S11 AY 2020 - 2021</p>");
          client.println("        </footer>");
          client.println("    </body>");
          client.println("    <script type=\"text/javascript\">");
          client.println("        /*----- Change the current pattern -----*/");
          client.println("        function changePattern(num) {");
          client.println("            if (num <= 3) {");
          client.println("                document.body.style.transition = \"0.5s\";");
          client.println("                document.body.style.backgroundColor = \"#363636\";");
          
          client.println("                document.getElementById(\"instructions-div\").style.transition = \"0.5s\";");
          client.println("                document.getElementById(\"instructions-div\").style.backgroundColor = \"#252525\";");
          client.println("                document.getElementById(\"instructions-div\").style.color = \"#FFFFFF\";");
          client.println("                document.getElementById(\"instructions-div\").style.border = \"2px solid #252525\";");
          
          client.println("                document.getElementById(\"current\").style.transition = \"0.5s\";");
          client.println("                document.getElementById(\"current\").classList.add(\"chosen-p\");");
          
          client.println("                document.getElementById(\"curr-header\").style.color = \"#191919\";");
          client.println("                document.getElementById(\"curr-pattern\").style.color = \"#4B4BE2\";");
          
          client.println("                document.getElementById(\"resetbutton\").disabled = false;");
          client.println("                document.getElementById(\"resetlink\").href = \"#\";");
          client.println("            } else {");
          client.println("                document.body.style.transition = \"0.5s\";");
          client.println("                document.body.style.backgroundColor = \"#FFFFFF\";");
          
          client.println("                document.getElementById(\"instructions-div\").style.transition = \"0.5s\";");
          client.println("                document.getElementById(\"instructions-div\").style.backgroundColor = \"#FFFFFF\";");
          client.println("                document.getElementById(\"instructions-div\").style.color = \"#191919\";");
          client.println("                document.getElementById(\"instructions-div\").style.border = \"2px solid #191919\";");
          
          client.println("                if (document.getElementById(\"button1\").classList.contains(\"chosen-button\")) {");
          client.println("                    document.getElementById(\"button1\").classList.remove(\"chosen-button\");");
          client.println("                }");
          client.println("                if (document.getElementById(\"p1\").classList.contains(\"chosen-p\")) {");
          client.println("                    document.getElementById(\"p1\").classList.remove(\"chosen-p\");");
          client.println("                }");
          
          client.println("                if (document.getElementById(\"button2\").classList.contains(\"chosen-button\")) {");
          client.println("                    document.getElementById(\"button2\").classList.remove(\"chosen-button\");");
          client.println("                }");
          client.println("                if (document.getElementById(\"p2\").classList.contains(\"chosen-p\")) {");
          client.println("                    document.getElementById(\"p2\").classList.remove(\"chosen-p\");");
          client.println("                }");
          
          client.println("                if (document.getElementById(\"button3\").classList.contains(\"chosen-button\")) {");
          client.println("                    document.getElementById(\"button3\").classList.remove(\"chosen-button\");");
          client.println("                }");
          client.println("                if (document.getElementById(\"p3\").classList.contains(\"chosen-p\")) {");
          client.println("                    document.getElementById(\"p3\").classList.remove(\"chosen-p\");");
          client.println("                }");
          
          client.println("                document.getElementById(\"current\").style.transition = \"0.5s\";");
          client.println("                document.getElementById(\"current\").classList.remove(\"chosen-p\");");
          
          client.println("                document.getElementById(\"curr-header\").style.color = \"#E6E6E6\";");
          client.println("                document.getElementById(\"curr-pattern\").style.color = \"#E6E6E6\";");
          client.println("                document.getElementById(\"curr-pattern\").innerText = \"No Pattern Chosen\";");
          
          client.println("                document.getElementById(\"resetbutton\").disabled = true;");
          client.println("                document.getElementById(\"resetlink\").href = \"#\";");
          client.println("            }");
          
          client.println("            if (num == 1) {");
          client.println("                document.getElementById(\"button2\").style.transition = \"0.5s\";");
          client.println("                document.getElementById(\"p2\").style.transition = \"0.5s\";");
          
          client.println("                document.getElementById(\"button3\").style.transition = \"0.5s\";");
          client.println("                document.getElementById(\"p3\").style.transition = \"0.5s\";");
          
          client.println("                if (document.getElementById(\"button2\").classList.contains(\"chosen-button\")) {");
          client.println("                    document.getElementById(\"button2\").classList.remove(\"chosen-button\");");
          client.println("                }");
          client.println("                if (document.getElementById(\"p2\").classList.contains(\"chosen-p\")) {");
          client.println("                    document.getElementById(\"p2\").classList.remove(\"chosen-p\");");
          client.println("                }");
          
          client.println("                if (document.getElementById(\"button3\").classList.contains(\"chosen-button\")) {");
          client.println("                    document.getElementById(\"button3\").classList.remove(\"chosen-button\");");
          client.println("                }");
          client.println("                if (document.getElementById(\"p3\").classList.contains(\"chosen-p\")) {");
          client.println("                    document.getElementById(\"p3\").classList.remove(\"chosen-p\");");
          client.println("                }");
          
          client.println("                document.getElementById(\"button1\").style.transition = \"0.5s\";");
          client.println("                document.getElementById(\"button1\").classList.add(\"chosen-button\");");
          
          client.println("                document.getElementById(\"p1\").style.transition = \"0.5s\";");
          client.println("                document.getElementById(\"p1\").classList.add(\"chosen-p\");");
          
          client.println("                document.getElementById(\"curr-pattern\").innerHTML = \"- .&emsp;. . .&emsp;.&emsp;- -&emsp;- . . .&emsp;.&emsp;- . .\";");
          client.println("            } else if (num == 2) {");
          client.println("                document.getElementById(\"button1\").style.transition = \"0.5s\";");
          client.println("                document.getElementById(\"p1\").style.transition = \"0.5s\";");
          
          client.println("                document.getElementById(\"button3\").style.transition = \"0.5s\";");
          client.println("                document.getElementById(\"p3\").style.transition = \"0.5s\";");
          
          client.println("                if (document.getElementById(\"button1\").classList.contains(\"chosen-button\")) {");
          client.println("                    document.getElementById(\"button1\").classList.remove(\"chosen-button\");");
          client.println("                }");
          client.println("                if (document.getElementById(\"p1\").classList.contains(\"chosen-p\")) {");
          client.println("                    document.getElementById(\"p1\").classList.remove(\"chosen-p\");");
          client.println("                }");
          
          client.println("                if (document.getElementById(\"button3\").classList.contains(\"chosen-button\")) {");
          client.println("                    document.getElementById(\"button3\").classList.remove(\"chosen-button\");");
          client.println("                }");
          client.println("                if (document.getElementById(\"p3\").classList.contains(\"chosen-p\")) {");
          client.println("                    document.getElementById(\"p3\").classList.remove(\"chosen-p\");");
          client.println("                }");
          
          client.println("                document.getElementById(\"button2\").style.transition = \"0.5s\";");
          client.println("                document.getElementById(\"button2\").classList.add(\"chosen-button\");");
          
          client.println("                document.getElementById(\"p2\").style.transition = \"0.5s\";");
          client.println("                document.getElementById(\"p2\").classList.add(\"chosen-p\");");
          
          client.println("                document.getElementById(\"curr-pattern\").innerHTML = \"- . . .&emsp;.&emsp;. - .&emsp;- .&emsp;. .&emsp;- . - .&emsp;.\";");
          client.println("            } else if (num == 3) {");
          client.println("                document.getElementById(\"button1\").style.transition = \"0.5s\";");
          client.println("                document.getElementById(\"p1\").style.transition = \"0.5s\";");
          
          client.println("                document.getElementById(\"button2\").style.transition = \"0.5s\";");
          client.println("                document.getElementById(\"p2\").style.transition = \"0.5s\";");
          
          client.println("                if (document.getElementById(\"button1\").classList.contains(\"chosen-button\")) {");
          client.println("                    document.getElementById(\"button1\").classList.remove(\"chosen-button\");");
          client.println("                }");
          client.println("                if (document.getElementById(\"p1\").classList.contains(\"chosen-p\")) {");
          client.println("                    document.getElementById(\"p1\").classList.remove(\"chosen-p\");");
          client.println("                }");
          
          client.println("                if (document.getElementById(\"button2\").classList.contains(\"chosen-button\")) {");
          client.println("                    document.getElementById(\"button2\").classList.remove(\"chosen-button\");");
          client.println("                }");
          client.println("                if (document.getElementById(\"p2\").classList.contains(\"chosen-p\")) {");
          client.println("                    document.getElementById(\"p2\").classList.remove(\"chosen-p\");");
          client.println("                }");
          
          client.println("                document.getElementById(\"button3\").style.transition = \"0.5s\";");
          client.println("                document.getElementById(\"button3\").classList.add(\"chosen-button\");");
          
          client.println("                document.getElementById(\"p3\").style.transition = \"0.5s\";");
          client.println("                document.getElementById(\"p3\").classList.add(\"chosen-p\");");
          
          client.println("                document.getElementById(\"curr-pattern\").innerHTML = \"- . . .&emsp;.&emsp;-&emsp;. .&emsp;-&emsp;- - -\";");
          client.println("            }");
          client.println("        }");
          
          client.println("        /*----- Display the morse code equivalent -----*/");
          client.println("        function morseText(num) {");
          client.println("            if (num == 1)");
          client.println("                document.getElementById(\"button1\").innerHTML = \"- .&ensp;. . .&ensp;.&ensp;- -&ensp;- . . .&ensp;.&ensp;- . .\";");
          client.println("            else if (num == 2)");
          client.println("                document.getElementById(\"button2\").innerHTML = \"- . . .&ensp;.&ensp;. - .&ensp;- .&ensp;. .&ensp;- . - .&ensp;.\";");
          client.println("            else if (num == 3)");
          client.println("                document.getElementById(\"button3\").innerHTML = \"- . . .&ensp;.&ensp;-&ensp;. .&ensp;-&ensp;- - -\";");
          client.println("        }");
          
          client.println("        /*----- Display the regular text -----*/");
          client.println("        function regText(num) {");
          client.println("            if (num == 1)");
          client.println("                document.getElementById(\"button1\").innerText = \"NSEMBED\";");
          client.println("            else if (num == 2)");
          client.println("                document.getElementById(\"button2\").innerText = \"Bernice\";");
          client.println("            else if (num == 3)");
          client.println("                document.getElementById(\"button3\").innerText = \"Betito\";");
          client.println("        }");
          client.println("    </script>");
          client.println("    <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js\"></script>");
          client.println("    <script>");
          client.println("        const get_pattern1 = document.getElementById(\"button1\")");
          client.println("        get_pattern1.addEventListener('click', function (event) {");
          client.println("            event.preventDefault()");
          client.println("            $.ajax({");
          client.println("                method: 'get',");
          client.println("                url: `/button1`,");
          client.println("                processData: false,");
          client.println("                contentType: false,");
          client.println("                error: e => {");
          client.println("                    console.log(e)");
          client.println("                    alert('error')");
          client.println("                }");
          client.println("            })");
          client.println("        })");
          
          client.println("        const get_pattern2 = document.getElementById(\"button2\")");
          client.println("        get_pattern2.addEventListener('click', function (event) {");
          client.println("            event.preventDefault()");
          client.println("            $.ajax({");
          client.println("                method: 'get',");
          client.println("                url: `/button2`,");
          client.println("                processData: false,");
          client.println("                contentType: false,");
          client.println("                error: e => {");
          client.println("                    console.log(e)");
          client.println("                    alert('error')");
          client.println("                }");
          client.println("            })");
          client.println("        })");
          
          client.println("        const get_pattern3 = document.getElementById(\"button3\")");
          client.println("        get_pattern3.addEventListener('click', function (event) {");
          client.println("            event.preventDefault()");
          client.println("            $.ajax({");
          client.println("                method: 'get',");
          client.println("                url: `/button3`,");
          client.println("                processData: false,");
          client.println("                contentType: false,");
          client.println("                error: e => {");
          client.println("                    console.log(e)");
          client.println("                    alert('error')");
          client.println("                }");
          client.println("            })");
          client.println("        })");
          
          client.println("        const reset = document.getElementById(\"resetbutton\")");
          client.println("        reset.addEventListener('click', function (event) {");
          client.println("            event.preventDefault()");
          client.println("            $.ajax({");
          client.println("                method: 'get',");
          client.println("                url: `/resetbutton`,");
          client.println("                processData: false,");
          client.println("                contentType: false,");
          client.println("                error: e => {");
          client.println("                    console.log(e)");
          client.println("                    alert('error')");
          client.println("                }");
          client.println("            })");
          client.println("        })");
          client.println("    </script>");
          client.println("</html>");
          break;
        }

        // Assign characters read
        current_string += current_char;
        previous_two = previous_one;
        previous_one = current_char;

        // Check if request is from buttons clicked
        if(current_string.indexOf("button1") > -1) {              // Pattern #1 (NSEMBED)
          xSemaphoreTake(bin_sem, portMAX_DELAY);
          int_blink_pattern = 1;
          current_string = "";
          xSemaphoreGive(bin_sem);
        } else if(current_string.indexOf("button2") > -1) {       // Pattern #2 (Bernice)
          xSemaphoreTake(bin_sem, portMAX_DELAY);
          int_blink_pattern = 2;
          current_string = "";
          xSemaphoreGive(bin_sem);
        } else if(current_string.indexOf("button3") > -1) {       // Pattern #3 (Betito)
          xSemaphoreTake(bin_sem, portMAX_DELAY);
          int_blink_pattern = 3;
          current_string = "";
          xSemaphoreGive(bin_sem);
        } else if(current_string.indexOf("resetbutton") > -1) {   // Reset Button
          xSemaphoreTake(bin_sem, portMAX_DELAY);
          int_blink_pattern = 4;
          current_string = "";
          xSemaphoreGive(bin_sem);
        }
      }
    }
    client.stop();
  }
}
