#include <header.h>

 static os_timer_t ptimer;

 int esperar,repeticion;
 uint8 bandera=0;
 int counter=0;

 char buffercaja[100];

//       puntero[2];
//
//void xstrcat(char string1[],char string2[]);
char *xstrcat(char *dest, const char *src);
void retardo(void *arg);



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


/*Funcion de respuesta ante recepción de información
incluye mostrar por uart lo recibido y devolver un
mensaje de acuse que notifique que la información
llegó correctamente*/
void ICACHE_FLASH_ATTR
server_recv(void *arg, char *pdata, unsigned short len)
{
int cmd1=os_strncmp(pdata,"GET /?num1",strlen("GET /?num1"));
int cmd2=os_strncmp(pdata,"GET /?num2",strlen("GET /?num2"));
int cmd3=os_strncmp(pdata,"GET /?num3",strlen("GET /?num3"));
int cmd4=os_strncmp(pdata,"GET /?num4",strlen("GET /?num4"));
int cmd5=os_strncmp(pdata,"GET /?num5",strlen("GET /?num5"));
int cmd6=os_strncmp(pdata,"GET /?num6",strlen("GET /?num6"));

int cmd7=os_strncmp(pdata,"GET /?gripon",strlen("GET /?gripon"));
int cmd8=os_strncmp(pdata,"GET /?gripoff",strlen("GET /?gripoff"));

// int cmd9=os_strncmp(pdata,"GET /?ssid",strlen("GET /?ssid"));
// int cmd10=os_strncmp(pdata,"GET /?password",strlen("GET /?password"));

int cmd11=os_strncmp(pdata,"GET /?Kp1",strlen("GET /?Kp1"));
int cmd12=os_strncmp(pdata,"GET /?Ki1",strlen("GET /?Ki1"));
int cmd13=os_strncmp(pdata,"GET /?Kd1",strlen("GET /?Kd1"));

int cmd14=os_strncmp(pdata,"GET /?Kp2",strlen("GET /?Kp2"));
int cmd15=os_strncmp(pdata,"GET /?Ki2",strlen("GET /?Ki2"));
int cmd16=os_strncmp(pdata,"GET /?Kd2",strlen("GET /?Kd2"));

int cmd17=os_strncmp(pdata,"GET /?Kp3",strlen("GET /?Kp3"));
int cmd18=os_strncmp(pdata,"GET /?Ki3",strlen("GET /?Ki3"));
int cmd19=os_strncmp(pdata,"GET /?Kd3",strlen("GET /?Kd3"));

int cmd20=os_strncmp(pdata,"GET /?Kpro1",strlen("GET /?Kpro1"));
int cmd21=os_strncmp(pdata,"GET /?Koffset1",strlen("GET /?Koffset1"));

int cmd22=os_strncmp(pdata,"GET /?Kpro2",strlen("GET /?Kpro2"));
int cmd23=os_strncmp(pdata,"GET /?Koffset2",strlen("GET /?Koffset2"));

int cmd24=os_strncmp(pdata,"GET /?Kpro3",strlen("GET /?Kpro3"));
int cmd25=os_strncmp(pdata,"GET /?Koffset3",strlen("GET /?Koffset3"));

int cmd26=os_strncmp(pdata,"GET /?puente1=ON",strlen("GET /?puente1=ON"));
int cmd27=os_strncmp(pdata,"GET /?puente1=OFF",strlen("GET /?puente1=OFF"));

int cmd28=os_strncmp(pdata,"GET /?puente2=ON",strlen("GET /?puente2=ON"));
int cmd29=os_strncmp(pdata,"GET /?puente2=OFF",strlen("GET /?puente2=OFF"));

int cmd30=os_strncmp(pdata,"GET /?puente3=ON",strlen("GET /?puente3=ON"));
int cmd31=os_strncmp(pdata,"GET /?puente3=OFF",strlen("GET /?puente3=OFF"));

// int cmd32=os_strncmp(pdata,"GET /?caja",strlen("GET /?caja"));
// int cmd33=os_strncmp(pdata,"GET /?caja&inic",strlen("GET /?caja&inic"));

os_strncpy(cadena,pdata,16);
cadena[16]='\0';
os_printf("\r\n%s",cadena);


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

if (cmd1==0){     //VERIFICA SI SE RECIBIO UNA INSTRUCCION PARA EL MOTOR 1

  char word1[20];   //VARIABLE AUXILIAR
  int numero;     //VARIABLE AUXILIAR PARA EL NUMERO RECIBIDO
  os_strncpy(cadena,pdata,16);  //COPIA EL REQUEST DEL CLIENTE EN LA VARIABLE AUXILIAR cadena
  cadena[16]='\0';    //SE COLOCA UN ELEMENTO NULO AL FINAL YA QUE LA INSTRUCCION STRNCPY NO LO COLOCA
  char *token=strtok((char *)cadena," =");  //SEPARA EL PRIMER ELEMENTO CON "=" o " "
  token=strtok(NULL," =");  //SEPARA EL SIGUIENTE ELEMENTO CON "=" o " "
  token=strtok(NULL," =");  //SEPARA EL SIGUIENTE ELEMENTO CON "=" o " "
  strcpy(word1,token);  //GUARDA LO OBTENIDO EN LA VARIABLE AUXILIAR word1
  int numero2=atoi(word1);  //CONVIERTE EL VALOR DE ASCII A ENTERO
  numero2=numero2/constante_grados; //SE DIVIDE ENTRE LA CONSTANTE 0.33 DEG/BITS PARA OBTENER 'BITS'
  numero2=numero2<<6; //INSTRUCCION BITWISE PARA ORDENAR LOS NUMERO Y GENERAR LA TRAMA
  int valorhigh=(numero2>>8); //VALOR HIGH
  int valorlow=(numero2); //VALOR LOW
  uint8 msg2[]={0xF1,valorhigh,valorlow};   //SE GENERA LA TRAMA
  uart0_tx_buffer(msg2,sizeof(msg2));   //SE TRANSMITE LA TRAMA POR UART

}

if(cmd2==0){

  char word1[20];
  int numero;
  os_strncpy(cadena,pdata,16);
  cadena[16]='\0';
  char *token=strtok((char *)cadena," =");
  token=strtok(NULL," =");
  token=strtok(NULL," =");
  strcpy(word1,token);
  int numero2=atoi(word1);
  numero2=numero2/constante_grados;
  numero2=numero2<<6;
  int valorhigh=(numero2>>8);
  int valorlow=(numero2);
  uint8 msg2[]={0xF2,valorhigh,valorlow};
  uart0_tx_buffer(msg2,sizeof(msg2));

}

if(cmd3==0){

  char word1[20];
  int numero;
  os_strncpy(cadena,pdata,16);
  cadena[16]='\0';
  char *token=strtok((char *)cadena," =");
  token=strtok(NULL," =");
  token=strtok(NULL," =");
  strcpy(word1,token);
  int numero2=atoi(word1);
  numero2=numero2/constante_grados;
  numero2=numero2<<6;
  int valorhigh=(numero2>>8);
  int valorlow=(numero2);
  uint8 msg2[]={0xF3,valorhigh,valorlow};
  uart0_tx_buffer(msg2,sizeof(msg2));

}

if(cmd4==0){

  char word1[20];
  int numero;
  os_strncpy(cadena,pdata,16);
  cadena[16]='\0';
  char *token=strtok((char *)cadena," =");
  token=strtok(NULL," =");
  token=strtok(NULL," =");
  strcpy(word1,token);
  int numero2=atoi(word1);
  numero2=(numero2/0.035)+5682;
  int valorhigh=(numero2>>8);
  int valorlow=(numero2);
  uint8 msg2[]={0xF4,valorhigh,valorlow};
  uart0_tx_buffer(msg2,sizeof(msg2));

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



  //numero=MyAtoi(msg2);
  int numero2=atoi(word1);
  numero2=(numero2/0.035)+5682;
  int valorhigh=(numero2>>8);
  int valorlow=(numero2);
  uint8 msg2[]={0xF5,valorhigh,valorlow};

  //msg2[2]=numero2;

  uart0_tx_buffer(msg2,sizeof(msg2));

  //os_printf("USANDO ATOI: %d\r\n",numero2);

}

if(cmd6==0){

  char word1[20];
  int numero;
  os_strncpy(cadena,pdata,16);
  cadena[16]='\0';
  char *token=strtok((char *)cadena," =");
  token=strtok(NULL," =");
  token=strtok(NULL," =");
  strcpy(word1,token);
  int numero2=atoi(word1);
  numero2=(numero2/0.035)+5682;
  int valorhigh=(numero2>>8);
  int valorlow=(numero2);
  uint8 msg2[]={0xF6,valorhigh,valorlow};
  uart0_tx_buffer(msg2,sizeof(msg2));


}

if(cmd7==0){

  uint8 msg2[]={0xE0,0x00,0x04};    //ACTIVAR LA PINZA
  uart0_tx_buffer(msg2,sizeof(msg2));

} else if(cmd8==0){

  uint8 msg2[]={0xE0,0x00,0x05};    //DESACTIVAR LA PINZA
  uart0_tx_buffer(msg2,sizeof(msg2));

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
/*
if(cmd32==0){
  char word1[22];
  os_strncpy(cadena,pdata,22);
  cadena[22]='\0';
  char *token=strtok((char *)cadena," ");
  token=strtok(NULL,"&");
  token=strtok(NULL,"=");

    if(os_strncmp(token,"num1",strlen("num1"))==0){
      token=strtok(NULL," ");
      strcpy(word1,token);
      int numero2=atoi(word1);
      numero2=numero2/constante_grados;
      numero2=numero2<<6;
      int valorhigh=(numero2>>8);
      int valorlow=(numero2);
      char msg2[]={0xF1,valorhigh,valorlow};

      os_sprintf(buffercaja+strlen(buffercaja),msg2);
      //xstrcat(buffercaja,msg2);
      os_printf(buffercaja);

      //uart0_tx_buffer(msg2,sizeof(msg2));
    }

    if(os_strncmp(token,"num2",strlen("num2"))==0){
      token=strtok(NULL," ");
      strcpy(word1,token);
      int numero2=atoi(word1);
      numero2=numero2/constante_grados;
      numero2=numero2<<6;
      int valorhigh=(numero2>>8);
      int valorlow=(numero2);
      char msg2[]={0xF2,valorhigh,valorlow,0};

      //xstrcat(buffercaja,msg2);
      os_sprintf(buffercaja+strlen(buffercaja),msg2);
      //os_printf(buffercaja);
      //uart0_tx_buffer(msg2,sizeof(msg2));
    }



    if(os_strncmp(token,"num3",strlen("num3"))==0){
      token=strtok(NULL," ");
      strcpy(word1,token);
      int numero2=atoi(word1);
      numero2=numero2/constante_grados;
      numero2=numero2<<6;
      int valorhigh=(numero2>>8);
      int valorlow=(numero2);
      char msg2[]={0xF3,valorhigh,valorlow};

      //xstrcat(buffercaja,msg2);
      os_sprintf(buffercaja +strlen(buffercaja),msg2);
      //os_printf(buffercaja);
      //uart0_tx_buffer(msg2,sizeof(msg2));
    }

    if(os_strncmp(token,"wait",strlen("wait"))==0){
      token=strtok(NULL," ");
      strcpy(word1,token);
      int numero2=atoi(word1);
      esperar=numero2;

      //strcat(buffercaja,"w");

      char msg2[]={'w',esperar,0};

      //xstrcat(buffercaja,msg2);
      os_sprintf(buffercaja +strlen(buffercaja),msg2);
      //os_delay_us(numero2*1000);
      //os_printf(buffercaja);
    }

}

if(cmd33==0){

//for(int k;k<repeticion;k++){

  for(int i=0;i<strlen(buffercaja);i++){
    if(buffercaja[i]!='w'){
      // uart0_tx_buffer((uint8 *)(int)buffercaja[i],sizeof((uint8 *)(int)buffercaja[i]));
      //os_timer_disarm(&ptimer);
      //os_timer_setfn(&ptimer, (os_timer_func_t *)retardo, NULL);
      //os_timer_arm(&ptimer, 1000, 1);

      os_printf("%c",buffercaja[i]);
      //os_printf("Nada\r\n");

    }else if(buffercaja[i]=='w'){
      //bandera=1;
      i++;
      //os_timer_disarm(&ptimer);
      //os_timer_setfn(&ptimer, (os_timer_func_t *)retardo, NULL);

  //    os_timer_arm(&ptimer, 1000, 0);
      counter=0;
      while(counter<11);
      os_printf("\r\nUn segundo!\r\n");

      //os_timer_arm(&ptimer, 1000, 1);
    }
  }

//}

}*/


  espconn_sent((struct espconn *)arg,(uint8 *)pagina2,strlen(pagina2));
  //espconn_sent((struct espconn *) arg, "Informacion recibida\r\n", strlen("Información recibida\r\n"));
}

//Función de respuesta ante envío de información
void ICACHE_FLASH_ATTR
server_sent(void *arg)
{
  //      ENCENDER LED DE NOTIFICACION
//  os_printf("Envío exitoso! bandera=%d\r\n",cmd1_flag);
}

//Función de respuesta ante desconexión
void ICACHE_FLASH_ATTR
server_discon(void *arg)
{   //AQUI APLICA EL ERROR HTTP 500: INTERNAL SERVER ERROR
    //    APAGAR LED DE NOTIFICACION
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
  //        AQUI APLICA EL ERROR HTTP 404: NOT FOUND
//  os_printf("Error de conexión, código de error: %d\r\n", err);
  //os_printf("Error de conexión, código de error: %d\r\n", err);
}



/*Función de  configuración para la creación
del servidor*/
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
}




