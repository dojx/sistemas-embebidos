unsigned char cuenta;
unsigned char TABLA[]={0x77,0x14,0xB3,0xB6,0xD4,0xE6,0xE7,0x34,0xF7,0xF4};
void main()
{
  TRISC=0x00;
  OPTION_REG = OPTION_REG & 0x7F;
  ANSELH = 0;
  PORTB = 0xFF;

  while(1)
  {
   for(cuenta=0;cuenta!=10;cuenta++)
   {
     if(!PORTB.RB7 && cuenta > 0) {
       cuenta--;
     }
     PORTC=TABLA[cuenta];
     delay_ms(200);
   }
  }
}