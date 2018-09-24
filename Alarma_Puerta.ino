//Declaración de variables
int ledBlue = 10;
int ledRed = 11;
int bocina = 8;
int led = 6;
int puerta = 18;
boolean onOff = false;


void setup() {
  pinMode(bocina, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(puerta, INPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledRed, OUTPUT);
  
  
  Serial.begin(9600);
}

void loop() {
  if(onOff){
    flash();
  }

}
