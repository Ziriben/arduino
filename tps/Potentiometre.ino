int valeur_p=0; //var pour récupérer la tension aux bornes du potentiomètre, init à 0
int pin_p=0; 
int led_p1 = 38;
int led_p2 = 39;


void setup() {
  Serial.begin(9600); //init de la communication
  pinMode(led_p1, OUTPUT);
  pinMode(led_p2, OUTPUT);
}

void loop() {
  valeur_p=analogRead(A0); //lecture & conversion de la tension en valeur stockée dans valeur_p
  Serial.print("Val: ");
  Serial.println(valeur_p);
  

  digitalWrite(led_p1, HIGH);
  digitalWrite(led_p2, LOW);
  delay(1023 - valeur_p);

  digitalWrite(led_p1, LOW);
  digitalWrite(led_p2, HIGH);
  delay(1023 - valeur_p);

}
