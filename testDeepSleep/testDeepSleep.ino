#define ESP8266_LED 5
const int sleepTimeS = 10;

void setup() {

  Serial.begin(57600);
  Serial.println("ESP8266 in normal mode");
  pinMode(ESP8266_LED, OUTPUT);
  
  // put your setup code here, to run once:
  digitalWrite(ESP8266_LED, HIGH);
  delay(500);
  digitalWrite(ESP8266_LED, LOW);
  delay(500);
  Serial.println("ESP8266 in sleep mode");
  ESP.deepSleep(sleepTimeS * 1000000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
