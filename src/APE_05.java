import java.io.*;
import java.util.*;

// Clase Alumno: representa a un estudiante con sus notas y estado
class Alumno {
    String nombre;
    double nota1, nota2, nota3, promedio;
    String estado;

    // Constructor: recibe nombre y 3 notas
    Alumno(String n, double n1, double n2, double n3) {
        nombre = n;
        nota1 = n1;
        nota2 = n2;
        nota3 = n3;

        // Calculamos el promedio al crear el objeto
        promedio = (nota1 + nota2 + nota3) / 3;

        // Determinamos si está aprobado o reprobado
        estado = (promedio >= 7) ? "Aprobado" : "Reprobado";
    }

    // Método para guardar los datos del alumno en el archivo notas.txt
    void guardar() throws IOException {
        FileWriter fw = new FileWriter("notas.txt", true); // true → agrega al final
        PrintWriter pw = new PrintWriter(fw);

        // Guardamos cada dato con etiqueta
        pw.println("Nombre   : " + nombre);
        pw.println("Nota 1   : " + nota1);
        pw.println("Nota 2   : " + nota2);
        pw.println("Nota 3   : " + nota3);
        pw.println("Promedio : " + promedio);
        pw.println("Estado   : " + estado);
        pw.println("------------------------------"); // separador
        pw.close();

        System.out.println("Alumno registrado ");
    }
}

// Clase principal Ejercicio5
public class Ejercicio5 {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in); // Scanner para leer teclado
        int opcion;

        // Menú principal
        do {
            System.out.println("\n=== MENÚ SISTEMA DE NOTAS ===");
            System.out.println("1. Registrar Alumno");
            System.out.println("2. Mostrar Alumnos");
            System.out.println("3. Salir");
            System.out.print("Opción: ");
            opcion = sc.nextInt();

            switch(opcion) {
                case 1:
                    // Registrar alumno
                    sc.nextLine(); // limpiar buffer
                    System.out.print("Nombre: "); String nombre = sc.nextLine();
                    System.out.print("Nota 1: "); double n1 = sc.nextDouble();
                    System.out.print("Nota 2: "); double n2 = sc.nextDouble();
                    System.out.print("Nota 3: "); double n3 = sc.nextDouble();

                    // Crear objeto Alumno y guardar en archivo
                    Alumno a = new Alumno(nombre, n1, n2, n3);
                    a.guardar();
                    break;

                case 2:
                    // Mostrar todos los alumnos registrados
                    File archivo = new File("notas.txt");
                    if(!archivo.exists()) {
                        System.out.println("No hay alumnos registrados.");
                    } else {
                        Scanner lector = new Scanner(archivo);
                        while(lector.hasNextLine()) {
                            System.out.println(lector.nextLine()); // imprime línea por línea
                        }
                        lector.close();
                    }
                    break;

                case 3:
                    // Salir del programa
                    System.out.println("Fin del programa.");
                    break;

                default:
                    System.out.println("Opción inválida.");
            }
        } while(opcion != 3);

        sc.close(); // cerramos el Scanner principal
    }
}
