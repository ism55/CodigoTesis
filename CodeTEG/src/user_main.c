
#include <header.h>

// RUTINA DE INICIO AL PRESIONAR UN BOTON
//F1 00 C0 F2 0B C0 F3 F4 40 F4 0E CC F5 0E CC F6 0E CC F1 00 00 F2 18 40 F3 DE 00 F4 16 32 F5 16 32 F6 16 32 F0 01 F4

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


/*Funcion de respuesta ante recepción de información*/
void ICACHE_FLASH_ATTR
server_recv(void *arg, char *pdata, unsigned short len)
{

struct espconn *pespconn = (struct espconn *)arg;

int cmd00=os_strncmp(pdata,"GET / HTTP/1.1",strlen("GET / HTTP/1.1")),
    cmd1=os_strncmp(pdata,"GET /?num1",strlen("GET /?num1")),
    cmd2=os_strncmp(pdata,"GET /?num2",strlen("GET /?num2")),
    cmd3=os_strncmp(pdata,"GET /?num3",strlen("GET /?num3")),
    cmd4=os_strncmp(pdata,"GET /?num4",strlen("GET /?num4")),
    cmd5=os_strncmp(pdata,"GET /?num5",strlen("GET /?num5")),
    cmd6=os_strncmp(pdata,"GET /?num6",strlen("GET /?num6")),

    cmd7=os_strncmp(pdata,"GET /?gripon",strlen("GET /?gripon")),
    cmd8=os_strncmp(pdata,"GET /?gripoff",strlen("GET /?gripoff")),

// int cmd9=os_strncmp(pdata,"GET /?ssid",strlen("GET /?ssid"));
// int cmd10=os_strncmp(pdata,"GET /?password",strlen("GET /?password"));

    cmd11=os_strncmp(pdata,"GET /?Kp1",strlen("GET /?Kp1")),
    cmd12=os_strncmp(pdata,"GET /?Ki1",strlen("GET /?Ki1")),
    cmd13=os_strncmp(pdata,"GET /?Kd1",strlen("GET /?Kd1")),

    cmd14=os_strncmp(pdata,"GET /?Kp2",strlen("GET /?Kp2")),
    cmd15=os_strncmp(pdata,"GET /?Ki2",strlen("GET /?Ki2")),
    cmd16=os_strncmp(pdata,"GET /?Kd2",strlen("GET /?Kd2")),

    cmd17=os_strncmp(pdata,"GET /?Kp3",strlen("GET /?Kp3")),
    cmd18=os_strncmp(pdata,"GET /?Ki3",strlen("GET /?Ki3")),
    cmd19=os_strncmp(pdata,"GET /?Kd3",strlen("GET /?Kd3")),

    cmd20=os_strncmp(pdata,"GET /?Kpro1",strlen("GET /?Kpro1")),
    cmd21=os_strncmp(pdata,"GET /?Koffset1",strlen("GET /?Koffset1")),

    cmd22=os_strncmp(pdata,"GET /?Kpro2",strlen("GET /?Kpro2")),
    cmd23=os_strncmp(pdata,"GET /?Koffset2",strlen("GET /?Koffset2")),

    cmd24=os_strncmp(pdata,"GET /?Kpro3",strlen("GET /?Kpro3")),
    cmd25=os_strncmp(pdata,"GET /?Koffset3",strlen("GET /?Koffset3")),

    cmd26=os_strncmp(pdata,"GET /?puente1=ON",strlen("GET /?puente1=ON")),
    cmd27=os_strncmp(pdata,"GET /?puente1=OFF",strlen("GET /?puente1=OFF")),

    cmd28=os_strncmp(pdata,"GET /?puente2=ON",strlen("GET /?puente2=ON")),
    cmd29=os_strncmp(pdata,"GET /?puente2=OFF",strlen("GET /?puente2=OFF")),

    cmd30=os_strncmp(pdata,"GET /?puente3=ON",strlen("GET /?puente3=ON")),
    cmd31=os_strncmp(pdata,"GET /?puente3=OFF",strlen("GET /?puente3=OFF"));

// os_strncpy(cadena,pdata,16);
// cadena[16]='\0';
// os_printf("\r\n%s",cadena);

if(cmd00==0){
  espconn_sent((struct espconn *)arg,(uint8 *)pagina2,strlen(pagina2));
  uint8 4inicio[]={0xF1,0x00,0xC0,0xF2,0x0B,0xC0,0xF3,0xF4,0x40,0xF4,0x0E,0xCC,0xF5,0x0E,0xCC,0xF6,0x0E,0xCC,0xF1,0x00,0x00,0xF2,0x18,0x40,0xF3,0xDE,0x00,0xF4,0x16,0x32,0xF5,0x16,0x32,0xF6,0x16,0x32,0xF0,0x01,0xF4};   //SE GENERA LA TRAMA
  uart0_tx_buffer(inicio,sizeof(inicio));   //SE TRANSMITE LA TRAMA POR UART
  espconn_disconnect(pespconn);
}

if (cmd1==0){     //VERIFICA SI SE RECIBIO UNA INSTRUCCION PARA EL MOTOR 1

  mover_motor(MOTOR_1, pdata, kpro1, koffset1);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
}

if(cmd2==0){
  mover_motor(MOTOR_2, pdata, kpro2, koffset2);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
}

if(cmd3==0){

  mover_motor(MOTOR_3, pdata, kpro3, koffset3);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
}

if(cmd4==0){

  mover_motor(MOTOR_4, pdata,0.035,-5682);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);

  //numero2=(numero2/0.035)+5682;

}

