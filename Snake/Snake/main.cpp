/*
Title: Snake_Game
Author: Guillermo Gomez Sanchez
Feat: ChatGPT & Guiris de Stackoverflow
Documentation: https://stackoverflow.com/questions/12183008/how-to-use-enums-in-c
               https://stackoverflow.com/questions/6442328/what-is-the-difference-between-define-and-const
               https://github.com/KaranJagtiani/Snake-Game-in-CPP
               https://github.com/leimao/Console-Snake/
               https://www.youtube.com/watch?reload=9&time_continue=5038&v=AxrQje7V65o // Este me ha servido de inspiracion para el tema de que a serpiente aparezca en el otro lado de la pantalla
*/

#define FRAME_RATE 15 // mas pequeño == mas fps == mas rapido todo

#include <iostream> // libreria para el input y output de datos
#include <thread> // se utiliza desde la "base" proporcionada por el profesor para la funcionalidad de refrescar la pantalla
#include <chrono> // para poder utilizar valores numericos de tiempo (horas, minutos, segundos...)
#include "keyboard.h" // header de control del teclado proporcionado por el profesor
#include "Engine.h"

using namespace std; // para evitar tener que poner " std:: " al principio del uso de cualquier libreria STANDARD


int main() {


    bool bGameOver = false; // declaramos el estado de false al boolean que funciona para el BUCLLE no para la partida

    while (!bGameOver) { // mientras ese boolean no se modifique...

        gameStartDraw(); // dibujamos el tablero, la serpiente y todo lo que se cante

        userInput(); // manejamos el input del usuario para que por cada iteracion de este bucle se actualice posteriormente }
        /*EL ORDEN DE ESTOS TIENE QUE SER ASI PORQUE SINO NO FUNCIONA*/
        gameLogic(); // actualizamos la logica del juego para que con el siguente frame se actualice todo de manera correcta }

        //Sleep main thread to control game speed execution
        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_RATE));
        if (gameOver) {
            bGameOver = true;
        }
    }

    return 0; // Añadido para corregir el estándar de retorno de main.
}