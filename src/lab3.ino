#include <PCD8544.h>


// A custom glyph (a smiley)...
static const byte glyph[] = { B00010000, B00110100, B00110000, B00110100, B00010000 };

// Se definen los PINES a leer
float V1 = 0;
float V2 = 0;
float V3 = 0;
float V4 = 0;


static PCD8544 lcd;


void setup() {
  // Voltaje de referencia, para que display lea entre 0 y 5V
  analogReference(DEFAULT);
  // PCD8544-compatible displays may have a different resolution...
  lcd.begin(84, 48);

  // Add the smiley to position "0" of the ASCII table...
  lcd.createChar(0, glyph);
}


void loop() {
  // Se leen los pines de entrada
  V1 = analogRead(A5);
  V2 = analogRead(A4);
  V3 = analogRead(A3);
  V4 = analogRead(A2);

  // Se escalan valores de 0 a 1023 para que display 
  // imprima valores de 0.0V a 5.0V
  V1 = (V1*5)/1023.0;
  V2 = (V2*5)/1023.0;
  V3 = (V3*5)/1023.0;
  V4 = (V4*5)/1023.0;

  // Just to show the program is alive...
  static int counter = 0;

  // Write a piece of text on the first line...
  lcd.setCursor(0, 0);
  lcd.print("V1: ");
  lcd.print(V1);

  // Write a piece of text on the second line...
  lcd.setCursor(0, 1);
  lcd.print("V2: ");
  lcd.print(V2);

  // Write a piece of text on the third line...
  lcd.setCursor(0, 2);
  lcd.print("V3: ");
  lcd.print(V3);

  // Write a piece of text on the fourth line...
  lcd.setCursor(0, 3);
  lcd.print("V4: ");
  lcd.print(V4);

  // Write the counter on the second line...
  /*
  lcd.setCursor(0, 1);
  lcd.print(counter, DEC);
  lcd.write(' ');
  lcd.write(0);  // write the smiley */

  // Use a potentiometer to set the LCD contrast...
  // short level = map(analogRead(A0), 0, 1023, 0, 127);
  // lcd.setContrast(level);
  
  //delay(200);
  //counter++;
}
