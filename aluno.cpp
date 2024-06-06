#include <stdio.h>
#include "library.h"

#define MAX_ALUNOS 100
#define DADOS_ALUNOS "dados/alunos/aluno_%03d.txt"

int genIdAluno(Aluno *alunos, int contador_estudante) {
    int max = -1;

    for (int i = 0; i < contador_estudante; ++i) {
        if (alunos[i].id > max) {
            max = alunos[i].id;
        }
    }

    return max + 1;
}

void excluiArquivosAlunosInexistentes(Aluno *alunos, int contador_estudante) {
    char filename[MAX_NOME];

    for (int id = 1; id <= MAX_ALUNOS; id++) {
        if (!alunoExisteEm(alunos, contador_estudante, id)) {
            sprintf(filename, DADOS_ALUNOS, id);
            remove(filename);
        }
    }
}

int alunoExisteEm(Aluno *alunos, int contador_estudante, int id) {
    for (int i = 0; i < contador_estudante; ++i) {
        if (alunos[i].id == id) {
            return 1;
        }
    }

    return 0;
}

void addAluno(Aluno *alunos, int *contador_estudante) {
    if (*contador_estudante >= MAX_ALUNOS) {
        printf("Número máximo de alunos alcançado.\n");
        return;
    }

    alunos[*contador_estudante].id = genIdAluno(alunos, *contador_estudante); 
    
    printf("Insira o nome do aluno: ");
    scanf(" %[^\n]", alunos[*contador_estudante].nome);

   
    int idadeValida = 0;
    while (!idadeValida) {
        printf("Insira a idade do aluno: ");
        scanf("%d", &alunos[*contador_estudante].idade);
        if (alunos[*contador_estudante].idade >= 0 && alunos[*contador_estudante].idade <= 120) {
            idadeValida = 1;
        } else {
            printf("Idade inválida. Por favor, insira uma idade entre 0 e 120 anos.\n");
        }
    }

    printf("Insira o instrumento musical do aluno: ");
    scanf(" %[^\n]", alunos[*contador_estudante].instrumento_musical);
    alunos[*contador_estudante].contador_aulas = 0;
    (*contador_estudante)++;
}


void listarAlunos(Aluno *alunos, int contador_estudante) {
    for (int i = 0; i < contador_estudante; i++) {
        printf("ID: %d, nome: %s, idade: %d, instrumento musical: %s, aulas: %d\n",
               alunos[i].id, alunos[i].nome, alunos[i].idade, alunos[i].instrumento_musical, alunos[i].contador_aulas);
    }
}

void editarAluno(Aluno *alunos, int contador_estudante) {
    for (int i = 0; i < contador_estudante; i++) {
        printf("-------------------------------\n");
        printf("Id - %d \n", alunos[i].id);
        printf("Nome: %s \n", alunos[i].nome);
        printf("Idade: %d \n", alunos[i].idade);
        printf("Instrumento musical: %s \n", alunos[i].instrumento_musical);
        printf("-------------------------------\n");
    }
    int id;
    printf("Insira o ID do aluno a editar: ");
    scanf("%d", &id);
    for (int i = 0; i < contador_estudante; i++) {
        if (alunos[i].id == id) {
            printf("Editar nome (atual: %s): ", alunos[i].nome);
            scanf(" %[^\n]", alunos[i].nome);

            
            int idadeValida = 0;
            while (!idadeValida) {
                printf("Editar idade (atual: %d): ", alunos[i].idade);
                scanf("%d", &alunos[i].idade);
                if (alunos[i].idade >= 0 && alunos[i].idade <= 120) {
                    idadeValida = 1;
                } else {
                    printf("Idade inválida. Por favor, insira uma idade entre 0 e 120 anos.\n");
                }
            }

            printf("Editar instrumento musical (atual: %s): ", alunos[i].instrumento_musical);
            scanf(" %[^\n]", alunos[i].instrumento_musical);
            return;
        }
    }
    printf("Aluno não encontrado.\n");
}

