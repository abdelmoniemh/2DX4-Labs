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

void PortK_Init(void){
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R9; // activate the clock for Port E
while((SYSCTL_PRGPIO_R&SYSCTL_RCGCGPIO_R9) == 0){}; // allow time for clock to stabilize
	GPIO_PORTK_DIR_R = 0b11111111;
	GPIO_PORTK_DEN_R = 0b11111111; 

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
	char dictionary[4][4] = {{'1','2','3','A'}, {'4','5','6','B'}, {'7','8','9','C'},{'*','0','#','D'}};
	//int binary[4][4] = {{0b0001,0b0010,0b0011,0b1010},{0b0100,0b0101,0b0110,0b1011},{0b0111,0b1000,0b1001,0b1100},{0b1110,0b0000,0b1111,0b1101}};
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
	
	return (int)dictionary[j][i];
}	


void turnOnLEDs(int binary){//d4d3d2d1
	GPIO_PORTK_DATA_R = binary;
	portmValue = GPIO_PORTK_DIR_R;
	
}

int main(void){
//PLL_Init();
//SysTick_Init();
PortE0E1E2E3_Init();
PortM0M1M2M3_Init();
PortN0N1_Init();
PortF0F4_Init();
PortK_Init();
	

/*	
while(1){
	int pm = GPIO_PORTM_DATA_R;
	int pe = GPIO_PORTE_DATA_R;
	int full8bit = (GPIO_PORTM_DATA_R<<4) + GPIO_PORTE_DATA_R;
	int binary = DecodeValue(full8bit);
	turnOnLEDs(binary);
}*/
int full8bit = 0;
int binary =0;
while(1){

//Row 1****************************************************************************

GPIO_PORTE_DIR_R = 0b00000001; // To drive you use the data direction register
GPIO_PORTE_DATA_R = 0b00000000;
int pm = GPIO_PORTM_DATA_R;
int pe = GPIO_PORTE_DIR_R;
full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);
	
//Column 1 - Button 1
while((GPIO_PORTM_DATA_R&0b00000001)==0){
full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);
turnOnLEDs(binary);
}
GPIO_PORTN_DATA_R=0b00000000;//Turn off Port N LED's
GPIO_PORTF_DATA_R=0b00000000;//Turn off Port F LED's
GPIO_PORTK_DATA_R = 0b00000000;

//Column 2 - Button 2
while((GPIO_PORTM_DATA_R&0b00000010)==0){
full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);
turnOnLEDs(binary);
}
GPIO_PORTN_DATA_R=0b00000000;
GPIO_PORTF_DATA_R=0b00000000;
GPIO_PORTK_DATA_R = 0b00000000;

while((GPIO_PORTM_DATA_R&0b00000100)==0){
full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);
turnOnLEDs(binary);
}

GPIO_PORTN_DATA_R=0b00000000;
GPIO_PORTF_DATA_R=0b00000000;
GPIO_PORTK_DATA_R = 0b00000000;

while((GPIO_PORTM_DATA_R&0b00001000)==0){
full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);
turnOnLEDs(binary);
}
GPIO_PORTN_DATA_R=0b00000000;
GPIO_PORTF_DATA_R=0b00000000;
GPIO_PORTK_DATA_R = 0b00000000;
//Row 2***************************************************************************************
GPIO_PORTE_DIR_R = 0b00000010; // To drive you use the data direction register
GPIO_PORTE_DATA_R = 0b00000000;
full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);




while((GPIO_PORTM_DATA_R&0b00000001)==0){
	full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);
turnOnLEDs(binary);
}
GPIO_PORTN_DATA_R=0b00000000;//Turn off Port N LED's
GPIO_PORTF_DATA_R=0b00000000;//Turn off Port F LED's
GPIO_PORTK_DATA_R = 0b00000000;


//Column 2 - Button 2
while((GPIO_PORTM_DATA_R&0b00000010)==0){
	full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);
