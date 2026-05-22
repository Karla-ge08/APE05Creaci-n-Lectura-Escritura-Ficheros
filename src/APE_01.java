import java.io.*;
import java.util.Scanner;
class Estudiante {
    String cedula, nombre, carrera;
    double promedio;

    Estudiante(String c, String n, String ca, double p) {
        cedula = c;
        nombre = n;
        carrera = ca;
        promedio = p;
    }

    // Método para guardar en archivo de forma ordenada
    void guardar() throws IOException {
        if(promedio < 0 || promedio > 10) {
            System.out.println("Promedio inválido (0-10).");
            return;
        }

        FileWriter fw = new FileWriter("estudiantes.txt", true);
        PrintWriter pw = new PrintWriter(fw);

        pw.println("Cédula   : " + cedula);
        pw.println("Nombre   : " + nombre);
        pw.println("Carrera  : " + carrera);
        pw.println("Promedio : " + promedio);
        pw.println("------------------------------");
        pw.close();

        System.out.println("Estudiante registrado.");
    }
}

public class Ejercicio1 {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        int opcion;

        do {
            System.out.println("\n=== MENÚ ===");
            System.out.println("1. Registrar Estudiante");
            System.out.println("2. Mostrar Estudiantes");
            System.out.println("3. Salir");
            System.out.print("Opción: ");
            opcion = sc.nextInt();

            switch(opcion) {
                case 1:
                    sc.nextLine(); // limpiar buffer
                    System.out.print("Cédula: "); 
                    String cedula = sc.nextLine();

                    // Validar que el nombre solo tenga letras
                    String nombre;
                    do {
                        System.out.print("Nombre: ");
                        nombre = sc.nextLine();
                        if(!nombre.matches("[a-zA-Z ]+")) {
                            System.out.println("Nombre inválido. Use solo letras.");
                        }
                    } while(!nombre.matches("[a-zA-Z ]+"));

                    // Validar que la carrera solo tenga letras
                    String carrera;
                    do {
                        System.out.print("Carrera : ");
                        carrera = sc.nextLine();
                        if(!carrera.matches("[a-zA-Z ]+")) {
                            System.out.println("Carrera inválida. Use solo letras.");
                        }
                    } while(!carrera.matches("[a-zA-Z ]+"));

                    System.out.print("Promedio (0-10): ");
                    double promedio = sc.nextDouble();

                    Estudiante e = new Estudiante(cedula, nombre, carrera, promedio);
                    e.guardar();
                    break;

                case 2:
                    File archivo = new File("estudiantes.txt");
                    if(!archivo.exists()) {
                        System.out.println("No hay registros. Archivo creado vacío.");
                        archivo.createNewFile();
                    } else {
                        Scanner lector = new Scanner(archivo);
                        while(lector.hasNextLine()) {
                            System.out.println(lector.nextLine());
                        }
                        lector.close();
                    }
                    break;

                case 3:
                    System.out.println("Fin del programa.");
                    break;

                default:
                    System.out.println("Opción inválida.");
            }
        } while(opcion != 3);
    }
}
