#include <Servo.h>

Servo servoPoussoir;  // Servo for pushing waste into the roulette
Servo servoRoulette;  // Servo for rotating the roulette

char commande;  // Variable to store the keyboard command

void setup() {
  servoPoussoir.attach(9);   // Servo for pushing waste into the roulette
  servoRoulette.attach(10);  // Servo for rotating the roulette

  Serial.begin(9600);  // Initialize serial communication

  // Initialize servos to a starting position
  servoPoussoir.write(90);
  servoRoulette.write(90);
}

void loop() {
  if (Serial.available() > 0) {
    // Read the command from the serial keyboard
    commande = Serial.read();
    executerCommande();
  }
}

void executerCommande() {
  // Execute the corresponding actions based on the command
  switch (commande) {
    case '1':
      pousserDansRoulette();
      break;
    case '2':
      tournerRoulette(45);  // Example: turn towards the plastic bin
      break;
    case '3':
      // Add your action for the third case
      break;
    // Add more cases for additional commands if needed
  }
}

void pousserDansRoulette() {
  // Move the servo to push waste into the roulette
  servoPoussoir.write(180);
  delay(500);  // Wait for a short moment
  servoPoussoir.write(90);  // Return to the initial position
}

void tournerRoulette(int angle) {
  // Move the servo to rotate the roulette towards the corresponding bin
  servoRoulette.write(angle);
  delay(1000);  // Wait for a short moment
  servoRoulette.write(90);  // Return to the initial position
}
