import java.io.*;
import java.util.*;

class Contacto {
    String nombre, telefono, correo;

    Contacto(String n, String t, String c) {
        nombre = n;
        telefono = t;
        correo = c;
    }

    // Guardar contacto en archivo
    void guardar() throws IOException {
        FileWriter fw = new FileWriter("agenda.txt", true);
        PrintWriter pw = new PrintWriter(fw);
        pw.println("Nombre   : " + nombre);
        pw.println("Teléfono : " + telefono);
        pw.println("Correo   : " + correo);
        pw.println("------------------------------");
        pw.close();
        System.out.println("Contacto agregado.");
    }
}

public class Ejercicio4 {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        int opcion;

        do {
            System.out.println("\n=== MENÚ AGENDA ===");
            System.out.println("1. Agregar Contacto");
            System.out.println("2. Buscar Contacto");
            System.out.println("3. Mostrar Todos");
            System.out.println("4. Salir");
            System.out.print("Opción: ");
            opcion = sc.nextInt();

            switch(opcion) {
                case 1:
                    sc.nextLine();
                    System.out.print("Nombre: "); String nombre = sc.nextLine();
                    System.out.print("Teléfono: "); String telefono = sc.nextLine();
                    System.out.print("Correo: "); String correo = sc.nextLine();

                    Contacto c = new Contacto(nombre, telefono, correo);
                    c.guardar();
                    break;

                case 2:
                    sc.nextLine();
                    System.out.print("Ingrese nombre a buscar: ");
                    String buscar = sc.nextLine();
                    File archivo = new File("agenda.txt");
                    if(!archivo.exists()) {
                        System.out.println(" No hay contactos registrados.");
                    } else {
                        Scanner lector = new Scanner(archivo);
                        boolean encontrado = false;
                        while(lector.hasNextLine()) {
                            String linea = lector.nextLine();
                            if(linea.startsWith("Nombre") && linea.contains(buscar)) {
                                System.out.println(linea);
                                System.out.println(lector.nextLine()); // Teléfono
                                System.out.println(lector.nextLine()); // Correo
                                encontrado = true;
                            }
                        }
                        lector.close();
                        if(!encontrado) {
                            System.out.println(" Contacto no encontrado.");
                        }
                    }
                    break;

                case 3:
                    File archivo2 = new File("agenda.txt");
                    if(!archivo2.exists()) {
                        System.out.println(" No hay contactos registrados.");
                    } else {
                        Scanner lector = new Scanner(archivo2);
                        while(lector.hasNextLine()) {
                            System.out.println(lector.nextLine());
                        }
                        lector.close();
                    }
                    break;

                case 4:
                    System.out.println(" Fin del programa.");
                    break;

                default:
                    System.out.println(" Opción inválida.");
            }
        } while(opcion != 4);

        sc.close();
    }
}
