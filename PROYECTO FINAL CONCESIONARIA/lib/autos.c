#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// librerias
#include "./autos.h"
#include "./personal.h"
#include "./utilidades.h"
#include "./gotoxy.h"

// Archivos
#define ARCHIVO_PERSONAL "./archivos/personal.bin"
#define ARCHIVO_AUTOS "./archivos/autos.bin"
#define FILTRAR_PRECIO 1
#define FILTRAR_KM 2
#define FILTRAR_ANIO 3


void mostrarVehiculo(stVehiculo vehiculo)
{
    /*
    printf("\n");
    printf("Marca: %s.\n", vehiculo.marca);
    printf("Modelo: %s.\n", vehiculo.modelo);
    printf("Precio: %.0lf\n", vehiculo.precio);
    printf("KM: %d\n", vehiculo.km);
    printf("A%Co modelo: %d\n",164, vehiculo.anio);
    printf("ID: %d.\n", vehiculo.idAuto);
    printf("Cantidad: %d.\n", vehiculo.cantidad);*/

   printf("\n");
    printf("\t\t\t \t %-5s | %-10s |  %-7.0lf | %-7.0lf |   %d   | %-6d| %d ",vehiculo.marca,vehiculo.modelo,vehiculo.precio,vehiculo.km,(int)vehiculo.anio,vehiculo.idAuto,vehiculo.cantidad);
}
stVehiculo cargarVehiculo()
{
    stVehiculo vehiculo;

    gotoxy(42,11);printf("Agregar todas las caracteristicas del auto... \n");

    gotoxy(42,17);printf("Marca: ");
    fflush(stdin);
    gets(vehiculo.marca);
    gotoxy(42,18);printf("Modelo: ");
    fflush(stdin);
    gets(vehiculo.modelo);
    gotoxy(42,19);printf("Precio: ");
    fflush(stdin);
    scanf("%lf", &vehiculo.precio);
    gotoxy(42,20);printf("KM: ");
    fflush(stdin);
    scanf("%lf", &vehiculo.km);
    gotoxy(42,21);printf("A%co: ",164);
    fflush(stdin);
    scanf("%lf", &vehiculo.anio);
    gotoxy(42,22);printf("Cantidad: ");
    fflush(stdin);
    scanf("%d", &vehiculo.cantidad);

    return vehiculo;
}


// Modelo
nodoModelo* inicModelo()
{
    return NULL;
}

nodoModelo* crearNodoModelo(stVehiculo vehiculo)
{
    nodoModelo* aux = (nodoModelo*) malloc(sizeof(nodoModelo));
    strcpy(aux->modelo, vehiculo.modelo);
    aux->vehiculo = vehiculo;
    aux->siguiente = inicModelo();
    return aux;
}

nodoModelo* agregarModeloAlPrincipio(nodoModelo* listaModelo, stVehiculo vehiculo)
{
    nodoModelo* nuevoModelo = crearNodoModelo(vehiculo);
    if(listaModelo == NULL)
    {
        listaModelo = nuevoModelo;
    }
    else
    {
        nuevoModelo->siguiente = listaModelo;
        listaModelo = nuevoModelo;
    }
    return listaModelo;
}

nodoModelo* agregarModeloEnOrden(nodoModelo* listaModelo, stVehiculo vehiculo)
{
    nodoModelo* nuevoModelo = crearNodoModelo(vehiculo);
    if(listaModelo == NULL)
    {
        listaModelo = nuevoModelo;
    }
    else
    {

        if(strcmpi(nuevoModelo->modelo, listaModelo->modelo) < 0)
        {
            listaModelo = agregarModeloAlPrincipio(listaModelo, vehiculo);
        }
        else
        {
            nodoModelo* iterador = listaModelo;
            nodoModelo* anterior = listaModelo;
            while(iterador != NULL && strcmpi(iterador->modelo, nuevoModelo->modelo) <= 0)
            {
                anterior = iterador;
                iterador = iterador->siguiente;
            }
            anterior->siguiente = nuevoModelo;
            nuevoModelo->siguiente = iterador;
        }
    }
    return listaModelo;
}

void mostrarListaModelo(nodoModelo* listaModelo)
{
    if(listaModelo != NULL)
    {
        mostrarVehiculo(listaModelo->vehiculo);
        mostrarListaModelo(listaModelo->siguiente);
    }
}


