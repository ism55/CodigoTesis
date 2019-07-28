const char *respuesta1=
"HTTP/1.1 200 OK\r\n\r\n";

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
    "\n<script src='http://ajax.googleapis.com/ajax/libs/jquery/1/jquery.min.js' type='text/javascript'></script>"

    "\n<link rel='icon' href='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAACXBIWXMAAA7EAAAOxAGVKw4bAAAAIGNIUk0AAHolAACAgwAA+f8AAIDpAAB1MAAA6mAAADqYAAAXb5JfxUYAAAIVSURBVHjadFOxSxtRHP6QbIEzuTa5mOIWjpNDYzIUMkSEhFucUjKUDhpwECqOWaSCDoGDkiUkg05XOhwIYqTUkCHQUhI5vV6t0AoFuaV0c+k/8HWQF+7S+OAb3u/3fd/v997vPZDEJCzLWt3a2qKiKLy4uGA+n2ej0Xg1jRvanJyc5Ofn578A8AEwnU5zZ2eHAKhpWi8ej3+rVqtvpxo0m80XQjg3N8d2u82bmxtGIhECoGma1HWdAHxVVfshg8vLy6QQA+Ds7Cxt26Zt2xQxx3FIkrlcjgD8xcXFD2MDWZa/CqLA7u4uU6nUeN/pdFgqlVgoFETMPz4+fg7P82RRXVXVfjQa/QHAN03zpRAbhsG1tTVOFkkkEsTBwcE40O/3VXG2hYWFnqhkWdZqNps9mzQAwIjv+xDr/v7+KYBfd3d3kdvbW03ENzY2PkmS9NdxnN5gMCi5rltFIDl2W1lZeUcShmEcBqr4wbEVi8X3oS729vY4SQ5ORJiSxObm5ptgDgDhed4TAH8AMJlMOvv7+7UgqdvtLg+Hw7QkSd8nxYqiPDjHYrGfAEJzF+BDS9Pgn56eLoN86GJmZuZ3q9UKkWRZfszA13X9Y+gpu66b0DRtECRub2/z/Pz8P/HS0tLZ1M80Go2eZTKZz+JOrq6uWKlUxkIAfr1ef/3obxS4vr6Or6+vkyRrtRrL5TKPjo6Madx/AwBNqMfqI8/1qwAAAABJRU5ErkJggg==' type='image/x-icon'>"
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
                "<button onClick='window.location.reload();'>Recargar pagina</button>"
            "</div>"
            "<div>"
            "<h3>Esquema de motores</h3>"
            "<img src='data:image/png;base64,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'>"
                "<form onsubmit='return false'>"
                    "<h3>Probador de trayectorias</h3>"
                    "<textarea name='caja' id='caja' cols='30' rows='10'></textarea>"
                    "<input type='submit' value='pulsar' onclick='areatexto(this.form.caja.value)'><br>"
                "</form>"
            "</div>"
            "<div id='movimiento'>"
                "<h3>Movimiento del brazo robot en tiempo real</h3>"
                "<article>"
                    "<p class='label'>Mover el motor A</p>"
                    "<form onsubmit='return false'>"

                       "<input type='range' name='num1' min='-135' max='135' step='10' id='slider' oninput='mover(this.value,this.name);this.form.xF1.value=this.value' >"
