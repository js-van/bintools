/****************************    assem.h    ***********************************
* Author:        Agner Fog
* Date created:  2017-04-17
* Last modified: 2017-11-03
* Version:       1.00
* Project:       Binary tools for ForwardCom instruction set
* Module:        assem.h
* Description:
* Header file for assembler
*
* Copyright 2017 GNU General Public License http://www.gnu.org/licenses
*****************************************************************************/
#pragma once

// Define token types:
const int  TOK_EOF = 1;                // end of file
const int  TOK_NAM = 2;                // unidentified name
const int  TOK_LAB = 3;                // code label or function name
const int  TOK_VAR = 4;                // data label
const int  TOK_SEC = 5;                // section name
const int  TOK_INS = 6;                // instruction name
const int  TOK_OPR = 7;                // operator
const int  TOK_NUM = 8;                // integer number
const int  TOK_FLT = (TOK_NUM + 1);    // floating point number
const int  TOK_CHA = 0x0A;             // character or string in single quotes ' '
const int  TOK_STR = 0x0B;             // string in double quotes " "
const int  TOK_DIR = 0x11;             // section or function directive
const int  TOK_ATT = 0x12;             // attribute of sections, functions, or symbols. also some keywords
const int  TOK_TYP = 0x14;             // type identifier
const int  TOK_OPT = 0x15;             // options of instructions and operands
const int  TOK_REG = 0x16;             // register name
const int  TOK_SYM = 0x1A;             // symbol, constant, variable, function. id = symbol index
const int  TOK_XPR = 0x1B;             // expression. id = expression index
const int  TOK_HLL = 0x20;             // high level language block (if, for, etc.)
const int  TOK_ERR = 0x80;             // error. illegal character or unmatched quote

// Define keyword id's:

// Directives
const int DIR_SECTION  = ((TOK_DIR << 24) + 1);
const int DIR_FUNCTION = ((TOK_DIR << 24) + 2);
const int DIR_END      = ((TOK_DIR << 24) + 4);
const int DIR_PUBLIC   = ((TOK_DIR << 24) + 8);
const int DIR_EXTERN   = ((TOK_DIR << 24) + 0x10);

// Attributes of sections
const int ATT_READ     = ((TOK_ATT << 24) + SHF_READ);
const int ATT_WRITE    = ((TOK_ATT << 24) + SHF_WRITE);
const int ATT_EXEC     = ((TOK_ATT << 24) + SHF_EXEC);
const int ATT_ALIGN    = ((TOK_ATT << 24) + 0x10);
const int ATT_WEAK     = ((TOK_ATT << 24) + 0x20);

// Attributes of variables, constants and functions
const int ATT_CONSTANT = ((TOK_ATT << 24) + 0x10000);  // used for external constants
const int ATT_UNINIT   = ((TOK_ATT << 24) + 0x20000);  // uninitialized section (BSS)
const int ATT_COMDAT   = ((TOK_ATT << 24) + 0x40000);  // communal section. duplicates and unreferenced sections are removed