// Lista de Autos....

nodoAuto* inicAuto()
{
    return NULL;
}

nodoAuto* crearNodoAuto(stVehiculo vehiculo)
{
    nodoAuto* aux = (nodoAuto*) malloc(sizeof(nodoAuto));

    aux->siguiente = inicAuto();
    aux->listaModelo = crearNodoModelo(vehiculo);
    strcpy(aux->marca, vehiculo.marca);
    return aux;
}

nodoAuto* agregarAutoAlPrincipio(nodoAuto* listaAutos, stVehiculo vehiculo)
{
    nodoAuto* nuevoAuto = crearNodoAuto(vehiculo);
    if(listaAutos == NULL)
    {
        listaAutos = nuevoAuto;
    }
    else
    {
        nuevoAuto->siguiente = listaAutos;
        listaAutos = nuevoAuto;
    }
    return listaAutos;
}

nodoAuto* agregarAutoEnOrden(nodoAuto* listaAutos, stVehiculo vehiculo)
{
    nodoAuto* nuevoAuto = crearNodoAuto(vehiculo);
    if(listaAutos == NULL)
    {
        // No hay ninguna lista de esa marca....
        listaAutos = nuevoAuto;
    }
    else
    {
        if(strcmpi(nuevoAuto->marca, listaAutos->marca) < 0)
        {
            nuevoAuto->siguiente = listaAutos;
            listaAutos = nuevoAuto;
        }
        else
        {
            // tengo que buscar en la lista si hay de esa marca...
            nodoAuto* iteradorMarcas = listaAutos;
            nodoAuto* anterior = listaAutos ;
            while(iteradorMarcas != NULL && strcmpi(nuevoAuto->marca, iteradorMarcas->marca) > 0)
            {
                anterior = iteradorMarcas;
                iteradorMarcas = iteradorMarcas->siguiente;
            }
            // Si existe ya esa marca, lo agrego a la lista....
            if(strcmpi(nuevoAuto->marca, iteradorMarcas->marca) == 0)
            {
                iteradorMarcas->listaModelo = agregarModeloEnOrden(iteradorMarcas->listaModelo, vehiculo);
            }
            else
            {
                nuevoAuto->siguiente = iteradorMarcas;
                anterior->siguiente = nuevoAuto;
            }
        }
    }
    return listaAutos;
}

void mostrarListaAutos(nodoAuto* listaAutos)
{
    if(listaAutos != NULL)
    {
        mostrarListaModelo(listaAutos->listaModelo);
        mostrarListaAutos(listaAutos->siguiente);
    }
}

nodoAuto* cargaAutos()
{
    nodoAuto* listaAutos = inicAuto();
    FILE* archivo = fopen(ARCHIVO_AUTOS, "r+b");
    if(archivo != NULL)
    {
        stVehiculo vehiculo;
        while(fread(&vehiculo, sizeof(vehiculo), 1, archivo) > 0)
        {
            listaAutos = agregarAutoEnOrden(listaAutos, vehiculo);
        }
        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo 'personal', en la función deArchivoAMemoria\n");
    }
    return listaAutos;
}



void guardarListaAutos(nodoAuto* listaAutos)
{
    FILE* archivo = fopen(ARCHIVO_AUTOS, "a+b");
    if(archivo != NULL)
    {
        // recorrer la lista de autos y guardar....
        int contador = 0;
        stVehiculo vehiculoACargar;


        if(listaAutos != NULL)
        {
            nodoAuto* iteradorMarcas = listaAutos;
            while(iteradorMarcas != NULL)
            {
                nodoModelo* iteradorModelos = iteradorMarcas->listaModelo;
                while(iteradorModelos != NULL)
                {

                    vehiculoACargar = iteradorModelos->vehiculo;
                    vehiculoACargar.idAuto = contador;
                    contador++;

                    fwrite(&vehiculoACargar, sizeof(vehiculoACargar), 1, archivo);

                    iteradorModelos = iteradorModelos->siguiente;
                }
                iteradorMarcas = iteradorMarcas->siguiente;
            }
        }

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo en guardarListaAutos()");
    }
}

