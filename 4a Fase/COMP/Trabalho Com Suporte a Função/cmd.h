#ifndef _CMD_N_DEF_
#define _CMD_N_DEF_

#include "eda.h"

#define MAX_COMMAND 10000
#define MAX_FUNCS 1000

typedef struct {
  int label;
  int command;
  int arg1;
  int arg2;
} CMD;

typedef struct {
  char* name;
  TIPO retType;
  int args;
  TIPO* argsType;
} FUNC;

// Commands               #Bin ID   #Arg1   #Arg2
#define CMD_ISTORE        0x0000 // Posi    --
#define CMD_BIPUSH        0x0001 // Number  --
#define CMD_IADD          0x0002 // --      --
#define CMD_IMULL         0x0003 // --      --
#define CMD_ILOAD         0x0004 // Posi    --
#define CMD_ICONST_1      0x0005 // --      --
#define CMD_ICONST_2      0x0006 // --      --
#define CMD_ICONST_3      0x0007 // --      --
#define CMD_ICONST_4      0x0008 // --      --
#define CMD_ICONST_5      0x0009 // --      --
#define CMD_IDIV          0x000A // --      --
#define CMD_INEG          0x000B // --      --
#define CMD_IREM          0x000C // --      --
#define CMD_ISHL          0x000D // --      --
#define CMD_ISHR          0x000E // --      --
#define CMD_ISUB          0x000F // --      --
#define CMD_GSOUT         0x0010 // --      -- -> getstatic java/lang/System/out Ljava/io/PrintStream;
#define CMD_INVKOUTI      0x0011 // --      -- -> invokevirtual java/io/PrintStream/println(I)V
#define CMD_INVKOUTL      0x0012 // --      -- -> invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
#define CMD_LDC           0x0013 // "str"   -- -> impilha o ponteiro para a string
#define CMD_LDCN          0x0014 // n       -- -> Empilha uma constante maior
#define CMD_IF_ICOMPEQ    0x0015 // Label   --
#define CMD_IF_ICOMPNE    0x0016 // Label   --
#define CMD_IF_ICOMPLT    0x0017 // Label   --
#define CMD_IF_ICOMPLE    0x0018 // Label   --
#define CMD_IF_ICOMPGT    0x0019 // Label   --
#define CMD_IF_ICOMPGE    0x001A // Label   --
#define CMD_GOTO          0x001B // Label   --
#define CMD_GETSTATICIN   0x001C // --      -- -> getstatic java/lang/System/in Ljava/io/InputStream;
#define CMD_READ          0x001D // --      -- -> invokevirtual java/io/InputStream/read()I \n istore id
#define CMD_ENDWHILE      0x001E // --      --
#define CMD_IRETURN        0x001F // --     --
#define CMD_INVOKESTATIC   0x0020 // id     --
#define CMD_INVOKESQRT     0x0021 // --     -- invokevirtual java/lang/Math/sqrt(D)D
#define CMD_I2D            0x0022 // --     --
#define CMD_D2I            0x0023 // --     --

void showCmd();
void ShowCmdAscii();

void showLiteralTable();

void cmdGenerate(int, int, int);

// Lista de Comandos para tratar Label

int LabelCreate();
void LabelUpdate(struct IntList* lista, int label);
int GetIndexPosition();

// Lista de Comandos em Pilha para a JVM
void CmdSqrt();
void CmdI2d();
void CmdD2i();

void CmdIstore (struct arvore* arv, char* var);
void CmdIadd ();
void CmdImull ();
void CmdBipush (int value);
void CmdIload (struct arvore* arv, char* var);
void CmdIdiv ();
void CmdIneg ();
void CmdIrem ();
void CmdIshl ();
void CmdIshr ();
void CmdIsub ();
void CmdGetStaticOut ();
void CmdInvokeOutInt ();
void CmdInvokeOutLiteral ();
void CmdIreturn();
void CmdInvokeStatic(int index);
void CmdInvokeFunction(char* name);

void CmdReadInt();

void CmdLdc (char*);
void CmdLdcn (int);

void CmdIfEQ();
void CmdIfNE();
void CmdIfLT();
void CmdIfLE();
void CmdIfGT();
void CmdIfGE();

void CmdGOTO();
void CmdGOTOLabel(int);

void CmdEndWhile();

// Operações de chamada do Bytecode
void loadToMain();

// Operações do Assembler
void writeCmds();
void writeJasminInit(char* file);
void writeJasminBody();
void writeJasminMain();
void writeJasminFunc(TIPO ret, char* funcName, char* param);
void clearJasmin();
void writeJasminExit();

void callJasmin();
void rmJasminOut();

// Functions
void createFunction(struct arvore* arv, char* name, TIPO retType, int size,TIPO *argTypes);
void showFunctionTable();

TIPO* criaListaTipo(TIPO initial);
void adicionaTipo(TIPO* lista , TIPO valor);
TIPO* criaListatipoVoid();
TIPO* addListaTipo(TIPO* valor1, TIPO* valor2);
TIPO* createListaTipoIntNVezes(int);
#endif
