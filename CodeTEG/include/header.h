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

LOCAL struct espconn user_tcp_espconn;
LOCAL struct _esp_tcp user_tcp;

char cadena[20];
float kpro1=0.33,
      kpro2=0.33,
      kpro3=0.33,
      koffset1=0,
      koffset2=39,
      koffset3=0,
      constante_grados=0.33;

struct softap_config config;
struct station_config station_cfg;


char sta_ssid[]="";
char sta_pass[]="";

void ap_config_func();

const char *pagina2=
"HTTP/1.1 200 OK\r\n\r\n"
"<!DOCTYPE html>"
"<html lang='es'>"
"<head>"
"<title>TEG</title>"
"<meta charset='UTF-8'>"
        "<meta name='viewport' content='width=device-width, user-scalable=no, initial-scale=1, maximum-scale=1, minimum-scale=1'>"
"<style>"
"\n* {"
    "\nmargin:0;"
    "\npadding: 0;"
    "\nbox-sizing: border-box;"
"\n}"

"\nbody {"
    "\nfont-family:sans-serif;"
"\n}"

"\nheader {"
    "\nwidth:100\x25;"
    "\nheight: 3em;"
    "\nbackground: #333;"
    "\ncolor: #fff;"
    "\nposition: fixed;"
    "\ntop: 0;"
    "\nleft: 0;"
    "\nz-index: 100;"
"\n}"

"\n.contenedor{"
    "\nwidth: 98\x25;"
    "\nmargin: auto;"
"\n}"

"\nh1 {"
    "\nfloat: left;"
    "\nfont-size: 1em;"
    "\npadding: 10px;"
"\n}"

"\nheader .contenedor{"
    "\ndisplay: table;"
"\n}"


"\n#resumen {"
    "\ntext-align: center;"
    "\nbackground-color: dimgrey;"
"\n}"

"\n#movimiento{"
    "\ntext-align: center;"
    "\nbackground-color:#222;"
    "\nheight: 70em;"
"\n}"

"\n#movimiento h3{"
    "\ncolor:#fff;"
    "\npadding:20px;"
"\n}"


"\n#laizquierda{"
    "\nwidth:49\x25;"
    "\nheight: 60em;"
    "\nfloat: left;"
    "\nbackground-color: lightgrey;"
"\n}"


"\n#laderecha{"
    "\nwidth:49\x25;"
    "\nheight: 60em;"
    "\nfloat: right;"
    "\nbackground-color: lightslategrey;"
"\n}"

"\ninput[type='text']{"
    "\nwidth: 55px;"
"\n}"

"\ninput[type='number']{"
    "\nwidth: 55px;"
"\n}"

"\ninput[type='submit']{"
    "\ncursor: pointer;"
"\n}"

"\ninput[type='range']{"
    "\nwidth: 75\x25;"
    "\nheight: 2px;"
    "\nbackground: #111;"
    "\n-webkit-appearance:none;"
    "\noutline: none;"
    "\nborder-radius: 2px;"
"\n}"

"\ninput[type='range']::-webkit-slider-thumb{"
     "\n-webkit-appearance:none;"
    "\nwidth: 20px;"
    "\nheight: 20px;"
    "\nborder-radius: 50\x25;"
    "\nbackground: #00bcd4;"
"\n}"


"\ninput{"
    "\nmargin: 20px 0px 0px 0px;"
"\n}"


"\n.label{"
    "\nmargin: 40px 0px 0px 20px;"
    "\ntext-align: center;"
    "\ncolor: #fff;"
"\n}"

"\n.labelconf{"
    "\nmargin: 40px 0px 0px 20px;"
    "\ntext-align: center;"
    "\ncolor: #000;"
    "\nfont-weight: bold;"

"\n}"

"\ndiv #wifi{"
    "\nheight: 8%;"
    "\nbackground-color:#444;"
    "\ncolor: #fff;"
    "\npadding: 10px;"

"}"

"\n#banner{"
    "\nmargin-top: 50px;"
    "\nposition: relative;"
"\n}"



"\n#banner img{"
    "\nwidth: 100\x25;"
    "\nheight: 100\x25;"
"\n}"

"\n#banner .contenedor{"
    "\nposition: absolute;"
    "\ntop:50\x25;"
    "\nleft: 50\x25;"
    "\ntransform: translateX(-50\x25) translateY(-50\x25);"
    "\ncolor: #fff;"
    "\nbackground: rgba(51,51,51,0.5);"
"\n}"

"\n#banner h2{"
    "\nfont-size: 1.5em;"
"\n}"
"\n</style>"
    "\n<script src='http://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js'></script>"
