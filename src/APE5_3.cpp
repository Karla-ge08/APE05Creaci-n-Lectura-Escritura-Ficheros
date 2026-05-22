#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
 
// Clase Producto
class Producto {
public:
    string codigo;
    string nombre;
    int cantidad;
    float precio;
 
    // Calcular el valor total de este producto
    float calcularValorTotal() {
        return cantidad * precio;
    }
 
    // Pedir los datos del producto al usuario
    void ingresarDatos() {
        cout << "Codigo del producto: ";
        cin >> codigo;
        cin.ignore();
 
        cout << "Nombre del producto: ";
        getline(cin, nombre);
 
        cout << "Cantidad en stock  : ";
        cin >> cantidad;
 
        cout << "Precio unitario    : ";
        cin >> precio;
    }
 
    // Guardar el producto en el archivo
    void guardarEnArchivo() {
        ofstream archivo("inventario.txt", ios::app);
 
        if (archivo.is_open()) {
            // Guardar todos los campos separados por comas
            archivo << codigo << "," << nombre << "," << cantidad << "," << precio << endl;
            archivo.close();
            cout << "\nProducto guardado en inventario.txt" << endl;
            cout << "Valor total de este producto: $" << calcularValorTotal() << endl;
        } else {
            cout << "Error al abrir el archivo." << endl;
        }
    }
};
 
// Calcular el valor total de todo el inventario
void mostrarValorInventario() {
    ifstream archivo("inventario.txt");
 
    if (!archivo.is_open()) {
        cout << "No existe el archivo inventario.txt aun." << endl;
        return;
    }
 
    string linea;
    float totalInventario = 0;
    int totalProductos = 0;
 
    cout << "\n=== INVENTARIO ACTUAL ===" << endl;
    cout << "--------------------------------------------" << endl;
 
    // Recorrer cada linea del archivo
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;
        string campos[4];
        int i = 0;
 
        // Separar la linea por comas
        while (getline(ss, campo, ',') && i < 4) {
            campos[i] = campo;
            i++;
        }
 
        int cant = stoi(campos[2]);
        float prec = stof(campos[3]);
        float valorProducto = cant * prec;
 
        cout << "Codigo: " << campos[0] << " | " << campos[1]
             << " | Cant: " << cant << " | $" << prec
             << " | Total: $" << valorProducto << endl;
 
        totalInventario += valorProducto;
        totalProductos++;
    }
 
    archivo.close();
 
    cout << "--------------------------------------------" << endl;
    cout << "Total de productos distintos: " << totalProductos << endl;
    cout << "Valor total del inventario  : $" << totalInventario << endl;
}
 
int main() {
    cout << "=== SISTEMA DE INVENTARIO ===" << endl << endl;
 
    // Crear un objeto producto y registramos sus datos
    Producto prod;
    prod.ingresarDatos();
    prod.guardarEnArchivo();
 
    // Mostrar el inventario completo
    mostrarValorInventario();
 
    return 0;
}