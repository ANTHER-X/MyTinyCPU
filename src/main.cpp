#include <iostream>
#include <limits>
#include <cpu.hpp>


int main(int argc, char* argv[]){
    if(argc < 2){
        std::cerr << "No Program Loaded. Use ./MyTinyCPU <program.bin> for use" << std::endl;
        return 1;
    }

    bool deb = false;

    int posFlag = 1;
    // Validar flag de debug
    for(; posFlag<argc; posFlag++){
        std::string arg = argv[posFlag];
        if(arg == "-debug" || arg == "-dbg"){
            std::cout << "Debug activo." << std::endl;
            deb = true;
            break;
        }
    }

    CPU cpu1;
    for (int i=1; i<argc; i++){
        // Evita cargar flag debug
        if(i == posFlag) continue;

        // Carga programas
        cpu1.InitRun();
        if(cpu1.LoadROM(argv[i])){
            cpu1.Run(deb);
        } else{
            std::cerr << "Error to load program " << i << ". Next program loading..." << std::endl;
        }
    }

    return 0;
}