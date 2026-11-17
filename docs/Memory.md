# Mapa de memoria

MyTinyCPU utiliza dos arreglos independientes: ROM para instrucciones y RAM para datos y pila.

## ROM

```cpp
static constexpr uint8_t ROM_SIZE = 255;
uint8_t ROM[ROM_SIZE] = {0};
```

Las direcciones válidas son `0x00–0xFE`. El programa se lee mediante `PC`. Los saltos modifican `PC` para continuar desde otra posición.

## RAM

RAM contiene 64 bytes, con direcciones válidas `0x00–0x3F`.

| Rango | Tamaño | Uso |
|---|---:|---|
| `0x00–0x2F` | 48 bytes | RAM general |
| `0x30–0x3F` | 16 bytes | Pila |

```text
0x3F ┌──────────────────┐
     │   Pila (16 B)    │  RAM[48..63]
0x30 ├──────────────────┤
     │  RAM general     │  RAM[0..47]
0x00 └──────────────────┘
```

## Acceso a RAM

`STORE`, `GET`, `ADD`, `DES` y `CMP` utilizan `DATA` como índice directo. `STORE` guarda los bits de `A`; `GET` carga los bits de la celda.

La implementación comprueba que `DATA < 64`. Los programas deben usar direcciones válidas, si no es asi no se opera.

## Espacios separados

ROM y RAM son arreglos distintos. `JMP 0x20` cambia el flujo de lectura de ROM; `STORE 0x20` escribe en `RAM[0x20]`.

## Fin de ROM

`GetByteROM()` detiene la CPU si `PC >= ROM_SIZE`, establece `PC = 0` y devuelve cero. No hay wraparound normal: alcanzar el límite detiene la ejecución.
