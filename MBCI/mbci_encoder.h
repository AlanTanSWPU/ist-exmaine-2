/**
 * @file mbci_encoder.h
 * @author Evan Xiao (1993996310@qq.com)
 * @brief 编码器设备的抽象。
 * @version 0.1
 * @date 2023-10-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __MBCI_ENCODER_H__
#define __MBCI_ENCODER_H__

struct mbci_encoder
{
    /**
     * @brief 初始化编码器设备。
     *
     */
    void (*init)(struct mbci_encoder *self);
    /**
     * @brief 读取编码器的计数值。
     *
     */
    signed long long (*read)(struct mbci_encoder *self);

    /**
     * @brief 重置编码器的计数值。
     *
     */
    void (*reset)(struct mbci_encoder *self);

    /**
     * @brief 私有数据，供驱动开发者使用。
     *
     */
    void *priv;
};

#define mbci_encoder_init(encoder) ((encoder)->init())
#define mbci_encoder_read(encoder) ((encoder)->read())
#define mbci_encoder_reset(encoder) ((encoder)->reset())

#endif
