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

//////////////////////////////     Nodos, Listas, Arboles     //////////////////////////////

nodoPersonaArbol* inicPersona()
{
    return NULL;
}

nodoPersonaArbol* crearPersona(stPersonal persona)
{
    nodoPersonaArbol* auxiliar = (nodoPersonaArbol*) malloc(sizeof(nodoPersonaArbol));
    auxiliar->persona = persona;
    auxiliar->izq = inicPersona();
    auxiliar->der = inicPersona();
    return auxiliar;
}

nodoPersonaArbol* insertarPersona(nodoPersonaArbol* arbol, stPersonal persona)
{
    if(arbol == NULL)
    {
        arbol = crearPersona(persona);
    } else
    {
        if(strcmpi(persona.nombre, arbol->persona.nombre) > 0)
        {
            arbol->der = insertarPersona(arbol->der, persona);
        } else
        {
            arbol->izq = insertarPersona(arbol->izq,persona);
        }
    }
}

void mostrarEnOrdesAscendente(nodoPersonaArbol* arbol)
{
    if(arbol != NULL)
    {
        mostrarEnOrdesAscendente(arbol->izq);
        mostrarPersona(arbol->persona);
        if(arbol->der != NULL)
        {
            mostrarEnOrdesAscendente(arbol->der);
        }
    }
}

void mostrarPersonal(nodoPersonaArbol* arbol)
{
    if(arbol == NULL)
    {
        printf("No hay Personas en el archivo.\n");
    }
    else
    {
        mostrarEnOrdesAscendente(arbol);
    }
}

nodoPersonaArbol* cargarArbolPersonas()
{
    nodoPersonaArbol* arbol = inicPersona();
    FILE* archivo = fopen(ARCHIVO_PERSONAL, "r+b");
    if(archivo != NULL)
    {
        stPersonal persona;
        while(fread(&persona, sizeof(persona), 1, archivo) > 0)
        {
            arbol = insertarPersona(arbol, persona);
        }
        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo 'personal', en la funci�n deArchivoAMemoria\n");
    }
    return arbol;
}

void guardarPersona(stPersonal persona)
{
    FILE* archivo = fopen(ARCHIVO_PERSONAL, "a+b");
    if(archivo != NULL)
    {
        fwrite(&persona, sizeof(persona),1, archivo);
        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo 'personal', en la funci�n guardarPersona\n");
    }
}

void guardarArbolPersonas(nodoPersonaArbol* arbol)
{
    if(arbol != NULL)
    {
        guardarArbolPersonas(arbol->izq);
        guardarPersona(arbol->persona);
        if(arbol->der != NULL)
        {
            guardarArbolPersonas(arbol->der);
        }
    }
}

// No encontre borrar nodo:
nodoPersonaArbol* borrarArbolPersonas(nodoPersonaArbol* arbolPersonas, int id)
{

    nodoPersonaArbol* arbol = inicPersona();
    FILE* archivo = fopen(ARCHIVO_PERSONAL, "r+b");
    if(archivo != NULL)
    {
        stPersonal persona;
        while(fread(&persona, sizeof(persona), 1, archivo) > 0)
        {
            if(persona.idPersonal != id)
            {
                arbol = insertarPersona(arbol, persona);
            }
        }
        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo 'personal', en la funci�n deArchivoAMemoria\n");
    }
    return arbol;
}


//////////////////////////////   FIN  Nodos, Listas, Arboles     //////////////////////////////


void mostrarPersona(stPersonal persona)
{
    /*printf("IdPersonal: %d\n", persona.idPersonal);
    printf("Nombre: %s\n", persona.nombre);
    printf("Usuario: %s\n", persona.usuario);
    printf("Clave: %s\n", persona.clave);
    printf("Admin: %d\n", persona.flagAdmin);*/
    printf("\n");
    printf("    %-3i | %-30s | %-30s | %-30s | %-3i ",persona.idPersonal,persona.nombre,persona.usuario,persona.clave, persona.flagAdmin);
}

