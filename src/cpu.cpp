#include <cpu.hpp>

void CPU::AddInstruccion(uint8_t instruccion, uint8_t data){
    ROM[PC++] = instruccion;
    ROM[PC++] = data;
}


void CPU::ViewRam(){
    std::cout << "Registros de RAM:" << std::endl; 
    for(uint8_t i=0; i<RAM_SIZE; i++)
        std::cout << std::bitset<8>(RAM[i]) << std::endl;
}

void CPU::ViewRom(){
    std::cout << std::endl << "Registros de ROM:" << std::endl;

    for(size_t i=0; i<ROM_SIZE; i+=8){
        for(size_t j=i; j<i+8; j++)
            std::cout << std::bitset<8>(ROM[j]) << "    ";
        std::cout<< std::endl;
    }
}

void CPU::ViewRegisters(){

    if(debug){
        ViewRam();
        ViewRom();
    }
    std::cout << std::endl << "Datos Internos:" << std::endl;
    std::cout << "PC: " << std::bitset<8>(PC) << std::endl;
    std::cout << "IR: " << std::bitset<8>(IR) << std::endl;
    std::cout << "A: " << std::bitset<8>(A) << std::endl;
    std::cout << "Flags: " << std::bitset<8>(Flags) << std::endl;
    std::cout << std::boolalpha;
    std::cout << "Running: " << Running << std::endl;
    std::cout << std::noboolalpha;
    std::cout << "Cycles Executed: " << TotalCycles << std::endl;
    std::cout << "Instructions Used: " << InstructionCount << std::endl;
}

uint8_t CPU::GetByteROM(){
    if(PC >= ROM_SIZE){
        PC = 0;
        Running = false;
        return 0x00;
    }
    uint8_t byte = ROM[PC];
    PC++;
    return byte;
}

void CPU::InitRun(){
    for(uint8_t& by : RAM) by=0;
    for(uint8_t& by : ROM) by=0;
    A = DATA = IR = OPCODE = PC = Flags = 0x00;
    SP = RAM_SIZE-1;
    debug = false;
    Running = true;
}

void CPU::Run(bool dbg){
    // Salimos si no se ah iniciado
    if(!Running){
        std::cout << std::endl << "La CPU no ah sido inicializada!!!" << std::endl;
        return;
    }
    debug = dbg;
    auto start = std::chrono::steady_clock::now();

    // ver los datos
    if(debug){
        ViewRom();
        ViewRam();
    }

    std::cout << "Potencia: " << CLOCK_HZ << "Hz";
    std::cout << std::endl << "Iniciando Ejecucion: " << std::endl;
    while(Running){
        Fetch();
        Decode();
        uint8_t cycles = Execute();

        TotalCycles += cycles;
        InstructionCount++;

        auto elapsed = std::chrono::duration<double>(static_cast<double>(TotalCycles) / CLOCK_HZ );
        auto target = start +
        std::chrono::duration_cast<std::chrono::steady_clock::duration>(elapsed);

        std::this_thread::sleep_until(target);
    }

    // ver los datos
    ViewRegisters();
}

void CPU::Fetch(){
    IR = GetByteROM();
    if(!Running) std::cout << "RUNNING STOP, OUT OF ROM" << std::endl;

    if(debug) std::cout << "IR: " << std::bitset<8>(IR) << std::endl
              << "A: " << std::bitset<8>(A) << std::endl
              << "SP: " << std::bitset<8>(SP) << std::endl
              << "PC Pointer: " << std::bitset<8>(PC)
              << ". PC Register: " << std::bitset<8>(ROM[PC]) << std::endl;
}

void CPU::Decode(){
    OPCODE = IR;
    DATA = GetByteROM();
    
    if(debug)std::cout << "Codigo de operacion: " << std::bitset<8>(OPCODE) << 
            ". Dato: " << std::bitset<8>(DATA) << std::endl << std::endl;
}

