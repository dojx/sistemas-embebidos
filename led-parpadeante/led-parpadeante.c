void main() {
     TRISC = 0; // Configurando el "Bit 0" del puerto "C" como salida
     PORTC = 0b10101010;
     while(1) {
       PORTC.RC0^=1; // XOR con el "Bit 0" del puerto "C"
       PORTC.RC1^=1; // XOR con el "Bit 1" del puerto "C"
       PORTC.RC2^=1; // XOR con el "Bit 2" del puerto "C"
       PORTC.RC3^=1; // XOR con el "Bit 3" del puerto "C"
       PORTC.RC4^=1; // XOR con el "Bit 4" del puerto "C"
       PORTC.RC5^=1; // XOR con el "Bit 5" del puerto "C"
       PORTC.RC6^=1; // XOR con el "Bit 6" del puerto "C"
       PORTC.RC7^=1; // XOR con el "Bit 7" del puerto "C"
       delay_ms(250); // Retardo de 1/4 de segundo
     }
}