// Type definitions
const int TYP_INT8     = ((TOK_TYP << 24) + 0x10);
const int TYP_INT16    = ((TOK_TYP << 24) + 0x11);
const int TYP_INT32    = ((TOK_TYP << 24) + 0x12);
const int TYP_INT64    = ((TOK_TYP << 24) + 0x13);
const int TYP_INT128   = ((TOK_TYP << 24) + 0x14);
const int TYP_UNS                         = 0x20;   // add this for unsigned integer types
const int TYP_PLUS                       = 0x100;   // add this larger type allowed
const int TYP_FLOAT16  = ((TOK_TYP << 24) + 0x44);
const int TYP_FLOAT32  = ((TOK_TYP << 24) + 0x45);
const int TYP_FLOAT64  = ((TOK_TYP << 24) + 0x46);
const int TYP_FLOAT128 = ((TOK_TYP << 24) + 0x47);
const int TYP_INT      =                    0x10;    // generic test for int types
const int TYP_FLOAT    =                    0x40;    // generic test for float types
const int TYP_STRING   = ((TOK_TYP << 24) + 0x18);
// Options and attributes of instructions
const int OPT_MASK     = ((TOK_OPT << 24) + 1);
const int OPT_FALLBACK = ((TOK_OPT << 24) + 2);
const int OPT_LENGTH   = ((TOK_OPT << 24) + 3);
const int OPT_BROADCAST= ((TOK_OPT << 24) + 4);
const int OPT_LIMIT    = ((TOK_OPT << 24) + 5);
const int OPT_SCALAR   = ((TOK_OPT << 24) + 6);
const int OPT_OPTIONS  = ((TOK_OPT << 24) + 7);
// Registers
const int REG_R        = 0x20;                     // register name prefixes
const int REG_V        = 0x40;
const int REG_THREADP  = ((TOK_REG << 24) + 0x1C);
const int REG_DATAP    = ((TOK_REG << 24) + 0x1D);
const int REG_IP       = ((TOK_REG << 24) + 0x1E);
const int REG_SP       = ((TOK_REG << 24) + 0x1F + REG_R);
const int REG_SPEC     = 0x60;
const int REG_CAPAB    = 0x80;
const int REG_PERF     = 0xA0;
const int REG_SYS      = 0xC0;
// high level language directives
const int HLL_IF       = ((TOK_HLL << 24) + 1);
const int HLL_ELSE     = ((TOK_HLL << 24) + 2);
const int HLL_SWITCH   = ((TOK_HLL << 24) + 3);
const int HLL_CASE     = ((TOK_HLL << 24) + 4);
const int HLL_FOR      = ((TOK_HLL << 24) + 5);
const int HLL_IN       = ((TOK_HLL << 24) + 6);
const int HLL_NOCHECK  = ((TOK_HLL << 24) + 7);
const int HLL_WHILE    = ((TOK_HLL << 24) + 8);
const int HLL_DO       = ((TOK_HLL << 24) + 9);
const int HLL_BREAK    = ((TOK_HLL << 24) + 10);
const int HLL_CONTINUE = ((TOK_HLL << 24) + 11);
// push and pop may be replaced by macros later:
const int HLL_PUSH     = ((TOK_HLL << 24) + 12);
const int HLL_POP      = ((TOK_HLL << 24) + 13);

// line types
const int LINE_DATADEF =    1;                   // data definition
const int LINE_CODEDEF =    2;                   // code instruction
const int LINE_PUBLICDEF =  3;                   // public symbol definition
const int LINE_METADEF =    4;                   // assemble-time definitions and metaprogramming
const int LINE_FUNCTION= 0x11;                   // function definition
const int LINE_SECTION = 0x12;                   // section definition
const int LINE_ENDDIR  = 0x10;                   // function or section end
const int LINE_ERROR   = 0xFF;                   // error detected in this line

// Operator id's are equal to the ASCII code with these additions:
const int EQ = 0x100;                  // operator followed by equal sign, e.g. +=
const int D2 = 0x200;                  // operator repeated, e.g. <<
const int D3 = 0x400;                  // operator triple, e.g. >>>
const int OP_UNS = 0x1000;             // unsigned operation

