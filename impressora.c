#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

FILE *arquivo;
char *nomearq = "impressora.dat";

struct impressora
{
    int id;
    char modelo[100];
    char marca[80];
    int capacidade;
    char pais[50];
    float peso;
    char tipo;
    float preco;
    int ano;
};

int IdExistente(int id)
{
    struct impressora imp;
    fseek(arquivo, 0, SEEK_SET);

    while (fread(&imp, sizeof(struct impressora), 1, arquivo))
    {
        if (imp.id == id)
        {
            return 1;
        }
    }
    return 0;
}

void MostraRegistro()
{
    int reg;
    struct impressora item;

    printf("Digite o número do registro: ");
    scanf("%d", &reg);

    fseek(arquivo, reg * sizeof(struct impressora), SEEK_SET);
    fread(&item, sizeof(struct impressora), 1, arquivo);

    if (feof(arquivo))
    {
        printf("Registro não existente!\n");
        return;
    }

    printf("\nID: %d\n", item.id);
    printf("Modelo: %s\n", item.modelo);
    printf("Marca: %s\n", item.marca);
    printf("Capacidade: %d\n", item.capacidade);
    printf("País de Origem: %s\n", item.pais);
    printf("Peso: %.2f\n", item.peso);
    printf("Tipo: %c\n", item.tipo);
    printf("Preço: %.2f\n", item.preco);
    printf("Ano de fabricação: %d\n", item.ano);
}

void MostraTodos()
{
    int reg = 0;
    struct impressora item;

    fseek(arquivo, 0, SEEK_SET);

    while (fread(&item, sizeof(struct impressora), 1, arquivo))
    {
        printf("\nRegistro número: %d\n", reg);
        printf("ID: %d\n", item.id);
        printf("Modelo: %s\n", item.modelo);
        printf("Marca: %s\n", item.marca);
        printf("Capacidade: %d\n", item.capacidade);
        printf("País de Origem: %s\n", item.pais);
        printf("Peso: %.2f\n", item.peso);
        printf("Tipo: %c\n", item.tipo);
        printf("Preço: %.2f\n", item.preco);
        printf("Ano de fabricação: %d\n", item.ano);
        printf("------------------------------------\n");
        reg++;
    }
}

void IncluiRegistro()
{
    char lixo[255];
    struct impressora item;

    gets(lixo);

    fseek(arquivo, 0, SEEK_END);

    printf("\nDigite os dados da impressora:\n");

    printf("ID: ");
    scanf("%d", &item.id);
    gets(lixo);

    if (IdExistente(item.id))
    {
        printf("Erro: ID já cadastrado!\n");
        return;
    }

    printf("Modelo: ");
    gets(item.modelo);

    printf("Marca: ");
    gets(item.marca);

    printf("Capacidade: ");
    scanf("%d", &item.capacidade);
    gets(lixo);

    printf("País de Origem: ");
    gets(item.pais);

    printf("Peso: ");
    scanf("%f", &item.peso);
    gets(lixo);

    do
    {
        printf("Tipo (c - colorida, p - preto e branco): ");
        scanf("%c", &item.tipo);
        gets(lixo);
    }
    while (item.tipo != 'c' && item.tipo != 'p');

    printf("Preço: ");
    scanf("%f", &item.preco);
    gets(lixo);

    printf("Ano de fabricação: ");
    scanf("%d", &item.ano);
    gets(lixo);

    fwrite(&item, sizeof(struct impressora), 1, arquivo);
    printf("Registro gravado!\n");
}

void ApagaUlt()
{
    FILE *temp;
    struct impressora item;
    int nregs = 0, i;

    temp = fopen("_temp.xxx", "ab+");
    fseek(arquivo, 0, SEEK_SET);

    while (fread(&item, sizeof(struct impressora), 1, arquivo))
    {
        fwrite(&item, sizeof(struct impressora), 1, temp);
        nregs++;
    }

    fclose(arquivo);
    remove(nomearq);

    arquivo = fopen(nomearq, "ab+");
    temp = fopen("_temp.xxx", "rb");

    for (i = 0; i < nregs - 1; i++)
    {
        fread(&item, sizeof(struct impressora), 1, temp);
        fwrite(&item, sizeof(struct impressora), 1, arquivo);
    }

    fclose(temp);
    remove("_temp.xxx");
    printf("Último registro apagado.\n");
}

