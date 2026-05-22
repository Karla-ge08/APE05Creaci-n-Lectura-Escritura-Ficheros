#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
 
using namespace std;
 
// Clase Persona
class Persona {
public:
    string id;
    string nombre;
    string telefono;
    string email;
 
    // Mostrar los datos de la persona
    void mostrar() {
        cout << "  ID      : " << id << endl;
        cout << "  Nombre  : " << nombre << endl;
        cout << "  Telefono: " << telefono << endl;
        cout << "  Email   : " << email << endl;
    }
};
 
// Separar campos de una linea CSV
string obtenerCampo(string linea, int posicion) {
    stringstream ss(linea);
    string campo;
    int i = 0;
    while (getline(ss, campo, ',')) {
        if (i == posicion) return campo;
        i++;
    }
    return "";
}
 
// Crear un nuevo registro
void crear() {
    Persona p;
    cin.ignore();
 
    cout << "\n--- Nuevo Registro ---" << endl;
 
    cout << "ID      : ";
    getline(cin, p.id);
 
    // Validar que el ID no este vacio
    if (p.id.empty()) {
        cout << "El ID no puede estar vacio." << endl;
        return;
    }
 
    cout << "Nombre  : ";
    getline(cin, p.nombre);
 
    cout << "Telefono: ";
    getline(cin, p.telefono);
 
    cout << "Email   : ";
    getline(cin, p.email);
 
    // Guardar en el archivo
    ofstream archivo("datos.txt", ios::app);
    if (archivo.is_open()) {
        archivo << p.id << "," << p.nombre << "," << p.telefono << "," << p.email << endl;
        archivo.close();
        cout << "Registro creado exitosamente." << endl;
    } else {
        cout << "Error al guardar." << endl;
    }
}
 
// Leer todos los registros
void leer() {
    ifstream archivo("datos.txt");
 
    if (!archivo.is_open()) {
        cout << "No hay datos registrados." << endl;
        return;
    }
 
    string linea;
    int total = 0;
 
    cout << "\n=== TODOS LOS REGISTROS ===" << endl;
 
    while (getline(archivo, linea)) {
        // Construir un objeto Persona con los datos leidos
        Persona p;
        p.id       = obtenerCampo(linea, 0);
        p.nombre   = obtenerCampo(linea, 1);
        p.telefono = obtenerCampo(linea, 2);
        p.email    = obtenerCampo(linea, 3);
 
        cout << "\nRegistro #" << total + 1 << ":" << endl;
        p.mostrar();
        total++;
    }
 
    archivo.close();
    cout << "\nTotal de registros: " << total << endl;
}
 
// Modificar un registro por su ID
void actualizar() {
    string idBuscar;
    cin.ignore();
 
    cout << "\n--- Actualizar Registro ---" << endl;
    cout << "ID del registro a actualizar: ";
    getline(cin, idBuscar);

    ifstream archivoLectura("datos.txt");

    if (!archivoLectura.is_open()) {
        cout << "No hay datos registrados." << endl;
        return;
    }

    // Leer todos los registros en un arreglo temporal
    string lineas[200];
    int total = 0;
    bool encontrado = false;
 
    while (getline(archivoLectura, lineas[total])) {
        total++;
    }
    archivoLectura.close();
 
    // Buscar y modificar la linea que coincide con el ID
    for (int i = 0; i < total; i++) {
        if (obtenerCampo(lineas[i], 0) == idBuscar) {
            cout << "Registro encontrado. Ingrese los nuevos datos:" << endl;
 
            string nuevoNombre, nuevoTelefono, nuevoEmail;
 
            cout << "Nuevo nombre  : ";
            getline(cin, nuevoNombre);
 
            cout << "Nuevo telefono: ";
            getline(cin, nuevoTelefono);
 
            cout << "Nuevo email   : ";
            getline(cin, nuevoEmail);
 
            // Reemplazar la linea con los datos nuevos
            lineas[i] = idBuscar + "," + nuevoNombre + "," + nuevoTelefono + "," + nuevoEmail;
            encontrado = true;
            break;
        }
    }
 
    if (!encontrado) {
        cout << "No se encontro el ID." << endl;
        return;
    }

    // Escribir todas las lineas de vuelta al archivo
    ofstream archivoEscritura("datos.txt");
    for (int i = 0; i < total; i++) {
        archivoEscritura << lineas[i] << endl;
    }
    archivoEscritura.close();
 
    cout << "Registro actualizado correctamente." << endl;
}

// Eliminar un registro por su ID
void eliminar() {
    string idBuscar;
    cin.ignore();
 
    cout << "\n--- Eliminar Registro ---" << endl;
    cout << "ID del registro a eliminar: ";
    getline(cin, idBuscar);
 
    ifstream archivoLectura("datos.txt");
 
    if (!archivoLectura.is_open()) {
        cout << "No hay datos registrados." << endl;
        return;
    }
 
    string lineas[200];
    int total = 0;
    bool encontrado = false;
 
    // Leer todas las lineas
    while (getline(archivoLectura, lineas[total])) {
        total++;
    }
    archivoLectura.close();
 
    // Escribir todo excepto la linea que queremos borrar
    ofstream archivoEscritura("datos.txt");
    for (int i = 0; i < total; i++) {
        if (obtenerCampo(lineas[i], 0) == idBuscar) {
            encontrado = true;
        } else {
            archivoEscritura << lineas[i] << endl;
        }
    }
    archivoEscritura.close();
 
    if (encontrado) {
        cout << "Registro eliminado correctamente." << endl;
    } else {
        cout << "No se encontro el ID." << endl;
    }
}
 
int main() {
    int opcion;
 
    cout << "===============================" << endl;
    cout << " SISTEMA DE GESTION - PROYECTO " << endl;
    cout << "===============================" << endl;
 
    do {
        cout << "\n1. Crear registro" << endl;
        cout << "2. Leer registros" << endl;
        cout << "3. Actualizar registro" << endl;
        cout << "4. Eliminar registro" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
 
        // Validar que la opcion sea valida
        if (opcion < 0 || opcion > 4) {
            cout << "Opcion invalida. Intente de nuevo." << endl;
            continue;
        }
 
        if (opcion == 1) crear();
        else if (opcion == 2) leer();
        else if (opcion == 3) actualizar();
        else if (opcion == 4) eliminar();
 
    } while (opcion != 0);
 
    cout << "\nGracias por usar el sistema." << endl;
    return 0;
}