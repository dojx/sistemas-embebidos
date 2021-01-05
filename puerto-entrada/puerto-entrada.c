// Nombre: Diego Omar Jimenez Navarro
// Codigo: 213526346
// Fecha: 24/09/19

void main() {
     TRISC = 0x00; // Puerto C salidas
     OPTION_REG = OPTION_REG & 0x7f; // Activar "Weak pull-up"
     ANSELH = 0x00; // Configurando entradas digitales en PORTB
     PORTB = 0xFF; // Activando pull-ups
     
     while(1) {
         PORTC = PORTB; // Leer valor del PORTB y depositarlo en PORTC
     }
}