nodoModelo* buscarNodoAuto(nodoAuto* listaAutos, int idAutoBuscado)
{
    nodoModelo* autoAModificar = inicModelo();
    if(listaAutos != NULL)
    {
        nodoAuto* iteradorMarcas = listaAutos;
        while(iteradorMarcas != NULL  && autoAModificar == NULL)
        {
            nodoModelo* iteradorModelos = iteradorMarcas->listaModelo;
            while(iteradorModelos != NULL && autoAModificar == NULL)
            {
                if(iteradorModelos->vehiculo.idAuto == idAutoBuscado)
                {
                    autoAModificar = iteradorModelos;
                }
                iteradorModelos = iteradorModelos->siguiente;
            }
            iteradorMarcas = iteradorMarcas->siguiente;
        }
    }
    return autoAModificar;
}

nodoAuto* removerAuto(nodoAuto* listaAutos,int idAutoBuscado, int* removido)
{
    FILE* archivo = fopen(ARCHIVO_AUTOS, "r+b");
    listaAutos = inicAuto();
    if(archivo != NULL)
    {
        stVehiculo vehiculo;
        while(fread(&vehiculo, sizeof(vehiculo),1, archivo) >0)
        {
            if(vehiculo.idAuto != idAutoBuscado)
            {
                listaAutos = agregarAutoEnOrden(listaAutos, vehiculo);

            }
            else
            {
                (*removido) = 1;
            }
        }
        fclose(archivo);
    }
    else
    {
        printf("Error al remover el auto.\n");
    }
    return listaAutos;
}


// Usos para el vendedor

// Por marcas
void mostrarMarcasDisponibles(nodoAuto* listaAutos)
{
    if(listaAutos != NULL)
    {
        printf("\t\t\t\t\t\t  %s\n", listaAutos->marca);
        mostrarMarcasDisponibles(listaAutos->siguiente);
    }
}

nodoModelo* filtroMarca(nodoAuto* listaAutos,char marca[])
{
    nodoAuto* iterador = listaAutos;
    nodoModelo* listaMarca = inicModelo();

    while(iterador != NULL)
    {
        if(strcmpi(iterador->marca, marca) == 0)
        {
            listaMarca = iterador->listaModelo;
        }
        iterador = iterador->siguiente;
    }
    return listaMarca;
}


// Por Precios

// menu por precio....
int buscarPorPrecio_menu()
{
    int option = -1;
    do
    {
        system("cls");
        marcoGeneral();
        tituloCentral("Busqueda por precio",4,159,159);
        /*gotoxy(48,12);
        printf("1. Por precio exacto: \n");
        gotoxy(48,13);
        printf("2. Por precios menores a: \n");
        gotoxy(48,14);
        printf("3. Por precios mayores a: \n");
        gotoxy(48,15);
        printf("4. Por precios entre: \n");

        gotoxy(48,17);
        printf("0. Volver: \n");
        gotoxy(48,18);
        printf("Opci%cn: ",162);
        */

        char opcionesMenu[5][30];
        strcpy(opcionesMenu[0],"Por precio exacto:    ");
        strcpy(opcionesMenu[1],"Por precios menores a:");
        strcpy(opcionesMenu[2],"Por precios mayores a:");
        strcpy(opcionesMenu[3],"Por precios entre:    ");
        strcpy(opcionesMenu[4],"Volver:               ");

        int seleccion=opcMenu(opcionesMenu,5,48,12,95,159);
        fflush(stdin);
        //scanf("%d", &option);
        option=seleccion;
        option = buscarPorPrecio_case(option);

    }
    while(option != 4);

    return option;
}

