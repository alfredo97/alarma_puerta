//Declaración de variables
int ledBlue = 10;
int ledRed = 11;
int bocina = 8;
int led = 6;
int puerta = 18;
boolean onOff = false;


void setup() {
  //Declración de pines
  pinMode(bocina, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(puerta, INPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledRed, OUTPUT);
  
  //Declarar interrupciones
  attachInterrupt(digitalPinToInterrupt(puerta), alarmaOn, HIGH);
  attachInterrupt(digitalPinToInterrupt(puerta), alarmaOff, LOW);
  
  Serial.begin(9600);
}

void loop() {
  if(onOff){
    flash();
  }

}


void alarmaOn(){
  onOff = true;
  digitalWrite(led, HIGH);
  Serial.println("Alarma Activada");  
  attachInterrupt(digitalPinToInterrupt(puerta), alarmaOff, LOW);
}

void alarmaOff(){
  onOff = false;
  digitalWrite(led, LOW);
  digitalWrite(led, LOW);
  attachInterrupt(digitalPinToInterrupt(puerta), alarmaOn, HIGH);
  
}

void flash(){
  digitalWrite(ledRed, LOW);
  digitalWrite(ledBlue, HIGH);
  tone(bocina, 700);
  delay(300);
  digitalWrite(ledBlue, LOW);
  digitalWrite(ledRed, HIGH);
  tone(bocina, 500);
  delay(300);
  digitalWrite(ledRed, LOW);
  noTone(bocina);
}
