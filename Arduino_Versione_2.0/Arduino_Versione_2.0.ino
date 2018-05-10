int myId;

void setup() {
  Serial.begin (9600);

  int pin;
  int b0, b1, b2, b3;
  
  for(int pin = 8; pin <= 11; pin ++)
    pinMode(pin, OUTPUT);

  b0 = digitalRead(2);
  b1 = digitalRead(3);
  b2 = digitalRead(4);
  b3 = digitalRead(5);
  myId = b0 + 2*b1 + 4*b2 + 8*b3;
}

void loop() {
   if (Serial.available() > 0){
    int destinatario = Serial.parseInt();  
    int tipo = Serial.parseInt();
    if (destinatario == myId)
    {
      if(tipo == 1){
          int numeroLed = Serial.parseInt();
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
      else{
        if (tipo == 2){
          String messaggio = Serial.readString();
          Serial.println(messaggio);
        }
        else{
          for(int pin=8; pin<=11; pin++)
          {
            digitalWrite(pin, HIGH);
            delay(500);
            digitalWrite(pin, LOW);
            delay(500);
          }
          for(int pin=11; pin>=8; pin--)
          {
            digitalWrite(pin, HIGH);
            delay(500);
            digitalWrite(pin, LOW);
            delay(500);
          }
        }
      }
     }  
    }
    else
    {
      if(int tipo == 1)
        String msg = String(destinatario)+ "," + String (tipo) + "," + String(numeroLed)+"," + String (statoLed);
      else
        if(tipo == 2)
          String msg = String(destinatario)+ "," + String (tipo) + "," + String (messaggio);
          
      Serial.println(msg);
    }
    
   }
}
