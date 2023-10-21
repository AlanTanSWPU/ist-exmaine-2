/**
  ******************************************************************************
  * @file   mbci_gpio.c
  * @author Alan Tan 
  * @brief  GPIO 设备的抽象，用于一般场景下的 GPIO 操作
  * @version 0.1
  * @date 2023-10
  *
***/


/* Includes ------------------------------------------------------------------*/
#include "mbci_gpio.h"
#include "cw32f030.h"
#include "cw32f030_gpio.h"
#include "cw32f030_rcc.h"

#define MBCI_ASSERT_ENABLE
#include "mbci_assert.h"


//=============================================================================
//GPIO 初始化
/**
 * @brief 初始化指定的 GPIO 引脚
 * 
 * @param name 引脚名称，必须以 P 开头，且后面跟着引脚编号。引脚编号的规则如下: 引脚编号应该由端口号和引脚号组成,并通过`.`分隔，端口号为 0~7 或者 A-Z，引脚号为 00~99。例如 P1.01 表示端口 1 的第 1 号引脚。端口号可以是一个数字，也可是一个字母。由具体的芯片决定。引脚号必须是两位数的数字。
 * @param dir 引脚的输入输出模式，参见 enum mbci_gpio_mode
 */
void mbci_gpio_init(char *name, enum mbci_gpio_mode dir)
{
	uint16_t GPIOx;
	if(name[1]>='A'&& name[1]<='Z') GPIOx=name[1]-'A';
	else if(name[1]>='0'&& name[1]<='9') GPIOx=name[1]-'0';  
	
	GPIO_TypeDef *GPIOX=(GPIO_TypeDef *)(GPIOA_BASE + 0x400 * GPIOx); //GPIOA到GPIOZ 基地址递增 0x400
	
	uint16_t Pins = 10*(name[3]-'0')+(name[4]-'0');
	
	MBCI_ASSERT(!((Pins<=15)&&(GPIOX==CW_GPIOA ||GPIOX==CW_GPIOB ||GPIOX==CW_GPIOC||GPIOX==CW_GPIOF)));
	
	REGBITS_SET(CW_SYSCTRL->AHBEN, RCC_AHB_PERIPH_GPIOA << GPIOx); //GPIOA到GPIOZ，写入AHBEN寄存器的值依次按位左移1
	
	GPIO_InitTypeDef GPIO_InitStruct;
    
	GPIO_InitStruct.IT = GPIO_IT_NONE;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	
	GPIO_InitStruct.Pins = GPIO_PIN_0 << Pins ; //Pin0到Pin99，写入DIR寄存器的值依次按位左移1
    
	switch(dir)  
	{
		case MBCI_GPIO_IN_FLOATING:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;          break;
		case MBCI_GPIO_IN_PULL_UP:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT_PULLUP;   break;
		case MBCI_GPIO_IN_PULL_DOWN:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT_PULLDOWN; break;
		case MBCI_GPIO_OUT_PP:
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;      break;
	    case MBCI_GPIO_OUT_OD: 
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;      break;
	}
	
	GPIO_Init(GPIOX, &GPIO_InitStruct);
}

//=============================================================================
//设置指定引脚电平
/**
 * @brief 对指定的 GPIO 引脚的输出进行设置
 * 
 * @param name 引脚名称。规则同 mbci_gpio_init
 * @param value 输出的电平，参见 MBCI_IO_HIGH 和 MBCI_IO_LOW
 */
void mbci_gpio_set(char *name, int value)
{
	uint16_t GPIOx;
	if(name[1]>='A'&& name[1]<='Z') GPIOx=name[1]-'A';
	else if(name[1]>='0'&& name[1]<='9') GPIOx=name[1]-'0';  
	
	GPIO_TypeDef *GPIOX=(GPIO_TypeDef *)(GPIOA_BASE + 0x400 * GPIOx); //GPIOA到GPIOZ 基地址递增 0x400
	
	uint16_t Pins = 10*(name[3]-'0')+(name[4]-'0');
	
	switch(value)
	{
		case MBCI_IO_HIGH:
			GPIO_WritePin(GPIOX, Pins, GPIO_Pin_SET); break;
		case MBCI_IO_LOW:
			GPIO_WritePin(GPIOX, Pins, GPIO_Pin_RESET); break;
	}
}

//=============================================================================
//获取指定引脚电平
/**
 * @brief 读取指定的 GPIO 引脚的输入
 * 
 * @param name 引脚名称。规则同 mbci_gpio_init
 * @return int 输入的电平，参见 MBCI_IO_HIGH 和 MBCI_IO_LOW
 */
int mbci_gpio_get(char *name)
{
	uint16_t GPIOx;
	if(name[1]>='A'&& name[1]<='Z') GPIOx=name[1]-'A';
	else if(name[1]>='0'&& name[1]<='9') GPIOx=name[1]-'0';  
	
	GPIO_TypeDef *GPIOX=(GPIO_TypeDef *)(GPIOA_BASE + 0x400 * GPIOx); //GPIOA到GPIOZ 基地址递增 0x400
	
	uint16_t Pins = 10*(name[3]-'0')+(name[4]-'0');

	
	return GPIO_ReadPin(GPIOX, Pins);
}