// SExpression types in .etype
const int XPR_INT           = 0x01;    // contains integer value
const int XPR_INT2          = 0x02;    // contains a second integer constant in the upper half of value
const int XPR_FLT           = 0x04;    // contains floating point value
const int XPR_IMMEDIATE     = 0x07;    // contains immediate constant
const int XPR_STRING        = 0x08;    // contains string (u = string buffer entry, sym2 = length)
const int XPR_REG           = 0x10;    // contains register operand
const int XPR_OP            = 0x20;    // contains instruction or operator
const int XPR_OPTION        = 0x80;    // contains option keyword for memory operand
const int XPR_MEM          = 0x100;    // contains memory operand, or part of it
const int XPR_SYM1         = 0x200;    // contains symbol address
const int XPR_SYM2         = 0x400;    // contains reference symbol address
const int XPR_SYMSCALE     = 0x800;    // contains scale factor on (sym1-sym2)
const int XPR_REG1        = 0x1000;    // contains first register operand
const int XPR_REG2        = 0x2000;    // contains second register operand
const int XPR_REG3        = 0x4000;    // contains third register operand in value.u
const int XPR_BASE        = 0x8000;    // contains base register
const int XPR_INDEX      = 0x10000;    // contains index register and scale factor
const int XPR_OFFSET     = 0x20000;    // contains memory address offset
const int XPR_LIMIT      = 0x40000;    // contains limit for index
const int XPR_SCALAR     = 0x80000;    // contains scalar memory operand without broadcast
const int XPR_LENGTH    = 0x100000;    // contains vector length register
const int XPR_BROADC    = 0x200000;    // contains vector broadcast length register
const int XPR_MASK      = 0x400000;    // contains mask register
const int XPR_FALLBACK  = 0x800000;    // contains fallback register
const int XPR_OPTIONS  = 0x1000000;    // contains options or signbits in IM3
const int XPR_JUMPOS   = 0x2000000;    // contains self-relative jump offset
const int XPR_UNRESOLV =0x40000000;    // contains unresolved name or value
const int XPR_ERROR    =0x80000000;    // an error occurred during the generation

// Instruction id's (16 bits)
const int II_NOP            =  0x30000;
const int II_STORE          =        1;
const int II_MOVE           =        2;
const int II_COMPARE        =        7;
const int II_ADD            =        8;
const int II_SUB            =        9;
const int II_SUB_REV        =       10;
const int II_MUL            =       11;
const int II_MUL_HI         =       12;
const int II_MUL_EX         =       14;
const int II_DIV            =       16;
const int II_DIV_U          =       17;
const int II_DIV_REV        =       18;
const int II_DIV_EX         =  0x12018;
const int II_REM            =       20;
const int II_REM_U          =       21;
const int II_MIN            =       22;
const int II_MIN_U          =       23;
const int II_MAX            =       24;
const int II_MAX_U          =       25;
const int II_AND            =       28; // 0x1C
const int II_AND_NOT        =       29;
const int II_OR             =       30; // 0x1E
const int II_XOR            =       31; // 0x1F
const int II_SHIFT_LEFT     =       32;
const int II_MUL_2POW       =       32;
const int II_ROTATE         =       33;
const int II_SHIFT_RIGHT_S  =       34;
const int II_SHIFT_RIGHT_U  =       35;  // must be = II_SHIFT_RIGHT_S | 1
const int II_SET_BIT        =       36;
const int II_CLEAR_BIT      =       37;
const int II_TOGGLE_BIT     =       38;
const int II_AND_BIT        =       39; // 0x27
const int II_TEST_BIT       =       40; // 0x28
const int II_MUL_ADD        =       48;
const int II_MUL_ADD2       =       49;
const int II_ADD_ADD        =       50;
const int II_SHIFT_U_ADD    =   0x0101;
const int II_ADD_H          =  0x50008;  // float16
const int II_SUB_H          =  0x50009;
const int II_MUL_H          =  0x5000B;
const int II_DIV_H          =  0x50010;
const int II_MUL_ADD_H      =  0x50030;
const int II_REPLACE        =  0xA0001;
const int II_REPLACE_EVEN   =  0x26004;
const int II_REPLACE_ODD    =  0x26005;

const int II_INCREMENT      =   0x0051;  // increment. combine with II_JUMP_POSITIVE
const int II_SUB_MAXLEN     =   0x0052;  // sbutract max vector length. combine with II_JUMP_POSITIVE
const int II_JUMP           = 0x101000;  // jump codes may be combined with II_ADD etc.
const int II_JUMP_ZERO      = 0x101200;  // xor with 0x100 for opposite condition
const int II_JUMP_NOTZERO   = 0x101300;  // not zero or not equal
const int II_JUMP_POSITIVE  = 0x101400;  // positive or signed above
const int II_JUMP_NEGATIVE  = 0x101600;  // positive or signed below
const int II_JUMP_OVERFLOW  = 0x101800;  // signed overflow
const int II_JUMP_CARRY     = 0x102000;  // carry, borrow, unsigned below, abs below. Reverse condition if sub n replaced by add (-n)
const int II_JUMP_UABOVE    = 0x102200;  // unsigned above, abs above
const int II_JUMP_ALL1      = 0x102400;
const int II_JUMP_NFINITE   = 0x102600;
const int II_JUMP_INSTR     = 0x100000;  // bit to identify direct jump and call instructions
const int II_JUMP_INVERT    =   0x0100;  // flip this bit to invert condition

