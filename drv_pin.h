#ifndef	__DRV_PIN_H__
#define __DRV_PIN_H__

typedef enum
{
  PIN_MODE_INPUT      = 0x00,
  PIN_MODE_INPUT_PULLUP,
  PIN_MODE_INPUT_IRQ,
  PIN_MODE_INPUT_PULLUP_IRQ,
  PIN_MODE_OUT_OD,
  PIN_MODE_OUT,
}PIN_MODE;
typedef enum
{
  TRIGGER_FALLING_LOW = 0,
  TRIGGER_RISING,
  TRIGGER_FALLING,
  TRIGGER_RISING_FALLING,
}PIN_IRQ_MODE;

void pin_mode_set(unsigned char id,PIN_MODE type);
void pin_write(unsigned char id,unsigned char level);
unsigned char pin_read(unsigned char id);
void pin_irq_set(unsigned char id, PIN_IRQ_MODE type, unsigned char level);

#endif