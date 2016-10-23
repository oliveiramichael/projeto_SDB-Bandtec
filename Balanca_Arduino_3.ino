#include "HX711.h"

#define DOUT A1

#define CLK A0

HX711 balanca;

double tara;

void setup() {

Serial.begin(9600);

balanca.begin(DOUT, CLK, 64);

int cont = 0;
Serial.println("Zerando...");
while (cont < 10) {
  balanca.power_up();
  balanca.readRaw();
  delay(50);
  cont = cont + 1;
  Serial.print(cont);
  Serial.println(" / 10");
}

tara = 0;
cont = 0;
while (cont < 20) {
  balanca.power_up();
  tara = tara + balanca.readRaw();
  delay(50);
  cont = cont + 1;
  Serial.print(cont);
  Serial.println(" / 20");
}
tara = tara / 20.0;

Serial.println("Coloque sua bagagem!");
}

void loop() {

double media = 0;
int cont = 0;
while (cont < 4) {
  balanca.power_up();
  media = media + balanca.readRaw();
  cont = cont + 1;
}
media = media / 4.0;
media = media - tara;
if (media < 0) {
  media = 0;
} else {
  media = media / 21500;
}

Serial.print("Sua bagagem pesa: ");
Serial.print(media, 1);
Serial.println(" kg");

}

