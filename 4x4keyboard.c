#include <16F877.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP,PUT
#use delay(clock= 20000000)
#use rs232(baud = 57600, xmit=PIN_C6, rcv=PIN_C7)


int data, rb_tast, flag;
char x;
byte const TAST_MAP[16] = {'1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}; //nasa lookup tabela

#INT_RB
void tastatura()
{
rb_tast = 0;
flag = 0;
output_high(PIN_B0); //postavi liniju b0 na 1
output_low(PIN_B1); // ostale linije na 0
output_low(PIN_B2);
output_low(PIN_B3);

if(input(PIN_B4)){ //Ispitivanje reda 0
rb_tast=rb_tast+1;
flag = 1;
}
if(input(PIN_B5)){ //Ispitivanje reda 1
rb_tast=rb_tast+5;
flag = 1;
}
if(input(PIN_B6)){ //Ispitivanje reda 2
rb_tast=rb_tast+9;
flag = 1;
}
if(input(PIN_B7)){ //Ispitivanje reda 3
rb_tast=rb_tast+13;
flag = 1;
}
if (flag) {
x= TAST_MAP[rb_tast-1]; //lookup tabela citanje
goto debauns;
} else { rb_tast = rb_tast+1;}

output_low(PIN_B0);
output_high(PIN_B1);
output_low(PIN_B2);
output_low(PIN_B3); // dovodimo drugu kolonu na stanje logicke jedinice

if(input(PIN_B4)){ //Ispitivanje reda 0
rb_tast=rb_tast+1;
flag = 1;
}
if(input(PIN_B5)){ //Ispitivanje reda 1
rb_tast=rb_tast+5;
flag = 1;
}
if(input(PIN_B6)){ //Ispitivanje reda 2
rb_tast=rb_tast+9;
flag = 1;
}
if(input(PIN_B7)){ //Ispitivanje reda 3
rb_tast=rb_tast+13;
flag = 1;
}
if (flag) {
x= TAST_MAP[rb_tast-1]; //lookup tabela citanje
goto debauns;
} else { rb_tast = rb_tast+1;}

output_low(PIN_B0);
output_low(PIN_B1);
output_high(PIN_B2);
output_low(PIN_B3); //dovodjenje trece kolone u stanje logicke 1

if(input(PIN_B4)){ //Ispitivanje reda 0
rb_tast=rb_tast+1;
flag = 1;
}
if(input(PIN_B5)){ //Ispitivanje reda 1
rb_tast=rb_tast+5;
flag = 1;
}
if(input(PIN_B6)){ //Ispitivanje reda 2
rb_tast=rb_tast+9;
flag = 1;
}
if(input(PIN_B7)){ //Ispitivanje reda 3
rb_tast=rb_tast+13;
flag = 1;
}
if (flag) {
x= TAST_MAP[rb_tast-1]; //lookup tabela citanje
goto debauns;
} else { rb_tast = rb_tast+1;}

output_high(PIN_B3);
output_low(PIN_B1);
output_low(PIN_B2);
output_low(PIN_B0);

if(input(PIN_B4)){ //Ispitivanje reda 0
rb_tast=rb_tast+1;
flag = 1;
}
if(input(PIN_B5)){ //Ispitivanje reda 1
rb_tast=rb_tast+5;
flag = 1;
}
if(input(PIN_B6)){ //Ispitivanje reda 2
rb_tast=rb_tast+9;
flag = 1;
}
if(input(PIN_B7)){ //Ispitivanje reda 3
rb_tast=rb_tast+13;
flag = 1;
}
if (flag) {
x= TAST_MAP[rb_tast-1]; //lookup tabela citanje
goto debauns;
} else goto debauns;

debauns:
while(input(pin_B4) || input(pin_B5) || input(pin_B6) || input(pin_B7)); //cekaj dok se ne otpusti pritisnuti taster
delay_ms(30);
//data = input_b(); //citanje viseg polubajta porta B za detekciju novog prekida po izlasku iz prekidne rutine
set_tris_b(0xF0);
output_b(0x0F); //sve cetiri kolone dovodimo u stanje logicke jedinice
input(PIN_B4);
input(PIN_B5);
input(PIN_B6);
input(PIN_B7);
//output_b(0x0F); //sve cetiri kolone dovodimo u stanje logicke jedinice
printf("Karakter koji odgovara pritisnutom tasteru je %c", x);
//Eventualno resetovati RBIF
}

void main()
{
set_tris_b(0xF0); //linije viseg polubajta ulazne, nizeg izlazne
// port_b_pullups(TRUE); imamo spojene otpornike
output_b(0x0F);
input(PIN_B4);
input(PIN_B5);
input(PIN_B6);
input(PIN_B7);
//data = input_b(); //upisivanje procitanog porta B u lecevima (flipflopovima)
//procitace se 0 u slucaju otvorenih tastera na redovima
enable_interrupts(INT_RB);
enable_interrupts(GLOBAL);
while(TRUE);
}