//Función para configurar el WIFI
void ap_config_func()
{


//Modo estación+punto de acceso
  wifi_set_opmode(SOFTAP_MODE); //MODO ESTACION + ACCES POINT
  wifi_softap_get_config(&config);  //DECLARA LA ESTRUCTURA config PARA CONFIGURAR EL MODO AP
/*  wifi_station_get_config(&station_cfg);  //DECLARA LA ESTRUCTURA station_cfg PARA CONFIGURAR EL MODO STATION


//  station_cfg.bssid_set=1;

//Nombre y contraseña del router que se conectara
  os_strcpy((char *)station_cfg.ssid,(const char *)sta_ssid); //NOMBRE DEL ROUTER A CONECTAR
  os_strcpy((char *)station_cfg.password,(const char *)sta_pass); //CLAVE DEL ROUTER A CONECTAR

  wifi_station_set_config(&station_cfg);  //CONFIGURADO EL MODO STATION
*/

  os_memcpy(config.ssid, "esp8266_WiFi",strlen("esp8266_WiFi"));  //NOMBRE DEL WIFI SERVIDOR
  os_memcpy(config.password,"esp123456",strlen("esp123456")); //CLAVE DEL WIFI SERVIDOR
  config.ssid_len = strlen("esp8266_WiFi"); //LONGITUD DE SSID
  config.authmode = AUTH_WPA_WPA2_PSK;
  wifi_softap_set_config(&config);  //CONFIGURADO EL MODO AP
}


