/**
 * @file drv_pin.c
 * @author zrw
 * @brief gpio通用io口驱动程序，可直接通过引脚号进行控制，如pin_write(3,1);即让PA2输出高电平，pin_read(3);即为读取PA2电平，需先使用pin_mode_set函数初始化。
 * @version 0.1
 * @date 2019-04-11
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "HeaderInclude.h"
#define PIN_NUM     64
static unsigned char pin_map[] =
{
    (1 << 4) + 0, (1 << 4) + 1, (1 << 4) + 2, (1 << 4) + 3, (1 << 4) + 4, (1 << 4) + 5, (1 << 4) + 6, (1 << 4) + 7,
    (0 << 4) + 0, (0 << 4) + 0, (0 << 4) + 0, (0 << 4) + 0, (0 << 4) + 0, (7 << 4) + 0, (7 << 4) + 1, (7 << 4) + 2,
    (7 << 4) + 3, (0 << 4) + 0, (5 << 4) + 0, (5 << 4) + 1, (5 << 4) + 2, (5 << 4) + 3, (5 << 4) + 4, (5 << 4) + 5,
    (4 << 4) + 0, (4 << 4) + 1, (4 << 4) + 2, (4 << 4) + 3, (0 << 4) + 0, (0 << 4) + 0, (2 << 4) + 0, (2 << 4) + 1,
    (2 << 4) + 2, (2 << 4) + 3, (2 << 4) + 4, (2 << 4) + 5, (2 << 4) + 6, (2 << 4) + 7, (6 << 4) + 0, (6 << 4) + 1,
    (6 << 4) + 4, (6 << 4) + 5, (6 << 4) + 6, (6 << 4) + 7, (4 << 4) + 4, (4 << 4) + 5, (4 << 4) + 6, (4 << 4) + 7,
    (7 << 4) + 4, (7 << 4) + 5, (7 << 4) + 6, (7 << 4) + 7, (3 << 4) + 0, (3 << 4) + 1, (0 << 4) + 0, (0 << 4) + 0,
    (3 << 4) + 2, (3 << 4) + 3, (3 << 4) + 4, (3 << 4) + 5, (3 << 4) + 6, (3 << 4) + 7, (5 << 4) + 6, (5 << 4) + 7
};

void pin_mode_set(unsigned char id, PIN_MODE type)
{
    GPIO_Mode_TypeDef mode;
    GPIO_TypeDef *port;
    uint8_t pin;

    if (id > PIN_NUM)
    {
        return;
    }

    switch (type)
    {
    case PIN_MODE_INPUT:
        mode = GPIO_Mode_In_FL_No_IT;
        break;

    case PIN_MODE_INPUT_PULLUP:
        mode = GPIO_Mode_In_PU_No_IT;
        break;

    case PIN_MODE_INPUT_IRQ:
        mode = GPIO_Mode_In_FL_IT;
        break;

    case PIN_MODE_INPUT_PULLUP_IRQ:
        mode = GPIO_Mode_In_PU_IT;
        break;

    case PIN_MODE_OUT_OD:
        mode = GPIO_Mode_Out_OD_HiZ_Fast;
        break;

    case PIN_MODE_OUT:
        mode = GPIO_Mode_Out_PP_High_Fast;
        break;

    default:
        mode = GPIO_Mode_Out_PP_High_Fast;
        break;
    }

    switch (pin_map[id - 1] >> 4)
    {
    case 1:
        port = GPIOA;
        break;

    case 2:
        port = GPIOB;
        break;

    case 3:
        port = GPIOC;
        break;

    case 4:
        port = GPIOD;
        break;

    case 5:
        port = GPIOE;
        break;

    case 6:
        port = GPIOF;
        break;

    case 7:
        port = GPIOG;
        break;

    default:
        port = GPIOA;
        break;
    }
    pin = 1 << (pin_map[id - 1] & 0xf);
    GPIO_Init(port, pin, mode);
}
void pin_irq_set(unsigned char id, PIN_IRQ_MODE type, unsigned char level)
{
    unsigned char pin = (pin_map[id - 1] & 0xf);
    ITC_PriorityLevel_TypeDef prilevel;
    switch (level)
    {
    case 0:
        prilevel = ITC_PriorityLevel_0;
        break;
    case 1:
        prilevel = ITC_PriorityLevel_1;
        break;
    case 2:
        prilevel = ITC_PriorityLevel_2;
        break;
    case 3:
        prilevel = ITC_PriorityLevel_3;
        break;

    default:
        prilevel = ITC_PriorityLevel_3;
        break;
    }
    switch (pin)
    {
    case 0:
        EXTI_SetPinSensitivity(EXTI_Pin_0, (EXTI_Trigger_TypeDef)type);
        ITC_SetSoftwarePriority(EXTI0_IRQn, prilevel);
        break;
    case 1:
        EXTI_SetPinSensitivity(EXTI_Pin_1, (EXTI_Trigger_TypeDef)type);
        ITC_SetSoftwarePriority(EXTI1_IRQn, prilevel);
        break;
    case 2:
        EXTI_SetPinSensitivity(EXTI_Pin_2, (EXTI_Trigger_TypeDef)type);
        ITC_SetSoftwarePriority(EXTI2_IRQn, prilevel);
        break;
    case 3:
        EXTI_SetPinSensitivity(EXTI_Pin_3, (EXTI_Trigger_TypeDef)type);
        ITC_SetSoftwarePriority(EXTI3_IRQn, prilevel);
        break;
    case 4:
        EXTI_SetPinSensitivity(EXTI_Pin_4, (EXTI_Trigger_TypeDef)type);
        ITC_SetSoftwarePriority(EXTI4_IRQn, prilevel);
        break;
    case 5:
        EXTI_SetPinSensitivity(EXTI_Pin_5, (EXTI_Trigger_TypeDef)type);
        ITC_SetSoftwarePriority(EXTI5_IRQn, prilevel);
        break;
    case 6:
        EXTI_SetPinSensitivity(EXTI_Pin_6, (EXTI_Trigger_TypeDef)type);
        ITC_SetSoftwarePriority(EXTI6_IRQn, prilevel);
        break;
    case 7:
        EXTI_SetPinSensitivity(EXTI_Pin_7, (EXTI_Trigger_TypeDef)type);
        ITC_SetSoftwarePriority(EXTI7_IRQn, prilevel);
        break;

    default:
        break;
    }
    EXTI_SetPinSensitivity(EXTI_Pin_1, EXTI_Trigger_Falling);
    ITC_SetSoftwarePriority(EXTI1_IRQn, ITC_PriorityLevel_3);
}
void pin_write(unsigned char id, unsigned char level)
{
    GPIO_TypeDef *port;
    uint8_t pin;
    switch (pin_map[id - 1] >> 4)
    {
    case 1:
        port = GPIOA;
        break;

    case 2:
        port = GPIOB;
        break;

    case 3:
        port = GPIOC;
        break;

    case 4:
        port = GPIOD;
        break;

    case 5:
        port = GPIOE;
        break;

    case 6:
        port = GPIOF;
        break;

    case 7:
        port = GPIOG;
        break;

    default:
        port = GPIOA;
        break;
    }
    pin = 1 << (pin_map[id - 1] & 0xf);
    if (level == 0)
    {
        GPIO_ResetBits( port, pin );
    }
    else
    {
        GPIO_SetBits( port, pin );
    }
}
unsigned char pin_read(unsigned char id)
{
    GPIO_TypeDef *port;
    uint8_t pin;
    switch (pin_map[id - 1] >> 4)
    {
    case 1:
        port = GPIOA;
        break;

    case 2:
        port = GPIOB;
        break;

    case 3:
        port = GPIOC;
        break;

    case 4:
        port = GPIOD;
        break;

    case 5:
        port = GPIOE;
        break;

    case 6:
        port = GPIOF;
        break;

    case 7:
        port = GPIOG;
        break;

    default:
        port = GPIOA;
        break;
    }
    pin = 1 << (pin_map[id - 1] & 0xf);
    if (GPIO_ReadInputDataBit(port, (GPIO_Pin_TypeDef)pin) == RESET)
    {
        return 0;
    }
    else
    {
        return 1;
    }

}