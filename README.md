<!--* Este proyecto ha sido creado como parte del currículo de 42 tras una colaboración conjunta y equitativa al 50% por joaqumar y acoromin. *-->

# Push_swap

<p align="center">
  <img src="https://shields.io" alt="Score 100/100">
  <img src="https://shields.io" alt="Norminette">
  <img src="https://shields.io" alt="Leaks None">
</p>

## 👥 División del Trabajo y Colaboración (50% / 50%)

Para garantizar el cumplimiento normativo de la Escuela 42 y un desarrollo equilibrado del software, el proyecto se estructuró en dos grandes bloques de responsabilidad técnica complementaria:

### 👤 Colaboración de acoromin (50%) — Arquitectura Base y Control de Datos
* **Estructura del Proyecto y Memoria:** Diseño e implementación del struct contenedor central `t_program` para encapsular datos de control de flujo sin recurrir a variables globales. Programación de los algoritmos de liberación de memoria en `memory.c` para mitigar fugas (*leaks*) bajo cualquier escenario de salida o error.
* **Módulo de Parseo y Validación (`parser.c`):** Desarrollo del sistema de deserialización de matrices de argumentos. Gestión de strings complejos mediante `ft_split` y validación robusta ante desbordamientos numéricos extremos (`INT_MAX` / `INT_MIN`), strings vacíos y valores duplicados.
* **Mapeo de Control e Índices (`indexing.c`):** Programación del algoritmo de indexación secuencial para pre-procesar los valores enteros reales de entrada a posiciones estables normalizadas de `0` a `size - 1`.

### 👤 Colaboración de joaqumar (50%) — Operaciones Core y Lógica Algorítmica
* **Mutaciones de Memoria y Despacho (`operations.c` y `handlers.c`):** Implementación de las operaciones estructurales primitivas (`core_swap`, `core_push`, `core_rotate`, `core_reverse_rotate`) y el despachador con contadores individuales integrados para el modo opcional estadístico `--bench`.
* **Enrutador Inteligente (`router.c`):** Diseño de la toma de decisiones dinámicas basadas en el análisis en tiempo real de la longitud de la entrada y el cálculo estadístico del *Índice de Desorden Inicial*.
* **Estrategias de Ordenación (`strategies_chunks.c` y `strategies_utils.c`):** Codificación matemática de la red de comparación cableada para 3 elementos, lógica para conjuntos menores o iguales a 5 elementos, y el algoritmo de ordenación avanzado de **Chunks Dinámicos Adaptativos**.

---

## 📝 Descripción
**Push_swap** es un proyecto de desarrollo de algoritmos de optimización en C cuyo objetivo es ordenar un conjunto de datos numéricos enteros aleatorios en un stack principal (Stack A) utilizando el menor número de instrucciones posible, auxiliándose de un stack secundario (Stack B).

El proyecto aborda de forma práctica la manipulación eficiente de estructuras de datos lineales (listas enlazadas circulares dobles o arrays dinámicos), el análisis de la complejidad temporal y espacial $O(n \sqrt{n})$, y el diseño de software modular bajo restricciones estrictas de rendimiento (Norma de la Escuela 42).

---

## 📐 Decisiones Técnicas y Algorítmicas

El núcleo de este software radica en su arquitectura **Adaptativa**. Antes de realizar cualquier mutación en los stacks, el programa analiza la lista de entrada y calcula su nivel de entropía matemática mediante el porcentaje de inversiones.

### Justificación de los Algoritmos Seleccionados

1. **Estrategia Simple — Red de Comparación e Inserción ($O(n^2)$)**
   * **Lógica:** Lógica directa (*hardcoded*) mediante evaluación combinatoria para $N=3$ (máximo 3 movimientos) e inserción directa localizando los valores mínimos globales para $N \le 5$ (máximo 12 movimientos).
   * **Justificación:** Para conjuntos pequeños o con un índice de desorden menor al 15%, los algoritmos masivos rompen la estructura preordenada de forma ineficiente. Este enfoque mitiga el coste constante y garantiza la máxima puntuación en los tramos cortos de la hoja de evaluación.

2. **Estrategia Avanzada — Algoritmo de Chunks Dinámicos Adaptativos ($O(n\sqrt{n})$)**
   * **Lógica:** Divide el rango de índices ordenados en bloques de tamaño variable calculados en tiempo real según los elementos restantes de la pila. El programa escanea el Stack A y envía elementos al Stack B si caen dentro de una ventana de proximidad móvil ("reloj de hourglass"). Los elementos con índices menores al promedio sufren un `rb` inmediato para pre-ordenar B en dos sub-bloques compactos.
   * **Justificación:** Sustituye ventajosamente a Radix Sort en base 2. Mientras que Radix es rígido y requiere un número fijo de pasadas bit a bit que eleva los movimientos para 500 números a ~6700, la ventana dinámica adaptativa de Chunks aprovecha la proximidad reduciendo el tamaño del bloque a medida que A se vacía (desde 45 elementos hasta 10). La devolución se realiza de forma óptima calculando de forma bidireccional el camino más corto hacia el tope mediante `rb` o `rrb`.

