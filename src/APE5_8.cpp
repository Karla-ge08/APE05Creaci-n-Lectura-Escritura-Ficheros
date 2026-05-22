#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
 
using namespace std;
 
// Clase Libro
class Libro {
public:
    string codigo;
    string titulo;
    string autor;
    string estado; 
 
    // Ingresar datos del libro
    void ingresarDatos() {
        cin.ignore();
        cout << "Codigo del libro: ";
        getline(cin, codigo);
 
        cout << "Titulo          : ";
        getline(cin, titulo);
 
        cout << "Autor           : ";
        getline(cin, autor);
 
        cout << "Estado          : ";
        getline(cin, estado);
    }

    // Guardar el libro en biblioteca.txt
    void guardarEnArchivo() {
        ofstream archivo("biblioteca.txt", ios::app);

        if (archivo.is_open()) {
            archivo << codigo << "," << titulo << "," << autor << "," << estado << endl;
            archivo.close();
            cout << "Libro registrado correctamente." << endl;
        } else {
            cout << "Error al guardar." << endl;
        }
    }
};
 
// Buscar un libro por titulo
void buscarLibro() {
    string busqueda;
    cin.ignore();
 
    cout << "\nIngrese el titulo a buscar: ";
    getline(cin, busqueda);
 
    ifstream archivo("biblioteca.txt");
 
    if (!archivo.is_open()) {
        cout << "No hay libros registrados." << endl;
        return;
    }
 
    string linea;
    bool encontrado = false;
 
    // Recorrer el archivo buscando el titulo
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campos[4];
        int i = 0;
        string campo;
        while (getline(ss, campo, ',') && i < 4) {
            campos[i] = campo;
            i++;
        }
 
        // Si el titulo coincide, mostrar el libro
        if (campos[1] == busqueda) {
            cout << "\nLibro encontrado:" << endl;
            cout << "  Codigo: " << campos[0] << endl;
            cout << "  Titulo: " << campos[1] << endl;
            cout << "  Autor : " << campos[2] << endl;
            cout << "  Estado: " << campos[3] << endl;
            encontrado = true;
        }
    }
 
    archivo.close();
 
    if (!encontrado) {
        cout << "No se encontro el libro." << endl;
    }
}
 
// Mostrar libros segun su estado
void mostrarLibrosPorEstado() {
    ifstream archivo("biblioteca.txt");
 
    if (!archivo.is_open()) {
        cout << "No hay libros registrados." << endl;
        return;
    }
 
    string linea;
    int disponibles = 0;
    int prestados = 0;
 
    cout << "\n=== LIBROS DISPONIBLES ===" << endl;
 
    // Mostrar los disponibles
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campos[4];
        int i = 0;
        string campo;
        while (getline(ss, campo, ',') && i < 4) {
            campos[i] = campo;
            i++;
        }
 
        if (campos[3] == "Disponible") {
            cout << "  [" << campos[0] << "] " << campos[1] << " - " << campos[2] << endl;
            disponibles++;
        }
    }
 
    // Reiniciar el archivo para segunda pasada
    archivo.clear();
    archivo.seekg(0);
 
    cout << "\n=== LIBROS PRESTADOS ===" << endl;
 
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campos[4];
        int i = 0;
        string campo;
        while (getline(ss, campo, ',') && i < 4) {
            campos[i] = campo;
            i++;
        }
 
        if (campos[3] == "Prestado") {
            cout << "  [" << campos[0] << "] " << campos[1] << " - " << campos[2] << endl;
            prestados++;
        }
    }

    archivo.close();

    cout << "\nTotal disponibles: " << disponibles << endl;
    cout << "Total prestados  : " << prestados << endl;
}

int main() {
    int opcion;
    cout << "=== BIBLIOTECA VIRTUAL ===" << endl;

    do {
        cout << "\n1. Agregar libro" << endl;
        cout << "2. Buscar libro" << endl;
        cout << "3. Ver disponibles y prestados" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            Libro libro;
            libro.ingresarDatos();
            libro.guardarEnArchivo();
        }
        else if (opcion == 2) buscarLibro();
        else if (opcion == 3) mostrarLibrosPorEstado();
        else if (opcion != 0) cout << "Opcion invalida." << endl;

    } while (opcion != 0);

    return 0;
}