#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
 
// Agregar un nuevo contacto al archivo
void agregarContacto() {
    string nombre, telefono, correo;
 
    cout << "\n--- Agregar Contacto ---" << endl;
    cin.ignore();
 
    cout << "Nombre  : ";
    getline(cin, nombre);
 
    cout << "Telefono: ";
    getline(cin, telefono);
 
    cout << "Correo  : ";
    getline(cin, correo);
 
    // Guardar el contacto en el archivo agenda.txt
    ofstream archivo("agenda.txt", ios::app);
 
    if (archivo.is_open()) {
        archivo << nombre << "," << telefono << "," << correo << endl;
        archivo.close();
        cout << "Contacto guardado correctamente." << endl;
    } else {
        cout << "Error al guardar el contacto." << endl;
    }
}
 
// Buscar un contacto por nombre
void buscarContacto() {
    string busqueda;
 
    cout << "\n--- Buscar Contacto ---" << endl;
    cin.ignore();
    cout << "Ingrese el nombre a buscar: ";
    getline(cin, busqueda);
 
    ifstream archivo("agenda.txt");
 
    if (!archivo.is_open()) {
        cout << "La agenda esta vacia." << endl;
        return;
    }
 
    string linea;
    bool encontrado = false;
 
    // Revisar cada linea del archivo
    while (getline(archivo, linea)) {
        string nombre = linea.substr(0, linea.find(','));
 
        // Comparar el nombre con la busqueda (busqueda simple)
        if (nombre == busqueda) {
            stringstream ss(linea);
            string campos[3];
            int i = 0;
            string campo;
            while (getline(ss, campo, ',') && i < 3) {
                campos[i] = campo;
                i++;
            }
 
            cout << "\nContacto encontrado:" << endl;
            cout << "  Nombre  : " << campos[0] << endl;
            cout << "  Telefono: " << campos[1] << endl;
            cout << "  Correo  : " << campos[2] << endl;
            encontrado = true;
        }
    }
 
    archivo.close();
 
    if (!encontrado) {
        cout << "No se encontro ningun contacto con ese nombre." << endl;
    }
}
 
// Mostrar todos los contactos guardados
void mostrarContactos() {
    ifstream archivo("agenda.txt");
 
    if (!archivo.is_open()) {
        cout << "La agenda esta vacia o no existe." << endl;
        return;
    }
 
    string linea;
    int numero = 1;
 
    cout << "\n=== TODOS LOS CONTACTOS ===" << endl;
 
    // Leer cada linea y mostramos el contacto
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campos[3];
        int i = 0;
        string campo;
        while (getline(ss, campo, ',') && i < 3) {
            campos[i] = campo;
            i++;
        }
 
        cout << numero << ". " << campos[0]
             << " | " << campos[1]
             << " | " << campos[2] << endl;
        numero++;
    }
 
    archivo.close();
}
 
int main() {
    int opcion;
 
    cout << "=== AGENDA TELEFONICA ===" << endl;
 
    // Menu que se repite hasta que el usuario elija salir
    do {
        cout << "\n1. Agregar contacto" << endl;
        cout << "2. Buscar contacto" << endl;
        cout << "3. Mostrar todos" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
 
        if (opcion == 1) agregarContacto();
        else if (opcion == 2) buscarContacto();
        else if (opcion == 3) mostrarContactos();
        else if (opcion != 0) cout << "Opcion invalida." << endl;
 
    } while (opcion != 0);
 
    cout << "Hasta luego." << endl;
    return 0;
}