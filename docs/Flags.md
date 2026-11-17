# Banderas de estado

## Registro Flags

Solo están definidos dos bits:

| Bandera | Bit | Máscara |
|---|---:|---:|
| Carry (C) | 0 | `0x01` |
| Zero (Z) | 1 | `0x02` |

Los demás bits no tienen función definida.

## Carry

En ADD, Carry se activa si se desborda la suma. En DES, Carry se activa cuando `A < b`, indicando préstamo. Las operaciones lógicas solicitan limpiar Carry.

## Zero

Zero indica que el resultado evaluado es cero:

- ADD: la suma es cero.
- DES: la resta produce cero; actualmente también se activa cuando hay subdesbordamiento saturado.
- CMP: compara A y RAM[DATA].
- AND, OR, XOR y NOT: el resultado de ocho bits es cero.

LOAD, STORE, GET, PUSH, POP y los saltos no actualizan explícitamente las banderas.

## Saltos condicionales

JZ comprueba si Zero Flag esta activa. JC comprueba si Carry Flag esta activa. Si la condición se cumple, `PC` recibe `DATA`.


## CMP y DES

La comparación establece `Z = (A == b)` y `C = (A < b)`.