const int II_ALIGN          = 0x100000;  // align directive

const int MAX_ALIGN         =     4096;  // maximum allowed alignment  (note: if changed, change also in error.cpp at ERR_ALIGNMENT)

// Bit values generated by fitConstant() and stored in SCode::fitNumX
// Indicates how many bits are needed to contain address offset or immediate constant of an instruction
//const int IFIT_I4        =        1;  // fits into signed 4-bit integer
//const int IFIT_J4        =        2;  // (-x) fits into signed 4-bit integer
const int IFIT_U4        =        4;  // x fits into unsigned 4-bit integer
const int IFIT_I8        =     0x10;  // fits into signed 8-bit integer
const int IFIT_J8        =     0x20;  // (-x) fits into signed 8-bit integer
const int IFIT_U8        =     0x40;  // x fits into unsigned 8-bit integer
const int IFIT_I8SHIFT   =     0x80;  // fits into signed 8-bit integer with left shift
const int IFIT_I16       =    0x100;  // fits into signed 16-bit integer
const int IFIT_J16       =    0x200;  // (-x) fits into signed 16-bit integer
const int IFIT_U16       =    0x400;  // fits into unsigned 16-bit integer
const int IFIT_I16SHIFT  =    0x800;  // fits into signed 16-bit integer with left shift
const int IFIT_I16SH16   =   0x1000;  // fits into signed 16-bit integer shifted left by 16
const int IFIT_I24       =   0x4000;  // fits into signed 24-bit signed integer
const int IFIT_I32       =  0x10000;  // fits into signed 32-bit integer
const int IFIT_J32       =  0x20000;  // (-x) fits into signed 32-bit integer
const int IFIT_U32       =  0x40000;  // fits into unsigned 32-bit integer
const int IFIT_I32SHIFT  =  0x80000;  // fits into signed 32-bit integer with left shift
const int IFIT_I32SH32   = 0x100000;  // fits into 32-bit integer shifted left by 32
const int IFIT_J         =  (IFIT_J8 | IFIT_J16 | IFIT_J32); // (-x) fits better than x
const int FFIT_16       = 0x1000000;  // fits into normal half precision
const int FFIT_32       = 0x2000000;  // fits into normal single precision
const int FFIT_64       = 0x4000000;  // fits into double precision
const int IFIT_RELOC   = 0x10000000;  // relocation record needed
const int IFIT_LARGE   = 0x20000000;  // choose the larger size if uncertain. This input is used if optimization process has convergence problems


// struct SLine contains information about each line in the input file
struct SLine {
    uint16_t type;                // line type: LINE_DATADEF, etc
    uint16_t sectionType;         // LINE_DATADEF, LINE_CODEDEF
    uint32_t beginPos;            // position in input file
    uint32_t firstToken;          // index to first token
    uint32_t numTokens;           // number of tokens in line
    uint32_t file;                // file of origin. (1 = source file, 2+ = include files, 0x1000+ = meta-generated lines)
    uint32_t linenum;             // line number in file of origin
};

// struct SToken is used for splitting each line into tokens
struct SToken {
    uint32_t type;                // Token type
    uint32_t id;                  // ID if known name or operator
    uint32_t pos;                 // File offset
    uint32_t stringLength;        // Length of token as string
    uint16_t priority;            // Priority if operator
    uint16_t vartype;             // 0: value not known, 3: int64, 5: double, 8: string
    uint32_t unused;
    union {                       // value if constant or assemble-time variable
        uint64_t u;
        int64_t  i;
        double   d;
        uint32_t w;
    } value;
};

// struct SOperator is used for list of operators
struct SOperator {
    char name[8];                 // name
    uint32_t id;                  // identifier
    uint32_t priority;            // priority if operator
};

