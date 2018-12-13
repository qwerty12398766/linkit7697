#include <LWiFi.h>
#include "MCS.h"

char _lwifi_ssid[] = "Denny-chen";
char _lwifi_pass[] = "ytrewq123";

MCSDevice mcs("DfxFS3q1", "1If0mVlhAz0ATgEl");
MCSControllerOnOff MySwitch("myswitch");

void setup()
{
  Serial.begin(9600);

  mcs.addChannel(MySwitch);
  Serial.println("Wi-Fi 開始連線");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) { delay(1000); }
  Serial.println("Wi-Fi 連線成功");
  while(!mcs.connected()) { mcs.connect(); }
  Serial.println("MCS 連線成功");
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  while (!mcs.connected()) {
    mcs.connect();
    if (mcs.connected()) { Serial.println("MCS 已重新連線"); }
  }
  mcs.process(100);

  if (MySwitch.updated()) {
    Serial.print("控制通道更新 :");
    Serial.println(MySwitch.value());

    if (MySwitch.value()) {
      digitalWrite(LED_BUILTIN, HIGH);

    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  delay(1000);
}
