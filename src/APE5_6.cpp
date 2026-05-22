#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
 
// Funcion para registrar la asistencia de un estudiante
void registrarAsistencia() {
    string nombre, fecha, estado;

    cin.ignore();

    cout << "\n--- Registrar Asistencia ---" << endl;
    cout << "Nombre del estudiante: ";
    getline(cin, nombre);
    cout << "Fecha (DD/MM/AAAA)   : ";
    getline(cin, fecha);

    // Validar el estado
    bool estadoValido = false;
    while (!estadoValido) {
        cout << "Estado (Presente / Ausente / Tardanza): ";
        getline(cin, estado);

        if (estado == "Presente" || estado == "Ausente" || estado == "Tardanza") {
            estadoValido = true;
        } else {
            cout << "Estado invalido. Intente de nuevo." << endl;
        }
    }

    // Guardar en el archivo asistencia.txt
    ofstream archivo("asistencia.txt", ios::app);

    if (archivo.is_open()) {
        archivo << nombre << "," << fecha << "," << estado << endl;
        archivo.close();
        cout << "Asistencia registrada correctamente." << endl;
    } else {
        cout << "Error al guardar." << endl;
    }
}

// Mostrar todo el historial de asistencia
void mostrarHistorial() {
    ifstream archivo("asistencia.txt");
 
    if (!archivo.is_open()) {
        cout << "No hay registros de asistencia aun." << endl;
        return;
    }
 
    string linea;
    cout << "\n=== HISTORIAL DE ASISTENCIA ===" << endl;
    cout << "Nombre               | Fecha       | Estado" << endl;
    cout << "-----------------------------------------------" << endl;

    // Leer e imprimir cada registro
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campos[3];
        int i = 0;
        string campo;
        while (getline(ss, campo, ',') && i < 3) {
            campos[i] = campo;
            i++;
        }
        cout << campos[0] << " | " << campos[1] << " | " << campos[2] << endl;
    }
 
    archivo.close();
}

// Contar las faltas de un estudiante especifico
void contarFaltas() {
    string nombreBuscar;
    cin.ignore();

    cout << "\n--- Contar Faltas ---" << endl;
    cout << "Nombre del estudiante: ";
    getline(cin, nombreBuscar);

    ifstream archivo("asistencia.txt");

    if (!archivo.is_open()) {
        cout << "No hay registros." << endl;
        return;
    }

    string linea;
    int totalFaltas = 0;
    int totalRegistros = 0;
 
    // Recorrer el archivo buscando al estudiante
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campos[3];
        int i = 0;
        string campo;
        while (getline(ss, campo, ',') && i < 3) {
            campos[i] = campo;
            i++;
        }
 
        // Contar si el nombre coincide
        if (campos[0] == nombreBuscar) {
            totalRegistros++;
            if (campos[2] == "Ausente") {
                totalFaltas++;
            }
        }
    }
 
    archivo.close();
 
    cout << "\nEstudiante    : " << nombreBuscar << endl;
    cout << "Total registros: " << totalRegistros << endl;
    cout << "Total faltas   : " << totalFaltas << endl;
}
 
int main() {
    int opcion;
    cout << "=== CONTROL DE ASISTENCIA ===" << endl;
 
    do {
        cout << "\n1. Registrar asistencia" << endl;
        cout << "2. Ver historial" << endl;
        cout << "3. Contar faltas de un estudiante" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
 
        if (opcion == 1) registrarAsistencia();
        else if (opcion == 2) mostrarHistorial();
        else if (opcion == 3) contarFaltas();
        else if (opcion != 0) cout << "Opcion invalida." << endl;
 
    } while (opcion != 0);
 
    return 0;
}