*This project was created as part of the 42 curriculum through an equal 50% collaboration by joaqumar and acoromin.*

# Push_swap

## 👥 Work Distribution and Collaboration (50% / 50%)

To keep the project understandable, maintainable, and aligned with the 42 evaluation process, the work was divided into two complementary technical areas.

### 👤 acoromin (50%) — Project Structure, Parsing, and Data Control

- **Project structure and memory management:** Design and implementation of the central `t_program` structure, used to group the execution state without relying on global variables. Implementation of memory cleanup utilities to ensure that both stacks are freed correctly on normal exits and error paths.
- **Parsing and validation:** Development of the argument parsing flow, including support for independent arguments, quoted strings containing several numbers, and optional flags. Validation covers empty arguments, invalid characters, integer overflow/underflow, and duplicated values.
- **Indexing system:** Implementation of the preprocessing step that maps each input value to a stable index from `0` to `size - 1`, allowing the sorting algorithms to work with normalized values instead of raw integers.

### 👤 joaqumar (50%) — Stack Operations and Sorting Logic

- **Core stack operations:** Implementation of the primitive Push_swap operations (`swap`, `push`, `rotate`, and `reverse rotate`) and their wrappers, including operation counting for the optional benchmark mode.
- **Strategy routing:** Design of the strategy selection logic based on the selected command-line flag, the input size, and the initial disorder index.
- **Sorting strategies:** Implementation of the simple strategy for small inputs, the chunk-based strategy for medium-sized inputs, and the radix-based strategy for larger or highly disordered inputs.

---

## 📝 Description

**Push_swap** is an algorithmic project written in C. The goal is to sort a list of integers stored in stack `a`, using a second stack `b` and a restricted set of operations, while producing as few operations as possible.

The project focuses on:

- linked-list stack manipulation;
- pointer-safe node movement between stacks;
- input parsing and error handling;
- memory ownership and cleanup;
- algorithmic complexity under the Push_swap operation model;
- modular C code following the 42 Norm.

The program prints the sequence of operations needed to sort stack `a` in ascending order, with the smallest value ending at the top of the stack.

---

## 📐 Technical and Algorithmic Decisions

The project is built around a modular architecture. The input is parsed first, then each value is normalized through an index, and finally a sorting strategy is selected and executed.

### Indexing

The input values are not sorted directly by their raw integer value. Instead, each node receives an `index` representing its position in the sorted order.

Example:

```text
value: 100 -> 23 -> 1 -> 74 -> 923
index:   3 ->  1 -> 0 ->  2 ->   4
```

This makes the sorting logic easier because the algorithms can work with a compact range from `0` to `size - 1`, regardless of whether the original values are negative, very large, or far apart.

Indexes are assigned once after parsing and before sorting. They are not updated during operations, because the index belongs to the value itself, not to the current position of the node in the stack.

### Initial Disorder Index

Before sorting, the program computes a disorder index based on inversions in the input. An inversion happens when a larger value appears before a smaller one.

This gives an estimation of how far the input is from being sorted and helps the adaptive strategy decide which internal approach is more appropriate.

### Sorting Strategies

#### 1. Simple Strategy — Small Inputs / O(n²)

The simple strategy is used for small inputs. It handles very small stacks with direct logic and uses minimum extraction for small sets.

This avoids the overhead of larger algorithms when the number of elements is low.

#### 2. Medium Strategy — Chunks / O(n√n)

The chunk-based strategy divides the indexed range into groups. Elements are pushed from stack `a` to stack `b` according to moving index windows, and stack `b` is partially organized during the process.

When all relevant values are in `b`, the algorithm repeatedly brings the highest index back to the top of `b` using the shortest rotation direction, then pushes it back to `a`.

This strategy gives good results for medium and large inputs while keeping the logic understandable.

#### 3. Complex Strategy — Radix / O(n log n)

The radix strategy works on the binary representation of the normalized indexes. It processes each bit and moves elements between stacks according to whether that bit is set.

Using indexes makes radix practical because all values are in the range `0` to `size - 1`.

#### 4. Adaptive Strategy

