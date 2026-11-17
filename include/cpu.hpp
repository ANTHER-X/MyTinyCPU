#ifndef CPU_HPP
#define CPU_HPP

#include <iostream>
#include <fstream>
#include <cstdint>
#include <bitset>

#include <thread>
#include <chrono>


class CPU{
private:

    static constexpr uint32_t CLOCK_HZ = 1000; // 1000Hz
    static constexpr uint8_t RAM_SIZE = 64;
    static constexpr uint8_t RAM_RESERVED = 16;
    static constexpr uint8_t ROM_SIZE = 255;

    uint64_t TotalCycles = 0;
    uint64_t InstructionCount = 0;

    uint8_t A = 0; // Registro A
    uint8_t PC = 0; // Program Counter
    uint8_t IR = 0; // Intruction Register
    uint8_t SP = RAM_SIZE; // Stack pointer
    uint8_t RAM[RAM_SIZE] = {0}; // Internal RAM
    uint8_t ROM[ROM_SIZE] = {0}; // ROM

    uint64_t Cycles = 0;

    // Datos para las operaciones
    uint8_t OPCODE;
    uint8_t DATA;

    // Flags de CPU
    uint8_t Flags = 0x00;
    
    static constexpr uint8_t FLAG_C = 0x01;
    static constexpr uint8_t FLAG_Z = 0x02;

    bool Running = false;
    bool debug = false; // Debug for programs

    // Pasos de los calculos de la CPU
    void Fetch();
    void Decode();
    uint8_t Execute();

    // Poner mascara de flag
    inline void SetFlag(uint8_t mask, bool state){
        if(state) Flags |= mask; // Agrega bits a Flags
        else Flags &= static_cast<uint8_t>(~mask); // Limpia esos bits de Flags
    }

    uint8_t GetByteROM();

    // Operaciones de la ALU
    uint8_t ADD(uint8_t a, uint8_t b);
    uint8_t DES(uint8_t a, uint8_t b);
    void CMP(uint8_t a, uint8_t b);
    void Jump();
    void PUSH(uint8_t addr);
    uint8_t POP();
    void CALL();
    void RET();
    inline uint8_t AND(uint8_t a, uint8_t b){return a&b;}
    inline uint8_t OR(uint8_t a, uint8_t b){return a|b;}
    inline uint8_t XOR(uint8_t a, uint8_t b){return a^b;}
    inline uint8_t NOT(uint8_t a){return ~a;}


public:

    // Cargamos un binario
    bool LoadROM(const std::string& filename);

    void AddInstruccion(uint8_t instruccion, uint8_t data);
    void ViewRam();
    void ViewRom();
    void ViewRegisters();

    // Inicializar la CPU
    void InitRun();
    void Run(bool dbg = false);
};


#endif // CPU_HPP
