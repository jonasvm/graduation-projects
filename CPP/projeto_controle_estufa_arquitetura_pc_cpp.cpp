#include <stdio.h>
#include <sys/io.h>
#define ON 0XFF
#define OFF 0X00
#define PORT_IN 0X379
#define PORT_OUT 0X378

unsigned char sw1,s3,s2,s1;
unsigned int estado;

void entrada(void)
{
     ioperm(PORT_IN,1,1);
     if((inb(PORT_IN)& 0x80) == 0X80) sw1 = ON;
     else sw1 = OFF;
     if((inb(PORT_IN)& 0XB0) == 0XB0) s3 = ON;
     else s3 = OFF;
     if((inb(PORT_IN)& 0XA0)== 0XA0) s2 = ON;
     else s2 = OFF;
     if((inb(PORT_IN)& 0x90) == 0X90) s1 = ON;
     else s1 = OFF;
     ioperm(PORT_IN,1,0);
}

void desliga_tudo(void)
{
     ioperm(PORT_OUT,1,1);
     outb(0x00,PORT_OUT);
     ioperm(PORT_OUT,1,0);
}

//sinalizador
void liga_lampada(void)
{
     ioperm(PORT_OUT,1,1);
     outb(0x80,PORT_OUT);
     ioperm(PORT_OUT,1,0);
}

//sensor de temperatura
void trata_s1(void)
{
     ioperm(PORT_OUT,1,1);
     outb(0x81,PORT_OUT);
     ioperm(PORT_OUT,1,0);
}

//sensor de umidade
void trata_s2(void)
{
     ioperm(PORT_OUT,1,1);
     outb(0x82,PORT_OUT);
     ioperm(PORT_OUT,1,0);
}

//sensor de agua no solo
void trata_s3(void)
{
     ioperm(PORT_OUT,1,1);
     outb(0x84,PORT_OUT);
     ioperm(PORT_OUT,1,0);
}

void maquina_estado(void)
{
     switch(estado)
     {
          case 1: //verfica sw1
               desliga_tudo();
               if(sw1 == ON) estado = 2;
               break;
          case 2:
               liga_lampada();
               ioperm(PORT_IN,1,1);
               if((inb(PORT_IN)& 0X90) == 0X90) estado = 3;
               ioperm(PORT_IN,1,0);
               ioperm(PORT_IN,1,1);
               if((inb(PORT_IN)& 0XA0) == 0XA0) estado = 4;
               ioperm(PORT_IN,1,0);
               ioperm(PORT_IN,1,1);
               if((inb(PORT_IN)& 0XB0) == 0XB0) estado = 5;
               ioperm(PORT_IN,1,0);
               ioperm(PORT_IN,1,1);
               if(sw1 == OFF) estado = 1;
               ioperm(PORT_IN,1,0);
               break;
          case 3:
               trata_s1();
               if(sw1 == OFF) estado = 1;
               else
                    estado = 2;
               break;
          case 4:
               trata_s2();
               if(sw1 == OFF) estado = 1;
               else
                    estado = 2;
               break;
          case 5:
               trata_s3();
               if(sw1 == OFF) estado = 1;
               else
                    estado = 2;
               break;
     }
}

int main(void)
{
     estado=1;
     while(1)
     {
          entrada();
          maquina_estado();
     }
	 
     return 0;
	 
	 //  Para executar
	 // gcc -o projeto projeto.gcc (ou projeto.c)
     // sudo ./projeto
}