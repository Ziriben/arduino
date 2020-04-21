#include "pitches.h"
//pin 2  a un led attaché à lui
int ledPin= 2;

//pin 12 a un bouton attaché à lui
int btnPin= 12;

//modifier ceci pour modifier la vitesse de la melodie
int tempo=108; 

// changez ce paramètre pour le pin que vous voulez utiliser
int buzz = 8;

int mel[] = { //notes de melodie
  NOTE_B4,8, NOTE_E5, 4, NOTE_C5,8, NOTE_B4,8, NOTE_C5,8,  NOTE_D5,4,    
};

//ceci calcule la durée d'une note entière en ms (60s/tempo)*4 beats
int fullNote = (60000 * 4) / tempo;

int divider = 0, noteTime = 0;

// sizeof donne le nombre d'octets, chaque valeur int est composée de deux octets (16 bits), il y a deux valeurs par note (hauteur et durée), donc pour chaque note il y a quatre octets
int notes=sizeof(mel)/sizeof(mel[0])/2; 

char msg = '  ';   // var pour contenir les données du serial
 
void setup() {
  //make the button's pin input
  pinMode(btnPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.print("Progr. intialisé\n");  
}

void loop_mel() {
  // itérer sur les notes de la mélodie. Rappelez-vous que le tableau est le double du nombre de notes (notes + durées)
  for (int aNote = 0; aNote < notes * 2; aNote = aNote + 2) {

    // calcule la durée de chaque note
    divider = mel[aNote + 1];
    if (divider > 0) {
      // note normale, continuer
      noteTime = (fullNote) / divider;
    } else if (divider < 0) {
      // les notes pointillées sont représentées avec des durées négatives !
      noteTime = (fullNote) / abs(divider);
      noteTime *= 1.5; // augmente la durée de moitié pour les notes pointillées
    }

    // nous ne jouons la note que pendant 90% de la durée, laissant 10% comme pause
    tone(buzz, mel[aNote], noteTime*0.9);

    // Attendez la durée spécifiée avant de jouer la note suivante.
    delay(noteTime);
    
    // Arrête la génération de la forme d'onde avant la note suivante.
    noTone(buzz);
  }
}

void pc_to_arduino() {
   // Pendant que les données sont envoyées en série, assigner au msg
  while (Serial.available()>0){ 
    msg=Serial.read();
  }

  // Allumer/éteindre la LED si nous recevons "O"/"N" en série
  if (msg=='H') {            
    digitalWrite(ledPin, HIGH);  // allumer la LED
    tone(buzz, mel[0], 600);
    delayMicroseconds(1000);
    //loop_mel();
  } else if (msg=='L') {
    digitalWrite(ledPin, LOW); // éteindre la LED
    noTone(buzz);
    delayMicroseconds(500);
  }
}

void arduino_to_pc() {
    //lire input pin
  int buttonState = digitalRead(btnPin);

  //si le bouton est appuyé
  if (buttonState == 1){
    Serial.write("1");
  }else{
    Serial.write("0");    
  }
}
void loop(){
  
  arduino_to_pc(); //pc_to_arduino();
}