int buscarPorPrecio_case(int opcion)
{
    nodoAuto* listaAutos = inicAuto();
    switch(opcion)
    {

    case 0:
        system("cls");
        marcoGeneral();
        double precioExacto;
        tituloCentral("Por precio exacto",4,159,159);
        gotoxy(45,12);printf("Ingrese el precio: ");
        fflush(stdin);
        scanf("%lf", &precioExacto);
        listaAutos = cargaAutos();
        listaAutos = filtrarRango(listaAutos, precioExacto, precioExacto, FILTRAR_PRECIO);

        if(listaAutos != NULL)
        {
            gotoxy(45,13);printf("La lista de autos con ese valor: \n\n");
            printf("\t\t\t\t MARCA |   MODELO   |  PRECIO  |   KM    |   A%cO    |  ID   |CANTIDAD\n",165);
            mostrarListaAutos(listaAutos);
        }
        else
        {
            gotoxy(43,23);printf("No se encontraron autos con ese valor...\n");
        }
        getch();
        break;
    case 1:;
        //printf("me sale error si no estoy");
        double precioMenorA;
        do
        {
            system("cls");
            marcoGeneral();
            tituloCentral("Por precios menores a:",4,159,159);
            gotoxy(50,11);printf("Ingrese el precio: ");
            fflush(stdin);
            scanf("%lf", &precioMenorA);

            if(precioMenorA < 0)
            {
                printf("\t");
                char textoError[30] = "Ingrese un valor positivo";
                escribirTexto(textoError, 50, 1000);
            }
        }
        while(precioMenorA < 0);

        listaAutos = cargaAutos();
        listaAutos = filtrarRango(listaAutos, 0, precioMenorA, FILTRAR_PRECIO);

        if(listaAutos != NULL)
        {
            gotoxy(42,12);printf("La lista de autos menores a $%.2lf: \n\n", precioMenorA);
            printf("\t\t\t\t MARCA |   MODELO   |  PRECIO  |   KM    |   A%cO    |  ID   |CANTIDAD\n",165);
            mostrarListaAutos(listaAutos);
        }
        else
        {
            gotoxy(43,23);printf("No se encontraron autos menores a $%.2lf: \n", precioMenorA);
        }
        getch();
        break;
    case 2:;
        //printf("me sale error si no estoy");
        double precioMayorA;
        do
        {
            system("cls");
            marcoGeneral();
            tituloCentral("Por precios mayores a:",4,159,159);
            gotoxy(42,13);printf("\tIngrese el precio minimo: ");
            fflush(stdin);
            scanf("%lf", &precioMayorA);

            if(precioMayorA < 0)
            {
            printf("\t");
              gotoxy(43,23);  char textoError[30] = "Ingrese un valor positivo";
                escribirTexto(textoError, 50, 1000);
            }
        }
        while(precioMayorA < 0);

        listaAutos = cargaAutos();
        listaAutos = filtrarRango(listaAutos, precioMayorA, 99999999999999, FILTRAR_PRECIO); // NO me anda el infinitom no se porque y queria reutilizar la función...
//        listaAutos = filtrarRango(listaAutos, precioMayorA, INFINITE);

        if(listaAutos != NULL)
        {
           gotoxy(42,13); printf("La lista de autos mayores a $%.2lf: \n\n", precioMayorA);
            printf("\t\t\t\t MARCA |   MODELO   |  PRECIO  |   KM    |   A%cO    |  ID   |CANTIDAD\n",165);
            mostrarListaAutos(listaAutos);
        }
        else
        {
            gotoxy(43,23); printf("\tNo se encontraron autos mayores a $%.2lf: \n", precioMayorA);
        }

        getch();
        break;

    case 3:;
        //printf("me sale error, si no estoy, codeblocks es una mierda");
        double precioMinimo;
        double precioMaximo;
        listaAutos = cargaAutos();
        do
        {
            system("cls");
            marcoGeneral();
            tituloCentral("Por precios entre valores:",4,159,159);
            gotoxy(46,12); printf("Ingrese el precio minimo: ");
            fflush(stdin);
            scanf("%lf", &precioMinimo);

            if(precioMinimo < 0)
            {
                printf("\t");
                gotoxy(42,25);  char textoError[30] = "Ingrese un valor positivo";
                escribirTexto(textoError, 50, 1000);
            }
        }
        while(precioMinimo < 0);

        do
        {
            system("cls");
            marcoGeneral();
            tituloCentral("Por precios entre valores:",4,159,159);
            gotoxy(46,12);printf("Ingrese el precio maximo: ");
            fflush(stdin);
            scanf("%lf", &precioMaximo);

            if(precioMaximo < 0)
            {
                printf("\t");
                gotoxy(42,25);  char textoError[30] = "Ingrese un valor positivo";
                escribirTexto(textoError, 50, 1000);
            }
        }
        while(precioMaximo < 0);


        listaAutos = filtrarRango(listaAutos, precioMinimo, precioMaximo, FILTRAR_PRECIO);

        if(listaAutos != NULL)
        {
            gotoxy(42, 14); printf("La lista de autos $%.2lf - $%.2lf \n", precioMinimo, precioMaximo);
            printf("\n\t\t\t\t MARCA |   MODELO   |  PRECIO  |   KM    |   A%cO    |  ID   |CANTIDAD\n",164);
            mostrarListaAutos(listaAutos);
        }
        else
        {
          gotoxy(41,23);  printf("No se encontraron autos $ %.2lf - $ %.2lf \n", precioMinimo, precioMaximo);
        }
        getch();
        break;

    case 4:
        return 4;
        break;

    default:
        printf("\t");
        char texto[50]= "Seleccione una de las opciones permitidas...";
        printf("\t");
        escribirTexto(texto, 50,1000);
        getch();
        break;
        return -1;
    }
}


