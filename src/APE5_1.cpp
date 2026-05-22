#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Clase Estudiante
class Estudiante {
private:
    // Atributos privados del estudiante
    string cedula;
    string nombre;
    string carrera;
    float  promedio;
 
public:
    // Constructor de la clase Estudiantes
    Estudiante(string ced, string nom, string car, float prom) {
        cedula   = ced;
        nombre   = nom;
        carrera  = car;
        promedio = prom;
    }
 

    // Escribir los datos del estudiante en el archivo indicado.
    void guardarEnArchivo(ofstream &archivo) {
        archivo << cedula   << "|"
                << nombre   << "|"
                << carrera  << "|"
                << promedio << "\n";
    }
 
    
    // Imprimir en consola los datos del estudiante
    void mostrarDatos() {
        cout << "  Cedula  : " << cedula   << "\n"
             << "  Nombre  : " << nombre   << "\n"
             << "  Carrera : " << carrera  << "\n"
             << "  Promedio: " << promedio << "\n";
    }
 
    
    // Pedir los datos al usuario y devuelve un objeto Estudiante
    static Estudiante solicitarDatos() {
        string ced, nom, car;
        float  prom;
 
        cout << "\n--- Ingreso de datos del estudiante ---\n";
        cout << "Cedula   : "; cin >> ced;
        cin.ignore();
        cout << "Nombre   : "; getline(cin, nom);
        cout << "Carrera  : "; getline(cin, car);
        cout << "Promedio : "; cin >> prom;
 
        return Estudiante(ced, nom, car, prom);
    }
};
 

int main() {
    cout << "========================================\n"
         << "   SISTEMA DE REGISTRO DE ESTUDIANTES  \n"
         << "========================================\n";
 
    char continuar = 's';
 
    // Abrir el archivo
    ofstream archivo("estudiantes.txt", ios::app);
 
    // Verificar que el archivo se abrió correctamente
    if (!archivo.is_open()) {
        cerr << "ERROR: No se pudo abrir/crear el archivo estudiantes.txt\n";
        return 1;
    }
 
    // Registrar uno o más estudiantes
    while (continuar == 's' || continuar == 'S') {
 
        Estudiante est = Estudiante::solicitarDatos();
        est.guardarEnArchivo(archivo);

        cout << "\nEstudiante registrado exitosamente:\n";
        est.mostrarDatos();
 
        cout << "\nDesea registrar otro estudiante? (s/n): ";
        cin >> continuar;
    }
 
    // Cerrar el archivo para liberar recursos
    archivo.close();   // Cierra el archivo para liberar recursos
    cout << "\nDatos guardados en 'estudiantes.txt'.\n";
 
    return 0;
}