stPersonal verificarUsuario(char usuario[],char clave[])
{
    // Si no lo encuentro devuelvo persona No Registrado
    stPersonal persona;
    persona.idPersonal = -1;
    strcpy(persona.clave, "");
    persona.flagAdmin = -1;
    strcpy(persona.usuario, "No Registrado");
    strcpy(persona.nombre, "No Registrado");

    FILE* archivo = fopen(ARCHIVO_PERSONAL, "r+b");
    if(archivo != NULL)
    {
        stPersonal auxiliar;
        while(fread(&auxiliar, sizeof(auxiliar), 1, archivo) > 0 && persona.flagAdmin == -1)
        {
            if(strcmpi(auxiliar.usuario, usuario) == 0 && strcmpi(auxiliar.clave, clave) == 0 )
            {
                persona = auxiliar;
            }
        }
        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo 'personal', en la funci�n verificar\n");
    }

    return persona;
}

stPersonal menuInicio()
{

    marcoGeneral();
    int usuario[30];
    char clave[30];


    tituloCentral("Bienvenido al sistema",4,159,159);
    gotoxy(51,14);printf("USUARIO: ");
    fflush(stdin);
    gets(&usuario);
    gotoxy(51,16);printf("CLAVE: ");
    char  caracter;
    int i = 0;
    while (caracter = getch())
    {
        if (caracter == 13) // 13 por el ascii enter
        {
            clave[i] = '\0';
            break;
        }
        else if (caracter == 8) // 8 por el ascii <- (borrar)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            if (i < 30)
            {
                printf("*");
                clave[i] = caracter;
                i++;
            }
        }
    }
    printf("\n");
    color(0);
    return verificarUsuario(usuario, clave);
}

nodoPersonaArbol* buscarNodoPersona_Id(nodoPersonaArbol* arbol,int id)
{
    nodoPersonaArbol* nodoBuscado = inicPersona();
    if(arbol != NULL)
    {
        if(arbol->persona.idPersonal == id)
        {
            nodoBuscado = arbol;
        }else
        {
            if(arbol->izq != NULL)
            {
                nodoBuscado = buscarNodoPersona_Id(arbol->izq, id);
            }
            if(arbol->der != NULL)
            {
                 nodoBuscado = buscarNodoPersona_Id(arbol->der, id);
            }
        }
    }
    return nodoBuscado;
}



///////////////////////////////////////////// Gerente /////////////////////////////////////////////