nodoAuto* filtrarRango(nodoAuto* listaAutos, double minimo, double maximo, int filtrarPor)
{
    nodoAuto* listaFiltrada = inicAuto();
    if(minimo > maximo)
    {
        double aux = minimo;
        minimo = maximo;
        maximo = aux;
    }

    if(listaAutos != NULL)
    {
        nodoAuto* iteradorMarcas = listaAutos;
        while(iteradorMarcas != NULL)
        {
            nodoModelo* iteradorModelos = iteradorMarcas->listaModelo;
            while(iteradorModelos != NULL)
            {
                if(filtrarPor == 1)
                {
                    if(iteradorModelos->vehiculo.precio >= minimo && maximo >= iteradorModelos->vehiculo.precio )
                    {
                        listaFiltrada = agregarAutoEnOrden(listaFiltrada, iteradorModelos->vehiculo);
                    }
                    iteradorModelos = iteradorModelos->siguiente;
                }
                else if(filtrarPor == 2)
                {
                    if(iteradorModelos->vehiculo.km >= minimo && maximo >= iteradorModelos->vehiculo.km )
                    {
                        listaFiltrada = agregarAutoEnOrden(listaFiltrada, iteradorModelos->vehiculo);
                    }
                    iteradorModelos = iteradorModelos->siguiente;
                }
                else if(filtrarPor == 3)
                {
                    if(iteradorModelos->vehiculo.anio >= minimo && maximo >= iteradorModelos->vehiculo.anio )
                    {
                        listaFiltrada = agregarAutoEnOrden(listaFiltrada, iteradorModelos->vehiculo);
                    }
                    iteradorModelos = iteradorModelos->siguiente;
                }

            }
            iteradorMarcas = iteradorMarcas->siguiente;
        }
    }
    return listaFiltrada;
}


// Por KM
int buscarPorKM_menu()
{
    int option = -1;
    do
    {
        system("cls");
        marcoGeneral();
        tituloCentral("Busqueda por kilometraje\n",4,159,159);
        /*gotoxy(45,12);printf("1. Por kilometraje exacto. \n");
        gotoxy(45,13);printf("2. Por kilometraje menores a: \n");
        gotoxy(45,14);printf("3. Por kilometraje mayores a: \n");
        gotoxy(45,15);printf("4. Por kilometraje entre: \n");

        gotoxy(45,17);printf("0. Volver: \n");
        gotoxy(45,18);printf("Opción: ");

        fflush(stdin);
        scanf("%d", &option);
        */
        char opcionesMenu[5][30];
        strcpy(opcionesMenu[0],"Por kilometraje exacto    ");
        strcpy(opcionesMenu[1],"Por kilometraje menores a:");
        strcpy(opcionesMenu[2],"Por kilometraje mayores a:");
        strcpy(opcionesMenu[3],"Por kilometraje entre:    ");
        strcpy(opcionesMenu[4],"Volver:                   ");
        int seleccion=opcMenu(opcionesMenu,5,45,10,95,159);
        option=seleccion;
        option = buscarPorKM_case(option);
    }
    while(option != 4);
    return option;
}



