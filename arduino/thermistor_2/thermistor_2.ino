const int TEMP = 0;
int val = 0;


void setup() {
  // put your setup code here, to run once:

pinMode(TEMP, INPUT);  // set pin AO as an input pin






}

void loop() {
  // put your main code here, to run repeatedly:
val = analogRead(TEMP);

Serial.print(Analog Reading:" val);
Serial.println;
delay(500);

}
