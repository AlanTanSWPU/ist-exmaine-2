/**
 * @file cw32f030_ram.h
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-05-14
 *
 * @copyright Copyright (c) 2021
 *
 */

/*******************************************************************************
*
* 代码许可和免责信息
* 武汉芯源半导体有限公司授予您使用所有编程代码示例的非专属的版权许可，您可以由此
* 生成根据您的特定需要而定制的相似功能。根据不能被排除的任何法定保证，武汉芯源半
* 导体有限公司及其程序开发商和供应商对程序或技术支持（如果有）不提供任何明示或暗
* 含的保证或条件，包括但不限于暗含的有关适销性、适用于某种特定用途和非侵权的保证
* 或条件。
* 无论何种情形，武汉芯源半导体有限公司及其程序开发商或供应商均不对下列各项负责，
* 即使被告知其发生的可能性时，也是如此：数据的丢失或损坏；直接的、特别的、附带的
* 或间接的损害，或任何后果性经济损害；或利润、业务、收入、商誉或预期可节省金额的
* 损失。
* 某些司法辖区不允许对直接的、附带的或后果性的损害有任何的排除或限制，因此某些或
* 全部上述排除或限制可能并不适用于您。
*
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CW32F03x_RAM_H__
#define __CW32F03x_RAM_H__

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "base_types.h"
#include "cw32f030.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define')                           */
/*****************************************************************************/
//============================================================

/** @defgroup 中断标志位
  * @{
  */
#define RAM_IT_PARITY                           (bv1)
#define IS_RAM_IT(IT)                           (((IT) & 0xFFFFFFFD == 0x0UL) && ((IT) != 0x0UL))
#define IS_RAM_GET_IT(IT)                       ((IT) == RAM_IT_PARITY)

//============================================================

//RAM PARITY中断使能配置
void RAM_ITConfig(uint32_t RAM_IT, FunctionalState NewState);
//获取RAM PARITY中断标志位
ITStatus RAM_GetITStatus(uint32_t RAM_IT);
//清除RAM PARITY断标志位
void RAM_ClearITPendingBit(uint32_t RAM_IT);
//获取发生奇偶校验错的RAM地址//
uint32_t RAM_GetErrorAddress(void);

//============================================================

#ifdef __cplusplus
}
#endif

#endif
