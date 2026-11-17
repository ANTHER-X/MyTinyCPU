# Conjunto de instrucciones

## Formato

Todas las instrucciones ocupan exactamente dos bytes: `[ OPCODE ][ DATA ]`. `Fetch()` lee el opcode y `Decode()` consume siempre el segundo byte, aunque la instrucción no lo utilice.

## Tabla de opcodes

| Opcode | Instrucción | Operación |
|---:|---|---|
| `0x00` | NOP | No realiza ninguna operación. |
| `0x01` | LOAD | `A = DATA` |
| `0x02` | STORE | `RAM[DATA] = A` |
| `0x03` | GET | `A = RAM[DATA]` |
| `0x04` | ADD | `A = ADD(A, RAM[DATA])` |
| `0x05` | DES | `A = DES(A, RAM[DATA])` |
| `0x06` | JMP | `PC = DATA` |
| `0x07` | JZ | Salta si Zero está activa. |
| `0x08` | JC | Salta si Carry está activa. |
| `0x09` | CMP | Compara `A` con `RAM[DATA]`. |
| `0x0A` | PUSH | Introduce `A` en la pila. |
| `0x0B` | POP | Extrae un byte de la pila y lo guarda en `A`. |
| `0x0C` | CALL | Guarda el retorno y salta a `DATA`. |
| `0x0D` | RET | Recupera el retorno desde la pila. |
| `0x0E` | AND | `A = A & DATA` |
| `0x0F` | OR | `A = A \| DATA` |
| `0x10` | XOR | `A = A ^ DATA` |
| `0x11` | NOT | `A = ~A` |
| `0xFF` | END | Finaliza la ejecución. |

Los opcodes no definidos ejecutan el caso `default`: no realizan una operación y devuelven dos ciclos.

## Transferencia de datos

- **NOP:** no modifica registros ni memoria; el byte de operando se consume.
- **LOAD:** copia el byte `DATA` a `A`.
- **STORE:** escribe `A` en `RAM[DATA]`.
- **GET:** carga `RAM[DATA]` en `A`.

## Aritmética

### ADD

Suma `A` con `RAM[DATA]`. Carry se activa si la suma supera mas de la capacidad de 1 byte; Zero se establece si esa suma es cero.

### DES

Resta `RAM[DATA]` a `A`. Si `A < RAM[DATA]`, el resultado se satura en cero y Carry se activa. En otro caso se realiza la resta normal.

### CMP

Compara A con el valor de la celda de RAM dada en DATA, actualiza Carry flag si el dato en RAM es mayor a A y Zero flag si ambos son iguales.

## Saltos

- **JMP:** asigna `DATA` a `PC`.
- **JZ:** asigna `DATA` a `PC` si Zero está activa.
- **JC:** asigna `DATA` a `PC` si Carry está activa.

Las direcciones de destino deben estar dentro de ROM.

## Pila y subrutinas

- **PUSH:** guarda `A` en la pila.
- **POP:** extrae un byte y lo guarda en `A`.
- **CALL:** guarda el `PC` actual (que ya apunta a la instrucción siguiente) y después salta a `DATA`.
- **RET:** extrae la dirección guardada y la asigna a `PC`.

## Operaciones lógicas

AND, OR y XOR combinan los ocho bits de `A` y `DATA`. NOT invierte los ocho bits de `A`. Estas operaciones actualizan Zero y solicitan limpiar Carry.

## END

`END` (`0xFF`) cambia `Running` a falso. Su segundo byte se consume antes de ejecutar la instrucción.

## Ejemplo

```text
01 05    ; LOAD 5
02 00    ; STORE RAM[0]
03 00    ; GET RAM[0]
FF 00    ; END
```

Los comentarios no forman parte del archivo binario.
