int pulses = 0, freq = 0;
unsigned char count = 0;
unsigned char T[] = {0b00001001, 0b10101111, 0b00110001, 0b00100011, 0b10000111,
                         0b01000011, 0b01000001, 0b00101111, 0b00000001, 0b00000111};
void disp(){
  unsigned char indexM, indexC, indexD, indexU;
  int aux = freq;
  indexM = aux/1000;
  indexC = (aux%1000)/100;
  aux -= 1000*indexM + 100*indexC;
  indexD = aux/10;
  indexU = aux%10;
  PORTD = 0x00;
  PORTC = 0x00;
  PORTD.RD1 = 1;
  PORTC = T[indexU];
  delay_ms(1);
  PORTD.RD1 = 0;
  PORTD.RD0 = 1;
  PORTC = T[indexD];
  delay_ms(1);
  PORTD.RD0 = 0;
  PORTD.RD2 = 1;
  PORTC = T[indexC];
  delay_ms(1);
  PORTD.RD2 = 0;
  PORTD.RD3 = 1;
  PORTC = T[indexM];
  delay_ms(1);
}

void main() {
  OPTION_REG.T0CS = 1;
  OPTION_REG.T0SE = 1;
  OPTION_REG.PSA  = 1;

  T1CON.TMR1ON = 1;
  T1CON.TMR1CS = 0;
  T1CON.T1CKPS1 = 0;
  T1CON.T1CKPS0 = 0;

  OPTION_REG.PS2  = 0;
  OPTION_REG.PS1  = 0;
  OPTION_REG.PS0  = 0;

  INTCON.GIE=1;
  INTCON.PEIE=1;
  INTCON.T0IE=1;
  PIE1.TMR1IE=1;

  TRISC = 0x00;
  TRISD = 0x00;
  PORTC = 0x00;
  PORTD = 0x00;
  TMR1H = 0;
  TMR1L = 0;
  while(1){
    disp();
  }
}

void interrupt(){
  if(INTCON.TMR0IF){
    pulses+=256;
    INTCON.TMR0IF = 0;
  }
  if(PIR1.TMR1IF){
    if(count>14){
      count = 0;
      pulses = pulses + TMR0;
      freq = pulses;
      pulses = 0;
      TMR0 = 0;
    }
    count++;
    PIR1.TMR1IF = 0;
  }
}