if(cmd5==0){
  mover_motor(MOTOR_5, pdata,0.035,-5682);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
}

if(cmd6==0){

  mover_motor(MOTOR_6, pdata,0.035,-5682);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
}

if(cmd7==0){

  uint8 msg2[]={PINZA,0x00,0x04};    //ACTIVAR LA PINZA
  uart0_tx_buffer(msg2,sizeof(msg2));
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if(cmd8==0){

  uint8 msg2[]={PINZA,0x00,0x05};    //DESACTIVAR LA PINZA
  uart0_tx_buffer(msg2,sizeof(msg2));
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
}
/*
if(cmd9==0){
  char word1[20];
  os_strncpy(cadena,pdata,16);
  cadena[16]='\0';
  char *token=strtok((char *)cadena," =");
  os_printf("%s\r\n",token);
  token=strtok(NULL," =");
  token=strtok(NULL," =");
  os_printf("%s\r\n",token);
  strcpy(word1,token);
  strcpy(sta_ssid,word1);
}

if(cmd10==0){
  char word1[20];
  os_strncpy(cadena,pdata,16);
  cadena[16]='\0';
  char *token=strtok((char *)cadena," =");
  os_printf("%s\r\n",token);
  token=strtok(NULL," =");
  token=strtok(NULL," =");
  os_printf("%s\r\n",token);
  strcpy(word1,token);
  strcpy(sta_pass,word1);

  //ap_config_func();


  //
  // wifi_station_get_config(&station_cfg);  //DECLARA LA ESTRUCTURA station_cfg PARA CONFIGURAR EL MODO STATION
  // //Nombre y contraseña del router que se conectara
  // os_strcpy((char *)station_cfg.ssid,(const char *)sta_ssid); //NOMBRE DEL ROUTER A CONECTAR
  // os_strcpy((char *)station_cfg.password,(const char *)sta_pass); //CLAVE DEL ROUTER A CONECTAR
  // wifi_station_set_config(&station_cfg);  //CONFIGURADO EL MODO STATION


}*/



if(cmd11==0){
  parametro_pid(KP_1,pdata);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd12==0){
  parametro_pid(KI_1,pdata);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd13==0){
  parametro_pid(KD_1,pdata);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd14==0){
  parametro_pid(KP_2,pdata);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd15==0){
  parametro_pid(KI_2,pdata);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd16==0){
  parametro_pid(KD_2,pdata);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd17==0){
  parametro_pid(KP_3,pdata);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd18==0){
  parametro_pid(KI_3,pdata);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd19==0){
  parametro_pid(KD_3,pdata);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
}

if (cmd20==0){
  cambiar_constante(pdata, kpro1);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd21==0){
  cambiar_constante(pdata, koffset1);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd22==0){
  cambiar_constante(pdata, kpro2);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd23==0){
  cambiar_constante(pdata, koffset2);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd24==0){
  cambiar_constante(pdata, kpro3);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd25==0){
  cambiar_constante(pdata, koffset3);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
}


if (cmd26==0){
  puenteH(PUENTE_H,pdata,PH1_ON);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd27==0){
  puenteH(PUENTE_H,pdata,PH1_OFF);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd28==0){
  puenteH(PUENTE_H,pdata,PH2_ON);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd29==0){
  puenteH(PUENTE_H,pdata,PH2_OFF);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd30==0){
  puenteH(PUENTE_H,pdata,PH3_ON);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
} else if (cmd31==0){
  puenteH(PUENTE_H,pdata,PH3_OFF);
  espconn_sent((struct espconn *)arg,(uint8 *)respuesta1,strlen(respuesta1));
  espconn_disconnect(pespconn);
}

}





