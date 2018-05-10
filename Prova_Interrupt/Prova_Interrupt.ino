// Test del piedino 2 come ingresso per segnale di Interrupt
const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;

void Isr() {  //routine di risposta al segnale di interrupt
  state = !state;
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), Isr, CHANGE);
}

void loop() {
  digitalWrite(ledPin, state);
}

