// C++ code
//
// SPD PRIMER PARCIAL, PARTE 2
// Braian Catriel Gatto, 2023

// ---------------------------------------- //

// 0. reemplazo valores por nombres especificos sin usar espacio de memoria
#define A 10
#define B 11
#define C 5
#define D 6
#define E 7
#define F 9
#define G 8

#define ALLOFF 0

#define UP 3
#define DOWN 2

#define DEBOUNCE 10

#define TEN A5
#define ONE A4

#define SLIDER 13

#define SENSORT A3

// ---------------------------------------- //

// 1. defino variables
int countDigit = 0;

// banderas para cada estado. 1 == no presionado (valor por defecto); 0 == presionado
int upBtn = 1;
int upBtnPreview = 1; /* almacena el estado anterior de los botones para comparar y
                   determinar si se presionó el botón */
int downBtn = 1;
int downBtnPreview = 1;

int sliderSwt = 1; // abajo está por defecto en 1

// sensor de temperatura TMP
float temp = 0;

// ---------------------------------------- //

// 2. establezco la configuración principal
void setup()
{
    /* si uso INPUT acá para los botones, cuando está conectado a 5V lee True y cuando
     está conectado a 0V lee False. Pero si no está conectado, devuelve valores
     randoms alternando entre 1 y 0. Así que es mejor usar la resistencia pull-up
     interna de Arduino para evitar este tipo de ruido */

    pinMode(DOWN, INPUT_PULLUP);
    pinMode(UP, INPUT_PULLUP);
    pinMode(SLIDER, INPUT_PULLUP);

    pinMode(C, OUTPUT);
    pinMode(D, OUTPUT);
    pinMode(E, OUTPUT);
    pinMode(F, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(TEN, OUTPUT);
    pinMode(ONE, OUTPUT);

    Serial.begin(9600);
}

// ---------------------------------------- //

// 3. declaro función bucle principal
void loop()
{
    // declaro variable int que almacena lo que me devuelva la función keypressed()
    int pressedState = keypressed();

    if (pressedState == UP) // si keypressed() me devuelve UP / si el upBtn ha sido apretado...
    {
        countDigit++; // subir en (1) el valor del contador
        Serial.println(countDigit);
    }
    else if (pressedState == DOWN)
    {
        countDigit--; // bajar en (1) el valor del contador
        Serial.println(countDigit);
    }

    // verifico y corrijo en los extremos -1 y 100
    if (countDigit < 0)
    {
        countDigit = 99;
        Serial.println(countDigit);
    }
    else if (countDigit > 99)
    {
        countDigit = 0;
        Serial.println(countDigit);
    }
    printCount(countDigit);

    getTemp(); // obtener temperatura

    Serial.println(temp, 1); // escribo "1" como segundo argumento para solo mostrar un solo dígito después de la coma
                             // muestro el valor del contador en el display
}

// ---------------------------------------- //

// 4. declaro función para prender y apagar leds internos de los displays

void printDigit(int digit) // la función espera valores entre 0 y 9
{

    // controlo los leds
    // PRIMERO, APAGO TODOS
    turnOffDisplay();

    // SEGUNDO, PRENDO SEGÚN EL CASO

    switch (digit)
    {
    case 1:
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        break;
    case 2:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(G, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(D, HIGH);
        break;
    case 3:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(G, HIGH);
        break;
    case 4:
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        break;
    case 5:
        digitalWrite(A, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        break;
    case 6:
        digitalWrite(A, HIGH);
        digitalWrite(G, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        break;
    case 7:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        break;
    case 8:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;
    case 9:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;
    case 0:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        break;
    }
}

// ---------------------------------------- //

// 5. declaro función para detectar si se han apretado los botones (para evitar que al mantener el botón se modifique infinitamente el contador)
int keypressed(void) // devuelve algo pero no espera ningún argumento

{
    // el valor del botón se establece según las variables
    upBtn = digitalRead(UP);
    downBtn = digitalRead(DOWN);
    sliderSwt = digitalRead(SLIDER); // leer estado del slider

    // comprobar estado de botones

    // NO PRESIONADO
    if (upBtn)
    {
        upBtnPreview = 1;
        /* si se lee el pin y me devuelve True (que significa que el botón
        NO está siendo presionado), el estado anterior del botón
        queda en True, o sea, que NO está presionado. Se repite abajo la misma lógica.
        Si no presione nada, el estado anterior es NO PRESIONADO*/
    }
    if (downBtn)
    {
        downBtnPreview = 1;
    }

    /* a continuación, si se lee el pin y me devuelve False (que significa
    que el botón está siendo presionado) al mismo tiempo que
    se lee el pin y me devuelve un valor diferente al estado anterior del botón (lo que
    significa que en la iteración anterior el botón UP no estaba presionado),
    entonces el estado anterior del botón se reemplaza por el estado actual (lo que
    significa decir que ahora el UP está siendo apretado),
    y me devuelve UP para ser usado posteriormente */

    // PRESIONADO

    if (upBtn == 0 && upBtn != upBtnPreview) /*si se presiona el botón y su valor actual
                                             es distinto al valor anterior...*/
    {
        upBtnPreview = upBtn; // el estado anterior es mi estado actual
        return UP;            // devuelve la info (en este caso 3) de que el botón ha sido apretado
    }
    if (downBtn == 0 && downBtn != downBtnPreview)
    {
        downBtnPreview = downBtn;
        return DOWN; // devuelve 2
    }

    return 0; // si no se toca nada, devuelve False
}

// ---------------------------------------- //

// 6. declaro función para controlar la visualización de los displays
void turnDigitOn(int digit)
{
    /* según que digitos (de ahí el parámetro) han de encenderse,
    los de la unidad o los de la decena, se desarrolla la función */

    if (digit == ONE) // si el argumento que se pasa es A4 / la unidad...
    {
        digitalWrite(ONE, LOW);  // prendo unidad (o sea, lo coloco en 0)
        digitalWrite(TEN, HIGH); // apago decena
        delay(DEBOUNCE);         /* delay que evita el 'rebote' de los inputs, es decir
                                ese efecto fantasma que aparece en los displays*/
    }
    else if (digit == TEN)
    {
        digitalWrite(ONE, HIGH);
        digitalWrite(TEN, LOW);
        delay(DEBOUNCE);
    }
    else // acá después vamos a pasarle ALLOFF para apagar los displays
    {
        digitalWrite(ONE, HIGH);
        digitalWrite(TEN, HIGH);
    }
}

// ---------------------------------------- //

// 7. declaro función para mostrar decenas y unidades secuencialmente
void printCount(int count)
{
    if (sliderSwt) // si el slider está en CONTADOR
    {
        turnDigitOn(ALLOFF);                        // apago display
        printDigit(count / 10);                     // obtengo el valor de la decena (me agarra solo el entero)
        turnDigitOn(TEN);                           // prendo la decena
        turnDigitOn(ALLOFF);                        // apago display
        printDigit(count - 10 * ((int)count / 10)); // obtengo el valor de la unidad
        turnDigitOn(ONE);                           // prendo la unidad
    }
    else // si el slider está en PRIMOS
    {
        bool isPrime = primeDetect(countDigit); // declaro variable bool que me guarda lo que me devuelve la función primedetect por medio del contador
        turnDigitOn(ALLOFF);                    // apago display

        if (isPrime && countDigit != 0) // si ES primo y el contador no es 0
        {
            turnDigitOn(ALLOFF);                        // apago display
            printDigit(count / 10);                     // obtengo el valor de la decena (me agarra solo el entero)
            turnDigitOn(TEN);                           // prendo la decena
            turnDigitOn(ALLOFF);                        // apago display
            printDigit(count - 10 * ((int)count / 10)); // obtengo el valor de la unidad
            turnDigitOn(ONE);                           // prendo la unidad
        }
    }
}

// ---------------------------------------- //

// 8. declaro función para determinar primos
bool primeDetect(int digit)
{
    bool isPrime = true; // lo dejo adentro para que se restablezca

    for (int i = 2; i < digit; i++)
    {
        if (digit % i == 0)
        {
            isPrime = false;
            break; // como se encontró un divisor adicional, n != primo
        }
    }

    return isPrime;
}

// ---------------------------------------- //

// 9. declaro función para apagar todos los displays
void turnOffDisplay()
{
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
}

// ---------------------------------------- //F

// 10. declaro función obtener temperatura
float getTemp()
{
    temp = map(analogRead(SENSORT), 0, 1023, -5000, 45000); // convertir a C°
    /* map funciona de la siguiente forma:
          leer valores del A3,
          0 es el valor inicial del rango analogico
          1023 es el valor final del rango analogico
          -5000 es el nuevo valor inicial del rango para pasar a C°
          45000 es el nuevo valor final del rango para pasar a C°
          */
    temp = temp / 100.00; // dar un valor más cercano al original
}
