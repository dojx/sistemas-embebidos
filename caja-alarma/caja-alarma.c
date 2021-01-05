// Laboratorio 4: Alarma
// Nombre: Diego Omar Jimenez Navarro
// Codigo: 213526346
// Fecha: 05/10/19

#define BUZZER PORTC.RC2
#define LED_VERDE PORTC.RC3
#define LED_AZUL PORTC.RC4
#define LED_ROJO PORTC.RC5
#define BOTON_1 !PORTB.RB7
#define BOTON_2 !PORTB.RB6
#define BOTON_3 !PORTB.RB5
#define ABIERTO voltsAN0 >= 0x320
#define ROBADO voltsAN1 >= 0x320

unsigned int voltsAN0, voltsAN1;
int codigo[] = {1, 1, 3, 2};
int it = 0;

void checarBoton() {
  if(BOTON_1) {
    if(codigo[it] == 1) {
      it++;
    } else {
      it = 0;
    }
    LED_VERDE = 1;
    delay_ms(125);
  } else if(BOTON_2) {
    if(codigo[it] == 2) {
      it++;
    } else {
      it = 0;
    }
    LED_VERDE = 1;
    delay_ms(125);
  } else if(BOTON_3) {
    if(codigo[it] == 3) {
      it++;
    } else {
      it = 0;
    }
    LED_VERDE = 1;
    delay_ms(125);
  }
  if(it == 4) {
    it = 0;
    PORTC = 0;
    delay_ms(1000);
    while(!BOTON_2 || !BOTON_3) {}
  }
  LED_VERDE = 0;
}

void toneRobado() {
  Sound_Play(900, 50);
  checarBoton();
  Sound_Play(500, 50);
  checarBoton();
}

void toneAbierto() {
  Sound_Play(900, 50);
  checarBoton();
  delay_ms(50);
  checarBoton();
}

void alarma() {
  voltsAN0 = ADC_Read(0);
  voltsAN1 = ADC_Read(1);
  if(ROBADO) {
    BUZZER = 1;
    LED_ROJO = 1;
    LED_AZUL = 0;
    toneRobado();
    LED_ROJO = 0;
    LED_AZUL = 1;
    toneRobado();
  } else if(ABIERTO) {
    BUZZER = 1;
    LED_ROJO = 1;
    LED_AZUL = 0;
    toneAbierto();
    LED_ROJO = 0;
    toneAbierto();
  } else {
    PORTC = 0;
  }
}

void main() {
  ANSEL = 0x03; // AN0 y AN1 como entrada analogica
  TRISA = 0xFF; // Puerto A como entrada
  OPTION_REG = OPTION_REG & 0x7F; // Activar "Weak Pull-up"
  ANSELH = 0; // Resto de pines son digitales
  PORTB = 0xFF; // Activando pull-ups en puerto B
  TRISC = 0; // Puerto C como salida
  PORTC = 0; // Puerto C en bajo
  Sound_Init(&PORTC, 2);
  while (1) {
    alarma();
  }
}