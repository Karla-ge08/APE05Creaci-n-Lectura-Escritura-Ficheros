#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>    
using namespace std;
 
//Clase estudiante
class Estudiante {
public:
    string cedula;
    string nombre;
    string carrera;
    float  promedio;
 
    Estudiante() : promedio(0.0f) {}
 
    // Constructor con parámetros
    Estudiante(string ced, string nom, string car, float prom)
        : cedula(ced), nombre(nom), carrera(car), promedio(prom) {}
 

    // Imprimir los datos de un estudiante con formato de tabla

    void mostrar(int numero) const {
        cout << left
             << setw(4)  << numero
             << setw(12) << cedula
             << setw(22) << nombre
             << setw(20) << carrera
             << fixed << setprecision(2) << promedio << "\n";
    }
};
 
class LectorEstudiantes {
private:
    vector<Estudiante> lista;
    string nombreArchivo;

    // Divide una línea del archivo usando '|' como separador
    bool parsearLinea(const string &linea, Estudiante &est) {
        stringstream ss(linea);
        string campo;
        vector<string> campos;
 
        while (getline(ss, campo, '|')) {
            campos.push_back(campo);
        }
 
        if (campos.size() != 4) return false;
 
        est.cedula   = campos[0];
        est.nombre   = campos[1];
        est.carrera  = campos[2];
        est.promedio = stof(campos[3]); 
        return true;
    }
 
public:
    // Recibe el nombre del archivo a leer
    LectorEstudiantes(string archivo) : nombreArchivo(archivo) {}
 
    bool cargarArchivo() {
        ifstream archivo(nombreArchivo);
 
        if (!archivo.is_open()) {
            cerr << "ERROR: No se encontró el archivo '" << nombreArchivo << "'\n"
                 << "Asegúrese de ejecutar primero el Ejercicio 1.\n";
            return false;
        }
 
        string linea;
        lista.clear();
 
        // Recorrer línea por línea con un ciclo while
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;
 
            Estudiante est;
            if (parsearLinea(linea, est)) {
                lista.push_back(est);
            }
        }
 
        archivo.close();
        return true;
    }
 

    // Imprimir todos los registros en formato de tabla
    void mostrarTodos() const {
        if (lista.empty()) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
 
        cout << "\n========== LISTA DE ESTUDIANTES ==========\n";
        cout << left
             << setw(4)  << "N-"
             << setw(12) << "Cedula"
             << setw(22) << "Nombre"
             << setw(20) << "Carrera"
             << "Promedio\n";
        cout << string(65, '-') << "\n";
 
        // Ciclo for para recorrer el arreglo e imprimir cada elemento
        for (int i = 0; i < (int)lista.size(); i++) {
            lista[i].mostrar(i + 1);
        }
        cout << string(65, '-') << "\n";
    }
 
    // Retorna el número total de estudiantes registrados

    int contarEstudiantes() const {
        return (int)lista.size();
    }
 

    // Calcula y retorna el promedio de todos los promedios
    float calcularPromedioGeneral() const {
        if (lista.empty()) return 0.0f;
 
        float suma = 0.0f;
        // Ciclo que acumula todos los promedios individuales
        for (const Estudiante &est : lista) {
            suma += est.promedio;
        }
        return suma / lista.size();
    }
};
 

int main() {
    cout << "========================================\n"
         << "   LECTURA DE ARCHIVO DE ESTUDIANTES   \n"
         << "========================================\n";
 
    // Crea el objeto lector apuntando al archivo del ejercicio 1
    LectorEstudiantes lector("estudiantes.txt");
 
    if (!lector.cargarArchivo()) return 1;
 
    lector.mostrarTodos();

    cout << "\n========== ESTADISTICAS ==========\n";
    cout << "Total de estudiantes : " << lector.contarEstudiantes()  << "\n";
    cout << fixed << setprecision(2)
         << "Promedio general     : " << lector.calcularPromedioGeneral() << "\n";
    cout << "===================================\n";
 
    return 0;
}