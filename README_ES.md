*Este proyecto fue creado como parte del plan de estudios de 42 a través de una colaboración equitativa al 50% por joaqumar y acoromin.*

# Push_swap

## 👥 Distribución del Trabajo y Colaboración (50% / 50%)

Para mantener el proyecto comprensible, mantenible y alineado con el proceso de evaluación de 42, el trabajo se dividió en dos áreas técnicas complementarias.

### 👤 acoromin (50%) — Estructura del Proyecto, Parseo y Control de Datos

- **Estructura del proyecto y gestión de memoria:** Diseño e implementación de la estructura central `t_program`, utilizada para agrupar el estado de ejecución sin depender de variables globales. Implementación de utilidades de limpieza de memoria para garantizar que ambas pilas se liberen correctamente tanto en salidas normales como en rutas de error.
- **Parseo y validación:** Desarrollo del flujo de parseo de argumentos, incluyendo soporte para argumentos independientes, cadenas entrecomilladas que contienen varios números y flags opcionales. La validación cubre argumentos vacíos, caracteres inválidos, desbordamiento de enteros (overflow/underflow) y valores duplicados.
- **Sistema de indexación:** Implementación del paso de preprocesamiento que mapea cada valor de entrada a un índice estable de `0` a `size - 1`, lo que permite que los algoritmos de ordenación trabajen con valores normalizados en lugar de enteros brutos.

### 👤 joaqumar (50%) — Operaciones de Stack y Lógica de Ordenación

- **Operaciones principales de stack:** Implementación de las operaciones primitivas de Push_swap (`swap`, `push`, `rotate` y `reverse rotate`) y sus envolturas (wrappers), incluyendo el conteo de operaciones para el modo benchmark opcional.
- **Enrutamiento de estrategias:** Diseño de la lógica de selección de estrategia basada en el flag seleccionado por línea de comandos, el tamaño de la entrada y el índice de desorden inicial.
- **Estrategias de ordenación:** Implementación de la estrategia simple para entradas pequeñas, la estrategia basada en bloques (chunks) para entradas de tamaño mediano y la estrategia basada en radix para entradas más grandes o altamente desordenadas.

---

## 📝 Descripción

**Push_swap** es un proyecto algorítmico escrito en C. El objetivo es ordenar una lista de enteros almacenados en la pila `a`, utilizando una segunda pila `b` y un conjunto restringido de operaciones, produciendo la menor cantidad de operaciones posible.

El proyecto se centra en:

- Manipulación de pilas mediante listas enlazadas;
- Movimiento de nodos entre pilas seguro para punteros;
- Parseo de entrada y manejo de errores;
- Propiedad de la memoria y limpieza;
- Complejidad algorítmica bajo el modelo de operaciones de Push_swap;
- Código C modular siguiendo la Norma de 42.

El programa imprime la secuencia de operaciones necesarias para ordenar la pila `a` en orden ascendente, de modo que el valor más pequeño quede en la parte superior de la pila.

---

## 📐 Decisiones Técnicas y Algorítmicas

El proyecto está construido alrededor de una arquitectura modular. Primero se parsea la entrada, luego se normaliza cada valor mediante un índice y, finalmente, se selecciona y ejecuta una estrategia de ordenación.

### Indexación

Los valores de entrada no se ordenan directamente por su valor entero bruto. En su lugar, cada nodo recibe un `index` que representa su posición en el orden ordenado.

Ejemplo:

```text
valor:  100 -> 23 -> 1 -> 74 -> 923
índice:   3 ->  1 -> 0 ->  2 ->   4
```
Esto facilita la lógica de ordenación porque los algoritmos pueden trabajar con un rango compacto de `0` a `size - 1`, independientemente de si los valores originales son negativos, muy grandes o están muy separados.

Los índices se asignan una sola vez después del parseo y antes de la ordenación. No se actualizan durante las operaciones, porque el índice pertenece al valor en sí, no a la posición actual del nodo en la pila.
### Índice de Desorden Inicial

Antes de ordenar, el programa calcula un índice de desorden basado en las inversiones de la entrada. Una inversión ocurre cuando un valor mayor aparece antes que uno menor.

Esto proporciona una estimación de qué tan lejos está la entrada de estar ordenada y ayuda a la estrategia adaptativa a decidir qué enfoque interno es más apropiado.

### Estrategias de Ordenación

#### 1. Estrategia Simple — Entradas Pequeñas / O(n²)

La estrategia simple se utiliza para entradas pequeñas. Maneja pilas muy pequeñas con lógica directa y utiliza la extracción mínima para conjuntos pequeños.

Esto evita la sobrecarga de algoritmos más grandes cuando el número de elementos es bajo.

#### 2. Estrategia Mediana — Chunks / O(n√n)

La estrategia basada en bloques (chunks) divide el rango indexado en grupos. Los elementos se pasan de la pila `a` a la pila `b` de acuerdo con ventanas de índice móviles, y la pila `b` se organiza parcialmente durante el proceso.

Cuando todos los valores relevantes están en `b`, el algoritmo lleva repetidamente el índice más alto de vuelta a la parte superior de `b` utilizando la dirección de rotación más corta, y luego lo empuja de vuelta a `a`.

Esta estrategia ofrece buenos resultados para entradas medianas y grandes manteniendo la lógica comprensible.

#### 3. Estrategia Compleja — Radix / O(n log n)

