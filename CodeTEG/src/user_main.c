
//#include "os_type.h"

//#include "user_iot_version.h"
//#include "user_json.h"
//#include "user_webserver.h"
//#include "upgrade.h"
#include "stdlib.h"


#include "osapi.h"
#include "user_interface.h"
#include "driver/uart.h"
#include "ets_sys.h"
#include "c_types.h"
#include "espconn.h"
#include "mem.h"
#include "gpio.h"
#include "eagle_soc.h"

int MyAtoi(uint8_t *str);

LOCAL struct espconn user_tcp_espconn;
LOCAL struct _esp_tcp user_tcp;

//int cmd1_flag,cmd2_flag;
const char *inicio1="\xf1\x00\xc0\xf2\x0b\xc0\xf3\xf4\x40\xf4\x0e\xcc\xf5\x0e\xcc\xf6\x0e\xcc";

uint8 inicio11[18]={241,0,192,242,11,192,243,244,64,244,15,204,245,15,204,246,14,204};
uint8 inicio111[]={0xF1,0x00,0xC0,0xF2,0x0B,0xC0,0xF3,0xF4,0x40,0xF4,0x0E,0xCC,0xF5,0x0E,0xCC,0xF6,0x0E,0xCC};
const char *inicio2="\xf1\x00\x00\xf2\x18\x40\xf3\xde\x00\xf4\x16\x32\xf5\x16\x32\xf6\x16\x32";
//char *buff;
char cadena[20];
//char *puntero;
uint8 inicio22[18]={241,0,0,242,24,64,243,222,0,244,22,50,245,22,50,246,22,50};



const char *pagina2=
"HTTP/1.1 200 OK\r\n\r\n"
"<!DOCTYPE html>"
"<html>"
"<head>"
"<title>TEG</title>"
"<style>"
"\n*{\nmargin: 0;\npadding: 0;\n}"
"\n#Superior{"
"\nbackground-color: #E6E6E6;"
"\n}"
"\n#Pagina{"
"\nmargin: 0 auto;"
"\nborder: 1px solid #9900CC;"
"\nheight: 85\x25;"
"\n}"
"\n#ncabezado{"
"height: 50px;"
"\nbackground-color: #FF3300;"
"\n}"
"\n#LaIzquierda{"
"\nwidth: 20\x25;"
"\nheight: 500px;"
"\nfloat: left;"
"\nbackground-color: #0066FF;"
"\n}"
"\n#Principal{"
"\nwidth: 60\x25;"
"\nfloat: left;"
"\nbackground-color: #FFFFFF;"
"\n}"
"\n#LaDerecha{"
"\nwidth: 20\x25;"
"\nheight: 500px;"
"\nfloat: right;"
"\nbackground-color: #006600;"
"\n}"
"\n#piePagina{"
"\nclear: both;"
"\nheight: 25px;"
"\nbackground-color: #CC6699;"
"\n}"
"\n</style>"
"\n<script>"
//"\nfunction myFunction() {"
//"\nvar slider = document.getElementById(\x22slider\x22);"
//"\nvar a = 0;"
//"\nsetInterval(function() {"
                          //"\na = slider.value;"
                          //"\nispDiv.innerHTML = \x22Valor= \x22 + a;"
                          //"\n//get(\x22 192.168.4.1:8266/\x22+a);"
                          //"\n}, 270)"
//"\n}"
/*
"\nvar slider = document.getElementById(\x22servoSlider\x22);"
   "\nvar servoP = document.getElementById(\x22servoPos\x22);"


   "\nservoP.innerHTML = slider.value;"
   "\nslider.oninput = function() {"
     "\nslider.value = this.value;"
     "\nservoP.innerHTML = this.value;"
   "\n}"*/
   "\n$.ajaxSetup({timeout:3600000});"
//"setInterval(servo,100);"
   "\nfunction mover(pos,nombre) {"
     "\n$.get(\x22?\x22+nombre+\x22=\x22 + pos);"
     "\nsetTimeout(function(){$.get(\x22?\x22+nombre+\x22=\x22 + pos);},10);"
     "\n{Connection: close};"
   "\n}"

"</script>"
 "<script src=\x22https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\x22></script>"
"</head>"
"<body>"
"<div id=\x22Superior\x22>"
"<h1>TRABAJO ESPECIAL DE GRADO</h1>"
"</div>"
"<div id=\x22Pagina\x22>"
"<header id=\x22ncabezado\x22>"
"<p>#ncabezado</p>"
"</header>"
"<aside id=\x22LaIzquierda\x22><p>#LaIzquierda</p></aside>"
"<section id=\x22Principal\x22>"
"<p>#Principal</p>\n<p>LED:"
"<a href=\x22?pin=ON1\x22><button>ON</button></a>"
"<a href=\x22?pin=OFF1\x22><button>OFF</button></a>"
"<a href=\x22?inicio1\x22><button>INICIAR1</button></a>"
"<a href=\x22?inicio2\x22><button>INICIAR2</button></a></p>"
"<form onsubmit=\x22return false\x22>\n"
"<input type=\x22number\x22 name=\x22num\x22>"
"<input type=\x22submit\x22 value=\x22subir\x22>"
"</form>"
"<form onsubmit=\x22return false\x22>\n"
"<input type=\x22number\x22 name=\x22xF1\x22 >"
"<input type=\x22submit\x22 value=\x22xF1\x22 onclick=\x22this.form.num1.value=this.form.xF1.value; mover(this.form.num1.value,this.form.xF1.name)\x22>"
"<input type=\x22range\x22 name=\x22num1\x22 min=\x22-135\x22 max=\x22 135\x22 oninput=\x22mover(this.value,this.name)\x22 onchange=\x22mover(this.value,this.name)\x22 step=\x22 10\x22 id=\x22slider\x22>"
"</form>"
"<form >\n"
"<input type=\x22number\x22 name=\x22xF2\x22>"
"<input type=\x22submit\x22 value=\x22xF2\x22>"
"</form>"
"<form >\n"
"<input type=\x22number\x22 name=\x22xF3\x22>"
"<input type=\x22submit\x22 value=\x22xF3\x22>"
"</form>"
"<form >\n"
"<input type=\x22number\x22 name=\x22xF4\x22>"
"<input type=\x22submit\x22 value=\x22xF4\x22>"
"</form>"
"<form >\n"
"<input type=\x22number\x22 name=\x22xF5\x22>"
"<input type=\x22submit\x22 value=\x22xF5\x22>"
"</form>"
"<form >\n"
"<input type=\x22number\x22 name=\x22xF6\x22>"
"<input type=\x22submit\x22 value=\x22xF6\x22>"
"</form>"
//"<form method=\x22GET\x22>"
//"<input type=\x22range\x22 min=\x22-135\x22 max=\x22 135\x22 id=\x22servoSlider\x22 oninput=\x22servo(this.value)\x22 step=\x22 10\x22>"
//"<div id=\x22ispDiv\x22></div>"
//"</form>"
"</section>"
"<aside id=\x22LaDerecha\x22><p>#LaDerecha</p></aside>"
"<footer id=\x22piePagina\x22><p>#piePagina</p></footer>"
"</div>"
"</body>"
"</html>";

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
  struct softap_config config;
  struct station_config station_cfg;


//Modo estación+punto de acceso
  wifi_set_opmode(STATIONAP_MODE);
  wifi_softap_get_config(&config);
  wifi_station_get_config(&station_cfg);

const char * const sta_ssid="";
const char * const sta_pass="";

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
