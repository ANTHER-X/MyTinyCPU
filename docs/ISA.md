# ISA

La cadena de ROM es de 2 bytes, 1 byte para el OPCode del CPU y el siguiente byte como datos, las instrucciones agregadas se guardan en ROM.

Se mantiene una secuancia de 8 bits par los datos en el CPU y 8 para el contador (PC), asi que solo hay un maximo de 255 bytes de ROM con un maximo de 64 de RAM para los registros temporales, o se el guardado de datos.

Los datos no incrustados en las instrucciones, es decir los datos que no son LOAD, se guardan y toman de RAM.
Los datos en la RAM se mantienen en los primeros 4 bits, pero la ram se representa en bytes.

AND, OR, XOR y NOT hacen las operaciones con A y guardan en A, solo afecta ZFlag y Flag Carry la deja en 0.

| Code | Instruction | Description |
|  --- | ---         | --- |
| 0000 0000 | NOP  | No hace nada, o lo tomas como datos (sin instruccion). |
| 0000 0001 | LOAD | Carga datos al registro A |
| 0000 0010 | STORE| Guarda A en una pocision de RAM |
| 0000 0011 | GET  | Guarda en A una posicion de RAM |
| 0000 0100 | ADD  | Suma a registro A una posicion de RAM |
| 0000 0101 | DES  | Resta a registro A una posicion de RAM|
| 0000 0110 | JMP  | Mueve PC a X posicion |
| 0000 0111 | JZ   | Mueve PC a X posicion si Zero esta actuvo |
| 0000 1000 | JC   | Mueve PC a X posicion si Carry esta activo|
| 0000 1001 | CMP  | Mueve Resta de A con pos en RAM, para C y Z |
| 0000 1010 | PUSH | Guarda A el la Pila |
| 0000 1011 | POP | Saca de la Pila y lo guarda en A |
| 0000 1100 | CALL | Movemos una rutina a N parte, el siguiente Byte es la posicion |
| 0000 1101 | RET | Extrae del Stack el valor guardandolo en el PC (contador de programa). |
| 0000 1110 | AND | Ejecuta: A And Data |
| 0000 1111 | OR | Ejecuta: A OR Data |
| 0001 0000 | XOR | Ejecuta: A XOR Data |
| 0001 0001 | NOT | Ejecuta: NOT A |
| 0001 0010 | ??? | ??? |
| 0001 0011 | ??? | ??? |
| 0001 0100 | ??? | ??? |
| 0001 0101 | ??? | ??? |
| 0001 0110 | ??? | ??? |
| 1111 1111 | END  | Termina las instrucciones (no es espera) |