"\n</head>"
"<body>"


        "<header>"
            "<div class='contenedor'>"
               "<h1 class='titulo'>TRABAJO ESPECIAL DE GRADO</h1>"
            "</div>"
        "</header>"

        "<main>"
            "<div id='banner'>"
                "<img src='data:image/png;base64,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'>"
            "</div>"

            "<div id='resumen'>"
                "<h2>Acceso remoto al controlador del brazo manipulador MA2000</h2>"
                "<p>En esta pagina se encontraran los controles necesarios para mover y configurar el brazo robot MA2000 ubicado en el LCID de la Escuela de Ingenieria Electrica.</p>"
            "</div>"
            /*"<div>"
                "<form onsubmit='return false'>"
                    "<input type='number' name='rep' id='rep' placeholder='0'><br>"
                    "<textarea name='caja' id='caja' cols='30' rows='10'></textarea>"
                    "<input type='submit' value='pulsar' onclick='areatexto(this.form.caja.value,this.form.rep.value)'><br>"
                "</form>"
            "</div>"*/
            "<div id='movimiento'>"
                "<h3>Movimiento del brazo robot en tiempo real</h3>"
                "<article>"
                    "<p class='label'>Mover el motor 1</p>"
                    "<form onsubmit='return false'>"

                       "<input type='range' name='num1' min='-135' max='135' step='1' id='slider' onchange='mover(this.value,this.name)' oninput='this.form.xF1.value=this.value' >"
