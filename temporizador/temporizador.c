int unidades = 1; // Variable para las unidades
int decenas = 0; // Variable para las decenas
int centenas = 0; // Variable para las centenas
int millares = 0; // Variable para las millares
int i;
const int ms = 1;
unsigned char TABLA[] = {0b00001001, 0b10101111, 0b00110001, 0b00100011, 0b10000111,
                         0b01000011, 0b01000001, 0b00101111, 0b00000001, 0b00000111};
void conteo_up() {
  if(PORTB.RB1) {
    unidades++;
    if(unidades == 10) {
      unidades = 0;
      decenas++;
      if(decenas == 6) {
        decenas = 0;
        centenas++;
        if(centenas == 10){
          centenas = 0;
          millares++;
          if(millares == 6){
            millares = 0;
          }
        }
      }
    }
  } else {
    unidades--;
    if(unidades == -1) {
      unidades = 9;
      decenas--;
      if(decenas == -1) {
        decenas = 5;
        centenas--;
        if(centenas == -1){
          centenas = 9;
          millares--;
          if(millares == -1){
            millares = 5;
          }
        }
      }
    }
  }
}

void multiplexado(unsigned char veces) {
  PORTD.RD0 = 0;
  PORTD.RD1 = 0;
  PORTD.RD2 = 0;
  PORTD.RD3 = 0;
  while(veces) {
    PORTC = TABLA[unidades];
    PORTD.RD1 = 1;
    delay_ms(ms);
    PORTD.RD1 = 0;
    PORTC = TABLA[decenas];
    PORTD.RD0 = 1;
    delay_ms(ms);
    PORTD.RD0 = 0;
    PORTC = TABLA[centenas];
    PORTC.RC0 = 0;
    PORTD.RD2 = 1;
    delay_ms(ms);
    PORTD.RD2 = 0;
    PORTC = TABLA[millares];
    PORTD.RD3 = 1;
    delay_ms(ms);
    PORTD.RD3 = 0;
    veces--;
  }
}

void main() {
  TRISA = 0x00;
  TRISC = 0x00;
  TRISD = ~0b00001111; // Bit 0, 1, 2 y 3 como salidas
  OPTION_REG = OPTION_REG & 0x7F;
  ANSELH = 0x00;
  ANSEL = 0x00;
  PORTA = 0x00;
  PORTB = 0xFF;
  PORTD = 0b00001111;
  Sound_Init(&PORTA, 0);
  while(1) {
    while(!PORTB.RB0) {
      PORTC = 0xFF;
    }
    if((unidades + decenas + centenas + millares) == 0) {
      for(i = 0; i < 50; i++) {
        Sound_Play(900, 50);
        multiplexado(1);
        delay_ms(30);
      }
    }
    multiplexado(125);
    if(PORTB.RB2) {
      conteo_up();
    } else {
      if(!PORTB.RB4) {
        unidades++;
        if(unidades == 10) {
          unidades = 0;
        }
      } else if (!PORTB.RB5) {
        decenas++;
        if(decenas == 6) {
          decenas = 0;
        }
      } else if (!PORTB.RB6) {
        centenas++;
        if(centenas == 10) {
          centenas = 0;
        }
      } else if (!PORTB.RB7) {
        millares++;
        if(millares == 6) {
          millares = 0;
        }
      }
    }
  }
}