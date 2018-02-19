#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int AfstandSL = 0;
int AfstandSM = 0;
int AfstandSR = 0;

int TESTLED = 2;

void setup() {
  pinMode(TESTLED, OUTPUT);
  
  cli();
  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0 = 0;
  OCR0A = 15624; //=(16*10^) / (2000 * 64) - 1 (moet kleiner zijn dan 256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM12);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS12) | (1 << CS10);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE1A);
  sei();
  
  Serial.begin(9600);
}

ISR(TIMER0_COMPA_vect){
  digitalWrite(TESTLED, !digitalRead(TESTLED));
}

void loop() {
   int tijd = millis();
  if (millis() - tijd > 50){
     
  }
                   // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int afstand = sonar.ping_cm();
  if (afstand != 0){
    Serial.print("Ping: ");
    Serial.print(afstand);
    Serial.println("cm");
  }
  //Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  
}
