double Determinante(Matriz matriz) {
    /* Calcula el determinante de una matriz cuadrada usando eliminación gaussiana */
    
    if (matriz.filas != matriz.columnas) {
        printf("ERROR: La matriz debe ser cuadrada para calcular el determinante.\n");
        return 0;
    }
    
    int n = matriz.filas;
    double det = 1.0;
    
    // Crear una copia de la matriz para no modificar la original
    Matriz temp;
    temp.filas = n;
    temp.columnas = n;
    temp.entrada = (double *)malloc(sizeof(double) * n * n);
    
    // Copiar los valores de la matriz original
    for (int i = 0; i < n * n; i++) {
        temp.entrada[i] = matriz.entrada[i];
    }
    
    // Aplicar eliminación gaussiana
    for (int i = 0; i < n; i++) {
        // Buscar el pivote máximo en la columna actual
        int max_row = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(temp.entrada[k * n + i]) > fabs(temp.entrada[max_row * n + i])) {
                max_row = k;
            }
        }
        
        // Si el pivote es cero, el determinante es cero
        if (fabs(temp.entrada[max_row * n + i]) < 1e-12) {
            free(temp.entrada);
            return 0;
        }
        
        // Intercambiar filas si es necesario
        if (max_row != i) {
            for (int k = 0; k < n; k++) {
                double temp_val = temp.entrada[i * n + k];
                temp.entrada[i * n + k] = temp.entrada[max_row * n + k];
                temp.entrada[max_row * n + k] = temp_val;
            }
            det *= -1; // El determinante cambia de signo al intercambiar filas
        }
        
        // Hacer ceros debajo del pivote
        for (int k = i + 1; k < n; k++) {
            double factor = temp.entrada[k * n + i] / temp.entrada[i * n + i];
            for (int j = i; j < n; j++) {
                temp.entrada[k * n + j] -= factor * temp.entrada[i * n + j];
            }
        }
        
        // Multiplicar el determinante por el pivote
        det *= temp.entrada[i * n + i];
    }
    
    free(temp.entrada);
    return det;
}