// operator < for sorting operator list
static inline bool operator < (SOperator const & a, SOperator const & b) {
    return strcmp(a.name, b.name) < 0;
}

// struct SKeyword is used for list of keywords
struct SKeyword {
    char name[28];                // name
    uint32_t id;                  // identifier
};

// struct SExpression is used during assemble-time evaluation of expressions containing
// any type of operands: integer, float, string, registers, memory operands, options
struct SExpression {
    union {                       // immediate value or addend to memory address
        int64_t  i;               // as signed
        uint64_t u;               // as unsigned
        double   d;               // as double
        uint32_t w;               // as unsigned 32 bit integer
    } value;
    int64_t  offset;              // offset for memory operand or jump
    uint32_t etype;               // flags for elements in expression: XPR_...
    uint32_t tokens;              // number of tokens used
    uint32_t sym1;                // first symbol, indexed by namebuffer offset
    uint32_t sym2;                // reference symbol, indexed by namebuffer offset
    uint32_t instruction;         // instruction corresponding to operator
    uint8_t  optionbits;          // option bits or sign bits
    uint8_t  base;                // base register of memory operand    
    uint8_t  index;               // index register of memory operand
    uint8_t  length;              // length or broadcast register of memory operand
    int8_t   scale;               // scale factor for index register
    uint8_t  symscale;            // scale factor for sym1-sym2    
    uint8_t  mask;                // mask register
    uint8_t  reg1;                // first register operand
    uint8_t  reg2;                // second register operand
    uint8_t  reg3;                // third register operand   
    uint8_t  fallback;            // fallback register
    uint8_t  unused1;             // alignment filler or future extension
};


// struct SCode is the result of interpreting a line of code containing an instruction
struct SCode : public SExpression {
    SFormat  const * formatp;     // instruction format. pointer to record in formatList in disassem1.cpp, or a copy of it
    uint32_t line;                // entry into lines buffer
    uint32_t section;             // code section
    uint32_t address;             // address relative to begin of section in current module
    uint32_t label;               // a code or data label, identified by an index into symbolNameBuffer (not an index into 'symbols' because this may change when new symbols are added)
    uint32_t dtype;               // data type. (TYP_INT8 etc.)
    uint32_t instr1;              // index to instruction in instructionlist
    uint32_t fitNum;              // indicates if immediate constant fits a certain representation (from fitInteger or fitFloat function)
    uint32_t fitAddr;             // indicates if relative address or jump offsets fits a certain number of bits
    uint8_t  dest;                // destination register (2 = memory destination)
    uint8_t  numOp;               // number of source operands
    uint8_t  size;                // size of instruction (0 = tiny). minimum size if actual size depends on unresolved cross references
    uint8_t  sizeUnknown;         // actual size may be up to this value bigger
    uint8_t  category;            // instruction category
};


// struct SBlock is used for tracking {} code blocks
struct SBlock  {
    uint32_t blockType;           // block type. see definitions of HL_FUNC etc. in assem5.cpp
    uint32_t blockNumber;         // sequential number used in label names
    uint32_t startBracket;        // token of start '{'
    uint32_t jumpLabel;           // target label for jump, else, or loop
    uint32_t breakLabel;          // target label for break statement. -1 if break is possible but label not yet defined
    uint32_t continueLabel;       // target label for continue statement. -1 if continue is possible but label not yet defined
    uint32_t codeBuffer2index;    // index of entry in codeBuffer2
    uint32_t codeBuffer2num;      // number of instruction codes in codeBuffer2
};

// combine contents of two expressions
static inline SExpression operator | (SExpression const & exp1, SExpression const & exp2) {
    SExpression expr;
    for (uint32_t i = 0; i < sizeof(SExpression) / sizeof(uint64_t); i++) {
        (&expr.value.u)[i] = (&exp1.value.u)[i] | (&exp2.value.u)[i];
    }
    return expr;
}

static inline SCode operator | (SCode const & code1, SExpression const & exp2) {
    SCode code0 = code1;
    for (uint32_t i = 0; i < sizeof(SExpression) / sizeof(uint64_t); i++) {
        (&code0.value.u)[i] = (&code1.value.u)[i] | (&exp2.value.u)[i];
    }
    return code0;
}

