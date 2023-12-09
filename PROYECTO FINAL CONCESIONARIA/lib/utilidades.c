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

const int dimensionX=120;
const int dimensionY=30;


int verificarArchivos(char nombre[])
{
    int creado = 0;
    FILE* archivo = fopen(ARCHIVO_PERSONAL, "r+b");
    if(archivo != NULL)
    {
        fclose(archivo);
    }
    else
    {
        archivo = fopen(ARCHIVO_PERSONAL, "wb");
        if(archivo != NULL)
        {
            printf("Archivo personal creado.\n");
            fclose(archivo);
            creado = 1;
        }
        else
        {
            printf("No se pudo generar el archivo personal.\n");
        }
    }
    return creado;
}


void escribirTexto(char texto[], int milisegundosBorrando, int milisegundosEnBorrar)
{

    for(int i = 0; i< strlen(texto); i++)
    {
        printf("%c", texto[i]);
        Sleep(milisegundosBorrando);
    }
    Sleep(milisegundosEnBorrar);
    for(int i = 0; i< strlen(texto); i++)
    {
        printf("\b \b");
        Sleep(milisegundosBorrando);
    }
}

void borrarArchivo(char nombre[])
{
    FILE* archivo = fopen(nombre, "w+b");
    if(archivo != NULL)
    {
        fclose(archivo);
    }
    else
    {
        printf("No se pudo Borrar el archivo personal.\n");
    }
}

void inicioSesion()
{
    /////////////               Verificar Que existan los archivos Archivos /////////////

    stPersonal persona;   // guardo la estructura del gerente o vendedor.
    int intentos = 1;
    do
    {

        if(verificarArchivos(ARCHIVO_PERSONAL))
        {
            // cargando user de pruebas si tuvo que crear archivos, para que la primera vez tenga algo para entrar y crear mas users.
            guardarPersona((stPersonal){0, "Gerente","Gerente", "1234",1 });
            guardarPersona((stPersonal){1, "Vendedor","Vendedor", "1234",0});
        }
        verificarArchivos(ARCHIVO_AUTOS);
        system("cls");


        /////////////               Home page /////////////
        do
        {
            system("cls");
            if(intentos>0)
            {
              color(159);
              gotoxy(4,26);printf("Intento %d/3", intentos);
            }
              persona = menuInicio();
            intentos++;
        }
        while(intentos <= 3 && persona.flagAdmin == -1);

        /////////////               Gerente /////////////
        if(persona.flagAdmin == 1)
        {
            int option = 0;
            do
            {
                system("cls");
                option = menuGerenete_homePage(persona);
            } while(option != 8);

        }
        /////////////               Vendedor /////////////
        if(persona.flagAdmin == 0)
        {
            int option = 0;
            do
            {
                system("color 37");
                system("cls");
                gotoxy(30,12);
                gotoxy(25,7);printf("\t\t\t\tBienvenido Vendedor: %s\n", persona.nombre);
                option = menuVendedor_homePage(persona);
            } while(option != 0);
        }
        /////////////               Pasado 3 intentos /////////////
        if(persona.flagAdmin == -1)
        {
            color(159);
            gotoxy(25,15);printf("\tError al iniciar sesi%cn (%s), reinicie el sistema. \n",162, persona.nombre);
            gotoxy(32,16);printf("Presione una tecla para cerrar");
            int pausa=getch();
        } else
        {
            intentos = 0;
        }
    }while(intentos < 3);
}













// Parte grafica
void dibujarCaja(int xSup,int ySup,int xInf, int yInf,int valoresAscii[7],int colorBordes) //ValoresAscii:
{                                                                           //izq-sup,der-sup,izq-inf,der-inf,hor-arriba,hor-abajo,vert-izq,vert-der
    color(colorBordes);
    int a,b=0;


    //HORIZONTAL
    for(a=xSup;a<=xInf;a++)
    {
        gotoxy(a,ySup);printf("%c",valoresAscii[4]);
        gotoxy(a,yInf);printf("%c",valoresAscii[5]);
    }

    //VERTICAL
    for(b=ySup;b<=yInf;b++)
    {
        gotoxy(xSup,b);printf("%c",valoresAscii[6]);
        gotoxy(xInf,b);printf("%c",valoresAscii[7]);
    }
    //esquinas. de izquiera a derecha y arriba hacia abajo
    gotoxy(xSup,ySup);printf("%c",valoresAscii[0]);
    gotoxy(xInf,ySup);printf("%c",valoresAscii[1]);
    gotoxy(xSup,yInf);printf("%c",valoresAscii[2]);
    gotoxy(xInf,yInf);printf("%c",valoresAscii[3]);

}

void llenarRec(int xInicial,int yInicial,int xFinal,int yFinal, int valorAsciiRelleno,int valorColor)
{
    color(valorColor);
    for(int y=yInicial;y<=yFinal;y++)
    {
        for(int x=xInicial;x<=xFinal;x++)
        {
            gotoxy(x,y);printf("%c",valorAsciiRelleno);
        }
    }
}

