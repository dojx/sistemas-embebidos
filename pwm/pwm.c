void PWM_CFG();
void Ancho_Pulso(int ancho_useg);
void Periodo(int t_useg);

void main() {
     int i;
     PWM_CFG();
     Periodo(256);

     while(1){
           for(i = 0;i<=1000;i=i+20){
                 Ancho_Pulso(i);
                 delay_ms(15);
           }
     }
}

void PWM_CFG(){
     CCP1CON.P1M1 = 0;
     CCP1CON.P1M0 = 0;
     CCP1CON.CCP1M3 = 1;
     CCP1CON.CCP1M2 = 1;

     PIR1.TMR2IF = 0;
     T2CON.TMR2ON=1;
     TRISC.RC2 = 0;
}

void Ancho_Pulso(int ancho){
     CCP1CON|=((ancho&0x0003)<<4);
     CCPR1L=ancho>>2;
}

void Periodo(int t_useg){
     PR2 = (t_useg-1);
}