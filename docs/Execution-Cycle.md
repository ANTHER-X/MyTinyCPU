# Ciclo de ejecución

## Etapas

La CPU utiliza tres etapas: Fetch, Decode y Execute.

```text
Fetch → Decode → Execute → repetir mientras Running
```

## Fetch

`CPU::Fetch()` obtiene un byte mediante `GetByteROM()` y lo almacena en `IR`. Conceptualmente, `IR = ROM[PC]` y después `PC` avanza una posición.

`GetByteROM()` comprueba el límite de ROM. Si `PC` ya no es válido, detiene la CPU.

## Decode

`CPU::Decode()` realiza:

```text
OPCODE ← IR
DATA ← siguiente byte de ROM
PC ← PC + 1
```

El segundo byte se consume siempre. Por ello, todas las instrucciones tienen dos bytes, incluso NOP, NOT y END.

## Execute

`CPU::Execute()` selecciona la operación mediante `switch(OPCODE)`. Devuelve el número de ciclos asociado a esa instrucción. Los opcodes desconocidos no realizan una operación y devuelven dos ciclos.

## Bucle principal

`CPU::Run()` ejecuta Fetch, Decode y Execute; suma los ciclos a `TotalCycles`, incrementa `InstructionCount` y calcula el instante objetivo a partir del reloj inicial y los ciclos acumulados. Después espera mediante `std::this_thread::sleep_until()`.

## END

`END` cambia `Running` a falso. El bucle actual todavía suma sus ciclos, incrementa el contador de instrucciones y realiza la espera de esa iteración. Por eso END se incluye en las estadísticas.

## Fin de ROM

Si una lectura excede ROM, `GetByteROM()` detiene la CPU y devuelve cero.
