#ifndef __SWM500_FLASH_H__
#define __SWM500_FLASH_H__


uint32_t FLASH_Erase(void);
uint32_t FLASH_Write(uint32_t addr, uint32_t data[], uint32_t count);
uint32_t FLASH_Read(uint32_t addr, uint32_t data[], uint32_t count);


#endif //__SWM500_H__
