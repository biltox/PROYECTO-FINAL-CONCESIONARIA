#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <locale.h>

// librerias
#include "./lib/autos.h"
#include "./lib/personal.h"
#include "./lib/utilidades.h"
#include "./lib/gotoxy.h"

// Archivos
#define ARCHIVO_PERSONAL "./archivos/personal.bin"
#define ARCHIVO_AUTOS "./archivos/autos.bin"


//


int main()
{
//    system("mode con: cols=120 lines=30");
    setlocale(LC_ALL, "es_ES");
    desactivarMaximizar();
    inicioSesion();

    stPersonal persona;
    strcpy(persona.nombre, "Juan Vendedor");


//    menuVendedor_homePage(persona);




    printf("\n\n                Fin Programa\n");
    return 0;
}

















