#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
 
using namespace std;
 
// Clase CuentaBancaria
class CuentaBancaria {
public:
    string usuario;
    float saldo;

    // Cargar los datos desde el archivo
    bool cargarDesdeArchivo() {
        ifstream archivo("cuenta.txt");
 
        if (!archivo.is_open()) {
            return false;
        }

        string linea;
        getline(archivo, linea);
        archivo.close();

        // Separar el usuario y el saldo
        stringstream ss(linea);
        string campo;
        getline(ss, campo, ',');
        usuario = campo;
        getline(ss, campo, ',');
        saldo = stof(campo);

        return true;
    }

    // Guardar o actualizar los datos en el archivo
    void guardarEnArchivo() {
        ofstream archivo("cuenta.txt");
 
        if (archivo.is_open()) {
            archivo << usuario << "," << saldo << endl;
            archivo.close();
        } else {
            cout << "Error al guardar." << endl;
        }
    }

    // Crear una cuenta nueva
    void crearCuenta() {
        cin.ignore();
        cout << "Nombre de usuario: ";
        getline(cin, usuario);

        cout << "Saldo inicial    : $";
        cin >> saldo;

        guardarEnArchivo();
        cout << "Cuenta creada para: " << usuario << endl;
    }

    // Mostrar el saldo actual
    void consultarSaldo() {
        cout << "\nUsuario: " << usuario << endl;
        cout << "Saldo  : $" << saldo << endl;
    }

    // Depositar dinero
    void depositar() {
        float monto;
        cout << "Monto a depositar: $";
        cin >> monto;

        // Validar que el monto sea positivo
        if (monto <= 0) {
            cout << "El monto debe ser mayor a 0." << endl;
            return;
        }

        saldo += monto;
        guardarEnArchivo();
        cout << "Deposito realizado. Nuevo saldo: $" << saldo << endl;
    }

    // Retirar dinero
    void retirar() {
        float monto;
        cout << "Monto a retirar: $";
        cin >> monto;

        // Validar que haya suficiente saldo
        if (monto <= 0) {
            cout << "El monto debe ser mayor a 0." << endl;
            return;
        }

        if (monto > saldo) {
            cout << "Saldo insuficiente. Saldo disponible: $" << saldo << endl;
            return;
        }

        saldo -= monto;
        guardarEnArchivo();
        cout << "Retiro realizado. Nuevo saldo: $" << saldo << endl;
    }
};

int main() {
    cout << "=== CAJERO AUTOMATICO ===" << endl;

    CuentaBancaria cuenta;

    // Cargar una cuenta existente
    if (!cuenta.cargarDesdeArchivo()) {
        cout << "\nNo existe una cuenta. Vamos a crear una." << endl;
        cuenta.crearCuenta();
    } else {
        cout << "\nCuenta cargada: " << cuenta.usuario << endl;
    }

    int opcion;

    do {
        cout << "\n1. Consultar saldo" << endl;
        cout << "2. Depositar" << endl;
        cout << "3. Retirar" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) cuenta.consultarSaldo();
        else if (opcion == 2) cuenta.depositar();
        else if (opcion == 3) cuenta.retirar();
        else if (opcion != 0) cout << "Opcion invalida." << endl;

    } while (opcion != 0);

    cout << "Gracias por usar el cajero." << endl;
    return 0;
}