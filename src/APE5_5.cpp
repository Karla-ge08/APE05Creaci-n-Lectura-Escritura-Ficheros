#include <iostream>
#include <fstream>
#include <string>
using namespace std;
 
// Clase Estudiante
class EstudianteNotas {
public:
    string nombre;
    float nota1;
    float nota2;
    float nota3;

    // Calcular el promedio de las tres notas
    float calcularPromedio() {
        return (nota1 + nota2 + nota3) / 3;
    }

    // Indicar si el estudiante aprobo o reprobo
    string obtenerEstado() {
        if (calcularPromedio() >= 7.0) {
            return "APROBADO";
        } else {
            return "REPROBADO";
        }
    }

    // Ingresar los datos del estudiante
    void ingresarDatos() {

        cout << "Nombre del estudiante: ";
        getline(cin, nombre);
 
        cout << "Nota 1 (sobre 10): ";
        cin >> nota1;
 
        cout << "Nota 2 (sobre 10): ";
        cin >> nota2;
 
        cout << "Nota 3 (sobre 10): ";
        cin >> nota3;

    }

    // Mostrar el resultado en pantalla
    void mostrarResultado() {
        float promedio = calcularPromedio();
        string estado = obtenerEstado();

        cout << "\n--- Resultado ---" << endl;
        cout << "Estudiante: " << nombre << endl;
        cout << "Nota 1    : " << nota1 << endl;
        cout << "Nota 2    : " << nota2 << endl;
        cout << "Nota 3    : " << nota3 << endl;
        cout << "Promedio  : " << promedio << endl;
        cout << "Estado    : " << estado << endl;
    }

    // Guardar los datos en el archivo notas.txt
    void guardarEnArchivo() {
        ofstream archivo("notas.txt", ios::app);

        if (archivo.is_open()) {
            // Guardar nombre, notas, promedio y estado
            archivo << nombre << ","
                    << nota1 << ","
                    << nota2 << ","
                    << nota3 << ","
                    << calcularPromedio() << ","
                    << obtenerEstado() << endl;

            archivo.close();
            cout << "Datos guardados en notas.txt" << endl;
        } else {
            cout << "Error al guardar." << endl;
        }
    }
};

int main() {
    cout << "=== SISTEMA DE NOTAS ===" << endl;

    // Crear el objeto y usar sus metodos
    EstudianteNotas est;
    est.ingresarDatos();
    est.mostrarResultado();
    est.guardarEnArchivo();

    return 0;
}