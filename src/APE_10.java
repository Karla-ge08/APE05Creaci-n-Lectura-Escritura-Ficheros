import java.io.*;
import java.util.*;

// Clase EstudianteIntegrador: representa un estudiante con cédula, nombre y carrera
class EstudianteIntegrador {
    String cedula, nombre, carrera;

    EstudianteIntegrador(String c, String n, String ca) {
        cedula = c;
        nombre = n;
        carrera = ca;
    }

    // Método para guardar estudiante en archivo
    void guardar(PrintWriter pw) {
        pw.println("Cédula  : " + cedula);
        pw.println("Nombre  : " + nombre);
        pw.println("Carrera : " + carrera);
        pw.println("------------------------------");
    }
}

public class Ejercicio10 {
    static final String ARCHIVO = "integrador.txt";

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        int opcion = 0;

        do {
            System.out.println("\n=== MENÚ PROYECTO INTEGRADOR ===");
            System.out.println("1. Crear Estudiante");
            System.out.println("2. Leer Estudiantes");
            System.out.println("3. Actualizar Estudiante");
            System.out.println("4. Eliminar Estudiante");
            System.out.println("5. Salir");
            System.out.print("Opción: ");

            if(!sc.hasNextInt()) {
                System.out.println("Debe ingresar un número válido.");
                sc.nextLine();
                continue;
            }
            opcion = sc.nextInt();

            switch(opcion) {
                case 1:
                    sc.nextLine();
                    System.out.print("Cédula: "); String cedula = sc.nextLine();
                    System.out.print("Nombre: "); String nombre = sc.nextLine();
                    System.out.print("Carrera: "); String carrera = sc.nextLine();

                    EstudianteIntegrador e = new EstudianteIntegrador(cedula, nombre, carrera);
                    PrintWriter pw = new PrintWriter(new FileWriter(ARCHIVO, true));
                    e.guardar(pw);
                    pw.close();
                    System.out.println("Estudiante registrado.");
                    break;

                case 2:
                    File archivo = new File(ARCHIVO);
                    if(!archivo.exists()) {
                        System.out.println("No hay estudiantes registrados.");
                    } else {
                        Scanner lector = new Scanner(archivo);
                        System.out.println("\n=== LISTA DE ESTUDIANTES ===");
                        while(lector.hasNextLine()) {
                            System.out.println(lector.nextLine());
                        }
                        lector.close();
                    }
                    break;

                case 3:
                    sc.nextLine();
                    System.out.print("Ingrese cédula del estudiante a actualizar: ");
                    String cedulaAct = sc.nextLine();

                    List<EstudianteIntegrador> lista = leerEstudiantes();
                    boolean actualizado = false;

                    for(EstudianteIntegrador est : lista) {
                        if(est.cedula.equals(cedulaAct)) {
                            System.out.print("Nuevo nombre: "); est.nombre = sc.nextLine();
                            System.out.print("Nueva carrera: "); est.carrera = sc.nextLine();
                            actualizado = true;
                        }
                    }

                    if(actualizado) {
                        guardarLista(lista);
                        System.out.println("Estudiante actualizado.");
                    } else {
                        System.out.println("Estudiante no encontrado.");
                    }
                    break;

                case 4:
                    sc.nextLine();
                    System.out.print("Ingrese cédula del estudiante a eliminar: ");
                    String cedulaDel = sc.nextLine();

                    List<EstudianteIntegrador> listaDel = leerEstudiantes();
                    boolean eliminado = listaDel.removeIf(est -> est.cedula.equals(cedulaDel));

                    if(eliminado) {
                        guardarLista(listaDel);
                        System.out.println("Estudiante eliminado.");
                    } else {
                        System.out.println("Estudiante no encontrado.");
                    }
                    break;

                case 5:
                    System.out.println("Fin del programa.");
                    break;

                default:
                    System.out.println("Opción inválida.");
            }
        } while(opcion != 5);

        sc.close();
    }

    // Método auxiliar para leer estudiantes desde archivo
    static List<EstudianteIntegrador> leerEstudiantes() throws IOException {
        List<EstudianteIntegrador> lista = new ArrayList<>();
        File archivo = new File(ARCHIVO);
        if(!archivo.exists()) return lista;

        Scanner lector = new Scanner(archivo);
        while(lector.hasNextLine()) {
            String cedula = lector.nextLine().split(":")[1].trim();
            String nombre = lector.nextLine().split(":")[1].trim();
            String carrera = lector.nextLine().split(":")[1].trim();
            lista.add(new EstudianteIntegrador(cedula, nombre, carrera));
            if(lector.hasNextLine()) lector.nextLine(); // separador
        }
        lector.close();
        return lista;
    }

    // Método auxiliar para guardar lista completa en archivo
    static void guardarLista(List<EstudianteIntegrador> lista) throws IOException {
        PrintWriter pw = new PrintWriter(new FileWriter(ARCHIVO));
        for(EstudianteIntegrador e : lista) {
            e.guardar(pw);
        }
        pw.close();
    }
}