int buscarPorKM_case(int opcion)
{
    nodoAuto* listaAutos = inicAuto();

    switch(opcion)
    {
    case 4:
        return 4;
        break;
    case 0:
        system("cls");
        marcoGeneral();
        double precioExacto;
        tituloCentral("Por kilometraje exacto",4,159,159); //printf("\t\t\t\tPor kilometraje exacto. \n\n");
        gotoxy(40,12);printf("\tIngrese el kilometraje: ");
        fflush(stdin);
        scanf("%lf", &precioExacto);
        listaAutos = cargaAutos();
        listaAutos = filtrarRango(listaAutos, precioExacto, precioExacto, FILTRAR_KM);

        if(listaAutos != NULL)
        {
            gotoxy(42,13);printf("La lista de autos con ese kilometraje: \n\n\n");
                        printf("\t\t\t\t MARCA |   MODELO   |  PRECIO  |   KM    |   A%cO    |  ID   |CANTIDAD\n",165);
            mostrarListaAutos(listaAutos);
        }
        else
        {
            printf("\n\t\t\t\t\t No se encontraron autos con ese kilometraje...\n");
        }
        getch();
        break;
    case 1:;
        //printf("me sale error si no estoy");
        double precioMenorA;
        do
        {
            system("cls");
            marcoGeneral();
            tituloCentral("Por kilometraje menores a:",4,159,159);
            gotoxy(42,11);printf("\tIngrese el kilometraje: ");
            fflush(stdin);
            scanf("%lf", &precioMenorA);

            if(precioMenorA < 0)
            {
                printf("\t");
                char textoError[30] = "Ingrese un valor positivo";
                escribirTexto(textoError, 50, 1000);
            }
        }
        while(precioMenorA < 0);

        listaAutos = cargaAutos();
        listaAutos = filtrarRango(listaAutos, 0, precioMenorA, FILTRAR_KM);

        if(listaAutos != NULL)
        {
            gotoxy(42,12);printf("\tLa lista de autos menores a %.0lf: Km\n", precioMenorA);
            printf("\n\t\t\t\t MARCA |   MODELO   |  PRECIO  |   KM    |   A%cO    |  ID   |CANTIDAD\n",165);
            mostrarListaAutos(listaAutos);
        }
        else
        {
            printf("\tNo se encontraron autos menores a %..0lf: Km\n", precioMenorA);
        }
        getch();
        break;
    case 2:;
        //printf("me sale error si no estoy");
        double precioMayorA;
        do
        {
            system("cls");
            marcoGeneral();
            tituloCentral("Por kilometraje mayores a:",4,159,159); //printf("\t\t\t\tPor kilometraje mayores a: \n\n");
            gotoxy(40,12);printf("\tIngrese el kilometraje minimo: ");
            fflush(stdin);
            scanf("%lf", &precioMayorA);

            if(precioMayorA < 0)
            {
                printf("\t");
                char textoError[30] = "Ingrese un valor positivo";
                escribirTexto(textoError, 50, 1000);
            }
        }
        while(precioMayorA < 0);

        listaAutos = cargaAutos();
        listaAutos = filtrarRango(listaAutos, precioMayorA, 99999999999999, FILTRAR_KM); // NO me anda el infinitom no se porque y queria reutilizar la función...

        if(listaAutos != NULL)
        {
            gotoxy(42,13);printf("La lista de autos mayores a %.0lf Km: \n", precioMayorA);
            mostrarListaAutos(listaAutos);
        }
        else
        {
           gotoxy(40,14); printf("\tNo se encontraron autos mayores a %.0lf: \n", precioMayorA);
        }

        getch();
        break;
    case 3:;
        //printf("me sale error si no estoy, codeblocks es una mierda");
        double precioMinimo;
        double precioMaximo;
        listaAutos = cargaAutos();
        do
        {
            system("cls");
            marcoGeneral();
            tituloCentral("Por kilometraje entre valores:",4,159,159); //printf("\t\t\t\tPor kilometraje entre valores: \n\n");
            gotoxy(42,14);printf("Ingrese el kilometraje minimo: ");
            fflush(stdin);
            scanf("%lf", &precioMinimo);

            if(precioMinimo < 0)
            {
                printf("\t");
                char textoError[30] = "Ingrese un valor positivo";
                escribirTexto(textoError, 50, 1000);
            }
        }
        while(precioMinimo < 0);

        do
        {
            system("cls");
            marcoGeneral();
            tituloCentral("Por kilometraje entre valores:",4,159,159); //printf("\t\t\t\tPor kilometraje entre valores: \n\n");
            gotoxy(42,14);printf("Ingrese el kilometraje maximo: ");
            fflush(stdin);
            scanf("%lf", &precioMaximo);

            if(precioMaximo < 0)
            {
                printf("\t");
                char textoError[30] = "Ingrese un valor positivo";
                escribirTexto(textoError, 50, 1000);
            }
        }
        while(precioMaximo < 0);


        listaAutos = filtrarRango(listaAutos, precioMinimo, precioMaximo, FILTRAR_KM);

        if(listaAutos != NULL)
        {
            gotoxy(42,15);printf("La lista de autos %.0lf Km - %.0lf Km \n", precioMinimo, precioMaximo);
            printf("\n\t\t\t\t MARCA |   MODELO   |  PRECIO  |   KM    |   A%cO    |  ID   |CANTIDAD\n",165);
            mostrarListaAutos(listaAutos);
        }
        else
        {
           gotoxy(42,16); printf("No se encontraron autos %.0lf Km - %.0lf Km \n", precioMinimo, precioMaximo);
        }
        getch();
        break;

    default:
        printf("\t");
        char texto[50]= "Seleccione una de las opciones permitidas...";
        printf("\t");
        escribirTexto(texto, 50,1000);
        getch();
        break;
    }
    return -1;
}



