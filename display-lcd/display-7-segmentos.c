unsigned char DB; // Variable para el manejo de instrucciones
#define DB0 0 // Bit 0 para data bus
#define DB1 1 // Bit 1 para data bus
#define DB2 2 // Bit 2 para data bus
#define DB3 3 // Bit 3 para data bus
#define DB4 4 // Bit 4 para data bus
#define DB5 5 // Bit 5 para data bus
#define DB6 6 // Bit 6 para data bus
#define DB7 7 // Bit 7 para data bus
#define ID 1 // Increment/Decrement Mode
#define SH 0 // Entere Shift ON/OFF
#define BLK 0 // Blink Shift ON/OFF
#define CUR 1 // Cursor Shift ON/OFF
#define DSP 2 // Display Shift ON/OFF
#define F 2 // Matrix
#define NL 3 // N Lines
#define B_Busy 7 // Bit Busy Flag
#define RS 0 // Bit Select register del LCD
#define RW 1 // Bit Read/Write del LCD
#define E 2 // Bit Enable
#define SC 3 // Desplazamiento del Display/Cursor
#define RL 2 // Izquierda/Derecha

volatile unsigned char TEXTO1[] = {"Diego Jimenez \n"};
volatile unsigned char TEXTO2[] = {"213526346 \n"};

void configuracion() {
  ANSEL = 0;
  PORTE &= (0 << RS | 0 << RW | 0 << E);
  PORTD = 0x30;
  TRISE &= (0 << RS | 0 << RW | 0 << E);
  TRISD = 0;
}

void RESET_LCD() {
  delay_ms(50);
}

void CONFIG_SET() {
  DB = (1 << DB5) | (1 << DB4) | (1 << NL);
}

void DISPLAY_ON_OFF() {
  DB = (1 << DB3) | (1 << DSP) | (1 << CUR); // | (1 << BLK);
}

void ENTRY_MODE_SET() {
  DB = (1 << DB2) | (1 << ID); // | (1 << SH);
}

void CLEAR_DISPLAY() {
  DB = 0x01;
}

void SET_DDRAM() {
  DB = 0xC0;
}

void ENABLE() {
  PORTD = DB;
  PORTE |= (1 << E);
  delay_ms(2);
  PORTE &= ~((1 << E));
}

void CADENA1() {
  unsigned char i = 0;
  PORTE |= (1 << RS);
  while((TEXTO1[i] != '\n')) {
    DB = TEXTO1[i];
    ENABLE();
    i++;
  }
  PORTE &= ~((1 << RS));
}

void CADENA2() {
  unsigned char i = 0;
  PORTE |= (1 << RS);
  while((TEXTO2[i] != '\n')) {
    DB = TEXTO2[i];
    ENABLE();
    i++;
  }
  PORTE &= ~((1 << RS));
}

void main() {
  configuracion();
  RESET_LCD();
  CONFIG_SET();
  ENABLE();
  DISPLAY_ON_OFF();
  ENABLE();
  CLEAR_DISPLAY();
  ENABLE();
  ENTRY_MODE_SET();
  ENABLE();
  CADENA1();
  SET_DDRAM();
  ENABLE();
  CADENA2();
  for(;;) {
  }
}