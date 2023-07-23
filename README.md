# Pacman en OpenGL y C++ 
¡Bienvenido al juego de Pacman desarrollado en OpenGL y C++! En este proyecto, hemos creado una versión parecida al clásico juego de Pacman con gráficos en 3D utilizando OpenGL y programación en C++. A continuación, encontrarás información esencial sobre el juego, cómo compilarlo y ejecutarlo, y algunas características clave.

## 1. Características del juego:

* Pacman y Fantasmas: El jugador controla a Pacman, el icónico personaje amarillo que debe recolectar todas las bolitas (o puntos) en el laberinto mientras evita ser capturado por los fantasmas. Los fantasmas se mueven para atrapar a Pacman.

* Power-ups: Además de las bolitas normales, hay Power-ups especiales que aparecen en puntos específicos del laberinto. Al comer un Power-up, Pacman obtiene temporalmente la habilidad de crecer y asi poder comer a los fantasmas, lo que le da una ventaja estratégica.

* Obstaculos: Además de los power-ups, se presentaran algunos obstaculos que apareceran en el laberinto. Al comer uno de ellos el Pacman temporalmente se encojera, y si en caso un fantasma te come estando durante el efecto de este obstaculo, perderas todas tus vidas.

* Niveles y Laberintos: El juego cuenta con tres niveles, en cada nivel se presentara un laberinto con diseño único. A medida que avanzas en el juego, los laberintos se vuelven más complicados y se iran mostrando los power-ups u obstaculos.

* Puntuación y Vidas: El jugador gana puntos por cada bolita recolectada y por comerse a los fantasmas después de comer un Power-up. Además, Pacman tiene un número limitado de vidas, y el juego termina si se queda sin vidas.

## 2. Requisitos del sistema

* Sistema operativo compatible: Windows, macOS o Linux.
* Tarjeta gráfica que soporte OpenGL 3.3 o superior.
* Compilador de C++.
* Dependencias de OpenGL (GLFW, GLAD, GLEW, etc.). 

## 3. Compilación e Instrucciones de Ejecución

1. Clonar el repositorio: Comienza clonando este repositorio en tu computadora.

        git clone https://github.com/fm1299/Pacman

2. Instalar dependencias: Asegúrate de tener instaladas las dependencias necesarias de OpenGL,

3. Compilar el juego: Utiliza el compilador de C++ para compilar el juego. A continuación, se muestra un ejemplo de cómo compilarlo usando GCC.

        g++ -std=c++11 -o pacman main.cpp -lglfw -lglew -lGL

4. Ejecutar el juego: Una vez compilado correctamente, ejecuta el juego.

        ./main

5. Jugar: Usa las teclas de dirección para mover a Pacman por el laberinto y trata de recolectar todas las bolitas mientras evitas a los fantasmas. ¡Buena suerte!
