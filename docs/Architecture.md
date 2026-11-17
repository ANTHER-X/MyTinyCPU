# Arquitectura de MyTinyCPU

## Descripción general

MyTinyCPU es una CPU experimental implementada en C++. Ejecuta programas binarios almacenados en una ROM interna y utiliza una RAM independiente para datos y pila.

Su diseño se basa en un acumulador, un contador de programa, un registro de instrucción, un puntero de pila y una unidad aritmético-lógica (ALU).

## Características

- Registros principales de 8 bits.
- ROM de 255 bytes (`0x00–0xFE`).
- RAM de 64 bytes (`0x00–0x3F`).
- Un acumulador general: `A`.
- Instrucciones de longitud fija de dos bytes.
- Direccionamiento directo para RAM y saltos.
- Pila descendente de 16 bytes al final de RAM.
- Banderas Carry y Zero.
- Frecuencia configurada de 2000 Hz.

## Organización funcional

La ejecución se divide en tres etapas:

1. **Fetch:** obtiene el opcode desde ROM y lo coloca en `IR`.
2. **Decode:** copia `IR` a `OPCODE` y consume el byte siguiente como `DATA`.
3. **Execute:** ejecuta la operación y devuelve su coste en ciclos.

`PC` indica la siguiente posición de ROM que se leerá.

## Acumulador y ALU

`A` es el único registro de propósito general. Las operaciones trabajan con 1 byte.

## Formato de instrucción

```text
[ OPCODE ][ OPERANDO ]
```

El segundo byte se consume siempre. Esto mantiene alineado `PC` incluso cuando una instrucción no necesita un operando.

## Alcance actual

La arquitectura no implementa registros adicionales, direccionamiento indirecto, entrada/salida.
