#include <PCD8544.h>
#include <math.h>

/* MACROS */
#define AC_PIN 7
#define LED_PIN 13
#define SERIAL_PIN 8

// Se definen los PINES a leer
float V1 = 0;
float V2 = 0;
float V3 = 0;
float V4 = 0;

// Resistencias divisoras de voltage
// Parte DC:
const float RESISTOR1 = 10000.0;
const float RESISTOR2 = 86000.0;
// Parte AC:
const float RESISTOR3 = 10000.0;
const float RESISTOR4 = 12800.0;

// Lista para iterar entre voltajes
float listaVoltajes[4] = {0.0,0.0,0.0,0.0}; 

// Variable para saber si AC_PIN esta alto/bajo
int ac_pin = 0;

// ledPin warning inicia en estado bajo
int ledPin = 0;

// Se define rango permitido por pines Arduino
float rangoInicialMin = 0.0, rangoInicialMax = 5.0;

// Se define rango real de voltajes
float rangoFinalMin = -24.0, rangoFinalMax = 24.0; 

static PCD8544 lcd;

                                                                                  /*  FUNCIONES  */
// Funcion para escalar el voltaje de entrada
float escalar(float valor){
    float voltajeReal;
    if(ac_pin){
      // Escalar el voltaje usando las resistencias del divisor para AC
      voltajeReal = (valor * (RESISTOR3 + RESISTOR4) / RESISTOR3)*2;
    }else{
      // Escalar el voltaje usando las resistencias del divisor para DC
      voltajeReal = valor * (RESISTOR1 + RESISTOR2) / RESISTOR1;
      voltajeReal = (voltajeReal - 24.0); // Ajustar el rango del voltaje
    }
    return voltajeReal;
}

void setup() {
  // Voltaje de referencia, para que display lea entre 0 y 5V
  analogReference(DEFAULT);

  // PCD8544-compatible displays may have a different resolution...
  lcd.begin(84, 48);

  // Se establece AC_PIN como entrada 
  pinMode(AC_PIN, INPUT);

  // Se establece LED_PIN como salida 
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Se establece SERIAL_PIN como entrada
  pinMode(SERIAL_PIN, INPUT);
  digitalWrite(SERIAL_PIN, LOW);


  Serial.begin(9600);
}


void loop(){

  // Se leen los pines de entrada
  V1 = analogRead(A5);
  V2 = analogRead(A4);
  V3 = analogRead(A3);
  V4 = analogRead(A2);

  // Se lee SERIAL_PIN para saber si esta alto/bajo
  int serial_pin = digitalRead(SERIAL_PIN);

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

  // Se agregan a la lista
  listaVoltajes[0] = V1; 
  listaVoltajes[1] = V2;
  listaVoltajes[2] = V3;
  listaVoltajes[3] = V4;

  for(int i; i<4; i++){
        // Encender el LED warning si voltaje mayor/menor a 20V
        if(abs(listaVoltajes[i]) > 20) {
          digitalWrite(LED_PIN, HIGH);
          break;
        } else if(abs(listaVoltajes[i]) < -20){
          digitalWrite(LED_PIN, HIGH);
          break;
        }else{
          digitalWrite(LED_PIN, LOW);
        }
  }

  if(!ac_pin){

    // Se escribe en 1era linea del display
    lcd.setCursor(0, 0);
    lcd.print("V1: ");
    lcd.print(V1);
    lcd.print(" V ");

    if(serial_pin){
      Serial.begin(9600);
      Serial.println("Voltages DC ");
      Serial.print("V1: ");
      Serial.print( V1 );
      Serial.print(" V ");
      Serial.println();
      Serial.end();
    }
  
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

    if(serial_pin){
      Serial.begin(9600);
      //V2
      Serial.print("V2: ");
      Serial.print( V2 );
      Serial.print(" V ");
      Serial.println();
      //V3
      Serial.print("V3: ");
      Serial.print( V3 );
      Serial.print(" V ");
      Serial.println();
      //V4
      Serial.print("V4: ");
      Serial.print( V4 );
      Serial.print(" V ");
      Serial.println();
      Serial.end();
    }

    delay(500);

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

    if(serial_pin){
      Serial.begin(9600);
      Serial.println("Voltages AC ");
      Serial.print("V1: ");
      Serial.print( V1 );
      Serial.print(" Vrms ");
      Serial.println();
      Serial.end();
    }
  
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

    if(serial_pin){
      Serial.begin(9600);
      //V2
      Serial.print("V2: ");
      Serial.print( V2 );
      Serial.print(" Vrms ");
      Serial.println();
      //V3
      Serial.print("V3: ");
      Serial.print( V3 );
      Serial.print(" Vrms ");
      Serial.println();
      //V4
      Serial.print("V4: ");
      Serial.print( V4 );
      Serial.print(" Vrms ");
      Serial.println();
      Serial.end();
    }

    delay(500);

  }

}