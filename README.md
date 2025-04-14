# Analizador Léxico para JSON Simplificado
## Autores:
1. Ian Delvalle 5550211
2. Matias Gaona 4553979
   
Este proyecto implementa un **analizador léxico** para el lenguaje **JSON simplificado** en C. El programa toma un archivo fuente en formato JSON, analiza los tokens y genera un archivo de salida con la secuencia de componentes léxicos encontrados. En caso de error léxico, se imprime un mensaje de error y se continúa con la siguiente línea del archivo.

## Características

- Reconoce los siguientes tokens:
  - Llaves (`{`, `}`)
  - Corchetes (`[`, `]`)
  - Coma (`,`)
  - Dos puntos (`:`)
  - Literales de cadena (`"string"`)
  - Números, incluyendo notación científica
  - Literales booleanos (`true`, `false`)
  - `null`
- Imprime la secuencia de tokens por línea del archivo fuente en el archivo de salida.
- Agrega una línea con `EOF` al final del archivo de salida para indicar el fin del archivo.

## Instalación

### Requisitos previos

- Un compilador C compatible con `gcc`.
- Sistema operativo Linux, Windows o MacOS (cualquier sistema que tenga un compilador C disponible).

### Instrucciones de uso

1. Clona el repositorio en tu máquina local:

   ```bash
   git clone https://github.com/ianmrc24/analizador-json.git
   ```

2. Navega al directorio del proyecto:

   ```bash
   cd analizador-json
   ```

3. Compila el código con `gcc`:

   ```bash
   gcc -o lexer lexer.c
   ```

4. Coloca tu archivo JSON de entrada (`fuente.txt`) en el mismo directorio que el programa.

5. Ejecuta el programa:

   ```bash
   ./lexer
   ```

6. Revisa el archivo de salida (`output.txt`) generado.

   El archivo de salida tendrá la secuencia de tokens por cada línea del archivo JSON, y al final se agregará la línea `EOF` para indicar el fin del archivo.

## Ejemplo

### Archivo de entrada (`fuente.txt`):

```json
{
  "personas": [
    {
      "ci": 1234567,
      "nombre": "Julio Pérez",
      "casado": false,
      "hijos": []
    },
    {
      "ci": 7654321,
      "nombre": "Juan Gómez",
      "casado": true,
      "hijos": [
        {
          "nombre": "Jorge",
          "edad": 18
        },
        {
          "nombre": "Valeria",
          "edad": 16
        }
      ]
    }
  ]
}
```

### Archivo de salida (`output.txt`):

```text
L_LLAVE 
  STRING DOS_PUNTOS L_CORCHETE 
    L_LLAVE 
      STRING DOS_PUNTOS NUMBER COMA 
      STRING DOS_PUNTOS STRING COMA 
      STRING DOS_PUNTOS PR_FALSE COMA 
      STRING DOS_PUNTOS L_CORCHETE 
      R_CORCHETE 
    R_LLAVE COMA 
    L_LLAVE 
      STRING DOS_PUNTOS NUMBER COMA 
      STRING DOS_PUNTOS STRING COMA 
      STRING DOS_PUNTOS PR_TRUE COMA 
      STRING DOS_PUNTOS L_CORCHETE 
        L_LLAVE 
          STRING DOS_PUNTOS STRING COMA
          STRING DOS_PUNTOS NUMBER
        R_LLAVE COMA
        L_LLAVE 
          STRING DOS_PUNTOS STRING COMA 
          STRING DOS_PUNTOS NUMBER 
        R_LLAVE
      R_CORCHETE
    R_LLAVE
  R_CORCHETE
R_LLAVE
EOF
```