void gpio_init(){
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
  gpio_output_set(GPIO_ID_PIN(2),0, GPIO_ID_PIN(2),0);

}


/*
void retardo(void *arg){
  counter++;
  //os_timer_disarm(&ptimer);
  //os_timer_disarm(&ptimer);
}
*/
/*
void xstrcat(char string1[],char string2[])
{
  int i,x,y;
  x=sizeof(string1);
  y=sizeof(string2);

  for(int k; k<x;k++){
    if(string1[k]=='!'){
      x=0;
    }
  }
  for(i=0;i<y;i++){
    string1[i+x]=string2[i];
  }//for ends
  //string1[x+y] = '\0';
}*/


/*
char *
xstrcat(char *dest, const char *src)
{
    //static int i=0;

    size_t x=sizeof(dest)/sizeof(dest[0]);

    strcpy(dest + x, src);

    return dest;
}
*/

void ICACHE_FLASH_ATTR
user_init(void)
{
    //CONFIGURARCION DEL UART
    uart_init(BIT_RATE_115200, BIT_RATE_115200);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0TXD_U, FUNC_U0TXD);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0RXD_U, FUNC_U0TXD);
    UART_SetStopBits(UART0, ONE_STOP_BIT);

    //os_sprintf(buffercaja,"");

    gpio_init();

    /*
    os_timer_disarm(&ptimer);
    os_timer_setfn(&ptimer, (os_timer_func_t *)retardo, NULL);
    os_timer_arm(&ptimer, 100, 1);
    */

//    os_printf("SDK version:%s\n", system_get_sdk_version());

//Llamada de función para la configuración del servidor
    ap_config_func();
/*Inicio del protocolo de comuicación por tcp
el argumento de la función es el puerto por el que se transmitirá
la información*/
    init_tcp(8266);



}
