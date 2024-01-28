#include <PCD8544.h>
#include <math.h>

/* MACROS */
#define AC_PIN 7

// Se definen los PINES a leer
float V1 = 0;
float V2 = 0;
float V3 = 0;
float V4 = 0;

// Variable para saber si AC_PIN esta alto/bajo
int ac_pin = 0;

// Se define rango permitido por pines Arduino
float rangoInicialMin = 0.0, rangoInicialMax = 5.0;

// Se define rango real de voltajes
float rangoFinalMin = -24.0, rangoFinalMax = 24.0; 

static PCD8544 lcd;

                                                                                  /*  FUNCIONES  */
// Funcion para escalar el voltaje de entrada
float escalar(float valor){
  // Regla de 3
  float voltajeReal = ( (valor - rangoInicialMin)/( rangoInicialMax - rangoInicialMin) )* (rangoFinalMax - rangoFinalMin) + rangoFinalMin;
  return voltajeReal;

}


void setup() {
  // Voltaje de referencia, para que display lea entre 0 y 5V
  analogReference(DEFAULT);

  // PCD8544-compatible displays may have a different resolution...
  lcd.begin(84, 48);

  // Se establece AC_PIN como entrada 
  pinMode(AC_PIN, INPUT);
}


void loop(){
  // Se leen los pines de entrada
  V1 = analogRead(A5);
  V2 = analogRead(A4);
  V3 = analogRead(A3);
  V4 = analogRead(A2);

  // Se lee AC_PIN para saber si esta alto/bajo
  ac_pin = digitalRead(AC_PIN);

  // Se escalan valores de 0 a 1023 para que display 
  // imprima valores de 0.0V a 5.0V
  V1 = (V1*5)/1023.0;
  V2 = (V2*5)/1023.0;
  V3 = (V3*5)/1023.0;
  V4 = (V4*5)/1023.0;

  // Escalar el voltaje al valor real
    V1 = escalar(V1);
    V2 = escalar(V2);
    V3 = escalar(V3);
    V4 = escalar(V4);

  if(!ac_pin){

    // Se escribe en 1era linea del display
    lcd.setCursor(0, 0);
    lcd.print("V1: ");
    lcd.print(V1);
    lcd.print(" V ");
  
    // Se escribe en 2da linea del display
    lcd.setCursor(0, 1);
    lcd.print("V2: ");
    lcd.print(V2);
    lcd.print(" V ");

    // Se escribe en 3ra linea del display
    lcd.setCursor(0, 2);
    lcd.print("V3: ");
    lcd.print(V3);
    lcd.print(" V ");

    // Se escribe en 4ta linea del display
    lcd.setCursor(0, 3);
    lcd.print("V4: ");
    lcd.print(V4);
    lcd.print(" V ");

  }else if(ac_pin){
    // Se obtiene Vrms
    V1 = V1/sqrt(2);
    V2 = V2/sqrt(2);
    V3 = V3/sqrt(2);
    V4 = V4/sqrt(2);

    // Se escribe en 1era linea del display
    lcd.setCursor(0, 0);
    lcd.print("V1: ");
    lcd.print(V1);
    lcd.print("Vrms");
  
    // Se escribe en 2da linea del display
    lcd.setCursor(0, 1);
    lcd.print("V2: ");
    lcd.print(V2);
    lcd.print("Vrms");

    // Se escribe en 3ra linea del display
    lcd.setCursor(0, 2);
    lcd.print("V3: ");
    lcd.print(V3);
    lcd.print("Vrms");

    // Se escribe en 4ta linea del display
    lcd.setCursor(0, 3);
    lcd.print("V4: ");
    lcd.print(V4);
    lcd.print("Vrms");

  }

}