void tituloCentral(char texto[100],int alturaY,int colorTexto,int colorRecuadro)
{
    color(colorRecuadro);
    int longitudP=strlen(texto);


    //EJE X
    int margenX=3; //SE DEBE REPETIR PARA QUE SEA SIMETRICO AL DEFINIR TAMAÑO DEL RECUADRO
    int puntoInicialX=(dimensionX-(longitudP+(margenX*2)))/2;
    int puntofinalX=puntoInicialX+longitudP+(margenX*2);

    //EJE Y
    int margenY=2; //SE DEBE REPETIR PARA QUE SEA SIMETRICO AL DEFINIR TAMAÑO DEL RECUADRO
    int espaciadoSup=0;
    int margenSupInf=margenY*2; //COMBINADOS AMBOS LADOS

    int puntoInicialY=espaciadoSup+alturaY;
    int puntoFinalY=espaciadoSup+margenSupInf+alturaY;

    /*//FONDO
    color(colorRelleno);
    for(int a=puntoInicialY;a<=puntoFinalY;a++)
    {
        for(int b=puntoInicialX;b<=puntofinalX;b++)
        {
            gotoxy(b,a);printf("%c",176);

        }
    }*/

    //CONTORNOS X LUEGO Y
    color(colorRecuadro);
    for(int x=puntoInicialX;x<=puntofinalX;x++)
    {
        gotoxy(x,espaciadoSup+alturaY);printf("%c",205);
        gotoxy(x,espaciadoSup+margenSupInf+alturaY); printf("%c",205);
    }
    for(int y=puntoInicialY;y<=puntoFinalY;y++)
    {
        gotoxy(puntoInicialX,y);printf("%c",186);
        gotoxy(puntofinalX,y); printf("%c",186);
    }

    //ESQUINAS, DE IZQUIERDA A DERECHA Y ARRIBA HACIA ABAJO
    gotoxy(puntoInicialX,espaciadoSup+alturaY);printf("%c",201);
    gotoxy(puntofinalX,espaciadoSup+alturaY);printf("%c",187);
    gotoxy(puntoInicialX,margenSupInf+espaciadoSup+alturaY);printf("%c",200);
    gotoxy(puntofinalX,margenSupInf+espaciadoSup+alturaY);printf("%c",188);

    //TEXTO
    int posicionTextoY=(espaciadoSup+margenSupInf+espaciadoSup)/2;
    int posicionTextoX=puntoInicialX+margenX;
    color(colorTexto);
    gotoxy(posicionTextoX,posicionTextoY+alturaY);printf("%s",texto);

}

void marcoGeneral()
{
    system("color 9F");
    int valoresAsciiBorde[8]={178,178,178,178,178,178,178,178};
    dibujarCaja(0,0,119,29,valoresAsciiBorde,0);
    dibujarCaja(1,1,118,28,valoresAsciiBorde,0);
    int valoresAscii[8]={219,219,219,219,223,220,219,219};
    dibujarCaja(2,1,117,28,valoresAscii,159);
    color(07);
}

void desactivarMaximizar(){
	HWND consoleWindow;
	consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE,GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void muestraMenu(char lista[][30],int validos, int posX,int posY,int lineaColor)
{
    for(int x=0;x<validos;x++)
    {
        mostrarItem(lista[x],posX,posY+x,lineaColor);
    }


}

void mostrarItem(char opcion[],int x, int y, int numColor)
{
    color(numColor);
    gotoxy(x,y);printf("%s",opcion);
}

int opcMenu(char lista[][30],int validos,int posX, int posY,int colorSelect, int colorDefault)
{
    hidecursor(0);
    muestraMenu(lista,validos,posX,posY,colorDefault);
    int posicion=1;
    int opcion=-1; //
    int ubicacionY=posY;
    int tecla;
    //mostrarItem(lista[posicion-1],10,posicion,150);
    mostrarItem(lista[posicion-1],posX,posY,colorSelect);
    do
    {
        fflush(stdin);
        tecla=getch();
        switch(tecla)
        {
            case 72: //TECLA ARRIBA
                if(posicion>1)
                {
                    ubicacionY--;
                    posicion--;
                    mostrarItem(lista[posicion-1],posX,ubicacionY,colorSelect);//PINTA DE COLOR RESALTADO
                    mostrarItem(lista[posicion],posX,ubicacionY+1,colorDefault);//PINTA DEL COLOR ORIGINAL
                }
            break;

            case 80: //TECLA ABAJO
                if(posicion<validos)
                {
                    mostrarItem(lista[posicion-1],posX,ubicacionY,colorDefault);//PINTA DEL COLOR ORIGINAL
                    mostrarItem(lista[posicion],posX,ubicacionY+1,colorSelect);//PINTA DE COLOR RESALTADO
                    posicion++;
                    ubicacionY++;
                }
            break;

            case 13:
                opcion=posicion;
            break;
        }
    }while (opcion==-1);

    //RECORDAR RESTAR 1 A POSICION, DADO QUE EL MENU MUESTRA DE 1 EN ADELANTE
    //PERO LOS ARREGLOS COMIENZAN EN 0
    return posicion-1;
}
