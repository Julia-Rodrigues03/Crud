/* startup.c
   supermarket startup system em C
   Funcionalidades:
   cadastrar produtos (chocolate, bala, suco) com preço e quantidade
   verificar estoque dos produtos
   Salva também o nome do vendedor em cada VENDA.

   Autores originais: Júlia, João e Leonardo
   Data: 2025-11-16
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define ARQUIVO "startup.txt"

/* --- DEFINIÇÕES DE CORES E ESTILOS (CÓDIGOS ANSI) --- */
#define RESET   "\033[0m"
#define NEGRITO "\033[1m"
#define AZUL_TITULO       "\033[94m"
#define CIANO_OPCAO       "\033[96m"
#define BRANCO_TEXTO      "\033[97m"
#define CINZA_SEPARADOR   "\033[90m"
#define VERDE_SUCESSO     "\033[92m"
#define VERMELHO_ERRO     "\033[91m"
#define AMARELO_AVISO     "\033[93m"

/* --- AUXILIARES --- */
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* lê uma linha com segurança, remove '\n' */
void lerLinha(char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) != NULL) {
        size_t ln = strlen(buffer);
        if (ln > 0 && buffer[ln - 1] == '\n') buffer[ln - 1] = '\0';
    } else {
        buffer[0] = '\0';
    }
}

/* lê um int com prompt, repete até ser validado */
int lerInt(const char *prompt) {
    char linha[128];
    int valor;
    while (1) {
        if (prompt && prompt[0] != '\0') printf("%s", prompt);
        if (fgets(linha, sizeof(linha), stdin) == NULL) return 0;
        if (sscanf(linha, "%d", &valor) == 1) return valor;
        printf("%sEntrada inválida. Digite um NÚMERO: %s\n", VERMELHO_ERRO, RESET);
    }
}

/* lê um float com prompt, repete até ser validado */
float lerFloat(const char *prompt) {
    char linha[128];
    float valor;
    while (1) {
        if (prompt && prompt[0] != '\0') printf("%s", prompt);
        if (fgets(linha, sizeof(linha), stdin) == NULL) return 0.0f;
        if (sscanf(linha, "%f", &valor) == 1) return valor;
        printf("%sEntrada inválida. Digite um NÚMERO: %s\n", VERMELHO_ERRO, RESET);
    }
}

/* pausa esperando Enter  do usuario */
void pausar() {
    char tmp[8];
    printf("\n%sPressione Enter para continuar...%s", AMARELO_AVISO, RESET);
    lerLinha(tmp, sizeof(tmp));
}

/* --- PROTÓTIPOS --- */
void cadastrarProduto(const char nome_produto[], int qtd, float preco);
int verificarEstoque(int estoque_atual);
void cadastrarVenda(const char *nome_vendedor, const char *nome_produto, int quantidade, const char *nome_usuario, float preco);
void verRelatorioVendas();
int fazerLogin(char nome_usuario[]);

/* --- FUNÇÃO DE LOGIN PARTE DO JOÃO --- */
int fazerLogin(char nome_usuario[]) {
    const char USUARIO_CORRETO[] = "admin";
    const char SENHA_CORRETA[] = "123";
    char senha_digitada[30];
    int tentativas = 0;
    const int MAX_TENTATIVAS = 3;

    while (tentativas < MAX_TENTATIVAS) {
        limparTela();
        printf("%s%s================ LOGIN DE ACESSO ================%s\n", NEGRITO, AZUL_TITULO, RESET);
        printf("%s-----------------------------------------------%s\n", CINZA_SEPARADOR, RESET);

        printf("%sNome de Usuário: %s", BRANCO_TEXTO, RESET);
        lerLinha(nome_usuario, 30);

        printf("%sSenha: %s", BRANCO_TEXTO, RESET);
        lerLinha(senha_digitada, sizeof(senha_digitada));

        if (strcmp(nome_usuario, USUARIO_CORRETO) == 0 && strcmp(senha_digitada, SENHA_CORRETA) == 0) {
            printf("\n%sLogin realizado com sucesso!%s\n", VERDE_SUCESSO, RESET);
            return 1;
        } else {
            tentativas++;
            printf("\n%sCredenciais inválidas. Tentativa %d de %d.%s\n", VERMELHO_ERRO, tentativas, MAX_TENTATIVAS, RESET);
            pausar();
        }
    }
    printf("\n%sLimite de tentativas atingido. O sistema será encerrado.%s\n", VERMELHO_ERRO, RESET);
    return 0;
}