La estrategia radix trabaja sobre la representación binaria de los índices normalizados. Procesa cada bit y mueve los elementos entre las pilas dependiendo de si ese bit está activo.

El uso de índices hace que radix sea práctico porque todos los valores se encuentran en el rango de `0` a `size - 1`.

#### 4. Estrategia Adaptativa

La estrategia adaptativa es el comportamiento por defecto. Elige la estrategia interna de acuerdo con el tamaño de la entrada y el índice de desorden.

El objetivo es evitar el uso de una estrategia pesada para entradas pequeñas o casi ordenadas, al tiempo que se utilizan métodos escalables para pilas más grandes y desordenadas.

---

## 📊 Objetivos de Rendimiento

De acuerdo con los requerimientos del proyecto, el programa debe mantenerse dentro de los límites de operaciones esperados:

### 100 números aleatorios

- Requisito mínimo: menos de 2000 operaciones
- Buen rendimiento: menos de 1500 operaciones
- Rendimiento excelente: menos de 700 operaciones

### 500 números aleatorios

- Requisito mínimo: menos de 12000 operaciones
- Buen rendimiento: menos de 8000 operaciones
- Rendimiento excelente: menos de 5500 operaciones

La implementación fue probada con entradas aleatorias y verificada con el checker del proyecto para asegurar que las operaciones generadas ordenan correctamente la pila.

---

## 🛠️ Uso

### Requisitos

- `cc`, `clang` o `gcc`
- `make`
- Sistema basado en Unix como Linux o macOS

### Compilación

Compilar el programa obligatorio:

```bash
make
```

Compilar el checker de bonus:

```bash
make bonus
```

Eliminar archivos objeto:

```bash
make clean
```

Eliminar archivos objeto y binarios:

```bash
make fclean
```

Recompilar todo:

```bash
make re
```

### Ejecución de Push_swap

El programa acepta enteros como argumentos independientes:

```bash
./push_swap 4 67 3 87 23
```

También acepta cadenas entrecomilladas que contienen varios números:

```bash
./push_swap "4 67 3 87 23"
```

Se admite la entrada mixta:

```bash
./push_swap "100 23 1" 74 923
```

Los flags opcionales de estrategia se pueden colocar antes, entre o después de los números:

```bash
./push_swap --simple 3 2 1
./push_swap 3 2 --medium 1
./push_swap "5 4" --complex 3 2 1
./push_swap 32 3 4 --bench 1 55
```

Si no se proporciona ningún flag de estrategia, el programa utiliza la estrategia adaptativa por defecto.

### Flags Disponibles

- `--simple`: fuerza la estrategia simple.
- `--medium`: fuerza la estrategia basada en chunks.
- `--complex`: fuerza la estrategia radix.
- `--adaptive`: fuerza la estrategia adaptativa.
- `--bench`: habilita la salida de benchmark.

Solo se debe utilizar un flag de estrategia a la vez. El flag `--bench` se puede combinar con un flag de estrategia.

### Modo Benchmark

El modo benchmark imprime información adicional en `stderr`, no en `stdout`.

Esto es importante porque `stdout` debe contener únicamente las operaciones de Push_swap, de modo que se puedan redirigir de forma segura al checker a través de un pipe.

Ejemplo:

```bash
./push_swap --bench 3 2 1 | ./checker 3 2 1
```

El checker recibe solo las operaciones a través del pipe. El informe del benchmark permanece separado en `stderr`.

---

## ✅ Validación con el Checker

Las operaciones generadas se pueden verificar con el checker:

```bash
ARG="3 1 2 5 4"; ./push_swap $ARG | ./checker $ARG
```

Salida esperada:

```text
OK
```

Un ejemplo de entrada mixta:

```bash
./push_swap "100 23 1 74 923" 89 33 12 | ./checker "100 23 1 74 923" 89 33 12
```

Salida esperada:

```text
OK
```

La salida del benchmark se puede redirigir por separado:

```bash
./push_swap --bench 3 2 1 > ops 2> bench.txt
./checker 3 2 1 < ops
```

---

## ❌ Manejo de Errores

El programa imprime `Error` seguido de un salto de línea en `stderr` cuando la entrada no es válida.

Ejemplos de entrada inválida:

```bash
./push_swap 1 2 2
./push_swap ""
./push_swap "   "
./push_swap 2147483648
./push_swap -2147483649
./push_swap 3 2 hello 1
./push_swap --simple --complex 3 2 1
```

El checker también imprime `Error` ante argumentos inválidos o instrucciones inválidas.

---

## 📚 Recursos y Uso de IA

### Referencias

- Enunciado de Push_swap de 42
- Norma de 42
- Explicaciones de la comunidad de 42 sobre la ordenación basada en chunks
- Referencias generales sobre algoritmos de ordenación y complejidad algorítmica

### Declaración de Uso de IA

La asistencia de IA se utilizó como herramienta de apoyo durante el flujo de trabajo del proyecto, principalmente para:

- revisar la estructura del proyecto;
- identificar casos límite (edge cases) en el parseo;
- mejorar la redacción y organización del README;
- razonar sobre los casos de prueba;
- comprobar si la implementación coincidía con el comportamiento esperado del enunciado.

Todas las sugerencias generadas fueron revisadas, adaptadas, probadas y validadas manualmente con:

- `norminette`;
- `make` y `make bonus`;
- `valgrind`;
- el checker del proyecto;
- pruebas con entradas aleatorias.

La responsabilidad final del código, las pruebas y la defensa del proyecto sigue siendo de los autores.

