#define BOTON_1 !PORTB.RB7
#define BOTON_2 !PORTB.RB6
#define BOTON_3 !PORTB.RB5
#define BOTON_4 !PORTB.RB4

// LCD module connections
sbit LCD_RS at RE0_bit;
sbit LCD_EN at RE2_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISE0_bit;
sbit LCD_EN_Direction at TRISE2_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;
// End LCD module connections

float V_AN0 = 0, grados = 0;
char txt[8];
char txt_luz[] = {"1. Temperatura"};
char txt_temp[] = {"2. Luz"};
char txt_temp_ops[] = {"1.C 2.F 3.K 4.<-"};

unsigned int mode = 0, temp_mode = 1, lux = 0, i = 0;

void main() {
  ANSEL = 0x03; // AN0 y AN1 como entradas analogicas
  TRISA = 0xFF;
  ANSELH = 0; // Los demas pines son digitales
  OPTION_REG = OPTION_REG & 0x7F; // Pull-ups en B
  TRISC = 0;
  PORTC = 0;
  
  Lcd_Init();
  Lcd_cmd(_LCD_CLEAR);
  Lcd_cmd(_LCD_CURSOR_OFF);

  while(1) {
    Lcd_out(1, 1, txt_luz);
    Lcd_out(2, 1, txt_temp);
    if(BOTON_1) {
      Lcd_cmd(_LCD_CLEAR);
      mode = 1;
    } else if(BOTON_2) {
      Lcd_cmd(_LCD_CLEAR);
      mode = 2;
    }
    while(mode == 1) {
      if(BOTON_1) {
        Lcd_cmd(_LCD_CLEAR);
        temp_mode = 1;
      } else if(BOTON_2) {
        Lcd_cmd(_LCD_CLEAR);
        temp_mode = 2;
      } else if(BOTON_3) {
        Lcd_cmd(_LCD_CLEAR);
        temp_mode = 3;
      }
      V_AN0 = 0;
      for (i = 0; i < 255; i++) {
        V_AN0 = V_AN0 + ADC_Read(0);
      }
      grados = (V_AN0/255 * 5)/10; // Celsius
      if(temp_mode == 2) {
        grados = (grados * 9/5) + 32; // Celsius a Fahrenheit
      } else if(temp_mode == 3) {
        grados = grados + 273; // Celsius a Kelvin
      }
      IntToStr(grados, txt);
      Lcd_out(1, 4, txt);
      Lcd_out(2, 1, txt_temp_ops);
      delay_ms(100);
      
      if(BOTON_4) {
        Lcd_cmd(_LCD_CLEAR);
        mode = 0;
      }
    }
    while(mode == 2) {
      lux = ADC_Read(1);
      lux = lux*8/255;
      for (i = 1; i < 32; i++) {
        if (lux <= i) {
          if (i < 17) {
            Lcd_Chr(1, i, ' ');
          } else {
            Lcd_Chr(2, i - 16, ' ');
          }
        } else {
          if (i < 17) {
            Lcd_Chr(1, i, 255);
          } else {
            Lcd_Chr(2, i - 16, 255);
          }
        }
      }
      if(BOTON_4) {
        Lcd_cmd(_LCD_CLEAR);
        mode = 0;
      }
    }
  }
}