uint8_t CPU::Execute(){
    if(!Running) std::cerr << "Limite de ROM alcanzado, no se puede continuar" << std::endl;
    switch(OPCODE){

        // No hace nada :/
        case 0x00:{ return 2; }
        // Carga Datos hacia A
        case 0x01:{ A = DATA; return 2;}

        case 0x02:{ // Guarda A en la posicion en memoria
            if(DATA >= RAM_SIZE) return 2;
            RAM[DATA] = A; return 3;}

        case 0x03:{ // Carga en A una pos en RAM
            if(DATA >= RAM_SIZE) return 2;
            A = RAM[DATA]; return 3;}

        case 0x04:{ // Suma A una pos de RAM
            if(DATA >= RAM_SIZE) return 2;
            A = ADD(A, RAM[DATA]);  return 4;}

        case 0x05:{ // Resta Suma A una pos de RAM
            if(DATA >= RAM_SIZE) return 2;
            A = DES(A, RAM[DATA]);  return 4;}

        // Salto de PC hacia puntero
        case 0x06:{ Jump();         return 3;}

        case 0x07: { // Salta a PC si esta activo Zero
            if((Flags & FLAG_Z) == FLAG_Z){
                Jump();
                return 3;
            }
            return 2;}

        case 0x08: { // Salta a PC si Carry esta activo
            if((Flags & FLAG_C) == FLAG_C){
                Jump();
                return 3;
            }
            return 2;}

        case 0x09: { // Compara la Resta de A y pos en RAM
            CMP(A, RAM[DATA]);  return 4;}
        
        // PUSH
        case 0x0A: { PUSH(A);   return 3;}
        // POP 
        case 0x0B: { A = POP(); return 3;}
        // CALL
        case 0x0C:{ CALL(); return 4;}
        // RET
        case 0x0D:{ RET(); return 4;}

        // And, execute A And Data
        case 0x0E:{
            A = AND(A, DATA);
            SetFlag(FLAG_Z, (A == 0x00));
            SetFlag(FLAG_C, false);
            return 2;
        }
        // OR
        case 0x0F:{
            A = OR(A, DATA);

            SetFlag(FLAG_Z, (A == 0x00));
            SetFlag(FLAG_C, false);
            return 2;
        }
        // XOR
        case 0x10:{
            A = XOR(A, DATA);

            SetFlag(FLAG_Z, (A == 0x00));
            SetFlag(FLAG_C, false);
            return 2;
        }
        // NOT
        case 0x11:{
            A = NOT(A);

            SetFlag(FLAG_Z, (A == 0x00));
            SetFlag(FLAG_C, false);
            return 2;
        }

        // Terminar las instrucciones
        case 0xFF: {
            Running = false;
            std::cout << std::endl << "Operaciones terminadas." << std::endl;
            return 2;
        }

        // No hacemos nada si no sabe la instruccion
        default: return 2;
    }
}

// Carga un .bin
bool CPU::LoadROM(const std::string& filename){

    // Open in bynary
    std::ifstream file(filename, std::ios::binary);
    if(!file.is_open())
        return false;

    uint8_t buffer[ROM_SIZE];

    // Leemos hasta el maximo de ROM
    file.read( reinterpret_cast<char*>(buffer), ROM_SIZE );
    std::streamsize bytesRead = file.gcount();

    // Verificamos
    if(file.bad()){
        file.close();
        return false;
    }

    // Guardamos en ROM
    for(std::streamsize i = 0; i < bytesRead; i++){
        ROM[i] = buffer[i];
    }

    file.close();
    return true;
}


/*########### Operacions de la ALU ###########*/
void CPU::PUSH(uint8_t addr){
    if(SP > RAM_SIZE - RAM_RESERVED){
        SP--;
        RAM[SP] = addr;
    }
}

uint8_t CPU::POP(){
    if(SP < RAM_SIZE){
        uint8_t addr = RAM[SP];
        SP++;
        return addr;
    }
    else return 0;
}

void CPU::CALL(){
    PUSH(PC);
    PC = DATA;
}

void CPU::RET(){
    PC = POP();
}

uint8_t CPU::ADD(uint8_t a, uint8_t b){
    bool carry = a + b > std::numeric_limits<uint8_t>::max();
    uint8_t result = a+b;
    SetFlag(FLAG_C, carry);
    SetFlag(FLAG_Z, (result == 0x00));

    return result;
}

uint8_t CPU::DES(uint8_t a, uint8_t b){
    uint8_t result;
    if(a < b){
        result = 0x00;
        SetFlag(FLAG_C, 1);
        SetFlag(FLAG_Z, 1);
    }
    else{
        result = a - b;
        SetFlag(FLAG_C, 0);
        SetFlag(FLAG_Z, (result == 0x00));
    }

    return result;
}

void CPU::CMP(uint8_t a, uint8_t b){
    SetFlag(FLAG_C, (a < b));
    SetFlag(FLAG_Z, (a == b));
}

void CPU::Jump(){
    PC = DATA;
}
