# MyTinyCPU

Documentación técnica de la arquitectura, memoria, registros, instrucciones y funcionamiento de **MyTinyCPU**.

## Índice

1. [Arquitectura](docs/Architecture.md)
2. [Registros](docs/Registers.md)
3. [Mapa de memoria](docs/Memory.md)
4. [Conjunto de instrucciones](docs/Instructions.md)
5. [Ciclo de ejecución](docs/Execution-Cycle.md)
6. [Pila y subrutinas](docs/Stack.md)
7. [Banderas](docs/Flags.md)
8. [Ciclos y temporización](docs/Timing.md)
9. [Limitaciones conocidas](docs/Known-Issues.md)

## Resumen

| Propiedad | Valor |
|---|---:|
| Frecuencia configurada | 2000 Hz (2 kHz) |
| ROM | 255 bytes (`0x00–0xFE`) |
| RAM | 64 bytes (`0x00–0x3F`) |
| RAM general | 48 bytes (`0x00–0x2F`) |
| RAM reservada para pila | 16 bytes (`0x30–0x3F`) |
| Registros principales | A, PC, IR, SP |
| Ancho de registros | 8 bits |
| Tamaño de instrucción | 2 bytes |
| Banderas | Carry (C), Zero (Z) |
| Terminador | `0xFF` (`END`) |

Todas las instrucciones ocupan dos bytes: `[ OPCODE ][ OPERANDO ]`. El segundo byte se consume siempre, aunque la instrucción no lo utilice.

Esta documentación describe el código proporcionado. Los defectos conocidos se señalan por separado y no se presentan como funcionalidades ya corregidas.

## Uso
Para usar:  
* **--debug** o **-dbg**: activa debug de consola (imprime registro y datos de ROM y RAM)  
``` bash
./MyTinyCPU <program.bin>
```
Ejemplo:
``` bash
./MyTinyCPU -dbg resta.bin
```

## Crear programas
Para crear los programas puedes consultar los archivos de la carpeta `docs`, con **ISA.md** para las instrucciones y **CPU.md** para las flags y SP.

Una vez tengas el programa que decees, lo puedes guardar en un archivo .hex y convertirlo en binario con xdd en linux:
``` bash
; crea tu programa
nano program.hex

; Convertirlo en binario
xxd -r -p program.hex program.bin

; Cargarlo al CPU
./MyTinyCPU -dbg program.bin
```

## Compilar y probar

Para ejecutar la prueba de rendimiento, primero se debe compilar el emulador y después ejecutar el programa `benchmark.hex`:

```bash
mkdir build
cmake -S . -B build
cmake --build build
```

Una vez compilado puedes probar:
```bash
./build/MyTinyCPU ./tests/benchmark.bin
```

## Autor 
**ANTHER-X**  
GitHub: https://github.com/ANTHER-X  
Email: fernandocisneroslemus@gmail.com  

## Licencia

Este proyecto está distribuido bajo los términos de la licencia MIT. Consulte el archivo LICENSE para obtener más detalles.