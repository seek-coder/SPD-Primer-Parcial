# PRIMER PARCIAL SPD - BRAIAN CATRIEL GATTO
![ArduinoTinkercad](https://github.com/seek-coder/SPD-Primer-Parcial/assets/130781541/7484325e-8708-4f26-8f15-d5f662a15d8a)

## INTEGRANTES DEL GRUPO PARA PARTES 1 Y 2
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
La función que se encarga de la lógica principal del programa, ```loop()``` ha de ser la función más importante del mismo, porque define la lógica que se itera todo el programa. A partir de ahí, se comprueban valores que permiten incrementar, decrementar o reiniciar el contador general. Sin embargo, hay que hacer notar que la función ```printCount()``` es prácticamente igual de relevante, no sólo porque me permite mostrar unidades y decenas secuencialmente sino porque el bucle inicial depende de sus resultados. Con el fin de obviar la relevancia del bucle inicial (con el cual ningún código de Arduino funcionaría realmente), determinaremos la función ```printCount()``` como la principal. 
La _estructura básica_ de la función es la siguiente:
  1) se apagan los displays
  2) se obtiene el valor de la decena mediante la división del entero count por diez (por ejemplo, si el numero es 23 me quedo con la parte entera al dividir, que es 2) y se prende la decena
  3) se apagan los displays
  4) se obtiene el valor de la unidad mediante el calculo del entero count menos diez por el parseo del cálculo anteriormente mencionado  (por ejemplo, si el numero es 23 me quedo con la parte de la unidad) y se prende la decena
```python3
void printCount(int count) 
{
  turnDigitOn(ALLOFF);
  printDigit(count/10);
  turnDigitOn(TEN);
  turnDigitOn(ALLOFF);
  printDigit(count - 10 * ((int)count/10));
  turnDigitOn(ONE);
}
```
## III. LINK AL PROYECTO
[SPD - Primer parcial - Proyecto de Arduino, Parte1](https://www.tinkercad.com/things/bEkxNiuQiZa)
##
## PROYECTO - PARTE 2: Modificador con interruptor deslizante y números primos + sensor de temperatura
![Sin título](https://github.com/seek-coder/SPD-Primer-Parcial/assets/130781541/b6f40232-5ccb-44e2-b346-1e536ab64746)

### I. DESCRIPCIÓN:
A la parte (1) le hemos agregado un interruptor deslizante que funciona de manera tal que deslizado hacia abajo permite mostrar secuencialmente todos los números del contador de la misma forma que hacía el anterior programa y deslizado hacia arriba muestra en el display únicamente aquellos números que sean primos, es decir, que sólo sean divisibles entre 1(uno) y sí mismo. Para esto se declaró una nueva función de nombre  ```primeDetect()```.

Además, se ha añadido un [sensor de temperatura](https://cursos.mcielectronics.cl/2022/08/01/como-utilizar-el-sensor-de-temperatura-tmp36-tutorial-de-arduino/) que funciona transcribiendo mediante un mapeo la información del tipo analógica que reciba a grados celsius. Para esto se declaró una nueva función de nombre  ```getTemp()```.

### II. FUNCIÓN PRINCIPAL
La función que resulta más relevante en el sentido de las nuevas modificaciones es la de  ```primeDetect()``` porque cambia rotundamente el enfoque del display, trabajando ahora en dos modos: uno de numeros enteros y otro de numeros primos.
La _estructura básica_ de la función es la siguiente:
  1) se declara una variable del tipo booleana y se especifica como 'true' sólo con fines demostrativos (se podría simplemente declarar sin igualarla a true)
  2) se inicia un bucle 'for' que evalua si el entero pasado a la función tiene más de dos divisores aparte de 1(uno) y de sí mismo. Si es así, se devuelve 'isPrime' como falsa y se rompe el bucle porque ya al tener un divisor adicional el número deja de ser primo.
  3) si no se encuentran divisores adicionales, el numero es en efecto primo
  4) se devuelve el valor de falsedad o verdad de la variable 'isPrime'
  5) en base a los resultados, se prenderán o apagarán los displays en el modo de números primos
 ```python3
bool primeDetect(int digit)
{
  bool isPrime = true;
  
  for(int i = 2; i < digit; i++)
  {
    if (digit % i == 0)
    {
      isPrime = false;
      break;
    }
  }
  
  return isPrime;
}
 ```
### III. LINK AL PROYECTO
[SPD - Primer parcial - Proyecto de Arduino, Parte2](https://www.tinkercad.com/things/cFFcPNF4vUZ)

### IV. SUGERENCIA DE COMPONENTE ADICIONAL
![image](https://github.com/seek-coder/SPD-Primer-Parcial/assets/130781541/87377c12-3684-44a5-8d99-e1ad2e115966)


Se podría agregar al proyecto un [motor de aficionado](https://techmake.com/blogs/tutoriales/empezando-con-arduino-5a-motores-dc) que permita controlar, por ejemplo, ruedas integradas al Arduino de manera tal que pueda moverse por una zona e ir detectando las diferentes variaciones de temperaturas de la misma. Para controlar un motor de corriente continúa con Arduino, generalmente se utiliza un puente H (H-bridge) o un módulo de control de motor.

Video explicativo (no es de nuestra autoría): [Control de motor de aficionado](https://youtu.be/srCOkz9Xgco)

##
## PROYECTO - PARTE 3: Modificación según el Último Número de Documento (0-3, fotorresistencia)
![image](https://github.com/seek-coder/SPD-Primer-Parcial/assets/130781541/a748d4da-e288-4423-aca2-fc705ff56156)

### I. DESCRIPCIÓN:
A la parte (2) le agregué una [fotorresistencia](https://blog.330ohms.com/2020/05/16/como-conectar-una-fotoresistencia-ldr-a-arduino/) que no es más que un componente cuya resistencia disminuye o aumenta en función a la intensidad de luz que incide sobre ella.

Armamos un divisor de voltaje para pasar las variaciones de intensidad de luz a variaciones de tensión: desde la terminal n°1 alimentamos con 5V al componente y desde la terminal n°2 sacamos un cable hacia el primer polo de una resistencia de 10kΩ. El primer polo se conecta a la vez a la entrada analógica, y el otro polo se conecta a GND. La señal entonces se toma del punto de conexión entre la fotorresistencia y la resistencia de 10kΩ. En este caso el componente devuelve valores entre 1 (que corresponde a 264mV) y 974 (que corresponde a 4,76V) que significa el rango de valores de resistencia proporcional a la cantidad de luz que incide sobre la fotorresistencia. Mientras más luz haya, menos es el valor de la resistencia.

Con fines demostrativos, agregué una función que refiere a un LED que se apaga llegada a media intensidad de luz. Se hace una lectura analógica del valor del pin de la fotorresistencia y en función de él se apaga o no el LED.

### II. LINK AL PROYECTO
[SPD - Primer parcial - Proyecto de Arduino, Parte3](https://www.tinkercad.com/things/k21l70HxwcG)
