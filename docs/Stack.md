# Pila y subrutinas

## Región reservada

La pila ocupa los últimos 16 bytes de RAM: `0x30–0x3F` (`RAM[48]` a `RAM[63]`). La RAM general ocupa `0x00–0x2F`.

## Crecimiento

La pila crece hacia direcciones inferiores. `SP` comienza en 64 (`0x40`), que representa la posición inmediatamente posterior al final de RAM.

`PUSH` comprueba que exista espacio, decrementa SP y escribe en `RAM[SP]`. `POP` comprueba que la pila no esté vacía, lee `RAM[SP]`, incrementa SP y devuelve el dato.

Ejemplo:

```text
Estado inicial: SP = 64
PUSH:           SP = 63; RAM[63] = dato
Segundo PUSH:   SP = 62; RAM[62] = dato
POP:            dato = RAM[62]; SP = 63
```

## Límites actuales

- `PUSH` no hace nada si SP ya no es mayor que 48.
- `POP` devuelve cero si SP es mayor o igual que 64.
- No se activa una bandera ni se genera un error al desbordar o subdesbordar la pila.
- La capacidad máxima es de 16 bytes.

## CALL

Decode ya consumió los dos bytes de CALL, por lo que `PC` apunta a la siguiente instrucción. `CALL` realiza:

```text
PUSH(PC)
PC ← DATA
```

## RET

`RET` realiza:

```text
PC ← POP()
```

## Ejemplo conceptual

```text
00: 0C 08    ; CALL 0x08
02: FF 00    ; END
08: 01 05    ; LOAD 5
0A: 0D 00    ; RET
```

CALL guarda `0x02`, salta a `0x08`, la subrutina carga 5 y RET recupera `0x02`. Después se ejecuta END.
