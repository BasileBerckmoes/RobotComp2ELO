#include <NewPing.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);
  Serial.println("Test");
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 10; i++){
    Serial.println(i);
  }
  //Serial.println("LOOP");
}
