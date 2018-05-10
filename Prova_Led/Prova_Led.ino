#define TRIG_PIN  7   //Impulso invio burst
#define ECHO_PIN  8   //misura durata distanza
#define LED_PIN   9
#define PERIOD    500 //millisecondi
#define MIN_DIST  20  //centimetri

//variabili globali 
unsigned char Led_State;
unsigned long Start;
double Distance;

void Blink()
{
  if(millis() - Start >= PERIOD)
  {
    Led_State = !Led_State;
    Start = millis();
  }
  digitalWrite(LED_PIN, Led_State);
}

//Inizializzazioni
void setup (void)
{
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Led_State = 0;
  digitalWrite(LED_PIN, Led_State);
  Start = millis();
}

void loop (void)
{
  //eseguo la misura della distanza
  digitalWrite(TRIG_PIN, 1);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, 0);
  delayMicroseconds(5);
  Distance = pulseIn(ECHO_PIN, 1);
  Distance = (Distance * 0.0343) / 2;

  //Controllo la prossimità
  if(Distance <= MIN_DIST)
  {
    Blink();
  }
  else
  {
    digitalWrite(LED_PIN, 0);
  }
  
  Serial.println(Start);
}
