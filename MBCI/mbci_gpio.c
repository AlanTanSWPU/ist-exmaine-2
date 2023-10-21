/**
  ******************************************************************************
  * @file   mbci_gpio.c
  * @author Alan Tan 
  * @brief  GPIO �豸�ĳ�������һ�㳡���µ� GPIO ����
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
//GPIO ��ʼ��
/**
 * @brief ��ʼ��ָ���� GPIO ����
 * 
 * @param name �������ƣ������� P ��ͷ���Һ���������ű�š����ű�ŵĹ�������: ���ű��Ӧ���ɶ˿ںź����ź����,��ͨ��`.`�ָ����˿ں�Ϊ 0~7 ���� A-Z�����ź�Ϊ 00~99������ P1.01 ��ʾ�˿� 1 �ĵ� 1 �����š��˿ںſ�����һ�����֣�Ҳ����һ����ĸ���ɾ����оƬ���������źű�������λ�������֡�
 * @param dir ���ŵ��������ģʽ���μ� enum mbci_gpio_mode
 */
void mbci_gpio_init(char *name, enum mbci_gpio_mode dir)
{
	uint16_t GPIOx;
	if(name[1]>='A'&& name[1]<='Z') GPIOx=name[1]-'A';
	else if(name[1]>='0'&& name[1]<='9') GPIOx=name[1]-'0';  
	
	GPIO_TypeDef *GPIOX=(GPIO_TypeDef *)(GPIOA_BASE + 0x400 * GPIOx); //GPIOA��GPIOZ ����ַ���� 0x400
	
	uint16_t Pins = 10*(name[3]-'0')+(name[4]-'0');
	
	MBCI_ASSERT(!((Pins<=15)&&(GPIOX==CW_GPIOA ||GPIOX==CW_GPIOB ||GPIOX==CW_GPIOC||GPIOX==CW_GPIOF)));
	
	REGBITS_SET(CW_SYSCTRL->AHBEN, RCC_AHB_PERIPH_GPIOA << GPIOx); //GPIOA��GPIOZ��д��AHBEN�Ĵ�����ֵ���ΰ�λ����1
	
	GPIO_InitTypeDef GPIO_InitStruct;
    
	GPIO_InitStruct.IT = GPIO_IT_NONE;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	
	GPIO_InitStruct.Pins = GPIO_PIN_0 << Pins ; //Pin0��Pin99��д��DIR�Ĵ�����ֵ���ΰ�λ����1
    
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
//����ָ�����ŵ�ƽ
/**
 * @brief ��ָ���� GPIO ���ŵ������������
 * 
 * @param name �������ơ�����ͬ mbci_gpio_init
 * @param value ����ĵ�ƽ���μ� MBCI_IO_HIGH �� MBCI_IO_LOW
 */
void mbci_gpio_set(char *name, int value)
{
	uint16_t GPIOx;
	if(name[1]>='A'&& name[1]<='Z') GPIOx=name[1]-'A';
	else if(name[1]>='0'&& name[1]<='9') GPIOx=name[1]-'0';  
	
	GPIO_TypeDef *GPIOX=(GPIO_TypeDef *)(GPIOA_BASE + 0x400 * GPIOx); //GPIOA��GPIOZ ����ַ���� 0x400
	
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
//��ȡָ�����ŵ�ƽ
/**
 * @brief ��ȡָ���� GPIO ���ŵ�����
 * 
 * @param name �������ơ�����ͬ mbci_gpio_init
 * @return int ����ĵ�ƽ���μ� MBCI_IO_HIGH �� MBCI_IO_LOW
 */
int mbci_gpio_get(char *name)
{
	uint16_t GPIOx;
	if(name[1]>='A'&& name[1]<='Z') GPIOx=name[1]-'A';
	else if(name[1]>='0'&& name[1]<='9') GPIOx=name[1]-'0';  
	
	GPIO_TypeDef *GPIOX=(GPIO_TypeDef *)(GPIOA_BASE + 0x400 * GPIOx); //GPIOA��GPIOZ ����ַ���� 0x400
	
	uint16_t Pins = 10*(name[3]-'0')+(name[4]-'0');

	
	return GPIO_ReadPin(GPIOX, Pins);
}
