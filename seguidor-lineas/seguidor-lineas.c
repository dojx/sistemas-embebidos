#define LED_ON PORTD.RD7
#define L4 PORTB.RB7
#define L3 PORTB.RB6
#define L2 PORTB.RB5
#define L1 PORTB.RB4
#define R1 PORTB.RB3
#define R2 PORTB.RB2
#define R3 PORTB.RB1
#define R4 PORTB.RB0

#define DEFAULT_SPEED 115
#define MAX_SPEED 115
#define MIN_SPEED 0

char lastBlack = 0, it = 0;
int leftSpeed = 0, rightSpeed = 0, i = 0, sum = 0;
float KP = 0.0328, KD = 1, error = 0, lastError = 0, prop = 0, der = 0, control = 0;
void sensorCheck();

void main() {
  ANSELH = 0;
  ANSEL = 0;
  TRISC = 0;
  TRISD = 0;
  PORTC = 0;

  PWM1_Init(5000);
  PWM1_Start();
  PWM2_Init(5000);
  PWM2_Start();

  while(1) {
    sensorCheck();
    if (L1+L2+L3+L4 >= 3 && R1+R2+R3+R4 <= 2) {
      while(PORTB != 0b00011000) {
        sensorCheck();
        rightSpeed = MAX_SPEED - (L2*5 + L3*5 + L4*5);
        PWM1_Set_Duty(0);
        PWM2_Set_Duty(rightSpeed);
      }
    } else if (R1+R2+R3+R4 >= 3 &&  L1+L2+L3+L4 <= 2){
      while(PORTB != 0b00011000) {
        sensorCheck();
        leftSpeed = MAX_SPEED - (R2*5 + R3*5 + R4*5);
        PWM1_Set_Duty(leftSpeed);
        PWM2_Set_Duty(0);
      }
    } else
    if(PORTB != 0) {
      error= (0*L4+1000*L3+2000*L2+3000*L1+4000*R1+5000*R2+6000*R3+7000*R4)/(L1+L2+L3+L4+R1+R2+R3+R4);
      error = 3500 - error;
      prop = KP * error;
      der = KD * (error - lastError);
      lastError = error;
      control = prop + der;
      leftSpeed = DEFAULT_SPEED - control;
      rightSpeed = DEFAULT_SPEED + control;
      if (leftSpeed < MIN_SPEED) {
          leftSpeed = MIN_SPEED;
      }
      if (leftSpeed > MAX_SPEED) {
        leftSpeed = MAX_SPEED;
      }
      if (rightSpeed < MIN_SPEED) {
        rightSpeed = MIN_SPEED;
      }
      if (rightSpeed > MAX_SPEED) {
        rightSpeed = MAX_SPEED;
      }
      PWM1_Set_Duty(leftSpeed);
      PWM2_Set_Duty(rightSpeed);
      lastBlack = PORTB;
    //} //else if(lastBlack <= 0b00011000) {
//      while(PORTB != 0b00011000) {
//        sensorCheck();
//        leftSpeed = MAX_SPEED - (R2*40 + R3*30 + R4*20);
//        PWM1_Set_Duty(leftSpeed);
//        PWM2_Set_Duty(MIN_SPEED);
//      }
//    } else {
//      while(PORTB != 0b00011000) {
//        sensorCheck();
//        rightSpeed = MAX_SPEED - (L2*40 + L3*30 + L4*20);
//        PWM1_Set_Duty(MIN_SPEED);
//        PWM2_Set_Duty(rightSpeed);
//      }
    }
  }
}

void sensorCheck() {
  LED_ON = 1;
  TRISB = 0x00;
  PORTB = 0xFF;
  delay_us(10);
  TRISB = 0xFF;
  PORTB = 0x00;
  delay_us(700);
  LED_ON = 0;
}