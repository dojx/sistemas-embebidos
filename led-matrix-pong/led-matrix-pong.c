// Proyecto 1: Pong en matriz de LEDs 8x8
// Nombre: Diego Omar Jimenez Navarro
// Codigo: 213526346
// Fecha: 05/10/19

#define P1_BI PORTC.RC3
#define P1_BD PORTC.RC2
#define P2_BI PORTC.RC0
#define P2_BD PORTC.RC1

int p1Pos, p2Pos, p1Puntos, p2Puntos, xPos, yPos, xSpeed, ySpeed, nivel, bDelay, frame;

int cero[8] = {0xFF, 0xFF, 0b00011111, 0b01011111, 0b01011111, 0b01011111, 0b00011111, 0xFF};
int uno[8] = {0xFF, 0xFF, 0b10111111, 0b10111111, 0b10111111, 0b10111111, 0b10111111, 0xFF};
int dos[8] = {0xFF, 0xFF, 0b00011111, 0b01111111, 0b00011111, 0b11011111, 0b00011111, 0xFF};
int tres[8] = {0xFF, 0xFF, 0b00011111, 0b11011111, 0b00011111, 0b11011111, 0b00011111, 0xFF};
int cuatro[8] = {0xFF, 0xFF, 0b11011111, 0b11011111, 0b00011111, 0b01011111, 0b01011111, 0xFF};
int cinco[8] = {0xFF, 0xFF, 0b00011111, 0b11011111, 0b00011111, 0b01111111, 0b00011111, 0xFF};

int newGame = 1;

void setup() {
  ANSEL = 0; // Digitales puerto A
  ANSELH = 0; // Digitales puerto B
  TRISA = 0;
  TRISB = 0;
  TRISC = 0xFF;
  PORTA = 0;
  PORTB = 0xFF;
  PORTC = 0;
  
  p1Pos = 3;
  p2Pos = 3;
  p1Puntos = 0;
  p2Puntos = 0;
  xPos = (rand() % 2) + 3; // Valor aleatorio entre 3 y 4
  yPos = (rand() % 2) + 3;
  xSpeed = 1;
  ySpeed = 1;
  nivel = 2; // Numero de frames que esperara la bola antes de moverse
  bDelay = nivel;
  frame = 1; // Empezar en frame 1
}

void gol() {
  int i, j;
  int a = 5;
  PORTB = 0b01010101;
  while(a > 0) {
    for (i = 0; i < 30; i++) { // Inicia frame
      for (j = 0; j < 8; j++) {
        PORTA = 0b10000000 >> j;
        PORTB ^= 0xFF;
        Delay_us(100);
      }
    } // Termina frame
    PORTB ^= 0xFF;
    a--;
  }
}

void score(int p1, int p2) {
  int i, j;
  int a = 10;
  PORTB = 0xFF;
  while(a > 0) {
    for (i = 0; i < 30; i++) { // Inicia frame
      for (j = 0; j < 8; j++) {
        PORTA = 0b10000000 >> j;
        if(p2 == 0) {
          PORTB = (cero[j] >> 5) | 0b11111000;
        } else if(p2 == 1) {
          PORTB = (uno[j] >> 5) | 0b11111000;
        } else if(p2 == 2) {
          PORTB = (dos[j] >> 5) | 0b11111000;
        } else if(p2 == 3) {
          PORTB = (tres[j] >> 5) | 0b11111000;
        } else if(p2 == 4) {
          PORTB = (cuatro[j] >> 5) | 0b11111000;
        } else if(p2 == 5) {
          PORTB = (cinco[j] >> 5) | 0b11111000;
        }
        if(p1 == 0) {
          PORTB &= cero[j];
        } else if(p1 == 1) {
          PORTB &= uno[j];
        } else if(p1 == 2) {
          PORTB &= dos[j];
        } else if(p1 == 3) {
          PORTB &= tres[j];
        } else if(p1 == 4) {
          PORTB &= cuatro[j];
        } else if(p1 == 5) {
          PORTB &= cinco[j];
        }
        Delay_us(100);
        PORTB = 0xFF;
      }
    } // Termina frame
    a--;
  }
  gol();
}

void main() {
  setup();
  while(1) {
    int i, j;
    for (i = 0; i < 30; i++) { // Inicia frame
      for (j = 0; j < 8; j++) {
        PORTA = 0b10000000 >> j;
        // Bola
        if(j == xPos) {
          PORTB &= (0b00000001 << yPos) ^ 0xFF;
        }
        // Paletas
        if(j == p1Pos -1 || j == p1Pos || j == p1Pos + 1) { // P1
          PORTB &= 0b01111111;
        }
        if(j == p2Pos -1 || j == p2Pos || j == p2Pos + 1) { // P2
          PORTB &= 0b11111110;
        }
        Delay_us(100);
        PORTB = 0xFF;
      }
    } // Termina frame
    
    if(P1_BI && P1_BD && P2_BI && P2_BD) {
      newGame = 0;
    }

    if(frame % 100 == 0 && nivel > 0) {
      nivel--;
    }

    // Jugadores
    if(P1_BI && p1Pos < 6) {
      p1Pos += 1;
    } else if(P1_BD && p1Pos > 1) {
      p1Pos += -1;
    }
    if(P2_BD && p2Pos < 6) {
      p2Pos += 1;
    } else if(P2_BI && p2Pos > 1) {
      p2Pos += -1;
    }

    // Bola fisica
    if(newGame == 0) {
      if(bDelay == 0) {
        if(yPos == 6 && ySpeed == 1) {
          if((xPos == p1Pos - 1) || (xPos == p1Pos) || (xPos == p1Pos + 1) || 
          (xPos + 1 == p1Pos - 1 && xSpeed == 1) || (xPos - 1 == p1Pos + 1 && xSpeed == -1)) {
            ySpeed = -1;
          }
        }
        if(yPos == 1 && ySpeed == -1) {
          if((xPos == p2Pos - 1) || (xPos == p2Pos) || (xPos == p2Pos + 1) || 
          (xPos + 1 == p2Pos - 1 && xSpeed == 1) || (xPos - 1 == p2Pos + 1 && xSpeed == -1)) {
            ySpeed = 1;
          }
        }
        if((xPos == 0 && xSpeed == -1) || (xPos == 7 && xSpeed == 1)) {
          xSpeed *= -1;
        }
        xPos += xSpeed;
        yPos += ySpeed;
        bDelay = nivel;
      } else {
        bDelay--;
      }
      frame++;
    }

    // Gol y resetear
    if(yPos < 0 || yPos > 7) {
      if(yPos < 0) {
        p1Puntos++;
      } else {
        p2Puntos++;
      }
      p1Pos = 3;
      p2Pos = 3;
      xPos = (rand() % 2) + 3; // Posicion aleatoria en x entre 3 y 4
      yPos = (rand() % 2) + 3; // Posicion aleatoria en y entre 3 y 4
      ySpeed *= -1;
      nivel = 2;
      bDelay = nivel;
      frame = 1;
      gol();
      score(p1Puntos, p2Puntos);
      PORTB = 0xFF;
    }
    
    // 5 puntos
    if(p1Puntos == 5 || p2Puntos == 5) {
      p1Puntos = 0;
      p2Puntos = 0;
      newGame = 1;
    }
  }
}