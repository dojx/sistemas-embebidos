// Nombre: Diego Omar Jimenez Navarro
// Codigo: 213526346

void main() {
  TRISC = 0x00; // Puerto C como salida - mostrara el ADRESL
  TRISD.RD0 = 0; // Bit 0 del puerto D como salida
  TRISD.RD1 = 0;
  
  TRISA.RA0 = 1; // Bit 0 de puerto A como entrada
  ANSEL.RA0 = 1; // Bit 0 de puerto A como entrada analoga
  
  ADCON0.ADCS1 = 1; // Seleccion del oscilador interno FRC
  ADCON0.ADCS0 = 1;
  
  ADCON1.ADFM = 1; // Justificado a la derecha
  
  ADCON0.ADON = 1; // Encendido del ADC
  
  while(1) {
    delay_ms(100); // Tiempo de muestreo
    
    ADCON0.GO_DONE = 1; // Inicio de conversion
    
    while(ADCON0.GO_DONE) {
      // Espera de la conversion "poleo"
    }
    
    PORTC = ADRESL; // Muestra los 10 bits de conversion
    PORTD = ADRESH;
  }
}