#include <cpu.hpp>

void CPU::AddInstruccion(uint8_t instruccion, uint8_t data){
    ROM[PC] = instruccion;
    ROM[PC++] = data;
    PC++;
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

    ViewRam();
    ViewRom();
    std::cout << std::endl << "Datos Internos:" << std::endl;
    std::cout << "PC: " << std::bitset<8>(PC) << std::endl;
    std::cout << "IR: " << std::bitset<8>(IR) << std::endl;
    std::cout << "A: " << std::bitset<8>(A) << std::endl;
    std::cout << "Flags: " << std::bitset<8>(Flags) << std::endl;
    std::cout << "Running: " << std::bitset<8>(Running) << std::endl;
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
    PC = 0;
    Running = true;
}

void CPU::Run(){
    // Salimos si no se ah iniciado
    if(!Running){
        std::cout << std::endl << "La CPU no ah sido inicializada!!!" << std::endl;
        return;
    }

    std::cout << std::endl << "Iniciando Ciclo: " << std::endl;
    while(Running){
        Fetch();
        Decode();
        Execute();
    }
}

void CPU::Fetch(){
    IR = GetByteROM();
    if(!Running) std::cout << "RUNNING STOP, OUT OF ROM" << std::endl;

    std::cout << "IR: " << std::bitset<8>(IR) << std::endl
              << "SP: " << std::bitset<8>(SP) << std::endl
              << "PC Pointer: " << std::bitset<8>(PC)
              << ". PC Register: " << std::bitset<8>(ROM[PC]) << std::endl;
}

void CPU::Decode(){
    OPCODE = IR;
    if( (OPCODE <= 0x05 && OPCODE > 0x00) || OPCODE == 0x09 || (OPCODE>=0xE && OPCODE < 0x11)) DATA = GetByteROM();
    std::cout << "Codigo de operacion: " << std::bitset<8>(OPCODE) << 
                 ". Dato: " << std::bitset<8>(DATA) << std::endl << std::endl;
}

void CPU::Execute(){
    switch(OPCODE){

        // No hace nada :/
        case 0x00:{ break; }
        // Carga Datos hacia A
        case 0x01:{ A = DATA; break;}

        case 0x02:{ // Guarda A en la posicion en memoria
            RAM[DATA] = (A & 0x0F); break;}

        case 0x03:{ // Guarda en A una pos en RAM
            A = (RAM[DATA] & 0x0F); break;}

        case 0x04:{ // Suma A una pos de RAM
            A = ADD(A, RAM[DATA]);  break;}

        case 0x05:{ // Resta Suma A una pos de RAM
            A = DES(A, RAM[DATA]);  break;}

        // Salto de PC hacia puntero
        case 0x06:{ Jump();         break;}

        case 0x07: { // Salta a PC si esta activo Zero
            if((Flags & 0x02) == 0x02) Jump();      break;}

        case 0x08: { // Salta a PC si Carry esta activo
            if( (Flags & 0x01) == 0x01 ) Jump();    break;}

        case 0x09: { // Compara la Resta de A y pos en RAM
            CMP(A, RAM[DATA]);  break;}
        
        // PUSH
        case 0x0A: { PUSH(A); break;}
        // POP 
        case 0x0B: { POP(A); break;}
        // CALL
        case 0x0C:{
            CALL();
            break;}
        // RET
        case 0x0D:{ RET(); break;}

        // And, execute A And Data
        case 0x0E:{
            A = AND(A, DATA);
            SetFlag(FLAG_Z, (A == 0x00));
            SetFlag(FLAG_C, false);
            break;
        }
        // OR
        case 0x0F:{
            A = OR(A, DATA);

            SetFlag(FLAG_Z, (A == 0x00));
            SetFlag(FLAG_C, false);
            break;
        }
        // XOR
        case 0x10:{
            A = XOR(A, DATA);

            SetFlag(FLAG_Z, (A == 0x00));
            SetFlag(FLAG_C, false);
            break;
        }
        // NOT
        case 0x11:{
            A = NOT(A);

            SetFlag(FLAG_Z, (A == 0x00));
            SetFlag(FLAG_C, false);
            break;
        }

        // Terminar las instrucciones
        case 0xFF: {
            Running = false;
            std::cout << std::endl << "Operaciones terminadas." << std::endl;
            break;
        }

        // No hacemos nada si no sabe la instruccion
        default: break;
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
void CPU::PUSH(uint8_t data){
    RAM[SP] = data;
    if(SP > 10) SP--;
}

void CPU::POP(uint8_t data){
    data = RAM[SP];
    if(SP < RAM_SIZE)SP++;
}

void CPU::CALL(){
    PUSH(PC);
    PC = DATA;
}

void CPU::RET(){
    POP(PC);
}

uint8_t CPU::ADD(uint8_t a, uint8_t b){
    uint8_t result = a + b;
    SetFlag(FLAG_C, (result > 15));
    SetFlag(FLAG_Z, (result == 0x00));

    return (result & 0x0F);
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

    return (result & 0x0F);
}

void CPU::CMP(uint8_t a, uint8_t b){
    uint8_t result = DES(a,b);
}

void CPU::Jump(){
    PC = DATA;
}
