# Descripción del funcionamiento de los programas de codificación y decodificación Huffman

## Bibliotecas utilizadas

Los programas utilizan las bibliotecas estándar `<stdio.h>`, `<stdlib.h>` y `<string.h>`. La biblioteca `<stdio.h>` proporciona las funciones necesarias para la entrada y salida de datos, incluyendo la lectura y escritura de archivos mediante funciones como `fopen()`, `fread()`, `fwrite()`, `fgetc()` y `fclose()`. La biblioteca `<stdlib.h>` se utiliza para la reserva dinámica de memoria mediante `malloc()` y para la finalización controlada del programa mediante `exit()`. Finalmente, `<string.h>` proporciona funciones para la manipulación de cadenas de caracteres, particularmente `strcpy()`, utilizada durante la construcción del diccionario de códigos Huffman.

## Estructuras de datos

### Estructura "Nodo"

La estructura `"Nodo"` representa cada elemento que forma parte del árbol de Huffman. Está compuesta por la variable `"caracter"`, encargada de almacenar el símbolo correspondiente, la variable `"frecuencia"`, que registra el número de apariciones del símbolo dentro del archivo analizado, y los punteros `"izq"` y `"der"`, utilizados para enlazar los nodos hijos izquierdo y derecho respectivamente.

La utilización de esta estructura permite construir un árbol binario donde los caracteres más frecuentes se encuentran más cerca de la raíz, reduciendo la longitud de sus códigos binarios y mejorando así la eficiencia de compresión.

### Estructura "MinHeap"

La estructura `"MinHeap"` implementa una cola de prioridad basada en un montículo mínimo. Está formada por la variable `"tamano"`, que indica la cantidad actual de elementos almacenados, la variable `"capacidad"`, que representa la capacidad máxima del montículo, y el arreglo de punteros `"arreglo"`, donde se almacenan las referencias a los nodos ordenados por frecuencia.

Esta estructura resulta fundamental para la construcción eficiente del árbol de Huffman, ya que permite localizar y extraer rápidamente los nodos con menor frecuencia.

## Funciones compartidas por ambos programas

### Función "nuevoNodo()"

La función `"nuevoNodo()"` recibe como parámetros un carácter y una frecuencia. Su propósito es reservar dinámicamente memoria para una nueva estructura `"Nodo"` utilizando la función `malloc()`. Después de verificar que la memoria fue asignada correctamente, inicializa los campos correspondientes y establece los punteros `"izq"` y `"der"` en `NULL`.

Esta función centraliza la creación de nodos y evita la repetición de código durante la construcción del árbol.

### Función "intercambiarNodos()"

La función `"intercambiarNodos()"` recibe dos punteros a nodos y realiza el intercambio de sus direcciones de memoria mediante una variable auxiliar.

Su finalidad es mantener el orden requerido dentro del montículo mínimo durante las operaciones de reorganización del heap.

### Función "minHeapify()"

La función `"minHeapify()"` recibe como parámetros un puntero a la estructura `"MinHeap"` y el índice de un nodo dentro del arreglo. Su objetivo es restaurar la propiedad de montículo mínimo verificando si alguno de sus hijos posee una frecuencia menor.

Para ello calcula las posiciones de los hijos izquierdo y derecho mediante las expresiones `2 * idx + 1` y `2 * idx + 2`. Si encuentra un nodo con menor frecuencia, realiza el intercambio correspondiente y vuelve a ejecutar el procedimiento de forma recursiva.

Esta función garantiza que el nodo con la frecuencia más pequeña permanezca siempre en la raíz del montículo.

### Función "extraerMinimo()"

La función `"extraerMinimo()"` obtiene el nodo con la frecuencia más baja almacenado en el montículo.

El procedimiento consiste en guardar el elemento ubicado en la raíz, sustituirlo por el último elemento del arreglo, reducir el tamaño del montículo y ejecutar nuevamente `"minHeapify()"` para restaurar el orden interno.

Esta operación es esencial para la construcción del árbol de Huffman, ya que en cada iteración se requieren los dos nodos menos frecuentes.

### Función "insertarMinHeap()"

La función `"insertarMinHeap()"` agrega un nuevo nodo dentro del montículo mínimo.

Inicialmente el nodo se coloca al final del arreglo. Posteriormente se realizan comparaciones con su nodo padre mediante la expresión `(i - 1) / 2`, desplazándolo hacia arriba mientras su frecuencia sea menor.

Este procedimiento permite conservar la propiedad de ordenamiento característica del montículo mínimo.

### Función "crearYConstruirMinHeap()"

La función `"crearYConstruirMinHeap()"` recibe los arreglos de caracteres y frecuencias junto con el tamaño del alfabeto detectado.

Inicialmente reserva memoria para la estructura `"MinHeap"` y para su arreglo interno. Posteriormente crea un nodo para cada carácter utilizando la función `"nuevoNodo()"`.

Una vez cargados todos los elementos, ejecuta `"minHeapify()"` desde los niveles inferiores hacia la raíz para transformar el arreglo en un montículo mínimo válido.

