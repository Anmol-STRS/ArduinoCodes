#include <Arduino.h>
#include <SHA256.h>
#include <Crypto.h>

// Function to generate a random salt
void generateSalt(byte* salt, size_t saltSize) {
  for (size_t i = 0; i < saltSize; i++) {
    salt[i] = random(256); // Generate random byte (0-255)
  }
}

// Function to hash password with salt using SHA-256
String hashPassword(const char* password, const byte* salt, size_t saltSize) {
  SHA256 sha256;
  sha256.reset();
  sha256.update(password, strlen(password));
  sha256.update(salt, saltSize);

  byte hash[32]; // Size of SHA-256 hash is 32 bytes
  sha256.finalize(hash, 32);

  String hashedPassword = "";
  for (size_t i = 0; i < 32; i++) { // Iterate through each byte of the hash
    if (hash[i] < 0x10) {
      hashedPassword += "0";
    }
    hashedPassword += String(hash[i], HEX);
  }
  return hashedPassword;
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); // Initialize random number generator

  const char* password = "AnmolDhiman";
  const size_t saltSize = 16; // Choose the size of the salt (in bytes)
  byte salt[saltSize];
  generateSalt(salt, saltSize);

  // Print the salt
  Serial.print("Salt: ");
  for (size_t i = 0; i < saltSize; i++) {
    if (salt[i] < 0x10) {
      Serial.print("0");
    }
    Serial.print(salt[i], HEX);
  }
  Serial.println();

  // Hash the password with the salt
  String hashedPassword = hashPassword(password, salt, saltSize);

  // Print the hashed password
  Serial.print("Hashed Password: ");
  Serial.println(hashedPassword);
}

void loop() {
  // Nothing here for now
 
}
