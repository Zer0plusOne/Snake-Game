#pragma once

#include <iostream> // libreria para el input y output de datos
#include <thread> // se utiliza desde la "base" proporcionada por el profesor para la funcionalidad de refrescar la pantalla
#include <chrono> // para poder utilizar valores numericos de tiempo (horas, minutos, segundos...)
#include "keyboard.h" // header de control del teclado proporcionado por el profesor

using namespace std; // para evitar tener que poner " std:: " al principio del uso de cualquier libreria STANDARD

const enum Direction { STOP = 0, IZQ, DER, UP, DOWN }; // definimos los posibles movimientos de la serpiente (se utiliza enum para poder utilizar un switch case mas adelante) && (utilizo const para poder trabajar con lo interior)
Direction dir = STOP; // dejamos la direccion en STOP desde este momento para que la serpiente se empiece a mover desde que el usuario presione "W, A, S o D"

const int ancho = 20; // defino el ancho del tablero    \
                                                         -Utilizo constantes ya que sino no se me permite operar con ellas mas adelante (#define no me deja utilizarlos como valores dentro de operacoines)
const int altura = 10; // defino la altura del tablero  /

/* Variables para la serpiente */
int tailX[ancho * altura], tailY[ancho * altura]; // no utilizo vectores porque segun el tamaño total del tablero la serpiente puede tener un valor maximo (en este caso al ser 20*10, su tamaño maximo sera de 200)
int numberTail = 0; // valor inicial (valores de la cola) de las "x" que van detras de la Mayuscula

/* Variables para el desarrollo del juego */

int x = ancho / 2; // para que la posicion inicial de la serpiente sea el medio del tablero (eje x)
int y = altura / 2; // para que la posicion inicial de la serpiente sea el medio del tablero (eje y)
int fruitX = rand() % ancho; // posición aleatoria de la fruta (eje X)
int fruitY = rand() % altura; // posicion aleatoria de la fruta (eje Y)
int punt = 0;
bool gameOver = false;


void bordesSuperiorInferior() {

    for (int i = 0; i < ancho * 2 + 1; i++) { // idicamos que queremos rellenar de guiones la parte superior de manera que mientras i sea menor al doble + 1 del ancho (recordemos que hemos rellenado de *2* espacios el tablero)
        cout << "-"; // rellena con guiones
    }
}

void gameStartDraw() {

    system("cls"); // para dar la ilusion de la pantalla se actualiza en directo y no parezca una novela grafica

    bordesSuperiorInferior();

    cout << endl; // saltito de linia necesario para que no se junte con el tablero para luego no molestar a la hora de rellenar los bordes

    for (int i = 0; i < altura; i++) { // bucle para toquetear cada fila del tablero
        for (int a = 0; a < ancho; a++) { // siempre que  "a" (no puedo usar i porque ya esta usada y estoy dentro de su bucle) sea menor al ancho...
            if (a == 0) { // cuando a sea igual a 0
                cout << "|"; // el valor de indice 0 de cada linia sera rellenado con el caracter "pipe" GRACIAS RAFALAGOON POR TUS ENSEÑANZAS
            }
            if (i == y && a == x) { // si i y a son iguales a la posicion de la cabeza de la serpiente...
                cout << "X "; // imprimo el caracter "X" y añado un espacio extra para la serpiente
            }
            else if (i == fruitY && a == fruitX) { // si i y a son iguales a las coordenadas de la posicion de la fruta...
                cout << "O "; // dubujamos la frutita con un espacio igual porque sino sale torcida si te mueves cerca de ella
            }
            else { // siempre que  "a" (no puedo usar i porque ya esta usada y estoy dentro de su bucle) NO sea menor al ancho...
                bool cola = false; // declaramos una variable que se encargara de comprovar si la cola esta donde debe de estar
                for (int b = 0; b < numberTail; b++) { // para toquetear el tablero pero en este caso para ver donde se pone la cola de la serpiente
                    if (tailX[b] == a && tailY[b] == i) { // si la coodenada de la cola en x y y es igual...
                        cout << "x "; // imprimimos el valor de la cola (una X pero minuscula)
                        cola = true; // terminamos de imprimir por ahora ya que no hay nada que nos indique que necesitamos imprimir mas colas
                    }
                }
                if (!cola) { // en caso de que la cola este en false...
                    cout << "  "; // añado dos espacios al final
                }
            }
            if (a == ancho - 1) { // imprimimos el borde derecho
                cout << "| "; // caracter del bode derecho
            }
        }
        cout << endl;// terminamos linia porque sino imprimiria la siguiente al lado y no abajo
    }

    bordesSuperiorInferior();

    cout << endl; // damos un espacio de linia despues del bucle for ya que sino la puntuacion la junta con la linia inferior (motivos esteticos)

    cout << "Puntuacion: " << punt << endl; // puntuacion que imprime tambien el valor hasta el momento de la variable "punt" 
}

void userInput() { // funcion para los imputs del usuario usando ' keyboard.h '

    if (IsWPressed()) { // no hace falta que comente que hace, simplemente le damos a WASD los valores "estandard" de movimiento
        dir = UP;
    }
    else if (IsSPressed()) {
        dir = DOWN;
    }
    else if (IsAPressed()) {
        dir = IZQ;
    }
    else if (IsDPressed()) {
        dir = DER;
    }
}

// logica del juego ( *IMPORTANTE*  RECUERDA QUE ESTO ESTARA DENTRO DE UN BUCLE WHILE, ASI QUE NO HACE FALTA TRABAJAR DENTRO DE UN BUCLE)
void gameLogic() {


    /* serpiente inicial */

    int colitaX = tailX[0]; // variable para inicializar la posicion de la cola de la serpiente (la serpiente) en el eje X
    int colitaY = tailY[0]; // variable para inicializar la posicion de la cola de la serpiente (la serpiente) en el eje y

    /* serpiente in game */

    int colita2X, colita2Y; // inicializamos las variables que serviran para almacenar las coordenadas previas de los segmentos de la cola mientras esta se mueve
    tailX[0] = x; // para que coincida con la posicion actual del movimiento con la impresion de la serpiente en el eje x
    tailY[0] = y; // para que coincida con la posicion actual del movimiento con la impresion de la serpiente en el eje y

    for (int i = 1; i < numberTail; i++) { // iteramos cada segmento de la serpiente (menos el de incide 0 porque es la cabeza)
        colita2X = tailX[i]; // actualizamos segun la direccion en la que se encuentre en ese frame en el eje X
        colita2Y = tailY[i]; // actualizamos segun la direccion en la que se encuentre en ese frame en el eje Y
        tailX[i] = colitaX; // justo despues realizamos lo mismo pero para toda la cola en el eje X
        tailY[i] = colitaY; // justo despues realizamos lo mismo pero para toda la cola en el eje X
        colitaX = colita2X;
        colitaY = colita2Y;
    }
    switch (dir) { // iniciamos un switch (es lo mejor que se me ha ocurrido) para las direcciones, indicando que pasa cuando la variable "dir" esta en alguno de los casos de abajo

    case UP:
        y--; // en caso de ir arriba se movera en negativo en relacion al tablero (alto)
        break;
    case DOWN:
        y++; // en caso de ir abajo se movera en positivo en relacion al tablero (alto)
        break;
    case IZQ:
        x--; // en caso de ir a la derecha se movera en negativo en relacion al tablero (ancho)
        break;
    case DER:
        x++; // en caso de ir a la izquierda se movera en positivo en relacion al tablero (ancho)
        break;

    }

    /* ESTE BLOQUE ESTABA HECHO PARA DEBUG, ELIMINARLO O COMENTARLO DEBERIA SUPONER QUE LA SERPIENTE MUERA AL TOCAR LOS BORDES DE LA PANTALLA */

    // BLOQUE DE DEBUG: este bloque (porque me has dicho que lo deje Alex) es lo que hace que la serpiente en caso de entrar en el borde de la pantalla salga por el lado opuesto, a continuacion comento lo que hace cada cosa.
    
    if (x >= ancho) { // en caso de que la coordenada X sea mayor o igual al ancho del tablero...
        x = 0; // cambiamos la coordenada X por un 0
    }
    else if (x < 0) { // en caso de que la coordenada x sea menor a 0 (indica que ha intentado salir por el lado izquierdo)...
        x = ancho - 1; // la coordenada cambia por el ancho total del tablero -1 (ya que el total indica que es el borde)
    }
    if (y >= altura) { // en caso de que la coordenada X sea mayor o igual a la altura del tablero...
        y = 0; // cambiamos la coordenada Y por un 0
    }
    else if (y < 0) { // en caso de que la coordenada Y sea menor a 0 (indica que ha intentado salir por arriba)...
        y = altura - 1; // // la coordenada cambia por la altura total del tablero -1 (ya que el total indica que es el borde)
    }

    
    /* Descomentar este codigo deberia hacer que cuando la serpiente toque un borde muera
    
        if (x >= ancho) { // en caso de que la coordenada X sea mayor o igual al ancho del tablero...
        gameOver = true; // Se muriooooo
    }
    else if (x < 0) { // en caso de que la coordenada x sea menor a 0 (indica que ha intentado salir por el lado izquierdo)...
        gameOver = true; // Se muriooooo
    }
    if (y >= altura) { // en caso de que la coordenada X sea mayor o igual a la altura del tablero...
        gameOver = true; // Se muriooooo
    }
    else if (y < 0) { // en caso de que la coordenada Y sea menor a 0 (indica que ha intentado salir por arriba)...
        gameOver = true; // Se muriooooo
    }
    
    */



    // este bucle comprueba por cada frame que las coordenadas de la cabeza y de la cola no coincidan en ningun punto, en caso de hacerlo...
    for (int i = 0; i < numberTail; i++) {
        if (tailX[i] == x && tailY[i] == y) { // en caso de que las coordenadas de la cabeza coincidan con alguna de las posiciones en la cola...
            gameOver = true; // cambiamos el valor a true del boolean que indica el GAME OVER
        }
    }
    // este bucle for se indica a comparar las coordenadas de la cabeza y la fruta en el tablerom en caso de coincidir...
    if (x == fruitX && y == fruitY) { // si las coordenadas en X y Y coinciden entre la fruta y la cabeza de la serpiente...
        punt += 10; // se le suman 10 puntos a la variable que almacena la puntuacion
        fruitX = rand() % ancho; // se generan nuevas coordenadas en el eje X para la fruta
        fruitY = rand() % altura; // se generan nuevas coordenadas en el eje Y para la fruta
        numberTail++; // se suma 1 caracter mas a la cola de la serpiente
    }
}
