/**
 * @file mbci_button.h
 * @author Evan Xiao (1993996310@qq.com)
 * @brief 按键设备的抽象。
 * @version 0.1
 * @date 2023-10-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MBCI_BUTTON_H__
#define __MBCI_BUTTON_H__

#define MBCI_BTN_PRESSED 1
#define MBCI_BTN_RELEASED 0

struct mbci_button
{
    /**
     * @brief 初始化按键设备。
     *
     */
    void (*init)(struct mbci_button *self);
    /**
     * @brief 读取按键的状态。返回类型为 int，返回值为 MBCI_BTN_PRESSED 或 MBCI_BTN_RELEASED。
     *
     */
    int (*read)(struct mbci_button *self);

    /**
     * @brief 私有数据，供驱动开发者使用。
     *
     */
    void *priv;
};

#define mbci_button_read(button) ((button)->read())

#endif
