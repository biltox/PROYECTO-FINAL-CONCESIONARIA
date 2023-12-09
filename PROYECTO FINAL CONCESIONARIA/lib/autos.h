#ifndef AUTOS_H_INCLUDED
#define AUTOS_H_INCLUDED

typedef struct
{
    char marca[15];     // para el enlace
    char modelo[15];    // para el enlace
    int idAuto;

    double precio;
    double anio;
    double km;     // para ver si es usado o no y cuando km tiene
    int cantidad;

    // Opcional para mostrar datos
    int motor;
    int puertas;
} stVehiculo;

typedef struct
{
    char modelo[15];
    stVehiculo vehiculo;
    struct nodoModelo* siguiente;
} nodoModelo;

typedef struct
{
    char marca[15];
    nodoModelo* listaModelo;
    struct nodoAuto* siguiente;
} nodoAuto; // Celda

void mostrarVehiculo(stVehiculo vehiculo);
stVehiculo cargarVehiculo();


nodoModelo* inicModelo();
nodoModelo* crearNodoModelo(stVehiculo vehiculo);
nodoModelo* agregarModeloAlPrincipio(nodoModelo* listaModelo, stVehiculo vehiculo);
nodoModelo* agregarModeloEnOrden(nodoModelo* listaModelo, stVehiculo vehiculo);
void mostrarListaModelo(nodoModelo* listaModelo);


nodoAuto* inicAuto();
nodoAuto* crearNodoAuto(stVehiculo vehiculo);
nodoAuto* agregarAutoAlPrincipio(nodoAuto* listaAutos, stVehiculo vehiculo);
nodoAuto* agregarAutoEnOrden(nodoAuto* listaAutos, stVehiculo vehiculo);
void mostrarListaAutos(nodoAuto* listaAutos);


nodoAuto* cargaAutos();
void guardarListaAutos(nodoAuto* listaAutos);
nodoModelo* buscarNodoAuto(nodoAuto* listaAutos, int idAutoBuscado);
nodoAuto* removerAuto(nodoAuto* listaAutos,int idAutoBuscado, int* removido);


// vendedor

void mostrarMarcasDisponibles(nodoAuto* listaAutos);
nodoModelo* filtroMarca(nodoAuto* listaAutos,char marca[]);
nodoAuto* filtrarRango(nodoAuto* listaAutos, double minimo, double maximo, int filtrarPor);

int buscarPorPrecio_menu();
int buscarPorPrecio_case(int opcion);

nodoAuto* filtrarRango(nodoAuto* listaAutos, double minimo, double maximo, int filtrarPor);

int buscarPorKM_menu();
int buscarPorKM_case(int opcion);
int buscarPorAnio_menu();
int buscarPorAnio_case(int opcion);

#endif // AUTOS_H_INCLUDED
