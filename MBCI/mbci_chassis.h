/**
 * @file mbci_chassis.h
 * @author Evan Xiao (1993996310@qq.com)
 * @brief 底盘控制接口的定义
 * @version 0.1
 * @date 2023-10-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MBCI_CHASSIS_H__
#define __MBCI_CHASSIS_H__

/**
 * @brief 普通底盘的控制接口
 *
 */
struct mbci_normal_chassis
{
    /**
     * @brief 初始化底盘设备。
     *
     */
    void (*init)(struct mbci_normal_chassis *self);

    /**
     * @brief 设置底盘的速度。
     *
     * @param speed 底盘的速度，范围为 -10000~10000
     */
    void (*set_speed)(struct mbci_normal_chassis *self, int speed);

    /**
     * @brief 设置底盘的转向。
     *
     * @param turn 底盘的转向程度，范围为 -10000~10000。并且正数为左转，负数为右转
     */
    void (*set_turn)(struct mbci_normal_chassis *self, int turn);

    /**
     * @brief 进入刹车状态。通过设置速度或转向可以退出刹车状态。
     *
     */
    void (*brake)(struct mbci_normal_chassis *self);

    /**
     * @brief 关闭维持底盘运行的所有线程，通常用于紧急情况。同时，在退出之前，应尽可能的保证相关设备停止运行。
     *
     */
    void (*shutdown)(struct mbci_normal_chassis *self);

    /**
     * @brief 私有数据，供驱动开发者使用。
     *
     */
    void *priv;
};

#define mbci_normal_chassis_init(self) ((self)->init(self))
#define mbci_normal_chassis_set_speed(self, speed) ((self)->set_speed(self, speed))
#define mbci_normal_chassis_set_turn(self, turn) ((self)->set_turn(self, turn))
#define mbci_normal_chassis_brake(self) ((self)->brake(self))
#define mbci_normal_chassis_shutdown(self) ((self)->shutdown(self))

/**
 * @brief 麦克纳姆轮底盘的模式
 *
 */
enum mbci_mecanum_mode
{
    /**
     * @brief 前进(后退)模式
     *
     */
    MBCI_MECANUM_MODE_FORWARD,
    /**
     * @brief 左移(右移)模式
     *
     */
    MBCI_MECANUM_MODE_SIDEWAYS,
    /**
     * @brief 旋转模式
     *
     */
    MBCI_MECANUM_MODE_ROTATE,
    /**
     * @brief 左前(右后)模式
     *
     */
    MBCI_MECANUM_MODE_LEFT_FORWARD,
    /**
     * @brief 右前(左后)模式
     *
     */
    MBCI_MECANUM_MODE_RIGHT_FORWARD,
};

/**
 * @brief 麦克纳姆轮底盘的控制接口
 *
 */
struct mbci_mecanum_chassis
{
    /**
     * @brief 初始化底盘设备。
     *
     */
    void (*init)(struct mbci_mecanum_chassis *self);

    /**
     * @brief 设置底盘的速度。
     *
     * @param speed 底盘的速度，范围为 -10000~10000
     */
    void (*set_speed)(struct mbci_mecanum_chassis *self, int speed);

    /**
     * @brief 设置底盘的模式, 参见 @ref mbci_mecanum_mode，默认为前进模式。
     *
     * @param mode 底盘的模式, 参见 @ref mbci_mecanum_mode
     *
     */
    void (*set_mode)(struct mbci_mecanum_chassis *self, enum mbci_mecanum_mode);

    /**
     * @brief 进入刹车状态。通过设置速度或转向可以退出刹车状态。
     *
     */
    void (*brake)(struct mbci_mecanum_chassis *self);

    /**
     * @brief 关闭维持底盘运行的所有线程，通常用于紧急情况。同时，在退出之前，应尽可能的保证相关设备停止运行。
     *
     */
    void (*shutdown)(struct mbci_mecanum_chassis *self);

    /**
     * @brief 私有数据，供驱动开发者使用。
     *
     */
    void *priv;
};

#define mbci_mecanum_chassis_init(self) ((self)->init(self))
#define mbci_mecanum_chassis_set_speed(self, speed) ((self)->set_speed(self, speed))
#define mbci_mecanum_chassis_set_mode(self, mode) ((self)->set_mode(self, mode))
#define mbci_mecanum_chassis_brake(self) ((self)->brake(self))
#define mbci_mecanum_chassis_shutdown(self) ((self)->shutdown(self))

#endif