// find the smallest representation that the floating point operand fits into
int fitFloat(double x);

// insert memory operand into code structure
void insertMem(SCode & code, SExpression & expr);

// insert everything from expression to code structure, OR'ing all bits
void insertAll(SCode & code, SExpression & expr);

// operator < for sorting keyword list
static inline bool operator < (SKeyword const & a, SKeyword const & b) {
    // case insensitive compare
#if defined (_MSC_VER)
    return _stricmp(a.name, b.name) < 0;    // microsoft
#else
    return strcasecmp(a.name, b.name) < 0;  // unix
#endif
    
}

// redefine symbol structure sorted by name
struct ElfFWC_Sym2 : public ElfFWC_Sym {
};

// Buffer for symbol names during assembly
// symbolNameBuffer is made global in order to make it accessible to bool operator < (ElfFWC_Sym2 const &, ElfFWC_Sym2 const &)
// It is defined in assem1.cpp
extern CTextFileBuffer symbolNameBuffer;      // Buffer for symbol names 


static inline bool operator < (ElfFWC_Sym2 const & a, ElfFWC_Sym2 const & b) {
    return strcmp((char*)symbolNameBuffer.buf()+a.st_name, (char*)symbolNameBuffer.buf()+b.st_name) < 0;
}

static inline bool operator == (ElfFWC_Sym2 const & a, ElfFWC_Sym2 const & b) {
    return strcmp((char*)symbolNameBuffer.buf()+a.st_name, (char*)symbolNameBuffer.buf()+b.st_name) == 0;
}

// structure in list of assembly errors
struct SAssemError {
    uint32_t pos;                                // position in input file
    uint32_t stringLength;                       // length of token string
    uint32_t file;                               // File where error was detected
    uint16_t num;                                // Error id
    uint16_t pass;                               // Pass during which error occurred
};

class CAssembler;                                // Forward definition

// class for reporting errors in assembly file
class CAssemErrors {
public:
    CAssemErrors();
    void report(uint32_t position, uint32_t stringLength, uint32_t num); // Report an error
    void report(SToken const & token);           // Report an error, pointing to a specific token
    void reportLine(uint32_t num);               // Report an error in current line
    void setOwner(CAssembler * a);               // Give access to CAssembler
    uint32_t numErrors();                        // Return number of errors
    bool tooMany();                              // true if too many errors
    void outputErrors();                         // Write all errors to stderr
protected:
    CAssembler * owner;
    CDynamicArray<SAssemError>list;              // List of errors
    uint32_t maxErrors;                          // Maximum number of errors to report
};


