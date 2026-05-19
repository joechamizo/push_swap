*Este proyecto ha sido creado como parte del currículo de 42 tras una colaboración conjunta y equitativa al 50% por joaqumar y acoromin.*

# Push_swap

## 👥 División del Trabajo y Colaboración (50% / 50%)

Para garantizar el cumplimiento normativo y un desarrollo equilibrado del software, el proyecto se dividió en dos grandes bloques de responsabilidad técnica complementaria:

### 👤 Colaboración de joaqumar (50%) — Arquitectura Base y Control de Datos
* **Estructura del Proyecto y Memoria:** Diseño e implementación del struct contenedor `t_program` para encapsular datos sin variables globales, así como los algoritmos de liberación limpia de memoria en `memory.c` para mitigar fugas (*leaks*).
* **Módulo de Parseo y Validación (`parser.c`):** Desarrollo del sistema de entrada de matrices de argumentos, gestión de strings complejos mediante `ft_split` y validación robusta ante desbordamientos numéricos (`INT_MAX`/`INT_MIN`) y duplicados.
* **Mapeo de Control e Índices (`indexing.c`):** Programación del algoritmo de indexación secuencial para pre-procesar los valores numéricos reales en posiciones estables de `0` a `size - 1`.

### 👤 Colaboración de acoromin (50%) — Operaciones Core y Lógica Algorítmica
* **Mutaciones de Memoria y Despacho (`operations.c` y `handlers.c`):** Implementación de las operaciones estructurales básicas (`core_swap`, `core_push`, etc.) y el manejador del despachador con contadores individuales integrados para el modo opcional `--bench`.
* **Enrutador Inteligente (`router.c`):** Diseño de la toma de decisiones dinámicas basadas en el análisis en tiempo real del tamaño de la entrada y el cálculo estadístico del *Índice de Desorden Inicial*.
* **Estrategias de Ordenación (`strategies.c` y `strategies_utils.c`):** Codificación matemática de la red de comparación para 3 elementos, el algoritmo de *Chunks* intermedio ($O(n\sqrt{n})$) y la ordenación binaria por bits *Radix Sort* ($O(n \log n)$).

---

## 📝 Descripción
**Push_swap** es un proyecto de desarrollo de algoritmos en C cuyo objetivo principal es ordenar un conjunto de datos numéricos en un stack (Stack A) utilizando un conjunto limitado de instrucciones, auxiliándose de un stack secundario (Stack B) y minimizando el número total de operaciones ejecutadas.

El proyecto aborda de forma práctica la complejidad temporal y espacial de los algoritmos de ordenación, la manipulación eficiente de estructuras de datos dinámicas (listas enlazadas) y el diseño de software modular bajo restricciones estrictas de optimización y normativas de código (Norma de 42).

---

## 🛠️ Instrucciones

### Requisitos previos
* Compilador `gcc` o `clang`.
* Herramienta de automatización `make`.
* Sistema operativo basado en Unix (macOS o Linux).

### Compilación e Instalación
El proyecto incluye un `Makefile` optimizado con barra de progreso interactiva que evita el *relink*.

1. Para compilar el programa principal `push_swap`:
   ```bash
   make
   ```
2. Para compilar el programa verificador de los bonus `checker`:
   ```bash
   make bonus
   ```
3. Para limpiar los archivos objeto (`.o`):
   ```bash
   make clean
   ```
4. Para realizar una limpieza total (objetos y binarios):
   ```bash
   make fclean
   ```

### Ejecución y Modos de Uso
El binario acepta una lista de enteros (como argumentos independientes o en una sola cadena entrecomillada) y selectores de estrategia opcionales:

* **Modo Adaptativo (Por Defecto):** Evalúa el desorden y el tamaño para elegir la mejor ruta automáticamente.
  ```bash
  ./push_swap 4 67 3 87 23
  ```
* **Estrategia Simple Forced ($O(n^2)$):**
  ```bash
  ./push_swap --simple 3 1 2
  ```
* **Estrategia Intermedia Forced ($O(n\sqrt{n})$):**
  ```bash
  ./push_swap --medium 5 4 3 2 1
  ```
