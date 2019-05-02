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
float constante_grados=0.33;

struct softap_config config;
struct station_config station_cfg;


char sta_ssid[]="";
char sta_pass[]="";

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
    "\nfont-size: 2em;"
"\n}"

"\nheader .contenedor{"
    "\ndisplay: table;"
"\n}"

"\nsection{"
    "\nwidth:100\x25;"
    "\nmargin-bottom: 25px;"
"\n}"


"\n#resumen {"
    "\ntext-align: center;"
    "\nbackground-color: dimgrey;"
"\n}"

"\n#movimiento{"
    "\ntext-align: center;"
    "\nbackground-color:#222;"
    "\nheight: 8\x25;"
"\n}"

"\n#movimiento h3{"
    "\ncolor:#fff;"
    "\npadding:20px;"
"\n}"
"\ndiv #configuracion{"

"\n}"

"\n#laizquierda{"
    "\nwidth:49\x25;"
    "\nheight: 300px;"
    "\nfloat: left;"
    "\nbackground-color: lightgrey;"
"\n}"


"\n#laderecha{"
    "\nwidth:49\x25;"
    "\nheight: 300px;"
    "\nfloat: right;"
    "\nbackground-color: lightslategrey;"
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

"\nsection article form{"
    "\nposition: relative;"
"\n}"

"\ninput{"
    "\nmargin: 20px 0px 0px 0px;"
"\n}"


"\n.label{"
    "\nmargin: 40px 0px 0px 20px;"
    "\ntext-align: center;"
    "\ncolor: #fff;"
"\n}"
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
            "<section id='banner'>"
                "<img src='data:image/jpeg;base64,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'>"
                "<div class='contenedor'>"
                    "<h2>Acceso remoto al controlador de un brazo manipulador</h2>"
                    "<p>Trabajo Especial de Grado para optar al titulo de Ingeniero Electricista de la ilustre Universidad Central de Venezuela.</p>"
                "</div>"
            "</section>"

            "<section id='resumen'>"
                "<h2>Acceso remoto al controlador del brazo manipulador MA2000</h2>"
                "<p>En esta pagina se encontraran los controles necesarios para mover y configurar el brazo robot MA2000 ubicado en el LCID de la Escuela de Ingenieria Electrica.</p>"
            "</section>"
            "<section id='movimiento'>"
                "<h3>Movimiento del brazo robot en tiempo real</h3>"
                "<article>"
                    "<p class='label'>Mover el motor 1</p>"
                    "<form onsubmit='return false'>"

                       "<input type='range' name='num1' min='-135' max='135' step='1' id='slider' oninput='mover(this.value,this.name);this.form.xF1.value=this.value' >"
