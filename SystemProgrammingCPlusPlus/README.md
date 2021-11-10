# Linux System Programming

**《 Hands-On System Programming with C++ 》**

## Requirement
- Intel-based Computer (CPU architectures)
- Linux Ubuntu 20.04 (OS)
- GCC 9.3.0 (Compiler)

```bash
# the basic tool for programming with gcc and g++
sudo apt install build-essential
sudo apt install git cmake
```

## chapter 01
**Getting Started with System Programming**

- System Programming and Network Programming
- System Calls and system call types
- Network Interface Controller(NIC) and sockets and TCP/IP stack
- Potential security risks associated with System Calls
- Non-Maskable Interrupt(NMI) and **SYSRET** instruction
- Meltdown and Spectre attacks and speculative execution technology(modern CPUs)
- **Application programming interface(API)** make calls to the operating system using an **Application Binary Interface(ABI)** called a **system call**. The act of making system calls to accomplish tasks provided by the operating system is called **system programming**
- Type safely and Error handing and Standard Template Library(STL) in C++
- Template Programming and Functional Programming with CPlusPlus


## chapter 02
**Learning the C C++17, and POSIX(Portable Operating System Interface for Computing Systems) Standards**

- C and C++ and POSIX standards 
- C standard: Environment, Language, Libraries
- Environment: compiler, linker, execution
- Language: details syntax, operators supported
- Libraries: describe library facilities
- Facilities these standards provide
- Program linking and execution
- The {} syntax can be used to create **scope** for anything (distinguish Assembly language)
- No matter how experienced you are, nobody truly understands pointers completely.
- C++ standard: General conventions and concepts, Language syntax, Libraries
- Resource Acquisition is Initialization(RAII)
- References versus Pointers
- POSIX standard: the functionality a POSIX-compliant operating system must implement
- Memory Management, Filesystem(FHS), Sockets, Threading(pthreads),

## chapter 03
**System Types for C and C++**

- Default types that C and C++ provide, Standard integer types
- Structure packing, Complications with optimizations, type conversions
- Complex Instruction Set Computer(CISC), Instruction Set Architecture(ISA)
- Reduced Instruction Set Computer(RISC)
- Alignment checks and Masking to perform simple arithmetic operations
- Standard integer types(stdint.h)
- Aligned in memory, Packing the structure

## chapter 04
**c++, Resource Acquisition Is Initialization(RAII), and the Guideline Support Library(GSL) Refresher**

- Resource Acquisition Is Initialization(RAII) in C++ design pattern
- RAII: Language change and Library change
- Guideline Support Library(GSL)
- GSL: Pointer ownership and Expectation management and No pointer arithmetic

## chapter 05
**Programming Linux/Unix Systems**

- Linux ABI or System V ABI and the Executable and Linkable Format(ELF) standard
- https://refspecs.linuxfoundation.org/
- Unix filesystem
- Unix process APIs
- Unix signal APIs
- System V ABI defines low-level details of program(the interfaces for system programming)
- The register layout; The stack frame; Function prologs and epilogs; The calling convention(parameter passing); Exception handing; Virtual memory layout; Debugging; The binary object format(ELF); Program loading and linking
- Instruction pointer(rip) defines a program's current location in executable memory
- Stack pointer(rsp) is used to define the current location in the stack
- Base pointer(rbp) is used to define the location of the beginning of a stack frame
- General-purpose registers: rax, rbx, rcx, rdx, rdi, rsi, r8, r9, r10, r11, r12, r13, r14 and r15
- other registers defined on system that have very specific purposes, including floating-point registers and wide registers(SSE and AVX)
- Registers end with letters(or end with numbers): AX, BX, CX and DX
- Stack frame is used to store the return address of each function, and to store function parameters and stack-based variables

```bash
high  | ---------- |  <- top of stack 
      |            |
      |   Used     |
      |            |
      | ---------- |  <- Current frame (rbp)
      |            |  <- Stack pointer (rsp)
      | ---------- |
      |            |
      |  Unused    |
      |            |
low   | ---------- |
```

- Disassemble the resulting binary and Compile the assemble code
- The calling convention dictates which registers are **volatile** or **non-volatile**
- Volatile register is one that a called function can change at will, without having to restore its value on return
- Frame Description Entry(FDE) and objdump command
- Virtual memory layout and Executable and Linkable Format(ELF)