void menuGerenete_case(int option)
{
    //Creo un arbol para trabajar todo en memoria.
    nodoPersonaArbol* arbolPersonas;
    arbolPersonas = inicPersona();
    arbolPersonas = cargarArbolPersonas();

    nodoAuto* listaAutos = inicAuto();
    listaAutos = cargaAutos();


    switch(option)
    {
    case 0:
        system("cls");
        marcoGeneral();
        stPersonal persona = cargarPersona(generarIdPersona());
        arbolPersonas = insertarPersona(arbolPersonas ,persona);
        gotoxy(42,12);printf("\tPersona Guardada con %cxito\n",130);
        Sleep(500);
        getch();
        break;
    case 1:
        system("cls");
        marcoGeneral();
        //printf("\tLista de Empleado\n");
        tituloCentral("Lista de Empleado",4,159,159);
        printf("\n\n\n\n");
        printf("    ID  |   NOMBRE                       |   USUARIO                      |  CLAVE                         |  ADM    ");
        mostrarPersonal(arbolPersonas);
        printf("\n\n\n\t\t\t\t\t\tFin Lista de Empleado\n");
        marcoGeneral();
        getch();
        break;
    case 2:
        system("cls");
        marcoGeneral();
        tituloCentral("Modificar Empleado",4,159,159);
        int idBuscado = -1;
        gotoxy(42,11);printf("Ingrese el id del empleado a modificar: ");
        scanf("%d", &idBuscado);

        mostrarPersona(arbolPersonas->persona);
        nodoPersonaArbol* nodoAModificar = inicPersona();
        nodoAModificar = buscarNodoPersona_Id(arbolPersonas, idBuscado);
        if(nodoAModificar == NULL)
        {
            gotoxy(42,17);printf("No se encuentra el registro con id:%d", idBuscado);
        } else
        {
            nodoAModificar->persona = cargarPersona(idBuscado);
            gotoxy(48,25);printf("Se modific%c con %Cxito",162,130);
        }
        getch();
        break;
    case 3:
        system("cls");
        marcoGeneral();
        tituloCentral("Despedir Empleado:",4,159,159);
        gotoxy(42,11);printf("Ingrese el id del empleado a despedir: ");
        scanf("%d", &idBuscado);

        arbolPersonas = borrarArbolPersonas(arbolPersonas, idBuscado);

        gotoxy(42,13);printf("\tEmpleado (id = %d) despedido\n\n", idBuscado);
        getch();
        break;
                            // Autos....
    case 4:
        system("cls");
        marcoGeneral();
        tituloCentral("Agregar Auto:",4,159,159); //printf("\t5. Agregar Auto: \n");            //C
        stVehiculo vehiculo = cargarVehiculo();
        listaAutos = agregarAutoEnOrden(listaAutos, vehiculo);
        gotoxy(42,25);printf("Se agrego con %cxito",130);
        getch();
        break;
    case 5:
        system("cls");
        marcoGeneral();
        //printf("\t6. Lista de Auto: \n");
        tituloCentral("Lista de Auto:",4,159,159);
        printf("\n\n\n\n");
        printf("\n\n\n\n");           //R
        printf("                                MARCA |   MODELO   |  PRECIO  |   KM    |   A%cO    |  ID   |CANTIDAD\n",165);
        mostrarListaAutos(listaAutos);
        printf("\n\n");
        gotoxy(50,25);printf("Fin Lista de Auto \n");           //R
        getch();
        break;
    case 6:
        system("cls");
        marcoGeneral();
        //printf("\t7. Modificar Auto: \n");          //U
        tituloCentral("Modificar Auto: ",4,159,159);
        gotoxy(43,11);printf("Id Auto a modificar: \n");
        gotoxy(64,11);
        int idAutoBuscado;
        fflush(stdin);
        scanf("%d", &idAutoBuscado);

        nodoModelo* autoAModificar = buscarNodoAuto(listaAutos, idAutoBuscado);

        if(autoAModificar != NULL)
        {
            printf("  ");
                    printf("                              MARCA |   MODELO   |  PRECIO  |   KM    |   A%cO    |  ID   |CANTIDAD",165);

            mostrarVehiculo(autoAModificar->vehiculo);
            stVehiculo vehiculoModificado = cargarVehiculo();
            vehiculoModificado.idAuto = idAutoBuscado;

            strcpy(autoAModificar->modelo, vehiculoModificado.modelo);
            autoAModificar->vehiculo = vehiculoModificado;
            printf("\n\t\t\t\t\tEl auto se modifico con exito.... \n");

        } else
        {

            printf("\n\t\t\t\t\tNo se encontro el vehiculo buscado!!!.\n");
        }
        getch();
        break;
    case 7:
        system("cls");
        marcoGeneral();
        tituloCentral("Id Auto a remover:",4,159,159);
        gotoxy(50,13);printf("Id Auto a remover: "); //D
        int idAutoRemover;
        fflush(stdin);
        scanf("%d", &idAutoRemover);

        int removido = 0;
        listaAutos = removerAuto(listaAutos, idAutoRemover, &removido);

        if(removido == 0)
        {
            gotoxy(42,14);printf("Imposible remover, no se encuentra el id.\n");

        }else
        {
            gotoxy(50,15);printf("Removido con exito\n");
        }

        getch();
        break;

    case 8:
        return 8;
        break;

    default:

        printf("\t");
        char texto[50]= "Seleccione una de las opciones permitidas...";
        printf("\t");
        escribirTexto(texto, 50,1000);
        Sleep(300);

        break;
    }
    //Guardo el arbol modificado...
    borrarArchivo(ARCHIVO_PERSONAL);
    borrarArchivo(ARCHIVO_AUTOS);
    guardarArbolPersonas(arbolPersonas);
    guardarListaAutos(listaAutos);
}


int menuGerenete_homePage(stPersonal gerente)
{
    int option = -1;
    do
    {
        system("cls");
        marcoGeneral();
        //printf("\t\t\t\tBienvenido gerente: %s\n\n", gerente.nombre);
        char titulo[50];
        strcpy(titulo,"Bienvenido gerente:");
        strcat(titulo,gerente.nombre);
        tituloCentral(titulo,4,159,159);

        /*printf("\t1. Contratar Empleado: \n");      //C
        printf("\t2. Lista de Empleado: \n");       //R
        printf("\t3. Modificar Empleado: \n");      //U
        printf("\t4. Despedir Empleado: \n\n");     //D

        printf("\t5. Agregar Auto: \n");            //C
        printf("\t6. Lista de Auto: \n");           //R
        printf("\t7. Modificar Auto: \n");          //U
        printf("\t8. Remover Auto: \n\n");          //D

        printf("\t0. Volver: \n");
        printf("\tOpci�n: ");

        fflush(stdin);
        scanf("%d", &option);*/
        char opcionesMenu[9][30];
        strcpy(opcionesMenu[0],"Contratar Empleado:");
        strcpy(opcionesMenu[1],"Lista de Empleado: ");
        strcpy(opcionesMenu[2],"Modificar Empleado:");
        strcpy(opcionesMenu[3],"Despedir Empleado: ");
        strcpy(opcionesMenu[4],"Agregar Auto:      ");
        strcpy(opcionesMenu[5],"Lista de Auto:     ");
        strcpy(opcionesMenu[6],"Modificar Auto:    ");
        strcpy(opcionesMenu[7],"Remover Auto:      ");
        strcpy(opcionesMenu[8],"Volver:            ");
        int seleccion=opcMenu(opcionesMenu,9,46,10,95,159);
        option=seleccion;
        menuGerenete_case(option);
    }
    while(option != 8);
    return option;
}