/* --- MAIN PARTE DE JULIA --- */
int main(void) {
/* locale e console utf-8 */
    setlocale(LC_ALL, "");
#ifdef _WIN32
    /* tenta configurar console para utf-8 no Windows */
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    float preco = 0.0f;
    int qtd = 0;
    int op = 0;
    int op1 = 0, op2 = 0, op3 = 0, op4 = 0;
    char nome_usuario[30] = "";   /* para login */
    char nome_vendedor[30] = "";  /* nome digitado no início (vendedor) */
    int estoque_chocolate = 0;
    int estoque_bala = 0;
    int estoque_suco = 0;

    /* preços por produto (persistem enquanto programa roda) */
    float preco_chocolate = 0.0f;
    float preco_bala = 0.0f;
    float preco_suco = 0.0f;

    printf("%sDigite seu nome (vendedor): %s", BRANCO_TEXTO, RESET);
    lerLinha(nome_vendedor, sizeof(nome_vendedor));
    if (strlen(nome_vendedor) == 0) {
        /* se vazio, usar "Vendedor" genérico */
        strncpy(nome_vendedor, "Vendedor", sizeof(nome_vendedor) - 1);
        nome_vendedor[sizeof(nome_vendedor)-1] = '\0';
    }

    /* Use nome_temp para mostrar boas-vindas antes do login (como no C++ original) */
    printf("%sSeja bem vindo(a) %s%s!%s\n", VERDE_SUCESSO, NEGRITO, nome_vendedor, RESET);
    pausar();

    /* LOGIN */
    if (!fazerLogin(nome_usuario)) {
        return 1;
    }

    printf("%sSeja bem vindo(a) %s%s!%s\n", VERDE_SUCESSO, NEGRITO, nome_usuario, RESET);
    pausar();

    do {
        limparTela();
        printf("%s%s================ STARTUP ================%s\n", NEGRITO, AZUL_TITULO, RESET);
        printf("%s---------------------------------------%s\n", CINZA_SEPARADOR, RESET);
        printf("  %s1%s - %sCadastrar produto%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
        printf("  %s2%s - %sVerificar estoque%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
        printf("  %s3%s - %sCadastrar venda%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
        printf("  %s4%s - %sExcluir Dados%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
        printf("  %s5%s - %sVer Relatório de Vendas%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
        printf("  %s6%s - %sSair do sistema%s\n", AMARELO_AVISO, RESET, BRANCO_TEXTO, RESET);
        printf("\n%s%sDigite a opção desejada: %s", NEGRITO, BRANCO_TEXTO, RESET);

        op = lerInt("");
        switch (op) {

            /* CADASTRO */
            case 1:
                do {
                    limparTela();
                    printf("%s%s--- Cadastro de Produtos --- %s\n", NEGRITO, AZUL_TITULO, RESET);
                    printf("%s----------------------------%s\n", CINZA_SEPARADOR, RESET);
                    printf("  %s1%s - %sChocolate%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
                    printf("  %s2%s - %sBala%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
                    printf("  %s3%s - %sSuco%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
                    printf("  %s4%s - %sVoltar ao menu anterior%s\n", AMARELO_AVISO, RESET, BRANCO_TEXTO, RESET);

                    op1 = lerInt("\nEscolha a opção desejada: ");
                    switch (op1) {
                        case 1:
                            printf("%sCadastrar Chocolate%s\n", BRANCO_TEXTO, RESET);
                            qtd = lerInt("Digite a quantidade a ser cadastrada: ");
                            preco = lerFloat("Digite o preço do produto: R$ ");
                            preco_chocolate = preco;
                            cadastrarProduto("Chocolate", qtd, preco);
                            estoque_chocolate += qtd;
                            printf("%sChocolate cadastrado!%s\n", VERDE_SUCESSO, RESET);
                            break;
                        case 2:
                            printf("%sCadastrar Bala%s\n", BRANCO_TEXTO, RESET);
                            qtd = lerInt("Digite a quantidade a ser cadastrada: ");
                            preco = lerFloat("Digite o preço do produto: R$ ");
                            preco_bala = preco;
                            cadastrarProduto("Bala", qtd, preco);
                            estoque_bala += qtd;
                            printf("%sBala cadastrado!%s\n", VERDE_SUCESSO, RESET);
                            break;
                        case 3:
                            printf("%sCadastrar Suco%s\n", BRANCO_TEXTO, RESET);
                            qtd = lerInt("Digite a quantidade a ser cadastrada: ");
                            preco = lerFloat("Digite o preço do produto: R$ ");
                            preco_suco = preco;
                            cadastrarProduto("Suco", qtd, preco);
                            estoque_suco += qtd;
                            printf("%sSuco cadastrado!%s\n", VERDE_SUCESSO, RESET);
                            break;
                        case 4:
                            printf("%sVoltando ao menu anterior...%s\n", AMARELO_AVISO, RESET);
                            break;
                        default:
                            printf("%sOpção inválida, tente novamente!%s\n", VERMELHO_ERRO, RESET);
                            break;
                    }
                    pausar();
                } while (op1 != 4);
                break;

            /* VERIFICAR ESTOQUE */
            case 2:
                do {
                    limparTela();
                    printf("%s%s--- Verificar Estoque --- %s\n", NEGRITO, AZUL_TITULO, RESET);
                    printf("%s---------------------------%s\n", CINZA_SEPARADOR, RESET);
                    printf("  %s1%s - %sVerificar estoque do Chocolate%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
                    printf("  %s2%s - %sVerificar estoque do Bala%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
                    printf("  %s3%s - %sVerificar estoque do Suco%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
                    printf("  %s4%s - %sVoltar ao menu anterior%s\n", AMARELO_AVISO, RESET, BRANCO_TEXTO, RESET);

                    op2 = lerInt("\nEscolha a opção desejada: ");
                    switch (op2) {
                        case 1:
                            printf("%sEstoque do Chocolate é de: %s%d%s\n", BRANCO_TEXTO, VERDE_SUCESSO, verificarEstoque(estoque_chocolate), RESET);
                            break;
                        case 2:
                            printf("%sEstoque do Bala é de: %s%d%s\n", BRANCO_TEXTO, VERDE_SUCESSO, verificarEstoque(estoque_bala), RESET);
                            break;
                        case 3:
                            printf("%sEstoque do Suco é de: %s%d%s\n", BRANCO_TEXTO, VERDE_SUCESSO, verificarEstoque(estoque_suco), RESET);
                            break;
                        case 4:
                            printf("%sVoltando ao menu anterior...%s\n", AMARELO_AVISO, RESET);
                            break;
                        default:
                            printf("%sOpção inválida, tente novamente!%s\n", VERMELHO_ERRO, RESET);
                            break;
                    }
                    pausar();
                } while (op2 != 4);
                break;

            /* CADASTRAR VENDA */
            case 3:
                do {
                    limparTela();
                    printf("%s%s--- Cadastrar Venda --- %s\n", NEGRITO, AZUL_TITULO, RESET);
                    printf("%s-------------------------%s\n", CINZA_SEPARADOR, RESET);
                    printf("  %s1%s - %sVender Chocolate%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
                    printf("  %s2%s - %sVender Bala%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
                    printf("  %s3%s - %sVender Suco%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
                    printf("  %s4%s - %sVoltar ao menu anterior%s\n", AMARELO_AVISO, RESET, BRANCO_TEXTO, RESET);

                    op3 = lerInt("\nEscolha a opção desejada: ");
                    switch (op3) {
                        case 1:
                            printf("%sVender Chocolate (Estoque: %s%d%s)%s\n", BRANCO_TEXTO, AMARELO_AVISO, estoque_chocolate, RESET, RESET);
                            qtd = lerInt("Digite a quantidade a ser vendida: ");
                            if (qtd <= estoque_chocolate) {
                                estoque_chocolate -= qtd;
                                cadastrarVenda(nome_vendedor, "Chocolate", qtd, nome_usuario, preco_chocolate);
                                printf("%sVenda realizada!%s\n", VERDE_SUCESSO, RESET);
                            } else {
                                printf("%sEstoque insuficiente!%s\n", VERMELHO_ERRO, RESET);
                            }
                            break;
                        case 2:
                            printf("%sVender Bala (Estoque: %s%d%s)%s\n", BRANCO_TEXTO, AMARELO_AVISO, estoque_bala, RESET, RESET);
                            qtd = lerInt("Digite a quantidade a ser vendida: ");
                            if (qtd <= estoque_bala) {
                                estoque_bala -= qtd;
                                cadastrarVenda(nome_vendedor, "Bala", qtd, nome_usuario, preco_bala);
                                printf("%sVenda realizada!%s\n", VERDE_SUCESSO, RESET);
                            } else {
                                printf("%sEstoque insuficiente!%s\n", VERMELHO_ERRO, RESET);
                            }
                            break;
                        case 3:
                            printf("%sVender Suco (Estoque: %s%d%s)%s\n", BRANCO_TEXTO, AMARELO_AVISO, estoque_suco, RESET, RESET);
                            qtd = lerInt("Digite a quantidade a ser vendida: ");
                            if (qtd <= estoque_suco) {
                                estoque_suco -= qtd;
                                cadastrarVenda(nome_vendedor, "Suco", qtd, nome_usuario, preco_suco);
                                printf("%sVenda realizada!%s\n", VERDE_SUCESSO, RESET);
                            } else {
                                printf("%sEstoque insuficiente!%s\n", VERMELHO_ERRO, RESET);
                            }
                            break;
                        case 4:
                            printf("%sVoltando ao menu anterior...%s\n", AMARELO_AVISO, RESET);
                            break;
                        default:
                            printf("%sOpção inválida, tente novamente!%s\n", VERMELHO_ERRO, RESET);
                            break;
                    }
                    pausar();
                } while (op3 != 4);
                break;

            /* EXCLUIR DADOS */
            case 4:
                do {
                    limparTela();
                    printf("%s%s--- Excluir Dados --- %s\n", NEGRITO, AZUL_TITULO, RESET);
                    printf("%s---------------------%s\n", CINZA_SEPARADOR, RESET);
                    printf("  %s1%s - %sExcluir estoque Chocolate%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
                    printf("  %s2%s - %sExcluir estoque Bala%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
                    printf("  %s3%s - %sExcluir estoque Suco%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
                    printf("  %s4%s - %sExcluir nome do vendedor (memória)%s\n", CIANO_OPCAO, RESET, BRANCO_TEXTO, RESET);
                    printf("  %s5%s - %sExcluir TUDO (Memória e Arquivo)%s\n", VERMELHO_ERRO, RESET, BRANCO_TEXTO, RESET);
                    printf("  %s6%s - %sVoltar ao menu anterior%s\n", AMARELO_AVISO, RESET, BRANCO_TEXTO, RESET);

                    op4 = lerInt("\nEscolha a opção desejada: ");
                    switch (op4) {
                        case 1:
                            estoque_chocolate = 0;
                            printf("%sEstoque do Chocolate excluído!%s\n", VERDE_SUCESSO, RESET);
                            break;
                        case 2:
                            estoque_bala = 0;
                            printf("%sEstoque do Bala excluído!%s\n", VERDE_SUCESSO, RESET);
                            break;
                        case 3:
                            estoque_suco = 0;
                            printf("%sEstoque do Suco excluído!%s\n", VERDE_SUCESSO, RESET);
                            break;
                        case 4:
                            nome_vendedor[0] = '\0';
                            printf("%sNome deletado com sucesso!%s\n", VERDE_SUCESSO, RESET);
                            break;
                        case 5: {
                            nome_vendedor[0] = '\0';
                            estoque_chocolate = estoque_bala = estoque_suco = 0;
                            printf("%sTodos dados da memória excluídos!%s\n", VERDE_SUCESSO, RESET);

                            FILE *arquivoParaLimpar = fopen(ARQUIVO, "w");
                            if (arquivoParaLimpar == NULL) {
                                printf("%sErro ao tentar limpar o arquivo!%s\n", VERMELHO_ERRO, RESET);
                            } else {
                                fclose(arquivoParaLimpar);
                                printf("%sArquivo '%s' limpo com sucesso!%s\n", VERDE_SUCESSO, ARQUIVO, RESET);
                            }
                            break;
                        }
                        case 6:
                            printf("%sVoltando ao menu anterior...%s\n", AMARELO_AVISO, RESET);
                            break;
                        default:
                            printf("%sOpção inválida, tente novamente.%s\n", VERMELHO_ERRO, RESET);
                            break;
                    }
                    pausar();
                } while (op4 != 6);
                break;

            /* RELATÓRIO */
            case 5:
                verRelatorioVendas();
                pausar();
                break;

            /* SAIR */
            case 6:
                limparTela();
                printf("%sSaindo do sistema... Até logo, %s!%s\n", AMARELO_AVISO, nome_vendedor, RESET);
                break;

            default:
                printf("%sOpção inválida, tente novamente.%s\n", VERMELHO_ERRO, RESET);
                pausar();
                break;
        }

    } while (op != 6);

    return 0;
}

/* --- IMPLEMENTAÇÕES PARTE DE LEO --- */

int verificarEstoque(int estoque_atual) {
    return estoque_atual;
}

void cadastrarProduto(const char nome_produto[], int qtd, float preco) {
    FILE *fp = fopen("startup.txt", "a");
    if (fp == NULL) {
        printf("%serro ao abrir o arquivo para escrita!%s\n", VERMELHO_ERRO, RESET);
        return;
    }
    fprintf(fp, "--- Produto Cadastrado ---\n"
                 " %s\n"
                 "Quantidade: %d\n"
                 "Preço: R$ %.2f\n\n", 
                 nome_produto, 
                 qtd, 
                 preco);
    fclose(fp);
}

/* função robusta para salvar VENDA (inclui nome do vendedor) */
void cadastrarVenda(const char *nome_vendedor, const char *nome_produto, int quantidade, const char *nome_usuario, float preco)
{
    FILE *fp = fopen(ARQUIVO, "a");
    if (fp == NULL) {
        perror("Erro ao abrir arquivo para gravar venda");
        printf("%sErro ao abrir o arquivo!%s\n", VERMELHO_ERRO, RESET);
        return;
    }

    int ret = fprintf(fp,
            "--- Registro de Venda ---\n"
            "Vendedor: %s\n"
            "Usuario: %s\n"
            "Produto: %s\n"
            "Quantidade: %d\n"
            "Preco Unitario: %.2f\n"
            "Total: %.2f\n\n",
            nome_vendedor ? nome_vendedor : "(vazio)",
            nome_usuario ? nome_usuario : "(vazio)",
            nome_produto ? nome_produto : "(vazio)",
            quantidade,
            preco,
            preco * quantidade);

    if (ret < 0) {
        perror("Erro ao escrever no arquivo");
        printf("%sFalha ao gravar a venda.%s\n", VERMELHO_ERRO, RESET);
        fclose(fp);
        return;
    }

    /* garantir gravação no disco */
    if (fflush(fp) != 0) {
        perror("Erro ao forçar flush");
    }

    if (fclose(fp) != 0) {
        perror("Erro ao fechar arquivo");
    } else {
        printf("%sVenda gravada com sucesso no arquivo '%s'.%s\n", VERDE_SUCESSO, ARQUIVO, RESET);
    }
}

void verRelatorioVendas() {
    limparTela();
    printf("%s%s--- Relatório de Vendas (Arquivo: %s) --- %s\n\n",
           NEGRITO, AZUL_TITULO, ARQUIVO, RESET);

    FILE *fp = fopen(ARQUIVO, "r");
    if (fp == NULL) {
        printf("%sNenhum registro encontrado.%s\n", AMARELO_AVISO, RESET);
        return;
    }

    char linha[512];
    int temConteudo = 0;

    while (fgets(linha, sizeof(linha), fp) != NULL) {
        printf("%s%s%s", BRANCO_TEXTO, linha, RESET);
        temConteudo = 1;
    }

    fclose(fp);

    if (!temConteudo) {
        printf("%sArquivo vazio. Nenhuma venda registrada.%s\n", AMARELO_AVISO, RESET);
    }

    printf("\n%s--- Fim do Relatório --- %s\n", CINZA_SEPARADOR, RESET);
}

