#include "LedControl.h"
#include "binary.h"

//Declaración de variables
const int INDICADOR_BLUE = 4; //Led azul de la alarma
const int INDICADOR_RED = 5;  //Led rojo de la alarma
const int SPEAKER = 3;        //Buzzer
const int INDICADOR = 2;      //Led que indica el estado de la alarma
const int PUERTA = 18;        //Puerto del Reed Switch
boolean ON_OFF = false;       //Indica si está abierta o cerrada la puerta

/*
 DIN va al pin 12
 CLK va al pin 11
 CS va al pin 10 
*/
LedControl lc=LedControl(12,11,10,1);

//Variables que representan las formas de las imágenes mostradas en la matriz, cada elemento de la variable byte es una columna
byte image1[8] = {  
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
  B00000000,
  B00000000};
  
byte image2[8] = {  
  B00000000,
  B00000000,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B00000000,
  B00000000};
  
byte image3[8] = {  
  B00000000,
  B01000010,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B01000010,
  B00000000};

byte image4[8] = {  
  B10000001,
  B01000010,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B01000010,
  B10000001};

void setup() {
  //Declración de pines
  pinMode(SPEAKER, OUTPUT);
  pinMode(INDICADOR, OUTPUT);
  pinMode(PUERTA, INPUT);
  pinMode(INDICADOR_BLUE, OUTPUT);
  pinMode(INDICADOR_RED, OUTPUT);
  
  //Declarar interrupciones
  attachInterrupt(digitalPinToInterrupt(PUERTA), alarmaOn, HIGH);
  attachInterrupt(digitalPinToInterrupt(PUERTA), alarmaOff, LOW);
  
  Serial.begin(9600);

  lc.shutdown(0,false);
  // Set brightness to a medium value
  lc.setIntensity(0,9);
  // Clear the display
  lc.clearDisplay(0);  
}

void loop() {
  if(ON_OFF){
    flash();
  }

}


void alarmaOn(){
  ON_OFF = true;
  digitalWrite(INDICADOR, HIGH);
  Serial.println("Alarma Activada");  
  attachInterrupt(digitalPinToInterrupt(PUERTA), alarmaOff, LOW);
}

void alarmaOff(){
  ON_OFF = false;
  digitalWrite(INDICADOR, LOW);
  digitalWrite(INDICADOR, LOW);
  attachInterrupt(digitalPinToInterrupt(PUERTA), alarmaOn, HIGH);
  
}

//Proceso de alarma en accion
void flash(){
  lc.clearDisplay(0); //Limpia matriz
  delay(100);
  digitalWrite(INDICADOR_RED, LOW);
  digitalWrite(INDICADOR_BLUE, HIGH);
  tone(SPEAKER, 700);
  lc.setIntensity(0, 0);  
  drawImage1();
  delay(150);
  lc.setIntensity(0, 3);
  drawImage2();
  delay(150);
  digitalWrite(INDICADOR_BLUE, LOW);
  digitalWrite(INDICADOR_RED, HIGH);
  tone(SPEAKER, 500);
  
  lc.setIntensity(0, 6);
  drawImage3();
  delay(150);
  lc.setIntensity(0, 9);
  drawImage4();
  delay(150);
  digitalWrite(INDICADOR_RED, LOW);
  noTone(SPEAKER);
  lc.clearDisplay(0);
}

//Métodos para dibujar en la matriz
void drawImage1(){
  for(int i=0; i<8; i++){
    lc.setRow(0, i, image1[i]);
  }
}

void drawImage2(){
  for(int i=0; i<8; i++){
    lc.setRow(0, i, image2[i]);
  }
}

void drawImage3(){
  for(int i=0; i<8; i++){
    lc.setRow(0, i, image3[i]);
  }
}

void drawImage4(){
  for(int i=0; i<8; i++){
    lc.setRow(0, i, image4[i]);
  }
}
