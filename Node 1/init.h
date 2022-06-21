#ifndef INIT_H
#define INIT_H

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include "math.h"
#include "tm4c123gh6pm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_i2c.h"
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "driverlib/can.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/i2c.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"

#define GPIO_LED  GPIO_PORTF_BASE
#define RED  GPIO_PIN_1
#define BLUE  GPIO_PIN_2
#define GREEN  GPIO_PIN_3
#define WHITE  RED | BLUE | GREEN 
#define SW1 0x01
#define SW2 0x10
#define SW1_2 0x00
#define SW   SW1 | SW2

volatile uint32_t SwitchCheck = 0;
volatile uint32_t StateCase = 0;
volatile bool switchFlag = 0;
volatile bool stateFlag = 0;
volatile bool incrementFlag = 0;
volatile bool decrementFlag = 0;
volatile bool whiteFlag = 0;
int state = 0;
volatile bool errFlag = 0; 
tCANMsgObject msg; 
unsigned int msgData;
unsigned char *msgDataPtr = (unsigned char *)&msgData; 

void SysTickIntHandler(void);
void CANIntHandler(void);

// CAN interrupt handler
void CANIntHandler(void) {
	unsigned long status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE); // read interrupt status
	// controller status interrupt
	if(status == CAN_INT_INTID_STATUS) { 
		status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
		errFlag = 1;
	} else if(status == 1) { // message object 1
		CANIntClear(CAN0_BASE, 1); // clear interrupt
		errFlag = 0; // clear any error flags
	} 
}
void CAN_Init(void){
	// Set up CAN0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // enable CAN0 GPIO peripheral
	GPIOPinConfigure(GPIO_PB4_CAN0RX);
	GPIOPinConfigure(GPIO_PB5_CAN0TX);
	GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
	CANInit(CAN0_BASE);
	CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
	CANIntRegister(CAN0_BASE, CANIntHandler);
	CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
	IntEnable(INT_CAN0);
	CANEnable(CAN0_BASE);
}

void CAN_Send(){
	// Set up msg object
	msgData = 0;
	msg.ui32MsgID = 1;
	msg.ui32MsgIDMask = 0;
	msg.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
	msg.ui32MsgLen = sizeof(msgDataPtr);
	msg.pui8MsgData = msgDataPtr;
	// send as msg object 1
	CANMessageSet(CAN0_BASE, 1, &msg, MSG_OBJ_TYPE_TX); 
}

void initClock(void){
	SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_5);
}
void initGPIO(void){//GPIO initialization and interrupt enabling
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
		GPIOPinTypeGPIOOutput(GPIO_LED, WHITE);
		GPIO_PORTF_LOCK_R = 0x4C4F434B;
		GPIO_PORTF_CR_R = 0x1F;
		GPIO_PORTF_DIR_R = 0x0E;
		GPIO_PORTF_PUR_R = 0x11;
		GPIO_PORTF_DEN_R = 0x1F;
	  IntMasterEnable();
    SysTickPeriodSet(SysCtlClockGet());
    SysTickIntRegister(SysTickIntHandler);
    SysTickIntEnable();
    SysTickEnable();
}

void SysTickIntHandler(void){
    SwitchCheck++;
    StateCase++;
    if(SwitchCheck == 1){
        SwitchCheck = 0;
        switchFlag = 1;
    }
    if(StateCase == 2){
        StateCase = 0;
        stateFlag = 1;
    }
}
void stateChange(uint32_t Color){
	  GPIOPinWrite(GPIO_LED, RED, ~RED);
    GPIOPinWrite(GPIO_LED, BLUE, ~BLUE);
    GPIOPinWrite(GPIO_LED, GREEN, ~GREEN);
    GPIOPinWrite(GPIO_LED, Color, Color);
}

uint32_t SW_Input(void){
   return (GPIO_PORTF_DATA_R&0x11);
}
void switchState(void){
  switch(SW_Input()){

        case SW1:
                incrementFlag = 1;
                while(SW_Input() == SW1){}
                break;    
        case SW2:
                decrementFlag = 1;
                while(SW_Input() == SW2){}
                break;
 
        case SW1_2:
                whiteFlag = 1;
                while(SW_Input() == SW1_2){}
                break;            
}
}
void vSwitchTask(void){
	        if(switchFlag == 1){
            switchState();
            switchFlag = 0; 
        }
}

void vLedTask(void){
	uint32_t Color[]={WHITE,RED,GREEN,BLUE};
	if(stateFlag==1){
            if(whiteFlag == 1){
                state = 0;
                whiteFlag = 0;
								stateChange(Color[state]);
								msgDataPtr[0] = Color[state];
								CAN_Send();
            }
            if(incrementFlag == 1){
                state++;
                if(state>3)
                    state=0;
						    stateChange(Color[state]);
								msgDataPtr[0] = Color[state];
								CAN_Send();
                incrementFlag = 0;
            }
            if(decrementFlag == 1){
                state--;
                if(state<0)
                    state=3;
								stateChange(Color[state]);
								msgDataPtr[0] = Color[state];
								CAN_Send();
                decrementFlag = 0;
            }
            stateFlag = 0;
        }
}

#endif