// Realizzazione di una rete di trasmissione, basata su schede Arduino Uno
// per il controllo tramite invio di messaggi Versione 2.0

String messaggio = "";     // inizializzo la variabile che conterrà la stringa proveniente dal seriale
int myId;   // variabile globale che rappresenta il proprio indirizzo
int numeroLed;
int vel;
int statoLed;
  
void setup() {
  // initialize serial:
  Serial.begin(9600);   //inizializzo la porta seriale per la comunicazione

  // dichiarazione variabili
  int pin;
  int b0, b1, b2, b3;

  // settaggio dei pin da 8 a 11 in modalità OUTPUT
  for(int pin = 8; pin <= 11; pin++)
  {
    pinMode(pin, OUTPUT);
  }

  //lettura del proprio ID
  b0 = digitalRead(2);  // legge il valore del led collegato al pin (0/1) e lo assegna ad una variabile 
  b1 = digitalRead(3);
  b2 = digitalRead(4);
  b3 = digitalRead(5);
  myId = b0 + 2*b1 + 4*b2 + 8*b3; //calcola il myId attraverso conversione BINARIO/DECIMALE
}

void loop() {

    if (Serial.available() > 0){  //se la lettura da monitor seriale è avvenuta
      int destinatario = Serial.parseInt(); //legge il destinatario
      int tipo = Serial.parseInt();   //legge il tipo
   
    if(destinatario == myId) // se il destinatario è il proprio ID
    {
      if( tipo == 1){ //caso 1 (controllo led)
        numeroLed = Serial.parseInt();  //legge led da controllare
        statoLed = Serial.parseInt();   //legge lo stato del led
        if(numeroLed == 9)  //se il numeroLed è 9, controlla tutti i led
        {
          digitalWrite(8,statoLed); 
          digitalWrite(9,statoLed);
          digitalWrite(10,statoLed);
          digitalWrite(11,statoLed);
        }
        else 
          digitalWrite(numeroLed+7, statoLed);  // altrimenti controlla i singoli led(numeroLed da 1 a 4 )
      }
      else{
        if(tipo == 2){  //caso 2 (invio messaggio)
          messaggio = Serial.readString();  //legge il messaggio
          messaggio = messaggio.substring(0, messaggio.length()); //toglie l'ultimo carattere(INVIO) dalla stringa
          Serial.println(messaggio);  //ristampa il messaggio nel monitor seriale
        }
        else{ //se caso 3 (specifici/privati)
          vel = Serial.parseInt();
          for(int pin=8; pin<= 11; pin++){ //per ogni led
            digitalWrite(pin,HIGH); //accende il led
            delay(vel);   //aspetta 100mS
            digitalWrite(pin,LOW);  //spegne il led
            delay(vel);   //aspetta altri 100mS
          }
          for(int pin=11; pin>= 8; pin--){  //ciclo inverso al precedente
            digitalWrite(pin,HIGH);
            delay(vel); 
            digitalWrite(pin,LOW);
            delay(vel); 
          }
        }
      }
    }
    else  // altrimenti se l'ID destinatario è un'altro
    { 
      if(tipo == 1){
        numeroLed = Serial.parseInt();  //legge led da controllare
        statoLed = Serial.parseInt();   //legge lo stato del led
        String msg = String(destinatario) + "," + String (tipo) + "," + String(numeroLed)+ "," + String (statoLed); 
        Serial.println(msg);  // invia i dati letti dal monitor seriale alla scheda successiva
      }else{
        if (tipo == 2){
          messaggio = Serial.readString();  //legge il messaggio
          messaggio = messaggio.substring(0, messaggio.length()); //toglie l'ultimo carattere(INVIO) dalla stringa
          String msg = String(destinatario) + "," + String (tipo)+"," + String(messaggio);
          Serial.println(messaggio);  // invia i dati letti dal monitor seriale alla scheda successiva
        }
        else{
        vel = Serial.parseInt();
        String msg = String(destinatario) + "," + String (tipo)+"," + String(vel);
        Serial.println(messaggio);  // invia i dati letti dal monitor seriale alla scheda successiva
        }
      }
    }
   }
}   
    /*if(destinatario == 15)
    {
      if( tipo == 1){ //caso 1 (controllo led)
        numeroLed = Serial.parseInt();  //legge led da controllare
        statoLed = Serial.parseInt();   //legge lo stato del led
        if(numeroLed == 9)  //se il numeroLed è 9, controlla tutti i led
        {
          digitalWrite(8,statoLed); 
          digitalWrite(9,statoLed);
          digitalWrite(10,statoLed);
          digitalWrite(11,statoLed);
        }
        else 
          digitalWrite(numeroLed+7, statoLed);  // altrimenti controlla i singoli led(numeroLed da 1 a 4 )
      }
      else{
        if(tipo == 2){  //caso 2 (invio messaggio)
          messaggio = Serial.readString();  //legge il messaggio
          messaggio = messaggio.substring(0, messaggio.length()); //toglie l'ultimo carattere(INVIO) dalla stringa
          Serial.println(messaggio);  //ristampa il messaggio nel monitor seriale
        }
      }
      if(tipo == 1){
        numeroLed = Serial.parseInt();  //legge led da controllare
        statoLed = Serial.parseInt();   //legge lo stato del led
        String msg = String(destinatario) + "," + String (tipo) + "," + String(numeroLed)+ "," + String (statoLed); 
        Serial.println(msg);  // invia i dati letti dal monitor seriale alla scheda successiva
      }else{
        if (tipo == 2){
          messaggio = Serial.readString();  //legge il messaggio
          messaggio = messaggio.substring(0, messaggio.length()); //toglie l'ultimo carattere(INVIO) dalla stringa
          String msg = String(destinatario) + "," + String (tipo)+"," + String(messaggio);
          Serial.println(msg);  // invia i dati letti dal monitor seriale alla scheda successiva
        }
      }
    }*/


