/*
 * rev_stopwatch.c
 *
 * Created: 5/10/2021 4:30:02 PM
 * Author : lenovo
 */ 

#define F_CPU 12000000ul
#include <avr/io.h>
#include <util/delay.h>

#define SSDPORT PORTD
#define SLPORT PORTC
#define SL1 PC1
#define SL2 PC2
#define SL3 PC3
#define SL4 PC4

//Function Declaration (with 4 arguments but no return type)
void display(unsigned int d1,unsigned int d2,unsigned int d3,unsigned int d4);

//Array holding patterns 0	  1		2	3	4	  5		6	7	8	 9
unsigned int digit[10]={0XFC,0X60,0XDA,0XF2,0X66,0XB6,0XBE,0XE0,0XFE,0XF6};
	 
	 
int data1,data2,data3,data4;	//4 global variables to hold data

int main(void)
{
	DDRD=0XFF;			//Define PORTD as output
	DDRC=0b0011110;		//Define PC1, PC2, PC3, PC4 as Output

	while (1)
	{
		display(data1,data2,data3,data4); //Function to display data on SSD
		
		data4--;		//increment data4
		if (data4<0)
		{
			data4=9;	//if data4=10, reset data4 to 0
			data3--;	//increment data3
			
			if (data3<0)
			{
				data3=9;	//if data3=10, reset data3 to 0
				data2--;	//increment data2
				
				if (data2<0)
				{
					data2=9;	//if data2=10, reset data2 to 0
					data1--;	//increment data1
					
					if (data1<0)	//if data1=10
					{
						data1=data2=data3=data4=9;	//reset all to 0
					}
				}
			}
		}
	}
}
//display Function definition

void display(unsigned int d1,unsigned int d2,unsigned int d3,unsigned int d4)
{
	unsigned int i=0;	//local variable for looping
	
	for(i=0;i<250;i++)  //one loop takes 4ms | to get 1000ms delay, run loop 250 times
	{
		SLPORT=1<<SL2|1<<SL3|1<<SL4;	//SSD1 active
		SSDPORT=digit[d1];				//Data transmitted to SSD1
		_delay_ms(1);

		SLPORT=1<<SL1|1<<SL3|1<<SL4;	//SSD2 active
		SSDPORT=digit[d2];				//Data transmitted to SSD2
		_delay_ms(1);

		SLPORT=1<<SL1|1<<SL2|1<<SL4;	//SSD3 active
		SSDPORT=digit[d3];				//Data transmitted to SSD3
		_delay_ms(1);

		SLPORT=1<<SL1|1<<SL2|1<<SL3;	//SSD4 active
		SSDPORT=digit[d4];				//Data transmitted to SSD4
		_delay_ms(1);
	}
}