void ICACHE_FLASH_ATTR
user_init(void)
{
    gpio_init();
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

void parpadear(void *arg){
      os_timer_disarm(&p_timer);
}


/******************************************************************************
 * FunctionName : server_sent
 * Description  : Función de respuesta ante envío de información
 * Parameters   : arg -- estructura espconn
  * Returns      : none
*******************************************************************************/

void ICACHE_FLASH_ATTR
server_sent(void *arg)
{
  //      ENCENDER LED DE NOTIFICACION
//  os_printf("Envío exitoso! bandera=%d\r\n",cmd1_flag);
GPIO_OUTPUT_SET(D2, 1);
os_timer_disarm(&p_timer);
os_timer_setfn(&p_timer, (os_timer_func_t *)parpadear, NULL);
os_timer_arm(&p_timer, 100, 0);
GPIO_OUTPUT_SET(D2, 0);
}

/******************************************************************************
 * FunctionName : server_discon
 * Description  : Función de respuesta ante desconexión
 * Parameters   : arg -- estructura espconn
  * Returns      : none
*******************************************************************************/

void ICACHE_FLASH_ATTR
server_discon(void *arg)
{
    //    APAGAR LED DE NOTIFICACION
  os_printf("Desconectado! \r\n");
  init_tcp(8266);
  GPIO_OUTPUT_SET(D4, 1);
}


/******************************************************************************
 * FunctionName : server_listen
 * Description  : Función de respuesta ante un servidor creado exitosamente
 * Parameters   : arg -- estructura espconn
  * Returns      : none
*******************************************************************************/

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


/******************************************************************************
 * FunctionName : server_recon
 * Description  : Función de respuesta ante un error en la creación del servidor
 * Parameters   : arg -- estructura espconn
  * Returns      : none
*******************************************************************************/

void ICACHE_FLASH_ATTR
server_recon(void *arg, sint8 err)
{
  //        AQUI APLICA EL ERROR HTTP 404: NOT FOUND
//  os_printf("Error de conexión, código de error: %d\r\n", err);
  //os_printf("Error de conexión, código de error: %d\r\n", err);
}



/******************************************************************************
 * FunctionName : init_tcp
 * Description  : Funcion para configurar el servidor
 * Parameters   : Local_port -- puerto donde se creara el socket
  * Returns      : none
*******************************************************************************/

void init_tcp(uint32_t Local_port)
{
  user_tcp_espconn.proto.tcp = &user_tcp; //SELECCION DEL APUNTADOR A UTILIZAR, SEGUN LA ESTRUCTURA user_tcp_espconn
  user_tcp_espconn.type = ESPCONN_TCP;  //SELECCION DEL TIPO DE PROTOCOLO SEGUN LOS REGISTROS
  user_tcp_espconn.proto.tcp->local_port = Local_port;  //SELECCION DEL PUERTO PARA CONEXION DEL SERVIDOR

  /*Declaración de las funciones de respuesta ante
  la creación del servidor*/
  espconn_regist_connectcb(&user_tcp_espconn, server_listen);
  espconn_regist_reconcb(&user_tcp_espconn, server_recon);

  //Inicio del servidor
  espconn_accept(&user_tcp_espconn);
  espconn_regist_time(&user_tcp_espconn,7200,0);

  GPIO_OUTPUT_SET(D4, 0);
}

/******************************************************************************
 * FunctionName : ap_config_func
 * Description  : Funcion para configurar el WiFi
 * Parameters   : none
  * Returns      : none
*******************************************************************************/

void ap_config_func()
{

//Modo estación+punto de acceso
  wifi_set_opmode(STATIONAP_MODE); //MODO ESTACION + ACCES POINT
  wifi_softap_get_config(&config);  //DECLARA LA ESTRUCTURA config PARA CONFIGURAR EL MODO AP
  wifi_station_get_config(&station_cfg);  //DECLARA LA ESTRUCTURA station_cfg PARA CONFIGURAR EL MODO STATION


  station_cfg.bssid_set=1;

//Nombre y contraseña del router que se conectara
  os_strcpy((char *)station_cfg.ssid,(const char *)sta_ssid); //NOMBRE DEL ROUTER A CONECTAR
  os_strcpy((char *)station_cfg.password,(const char *)sta_pass); //CLAVE DEL ROUTER A CONECTAR

  wifi_station_set_config(&station_cfg);  //CONFIGURADO EL MODO STATION

  os_memcpy(config.ssid, AP_SSID,strlen(AP_SSID));  //NOMBRE DEL WIFI SERVIDOR
  os_memcpy(config.password,AP_PASSWORD,strlen(AP_PASSWORD)); //CLAVE DEL WIFI SERVIDOR
  config.ssid_len = strlen(AP_SSID); //LONGITUD DE SSID
  config.authmode =  AUTH_WPA_WPA2_PSK;
  wifi_softap_set_config(&config);  //CONFIGURADO EL MODO AP
}


/******************************************************************************
 * FunctionName : gpio_init
 * Description  : Configura los pines de proposito general y UART
 * Parameters   : none
  * Returns      : none
*******************************************************************************/

void gpio_init(){
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
  gpio_output_set(D4,0, D4,0);

  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4 );
  gpio_output_set(D2,0, D2,0);

  //CONFIGURARCION DEL UART
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0TXD_U, FUNC_U0TXD);
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0RXD_U, FUNC_U0TXD);
  UART_SetStopBits(UART0, ONE_STOP_BIT);
  uart_init(BIT_RATE_115200, BIT_RATE_115200);


}



