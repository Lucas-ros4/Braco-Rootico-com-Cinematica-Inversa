/*
  Codigo por Lucas Rosa 
  GitHub Lucas-ros4
  data 25/12/28
  Esse projeto atualmetne esta na sua versao 1.0 e fuguramente pretendo adicionar mais um grau de liberdade e fazer a articulacao do pulso sempre ficar paralelo ao chao, alem de melhorar
  a precisao e integrar com imagem computacional
*/


#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <math.h>

// PCA9685 driver
Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40); //endereco padrao

//Tamanho dos elos dos bracos
const float L1 = 9.0;  
const float L2 = 9.0;

#define SERVO_FREQ 50  //frequencia padrao para servomotores
#define OMBRO_CH 1
#define COTOV_CH 2

// calibracao dos pulsos pwm
// valores encontrados rodando o teste e testando manualmente
#define OMBRO_MIN_PULSE 90
#define OMBRO_MAX_PULSE 530
#define COTOV_MIN_PULSE 90
#define COTOV_MAX_PULSE 500

//suavizacao - evita movimentos bruscos e reduz o esforco mecanicos dos servos motores
#define PASSO 2       // incremento de pulso pwm a cada iteracao
#define TEMPO 10      // delay em ms entre cada passo


// mantem a posicao atal em memória da posicao atual
int ombroAtual = OMBRO_MIN_PULSE;  
int cotovAtual = COTOV_MIN_PULSE;

void setup() {

  Serial.begin(115200);  
  Wire.begin();
  pca.begin();
  pca.setPWMFreq(SERVO_FREQ);

  Serial.println("Digite X Y em cm (ex: 9 9)");
}

// funcao para converter valores continuos(angulos) para pulsos pwm
int mapFloatToInt(float angle, float in_min, float in_max, int out_min, int out_max) {
  return (int)((angle - in_min) * (float)(out_max - out_min) / (in_max - in_min) + out_min);
}

// move o servo do valor atual ate o valor alvo em pequenos incrementos, em movimento crescente ou movimento decrescente
void moverSuave(int canal, int atual, int alvo) {
  if(atual < alvo){
    for(int i = atual; i <= alvo; i += PASSO){
      pca.setPWM(canal, 0, i);
      delay(TEMPO);
    }
  } else {
    for(int i = atual; i >= alvo; i -= PASSO){
      pca.setPWM(canal, 0, i);
      delay(TEMPO);
    }
  }
}

void loop() {
  if(Serial.available() >= 2){
    float y = Serial.parseFloat(); // vertical
    float x = Serial.parseFloat(); // horizontal


    //calcula a distancia do ponto d do ponto de origem do braco
    float dist2 = x*x + y*y;
    float dist = sqrt(dist2);

    // verifica se o ponto esta dentro do limite do braco
    if(dist > (L1+L2) || dist < fabs(L1-L2)){
      Serial.println("FORA DO ALCANCE");
      return;
    }

    // aqui calcula o cotovlo com lei dos cossenos
    float cosT2 = (dist2 - L1*L1 - L2*L2)/(2*L1*L2);
    cosT2 = constrain(cosT2, -1, 1);
    float t2 = acos(cosT2);

    // ombro
    float t1 = atan2(y, x) - atan2(L2*sin(t2), L1+L2*cos(t2));

    float t1_deg = degrees(t1);
    float t2_deg = degrees(t2);

    // aqui chama a funcao para converter o angulo para pulso
    int ombroPulse = mapFloatToInt(t1_deg, -90, 90, OMBRO_MIN_PULSE, OMBRO_MAX_PULSE);
    int cotovPulse = mapFloatToInt(t2_deg, 0, 180, COTOV_MIN_PULSE, COTOV_MAX_PULSE);

    // chama a funcao de suavizacao de movimento primeiro do ombro e depois do cotovelo
    // futuramente pretendo fazer elas se moverem juntas
    moverSuave(OMBRO_CH, ombroAtual, ombroPulse);
    ombroAtual = ombroPulse;

    moverSuave(COTOV_CH, cotovAtual, cotovPulse);
    cotovAtual = cotovPulse;

    Serial.print("X Y: "); Serial.print(x); Serial.print(" "); Serial.println(y);
    Serial.print("Ang Ombro: "); Serial.print(t1_deg); 
    Serial.print(" | Pulso Ombro: "); Serial.println(ombroPulse);
    Serial.print("Ang Cotovelo: "); Serial.print(t2_deg);
    Serial.print(" | Pulso Cotovelo: "); Serial.println(cotovPulse);
    Serial.println("------------------------");
  }
}