```bash
# Every ELF file can be viewed in terms of either its segments or its sections.
# Each ELF file is composed of sections. The sections are then grouped into segments, 
# which are used to define which sections need to be loaded, and how 
# (for example, some sections need to be loaded as read-write, 
# others as read-execute, or, in some sub-optimal cases, read-write-execute).


     Segments        Sections
  | ---------- |  | ---------- | 
  |   Header   |  |   Header   | 
  | ---------- |  | ---------- | 
  |            |  |            | 
  |            |  | ---------- | 
  |            |  |            | 
  |            |  |            | 
  | ---------- |  | ---------- | 
  |            |  |            | 
  |            |  | ---------- | 
  |            |  |            | 
  |            |  |            | 
  | ---------- |  | ---------- |

# To see a list of all of the sections
readelf -SW a.out
```

- Position Independent Executable(PIE)
- **.text** : code and segment marked as read-execute, and not given write permissions
- **.data** : global variables that initialized to zero
- **.bss** : all the global variables that should be initialized to 0
- **.dynstr/.strtab** :  These tables contain the strings that are used for symbol names(variable and function names)
- Global Offset Table(GOT) and ELF segments
- Procedure Linkage Table(PLT) and compiler to know the location of symbol
- Unix filesystem and virtual filesystem tree(root /)
- Physical filesystem is usually mapped onto the virtual filesystem(/etc/fstab)
- Unix processes or User-space application
- Create and manage Unix-based processes using commonly-seen POSIX interfaces
- fork function and memory shared marked as copy-on-write
- fork and wait and exec system call
- InterProcess Communication(IPC)
- Output redirection and Unix signals

## chapter 06
**Learning to Program Console Input/Output**

- Standard C printf/scanf IO function
- Stream-based IO
- User-defined type-manipulators
- The Serial Echo server example
- Common debugging patterns
- Performance of C++ streams and Control manipulators
- Example of echo program
- Example of echo server program

## chapter 07
**Comprehensive Look at Memory Management**

- safety and reliability and stability of memory management
- new and delete function
- allocate type-safe memory and aligned memory
- smart pointers and memory mapping and permissions and fragmentation
- Global memory and Stack memory and Heap memory
- Exception for memory, Placement of memory, Overloading
- Smart pointers to increase the safety, reliability, and stability
- Mapping memory and permissions
- Memory fragmentation: external fragmentation and internal fragmentation

## chapter 08
**File Input and Output**

- Ways to open a file
- Reading and writing to a file
- File utilities : debugging, saving program states, handling user-specific data, interfacing with physical devices
- filesystem management
- POSIX block and character devices(physical devices)
- Modes for opening a file
- Reading from files by field, by bytes, and by line
- Writing to files by field and by bytes

## chapter 09
**Approach to allocators**

- C++ allocators template class
- Allocate memory for specific type: Allocators that are equal and are unequal
- Allocator equal: allocator that can allocate memory from one allocator and de-allocate memory from another
- An unequal allocator is usually an allocator that is stateful,meaning it stores a state within itself that prevents an allocator from de-allocating memory from another instance of the same allocator (because the state is different)
- Stateful and unequal allocator; Stateless and equal allocator(basic allocator)
- The properties and options of allocator
- Stateless, cache-aligned allocated
- Stateful, memory-pool allocated

## chapter 10
**Programming POSIX Sockets Using C++**

- POSIX sockets
- Leveraging C++ and RAII with sockets
- TCP(connection-based protocol) versus UDP(connectionless protocol)
- Socket APIs: socket(); recv(); send(); listen(); connect();
- Packets(JSON format) from the client to the server

## chapter 11
**Time Interfaces in Unix or Linux**

- the POSIX and C++ time interfaces
- the UNIX epoch and POSIX time.h APIs
- the C++ chrono APIs and the time interfaces
- read the system clock and output the results to the console on an interval
- how to benchmark software using the C++ high-resolution timer
- system clock and steady clock for more precise timing

## chapter 12
**Program POSIX and C++ Threads**

- POSIX threads
- C++ threads
- Using threading to perform a parallel computation
- Creating own high-resolution timer using threading in order to perform benchmarking
- Building debugging to provide support for multiple clients 
- basic understanding of threading
- thread synchronization
- the challenges associated with race conditions and deadlock

## chapter 13
**Error —— Handling with Exceptions**

- Perform error handling while system programming
- How to use POSIX-style error handling
- How to use the standard C-style set jump exceptions
- How to use C++ exceptions


## About Author

### Talk is cheap, show me the code.
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;——Linus Torvalds

### 掌中星辰转日月，手心苍穹天外天。
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;——云主宰苍穹

### Stay Hungry, Stay Foolish.
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;——Steve Jobs

--------------------------------------------------------------------------------

- Mail：2694048168@qq.com
- Weibo：云主宰苍穹
- GitHub: https://github.com/2694048168/
- Gitee：https://gitee.com/weili_yzzcq/

--------------------------------------------------------------------------------
