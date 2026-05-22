import java.io.*;
import java.util.*;

public class LecturaEstudiantes {
    public static void main(String[] args) throws IOException {
        File archivo = new File("estudiantes.txt");

        if(!archivo.exists()) {
            System.out.println(" El archivo 'estudiantes.txt' no existe. Ejecute primero el registro.");
            return;
        }

        Scanner lector = new Scanner(archivo);
        int contador = 0;
        double sumaPromedios = 0;

        System.out.println("\n=== LISTA DE ESTUDIANTES ===");

        // Leer línea por línea y mostrar directamente
        while(lector.hasNextLine()) {
            String linea = lector.nextLine();
            System.out.println(linea);

            // Si la línea contiene el promedio, lo sumamos
            if(linea.startsWith("Promedio")) {
                double prom = Double.parseDouble(linea.split(":")[1].trim());
                sumaPromedios += prom;
                contador++;
            }
        }
        lector.close();

        // Mostrar estadísticas
        System.out.println("Total estudiantes: " + contador);
        if(contador > 0) {
            System.out.println("Promedio general: " + (sumaPromedios / contador));
        }
    }
}