/******************************************************************************

INFORMACION DE LA TRAMA ENVIADA POR EL CLIENTE (BROWSER):

El cliente realiza un request via GET cuya cabecera contiene lo siguiente:

GET /?num1=XXX HTTP/1.1

En este mensaje el valor XXX debe ser aislado para ser procesado.
Esto se hace mediante la funcion strtok de la libreria string.h
Se colocaran como selectores de token, los caracteres " " y "="

1ra vez:
GET /?num1=XXX HTTP/1.1
  ^     token=GET
2da vez:
/?num1=XXX HTTP/1.1
     ^    token=/?num1

3ra vez:
XXX HTTP/1.1
  ^   token=XXX     y con esto ya se obtiene el valor de XXX.

*******************************************************************************/


/******************************************************************************
 * FunctionName : mover_motor
 * Description  : Mueve el motor indicado con el parametro comando
 * Parameters   : comando -- nombre del motor a mover
                  recibido -- string recibido en el request de la pagina
                  constante_grados -- constante de calibracion para convertir la informacion a un valor binario
                  constante_offset -- constante de calibracion para corregir el error de bits
 * Returns      : none
*******************************************************************************/

void mover_motor(int comando, char* recibido,float constante_grados,float constante_offset){

  char word1[20];   //VARIABLE AUXILIAR
  int numero;     //VARIABLE AUXILIAR PARA EL NUMERO RECIBIDO
  os_strncpy(cadena,recibido,16);  //COPIA EL REQUEST DEL CLIENTE EN LA VARIABLE AUXILIAR cadena
  cadena[16]='\0';    //SE COLOCA UN ELEMENTO NULO AL FINAL YA QUE LA INSTRUCCION STRNCPY NO LO COLOCA
  char *token=strtok((char *)cadena," =");  //SEPARA EL PRIMER ELEMENTO CON "=" o " "
  token=strtok(NULL," =");  //SEPARA EL SIGUIENTE ELEMENTO CON "=" o " "
  token=strtok(NULL," =");  //SEPARA EL SIGUIENTE ELEMENTO CON "=" o " "
  strcpy(word1,token);  //GUARDA LO OBTENIDO EN LA VARIABLE AUXILIAR word1
  int numero2=atoi(word1);  //CONVIERTE EL VALOR DE ASCII A ENTERO
  numero2=(numero2/constante_grados)-constante_offset; //SE DIVIDE ENTRE LA CONSTANTE 0.33 DEG/BITS PARA OBTENER 'BITS'
  numero2=numero2<<6; //INSTRUCCION BITWISE PARA ORDENAR LOS NUMERO Y GENERAR LA TRAMA
  int valorhigh=(numero2>>8); //VALOR HIGH
  int valorlow=(numero2); //VALOR LOW
  uint8 msg2[]={comando,valorhigh,valorlow};   //SE GENERA LA TRAMA
  uart0_tx_buffer(msg2,sizeof(msg2));   //SE TRANSMITE LA TRAMA POR UART
}


