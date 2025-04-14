#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1024

int nivel_indentacion = 0;

void imprimir_indentacion(FILE* salida) {
    for (int i = 0; i < nivel_indentacion; i++) {
        fprintf(salida, "  ");
    }
}

void analizar_linea(const char* linea, FILE* salida) {
    int i = 0;
    int inicio_linea = 1;

    while (linea[i] != '\0') {
        if (isspace(linea[i])) {
            i++;
            continue;
        }

        if ((linea[i] == '}' || linea[i] == ']') && nivel_indentacion > 0) {
            nivel_indentacion--;
        }

        if (inicio_linea) {
            imprimir_indentacion(salida);
            inicio_linea = 0;
        }

        switch (linea[i]) {
            case '{':
                fprintf(salida, "L_LLAVE ");
                nivel_indentacion++;
                i++;
                break;
            case '}':
                fprintf(salida, "R_LLAVE ");
                i++;
                break;
            case '[':
                fprintf(salida, "L_CORCHETE ");
                nivel_indentacion++;
                i++;
                break;
            case ']':
                fprintf(salida, "R_CORCHETE ");
                i++;
                break;
            case ',':
                fprintf(salida, "COMA ");
                i++;
                break;
            case ':':
                fprintf(salida, "DOS_PUNTOS ");
                i++;
                break;
            case '"': {
                i++;
                while (linea[i] != '"' && linea[i] != '\0') i++;
                if (linea[i] == '"') {
                    fprintf(salida, "STRING ");
                    i++;
                } else {
                    fprintf(salida, "\n[ERROR]: cadena sin cierre\n");
                    return;
                }
                break;
            }
            default:
                if (isdigit(linea[i]) || (linea[i] == '-' && isdigit(linea[i+1]))) {
                    while (isdigit(linea[i]) || linea[i] == '.' || linea[i] == 'e' || linea[i] == 'E' || linea[i] == '+' || linea[i] == '-') i++;
                    fprintf(salida, "NUMBER ");
                }
                else if (strncmp(&linea[i], "true", 4) == 0 || strncmp(&linea[i], "TRUE", 4) == 0) {
                    fprintf(salida, "PR_TRUE ");
                    i += 4;
                }
                else if (strncmp(&linea[i], "false", 5) == 0 || strncmp(&linea[i], "FALSE", 5) == 0) {
                    fprintf(salida, "PR_FALSE ");
                    i += 5;
                }
                else if (strncmp(&linea[i], "null", 4) == 0 || strncmp(&linea[i], "NULL", 4) == 0) {
                    fprintf(salida, "PR_NULL ");
                    i += 4;
                }
                else {
                    fprintf(salida, "\n[ERROR]: token no reconocido en \"%s\"\n", &linea[i]);
                    return;
                }
        }
    }

    fprintf(salida, "\n");
}

int main() {
    FILE* entrada = fopen("fuente.txt", "r");
    FILE* salida = fopen("output.txt", "w");

    if (!entrada || !salida) {
        perror("Error abriendo archivo");
        return 1;
    }

    char linea[MAX_LINE];
    while (fgets(linea, sizeof(linea), entrada)) {
        analizar_linea(linea, salida);
    }
    
    fprintf(salida, "EOF\n");

    fclose(entrada);
    fclose(salida);

    printf("Análisis léxico completado. Revisa output.txt\n");
    return 0;
}