The adaptive strategy is the default behavior. It chooses the internal strategy according to the input size and the disorder index.

The goal is to avoid using a heavy strategy for small or nearly sorted inputs, while still using scalable methods for larger and more disordered stacks.

---

## 📊 Performance Targets

According to the project requirements, the program must stay within the expected operation limits:

### 100 random numbers

- Minimum requirement: fewer than 2000 operations
- Good performance: fewer than 1500 operations
- Excellent performance: fewer than 700 operations

### 500 random numbers

- Minimum requirement: fewer than 12000 operations
- Good performance: fewer than 8000 operations
- Excellent performance: fewer than 5500 operations

The implementation was tested with random inputs and verified with the project checker to ensure that the generated operations correctly sort the stack.

---

## 🛠️ Usage

### Requirements

- `cc`, `clang`, or `gcc`
- `make`
- Unix-based system such as Linux or macOS

### Compilation

Compile the mandatory program:

```bash
make
```

Compile the bonus checker:

```bash
make bonus
```

Remove object files:

```bash
make clean
```

Remove object files and binaries:

```bash
make fclean
```

Rebuild everything:

```bash
make re
```

### Running Push_swap

The program accepts integers as separate arguments:

```bash
./push_swap 4 67 3 87 23
```

It also accepts quoted strings containing several numbers:

```bash
./push_swap "4 67 3 87 23"
```

Mixed input is supported:

```bash
./push_swap "100 23 1" 74 923
```

Optional strategy flags may be placed before, between, or after the numbers:

```bash
./push_swap --simple 3 2 1
./push_swap 3 2 --medium 1
./push_swap "5 4" --complex 3 2 1
./push_swap 32 3 4 --bench 1 55
```

If no strategy flag is provided, the program uses the adaptive strategy by default.

### Available Flags

- `--simple`: forces the simple strategy.
- `--medium`: forces the chunk-based strategy.
- `--complex`: forces the radix strategy.
- `--adaptive`: forces the adaptive strategy.
- `--bench`: enables benchmark output.

Only one strategy flag should be used at a time. The `--bench` flag can be combined with one strategy flag.

### Benchmark Mode

Benchmark mode prints additional information to `stderr`, not to `stdout`.

This is important because `stdout` must contain only Push_swap operations, so it can be safely piped into the checker.

Example:

```bash
./push_swap --bench 3 2 1 | ./checker 3 2 1
```

The checker receives only the operations through the pipe. The benchmark report remains separated on `stderr`.

---

## ✅ Validation with Checker

The generated operations can be verified with the checker:

```bash
ARG="3 1 2 5 4"; ./push_swap $ARG | ./checker $ARG
```

Expected output:

```text
OK
```

A mixed input example:

```bash
./push_swap "100 23 1 74 923" 89 33 12 | ./checker "100 23 1 74 923" 89 33 12
```

Expected output:

```text
OK
```

Benchmark output can be redirected separately:

```bash
./push_swap --bench 3 2 1 > ops 2> bench.txt
./checker 3 2 1 < ops
```

---

## ❌ Error Handling

The program prints `Error` followed by a newline to `stderr` when the input is invalid.

Examples of invalid input:

```bash
./push_swap 1 2 2
./push_swap ""
./push_swap "   "
./push_swap 2147483648
./push_swap -2147483649
./push_swap 3 2 hello 1
./push_swap --simple --complex 3 2 1
```

The checker also prints `Error` for invalid arguments or invalid instructions.

---

## 📚 Resources and Use of AI

### References

- 42 Push_swap subject
- 42 Norm
- 42 community explanations about chunk-based sorting
- General references on sorting algorithms and algorithmic complexity

### AI Usage Statement

AI assistance was used as a support tool during the project workflow, mainly for:

- reviewing project structure;
- identifying parsing edge cases;
- improving the README wording and organization;
- reasoning about test cases;
- checking whether the implementation matched the expected subject behavior.

All generated suggestions were manually reviewed, adapted, tested, and validated with:

- `norminette`;
- `make` and `make bonus`;
- `valgrind`;
- the project checker;
- random input tests.

The final responsibility for the code, the tests, and the project defense remains with the authors.
