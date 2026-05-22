import java.io.*;
import java.util.*;

// Clase Cuenta: representa una cuenta bancaria con usuario y saldo
class Cuenta {
    String usuario;
    double saldo;

    // Constructor: recibe usuario y saldo inicial
    Cuenta(String u, double s) {
        usuario = u;
        saldo = s;
    }

    // Método para guardar la cuenta en archivo
    void guardar() throws IOException {
        FileWriter fw = new FileWriter("cuentas.txt", true); // true → agrega al final
        PrintWriter pw = new PrintWriter(fw);

        pw.println("Usuario : " + usuario);
        pw.println("Saldo   : " + saldo);
        pw.println("------------------------------"); // separador
        pw.close();

        System.out.println("Cuenta registrada ");
    }
}

public class Ejercicio7 {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        int opcion = 0; // inicializamos para evitar errores de compilación

        // Menú principal
        do {
            System.out.println("\n=== MENÚ CAJERO AUTOMÁTICO ===");
            System.out.println("1. Registrar Usuario");
            System.out.println("2. Consultar Saldo");
            System.out.println("3. Depositar Dinero");
            System.out.println("4. Retirar Dinero");
            System.out.println("5. Salir");
            System.out.print("Opción: ");

            // Validación de entrada numérica
            if(!sc.hasNextInt()) {
                System.out.println("Debe ingresar un número válido.");
                sc.nextLine(); // limpiar entrada incorrecta
                continue;
            }
            opcion = sc.nextInt();

            switch(opcion) {
                case 1:
                    // Registrar usuario
                    sc.nextLine(); // limpiar buffer
                    System.out.print("Usuario: "); String usuario = sc.nextLine();
                    System.out.print("Saldo inicial: "); double saldo = sc.nextDouble();

                    Cuenta c = new Cuenta(usuario, saldo);
                    c.guardar();
                    break;

                case 2:
                    // Consultar saldo
                    sc.nextLine();
                    System.out.print("Ingrese usuario: "); String buscar = sc.nextLine();
                    File archivo = new File("cuentas.txt");
                    if(!archivo.exists()) {
                        System.out.println("No hay cuentas registradas.");
                    } else {
                        Scanner lector = new Scanner(archivo);
                        boolean encontrado = false;
                        while(lector.hasNextLine()) {
                            String linea = lector.nextLine();
                            if(linea.startsWith("Usuario") && linea.contains(buscar)) {
                                double saldoActual = Double.parseDouble(lector.nextLine().split(":")[1].trim());
                                System.out.println("Saldo actual de " + buscar + ": " + saldoActual);
                                encontrado = true;
                            }
                        }
                        lector.close();
                        if(!encontrado) {
                            System.out.println("Usuario no encontrado.");
                        }
                    }
                    break;

                case 3:
                    // Depositar dinero
                    sc.nextLine();
                    System.out.print("Ingrese usuario: "); String usuarioDep = sc.nextLine();
                    System.out.print("Monto a depositar: "); double montoDep = sc.nextDouble();

                    actualizarSaldo(usuarioDep, montoDep, true);
                    break;

                case 4:
                    // Retirar dinero
                    sc.nextLine();
                    System.out.print("Ingrese usuario: "); String usuarioRet = sc.nextLine();
                    System.out.print("Monto a retirar: "); double montoRet = sc.nextDouble();

                    actualizarSaldo(usuarioRet, montoRet, false);
                    break;

                case 5:
                    // Salir del programa
                    System.out.println("Fin del programa.");
                    break;

                default:
                    System.out.println("Opción inválida. Intente nuevamente.");
            }
        } while(opcion != 5);

        sc.close(); // cerrar Scanner principal
    }

    // Método auxiliar para actualizar saldo (depósito o retiro)
    static void actualizarSaldo(String usuario, double monto, boolean deposito) throws IOException {
        File archivo = new File("cuentas.txt");
        if(!archivo.exists()) {
            System.out.println("No hay cuentas registradas.");
            return;
        }

        // Leer todas las cuentas en memoria
        Scanner lector = new Scanner(archivo);
        ArrayList<Cuenta> cuentas = new ArrayList<>();
        while(lector.hasNextLine()) {
            String linea = lector.nextLine();
            if(linea.startsWith("Usuario")) {
                String u = linea.split(":")[1].trim();
                double s = Double.parseDouble(lector.nextLine().split(":")[1].trim());
                cuentas.add(new Cuenta(u, s));
                if(lector.hasNextLine()) lector.nextLine(); // separador
            }
        }
        lector.close();

        // Buscar usuario y actualizar saldo
        boolean encontrado = false;
        for(Cuenta c : cuentas) {
            if(c.usuario.equals(usuario)) {
                if(deposito) {
                    c.saldo += monto;
                    System.out.println("Depósito realizado. Nuevo saldo: " + c.saldo);
                } else {
                    if(monto > c.saldo) {
                        System.out.println("Saldo insuficiente.");
                    } else {
                        c.saldo -= monto;
                        System.out.println("Retiro realizado. Nuevo saldo: " + c.saldo);
                    }
                }
                encontrado = true;
            }
        }

        if(!encontrado) {
            System.out.println("Usuario no encontrado.");
        }

        // Reescribir archivo con saldos actualizados
        PrintWriter pw = new PrintWriter(new FileWriter("cuentas.txt"));
        for(Cuenta c : cuentas) {
            pw.println("Usuario : " + c.usuario);
            pw.println("Saldo   : " + c.saldo);
            pw.println("------------------------------");
        }
        pw.close();
    }
}
