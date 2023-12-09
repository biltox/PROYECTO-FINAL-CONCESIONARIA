#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED

void escribirTexto(char texto[], int milisegundosBorrando, int milisegundosEnBorrar);
int verificarArchivos(char nombre[50]);
void inicioSesion();
void borrarArchivo(ARCHIVO_PERSONAL);


//Parte grafica
void dibujarCaja(int xSup,int ySup,int xInf, int yInf,int valoresAscii[7], int color); //izq-sup,der-sup,izq-inf,der-inf,horizontal,vertical
void llenarRec(int xInicial,int yInicial,int xFinal,int yFinal, int valorAscii,int color);
void tituloCentral(char texto[100], int alturaY,int colorTexto,int colorRecuadro);
void marcoGeneral();
void desactivarMaximizar();
void muestraMenu(char lista[][30],int validos, int posX,int posY,int color);
void mostrarItem(char opcion[],int x, int y, int numColor);
int opcMenu(char lista[][30],int validos,int posX, int posY,int colorSelect, int colorDefault);

#endif // UTILIDADES_H_INCLUDED
