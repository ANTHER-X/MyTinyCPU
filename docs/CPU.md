# CPU

La CPU tiene RAM y ROM Interna, en total 64 bytes de RAM y 255 bytes de ROM.
Puedes cargar datos a ROM agregando un binario, en main esta definido como "inst.bin"

## Flags
Para las flags, de momento tenemos implementado:
| Bit       | Tipo |
| ---       | --- |
| 0000 000X | Carry |
| 0000 00X0 | Zero |

## SP (Stack Pointer)
La CPU tiene una limitacion de 16 bytes de RAM, dentro de esos 16 bytes, hay un espacio reservado para el Stack, este espacio es de los bytes de RAM 11-15. El resto 0-10 esta libre para el uso de variables. 