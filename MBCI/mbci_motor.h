/**
 * @file mbci_motor.h
 * @author Evan Xiao (1993996310@qq.com)
 * @brief 电机设备的抽象。
 * @version 0.1
 * @date 2023-10-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MBCI_MOTOR_H__
#define __MBCI_MOTOR_H__

/**
 * @brief 电机的驱动模式。
 *
 */
enum mbci_motor_mode
{
    /**
     * @brief 慢衰减模式。此模式下，若速度为 0 则表现为滑行状态。
     *
     */
    MBCI_MOTOR_FAST_DECAY = 0,
    /**
     * @brief 快衰减模式。此模式下，若速度为 0 则表现为制动状态。
     *
     */
    MBCI_MOTOR_SLOW_DECAY = 1,
};

struct mbci_motor
{
    /**
     * @brief 初始化电机设备。
     *
     */
    void (*init)(struct mbci_motor *self);

    /**
     * @brief 设置电机的输出强度。
     * @param value 输出强度，范围为 -10000~10000，负数表示反转。
     *
     */
    void (*set_output)(struct mbci_motor *self, int value);

    /**
     * @brief 设置电机的驱动模式
     * @param mode 驱动模式，参见 enum mbci_motor_mode
     */
    void (*set_mode)(struct mbci_motor *self, enum mbci_motor_mode mode);

    /**
     * @brief 设置为制动状态(下桥全开)。在下一次设置输出后状态解除。
     */
    void (*brake)(struct mbci_motor *self);

    /**
     * @brief 私有数据，供驱动开发者使用。
     *
     */
    void *priv;
};

#define mbci_motor_init(motor) (motor)->init(motor)
#define mbci_motor_set_output(motor, value) (motor)->set_output(motor, value)
#define mbci_motor_set_mode(motor, mode) (motor)->set_mode(motor, mode)
#define mbci_motor_brake(motor) (motor)->brake(motor)

#endif
