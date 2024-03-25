#include <do an nhung.h>
#define LCD_RS_Pin   Pin_B0
#define LCD_RW_Pin   Pin_B1
#define LCD_ENABLE_Pin   Pin_B2
#define LCD_DATA4   Pin_B3
#define LCD_DATA5   Pin_B4
#define LCD_DATA6   Pin_B5
#define LCD_DATA7   Pin_B6

#include <lcd.c> //thu vien LCD
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
unsigned int16 Nhietdo;
void Sim()
{  printf("ATE1\n\r");
   delay_ms(50);
   printf("AT\n\r");
   delay_ms(1000);
   printf("AT+IPR=9600\n\r");
   delay_ms(50);
   printf("AT&W\n\r");
   delay_ms(50);
}
void Nhantin()
{  printf("AT+CMGF=1\n\r");
   delay_ms(50);
   printf("AT+CMGS=\"0367601002\"\n\r");
   delay_ms(1000);
   printf("FIRE ALERT");
   delay_ms(5000);
}
void main()
{  
   SET_tris_B(0x00);
   LCD_init();  // khoi tao lcd
   SETUP_ADC(ADC_clock_internal);
   SETUP_ADC_ports(PIN_A0); // chan chuyen doi thiet lap chan analog
   SET_ADC_CHANNEL(0);
   Sim();
   while(TRUE)
   {  
      LCD_gotoxy(1,1);
      LCD_putc("NHIET DO:");
      LCD_gotoxy(1,2);
      LCD_putc("KHOI:");
      Nhietdo=read_adc()/2.046;
      delay_ms(1);
      
      LCD_gotoxy(11,1);
      printf(LCD_putc,"%2LU C",Nhietdo);
      LCD_gotoxy(15,1);
      LCD_putc(0xDF);
      if(Nhietdo > 51 || input(pin_A1)==0)
      {  if(input(pin_A1)==0)
         {
            LCD_gotoxy(7,2);
            LCD_putc("CO   ");
            delay_ms(50);
         }
         if(input(pin_A1)==1)
         {  
            LCD_gotoxy(7,2);
            LCD_putc("KHONG");
            delay_ms(50);
         }
         output_high(pin_C0);
         Nhantin();
      }
      if(Nhietdo <=51 & input(pin_A1)==1)
      {  LCD_gotoxy(7,2);
         LCD_putc("KHONG");
         delay_ms(50);
         output_low(pin_C0);
      }

   }
      
   
      //TODO: User Code

}
