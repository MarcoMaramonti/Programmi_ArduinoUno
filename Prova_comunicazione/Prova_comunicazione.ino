void setup() {
  // initialize serial:
  Serial.begin(9600);   //attiva comunicazione tramite porta seriale USB
  int pin;
  for (int pin = 8; pin <= 11; pin++){
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  if (Serial.available() > 0){
    char destinatario = Serial.read();
    if(destinatario == 'A')
    {
      int numeroLed = Serial.parseInt();    //traduce i codici ASCII di caratteri numerici in valore intero
      int statoLed = Serial.parseInt();
      if(numeroLed == 9)
      {
        digitalWrite(8,statoLed); 
        digitalWrite(9,statoLed);
        digitalWrite(10,statoLed);
        digitalWrite(11,statoLed);
      }
      else
        digitalWrite(numeroLed+7, statoLed);
    }
    else
    {
      Serial.write(destinatario);
    }
  }
}



