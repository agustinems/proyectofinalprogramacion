#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Competidor {
    int numeroInscripcion;
    string nombre;
    int categoria;
    int subcategoria;
    int tirosCentro;
    int tirosNoCentro;
    int puntos;

    Competidor() : numeroInscripcion(0), nombre(""), categoria(0), subcategoria(0), tirosCentro(0), tirosNoCentro(0), puntos(0) {}
};

const int MAX_COMPETIDORES = 20;

Competidor competidores[MAX_COMPETIDORES];

int numCompetidores = 0;

//lectura del archivo

void cargarCompetidores() {
    ifstream archivo("competidores.txt");

    if (!archivo) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    while (archivo >>
        competidores[numCompetidores].numeroInscripcion >>
        competidores[numCompetidores].nombre >>
        competidores[numCompetidores].categoria >>
        competidores[numCompetidores].subcategoria >>
        competidores[numCompetidores].tirosCentro >>
        competidores[numCompetidores].tirosNoCentro) {
        numCompetidores++;
    }

    archivo.close();
}

//consigna numero 2

void calcularPuntos() {
    for (int i = 0; i < numCompetidores; i++) {
        competidores[i].puntos = competidores[i].tirosCentro * 10 + competidores[i].tirosNoCentro * 5;
    }
}

//consigna numero 1

void mostrarNombresCompetidores() {
    cout << "Nombres de los competidores:" << endl;
    for (int i = 0; i < numCompetidores; i++) {
        cout << competidores[i].nombre << endl;
    }
}

//consigna numero 3

void generarResultados() {
    // Ordena los competidores por puntos de mayor a menor
    for (int i = 0; i < numCompetidores - 1; i++) {
        for (int j = 0; j < numCompetidores - i - 1; j++) {
            if (competidores[j].puntos < competidores[j + 1].puntos) {
                swap(competidores[j], competidores[j + 1]);
            }
        }
    }

    ofstream archivoResultados("resultados.txt");

    for (int i = 0; i < numCompetidores; i++) {
        archivoResultados << "Numero de Inscripcion: " << competidores[i].numeroInscripcion << endl;
        archivoResultados << "Nombre: " << competidores[i].nombre << endl;
        archivoResultados << "Categoria: " << competidores[i].categoria << endl;
        archivoResultados << "Subcategoria: " << competidores[i].subcategoria << endl;
        archivoResultados << "Tiros en el Centro: " << competidores[i].tirosCentro << endl;
        archivoResultados << "Tiros Fuera del Centro: " << competidores[i].tirosNoCentro << endl;
        archivoResultados << "Puntos: " << competidores[i].puntos << endl;
        archivoResultados << "----------------------------------" << endl;
    }

    archivoResultados.close();
}

//consigna numero 4

int contarCompetidoresSuperanPuntos(int umbral) {
    int contador = 0;
    for (int i = 0; i < numCompetidores; i++) {
        if (competidores[i].puntos > umbral) {
            contador++;
        }
    }
    return contador;
}

//consigna numero 5

void contarCompetidoresPorCategoriaSubcategoria() {
    int matriz[3][3] = { 0 };

    for (int i = 0; i < numCompetidores; i++) {
        int categoria = competidores[i].categoria;
        int subcategoria = competidores[i].subcategoria;
        matriz[categoria][subcategoria]++;
    }

    cout << "Cantidad de competidores por categoria y subcategoria:" << endl;
    for (int fila = 0; fila < 3; fila++) {
        for (int columna = 0; columna < 3; columna++) {
            cout << matriz[fila][columna] << " ";
        }
        cout << endl;
    }
}

int main() {
    cargarCompetidores();
    calcularPuntos();

    int opcion;
    do {
        cout << "Menu:" << endl;
        cout << "1. Nombre de los participantes" << endl;
        cout << "2. Total de puntos por competidor" << endl;
        cout << "3. Crear  archivo resultados.txt " << endl;
        cout << "4. Cantidad de competidores que superan un umbral de puntos" << endl;
        cout << "5. Cantidad de competidores por categoria y subcategoria" << endl;
        cout << "6. Calir del programa" << endl;
        cout << "Elija una opcion: ";
        cin >> opcion;

        int cantidadSuperanUmbral = 0;

        switch (opcion) {
        case 1:
            mostrarNombresCompetidores();
            break;

        case 2:
            cout << "Puntos calculados para cada competidor:" << endl;
            for (int i = 0; i < numCompetidores; i++) {
                cout << competidores[i].nombre << ": " << competidores[i].puntos << " puntos" << endl;
            }
            break;

        case 3:
            generarResultados();
            cout << "Archivo resultados.txt creado con exito" << endl;
            break;

        case 4:
            int umbral;
            cout << "Ingrese el umbral de puntos: ";
            cin >> umbral;


            cout << "Competidores que superan: " << umbral << " puntos:" << endl;
            for (int i = 0; i < numCompetidores; i++) {
                if (competidores[i].puntos > umbral) {
                    cout << competidores[i].nombre << ": " << competidores[i].puntos << " puntos" << endl;
                    cantidadSuperanUmbral++;
                }
            }

            cout << "Los competidores que superan " << umbral << " puntos " << cantidadSuperanUmbral << endl;
            break;
        case 5:
            contarCompetidoresPorCategoriaSubcategoria();
            break;
        case 6:
            cout << "." << endl;
            break;
        default:
            cout << "Opcion no valida por favor elija una opcion valida" << endl;
        }
    } while (opcion != 6);

    return 0;
}