unsigned char unidades = 0; // Variable para las unidades
unsigned char decenas = 0; // Variable para las decenas
unsigned char TABLA[] = {0b00001000, 0b01011110, 0b00010001, 0b00010010, 0b01000110, 0b00100010,
                         0b00100000, 0b00011110, 0b00000000, 0b00000110};

void conteo_up() {
  unidades++;
  if(unidades == 10) {
    unidades = 0;
    decenas++;
    if(decenas == 10) {
      decenas = 0;
    }
  }
}

void multiplexado(unsigned char veces) {
  PORTD.RD1 = 0;
  PORTD.RD2 = 0;
  while(veces) {
    PORTC = TABLA[unidades];
    PORTD.RD1 = 1;
    delay_ms(5);
    PORTD.RD1 = 0;
    PORTC = TABLA[decenas];
    PORTD.RD2 = 1;
    delay_ms(5);
    PORTD.RD2 = 0;
    veces--;
  }
}

void main() {
  TRISC = 0x00;
  TRISD = ~0b00000110; // Bit 0 y 1 como salida
  OPTION_REG = OPTION_REG & 0x7F;
  ANSELH = 0x00;
  PORTB = 0x01;
  PORTD = 0b00000110;
  while(1) {
    if(PORTB & 0x01) {
      conteo_up();
    }
    multiplexado(25);
  }
}