// Por Año

int buscarPorAnio_menu()
{
    int option = -1;
    do
    {
        system("cls");
        marcoGeneral();
        tituloCentral("Busqueda por anio del modelo\n",4,159,159);

        /*printf("\t1. Por año del modelo exacto. \n");
        printf("\t2. Por año del modelo menores a: \n");
        printf("\t3. Por año del modelo mayores a: \n");
        printf("\t4. Por año del modelo entre: \n");

        printf("\t0. Volver: \n");
        printf("\tOpción: ");

        fflush(stdin);
        scanf("%d", &option);
        */
        char opcionesMenu[5][30];
        strcpy(opcionesMenu[0],"Por anio del modelo exacto   ");
        strcpy(opcionesMenu[1],"Por anio del modelo menores a");
        strcpy(opcionesMenu[2],"Por anio del modelo mayores a");
        strcpy(opcionesMenu[3],"Por anio del modelo entre:   ");
        strcpy(opcionesMenu[4],"Volver"                       );
        int seleccion=opcMenu(opcionesMenu,5,45,10,95,159);
        option=seleccion;
        option = buscarPorAnio_case(option);
    }
    while(option != 4);
    return option;
}


int buscarPorAnio_case(int opcion)
{
    nodoAuto* listaAutos = inicAuto();

    switch(opcion)
    {
    case 4:
        return 4;
        break;
    case 0:
        system("cls");
        marcoGeneral();
        double precioExacto;
        //printf("\t\t\t\tPor anio exacto. \n\n");
        tituloCentral("Por anio exacto.",4,159,159);
        gotoxy(47,11);printf("\tIngrese el anio: ");
        fflush(stdin);
        scanf("%lf", &precioExacto);
        listaAutos = cargaAutos();
        listaAutos = filtrarRango(listaAutos, precioExacto, precioExacto, FILTRAR_ANIO);

        if(listaAutos != NULL)
        {
            gotoxy(45,12);printf("La lista de autos con ese anio: \n");
            printf("                                                   \n");
            printf("\t\t\t\t MARCA |   MODELO   |  PRECIO  |   KM    |   A%cO    |  ID   |CANTIDAD\n",165);
            mostrarListaAutos(listaAutos);
        }
        else
        {
            printf("\n\t\t\t\t\tNo se encontraron autos con ese anio...\n");
        }
        marcoGeneral();
        getch();
        break;
    case 1:;
        //printf("me sale error si no estoy");
        double precioMenorA;
        do
        {
            system("cls");
            marcoGeneral();
            //printf("\t\t\t\tPor año menores a: \n\n");
            tituloCentral("Por anio menores a:",4,159,159);
            gotoxy(45,11);printf("\tIngrese el anio: ");
            fflush(stdin);
            scanf("%lf", &precioMenorA);

            if(precioMenorA < 0)
            {
                printf("\t");
                char textoError[30] = "Ingrese un valor positivo";
                escribirTexto(textoError, 50, 1000);
            }
        }
        while(precioMenorA < 0);

        listaAutos = cargaAutos();
        listaAutos = filtrarRango(listaAutos, 0, precioMenorA, FILTRAR_ANIO);

        if(listaAutos != NULL)
        {
            gotoxy(42,12);printf("La lista de autos menores a %.0lf: \n", precioMenorA);
           // printf("                                                                     ");
            printf("\t\t\t\t MARCA |   MODELO   |  PRECIO  |   KM    |   A%cO    |  ID   |CANTIDAD\n",165);
            mostrarListaAutos(listaAutos);
        }
        else
        {
            gotoxy(42,14);printf("No se encontraron autos menores a %.0lf: \n", precioMenorA);
        }
        getch();
        break;
    case 2:;
        //printf("me sale error si no estoy");
        system("cls");
        double precioMayorA;
        do
        {
            system("cls");
            marcoGeneral();
            //printf("\t\t\t\tPor anio mayores a: \n\n");
            tituloCentral("Por anio mayores a:",4,159,159);
            gotoxy(42,11);printf("\tIngrese el anio minimo: ");
            fflush(stdin);
            scanf("%lf", &precioMayorA);

            if(precioMayorA < 0)
            {
                printf("\t");
                char textoError[30] = "Ingrese un valor positivo";
                escribirTexto(textoError, 50, 1000);
            }
        }
        while(precioMayorA < 0);

        listaAutos = cargaAutos();
        listaAutos = filtrarRango(listaAutos, precioMayorA, 99999999999999, FILTRAR_ANIO); // NO me anda el infinitom no se porque y queria reutilizar la función...
        if(listaAutos != NULL)
        {
            gotoxy(42,13);printf("\tLa lista de autos mayores a %.0lf: \n\n", precioMayorA);
            printf("\t\t\t\t MARCA |   MODELO   |  PRECIO  |   KM    |   A%cO    |  ID   |CANTIDAD\n",165);
            mostrarListaAutos(listaAutos);
        }
        else
        {
            gotoxy(42,15);printf("No se encontraron autos mayores a %.0lf: \n", precioMayorA);
        }

        getch();
        break;
    case 3:;
        //printf("me sale error si no estoy, codeblocks es una mierda");
        double precioMinimo;
        double precioMaximo;
        listaAutos = cargaAutos();
        do
        {
            system("cls");
            marcoGeneral();
            tituloCentral("Por anio entre valores:",4,159,159);
            gotoxy(42,11);printf("\tIngrese el anio minimo: ");
            fflush(stdin);
            scanf("%lf", &precioMinimo);

            if(precioMinimo < 0)
            {
                printf("\t");
                char textoError[30] = "Ingrese un valor positivo";
                escribirTexto(textoError, 50, 1000);
            }
        }
        while(precioMinimo < 0);

        do
        {
            system("cls");
            marcoGeneral();
            tituloCentral("Por anio entre valores:",4,159,159);
            gotoxy(42,11);printf("\tIngrese el anio maximo: ",164);
            fflush(stdin);
            scanf("%lf", &precioMaximo);

            if(precioMaximo < 0)
            {
                printf("\t");
                char textoError[30] = "Ingrese un valor positivo";
                escribirTexto(textoError, 50, 1000);
            }
        }
        while(precioMaximo < 0);


        listaAutos = filtrarRango(listaAutos, precioMinimo, precioMaximo, FILTRAR_ANIO);

        if(listaAutos != NULL)
        {
            gotoxy(42,12);printf("\tLa lista de autos %.0lf - %.0lf \n", precioMinimo, precioMaximo);
            gotoxy(33,14);printf("MARCA |   MODELO   |  PRECIO  |   KM    |   A%cO    |  ID   |CANTIDAD\n",165);
            mostrarListaAutos(listaAutos);
        }
        else
        {
            gotoxy(42,15);printf("\tNo se encontraron autos %.0lf - %.0lf \n", precioMinimo, precioMaximo);
        }
        getch();
        break;

    default:
        printf("\t");
        char texto[50]= "Seleccione una de las opciones permitidas...";
        printf("\t");
        escribirTexto(texto, 50,1000);
        getch();
        break;
    }
    return -1;
}
