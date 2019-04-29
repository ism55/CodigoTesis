
//#include "os_type.h"

//#include "user_iot_version.h"
//#include "user_json.h"
//#include "user_webserver.h"
//#include "upgrade.h"

#include <header.h>
//int MyAtoi(uint8_t *str);


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

/*
int MyAtoi(uint8_t *str){
  int res=0;
  int sign=1;
  int i=0;



  if (str[0]=='-'){
    sign=-1;
    i++;
  }

  for(; str[i]!='\0';i++){
    res=res*10+str[i]-'0';
  }
  return sign*res;
}
*/

/*Funcion de respuesta ante recepción de información
incluye mostrar por uart lo recibido y devolver un
mensaje de acuse que notifique que la información
llegó correctamente*/
void ICACHE_FLASH_ATTR
server_recv(void *arg, char *pdata, unsigned short len)
{
int cmd1=os_strncmp(pdata,"GET /?pin=ON1",strlen("GET /?pin=ON1"));
int cmd2=os_strncmp(pdata,"GET /?pin=OFF1",strlen("GET /?pin=OFF1"));
int cmd3=os_strncmp(pdata,"GET /?inicio1",strlen("GET /?inicio1"));
int cmd4=os_strncmp(pdata,"GET /?inicio2",strlen("GET /?inicio2"));
int cmd5=os_strncmp(pdata,"GET /?num1",strlen("GET /?num1"));


/*
os_strncpy(cadena,pdata,16);
cadena[16]='\0';
os_printf(cadena);
*/
if (cmd1==0){
  os_printf("LED ENCENDIDO!!!\r\n");
//cmd1_flag=1;

GPIO_OUTPUT_SET(GPIO_ID_PIN(2), 0);
//uart0_sendStr("LED ENCENDIDO!!!\r\n");
}

if(cmd2==0){
  os_printf("LED APAGADO!!!\r\n");
//  cmd1_flag=0;
GPIO_OUTPUT_SET(GPIO_ID_PIN(2), 1);
//uart0_sendStr("LED APAGADO!!!\r\n");
}

if(cmd3==0){
//  cmd1_flag=0;
//uart0_sendStr("\xf1\x01\xc0\xf2\x0b\xc0\xf3\xf4\x40\xf4\x0e\xcc\xf5\x0e\xcc\xf6\x0e\xcc");
uart0_tx_buffer(inicio11,sizeof(inicio11));
}

if(cmd4==0){
//  cmd1_flag=0;
//uart0_sendStr("\xf1\x01\x01\xf2\x18\x40\xf3\xde\x01\xf4\x16\x32\xf5\x16\x32\xf6\x16\x32");
uart0_tx_buffer(inicio111,sizeof(inicio111));
}



if(cmd5==0){
  char word1[20];
  int numero;
  //char *pointer;
  os_strncpy(cadena,pdata,16);
  cadena[16]='\0';
  char *token=strtok((char *)cadena," =");
  token=strtok(NULL," =");
  token=strtok(NULL," =");
  strcpy(word1,token);

/*
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



  //numero=MyAtoi(msg2);
  int numero2=atoi(word1);
//  numero2=numero2/0.33;
//  numero2=numero2<<6;
  int valorhigh=(numero2>>8);
  int valorlow=(numero2);
  uint8 msg2[]={0xF1,valorhigh,valorlow};

  //msg2[2]=numero2;

  uart0_tx_buffer(msg2,sizeof(msg2));

  os_printf("USANDO ATOI: %d\r\n",numero2);

}


//const char *pagina="HTTP/1.1 200 OK\r\n\r\n<!DOCTYPE html><html><head><title>TESIS</title></head><body><div><div><input></div><button>Buscar</button><p>LED: <a href=\x5c?pin=ON1\x5c><button>ON</button></a><a href=\x5c?pin=OFF1><button>OFF</button></a></p></div></body></html>";

  espconn_sent((struct espconn *)arg,(uint8 *)pagina2,strlen(pagina2));
  //espconn_sent((struct espconn *) arg, "Informacion recibida\r\n", strlen("Información recibida\r\n"));
}

//Función de respuesta ante envío de información
void ICACHE_FLASH_ATTR
server_sent(void *arg)
{
//  os_printf("Envío exitoso! bandera=%d\r\n",cmd1_flag);
}

//Función de respuesta ante desconexión
void ICACHE_FLASH_ATTR
server_discon(void *arg)
{
//  os_printf("Desconectado! \r\n");
}


/*Función de respuesta ante un servidor
creado exitosamente*/
void ICACHE_FLASH_ATTR
server_listen(void *arg)
{
  struct espconn *pespconn = (struct espconn *)arg;
/*Declaración de las funciones de respuesta ante
transmisión y recepción de información*/
  espconn_regist_recvcb(pespconn, server_recv);
  espconn_regist_sentcb(pespconn, server_sent);
  espconn_regist_disconcb(pespconn, server_discon);
}



/*Función de respuesta ante un error en la
creación del servidor*/
void ICACHE_FLASH_ATTR
server_recon(void *arg, sint8 err)
{
//  os_printf("Error de conexión, código de error: %d\r\n", err);
  //os_printf("Error de conexión, código de error: %d\r\n", err);
}



/*Función de  configuración para la creación
del servidor*/
void init_tcp(uint32_t Local_port)
{
  user_tcp_espconn.proto.tcp = &user_tcp;
  user_tcp_espconn.type = ESPCONN_TCP;
  user_tcp_espconn.proto.tcp->local_port = Local_port;

  /*Declaración de las funciones de respuesta ante
  la creación del servidor*/
  espconn_regist_connectcb(&user_tcp_espconn, server_listen);
  espconn_regist_reconcb(&user_tcp_espconn, server_recon);

  //Inicio del servidor
  espconn_accept(&user_tcp_espconn);
}




//Función para configurar el WIFI
void ap_config_func()
{


//Modo estación+punto de acceso
  wifi_set_opmode(STATIONAP_MODE);
  wifi_softap_get_config(&config);
  wifi_station_get_config(&station_cfg);


//  station_cfg.bssid_set=1;

//Nombre y contraseña de servidor que se creará
  os_strcpy((char *)station_cfg.ssid,(const char *)sta_ssid);
  os_strcpy((char *)station_cfg.password,(const char *)sta_pass);

//  os_memcpy(station_cfg.ssid,"",strlen(""));
//  os_memcpy(station_cfg.password,"",strlen(""));
  wifi_station_set_config(&station_cfg);

  os_memcpy(config.ssid, "esp8266_WiFi",strlen("esp8266_WiFi"));
  os_memcpy(config.password,"esp123",strlen("esp123"));
  config.ssid_len = strlen("esp8266_WiFi");
  wifi_softap_set_config(&config);
}


void gpio_init(){
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
gpio_output_set(GPIO_ID_PIN(2),0, GPIO_ID_PIN(2),0);

}


void ICACHE_FLASH_ATTR
user_init(void)
{
    uart_init(BIT_RATE_115200, BIT_RATE_115200);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0TXD_U, FUNC_U0TXD);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0RXD_U, FUNC_U0TXD);
    UART_SetStopBits(UART0, ONE_STOP_BIT);


    gpio_init();

//    os_printf("SDK version:%s\n", system_get_sdk_version());

//Llamada de función para la configuración del servidor
    ap_config_func();
/*Inicio del protocolo de comuicación por tcp
el argumento de la función es el puerto por el que se transmitirá
la información*/
    init_tcp(8266);



}
