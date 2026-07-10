#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <LittleFS.h>
#include <IRremote.hpp>

#define IR_SEND_PIN D1

const char* AP_SSID = "IRRemote";
const char* AP_PASS = "12345678"; // en az 8 karakter

DNSServer dnsServer;
ESP8266WebServer server(80);

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);

void handleIR() {
  String dev = server.arg("dev");
  String cmd = server.arg("cmd");
  String val = server.arg("val");

  if (dev == "tv") {
    if (cmd == "vol_up")   IrSender.sendNEC(0xFD01, 0xD0, 0);
    else if (cmd == "vol_down") IrSender.sendNEC(0xFD01, 0xCC, 0);
    else if (cmd == "power") IrSender.sendNEC(0xFD01, /* power kodun */ 0x00, 0);
    // diğer TV komutlarını buraya ekle
  }
  else if (dev == "ac") {
    if (cmd == "power") IrSender.sendLG(0x88, /* power kodun */ 0x0000, 0);
    else if (cmd == "temp") {
      // val parametresine göre önceden eşleştirdiğin sıcaklık kodlarını gönder
      int temp = val.toInt();
      // örnek: if (temp == 24) IrSender.sendLG(0x88, 0x92F1, 0);
    }
    else if (cmd == "mode") {
      // val: "cool" / "fan" / "auto"
    }
    else if (cmd == "fan") {
      // val: "low" / "med" / "high"
    }
  }

  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  IrSender.begin(IR_SEND_PIN);

  LittleFS.begin();

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(AP_SSID, AP_PASS);

  // Captive portal: hangi adrese gidilirse gidilsin ESP'nin IP'sine yönlendir
  dnsServer.start(DNS_PORT, "*", apIP);

  // Ana sayfa
  server.serveStatic("/", LittleFS, "/remote.html");

  // IR komut endpoint'i
  server.on("/ir", HTTP_GET, handleIR);

  // Telefon otomatik "internet var mı" kontrolü yapar, bunları da yönlendir
  server.onNotFound([]() {
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "");
  });

  server.begin();
  Serial.println("AP baslatildi, SSID: " + String(AP_SSID));
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
}