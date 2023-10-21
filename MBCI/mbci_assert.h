/**
 * @file mbci_assert.h
 * @author Evan Xiao (1993996310@qq.com)
 * @brief 断言相关的宏定义。
 * @version 0.1
 * @date 2023-10-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MBCI_ASSERT_H__
#define __MBCI_ASSERT_H__

#include <stdio.h>

#define MBCI_ASSERT_BANNER "Whoops! An assertion failed!\n"


#ifdef MBCI_ASSERT_ENABLE

/**
 * @brief 断言宏定义。如果条件为假，则输出错误信息并死机。
 *
 */
#define MBCI_ASSERT(cond)                                          \
    if (!(cond))                                                   \
    {                                                              \
        printf(MBCI_ASSERT_BANNER);                                \
        printf("Assertion failed at %s:%d\n", __FILE__, __LINE__); \
        while (1)                                                  \
            ;                                                      \
    }

/**
 * @brief 整数相等断言宏定义。如果两个整数不相等，则输出错误信息并死机。
 *
 */
#define MBCI_INT_EQ(a, b)                                          \
    if ((a) != (b))                                                \
    {                                                              \
        printf(MBCI_ASSERT_BANNER);                                \
        printf("Assertion failed at %s:%d\n", __FILE__, __LINE__); \
        printf("Expected %d, got %d\n", (a), (b));                 \
        while (1)                                                  \
            ;                                                      \
    }

#define MBCI_INT_BETWEEN(a, b, c)                                       \
    if ((a) < (b) || (a) > (c))                                         \
    {                                                                   \
        printf(MBCI_ASSERT_BANNER);                                     \
        printf("Assertion failed at %s:%d\n", __FILE__, __LINE__);      \
        printf("Expected %d to be between %d and %d\n", (a), (b), (c)); \
        while (1)                                                       \
            ;                                                           \
    }

/**
 * @brief 浮点数相等断言宏定义。如果两个浮点数在 1e-6 的精度下不相等，则输出错误信息并死机。
 *
 */
#define MBCI_FLOAT_EQ(a, b)                                        \
    if (fabs((a) - (b)) > 1e-6)                                    \
    {                                                              \
        printf(MBCI_ASSERT_BANNER);                                \
        printf("Assertion failed at %s:%d\n", __FILE__, __LINE__); \
        printf("Expected %f, got %f\n", (a), (b));                 \
        while (1)                                                  \
            ;                                                      \
    }

/**
 * @brief 浮点数在区间内断言宏定义。如果浮点数不在区间内，则输出错误信息并死机。
 *
 */
#define MBCI_FLOAT_BETWEEN(a, b, c)                                     \
    if ((a) < (b) || (a) > (c))                                         \
    {                                                                   \
        printf(MBCI_ASSERT_BANNER);                                     \
        printf("Assertion failed at %s:%d\n", __FILE__, __LINE__);      \
        printf("Expected %f to be between %f and %f\n", (a), (b), (c)); \
        while (1)                                                       \
            ;                                                           \
    }

#else

#define MBCI_ASSERT(cond)
#define MBCI_INT_EQ(a, b)
#define MBCI_INT_BETWEEN(a, b, c)
#define MBCI_FLOAT_EQ(a, b)
#define MBCI_FLOAT_BETWEEN(a, b, c)

#endif

#endif
