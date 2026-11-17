# Ciclos y temporización

## Frecuencia

La constante actual es:

```cpp
static constexpr uint32_t CLOCK_HZ = 2000;
```

Esto representa 2000 Hz (2 kHz). El tiempo ideal por ciclo es `1 / 2000 = 0.0005 s`, es decir, 0.5 ms.

## Coste de instrucciones

| Instrucción | Ciclos |
|---|---:|
| NOP | 2 |
| LOAD | 2 |
| STORE | 3 |
| GET | 3 |
| ADD | 4 |
| DES | 4 |
| JMP | 3 |
| JZ, no tomado | 2 |
| JZ, tomado | 3 |
| JC, no tomado | 2 |
| JC, tomado | 3 |
| CMP | 4 |
| PUSH | 3 |
| POP | 3 |
| CALL | 4 |
| RET | 4 |
| AND | 2 |
| OR | 2 |
| XOR | 2 |
| NOT | 2 |
| END | 2 |
| Opcode desconocido | 2 |

Estos valores son el modelo de temporización propio de MyTinyCPU.

## Tiempo teórico

```text
Tiempo = TotalCycles / CLOCK_HZ
```

Por ejemplo, 6000 ciclos a 2000 Hz representan 3 segundos.

## Estadísticas

- `TotalCycles`: suma de ciclos devueltos por Execute.
- `InstructionCount`: cantidad de instrucciones contabilizadas.

END se incluye en ambos contadores. `InitRun()` no reinicia actualmente los contadores, por lo que varias ejecuciones con la misma instancia pueden acumular estadísticas.
