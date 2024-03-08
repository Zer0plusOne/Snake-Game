#define FRAME_RATE 15

#include <iostream> // libreria para el input y output de datos
#include <thread> // se utiliza desde la "base" proporcionada por el profesor para la funcionalidad de refrescar la pantalla
#include <chrono> // para poder utilizar valores numericos de tiempo (horas, minutos, segundos...)
#include "keyboard.h" // header de control del teclado proporcionado por el profesor

using namespace std; // para evitar tener que poner " std:: " al principio del uso de cualquier libreria STANDARD

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN }; // definimos los posibles movimientos de la serpiente
Direction dir = STOP; // dejamos la direccion en STOP desde este momento para que l aserpiente se empiece a mover desde que el usuario presione "W, A, S o D"

const int ancho = 20; // defino el ancho del tablero
const int altura = 20; // defino la altura del tablero
int x, y, fruitX, fruitY, punt; // variables necesarias para la posicion general, posicion de la fruta y la puntuacion
int tailX[100], tailY[100]; // no utilizo vectores porque segun el tamaño total del tablero la serpiente puede tener un valor maximo
int nTail = 0; // valor inicial (valores de la cola) de las "x" que van detras de la inicial
bool gameOver = false; // para el bucle jugable del juego (si es "TRUE" inica el final del juego) [ESTO ES SOLO LA INICIALIZACION DE LA VARIABLE]

void gameSetup() {

    /* las variables que no se inicializan aqui es porque han sido inicializadas anteriormente */


    x = ancho / 2; // para que la posicion inicial de la serpiente sea el medio del tablero (eje x)
    y = altura / 2; // para que la posicion inicial de la serpiente sea el medio del tablero (eje y)
    fruitX = rand() % ancho; // posición aleatoria de la fruta (eje X)
    fruitY = rand() % altura; // posicion aleatoria de la fruta (eje Y)
    punt = 0; // iniciamos la variable almacenando el valor 0 (anteriormente estaba vacia)
}

void gameStartDraw() {

    system("cls"); // Limpia la consola
    for (int i = 0; i < ancho + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < ancho; j++) {
            if (j == 0)
                cout << "|";
            if (i == y && j == x)
                cout << "X "; // Añade un espacio extra para la serpiente
            else if (i == fruitY && j == fruitX)
                cout << "O "; // Añade un espacio extra para la fruta
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "x "; // Añade un espacio extra para la cola
                        print = true;
                    }
                }
                if (!print)
                    cout << "  "; // Añade dos espacios para las celdas vacías
            }
            if (j == ancho - 1)
                cout << "|";
        }
        cout << endl;
    }

    for (int i = 0; i < ancho + 2; i++)
        cout << "-";
    cout << endl;

    cout << "Score: " << punt << endl;
}

void Input() {
    if (IsAPressed()) dir = LEFT;
    else if (IsDPressed()) dir = RIGHT;
    else if (IsWPressed()) dir = UP;
    else if (IsSPressed()) dir = DOWN;
}

// Añadir aquí las variables globales y la inicialización del juego (ver ejemplos anteriores)
void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x >= ancho) x = 0; else if (x < 0) x = ancho - 1;
    if (y >= altura) y = 0; else if (y < 0) y = altura - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        punt += 10;
        fruitX = rand() % ancho;
        fruitY = rand() % altura;
        nTail++;
    }
}

int main() {
    gameSetup(); // Inicializar el juego

    bool bGameOver = false;

    while (!bGameOver) {
        gameStartDraw(); // Dibujar el tablero y la serpiente
        Input(); // Manejar la entrada del usuario
        Logic(); // Actualizar la lógica del juego

        //Sleep main thread to control game speed execution
        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_RATE));

        if (gameOver) bGameOver = true; // Actualizar la condición de terminación basada en la lógica del juego
    }

    return 0; // Añadido para corregir el estándar de retorno de main.
}
