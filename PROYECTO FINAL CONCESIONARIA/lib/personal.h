#ifndef PERSONAL_H_INCLUDED
#define PERSONAL_H_INCLUDED

typedef struct
{
    int idPersonal;
    char nombre[30]; // opcional para darle bienvenida
    char usuario[30];
    char clave[30];
    int flagAdmin;   // 1 para Gerente 0 para Venderdor
} stPersonal;

typedef struct
{
    stPersonal persona;
    struct nodoPersona* izq;
    struct nodoPersona* der;
} nodoPersonaArbol;


// Utilidades de nodos
nodoPersonaArbol* inicPersona();
nodoPersonaArbol* crearPersona(stPersonal persona);
nodoPersonaArbol* insertarPersona(nodoPersonaArbol* arbol, stPersonal persona);
void mostrarEnOrdesAscendente(nodoPersonaArbol* arbol);
nodoPersonaArbol* borrarArbolPersonas(nodoPersonaArbol* arbolPersonas, int id);

// Menu Inicio
void mostrarPersona(stPersonal persona);
stPersonal verificarUsuario(char usuario[],char clave[]);
stPersonal menuInicio();

// Gerente
void menuGerenete_case(int option);
int  menuGerenete_homePage(stPersonal gerente);

// Gerente Case
nodoPersonaArbol* cargarArbolPersonas();
stPersonal cargarPersona(int id);                           // case 1
int generarIdPersona();                                     // case 1
void mostrarPersonal(nodoPersonaArbol* arbol);              // case 2
nodoPersonaArbol* buscarNodoPersona_Id(nodoPersonaArbol* arbol,int id);  // case 3

// Termino el case guardando el arbol
void guardarPersona(stPersonal arbolPersonas);
void guardarArbolPersonas(nodoPersonaArbol* arbol);

// Vendedor

int menuVendedor_case(int option);
int menuVendedor_homePage(stPersonal vendedor);


#endif // PERSONAL_H_INCLUDED
