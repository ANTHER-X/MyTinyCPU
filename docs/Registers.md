# Registros de MyTinyCPU

Todos los registros principales tienen un ancho de ocho bits.

## A — Accumulator

Es el acumulador y principal registro de trabajo. Recibe datos de `LOAD`, `GET` y `POP`; participa en `STORE`, `ADD`, `DES`, `CMP` y las operaciones lógicas.

`A` tiene ocho bits, `STORE` guarda `A`, `GET` recupera `RAM[DATA]`, y `ADD`/`DES`, `LOAD` y las operaciones lógicas pueden modificar los ocho bits.

## PC — Program Counter

Indica la dirección de ROM que se leerá a continuación. Se incrementa al consumir bytes y puede modificarse mediante `JMP`, `JZ`, `JC`, `CALL` y `RET`.

Aunque puede representar `0xFF`, las posiciones válidas de ROM son `0x00–0xFE`.

## IR — Instruction Register

Almacena el byte leído durante Fetch. Después, `Decode()` lo copia a `OPCODE`.

## SP — Stack Pointer

Apunta a la pila dentro de RAM. Se inicializa en 64 (`0x40`), la posición inmediatamente posterior al final de RAM. `PUSH` decrementa SP antes de escribir; `POP` lee y después lo incrementa. La pila ocupa `0x30–0x3F`.

## OPCODE y DATA

Son variables internas. `OPCODE` contiene la instrucción que ejecutará `Execute()`. `DATA` contiene el segundo byte de la instrucción. `Decode()` siempre consume ese byte, incluso si no se utiliza.

## Flags

`Flags` contiene Carry en el bit 0 (`0x01`) y Zero en el bit 1 (`0x02`). Los demás bits no están definidos. Véase [Flags.md](Flags.md).

## Contadores estadísticos

`TotalCycles` acumula los ciclos devueltos por `Execute()`. `InstructionCount` cuenta las instrucciones ejecutadas y contabilizadas por el bucle principal.
