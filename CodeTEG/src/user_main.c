
#include <header.h>
#include "funciones.h"

uint32 ICACHE_FLASH_ATTR
user_rf_cal_sector_set(void)
{
    enum flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;
    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 5;
            break;
        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;
        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;
        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;
        case FLASH_SIZE_64M_MAP_1024_1024:
            rf_cal_sec = 2048 - 5;
            break;
        case FLASH_SIZE_128M_MAP_1024_1024:
            rf_cal_sec = 4096 - 5;
            break;
        default:
            rf_cal_sec = 0;
            break;
    }
    return rf_cal_sec;
}

void ICACHE_FLASH_ATTR
user_rf_pre_init(void)
{
}


void ICACHE_FLASH_ATTR
user_init(void)
{

    system_set_os_print(0);
    gpio_init();
    GPIO_OUTPUT_SET(D4, 0);
//Llamada de función para la configuración del servidor
    ap_config_func();
/*Inicio del protocolo de comunicación por tcp
el argumento de la función es el puerto por el que se transmitirá
la información*/
    init_tcp(8266);
}



/////////////////////////////////////////////////////////////////////////


/*////Convertir char a uint8
  int l = strlen(word1) + 1;
  uint8_t msg2[l];
  size_t i = 0;
  const char* beg = word1;
  const char* end = word1 + l;
  for (; beg != end; ++beg, ++i) {
    msg2[i] = (uint8_t)(*beg);
   }
  //uart0_tx_buffer(msg2,sizeof(msg2));
*/

//////////////////////////////////////////////////////////////////////////

//void parpadear(void *arg){
//  GPIO_OUTPUT_SET(D2, 0);
//  os_timer_disarm(&p_timer);
//}
