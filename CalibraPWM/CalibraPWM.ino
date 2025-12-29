#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);

#define SERVO_FREQ 50
#define SERVO_CH 0   // colocar o numero do servo aqui para calibrar

void setup() {
  Serial.begin(115200);
  Wire.begin();

  pca.begin();
  pca.setPWMFreq(SERVO_FREQ);

  Serial.println("=== CALIBRACAO DE SERVO ===");
  Serial.println("Digite um valor de pulso: ");
}

void loop() {
  if (Serial.available()) {
    int pulse = Serial.parseInt();

    if (pulse > 0) {
      pca.setPWM(SERVO_CH, 0, pulse);

      Serial.print("Pulso enviado: ");
      Serial.println(pulse);
    }
  }
}
