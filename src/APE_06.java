import java.io.*;
import java.util.*;

// Clase Asistencia: representa un registro de asistencia de un estudiante
class Asistencia {
    String nombre, fecha, estado;

    // Constructor: recibe nombre, fecha y estado
    Asistencia(String n, String f, String e) {
        nombre = n;
        fecha = f;
        estado = e;
    }

    // Método para guardar el registro en el archivo asistencia.txt
    void guardar() throws IOException {
        FileWriter fw = new FileWriter("asistencia.txt", true); // true → agrega al final
        PrintWriter pw = new PrintWriter(fw);

        pw.println("Nombre : " + nombre);
        pw.println("Fecha  : " + fecha);
        pw.println("Estado : " + estado);
        pw.println("------------------------------"); // separador
        pw.close();

        System.out.println("Registro guardado ");
    }
}

public class Ejercicio6 {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        int opcion = 0; // inicializamos para evitar error de compilación

        // Menú principal con ciclo controlado
        do {
            System.out.println("\n=== MENÚ CONTROL DE ASISTENCIA ===");
            System.out.println("1. Registrar Asistencia");
            System.out.println("2. Mostrar Historial");
            System.out.println("3. Contar Faltas");
            System.out.println("4. Salir");
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
                    // Registrar asistencia
                    sc.nextLine(); // limpiar buffer
                    System.out.print("Nombre: "); 
                    String nombre = sc.nextLine();

                    // Validación de fecha con formato dd/mm/aaaa
                    String fecha;
                    while(true) {
                        System.out.print("Fecha (dd/mm/aaaa): "); 
                        fecha = sc.nextLine();
                        if(fecha.matches("\\d{2}/\\d{2}/\\d{4}")) {
                            break;
                        } else {
                            System.out.println("Formato inválido. Use dd/mm/aaaa.");
                        }
                    }

                    System.out.print("Estado (Presente/Falta): "); 
                    String estado = sc.nextLine();

                    // Validación estricta del estado
                    if(!estado.equalsIgnoreCase("Presente") && !estado.equalsIgnoreCase("Falta")) {
                        System.out.println("Estado inválido. Use 'Presente' o 'Falta'.");
                    } else {
                        Asistencia a = new Asistencia(nombre, fecha, estado);
                        a.guardar();
                    }
                    break;

                case 2:
                    // Mostrar historial completo
                    File archivo = new File("asistencia.txt");
                    if(!archivo.exists()) {
                        System.out.println("No hay registros de asistencia.");
                    } else {
                        Scanner lector = new Scanner(archivo);
                        while(lector.hasNextLine()) {
                            System.out.println(lector.nextLine());
                        }
                        lector.close();
                    }
                    break;

                case 3:
                    // Contar faltas
                    File archivo2 = new File("asistencia.txt");
                    if(!archivo2.exists()) {
                        System.out.println("No hay registros de asistencia.");
                    } else {
                        Scanner lector = new Scanner(archivo2);
                        int faltas = 0;
                        while(lector.hasNextLine()) {
                            String linea = lector.nextLine();
                            if(linea.startsWith("Estado") && linea.contains("Falta")) {
                                faltas++;
                            }
                        }
                        lector.close();
                        System.out.println("Total de faltas registradas: " + faltas);
                    }
                    break;

                case 4:
                    // Salir del programa
                    System.out.println("Fin del programa.");
                    break;

                default:
                    System.out.println("Opción inválida. Intente nuevamente.");
            }
        } while(opcion != 4);

        sc.close(); // cerrar Scanner principal
    }
}