void EditarRegistro()
{
    int id, achou = 0, opcao;
    char lixo[255], continuar;
    struct impressora item;
    FILE *temp = fopen("_temp.xxx", "wb");

    printf("Digite o ID da impressora que deseja editar: ");
    scanf("%d", &id);
    gets(lixo);

    fseek(arquivo, 0, SEEK_SET);

    while (fread(&item, sizeof(struct impressora), 1, arquivo))
    {
        if (item.id == id)
        {
            achou = 1;

            do
            {
                system("cls");
                printf("Editando registro da impressora ID: %d\n\n", item.id);
                printf("1 - Modelo: %s\n", item.modelo);
                printf("2 - Marca: %s\n", item.marca);
                printf("3 - Capacidade: %d\n", item.capacidade);
                printf("4 - País de origem: %s\n", item.pais);
                printf("5 - Peso: %.2f\n", item.peso);
                printf("6 - Tipo: %c\n", item.tipo);
                printf("7 - Preço: %.2f\n", item.preco);
                printf("8 - Ano de fabricação: %d\n", item.ano);
                printf("0 - Cancelar edição\n\n");

                printf("Qual campo deseja editar? ");
                scanf("%d", &opcao);
                gets(lixo);

                switch (opcao)
                {
                case 1:
                    printf("Novo modelo: ");
                    gets(item.modelo);
                    break;
                case 2:
                    printf("Nova marca: ");
                    gets(item.marca);
                    break;
                case 3:
                    printf("Nova capacidade: ");
                    scanf("%d", &item.capacidade);
                    gets(lixo);
                    break;
                case 4:
                    printf("Novo país de origem: ");
                    gets(item.pais);
                    break;
                case 5:
                    printf("Novo peso: ");
                    scanf("%f", &item.peso);
                    gets(lixo);
                    break;
                case 6:
                    do
                    {
                        printf("Novo tipo (c ou p): ");
                        scanf("%c", &item.tipo);
                        gets(lixo);
                    }
                    while (item.tipo != 'c' && item.tipo != 'p');
                    break;
                case 7:
                    printf("Novo preço: ");
                    scanf("%f", &item.preco);
                    gets(lixo);
                    break;

                case 8:
                    printf("Novo ano de fabricação: ");
                    scanf("%d", &item.ano);
                    gets(lixo);
                    break;
                case 0:
                    printf("Edição cancelada.\n");
                    break;
                default:
                    printf("Opção inválida.\n");
                    break;
                }

                if (opcao != 0)
                {
                    printf("\nDeseja editar mais alguma coisa? (s/n): ");
                    scanf("%c", &continuar);
                    gets(lixo);
                }
                else
                {
                    continuar = 'n';
                }

            }
            while (continuar == 's' || continuar == 'S');
        }

        fwrite(&item, sizeof(struct impressora), 1, temp);
    }

    fclose(arquivo);
    fclose(temp);
    remove(nomearq);
    rename("_temp.xxx", nomearq);
    arquivo = fopen(nomearq, "ab+");

    if (achou)
        printf("Registro atualizado com sucesso.\n");
    else
        printf("ID não encontrado.\n");
}



void ApagaRegistroPorID()
{
    int id, achou = 0;
    struct impressora item;
    FILE *temp = fopen("_temp.xxx", "wb");

    printf("Digite o ID da impressora que deseja apagar: ");
    scanf("%d", &id);

    fseek(arquivo, 0, SEEK_SET);

    while (fread(&item, sizeof(struct impressora), 1, arquivo))
    {
        if (item.id != id)
            fwrite(&item, sizeof(struct impressora), 1, temp);
        else
            achou = 1;
    }

    fclose(arquivo);
    fclose(temp);
    remove(nomearq);
    rename("_temp.xxx", nomearq);
    arquivo = fopen(nomearq, "ab+");

    if (achou)
        printf("Registro removido com sucesso.\n");
    else
        printf("ID não encontrado.\n");
}

int main()
{
    setlocale (LC_ALL, "Portuguese");
    int opcao;
    arquivo = fopen(nomearq, "ab+");
    do
    {
        system("cls");
        printf("\nCadastro de Impressoras\n\n");
        printf("1 - Mostrar um registro\n");
        printf("2 - Mostrar todos os registros\n");
        printf("3 - Incluir um registro\n");
        printf("4 - Apagar o último registro\n");
        printf("5 - Editar um registro por ID\n");
        printf("6 - Apagar um registro por ID\n");
        printf("0 - Sair\n\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) MostraRegistro();
        if (opcao == 2) MostraTodos();
        if (opcao == 3) IncluiRegistro();
        if (opcao == 4) ApagaUlt();
        if (opcao == 5) EditarRegistro();
        if (opcao == 6) ApagaRegistroPorID();

        if (opcao != 0)
        {
            printf("\nPressione ENTER para continuar...");
            getchar();
            getchar();
        }
    }
    while (opcao != 0);

    fclose(arquivo);
    printf("Até logo!\n");
    return 0;
}
