#include <iostream>
#include <cpu.hpp>


int main(){

    CPU cpu1;
    cpu1.LoadROM("inst.bin");

    cpu1.ViewRam(); // Tabla de RAM
    cpu1.ViewRom(); // Matriz de la ROM

    cpu1.InitRun(); // PC = 0
    cpu1.Run(); // Itera y recorre IR y PC hasta que se detenga: 1111
    // Si PC llega al tope de la RAM, se reinicia el contador

    cpu1.ViewRegisters(); // Mostrar la tabla de RA final, asi como
    /*A, PC, IR, Carry, Zero y Running (estado activo del CPU)*/

    return 0;
}