"<!--                       onchange='mover(this.value,this.name)'-->"

                        "<input type='number' name='xF1' placeholder='0' min='-135' max='135'>"

                        "<input type='submit' value='Motor 1' onclick='var that=this;this.form.num1.value=this.form.xF1.value;mover(this.form.num1.value,that.form.num1.name)'>"
                    "</form>"
                "</article>"
                "<article>"
                   "<p class='label'>Mover el motor 2</p>"
                    "<form onsubmit='return false'>"
                       "<input type='range' name='num2' min='-135' max='135' step='1' id='slider' oninput='mover(this.value,this.name);this.form.xF2.value=this.value'>"
                        "<input type='number' name='xF2' placeholder='0' min='-135' max='135'>"
                        "<input type='submit' value='Motor 2' onclick='var that=this;this.form.num2.value=this.form.xF2.value;mover(this.form.num2.value,that.form.num2.name)'>"
                    "</form>"
                "</article>"
                "<article>"
                   "<p class='label'>Mover el motor 3</p>"
                    "<form onsubmit='return false'>"
                       "<input type='range' name='num3' min='-135' max='135' step='1' id='slider' oninput='mover(this.value,this.name);this.form.xF3.value=this.value'>"
                        "<input type='number' name='xF3' placeholder='0' min='-135' max='135'>"
                        "<input type='submit' value='Motor 3' onclick='var that=this;this.form.num3.value=this.form.xF3.value;mover(this.form.num3.value,that.form.num3.name)'>"
                    "</form>"
                "</article>"
                "<article>"
                   "<p class='label'>Mover el motor 4</p>"
                    "<form onsubmit='return false'>"
                       "<input type='range' name='num4' min='-60' max='60' step='1' id='slider' oninput='mover(this.value,this.name);this.form.xF4.value=this.value'>"
                        "<input type='number' name='xF4' placeholder='0' min='-60' max='60'>"
                        "<input type='submit' value='Motor 4' onclick='var that=this;this.form.num4.value=this.form.xF4.value;mover(this.form.num4.value,that.form.num4.name)'>"
                    "</form>"
                "</article>"
                "<article>"
                   "<p class='label'>Mover el motor 5</p>"
                    "<form onsubmit='return false'>"
                       "<input type='range' name='num5' min='-60' max='60' step='1' id='slider' oninput='mover(this.value,this.name);this.form.xF5.value=this.value'>"
                        "<input type='number' name='xF5' placeholder='0' min='-60' max='60'>"
                        "<input type='submit' value='Motor 5' onclick='var that=this;this.form.num5.value=this.form.xF5.value;mover(this.form.num5.value,that.form.num5.name)'>"
                    "</form>"
                "</article>"
                "<article>"
                   "<p class='label'>Mover el motor 6</p>"
                    "<form onsubmit='return false'>"
                       "<input type='range' name='num6' min='-60' max='60' step='1' id='slider' oninput='mover(this.value,this.name);this.form.xF6.value=this.value'>"
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
            "</section>"

            "<section>"
            "<div id='configuracion'>"
                   "<div id='laizquierda'>"

                    "<h4>PID</h4>"
                    "<p>En esta seccion se podran configurar los parametros del PID correspondiente a los motores 1, 2 y 3.</p>"

                        "<p class='labelconf'>Configurar PID 1</p>"
                        "<form onsubmit='return false'>"
                            "<input type='number' name='Kp1' placeholder='0' min='0' max='32767' value='29491'>"
                            "<input type='submit' value='Kp' onclick='mover(this.form.Kp1.value,this.form.Kp1.name)'>"

                            "<input type='number' name='Ki1' placeholder='0' min='0' max='32767' value='114'>"
                            "<input type='submit' value='Ki' onclick='mover(this.form.Ki1.value,this.form.Ki1.name)'>"

                            "<input type='number' name='Kd1' placeholder='0' min='0' max='32767' value='0'>"
                            "<input type='submit' value='Kd' onclick='mover(this.form.Kd1.value,this.form.Kd1.name)'>"
                        "</form>"

                        "<p class='labelconf'>Configurar PID 2</p>"
                        "<form onsubmit='return false'>"
                            "<input type='number' name='Kp2' placeholder='0' min='0' max='32767' value='29491'>"
                            "<input type='submit' value='Kp' onclick='mover(this.form.Kp2.value,this.form.Kp2.name)'>"

                            "<input type='number' name='Ki2' placeholder='0' min='0' max='32767' value='114'>"
                            "<input type='submit' value='Ki' onclick='mover(this.form.Ki2.value,this.form.Ki2.name)'>"

                            "<input type='number' name='Kd2' placeholder='0' min='0' max='32767' value='0'>"
                            "<input type='submit' value='Kd' onclick='mover(this.form.Kd2.value,this.form.Kd2.name)'>"
                        "</form>"

                        "<p class='labelconf'>Configurar PID 3</p>"
                        "<h5>Configurar PID 3</h5>"
                        "<form onsubmit='return false'>"
                            "<input type='number' name='Kp3' placeholder='0' min='0' max='32767' value='29491'>"
                            "<input type='submit' value='Kp' onclick='mover(this.form.Kp3.value,this.form.Kp3.name)'>"

                            "<input type='number' name='Ki3' placeholder='0' min='0' max='32767' value='114'>"
                            "<input type='submit' value='Ki' onclick='mover(this.form.Ki3.value,this.form.Ki3.name)'>"

                            "<input type='number' name='Kd3' placeholder='0' min='0' max='32767' value='0'>"
                            "<input type='submit' value='Kd' onclick='mover(this.form.Kd3.value,this.form.Kd3.name)'>"
                        "</form>"
                "</div>"
                "<div id='laderecha'>"
                    "<h4>Parametros generales</h4>"
                    "<p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Similique corporis, ratione nihil! Dolorem libero vero inventore, nostrum nobis asperiores voluptatem!</p>"

                    "<form onsubmit='return false'>"
                        "<input type='number' name='periodo' id='periodo'>"
                        "<input type='submit' value='Modificar'>"
                    "</form>"

                    "<h5>Constantes de calibracion</h5>"
                    "<form onsubmit='return false'>"
                            "<input type='number' name='Kp3' placeholder='0' min='0' max='32767' value='29491'>"
                            "<input type='submit' value='Kp' onclick='mover(this.form.Kp3.value,this.form.Kp3.name)'>"

                            "<input type='number' name='Ki3' placeholder='0' min='0' max='32767' value='114'>"
                            "<input type='submit' value='Ki' onclick='mover(this.form.Ki3.value,this.form.Ki3.name)'>"

                            "<input type='number' name='Kd3' placeholder='0' min='0' max='32767' value='0'>"
                            "<input type='submit' value='Kd' onclick='mover(this.form.Kd3.value,this.form.Kd3.name)'>"
                        "</form>"

                    "<form onsubmit='return false'>"
                            "<input type='number' name='Kp3' placeholder='0' min='0' max='32767' value='29491'>"
                            "<input type='submit' value='Kp' onclick='mover(this.form.Kp3.value,this.form.Kp3.name)'>"

                            "<input type='number' name='Ki3' placeholder='0' min='0' max='32767' value='114'>"
                            "<input type='submit' value='Ki' onclick='mover(this.form.Ki3.value,this.form.Ki3.name)'>"

                            "<input type='number' name='Kd3' placeholder='0' min='0' max='32767' value='0'>"
                            "<input type='submit' value='Kd' onclick='mover(this.form.Kd3.value,this.form.Kd3.name)'>"
                        "</form>"
                "</div>"
            "</div>"
        "</section>"
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
           "\nmover('=',gripon);"
           "\n}else if(state=='OFF'){"
               "\nmover('=',gripoff);"
           "\n}"

    "\n}"

"var pass;"
"var exito='ROBOCOM';"

"pass=prompt('Introduzca la clave para entrar');"

"if(pass==exito){"
    "alert('Clave exitosa! Haga clic para entrar');"
"} else{"
    "alert('Clave incorrecta! Haga clic para ir a Google');"
    "window.location='http://www.google.com';"
"}"

    "\n</script>"
"</body>"
"</html>";
