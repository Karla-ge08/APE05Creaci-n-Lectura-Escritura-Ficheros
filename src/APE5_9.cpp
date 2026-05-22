#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
 
using namespace std;
 
// Clase Venta
class Venta {
public:
    string producto;
    int cantidad;
    float precio;
    float total;
 
    // Ingresar los datos de la venta
    void ingresarDatos() {
        cin.ignore();
 
        cout << "Producto  : ";
        getline(cin, producto);
 
        cout << "Cantidad  : ";
        cin >> cantidad;
 
        cout << "Precio unitario: $";
        cin >> precio;
 
        // Calcular el total automaticamente
        total = cantidad * precio;
    }
 
    // Mostrar la factura en pantalla
    void generarFactura() {
        cout << "\n========== FACTURA ==========" << endl;
        cout << "Producto  : " << producto << endl;
        cout << "Cantidad  : " << cantidad << endl;
        cout << "P. Unitario: $" << precio << endl;
        cout << "-----------------------------" << endl;
        cout << "TOTAL     : $" << total << endl;
        cout << "=============================" << endl;
    }
 
    // Guardar la venta en ventas.txt
    void guardarEnArchivo() {
        ofstream archivo("ventas.txt", ios::app);
 
        if (archivo.is_open()) {
            archivo << producto << "," << cantidad << "," << precio << "," << total << endl;
            archivo.close();
            cout << "Venta registrada en ventas.txt" << endl;
        } else {
            cout << "Error al guardar." << endl;
        }
    }
};
 
// Mostrar el historial de todas las ventas
void mostrarHistorial() {
    ifstream archivo("ventas.txt");
 
    if (!archivo.is_open()) {
        cout << "No hay ventas registradas." << endl;
        return;
    }
 
    string linea;
    float totalGeneral = 0;
    int numeroVenta = 1;
 
    cout << "\n=== HISTORIAL DE VENTAS ===" << endl;
 
    // Leer cada venta registrada
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campos[4];
        int i = 0;
        string campo;
        while (getline(ss, campo, ',') && i < 4) {
            campos[i] = campo;
            i++;
        }
 
        float totalVenta = stof(campos[3]);
 
        cout << "Venta #" << numeroVenta << ": "
             << campos[0] << " | Cant: " << campos[1]
             << " | $" << campos[2] << " c/u"
             << " | Total: $" << campos[3] << endl;
 
        totalGeneral += totalVenta;
        numeroVenta++;
    }
 
    archivo.close();
 
    cout << "----------------------------" << endl;
    cout << "Total general de ventas: $" << totalGeneral << endl;
}
 
int main() {
    int opcion;
    cout << "=== SISTEMA DE VENTAS ===" << endl;
 
    do {
        cout << "\n1. Registrar nueva venta" << endl;
        cout << "2. Ver historial de ventas" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
 
        if (opcion == 1) {
            Venta venta;
            venta.ingresarDatos();
            venta.generarFactura();
            venta.guardarEnArchivo();
        }
        else if (opcion == 2) mostrarHistorial();
        else if (opcion != 0) cout << "Opcion invalida." << endl;
 
    } while (opcion != 0);
 
    return 0;
}