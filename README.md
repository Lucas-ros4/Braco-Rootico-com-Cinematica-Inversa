# Braço Robótico com Cinemática Inversa

https://github.com/user-attachments/assets/08c4fb1e-5cd2-4366-8970-d2f45a87a15a

Este repositório apresenta um **projeto educacional de braço robótico com dois graus de liberdade (2-DOF)**, cujo objetivo principal é **ensinar e fornecer a base conceitual e prática para que qualquer pessoa consiga implementar cinemática inversa em seu próprio braço robótico**.

O projeto foi pensado menos como um produto fechado e mais como um **guia estruturado** para a compreensão e aplicação da cinemática inversa em braços planares com dois eixos.

---

## Objetivo do Projeto

O foco central deste trabalho é **entender como funciona a cinemática inversa em um braço robótico de 2 graus de liberdade**, partindo do modelo geométrico até sua implementação em código.

Futuramente, pretende-se implementar **3 graus de liberdade**.

O principal objetivo do projeto é **auxiliar qualquer pessoa a aplicar cinemática inversa em seus próprios projetos**, fornecendo base teórica e prática.

Ao longo do projeto, busca-se:

- compreender a lógica geométrica da cinemática inversa;
- adaptar os cálculos para braços com diferentes dimensões;
- converter ângulos articulares em sinais PWM para servomotores;
- aplicar o mesmo raciocínio em **qualquer braço robótico 2-DOF**, independentemente do modelo mecânico.

---

## Sobre o Modelo 3D

O **modelo 3D original não é de minha autoria**.

Modelo 3D original:  
https://www.thingiverse.com/thing:6313449

O modelo foi **modificado com o objetivo de reduzir custos**, mantendo a funcionalidade necessária para o estudo da cinemática inversa.

>  O modelo 3D modificado ainda será adicionado ao repositório.

### Comparação de configuração

**Modelo original**
- 4 × MG996R  
- 1 × SG90  

**Modelo modificado (este projeto)**
- 3 × MG996R  
- 2 × SG90  

Essa modificação reduz o custo do projeto, tornando-o mais acessível para fins educacionais.

---

## Programação

Toda a **programação do projeto é autoral**.

O código foi desenvolvido com foco em:
- clareza conceitual;
- correspondência direta entre geometria e implementação;
- facilidade de adaptação para outros braços robóticos;
- aprendizado do funcionamento da cinemática inversa.

Principais características:
- uso de microcontrolador (Arduino / ESP32);
- controle de servos via **PCA9685**;
- movimento suavizado entre posições.

---

## Cinemática Inversa

A cinemática inversa implementada considera:

- braço **planar**;
- dois elos rígidos;
- duas articulações rotacionais (ombro e cotovelo).

O problema resolvido é:

> Dado um ponto cartesiano \((x, y)\), calcular os ângulos do ombro e do cotovelo necessários para que a ponta do braço alcance esse ponto.

A solução baseia-se em:
- construção de um triângulo geométrico;
- Lei dos Cossenos;
- funções trigonométricas (`acos`, `atan2`).

O método apresentado **não depende do braço específico deste repositório** e pode ser reutilizado em **qualquer braço robótico com 2 graus de liberdade**.

---

## PDF explicativo

Os **desenhos, a lógica e a explicação do código** foram escritos e desenhados por mim no PDF abaixo:

[ProjetoBracoDesenho.pdf](https://github.com/user-attachments/files/24362834/ProjetoBracoDesenho.pdf)

O PDF explica:
- a construção geométrica da cinemática inversa;
- o significado físico de cada ângulo;
- a transição da matemática para o código;
- como adaptar os cálculos para outros braços.

Este material foi pensado para que **qualquer pessoa consiga implementar cinemática inversa**, mesmo sem experiência prévia em robótica.

---

## Estado Atual do Projeto

Futuramente, pretendo:
- implementar mais um grau de liberdade;
- trabalhar com coordenadas \((x, y, z)\), e não apenas \((x, y)\);
- fazer com que a articulação do pulso permaneça sempre paralela ao chão;
- integrar o controle do braço com visão computacional.

---

## Vídeos

https://github.com/user-attachments/assets/52a2e25b-cd42-4387-9cb3-ba07fd79e5c0  


https://github.com/user-attachments/assets/cf884404-c777-4614-be0b-01da1af36e56  


https://github.com/user-attachments/assets/ffa2af8b-93b5-4ceb-b231-34baa1e6569a 


https://github.com/user-attachments/assets/fbf14f48-b9dd-4fd4-9a69-1422732b3dc9  


https://github.com/user-attachments/assets/c835e01b-6be3-4bfc-a7b7-b3cbc7499b33  

---

```text
/src      → Código-fonte
/pdf      → PDF explicativo
/media    → Fotos e vídeos
/models   → STL (modelo modificado – ainda será adicionado)
/calib    → Código de calibração de PWM
