// Projekt: Thermometer
   
int zahl_array[11][8] = {   // Zahlen der 7 Segment Anzeige; 1 = HIGH, 0 = LOW; Common Anode
  { 0,0,0,0,0,0,1,1 },      // 0
  { 1,0,0,1,1,1,1,1 },      // 1
  { 0,0,1,0,0,1,0,1 },      // 2
  { 0,0,0,0,1,1,0,1 },      // 3
  { 1,0,0,1,1,0,0,1 },      // 4
  { 0,1,0,0,1,0,0,1 },      // 5
  { 0,1,0,0,0,0,0,1 },      // 6
  { 0,0,0,1,1,1,1,1 },      // 7
  { 0,0,0,0,0,0,0,1 },      // 8
  { 0,0,0,0,1,0,0,1 },      // 9
  { 1,1,1,1,1,1,1,0 },      // Punkt (10)
};

int pin_array[] = {2, 3, 4, 5, 6, 7, 9, 10};  //Pins am Arduino

float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;   // Variablen für Temperatur Berechnung 

void setup() {
  Serial.begin(9600);
  pinMode(8,INPUT);
  

  for(int i = 0; i < 8; i++){
    pinMode(pin_array[i], OUTPUT);
  }
}


void loop() {
  int Schalterzustand = digitalRead(8);   //Zustand des drückens der Taste
  if(Schalterzustand == 1){               //überprüfen ob Strom fließt, wenn dann Temperatur messen
  int Vo = analogRead(8);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  Tc = 1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2) - 273.15; //Temperatur Berechnung

  int Temp = round(Tc); // Temperatur wird gerundet

  if (Temp > 9) {   // angezeigte Ziffern
    int ersteZiffer = Temp / 10;  
    int zweiteZiffer = Temp % 10;

    zahl(ersteZiffer);
    delay(2000);

    zahl(zweiteZiffer);
    punkt(false);
  } else {
    zahl(Temp);
    punkt(false);
  }

  Serial.print("Temperature: "); 
  //Serial.print(Tc);
  Serial.print(Temp);
  Serial.println(" C");   

  delay(500);
  }
}

void zahl(int zahl){
  for(int i = 0; i < 8; i++){
    digitalWrite(pin_array[i], zahl_array[zahl][i]);
  }
}

void punkt(boolean state) {
  digitalWrite(pin_array[7], state); // Der Punkt wird an Pin 7 angeschlossen
}