int generarIdPersona()
{

    stPersonal persona;
    persona.idPersonal = -1;
    FILE* archivo = fopen(ARCHIVO_PERSONAL, "r+b");
    if(archivo != NULL)
    {
        fseek(archivo, 0 ,SEEK_END);
        int bytes = ftell(archivo);
        if(bytes != 0)
        {
            persona.idPersonal = (bytes/sizeof(persona));
        }
        else
        {
            persona.idPersonal = 0;
        }
        fclose(archivo);
    }
    else
    {
        printf("Error al abrir archivo personal en, generarIdPersona.\n");
    }
    return persona.idPersonal;
}

stPersonal cargarPersona(int id)
{
    stPersonal persona;
    tituloCentral("Menu cargar persona",4,159,159);
    gotoxy(40,17);printf("\tNombre y apellido: ");
    fflush(stdin);
    gets(persona.nombre);

    gotoxy(40,18);printf("\tNombre de usuario: ");
    fflush(stdin);
    gets(persona.usuario);

    gotoxy(40,19);printf("\tClave de usuario: ");
    fflush(stdin);
    gets(persona.clave);

    persona.idPersonal = id;
    gotoxy(40,20);printf("\tSu ID Personal (autom%Ctico): %d\n",160, persona.idPersonal);

    persona.flagAdmin = -1;
    gotoxy(40,21);printf("\tFunci%Cn: \n",162);
    gotoxy(40,22);printf("\t\t1: Gerente\n");
    gotoxy(40,23);printf("\t\t2: Vendedor\n\t\t");
    do
    {
        int funcionEmpleado;
        fflush(stdin);
        funcionEmpleado = getch();
        if(funcionEmpleado == 49)
        {
            persona.flagAdmin = 1;
        }
        else if(funcionEmpleado == 50)
        {
            persona.flagAdmin = 0;
        }
        else
        {
            printf("Seleccione 1 o 2... ");
            Sleep(1000);
            for(int i = 0; i< 20; i++)
            {
                printf("\b \b");
                Sleep(100);
            }
        }
    }
    while(persona.flagAdmin == -1);
    return persona;
}



///////////////////////////////////////////// Vendedor /////////////////////////////////////////////



int menuVendedor_homePage(stPersonal vendedor)
{
    int option = -1;
    do
    {
        system("cls");

        //gotoxy(22,7);printf("\t\t\t\t Bienvenido Vendedor: %s\n\n", vendedor.nombre);
        char titulo[50];
        strcpy(titulo,"Bienvenido vendedor: ");
        strcat(titulo,vendedor.nombre);
        marcoGeneral();
        tituloCentral(titulo,4,159,159);
        /*
        gotoxy(42,12);printf("1. Lista de Auto Albeticamente:");
        gotoxy(42,13);printf("2. Buscar por marca ");
        gotoxy(42,14);printf("3. Buscar por precio ");
        gotoxy(42,15);printf("4. Buscar por Km ");
        gotoxy(42,16);printf("5. Buscar por a%co ",164);
        gotoxy(42,17);printf("6. Ingresar venta auto por ID: ");

        gotoxy(42,18);printf("0. Volver: ");
        gotoxy(42,20);printf("Opci%cn: ",162);
        */

        char listaOpciones[7][30];
        strcpy(listaOpciones[0],"Lista de Auto Alfabeticamente");
        strcpy(listaOpciones[1],"Buscar por marca            ");
        strcpy(listaOpciones[2],"Buscar por precio           ");
        strcpy(listaOpciones[3],"Buscar por Km               ");
        strcpy(listaOpciones[4],"Buscar por anio              ");
        strcpy(listaOpciones[5],"Ingresar venta auto por ID: ");
        strcpy(listaOpciones[6],"Volver:                     ");

        int seleccionMenu=opcMenu(listaOpciones,7,43,12,95,159);
        //fflush(stdin);
        //scanf("%d", &option);
        option=seleccionMenu;
        option = menuVendedor_case(option);
    } while(option != 0); // ORIGINAL 0
    return option;
}