// class CDisassembler handles disassembly of ForwardCom ELF file
class CAssembler : public CFileBuffer {
public:
    CAssembler();                                // Constructor
    void go();
protected:
    friend class CAssemErrors;                   // This class handles error messages
    uint32_t iInstr;                             // Position of current instruction relative to section start
    uint32_t instrLength;                        // Length of current instruction, in 32-bit words
    uint32_t operandType;                        // Operand type of current instruction
    uint32_t format;                             // Format of current instruction
    uint64_t variant;                            // Template variant and options
    int64_t  value0;                             // original value of immediate operand   
    uint32_t tokenB;                             // index to first token in current line
    uint32_t tokenN;                             // number of tokens in current line
    uint32_t section;                            // Current section
    uint32_t sectionFlags;                       // current section information flags
    uint32_t linei;                              // index to current line
    uint32_t filei;                              // index to current input file
    uint32_t pass;                               // what pass are we in
    uint32_t iLoop;                              // index of current loop statement
    uint32_t iIf;                                // index of current 'if' statement
    uint32_t iSwitch;                            // index of current 'switch' statement    
    uint32_t numSwitch;                          // total number of 'switch' statements
    bool     lineError;                          // error in current line. stop interpreting
    STemplate const * pInstr;                    // Pointer to current instruction code
    SInstruction2 const * iRecord;               // Pointer to instruction table entry
    SFormat const * fInstr;                      // Format details of current instruction code
    CELF outFile;                                // Output file
    CDynamicArray<SToken> tokens;                // List of tokens
    CDynamicArray<SLine> lines;                  // Information about each line of the input file
    CDynamicArray<SInstruction> instructionlist; // List of instruction set, sorted by name
    CDynamicArray<SInstruction3> instructionlistId; // List of instruction set, sorted by id
    CDynamicArray<SOperator> operators;          // List of operators
    CDynamicArray<SKeyword> keywords;            // List of keywords
    CDynamicArray<ElfFWC_Sym2> symbols;          // List of symbols
    CDynamicArray<ElfFWC_Rela2> relocations;     // List of relocations
    CDynamicArray<uint8_t> brackets;             // Stack of nested brackets during evaluation of expression
    CDynamicArray<SCode> codeBuffer;             // Coded instructions
    CDynamicArray<SCode> codeBuffer2;            // Temporary storage of instructions for loops and switch statements
    CDynamicArray<Elf64_Shdr> sectionHeaders;    // Section headers
    CDynamicArray<SFormat> formatList3;          // Subset of formatList for multiformat instruction formats
    CDynamicArray<SFormat> formatList4;          // Subset of formatList for jump instruction formats
    CDynamicArray<SBlock>  hllBlocks;            // Tracking of {} blocks    
    CDynamicArray<SExpression> expressions;      // Expressions saved as assemble-time symbols    
    CTextFileBuffer stringBuffer;                // Buffer for assemble-time string variables
    CMetaBuffer<CMemoryBuffer> dataBuffers;      // databuffer for each section
    CAssemErrors errors;                         // Error reporting
    void initializeWordLists();                  // Initialize and sort instruction list, operator list, and keyword list
    void pass1();                                // Split input file into lines and tokens. Handle preprocessing directives. Find symbol definitions
    void interpretSectionDirective();            // Interpret section directive during pass 2 or 3
    void interpretFunctionDirective();           // Interpret function directive during pass 2 or 3
    void interpretEndDirective();                // Interpret section or function end directive during pass 2 or 3
    uint32_t addSymbol(ElfFWC_Sym2 & sym);       // Add a symbol to symbols list
    uint32_t findSymbol(uint32_t name);          // Find symbol by index into symbolNameBuffer
    uint32_t findSymbol(const char * name, uint32_t len); // Find symbol by name with specified length
    void pass2();                                // A. Handle metaprogramming directives
                                                 // B. Classify lines
                                                 // C. Identify symbol names, sections, labels, functions 

