// Proyecto 1: Pong en matriz de LEDs 8x8
// Nombre: Diego Omar Jimenez Navarro
// Codigo: 213526346

signed char stop = 1;
signed char cuenta = 0;
unsigned char TABLA[]={0x77,0x14,0xB3,0xB6,0xD4,0xE6,0xE7,0x34,0xF7,0xF4};
void main()
{
  TRISC=0x00;
  OPTION_REG = OPTION_REG & 0x7F;
  ANSELH = 0;
  PORTB = 0xFF;

  while(1)
  {
    while(!PORTB.RB1) {
      PORTC = 0;
    }
    PORTC=TABLA[cuenta];
    delay_ms(200);
    if(!PORTB.RB7) {
      stop *= -1;
      delay_ms(100);
    }
    if(stop == 1) {
      if(!PORTB.RB2) {
        cuenta--;
      } else {
        cuenta++;
      }
      if(cuenta == 10) {
        cuenta = 0;
      } else if(cuenta == -1) {
        cuenta = 9;
      }
    }
  }
}