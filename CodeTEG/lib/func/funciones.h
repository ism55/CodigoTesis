#include "stdlib.h"
#include "stdio.h"
#include "osapi.h"
#include "user_interface.h"
#include "driver/uart.h"
#include "ets_sys.h"
#include "c_types.h"
#include "espconn.h"
#include "mem.h"
#include "gpio.h"
#include "eagle_soc.h"




/******************************************************************************
 * FunctionName : server_recv
 * Description  : Función de respuesta ante recepción de información
 * Parameters   : arg -- estructura espconn
                  pdata -- informacion recibida
                  len -- tamaño de información recibida
  * Returns      : none
*******************************************************************************/

void ICACHE_FLASH_ATTR
server_recv(void *arg, char *pdata, unsigned short len);


/******************************************************************************
 * FunctionName : server_sent
 * Description  : Función de respuesta ante envío de información
 * Parameters   : arg -- estructura espconn
  * Returns      : none
*******************************************************************************/

void ICACHE_FLASH_ATTR
server_sent(void *arg);

/******************************************************************************
 * FunctionName : server_discon
 * Description  : Función de respuesta ante desconexión
 * Parameters   : arg -- estructura espconn
  * Returns      : none
*******************************************************************************/

void ICACHE_FLASH_ATTR
server_discon(void *arg);


/******************************************************************************
 * FunctionName : server_listen
 * Description  : Función de respuesta ante un servidor creado exitosamente
 * Parameters   : arg -- estructura espconn
  * Returns      : none
*******************************************************************************/

void ICACHE_FLASH_ATTR
server_listen(void *arg);

/******************************************************************************
 * FunctionName : server_recon
 * Description  : Función de respuesta ante un error en la creación del servidor
 * Parameters   : arg -- estructura espconn
  * Returns      : none
*******************************************************************************/

void ICACHE_FLASH_ATTR
server_recon(void *arg, sint8 err);

/******************************************************************************
 * FunctionName : init_tcp
 * Description  : Funcion para configurar el servidor
 * Parameters   : Local_port -- puerto donde se creara el socket
  * Returns      : none
*******************************************************************************/

void init_tcp(uint32_t Local_port);

/******************************************************************************
 * FunctionName : ap_config_func
 * Description  : Funcion para configurar el WiFi
 * Parameters   : none
  * Returns      : none
*******************************************************************************/

void ap_config_func();


/******************************************************************************
 * FunctionName : gpio_init
 * Description  : Configura los pines de proposito general
 * Parameters   : none
  * Returns      : none
*******************************************************************************/

void gpio_init();

/******************************************************************************
 * FunctionName : mover_motor
 * Description  : Mueve el motor indicado con el parametro comando
 * Parameters   : comando -- nombre del motor a mover
                  recibido -- string recibido en el request de la pagina
                  constante_grados -- constante de calibracion para convertir la informacion a un valor binario
                  constante_offset -- constante de calibracion para corregir el error de bits
 * Returns      : none
*******************************************************************************/

void mover_motor(int comando, char* recibido,float constante_grados,float constante_offset);

/******************************************************************************
 * FunctionName : mover_motor_2
 * Description  : Mueve el motor indicado con el parametro comando
 * Parameters   : comando -- nombre del motor a mover
 * Returns      : none
*******************************************************************************/

void mover_motor_2(int comando, char* recibido);


/******************************************************************************
 * FunctionName : cambiar_constante
 * Description  : Mueve el motor indicado con el parametro comando
 * Parameters   : recibido -- string recibido en el request de la pagina
                  constante_cambiada -- constante de calibracion cambiada
 * Returns      : none
*******************************************************************************/

float cambiar_constante(char* recibido);


/******************************************************************************
 * FunctionName : parametro_pid
 * Description  : Modifica el parametro del PID
 * Parameters   : comando -- parametro del PID a modificar
                  recibido -- string recibido en el request de la pagina
 * Returns      : none
*******************************************************************************/

void parametro_pid(int comando,char* recibido);

/******************************************************************************
 * FunctionName : puenteH
 * Description  : Modifica el parametro del PID
 * Parameters   : comando -- parametro del PID a modificar
                  recibido -- string recibido en el request de la pagina
                  instruccion -- Indica el encendido o apagado
 * Returns      : none
*******************************************************************************/

void puenteH(int comando,char* recibido,int instruccion);


/******************************************************************************
 * FunctionName : myatof
 * Description  : Convierte de ascii a float
 * Parameters   : char -- string a convertir
 * Returns      : valor convertido a float
*******************************************************************************/

float myatof(char *p);