"<!--                       onchange='mover(this.value,this.name)'-->"

                        "<input type='number' name='xF1' placeholder='0' min='-135' max='135'>"

                        "<input type='submit' value='Motor 1' onclick='var that=this;this.form.num1.value=this.form.xF1.value;mover(this.form.num1.value,that.form.num1.name)'>"
                    "</form>"
                "</article>"
                "<article>"
                   "<p class='label'>Mover el motor 2</p>"
                    "<form onsubmit='return false'>"
                       "<input type='range' name='num2' min='-135' max='135' step='1' id='slider' onchange='mover(this.value,this.name)' oninput='this.form.xF2.value=this.value'>"
                        "<input type='number' name='xF2' placeholder='0' min='-135' max='135'>"
                        "<input type='submit' value='Motor 2' onclick='var that=this;this.form.num2.value=this.form.xF2.value;mover(this.form.num2.value,that.form.num2.name)'>"
                    "</form>"
                "</article>"
                "<article>"
                   "<p class='label'>Mover el motor 3</p>"
                    "<form onsubmit='return false'>"
                       "<input type='range' name='num3' min='-135' max='135' step='1' id='slider' onchange='mover(this.value,this.name)' oninput='this.form.xF3.value=this.value'>"
                        "<input type='number' name='xF3' placeholder='0' min='-135' max='135'>"
                        "<input type='submit' value='Motor 3' onclick='var that=this;this.form.num3.value=this.form.xF3.value;mover(this.form.num3.value,that.form.num3.name)'>"
                    "</form>"
                "</article>"
                "<article>"
                   "<p class='label'>Mover el motor 4</p>"
                    "<form onsubmit='return false'>"
                       "<input type='range' name='num4' min='-60' max='60' step='1' id='slider' onchange='mover(this.value,this.name)' oninput='this.form.xF4.value=this.value'>"
                        "<input type='number' name='xF4' placeholder='0' min='-60' max='60'>"
                        "<input type='submit' value='Motor 4' onclick='var that=this;this.form.num4.value=this.form.xF4.value;mover(this.form.num4.value,that.form.num4.name)'>"
                    "</form>"
                "</article>"
                "<article>"
                   "<p class='label'>Mover el motor 5</p>"
                    "<form onsubmit='return false'>"
                       "<input type='range' name='num5' min='-60' max='60' step='1' id='slider' onchange='mover(this.value,this.name)' oninput='this.form.xF5.value=this.value'>"
                        "<input type='number' name='xF5' placeholder='0' min='-60' max='60'>"
                        "<input type='submit' value='Motor 5' onclick='var that=this;this.form.num5.value=this.form.xF5.value;mover(this.form.num5.value,that.form.num5.name)'>"
                    "</form>"
                "</article>"
                "<article>"
                   "<p class='label'>Mover el motor 6</p>"
                    "<form onsubmit='return false'>"
                       "<input type='range' name='num6' min='-60' max='60' step='1' id='slider' onchange='mover(this.value,this.name)' oninput='this.form.xF6.value=this.value'>"
                        "<input type='number' name='xF6' placeholder='0' min='-60' max='60'>"
                        "<input type='submit' value='Motor 6' onclick='var that=this;this.form.num6.value=this.form.xF6.value;mover(this.form.num6.value,that.form.num6.name)'>"
                    "</form>"
                "</article>"
                "<article>"
                   "<p class='label'>Activar/Desactivar la Pinza neumatica</p>"
                    "<form onsubmit='return false' id='pinza'>"
                        "<input type='button' onclick='pinza(this.form.ON.name)' value='PINZA ON' name='ON'>"

                        "<input type='button' onclick='pinza(this.form.OFF.name)' value='PINZA OFF' name='OFF'>"
                    "</form>"
                "</article>"
            "</div>"

            "<div>"
            "<div id='wifi'>"
              "<h3>CONFIGURAR WIFI</h3>"
                      "<p>Introduzca el nombre del WiFi y su clave. (Por favor, siempre configure estos valores antes de iniciar movimiento. De no poseer Router, envie los valores en blanco.)</p>"

                      "<form onsubmit='return false'>"
                                "<input type='textbox' name='ssid' placeholder='SSID'>"
                                "<input type='submit' value='SSID' onclick='mover(this.form.ssid.value,this.form.ssid.name)'><br>"

                                "<input type='textbox' name='password' placeholder='PASSWORD'>"
                                "<input type='submit' value='PASSWORD' onclick='mover(this.form.password.value,this.form.password.name)'>"
                        "</form>"

                   "<div id='laizquierda'>"

                    "<h4>PID</h4>"
                    "<p>En esta seccion se podran configurar los parametros del PID correspondiente a los motores 1, 2 y 3.</p>"

                        "<p class='labelconf'>Configurar PID 1</p>"
                        "<form onsubmit='return false'>"
                            "<input type='number' name='Kp1' placeholder='0' min='0' max='32767' value='29491'>"
                            "<input type='submit' value='Kp' onclick='mover(this.form.Kp1.value,this.form.Kp1.name)'><br>"

                            "<input type='number' name='Ki1' placeholder='0' min='0' max='32767' value='114'>"
                            "<input type='submit' value='Ki' onclick='mover(this.form.Ki1.value,this.form.Ki1.name)'><br>"

                            "<input type='number' name='Kd1' placeholder='0' min='0' max='32767' value='0'>"
                            "<input type='submit' value='Kd' onclick='mover(this.form.Kd1.value,this.form.Kd1.name)'><br>"
                        "</form>"

                        "<p class='labelconf'>Configurar PID 2</p>"
                        "<form onsubmit='return false'>"
                            "<input type='number' name='Kp2' placeholder='0' min='0' max='32767' value='29491'>"
                            "<input type='submit' value='Kp' onclick='mover(this.form.Kp2.value,this.form.Kp2.name)'><br>"

                            "<input type='number' name='Ki2' placeholder='0' min='0' max='32767' value='114'>"
                            "<input type='submit' value='Ki' onclick='mover(this.form.Ki2.value,this.form.Ki2.name)'><br>"

                            "<input type='number' name='Kd2' placeholder='0' min='0' max='32767' value='0'>"
                            "<input type='submit' value='Kd' onclick='mover(this.form.Kd2.value,this.form.Kd2.name)'><br>"
                        "</form>"

                        "<p class='labelconf'>Configurar PID 3</p>"
                        "<h5>Configurar PID 3</h5>"
                        "<form onsubmit='return false'>"
                            "<input type='number' name='Kp3' placeholder='0' min='0' max='32767' value='29491'>"
                            "<input type='submit' value='Kp' onclick='mover(this.form.Kp3.value,this.form.Kp3.name)'><br>"

                            "<input type='number' name='Ki3' placeholder='0' min='0' max='32767' value='114'>"
                            "<input type='submit' value='Ki' onclick='mover(this.form.Ki3.value,this.form.Ki3.name)'><br>"

                            "<input type='number' name='Kd3' placeholder='0' min='0' max='32767' value='0'>"
                            "<input type='submit' value='Kd' onclick='mover(this.form.Kd3.value,this.form.Kd3.name)'><br>"
                        "</form>"
                "</div>"
                "<div id='laderecha'>"
                    "<h4>Otras configuraciones</h4>"

                    "<p class='labelconf'>Configurar constantes para Motor 1</p>"
                    "<form onsubmit='return false'>"
                        "<input type='text' name='Kpro1' value='0.33'>"
                        "<input type='submit' value='Kpro' onclick='mover(this.form.Kpro1.value,this.form.Kpro1.name)'><br>"

                        "<input type='text' name='Koffset1' value='0'>"
                        "<input type='submit' value='Koffset' onclick='mover(this.form.Koffset1.value,this.form.Koffset1.name)'>"
                    "</form>"

                    "<p class='labelconf'>Configurar constantes para Motor 2</p>"
                            "<form onsubmit='return false'>"
                                "<input type='text' name='Kpro2' value='0.33'>"
                                "<input type='submit' value='Kpro' onclick='mover(this.form.Kpro2.value,this.form.Kpro2.name)'><br>"
                                "<input type='text' name='Koffset2' value='39'>"
                                "<input type='submit' value='Koffset' onclick='mover(this.form.Koffset2.value,this.form.Koffset2.name)'>"

                                "</form>"

                    "<p class='labelconf'>Configurar constantes para Motor 3</p>"
                                "<form onsubmit='return false'>"
                                    "<input type='text' name='Kpro3' value='0.33'>"
                                    "<input type='submit' value='Kpro' onclick='mover(this.form.Kpro3.value,this.form.Kpro3.name)'><br>"

                                    "<input type='text' name='Koffset3' value='0'>"
                                    "<input type='submit' value='Koffset' onclick='mover(this.form.Koffset3.value,this.form.Koffset3.name)'>"


                                "</form>"
                    "<p class='labelconf'>Habilitar/Deshabilitar puentes H</p>"
                             "<form onsubmit='return false'>"
                                  "<input type='checkbox' name='puente1' checked onclick='chequear(this)'> Puente H del Motor 1<br>"
                                  "<input type='checkbox' name='puente2' checked onclick='chequear(this)'> Puente H del Motor 2<br>"
                                  "<input type='checkbox' name='puente3' checked onclick='chequear(this)'> Puente H del Motor 3<br>"
                            "</form>"
                "</div>"
            "</div>"
        "</div>"
    "</main>"

    "\n<script>"
    "\n$.ajaxSetup({timeout: 3600000});"

    "\nfunction mover(pos, nombre) {"
        //$.get("?" + nombre + "=" + pos);
        "\nsetTimeout(function () {$.get('?' + nombre + '=' + pos); }, 10);"
    "\n}"

    "\nfunction pinza(state){"
        "\nvar gripon='gripon';"
        "\nvar gripoff='gripoff';"
        "\nif(state=='ON'){"
           "\nmover('',gripon);"
           "\n}else if(state=='OFF'){"
               "\nmover('',gripoff);"
           "\n}"

    "\n}"

