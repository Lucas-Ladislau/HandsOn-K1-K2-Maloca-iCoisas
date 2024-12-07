const int PIN_BUZZER = 5;
const int PIN_PIR = 34;
const int PIN_BUTTON = 22;
const int PIN_TRIG  = 25;
const int PIN_ECHO  = 26;

void setup() {
  pinMode(PIN_BUZZER,OUTPUT);
  pinMode (PIN_PIR , INPUT );
  pinMode(PIN_BUTTON,INPUT_PULLUP);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  Serial.begin(115200); 

  Serial.println("Dispenser Higiênico");
}

void loop() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  long duracao = pulseIn(PIN_ECHO, HIGH); 
  float distancia = (duracao * 0.0343) / 2;
  if ( (digitalRead(PIN_PIR) == HIGH) && (digitalRead(PIN_BUTTON) == LOW) ) {
            if(distancia < 10 ){
              Serial.println("Movimento detectado a " + String(distancia) + " cm!!!");
              while (digitalRead(PIN_BUTTON) == LOW);
            }else{
              Serial.println("Movimento no PIR detectado");
            }
            delay(500);
        } 
  else{
    Serial.println("Sem movimento no PIR");
    delay(500);
  }

  
}