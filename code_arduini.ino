#include <Servo.h>

const int pirPin = 2;       // Broche de signal du capteur PIR
Servo fixedServo;            // Servomoteur pour le déplacement fixe
Servo rotatingServo;         // Servomoteur pour la rotation de la roulette

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  fixedServo.attach(9);       // Connecté à la broche 9
  rotatingServo.attach(10);   // Connecté à la broche 10
}

void loop() {
  if (digitalRead(pirPin) == HIGH) {
    captureAndProcessImage();
    delay(1000);  // Ajoutez un délai pour éviter la détection continue
  }
}

void captureAndProcessImage() {
  Serial.println("Capture d'image...");

  // Envoyer une commande pour déclencher la capture d'écran sur le PC
  Serial.println("CaptureScreen");

  // Attendre la réponse du PC (à ajuster en fonction de la réponse réelle)
  delay(2000);

  // Simulation du traitement d'image
  int wasteType = processImage();

  // Déterminer l'action en fonction du type de déchet détecté
  switch (wasteType) {
    case 1:
      Serial.println("Type de déchet 1 détecté");
      moveFixedServo(90);      // Exemple: déplacez le servomoteur à 90 degrés
      rotateRoulette(45);      // Exemple: tournez le servomoteur à 45 degrés
      break;
    // Ajoutez des cas pour d'autres types de déchets si nécessaire
  }
}

int processImage() {
  // Simulation : valeurs de luminosité des pixels (à remplacer par votre propre logique)
  int redValue = 100;  // Valeur de luminosité rouge simulée
  int greenValue = 80;  // Valeur de luminosité verte simulée
  int blueValue = 60;   // Valeur de luminosité bleue simulée

  // Simulation d'une détection de couleur (à remplacer par votre propre logique)
  if (redValue > greenValue && redValue > blueValue) {
    return 1; // Type de déchet 1
  } else if (greenValue > redValue && greenValue > blueValue) {
    return 2; // Type de déchet 2
  } else {
    return 3; // Type de déchet 3
  }
}

void moveFixedServo(int targetAngle) {
  // Ajoutez le code pour déplacer le servomoteur fixe à l'angle cible
  fixedServo.write(targetAngle);
  delay(1000);  // Ajoutez un délai pour laisser le servomoteur effectuer le mouvement
}

void rotateRoulette(int targetAngle) {
  // Ajoutez le code pour faire tourner le servomoteur de la roulette à l'angle cible
  rotatingServo.write(targetAngle);
  delay(1000);  // Ajoutez un délai pour laisser le servomoteur effectuer le mouvement
}
