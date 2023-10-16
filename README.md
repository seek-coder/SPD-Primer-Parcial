# PRIMER PARCIAL SPD
![ArduinoTinkercad](https://github.com/seek-coder/SPD-Primer-Parcial/assets/130781541/7484325e-8708-4f26-8f15-d5f662a15d8a)

## INTEGRANTES
+ Braian Catriel Gatto
+ Leandro Gómez
+ Rocío Gómez

## PROYECTO - PARTE 1: Contador de 0 a 99 con Display 7 Segmentos y Multiplexación
![part1](https://github.com/seek-coder/SPD-Primer-Parcial/assets/130781541/db9afa65-e152-49b8-ad2c-3fb52d3a5ddb)

### I. DESCRIPCIÓN: 
Se trata de un **contador de dos dígitos a partir de dos displays de siete segmentos** que se controlan por medío de **tres botones**, uno para **aumentar** el contador, otro para **disminuirlo** y otro para **reiniciarlo**.
La _estructura básica_ del código es la siguiente:
  1) la definición de nombres para diferentes valores con el objetivo de no utilizar espacio de memoria adicional pero aportar legibilidad al código
  2) la declaración de variables necesarias para el correcto desarrollo del programa
  3) una función ```setup()``` que configura pines de entrada para los botones
  4) una función ```loop()``` para determinar la lógica principal del programa que se repetirá mientras Arduino esté encendido
  5) una función ```printDigit()``` para prender segmentos del display
  6) una función ```keypressed()``` para detectar si los botones se presionaron o no
  7) una función ```turnDigitOn()``` para activar unidades o decenas
  8) una función ```printCount()``` para mostrar unidades o decenas en el display

El trabajo de electrónica cuenta con [multiplexación](https://www.uazuay.edu.ec/sistemas/teleprocesos/multiplexacion) y logra evitar ruidos de señal como el [debounce](https://www.murkyrobot.com/guias/arduino/debounce)
### II. FUNCIÓN PRINCIPAL:
La función que se encarga de la lógica principal del programa, ```loop()``` ha de ser la función más importante del mismo, porque define su lógica. Se declara una variable que almacena lo que devuelva la función ```keypressed()``` y a partir de ahí, se comprueban valores que permiten incrementar, decrementar o reiniciar el contador general. Sin embargo, hay que hacer notar que la función ```keypressed()``` es prácticamente igual de relevante, no sólo por su utilidad sino por que el bucle inicial depende de sus resultados. Con el fin de obviar la relevancia del bucle inicial (con el cual ningún código de Arduino funcionaría realmente), determinaremos la función ```keypressed()``` como la principal. 
La _estructura básica_ de la función es la siguiente:
  1) se establece el valor de cada botón según variables previamente definidas
  2) se comprueba el estado de los botones (no presionado por defecto)
  3) se devuelven los valores específicos según cada caso de botón presionado: si se incrementa el contador, si disminuye, si se reinicia o si no se presiona nada.
```python3
int keypressed(void)
{
  upBtn = digitalRead(UP);
  downBtn = digitalRead(DOWN);
  resetBtn = digitalRead(RESET);
  
  if (upBtn)
  {
    upBtnPreview = 1;
  }
  if(downBtn)
  {
    downBtnPreview = 1;
  }
  if(resetBtn)
  {
    resetBtnPreview = 1;
  }
  
  if(upBtn == 0 && upBtn != upBtnPreview)
    {
      upBtnPreview = upBtn;
      return UP;
    }
  if(downBtn == 0 && downBtn !=  downBtnPreview)
    {
      downBtnPreview = downBtn;
      return DOWN;
    }
  if(resetBtn == 0 && resetBtn != resetBtnPreview)
    {
      resetBtnPreview = resetBtn;
      return RESET;
    }
  return 0;
}
```
## III. LINK AL PROYECTO
[SPD - Primer parcial - Proyecto de Arduino, Parte1](https://www.tinkercad.com/things/bEkxNiuQiZa-seven-segment-count-part1/editel?sharecode=vG5uMc3atoVj3arptUi8D7p_fGtIZmHsku-pPS9-IcI)