/******************************************************************************
 * FunctionName : cambiar_constante
 * Description  : Mueve el motor indicado con el parametro comando
 * Parameters   : recibido -- string recibido en el request de la pagina
                  constante_cambiada -- constante de calibracion cambiada
 * Returns      : none
*******************************************************************************/

void cambiar_constante(char* recibido,float constante_cambiada){

  char word1[20];   //VARIABLE AUXILIAR
  int numero;     //VARIABLE AUXILIAR PARA EL NUMERO RECIBIDO
  os_strncpy(cadena,recibido,16);  //COPIA EL REQUEST DEL CLIENTE EN LA VARIABLE AUXILIAR cadena
  cadena[16]='\0';    //SE COLOCA UN ELEMENTO NULO AL FINAL YA QUE LA INSTRUCCION STRNCPY NO LO COLOCA
  char *token=strtok((char *)cadena," =");  //SEPARA EL PRIMER ELEMENTO CON "=" o " "
  token=strtok(NULL," =");  //SEPARA EL SIGUIENTE ELEMENTO CON "=" o " "
  token=strtok(NULL," =");  //SEPARA EL SIGUIENTE ELEMENTO CON "=" o " "
  strcpy(word1,token);  //GUARDA LO OBTENIDO EN LA VARIABLE AUXILIAR word1
  int numero2=atoi(word1);  //CONVIERTE EL VALOR DE ASCII A ENTERO
  numero2=constante_cambiada; //SE CAMBIA EL VALOR DE LA constante_cambiada
}


/******************************************************************************
 * FunctionName : parametro_pid
 * Description  : Modifica el parametro del PID
 * Parameters   : comando -- parametro del PID a modificar
                  recibido -- string recibido en el request de la pagina
 * Returns      : none
*******************************************************************************/

void parametro_pid(int comando,char* recibido){

  char word1[20];   //VARIABLE AUXILIAR
  int numero;     //VARIABLE AUXILIAR PARA EL NUMERO RECIBIDO
  os_strncpy(cadena,recibido,16);  //COPIA EL REQUEST DEL CLIENTE EN LA VARIABLE AUXILIAR cadena
  cadena[16]='\0';    //SE COLOCA UN ELEMENTO NULO AL FINAL YA QUE LA INSTRUCCION STRNCPY NO LO COLOCA
  char *token=strtok((char *)cadena," =");  //SEPARA EL PRIMER ELEMENTO CON "=" o " "
  token=strtok(NULL," =");  //SEPARA EL SIGUIENTE ELEMENTO CON "=" o " "
  token=strtok(NULL," =");  //SEPARA EL SIGUIENTE ELEMENTO CON "=" o " "
  strcpy(word1,token);  //GUARDA LO OBTENIDO EN LA VARIABLE AUXILIAR word1
  int numero2=atoi(word1);  //CONVIERTE EL VALOR DE ASCII A ENTERO
  int valorhigh=(numero2>>8); //VALOR HIGH
  int valorlow=(numero2); //VALOR LOW
  uint8 msg2[]={comando,valorhigh,valorlow};   //SE GENERA LA TRAMA
  uart0_tx_buffer(msg2,sizeof(msg2));   //SE TRANSMITE LA TRAMA POR UART
}


/******************************************************************************
 * FunctionName : puenteH
 * Description  : Modifica el parametro del PID
 * Parameters   : comando -- parametro del PID a modificar
                  recibido -- string recibido en el request de la pagina
                  instruccion -- Indica el encendido o apagado
 * Returns      : none
*******************************************************************************/

void puenteH(int comando,char* recibido,int instruccion){

  uint8 msg2[]={comando,0x00,instruccion};   //SE GENERA LA TRAMA
  uart0_tx_buffer(msg2,sizeof(msg2));   //SE TRANSMITE LA TRAMA POR UART
}
