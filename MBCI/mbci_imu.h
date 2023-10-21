/**
 * @file mbci_imu.h
 * @author Evan Xiao (1993996310@qq.com)
 * @brief IMU设备的抽象。
 * @version 0.1
 * @date 2023-10-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MBCI_IMU_H__
#define __MBCI_IMU_H__

enum mbci_imu_axis
{
    MBCI_IMU_AXIS_X = 1,
    MBCI_IMU_AXIS_NX = -1,
    MBCI_IMU_AXIS_Y = 2,
    MBCI_IMU_AXIS_NY = -2,
    MBCI_IMU_AXIS_Z = 3,
    MBCI_IMU_AXIS_NZ = -3,
};

struct mbci_imu
{
    /**
     * @brief 初始化 IMU 设备。
     *
     */
    void (*init)(struct mbci_imu *self);
    /**
     * @brief 读取加速度计的数据。
     *
     * @param x 加速度计 X 轴的数据
     * @param y 加速度计 Y 轴的数据
     * @param z 加速度计 Z 轴的数据
     */
    void (*read_accel)(struct mbci_imu *self, float *x, float *y, float *z);

    /**
     * @brief 读取陀螺仪的数据。
     *
     * @param x 陀螺仪 X 轴的数据
     * @param y 陀螺仪 Y 轴的数据
     * @param z 陀螺仪 Z 轴的数据
     */
    void (*read_gyro)(struct mbci_imu *self, float *x, float *y, float *z);

    /**
     * @brief 读取磁力计的数据。仅在设备支持时可用。如果不支持此功能，请将此函数指针设置为 NULL。
     *
     * @param x 磁力计 X 轴的数据
     * @param y 磁力计 Y 轴的数据
     * @param z 磁力计 Z 轴的数据
     */
    void (*read_mag)(struct mbci_imu *self, float *x, float *y, float *z);

    /**
     * @brief 读取欧拉角的数据。仅在设备支持时可用。如果不支持此功能，请将此函数指针设置为 NULL。
     * @param pitch 欧拉角的俯仰角, 单位为度，范围为 -180~180
     * @param roll 欧拉角的横滚角, 单位为度，范围为 -180~180
     * @param yaw 欧拉角的偏航角, 单位为度，范围为 -180~180
     *
     */
    void (*read_euler)(struct mbci_imu *self, float *pitch, float *roll, float *yaw);

    /**
     * @brief 设置 IMU 设备的坐标轴映射。例如，如果 IMU 设备的 X 轴指向前方，Y 轴指向左方，Z 轴指向上方，则应该调用此函数设置为 MBCI_IMU_AXIS_X, MBCI_IMU_AXIS_NY, MBCI_IMU_AXIS_NZ。
     *
     */
    void (*set_axis_map)(struct mbci_imu *self, enum mbci_imu_axis x, enum mbci_imu_axis y, enum mbci_imu_axis z);

    /**
     * @brief 私有数据，供驱动开发者使用。
     *
     */
    void *priv;
};

#define mbci_imu_init(self) ((self)->init(self))
#define mbci_imu_read_accel(self, x, y, z) ((self)->read_accel(self, x, y, z))
#define mbci_imu_read_gyro(self, x, y, z) ((self)->read_gyro(self, x, y, z))
#define mbci_imu_read_mag(self, x, y, z) ((self)->read_mag(self, x, y, z))
#define mbci_imu_read_euler(self, pitch, roll, yaw) ((self)->read_euler(self, pitch, roll, yaw))
#define mbci_imu_set_axis_map(self, x, y, z) ((self)->set_axis_map(self, x, y, z))

#define mbci_imu_is_supported_mag(self) ((self)->read_mag != NULL)
#define mbci_imu_is_supported_euler(self) ((self)->read_euler != NULL)

#endif // __MBCI_IMU_H__
