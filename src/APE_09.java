import java.io.*;
import java.util.*;

// Clase Venta: representa una venta con producto, cantidad, precio y total
class Venta {
    String producto;
    int cantidad;
    double precio;
    double total;

    // Constructor: recibe producto, cantidad y precio
    Venta(String p, int c, double pr) {
        producto = p;
        cantidad = c;
        precio = pr;
        total = cantidad * precio; // cálculo automático del total
    }

    // Método para guardar la venta en archivo
    void guardar() throws IOException {
        FileWriter fw = new FileWriter("ventas.txt", true); // true → agrega al final
        PrintWriter pw = new PrintWriter(fw);

        pw.println("Producto : " + producto);
        pw.println("Cantidad : " + cantidad);
        pw.println("Precio   : " + precio);
        pw.println("Total    : " + total);
        pw.println("------------------------------"); // separador
        pw.close();

        System.out.println("Venta registrada");
    }

    // Método para mostrar la factura de la venta
    void mostrarFactura() {
        System.out.println("\n=== FACTURA ===");
        System.out.println("Producto : " + producto);
        System.out.println("Cantidad : " + cantidad);
        System.out.println("Precio   : " + precio);
        System.out.println("Total    : " + total);
    }
}

public class Ejercicio9 {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        int opcion = 0; // inicializamos para evitar errores de compilación

        // Menú principal
        do {
            System.out.println("\n=== MENÚ SISTEMA DE VENTAS ===");
            System.out.println("1. Registrar Venta");
            System.out.println("2. Mostrar Historial de Ventas");
            System.out.println("3. Salir");
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
                    // Registrar venta
                    sc.nextLine(); // limpiar buffer
                    System.out.print("Producto: "); String producto = sc.nextLine();

                    // Validación de cantidad
                    int cantidad;
                    while(true) {
                        System.out.print("Cantidad: ");
                        if(sc.hasNextInt()) {
                            cantidad = sc.nextInt();
                            if(cantidad > 0) break;
                            else System.out.println("La cantidad debe ser mayor a 0.");
                        } else {
                            System.out.println("Debe ingresar un número entero.");
                            sc.nextLine();
                        }
                    }

                    // Validación de precio
                    double precio;
                    while(true) {
                        System.out.print("Precio: ");
                        if(sc.hasNextDouble()) {
                            precio = sc.nextDouble();
                            if(precio > 0) break;
                            else System.out.println("El precio debe ser mayor a 0.");
                        } else {
                            System.out.println("Debe ingresar un número válido.");
                            sc.nextLine();
                        }
                    }

                    // Crear objeto Venta y guardar
                    Venta v = new Venta(producto, cantidad, precio);
                    v.guardar();
                    v.mostrarFactura();
                    break;

                case 2:
                    // Mostrar historial completo de ventas
                    File archivo = new File("ventas.txt");
                    if(!archivo.exists()) {
                        System.out.println("No hay ventas registradas.");
                    } else {
                        Scanner lector = new Scanner(archivo);
                        System.out.println("\n=== HISTORIAL DE VENTAS ===");
                        while(lector.hasNextLine()) {
                            System.out.println(lector.nextLine());
                        }
                        lector.close();
                    }
                    break;

                case 3:
                    // Salir del programa
                    System.out.println("Fin del programa.");
                    break;

                default:
                    System.out.println("Opción inválida. Intente nuevamente.");
            }
        } while(opcion != 3);

        sc.close(); // cerrar Scanner principal
    }
}