int menuVendedor_case(int option)
{
    nodoAuto* listaAutos = inicAuto();
    listaAutos = cargaAutos();

    switch(option)
    {
    case 6:
        return 0; //SE MANTIENE DADO QUE POR ALGUNA RAZON CON 6 NO FUNCIONA
        break;
    case 0:
        system("cls");
        marcoGeneral();
        tituloCentral("Lista Completa de Autos:",4,159,159);
        printf("\n\n\n\n");
        gotoxy(34,13);printf("MARCA |   MODELO   |  PRECIO  |   KM    |   A%cO    |  ID   |CANTIDAD",165);
        mostrarListaAutos(listaAutos);
        gotoxy(50,23);printf("Fin Lista de Auto \n");
        getch();
        break;
    case 1:
        system("cls");
        marcoGeneral();
        tituloCentral("2. Buscar por marca\n",4,159,159);
        char marca[15];
        gotoxy(50,12);printf("Marcas disponibles: \n");
        mostrarMarcasDisponibles(listaAutos);
        gotoxy(50,16);printf("Ingrese Marca: ");
        fflush(stdin);
        gets(marca);
        nodoModelo* listaPorMarca = filtroMarca(listaAutos, marca);
        if(listaPorMarca != NULL)
        {
            printf("\n\t\t\t\t MARCA |   MODELO   |  PRECIO  |   KM    |   A%cO    |  ID   |CANTIDAD\n",165);
            mostrarListaModelo(listaPorMarca);
        } else
        {
            gotoxy(42,17);printf("La marca ingresada (%s) no se encuentra. \n", marca);
        }
        getch();
        break;
    case 2:
        system("cls");
        marcoGeneral();
        tituloCentral("3.Buscar por precio",4,159,159);
        int opcionPorPrecio = -1;
        do
        {
            opcionPorPrecio = buscarPorPrecio_menu();
            buscarPorPrecio_case(opcionPorPrecio);

        } while(opcionPorPrecio != 4);
        break;
    case 3:
        system("cls");
        marcoGeneral();
        printf("\t4. Buscar por kilometraje \n\n");
        int opcionPorKm = -1;
        do
        {
            opcionPorKm = buscarPorKM_menu();
            buscarPorKM_case(opcionPorKm);

        } while(opcionPorKm != 4);
        break;
    case 4:
        system("cls");
        marcoGeneral();
        printf("\t4. Buscar por a%Cio \n\n",164);
        int opcionPorAnio = -1;
        do
        {
            opcionPorAnio = buscarPorAnio_menu();
            buscarPorAnio_case(opcionPorAnio);

        } while(opcionPorAnio != 4);
        break;

    case 5:
        system("cls");
        marcoGeneral();
        //printf("\t4. Control de ventas\n\n");
        tituloCentral("Control de ventas",4,159,159);
        gotoxy(42,12);printf("Ingrese el ID del auto vendido: ");
        int idAuto;
        fflush(stdin);
        scanf("%d", &idAuto);
        nodoModelo* autoAmodificar = inicModelo();
        autoAmodificar = buscarNodoAuto(listaAutos, idAuto);
        if(autoAmodificar == NULL)
        {
            gotoxy(42,15);printf("No se encontro el auto con id: %d", idAuto);
        } else
        {
            if(autoAmodificar->vehiculo.cantidad > 0)
            {
                autoAmodificar->vehiculo.cantidad = autoAmodificar->vehiculo.cantidad -1;
                gotoxy(42,15);printf("FELICIDADES POR EL AUTO VENDIDO.\n");
            } else
            {
                gotoxy(40,15);printf("Lo siento no se encuentran unidades disponibles.\n");
            }
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
    //Guardo el arbol modificado...
    borrarArchivo(ARCHIVO_AUTOS);
    guardarListaAutos(listaAutos);
    return -1;
}