"var pass;"
"var exito='ROBOCOM';"

"\npass=prompt('Introduzca la clave para entrar');"

"\nif(pass==exito){"
    "\nalert('Clave exitosa! Haga clic para entrar');"
"\n} else{"
    "\nalert('Clave incorrecta! Haga clic para ir a Google');"
    "\nwindow.location='http://www.google.com';"
"}"

"\nfunction chequear(formulario){"
    "\nvar state;"
    "\nvar that=formulario;"
    "\nif(that.checked){"
        "\nstate='ON';"
  "\n}else{"
        "\nstate='OFF';"
    "}"

    "\nmover(state,that.name);"
"}"

/*
"\nvar wait=0;"

"\nfunction areatexto(valor,repeticion){"
   "\nvar arrayOfLines = valor.split('\x5C\x6E');"

        "\n$.each(arrayOfLines, function(index, item) {"
        "\nitem=item.split(' ');"


            //if(item[0]=='wait'){wait=item[1];}

            "\ncomprobar(item[0],item[1]);"


        "\n});"
        "\nmover(repeticion,'caja&inic');"
"\n}"


"\nfunction comprobar(item0,item1) {"

"\nswitch (item0) {"
                "\ncase 'q1':"

                    "\nmover(item1,'caja&num1');"
                    "\nwait=0;"
                    "\nbreak;"

                "\ncase 'q2':"

                    "\nmover(item1,'caja&num2');"
                    "\nwait=0;"
                    "\nbreak;"

                "\ncase 'q3':"

                    "\nmover(item1,'caja&num3');"
                    "\nwait=0;"
                    "\nbreak;"

                "\ncase 'q4':"

                    "\nmover(item1,'caja&num4');"
                    "\nwait=0;"
                    "\nbreak;"

                "\ncase 'q5':"

                    "\nmover(item1,'caja&num5');"
                    "\nwait=0;"
                    "\nbreak;"

                "\ncase 'q6':"

                    "\nmover(item1,'caja&num6');"
                    "\nwait=0;"
                    "\nbreak;"

                "\ncase 'wait':"

                    "\nwait=mover(item1,'caja&wait');"
                    "\nbreak;"
                "\ndefault:"
                    "\nwait=0;"
                    "\nbreak;"
            "\n}"
"\n}"
*/


    "\n</script>"
"</body>"
"</html>";
