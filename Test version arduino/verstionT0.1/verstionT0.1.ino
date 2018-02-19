#include <NewPing.h>

int TriggerPinnen[] = {12, 13, 14};
int Echo_Pinnen[] = {9, 10, 11};
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonarL(TriggerPinnen[0], Echo_Pinnen[0], MAX_DISTANCE);
NewPing sonarM(TriggerPinnen[1], Echo_Pinnen[1], MAX_DISTANCE);
NewPing sonarR(TriggerPinnen[2], Echo_Pinnen[2], MAX_DISTANCE);

int AfstandSL = 0;
int AfstandSM = 0;
int AfstandSR = 0;

void setup() {
  // TIMER 0 for interrupt frequency 200.32051282051282 Hz:
  cli(); // stop interrupts
  TCCR0A = 0; // set entire TCCR0A register to 0
  TCCR0B = 0; // same for TCCR0B
  TCNT0  = 0; // initialize counter value to 0
  // set compare match register for 200.32051282051282 Hz increments
  OCR0A = 77; // = 16000000 / (1024 * 200.32051282051282) - 1 (must be <256)
  // turn on CTC mode
  TCCR0B |= (1 << WGM01);
  // Set CS02, CS01 and CS00 bits for 1024 prescaler
  TCCR0B |= (1 << CS02) | (0 << CS01) | (1 << CS00);
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  sei(); // allow interrupts

  Serial.begin(9600);
}

ISR(TIMER0_COMPA_vect) {
   AfstandSL = sonarL.ping_cm();;
   AfstandSM = sonarM.ping_cm();;
   AfstandSR = sonarR.ping_cm();;
}

void loop() {
  int tijd = millis();
  if (millis() - tijd > 50) {

  }
  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  //int afstand = sonar.ping_cm();
  
    Serial.print("PingL: ");
    Serial.print(AfstandSL);
    Serial.println("cm    ");
    Serial.print("PingM: ");
    Serial.print(AfstandSM);
    Serial.println("cm    ");
    Serial.print("PingR: ");
    Serial.print(AfstandSR);
    Serial.println("cm");

  //Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)

}
