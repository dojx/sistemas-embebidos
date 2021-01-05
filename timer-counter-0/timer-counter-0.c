 // Nombre: Diego Omar Jimenez Navarro
// Codigo: 213526346

void main() {
  OPTION_REG.T0CS = 1; // Contador externo
  OPTION_REG.T0SE = 1; // Flanco de bajada
  OPTION_REG.PSA = 1; // Asignacion del pre-escalador al WDT
  
  OPTION_REG.PS2 = 0; // Debido a lo anterior pre-escala 1:1
  OPTION_REG.PS1 = 0;
  OPTION_REG.PS0 = 0;
  
  TRISC = 0x00; // Puerto C como salida
  PORTC = 0x00; // Limpiar puerto C
  TMR0 = 0x00; // Inicializar TMR0
  
  while(1) {
    PORTC = TMR0; // Valor del TMR0 en el PORTC
  }
}