void excluirAluno(Aluno *alunos, int *contador_estudante, Aula *aulas, int contador_aulas) {
    for (int i = 0; i < *contador_estudante; i++) {
        printf("-------------------------------\n");
        printf("Id - %d \n", alunos[i].id);
        printf("Nome: %s \n", alunos[i].nome);
        printf("Idade: %d \n", alunos[i].idade);
        printf("Instrumento musical: %s \n", alunos[i].instrumento_musical);
        printf("-------------------------------\n");
    }
    int id;
    printf("Insira o ID do aluno a excluir: ");
    scanf("%d", &id);
    for (int i = 0; i < *contador_estudante; i++) {
        if (alunos[i].id == id) {
            for (int j = i; j < *contador_estudante - 1; j++) {
                alunos[j] = alunos[j + 1];
            }
            (*contador_estudante)--;

            for (int j = 0; j < contador_aulas; j++) {
                for (int k = 0; k < aulas[j].contador_alunos; k++) {
                    if (aulas[j].id_aluno[k] == id) {
                        for (int l = k; l < aulas[j].contador_alunos - 1; l++) {
                            aulas[j].id_aluno[l] = aulas[j].id_aluno[l + 1];
                        }
                        aulas[j].contador_alunos--;
                    }
                }
            }

            for (int j = 0; j < contador_aulas; j++) {
                for (int k = 0; k < aulas[j].contador_alunos; k++) {
                    if (aulas[j].id_aluno[k] > id) {
                        aulas[j].id_aluno[k]--;
                    }
                }
            }
            return;
        }
    }
    printf("Aluno não encontrado.\n");
}

void adicionarAlunoAula(Aula *aulas, int contador_aulas, Aluno *alunos, int contador_estudante) {
    for (int i = 0; i < contador_aulas; i++) {
        char nome_professor[MAX_NOME] = "Desconhecido";
        printf("-------------------------------\n");
        printf("Id - %d \n", aulas[i].id);
        printf("Nome: %s \n", aulas[i].nome);
        printf("Horario: %s \n", aulas[i].horario);
        printf("Professor Id: %d \n", aulas[i].Professor_id);
        printf("-------------------------------\n");
    }
    int id_aula, id_aluno;
    printf("Insira o ID da aula: ");
    scanf("%d", &id_aula);
    for (int i = 0; i < contador_estudante; i++) {
        printf("-------------------------------\n");
        printf("Id - %d \n", alunos[i].id);
        printf("Nome: %s \n", alunos[i].nome);
        printf("Idade: %d \n", alunos[i].idade);
        printf("Instrumento musical: %s \n", alunos[i].instrumento_musical);
        printf("-------------------------------\n");
    }
    printf("Insira o ID do aluno: ");
    scanf("%d", &id_aluno);

    for (int i = 0; i < contador_aulas; i++) {
        if (aulas[i].id == id_aula) {
            if (aulas[i].contador_alunos >= MAX_ALUNOS) {
                printf("Número máximo de alunos nesta aula alcançado.\n");
                return;
            }
            for (int j = 0; j < contador_estudante; j++) {
                if (alunos[j].id == id_aluno) {
                    aulas[i].id_aluno[aulas[i].contador_alunos] = id_aluno;
                    aulas[i].contador_alunos++;
                    alunos[j].contador_aulas++;
                    return;
                }
            }
        }
    }
    printf("ID da aula ou aluno não encontrado.\n");
}

void listarAulasAlunos(Aula *aulas, int contador_aulas, Aluno *alunos, int contador_estudante) {
    for (int i = 0; i < contador_estudante; i++) {
        printf("-------------------------------\n");
        printf("Id - %d \n", alunos[i].id);
        printf("Nome: %s \n", alunos[i].nome);
        printf("Idade: %d \n", alunos[i].idade);
        printf("Instrumento musical: %s \n", alunos[i].instrumento_musical);
        printf("-------------------------------\n");
    }
    int id_aluno;
    printf("Insira o ID do aluno para listar suas aulas: ");
    scanf("%d", &id_aluno);

    
    int encontrado = 0;
    for (int i = 0; i < contador_estudante; i++) {
        if (alunos[i].id == id_aluno) {
            encontrado = 1;
            printf("Aulas do aluno %s (ID: %d):\n", alunos[i].nome, alunos[i].id);
            for (int j = 0; j < contador_aulas; j++) {
                for (int k = 0; k < aulas[j].contador_alunos; k++) {
                    if (aulas[j].id_aluno[k] == id_aluno) {
                        printf("ID da aula: %d\n", aulas[j].id);
                        printf("Nome da aula: %s\n", aulas[j].nome);
                        printf("Horário: %s\n", aulas[j].horario);
                        break;
                    }
                }
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Aluno não encontrado.\n");
    }
}