turnOnLEDs(binary);
}
GPIO_PORTN_DATA_R=0b00000000;
GPIO_PORTK_DATA_R = 0b00000000;
GPIO_PORTF_DATA_R=0b00000000;

while((GPIO_PORTM_DATA_R&0b00000100)==0){
	full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);
turnOnLEDs(binary);
}
GPIO_PORTN_DATA_R=0b00000000;
GPIO_PORTF_DATA_R=0b00000000;
GPIO_PORTK_DATA_R = 0b00000000;

while((GPIO_PORTM_DATA_R&0b00001000)==0){
	full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);
turnOnLEDs(binary);
}
GPIO_PORTN_DATA_R=0b00000000;
GPIO_PORTF_DATA_R=0b00000000;
GPIO_PORTK_DATA_R = 0b00000000;

//Row 3***********************************************************************

GPIO_PORTE_DIR_R = 0b00000100; //Drive Row 3
GPIO_PORTE_DATA_R = 0b00000000; 
full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);

while((GPIO_PORTM_DATA_R&0b00000001)==0){
	full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);
turnOnLEDs(binary);
}
GPIO_PORTN_DATA_R=0b00000000;//Turn off Port N LED's
GPIO_PORTF_DATA_R=0b00000000;//Turn off Port F LED's
GPIO_PORTK_DATA_R = 0b00000000;


//Column 2 - Button 2
while((GPIO_PORTM_DATA_R&0b00000010)==0){
	full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);
turnOnLEDs(binary);
}
GPIO_PORTN_DATA_R=0b00000000;
GPIO_PORTF_DATA_R=0b00000000;
GPIO_PORTK_DATA_R = 0b00000000;

while((GPIO_PORTM_DATA_R&0b00000100)==0){
	full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);
turnOnLEDs(binary);
}
GPIO_PORTN_DATA_R=0b00000000;
GPIO_PORTF_DATA_R=0b00000000;
GPIO_PORTK_DATA_R = 0b00000000;

while((GPIO_PORTM_DATA_R&0b00001000)==0){
	full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);
turnOnLEDs(binary);
}
GPIO_PORTN_DATA_R=0b00000000;
GPIO_PORTK_DATA_R = 0b00000000;
GPIO_PORTF_DATA_R=0b00000000;

//Row 4****************************************************************

GPIO_PORTE_DIR_R = 0b00001000; //Drive Row 4
GPIO_PORTE_DATA_R = 0b00000000; 
full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);

while((GPIO_PORTM_DATA_R&0b00000001)==0){
	full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);
turnOnLEDs(binary);
}
GPIO_PORTN_DATA_R=0b00000000;//Turn off Port N LED's
GPIO_PORTF_DATA_R=0b00000000;//Turn off Port F LED's
GPIO_PORTK_DATA_R = 0b00000000;


//Column 2 - Button 2
while((GPIO_PORTM_DATA_R&0b00000010)==0){
	full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);
turnOnLEDs(binary);
}
GPIO_PORTN_DATA_R=0b00000000;
GPIO_PORTF_DATA_R=0b00000000;
GPIO_PORTK_DATA_R = 0b00000000;

while((GPIO_PORTM_DATA_R&0b00000100)==0){
	full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);
turnOnLEDs(binary);
}
GPIO_PORTN_DATA_R=0b00000000;
GPIO_PORTF_DATA_R=0b00000000;
GPIO_PORTK_DATA_R = 0b00000000;

while((GPIO_PORTM_DATA_R&0b00001000)==0){
	full8bit = (GPIO_PORTM_DATA_R<<4) + (GPIO_PORTE_DIR_R&0b00001111);
binary = DecodeValue(full8bit);
turnOnLEDs(binary);
}
GPIO_PORTN_DATA_R=0b00000000;
GPIO_PORTF_DATA_R=0b00000000;
GPIO_PORTK_DATA_R = 0b00000000;



}



}