    void interpretExternDirective();             // Interpret extern directive during pass 2
    void interpretPublicDirective();             // Interpret public directive during pass 2
    void interpretLabel(uint32_t tok);           // Interpret code or data label during pass 2
    void interpretVariableDefinition1();         // interpret assembly style variable definition
    void interpretVariableDefinition2();         // interpret C style variable definition
    void determineLineType();                    // check if line is code or data
    void interpretAlign();                       // interpret code or data alignment directive
    void interpretMetaDefinition();              // Interpret line beginning with '%' containing meta code
    void replaceKnownNames();                    // Replace known symbol names with symbol references and meta variables with their value
    SExpression expression(uint32_t tok1, uint32_t ntok, uint32_t option); // Interpret and evaluate expression
    SExpression symbol2expression(uint32_t symi); // make expression out of symbol
    SExpression op1minus(SExpression & exp1);    // Interpret -(A+B), etc.
    SExpression op2(uint32_t op, SExpression & exp1, SExpression & exp2); // Interpret dyadic expression with any type of operands
    SExpression op2Int(uint32_t op, SExpression const & exp1, SExpression const & exp2); // Interpret dyadic expression with integer operands
    SExpression op2Float(uint32_t op, SExpression & exp1, SExpression & exp2); // Interpret dyadic expression with floating point operands
    SExpression op2String(uint32_t op, SExpression const & exp1, SExpression const & exp2); // Interpret dyadic expression with string operands
    SExpression op2Registers(uint32_t op, SExpression const & exp1, SExpression const & exp2); // Interpret dyadic expression with register operands
    SExpression op2Memory(uint32_t op, SExpression & exp1, SExpression & exp2); // Interpret dyadic expression with memory operands
    SExpression op3(uint32_t tok1, uint32_t toklow, uint32_t tokcolon, uint32_t maxtok, uint32_t options); // Interpreted triadic expression exp1 ? exp2 : exp3 at the indicated positions
    void assignMetaVariable(uint32_t symi, SExpression & expr, uint32_t typetoken); // define or modify assemble-time constant or variable
    void pass3();                                // Generate code and data
    void makeFormatLists();                      // extract subsets of formatList into formatList3 and formatList4
    void interpretCodeLine();                    // Interpret a line defining code
    int  fitCode(SCode & code);                  // find an instruction variant that fits the code
    bool instructionFits(SCode const & code, SCode & codeTemp, uint32_t ii); // check if instruction fits into specified format
    bool jumpInstructionFits(SCode const & code, SCode & codeTemp, uint32_t ii); // check if jump instruction fits into specified format
    int  fitConstant(SCode & code);              // check how many bits are needed to contain immediate constant in an instruction.
    int  fitAddress(SCode & code);               // check how many bits are needed to contain relative address in an instruction.
    void checkCode1(SCode & code);               // eheck code for correctness before fitting a format, and fix some code details
    void checkCode2(SCode & code);               // eheck register types etc. after fitting a format, and finish code details
    uint32_t checkCodeE(SCode & code);           // find reason why no format fits, and return error number
    void optimizeCode(SCode & code);             // optimize instruction. replace by more efficient instruction if possible
    void pass4();                                // Resolve symbol addresses and cross references, optimize forward references
    void pass5();                                // Make binary file
    void removePrivateSymbols();                 // remove local symbols and adjust relocation records with new symbol indexes
    void makeListFile();                         // make output listing
    int64_t calculateMemoryOffset(SCode & code);    // calculate memory address possibly involving symbol. generate relocation if necessary
    int64_t calculateConstantOperand(SExpression & expr, uint64_t address, uint32_t fieldSize); // calculate constant or immediate operand possibly involving symbol. generate relocation if necessary
    void makeBinaryCode();                       // make binary data for code sections
    void makeBinaryData();                       // make binary data for data sections
    void makeBinaryRelocations();                // put relocation records in output file
    void showTokens();                           // Show all tokens. For debugging only
    void showSymbols();                          // Show all symbols. For debugging only
    void interpretHighLevelStatement();          // if, else, switch, for, do, while statements    
    void interpretEndBracket();                  // finish {} block
    void codeIf();                               // Interpret if statement in assembly code
    void codeIf2();                              // Finish if statement at end bracket
    void codeWhile();                            // Interpret while loop in assembly code
    void codeWhile2();                           // Finish while-loop at end bracket
    void codeDo();                               // Interpret do-while loop in assembly code
    void codeDo2();                              // Finish do-while loop at end bracket
    void codeFor();                              // Interpret for-loop in assembly code
    void codeFor2();                             // Finish for-loop at end bracket
    void codeForIn();                            // Interpret for-in vector loop in assembly code
    void codeForIn2();                           // Finish for-in vector loop in assembly code
    void codeSwitch();                           // Interpret switch statement in assembly code
    void codeCase();                             // Interpret switch case label in assembly code
    void codeSwitch2();                          // Finish switch statement at end bracket
    void codeBreak();                            // Interpret break or continue statement in assembly code
    uint32_t findBreakTarget(uint32_t k);        // Find or make the target symbol of a break or continue statement
    uint32_t makeLabelSymbol(const char * name); // Make a symbol for branch label etc., address not known yet
    bool mergeJump(SCode & code2);               // Merge jump instruction with preceding arithmetic instruction
    uint32_t hasJump(uint32_t line);             // check if line contains unconditional direct jump
    void interpretCondition(SCode & code);       // interpret condition in if(), while(), and for(;;) statements
    void codePush();                             // push register on stack. (may be replaced by macros later)
    void codePop();                              // pop register from stack. (may be replaced by macros later)

};