### Función "construirArbolHuffman()"

La función `"construirArbolHuffman()"` implementa la etapa principal del algoritmo de Huffman.

Primero construye un montículo mínimo utilizando las frecuencias de aparición de cada carácter. Después, mientras existan más de un nodo dentro del montículo, extrae los dos nodos con menor frecuencia mediante `"extraerMinimo()"`.

Posteriormente crea un nuevo nodo interno cuya frecuencia corresponde a la suma de ambos nodos extraídos. Dicho nodo se inserta nuevamente en el montículo utilizando `"insertarMinHeap()"`.

El proceso continúa hasta que solamente queda un nodo dentro del montículo, el cual se convierte en la raíz del árbol de Huffman. Este árbol será utilizado posteriormente tanto para codificar como para decodificar información.

## Funciones exclusivas del programa de codificación

### Función "procesarArchivoTexto()"

La función `"procesarArchivoTexto()"` se encarga de analizar el contenido completo del archivo de entrada.

Mediante la función `fgetc()` realiza la lectura carácter por carácter, contabilizando la frecuencia de aparición de cada símbolo dentro del arreglo `"frecuenciasGlobales"`.

Una vez finalizada la lectura, recorre el arreglo de frecuencias y almacena únicamente los caracteres que realmente aparecen en el archivo dentro de los arreglos `"caracteresActivos"` y `"frecuenciasActivas"`.

El valor retornado corresponde al tamaño efectivo del alfabeto encontrado.

### Variable global "diccionario"

La variable global `"diccionario"` consiste en una matriz bidimensional de caracteres donde cada posición representa el código binario asociado a un símbolo específico.

Su propósito es almacenar las secuencias de ceros y unos generadas a partir del árbol de Huffman para facilitar el proceso de compresión.

### Función "generarDiccionario()"

La función `"generarDiccionario()"` recorre el árbol de Huffman mediante una estrategia recursiva.

Cada vez que avanza hacia el hijo izquierdo agrega el carácter `'0'` al código temporal y cuando avanza hacia el hijo derecho agrega el carácter `'1'`.

Cuando alcanza un nodo hoja, copia el código generado al arreglo `"diccionario"` utilizando la función `strcpy()`.

Gracias a este procedimiento cada símbolo queda asociado a una secuencia binaria única.

### Función "comprimirYGuardar()"

La función `"comprimirYGuardar()"` realiza la compresión efectiva del archivo.

Inicialmente escribe en el archivo binario la información necesaria para reconstruir posteriormente el árbol de Huffman, incluyendo el número total de caracteres originales, el tamaño del alfabeto y las frecuencias de cada símbolo.

Posteriormente vuelve a leer el archivo original y sustituye cada carácter por su correspondiente código binario almacenado en `"diccionario"`.

Los bits generados son acumulados dentro de la variable `"buffer"` hasta completar un byte. Cuando el buffer alcanza ocho bits, se almacena en el archivo de salida mediante `fwrite()`.

Este mecanismo permite reducir significativamente el espacio requerido para almacenar la información.

### Función "main()" del codificador

La función principal verifica inicialmente que el usuario proporcione los nombres del archivo de entrada y del archivo comprimido.

Posteriormente ejecuta las etapas principales del algoritmo: análisis de frecuencias, construcción del árbol de Huffman, generación del diccionario y compresión del contenido.

Finalmente muestra un mensaje indicando que el proceso de codificación fue realizado correctamente.

## Funciones exclusivas del programa de decodificación

### Función "main()" del decodificador

La función principal del programa de decodificación recibe como argumento el archivo binario generado por el codificador.

Inicialmente recupera la información almacenada durante la compresión, incluyendo el número total de caracteres originales, el tamaño del alfabeto y las frecuencias de cada símbolo.

Con estos datos reconstruye exactamente el mismo árbol de Huffman mediante la función `"construirArbolHuffman()"`.

Posteriormente comienza a leer cada byte almacenado en el archivo comprimido. Mediante operaciones de desplazamiento de bits utilizando la expresión `(byte >> i) & 1`, extrae individualmente cada bit.

Si el bit leído es cero, avanza hacia el hijo izquierdo del árbol; si es uno, avanza hacia el hijo derecho. Cuando alcanza un nodo hoja, imprime el carácter correspondiente utilizando `putchar()` y reinicia el recorrido desde la raíz.

El proceso continúa hasta reconstruir la totalidad de los caracteres originales almacenados antes de la compresión.

## Conclusión

Los programas desarrollados implementan de manera completa el algoritmo de compresión Huffman mediante el uso de árboles binarios y montículos mínimos. El programa de codificación analiza las frecuencias de aparición de los caracteres, construye el árbol correspondiente y genera una representación binaria más eficiente de la información. Por su parte, el programa de decodificación reconstruye el mismo árbol a partir de los datos almacenados y recupera el contenido original recorriendo la estructura según los bits leídos. La combinación de ambos programas permite realizar procesos de compresión y recuperación de información de forma eficiente, manteniendo la integridad de los datos originales.