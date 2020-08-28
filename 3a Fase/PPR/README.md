# Projetos de Programas

###Trabalho Final para a disciplina de Projetos de Programas

###Assunto: Implementação de um Sistema de adoção de cachorros necessitados
	Gostaríamos de criar um sistema para cadastrar e fazer o processo de adoção de cachorros recuperados das ruas

No sistema deve ser possível:
    • Cadastrar novos cachorros recolhidos e devidamente vacinados.
    • Fazer login e senha com um único perfil de usuário já cadastrado
    • Fazer a distinção entre animais apenas recolhidos e animais devidamente prontos para adoção.
    • Fazer o processo de adoção de cachorros, nele o usuário do sistema irá inserir algumas informações básicas sobre a pessoa que irá adotar o animal.
    • Listar todos os cachorros que necessitam serem adotados.
    • Listar todos os cachorros já adotados.
    • Listar o nome de todos os novos donos dos cães já adotados, bem como já listando o animal que adotaram.

Os animais prontamente recolhidos serão cadastrados no sistema para ter um levantamento e diagnóstico dos veterinários sobre o animal. Quando o cachorro estiver devidamente tratado (caso necessário cuidados médicos após o resgate do animal), o status do animal será alterado para “pronto para adoção!”. Na hora da adoção (em feiras a serem realizadas pelos usuários do sistema) o futuro dono assinará um termo (por escrito a ser levado pelos usuários do sistema) de comprometimento de bem tratar o animal a ser adotado. Só então o processo de adoção será cadastrado no sistema, onde o status do animal será alterado para “adotado!”, junto com os dados da pessoa que o adotou.
	A ficha do sistema contendo os dados da pessoa a adotar o animal permanecerá em branco até que o cachorro seja adotado.

###Levantamento de Requisitos

Funcionais:
    • O sistema deve permitir o usuário de cadastrar novos cachorros recolhidos (Nome [se houver], Sexo, Raça, Porte [indefinido, pequeno, médio, grande] , Idade [se houver], status [em tratamento, pronto para adoção e adotado] , descrição e observações e notas do veterinário).
    • O sistema deve permitir ao usuário alterar o cadastro de alguns campos de um animal já cadastrado, como porte, status e campos de observações.
    • O sistema deve permitir ao usuário fazer o processo de adoção, assim preenchendo o campo vazio de dono do animal, com informações de nome do dono, endereço, CPF e telefone para contato.
    • O sistema deve permitir ao usuário listar todos os animais que estão com status indicando “pronto para ser adotado!”.
    • O sistema deve permitir ao usuário listar todos os animais que estão com status indicando “adotado”, bem como após isso listar as informações do novo dono.
    • O sistema deve permitir ao usuário excluir o registro de um animal.
Não funcionais:
    • O sistema poderá ser executado tanto em Windows quanto em Linux.
Normativos:
    • O campo de “informações do dono” deve permanecer em branco até o momento da adoção.
    • Apenas animais com status “pronto para adoção!” podem ser adotados.
    • As observações e notas do veterinário devem ser mantidas no cadastro do animal, e mostradas para o novo dono na hora da adoção.
    • Os participantes da instituição que usarem o sistema terão apenas um usuário e senha, que serão compartilhados entre todos os pertencentes a ONG.
    • A senha do usuario deve ser composta de pelo menos 8 dígitos, sendo pelo menos um desses um número.
