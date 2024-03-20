# Snake-Game
Juego clasico del Snake hecho como practica entregable del modulo de programacion de ASIX-Ciberseguridad de ENTI-UB
## Características

- Control del movimiento de la serpiente usando las teclas W, A, S, D.
- El juego termina cuando la serpiente choca consigo misma.
- Cada fruta consumida por la serpiente aumenta su longitud y la puntuación del jugador.

## Requisitos Previos

Para compilar y ejecutar este juego, necesitarás:

- Compilador de C++ que soporte C++11 o superior (GCC, Clang, MSVC)
- Sistema operativo Windows (debido al uso de la biblioteca `<Windows.h>` para la detección de teclas)

## Cómo Compilar y Ejecutar

1. Clona este repositorio o descarga los archivos fuente.
2. Abre un terminal o línea de comandos en el directorio del proyecto.
3. Compila el proyecto usando tu compilador de C++. Por ejemplo, si estás usando GCC, puedes usar el siguiente comando:

    ```bash
    g++ main.cpp Engine.cpp keyboard.cpp -o snake_game
    ```

4. Ejecuta el juego:

    ```bash
    ./snake_game
    ```

## Cómo Jugar

- Al iniciar el juego, la serpiente comenzará en el centro del tablero.
- Usa las teclas W (arriba), A (izquierda), S (abajo) y D (derecha) para controlar la dirección de la serpiente.
- Trata de comer tantas frutas como sea posible sin chocar con los bordes del tablero o con la cola de la serpiente.

## Contribuir

Si te interesa contribuir a este proyecto, por favor, considera:

- Reportar errores
- Sugerir nuevas características
- Mejorar el código existente

## Créditos

- Guillermo Gomez Sanchez: Desarrollador principal
- ChatGPT & Giris de StackOverflow: Por proporcionar inspiración y soluciones a problemas específicos.

## Licencia

Este proyecto está licenciado bajo [GPL-3.0] . Para más detalles, ver el archivo LICENSE.
