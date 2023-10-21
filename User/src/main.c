#include "main.h"
#include "mbci_gpio.h"
 
int main(void)
{
	mbci_gpio_init("PC.22", MBCI_GPIO_OUT_PP);
	mbci_gpio_init("PB.11", MBCI_GPIO_OUT_PP);
	mbci_gpio_init("PA.01", MBCI_GPIO_IN_PULL_UP);
	
	mbci_gpio_set("PC.13",0);
	
    while (1)
    {
       if(mbci_gpio_get("PA.01")== 0 ) mbci_gpio_set("PB.11",0);
	   else mbci_gpio_set("PB.11",1);
    }
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
