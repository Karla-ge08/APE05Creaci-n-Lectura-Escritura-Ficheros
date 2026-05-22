import java.io.*;
import java.util.*;

class Producto {
    String codigo, nombre;
    int cantidad;
    double precio;

    Producto(String c, String n, int cant, double p) {
        codigo = c;
        nombre = n;
        cantidad = cant;
        precio = p;
    }

    // Guardar producto en archivo
    void guardar() throws IOException {
        FileWriter fw = new FileWriter("inventario.txt", true);
        PrintWriter pw = new PrintWriter(fw);
        pw.println("Código   : " + codigo);
        pw.println("Nombre   : " + nombre);
        pw.println("Cantidad : " + cantidad);
        pw.println("Precio   : " + precio);
        pw.println("------------------------------");
        pw.close();
        System.out.println(" Producto registrado.");
    }

    // Calcular valor total de este producto
    double valorTotal() {
        return cantidad * precio;
    }
}

public class Ejercicio3 {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        int opcion;

        do {
            System.out.println("\n=== MENÚ INVENTARIO ===");
            System.out.println("1. Registrar Producto");
            System.out.println("2. Mostrar Inventario");
            System.out.println("3. Calcular Valor Total");
            System.out.println("4. Salir");
            System.out.print("Opción: ");
            opcion = sc.nextInt();

            switch(opcion) {
                case 1:
                    sc.nextLine(); // limpiar buffer
                    System.out.print("Código: "); String codigo = sc.nextLine();
                    System.out.print("Nombre: "); String nombre = sc.nextLine();
                    System.out.print("Cantidad: "); int cantidad = sc.nextInt();
                    System.out.print("Precio: "); double precio = sc.nextDouble();

                    Producto p = new Producto(codigo, nombre, cantidad, precio);
                    p.guardar();
                    break;

                case 2:
                    File archivo = new File("inventario.txt");
                    if(!archivo.exists()) {
                        System.out.println(" No hay productos registrados.");
                    } else {
                        Scanner lector = new Scanner(archivo);
                        while(lector.hasNextLine()) {
                            System.out.println(lector.nextLine());
                        }
                        lector.close();
                    }
                    break;

                case 3:
                    File archivo2 = new File("inventario.txt");
                    if(!archivo2.exists()) {
                        System.out.println(" No hay productos registrados.");
                    } else {
                        Scanner lector = new Scanner(archivo2);
                        double totalInventario = 0;
                        while(lector.hasNextLine()) {
                            String linea = lector.nextLine();
                            if(linea.startsWith("Cantidad")) {
                                int cant = Integer.parseInt(linea.split(":")[1].trim());
                                double precioProd = Double.parseDouble(lector.nextLine().split(":")[1].trim());
                                totalInventario += cant * precioProd;
                                if(lector.hasNextLine()) lector.nextLine(); // separador
                            }
                        }
                        lector.close();
                        System.out.println(" Valor total del inventario: " + totalInventario);
                    }
                    break;

                case 4:
                    System.out.println(" Fin del programa.");
                    break;

                default:
                    System.out.println("Opción inválida.");
            }
        } while(opcion != 4);

        sc.close();
    }
}