"<!--                       onchange='mover(this.value,this.name)'-->"

                        "<input type='number' name='xF1' placeholder='0' min='-135' max='135'>"

                        "<input type='submit' value='Motor 1' onclick='var that=this;this.form.num1.value=this.form.xF1.value;mover(this.form.num1.value,that.form.num1.name)'>"
                    "</form>"
                "</article>"
                "<article>"
                   "<p class='label'>Mover el motor B</p>"
                    "<form onsubmit='return false'>"
                       "<input type='range' name='num2' min='-135' max='135' step='10' value= '45' id='slider' oninput='mover(this.value,this.name);this.form.xF2.value=this.value'>"
                        "<input type='number' name='xF2' placeholder='45' min='-135' max='135'>"
                        "<input type='submit' value='Motor 2' onclick='var that=this;this.form.num2.value=this.form.xF2.value;mover(this.form.num2.value,that.form.num2.name)'>"
                    "</form>"
                "</article>"
                "<article>"
                   "<p class='label'>Mover el motor C</p>"
                    "<form onsubmit='return false'>"
                       "<input type='range' name='num3' min='-135' max='135' step='10' id='slider' value='-45' oninput='mover(this.value,this.name);this.form.xF3.value=this.value'>"
                        "<input type='number' name='xF3' placeholder='-45' min='-135' max='135'>"
                        "<input type='submit' value='Motor 3' onclick='var that=this;this.form.num3.value=this.form.xF3.value;mover(this.form.num3.value,that.form.num3.name)'>"
                    "</form>"
                "</article>"
                "<article>"
                   "<p class='label'>Mover el motor D</p>"
                    "<form onsubmit='return false'>"
                       "<input type='range' name='num4' min='-60' max='60' step='10' id='slider' oninput='mover(this.value,this.name);this.form.xF4.value=this.value'>"
                        "<input type='number' name='xF4' placeholder='0' min='-60' max='60'>"
                        "<input type='submit' value='Motor 4' onclick='var that=this;this.form.num4.value=this.form.xF4.value;mover(this.form.num4.value,that.form.num4.name)'>"
                    "</form>"
                "</article>"
                "<article>"
                   "<p class='label'>Mover el motor E</p>"
                    "<form onsubmit='return false'>"
                       "<input type='range' name='num5' min='-60' max='60' step='10' id='slider' oninput='mover(this.value,this.name);this.form.xF5.value=this.value'>"
                        "<input type='number' name='xF5' placeholder='0' min='-60' max='60'>"
                        "<input type='submit' value='Motor 5' onclick='var that=this;this.form.num5.value=this.form.xF5.value;mover(this.form.num5.value,that.form.num5.name)'>"
                    "</form>"
                "</article>"
                "<article>"
                   "<p class='label'>Mover el motor F</p>"
                    "<form onsubmit='return false'>"
                       "<input type='range' name='num6' min='-60' max='60' step='10' id='slider' oninput='mover(this.value,this.name);this.form.xF6.value=this.value'>"
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
          /*  "<div id='wifi'>"
              "<h3>CONFIGURAR WIFI</h3>"
                      "<p>Introduzca el nombre del WiFi y su clave. (Por favor, siempre configure estos valores antes de iniciar movimiento. De no poseer Router, envie los valores en blanco.)</p>"

                      "<form onsubmit='return false'>"
                                "<input type='textbox' name='ssid' placeholder='SSID'>"
                                "<input type='submit' value='SSID' onclick='mover(this.form.ssid.value,this.form.ssid.name)'><br>"

                                "<input type='textbox' name='password' placeholder='PASSWORD'>"
                                "<input type='submit' value='PASSWORD' onclick='mover(this.form.password.value,this.form.password.name)'>"
                        "</form>"
*/
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
                            "<input type='number' name='Kp2' placeholder='0' min='0' max='32767' value='5000'>"
                            "<input type='submit' value='Kp' onclick='mover(this.form.Kp2.value,this.form.Kp2.name)'><br>"

                            "<input type='number' name='Ki2' placeholder='0' min='0' max='32767' value='10'>"
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

                            "<p class='labelconf'>Configurar registro PR1</p>"
                            "<form onsubmit='return false'>"
                                "<input type='text' name='PR1' value='500'>"
                                "<input type='submit' value='PR1' onclick='mover(this.form.PR1.value,this.form.PR1.name)'><br>"
                            "</form>"
                "</div>"
            "</div>"
        "</div>"
    "</main>"

    "\n<script>"

    "\n/*global $, prompt, alert, window*/"
    "\n/*jslint node: true */"
    "\n'use strict';"


    "\nfunction mover(pos, nombre) {"
    "\n$.get('?' + nombre + '=' + pos);"
    //setTimeout(function () {$.get('?' + nombre + '=' + pos); }, 10);
    //{Connection:close};
/*    //"\nvar URL = '?' + nombre + '=' + pos;"

    //"\n$.ajax({"
      //  "\ntype: 'GET',"
      //  "\nurl: URL"
    //"\n});"*/
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


"\nfunction areatexto(valor){"
   "\nvar arrayOfLines = valor.split('\x5C\x6E');"

        "\n$.each(arrayOfLines, function(index, item) {"
        "\nitem=item.split(' ');"


            //if(item[0]=='wait'){wait=item[1];}

            "\ncomprobar(item[0],item[1]);"


        "\n});"
"\n}"


"\nfunction comprobar(item0,item1) {"

"\nswitch (item0) {"
                "\ncase 'q1':"
                    "\nif(item1>135){"
                      "\nmover(135,'num1');"
                    "\n}else if(item1<-135){"
                      "\nmover(-135,'num1');"
                    "\n}else{"
                      "\nmover(item1,'num1');"
                    "\n}"

                    "\nbreak;"

                "\ncase 'q2':"

                "\nif(item1>135){"
                  "\nmover(135,'num2');"
                "\n}else if(item1<-135){"
                  "\nmover(-135,'num2');"
                "\n}else{"
                  "\nmover(item1,'num2');"
                "\n}"
                    "\nbreak;"

                "\ncase 'q3':"

                "\nif(item1>135){"
                  "\nmover(135,'num3');"
                "\n}else if(item1<-135){"
                  "\nmover(-135,'num3');"
                "\n}else{"
                  "\nmover(item1,'num3');"
                "\n}"
                    "\nbreak;"

                "\ncase 'q4':"

                  "\nif(item1>60){"
                    "\nmover(60,'num4');"
                  "\n}else if(item1<-60){"
                    "\nmover(-60,'num4');"
                  "\n}else{"
                    "\nmover(item1,'num4');"
                  "\n}"
                    "\nbreak;"

                "\ncase 'q5':"

                  "\nif(item1>60){"
                    "\nmover(60,'num5');"
                  "\n}else if(item1<-60){"
                    "\nmover(-60,'num5');"
                  "\n}else{"
                    "\nmover(item1,'num5');"
                  "\n}"
                    "\nbreak;"

                "\ncase 'q6':"
                  "\nif(item1>60){"
                    "\nmover(60,'num6');"
                  "\n}else if(item1<-60){"
                    "\nmover(-60,'num6');"
                  "\n}else{"
                    "\nmover(item1,'num6');"
                  "\n}"
                    "\nbreak;"

                "\ncase 'gripon':"
                    "\npinza('ON');"
                    "\nbreak;"

                "\ncase 'gripoff':"
                    "\npinza('OFF');"
                    "\nbreak;"
              "\ndefault:"
                    "\nbreak;"
            "\n}"
"\n}"



    "\n</script>"
"</body>"
"</html>";