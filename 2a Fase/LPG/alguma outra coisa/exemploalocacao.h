#ifndef AGENDA
#define AGENDA

#define TAM_NOME 80
#define TAM_COMPLEMENTO 80
#define TAM_ENDERECO 80
#define TAM_TELEFONE 20

typedef struct {
	int dia;
	int mes;
	int ano;
} Nascimento;

typedef struct {
	char *endereco;
	char *complemento;
	char uf[2];
} Endereco;

typedef struct {
	char *nome;
	char *telefone;
	Nascimento nasc;
	Endereco *end;
} Contato;

typedef struct {
	Contato **contatos;
	int elementos;
} Agenda;

Agenda *inicializa_agenda (void);
void inserir_contato(Agenda *a);
void libera_agenda(Agenda *a);

Contato *novo_contato(void);
void libera_contato(Contato *c);
Endereco *novo_endereco(void);
void libera_endereco(Endereco *end);

void lista_pessoas(Agenda *a);

#endif
