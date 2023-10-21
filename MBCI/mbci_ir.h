/**
 * @file mbci_ir.h
 * @author Evan Xiao (1993996310@qq.com)
 * @brief 光电循迹模块的控制接口的定义
 * @version 0.1
 * @date 2023-10-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MBCI_IR_H__
#define __MBCI_IR_H__

/**
 * @brief 光电循迹模块的控制接口
 *
 */
struct mbci_ir
{
    /**
     * @brief 初始化光电循迹模块
     *
     */
    void (*init)(struct mbci_ir *self);

    /**
     * @brief 获取光电循迹模块的数据
     *
     * @param left_data 左边的数据,以二进制的形式存储，其中 1 代表有黑线，0 代表无黑线，低位靠近传感器中间。
     * @param right_data 右边的数据，以二进制的形式存储，其中 1 代表有黑线，0 代表无黑线，低位靠近传感器中间。
     * @param middle_data 中间的数据，以二进制的形式存储，其中 1 代表有黑线，0 代表无黑线，通常只有第一位有效。
     *
     */
    void (*fetch)(struct mbci_ir *self, unsigned char left_data, unsigned char right_data, unsigned char middle_data);

    /**
     * @brief 私有数据，供驱动开发者使用。
     *
     */
    void *priv;
};

#endif // __MBCI_IR_H__