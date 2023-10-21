/**
 * @file mbci_gpio.h
 * @author Evan Xiao (1993996310@qq.com)
 * @brief GPIO 设备的抽象，用于一般场景下的 GPIO 操作
 * @version 0.1
 * @date 2023-09-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MBCI_GPIO_H__
#define __MBCI_GPIO_H__

#define MBCI_IO_HIGH 1
#define MBCI_IO_LOW 0


/**
 * @brief GPIO 输出模式
 * 
 */
enum mbci_gpio_mode
{
    /**
     * @brief 浮空输入。I/O 电平信号直接输入到寄存器，内部无上下拉电阻。如果在外部电路中没有上下拉电阻，那么输入信号将是不确定的。
     *
     */
    MBCI_GPIO_IN_FLOATING = 0x00,
    /**
     * @brief 上拉输入。内部连接上拉电阻，在引脚浮空时，输入信号将被读取为高电平。
     * 
     */
    MBCI_GPIO_IN_PULL_UP = 0x01,
    /**
     * @brief 下拉输入。内部连接下拉电阻，在引脚浮空时，输入信号将被读取为低电平。
     * 
     */
    MBCI_GPIO_IN_PULL_DOWN = 0x02,
    /**
     * @brief 推挽输出。当设置输出为高电平时，引脚输出高电平；当设置输出为低电平时，引脚输出低电平。
     * 
     */
    MBCI_GPIO_OUT_PP = 0x10,
    /**
     * @brief 开漏输出。当设置输出为高电平时，引脚为高阻状态，由外部电路决定状态；当设置输出为低电平时，引脚将拉低电平。
     * 
     */
    MBCI_GPIO_OUT_OD = 0x11,
};

/**
 * @brief 初始化指定的 GPIO 引脚
 * 
 * @param name 引脚名称，必须以 P 开头，且后面跟着引脚编号。引脚编号的规则如下: 引脚编号应该由端口号和引脚号组成,并通过`.`分隔，端口号为 0~7 或者 A-Z，引脚号为 00~99。例如 P1.01 表示端口 1 的第 1 号引脚。端口号可以是一个数字，也可是一个字母。由具体的芯片决定。引脚号必须是两位数的数字。
 * @param dir 引脚的输入输出模式，参见 enum mbci_gpio_mode
 */
void mbci_gpio_init(char *name, enum mbci_gpio_mode dir);

/**
 * @brief 对指定的 GPIO 引脚的输出进行设置
 * 
 * @param name 引脚名称。规则同 mbci_gpio_init
 * @param value 输出的电平，参见 MBCI_IO_HIGH 和 MBCI_IO_LOW
 */
void mbci_gpio_set(char *name, int value);

/**
 * @brief 读取指定的 GPIO 引脚的输入
 * 
 * @param name 引脚名称。规则同 mbci_gpio_init
 * @return int 输入的电平，参见 MBCI_IO_HIGH 和 MBCI_IO_LOW
 */
int mbci_gpio_get(char *name);

#endif // __MBCI_GPIO_H__
