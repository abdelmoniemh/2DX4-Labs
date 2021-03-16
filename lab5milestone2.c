// 2DX4StudioW30E1_Decoding a Button Press
// This program illustrates detecting a single button press.
// This program uses code directly from your course textbook.
//
// This example will be extended for in W21E0 and W21E1.
//
// Written by Ama Simons
// January 30, 2020
// Last Update: January 21, 2020


#include <stdio.h>
#include <stdint.h>
#include "tm4c1294ncpdt.h"
#include "Systick.h"
#include "PLL.h"

int portmValue = 0;

void PortE0E1E2E3_Init(void){
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; // activate the clock for Port E
while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R4) == 0){}; // allow time for clock to stabilize
	GPIO_PORTE_DIR_R = 0b00001111;
	GPIO_PORTE_DEN_R = 0b00001111; // Enable PE0:PE3 
return;
}


void PortM0M1M2M3_Init(void){
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R11; //activate the clock for Port M
while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R11) == 0){}; //allow time for clock to stabilize
	GPIO_PORTM_DIR_R = 0b00000000; // Make PM0:PM3 inputs, reading if the button is pressed or not
	GPIO_PORTM_DEN_R = 0b00001111; // Enable PM0:PM3
return;
}




//Turns on D2, D1
void PortN0N1_Init(void){
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R12; //activate the clock for Port N
while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R12) == 0){};//allow time for clock to stabilize
GPIO_PORTN_DIR_R=0b00000011; //Make PN0 and PN1 outputs, to turn on LED's
GPIO_PORTN_DEN_R=0b00000011; //Enable PN0 and PN1
return;
}



//Turns on D3, D4
void PortF0F4_Init(void){
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5; //activate the clock for Port F
while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R5) == 0){};//allow time for clock to stabilize
GPIO_PORTF_DIR_R=0b00010001; //Make PF0 and PF4 outputs, to turn on LED's
GPIO_PORTF_DEN_R=0b00010001;
return;
}


int DecodeValue(int full8bits){
	//char dictionary[4][4] = {{'1','2','3','A'}, {'4','5','6','B'}, {'7','8','9','C'},{'*','0','#','D'}};
	int binary[4][4] = {{0b0001,0b0010,0b0011,0b1010},{0b0100,0b0101,0b0110,0b1011},{0b0111,0b1000,0b1001,0b1100},{0b1110,0b0000,0b1111,0b1101}};
	//int evalue = full8bits%10000;
	//int mvalue = (full8bits - full8bits%10000)/10000;
	
	int evalue = full8bits&0b00001111;
	int mvalue = full8bits&0b11110000;
	mvalue = mvalue>>4; 
		
	int mvalues[] = {0b1110,0b1101,0b1011,0b111};
	int evalues[] = {0b0001,0b0010,0b0100,0b1000};
	int i =0;	
	for (i = 0;i<4;i++){
		if (mvalue == mvalues[i])
			break;
	}
	int j =0;	
	for (j = 0;j<4;j++){
		if (evalue == evalues[j])
			break;
	}
	
	return binary[j][i];
}	




int main(void){
//PLL_Init();
//SysTick_Init();
PortE0E1E2E3_Init();
PortM0M1M2M3_Init();
PortN0N1_Init();
PortF0F4_Init();

int values[16] = {0};
values[0] = DecodeValue(0b11100001); //1
values[1] = DecodeValue(0b11010001); //2 
values[2] = DecodeValue(0b10110001); //3
values[3] = DecodeValue(0b01110001); //A
values[4] = DecodeValue(0b11100010); //4
values[5] = DecodeValue(0b11010010); //5 
values[6] = DecodeValue(0b10110010); //6
values[7] = DecodeValue(0b01110010); //B
values[8] = DecodeValue(0b11100100); //7
values[9] = DecodeValue(0b11010100); //8 
values[10] = DecodeValue(0b10110100); //9
values[11] = DecodeValue(0b01110100); //C
values[12] = DecodeValue(0b11101000); //*
values[13] = DecodeValue(0b11011000); //0 
values[14] = DecodeValue(0b10111000); //#
values[15] = DecodeValue(0b01111000); //D



	

