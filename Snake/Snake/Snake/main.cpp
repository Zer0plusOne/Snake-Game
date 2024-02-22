#define FRAME_RATE 150

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <keyboard.h>

using namespace std;

vector<char> Snake = { 'x' }; // Declaro el vector que sera la serpiente finalmente
const int X_tableroSize = 20;
const int Y_tableroSize = 20;
const int maxSizeSnake = 400;

void screenClear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printTablero() {

}

void main() {

    bool bGameOver = false;

    //While game is not over execute game loop
    while (!bGameOver) {

        int score = 0; // Inicializamos con la partida el contador de la puntuacion.

        // Caso en el que la serpiente alcanza la puntuacion maxima
        if (snake.size() = maxSizeSnake) { // Comparamos el tamaño del vector que almacena la "serpiente" a el valor fisicamente maximo que puede tener la serpiente dentro del tablero.
            screenClear();
            cout << "CONGRATULATIONS" << endl;
            cout << "You have beated the game with score: "<< score << endl;
            cout << "\n" << endl;
            cout << "Press ENTER to end the game..." << endl;

            string userInput;
            getline(cin, userInput);

            bGameOver = true;
        }

        cout << "a" << endl;
        //Sleep main thread to control game speed execution
        this_thread::sleep_for(chrono::milliseconds(FRAME_RATE));
    }
}