* **Estrategia Compleja Forced ($O(n \log n)$):**
  ```bash
  ./push_swap --complex "4 67 3 87 23"
  ```
* **Modo Benchmark (`--bench`):** Envía a la salida de error estándar (`stderr`) un reporte estadístico detallado tras la ordenación.
  ```bash
  ./push_swap --bench 4 67 3 87 23
  ```

### Pruebas con el Checker (Bonus)
Puedes validar la veracidad de los movimientos conectando ambos binarios mediante una tubería (*pipe*):
```bash
ARG="3 1 2"; ./push_swap $ARG | ./checker $ARG
```

---

## 📐 Decisiones Técnicas y Algorítmicas

El núcleo de este proyecto radica en su arquitectura **Adaptativa**, la cual calcula el **Índice de Desorden Inicial** basándose en el porcentaje de inversiones matemáticas del stack antes de mover ningún nodo.

### Justificación de los Algoritmos Seleccionados

1. **Estrategia Simple — Ordenación por Selección ($O(n^2)$)**
   * **Lógica:** Red de comparación cableada para $N=3$ e inserción directa local localizando el mínimo global para $N \le 5$.
   * **Justificación:** Para conjuntos minúsculos o stacks con un desorden inferior al 15%, los algoritmos complejos rompen la estructura preordenada de forma ineficiente. Este enfoque mitiga el coste constante y garantiza el número mínimo absoluto de pasos exigido por la hoja de evaluación.

2. **Estrategia Intermedia — Algoritmo de Chunks ($O(n\sqrt{n})$)**
   * **Lógica:** Divide el rango de índices ordenados en $\sqrt{n}$ bloques numéricos. Los elementos se envían al Stack B si caen dentro de una ventana de proximidad dinámica, creando una estructura de "reloj de arena". El retorno al Stack A se realiza localizando secuencialmente el máximo por el camino de rotación más corto (`rb`/`rrb`).
   * **Justificación:** Es idóneo para volúmenes medianos (~100 números). Reduce drásticamente el coste de rotación en el Stack A al pre-agrupar los elementos en B, logrando un rendimiento drásticamente inferior a las restricciones de puntuación de 42 de forma consistente.

3. **Estrategia Compleja — Radix Sort Binario ($O(n \log n)$)**
   * **Lógica:** Algoritmo de ordenación no comparativo que procesa la representación binaria de los índices de los nodos bit a bit de derecha a izquierda (LSD). Los elementos con el bit evaluado en `0` se mueven a B (`pb`) y los de bit `1` rotan en A (`ra`).
   * **Justificación:** Para grandes volúmenes de datos (500 números o más), asegura un comportamiento totalmente predecible y acotado. Al depender de una cantidad fija de bits ($k \approx \log_2 n$), el peor caso (*worst-case scenario*) queda matemáticamente blindado frente a distribuciones caóticas de entradas que saturarían otros algoritmos.

---

## 📚 Recursos y Uso de IA

### Referencias Consultadas
* *Introduction to Algorithms* (CLRS) - Documentación teórica sobre análisis asintótico y Radix Sort.
* Tutoriales de la comunidad de 42 sobre el "Turk Algorithm" y mecánicas de "Hourglass/Chunks Sort".

### Declaración de Uso de Inteligencia Artificial
En cumplimiento con las directrices del proyecto, se declara que se ha utilizado un Asistente de IA como herramienta de co-creación y soporte técnico bajo el siguiente desglose:

* **Tareas Automatizadas:** Generación de la estructura del `Makefile` adaptada a terminales estrictas como Fish/Zsh y formateo visual de la barra de progreso con caracteres Unicode.
* **Diseño Arquitectónico:** Soporte en la abstracción del struct contenedor `t_program` para encapsular los estados de los stacks y evitar estrictamente el uso de variables globales proscritas por las reglas del proyecto.
* **Depuración de Errores:** Identificación y resolución de discrepancias de tipos en el compilador Clang (`Wpointer-integer-compare`) al migrar la función pública `parse_flag` hacia los archivos comunes del directorio `srcs/`.