### Rendimiento Estadístico Obtenido (Tests de 500 números)
* **Límite máximo permitido por 42:** 11,500 movimientos.
* **Límite exigido para 5 estrellas (Máxima puntuación):** Menos de 5,500 movimientos.
* **Métricas de nuestra implementación:**
  * **Movimientos Mínimos:** 4,974
  * **Movimientos Máximos:** 5,457 (Ningún test supera la barrera crítica)
  * **Promedio Global:** 5,167
  * **Puntuación del Tester:** **201/201 Tests Exitosos (5/5 Estrellas) 🥳✅**

---

## 🛠️ Instrucciones de Uso

### Requisitos previos
* Compilador `clang` o `gcc` con soporte para flags `-Wall -Wextra -Werror`.
* Herramienta de automatización `make`.
* Sistema operativo basado en Unix (Linux o macOS).

### Compilación e Instalación
El sistema de construcción incluye un `Makefile` optimizado que evita el *relink* y muestra de forma interactiva la compilación modular de los fuentes.

1. Compilar el programa principal `push_swap`:
   ```bash
   make
   ```
2. Compilar el programa verificador de operaciones (Bonus) `checker`:
   ```bash
   make bonus
   ```
3. Limpiar los archivos objeto generados (`.o`):
   ```bash
   make clean
   ```
4. Realizar una limpieza total (objetos, librerías y binarios):
   ```bash
   make fclean
   ```

### Modos de Ejecución
El ejecutable acepta secuencias de números enteros tanto como argumentos independientes como estructurados en una única cadena entrecomillada. 

> 💡 **Flexibilidad del Parser:** Los selectores opcionales de estrategia y depuración se procesan e interpretan de manera **completamente independiente de la posición** en la que se introduzcan dentro de la línea de comandos (pueden enviarse al inicio, intercalados entre los números enteros o al final de la secuencia de argumentos).

* **Modo Adaptativo (Por Defecto):** Analiza la longitud y la entropía de los argumentos y aplica la mejor estrategia algorítmica de forma automática.
  ```bash
  ./push_swap 4 67 3 87 23
  ```
* **Forzar Estrategia Simple:** Puedes intercalar el selector sin romper el flujo:
  ```bash
  ./push_swap 3 1 --simple 2
  ```
* **Forzar Estrategia de Chunks Dinámicos:**
  ```bash
  ./push_swap --medium 5 4 3 2 1
  ```
* **Modo Estadístico / Benchmark (`--bench`):** Desvía un informe pormenorizado con el recuento exacto de cada una de las operaciones ejecutadas directamente a la salida de errores (`stderr`), colocado al final:
  ```bash
  ./push_swap "4 67 3 87 23" --bench
  ```

### Validación Automática con Checker
Puedes verificar mediante una tubería (*pipe*) que la secuencia de operaciones generada ordena perfectamente el Stack sin estados corruptos:
```bash
ARG="3 1 2 5 4"; ./push_swap $ARG | ./checker $ARG
```

---

## 📚 Recursos y Uso de IA

### Referencias Consultadas
* *Introduction to Algorithms* (CLRS): Fundamentos teóricos sobre la optimización de algoritmos de ordenación no comparativos y análisis asintótico de ventanas de proximidad.
* Documentación y guías de la comunidad de la Escuela 42 relativas a las mecánicas de *Hourglass/Chunks Sort* aplicadas a pilas.

### Declaración de Uso de Inteligencia Artificial
En cumplimiento con las normativas éticas de desarrollo de la Escuela 42, se declara que se ha utilizado un Asistente de IA como herramienta de co-creación y soporte técnico bajo las siguientes pautas:

* **Estructura y Formato:** Soporte en el formateo de cadenas visuales Unicode complejas del `Makefile` para evitar la corrupción de terminales modernas y la generación estructurada de este documento técnico en Markdown.
* **Diseño Arquitectónico:** Asistencia conceptual en la encapsulación del entorno de ejecución mediante el struct `t_program`, asegurando que no se utilicen variables globales proscritas.
* **Optimización Algorítmica y Depuración:** Colaboración en el cálculo matemático analítico para la transición de un Radix Sort rígido en base 2 hacia un modelo dinámico adaptativo de *Chunks*, fragmentando la lógica en funciones independientes con el fin de cumplir estrictamente la restricción de las 25 líneas impuestas por la Norma de 42.
