#include <iostream> 
#include <cstdlib> // Para system()
#include <locale.h>
#include <cstdio> 
#include <windows.h> 
#include <cstring> // Para strstr
#include <limits>   // Para limpar o buffer de entrada (cin)
#include <ios> 
#include <string>

#undef max // soluciona o erro das linhas 51 e 57.

#define ARQUIVO "startup.txt"

using namespace std;

// --- DEFINIÇÕES DE CORES E ESTILOS (CÓDIGOS ANSI) ---

// Reseta toda a formatação
#define RESET   "\033[0m"

// Estilos de texto
#define NEGRITO "\033[1m"

// Paleta Principal (Azul, Cinza, Branco)
#define AZUL_TITULO       "\033[94m" // Azul Brilhante (para títulos)
#define CIANO_OPCAO       "\033[96m" // Ciano Brilhante (para números de opção)
#define BRANCO_TEXTO      "\033[97m" // Branco Brilhante (para texto principal)
#define CINZA_SEPARADOR   "\033[90m" // Cinza (Preto Brilhante) (para divisórias)

// Cores de Feedback
#define VERDE_SUCESSO     "\033[92m" // Verde Brilhante
#define VERMELHO_ERRO     "\033[91m" // Vermelho Brilhante
#define AMARELO_AVISO     "\033[93m" // Amarelo Brilhante

// --- FUNÇÕES AUXILIARES ---

// Limpa a tela do terminal
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Pausa a execução e espera o usuário pressionar Enter
void pausar() {
    cout << "\n" << AMARELO_AVISO << "Pressione Enter para continuar..." << RESET;
    // Limpa o buffer de entrada ANTES de esperar o get()
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Limpa o buffer de entrada (para usar depois de cin >>)
void limparBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Função de Validação de Entrada
template <typename T>
T lerOpcao(const char* prompt) {
    T valor;
    cout << "\n" << NEGRITO << BRANCO_TEXTO << prompt << RESET;
    while (!(cin >> valor)) {
        cin.clear(); 
        limparBuffer(); 
        cout << NEGRITO << VERMELHO_ERRO << "Entrada inválida. Digite um NÚMERO: " << RESET;
    }
    return valor;
}


// --- DECLARAÇÕES DAS FUNÇÕES DO CRUD ---
void cadastrarProduto (const char nome_produto[], int qtd, float preco);
int verificarEstoque(int estoque_atual);
void cadastrarVenda(const char nome_produto[], int qtd);
void verRelatorioVendas(); 

// --- FUNÇÃO DE LOGIN ---
bool fazerLogin(char nome_usuario[]) {
    const char USUARIO_CORRETO[] = "admin";
    const char SENHA_CORRETA[] = "123"; 
    char senha_digitada[30];
    int tentativas = 0;
    const int MAX_TENTATIVAS = 3;

    while (tentativas < MAX_TENTATIVAS) {
        limparTela();
        cout << NEGRITO << AZUL_TITULO << "================ LOGIN DE ACESSO ================" << RESET << endl;
        cout << CINZA_SEPARADOR << "-----------------------------------------------" << RESET << endl;
        
        cout << BRANCO_TEXTO << "Nome de Usuário: " << RESET;
        cin.getline(nome_usuario, 30);
        
        cout << BRANCO_TEXTO << "Senha: " << RESET;
        cin.getline(senha_digitada, 30);

        if (strcmp(nome_usuario, USUARIO_CORRETO) == 0 && strcmp(senha_digitada, SENHA_CORRETA) == 0) {
            cout << "\n" << VERDE_SUCESSO << "Login realizado com sucesso!" << RESET << endl;
            return true;
        } else {
            tentativas++;
            cout << "\n" << VERMELHO_ERRO << "Credenciais inválidas. Tentativa " << tentativas << " de " << MAX_TENTATIVAS << "." << RESET << endl;
            pausar();
        }
    }
    cout << "\n" << VERMELHO_ERRO << "Limite de tentativas atingido. O sistema será encerrado." << RESET << endl;
    return false;
}

// --- INÍCIO DO PROGRAMA ---
int main() {
    setlocale(LC_ALL, ".UTF-8");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001); 

    // --- VARIÁVEIS PRINCIPAIS ---
    float preco = 0.0;
    int qtd = 0;
    int op = 0; 
    int op1 = 0, op2 = 0, op3 = 0, op4 = 0;
    char nome_usuario[30] = "";
    char nome[30] = ""; 

    // --- VARIÁVEIS DE ESTOQUE ---
    int estoque_chocolate = 0;
    int estoque_bala = 0;
    int estoque_suco = 0;

    // --- BOAS VINDAS ---
    cout << BRANCO_TEXTO << "Digite seu nome: " << RESET;
    cin.getline(nome_usuario, 30); // getline é seguro aqui (primeiro input)
    cout << VERDE_SUCESSO << "Seja bem vindo(a) " << NEGRITO << nome_usuario << "!" << RESET << endl; 

    pausar(); 

    // --- CHAMADA DE LOGIN ANTES DO MENU CRUD ---
// Se o login falhar, o programa termina.
if (!fazerLogin(nome_usuario)) {
    return 1;
}

cout << VERDE_SUCESSO << "Seja bem vindo(a) " << NEGRITO << nome_usuario << "!" << RESET << endl; 
pausar();

    // --- LOOP PRINCIPAL DO MENU ---
    do {
        limparTela(); 
        cout << NEGRITO << AZUL_TITULO << "================ STARTUP ================" << RESET << endl;
        cout << CINZA_SEPARADOR << "---------------------------------------" << RESET << endl;
        cout << "  " << CIANO_OPCAO << "1" << RESET << BRANCO_TEXTO << " - Cadastrar produto" << RESET << endl;
        cout << "  " << CIANO_OPCAO << "2" << RESET << BRANCO_TEXTO << " - Verificar estoque" << RESET << endl;
        cout << "  " << CIANO_OPCAO << "3" << RESET << BRANCO_TEXTO << " - Cadastrar venda" << RESET << endl;
        cout << "  " << CIANO_OPCAO << "4" << RESET << BRANCO_TEXTO << " - Excluir Dados" << RESET << endl; 
        cout << "  " << CIANO_OPCAO << "5" << RESET << BRANCO_TEXTO << " - Ver Relatório de Vendas" << RESET << endl; 
        cout << "  " << AMARELO_AVISO << "6" << RESET << BRANCO_TEXTO << " - Sair do sistema" << RESET << endl; 
        cout << "\n" << NEGRITO << BRANCO_TEXTO << "Digite a opção desejada: " << RESET; 
        
        while (!(cin >> op)) {
            cin.clear(); 
            limparBuffer(); 
            cout << NEGRITO << VERMELHO_ERRO << "Entrada inválida. Digite um NÚMERO: " << RESET;
        }
        limparBuffer(); // Limpa o '\n' deixado pelo cin >>
        
        switch (op) {
            
            // --- CASE 1: CADASTRO ---
            case 1: {
                do {
                    limparTela(); 
                    cout << NEGRITO << AZUL_TITULO << "--- Cadastro de Produtos ---" << RESET << endl;
                    cout << CINZA_SEPARADOR << "----------------------------" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "1" << RESET << BRANCO_TEXTO << " - Chocolate" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "2" << RESET << BRANCO_TEXTO << " - Bala" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "3" << RESET << BRANCO_TEXTO << " - Suco" << RESET << endl;
                    cout << "  " << AMARELO_AVISO << "4" << RESET << BRANCO_TEXTO << " - Voltar ao menu anterior" << RESET << endl;
                    cout << "\n" << NEGRITO << BRANCO_TEXTO << "Escolha a opção desejada: " << RESET;
                    
                    op1 = lerOpcao<int>("Escolha a opção desejada: ");
                    limparBuffer();
                    
                    switch (op1){
                        case 1:
                            cout << BRANCO_TEXTO << "cadastrar Chcolate" << RESET << endl; 
                            cout << BRANCO_TEXTO << "Digite a quantidade a ser cadastrada: " << RESET; 
                            cin >> qtd; limparBuffer();
                            cout << BRANCO_TEXTO << "Digite o preço do produto: R$ " << RESET;
                            cin >> preco; limparBuffer();
                            cadastrarProduto("Chocolate", qtd, preco); 
                            estoque_chocolate += qtd;
                            cout << VERDE_SUCESSO <<"Chocolate cadastrado!" << RESET << endl;
                            break;
                        case 2:
                            cout << BRANCO_TEXTO << "cadastrar bala" << RESET << endl; 
                            cout << BRANCO_TEXTO << "Digite a quantidade a ser cadastrada: " << RESET;
                            cin >> qtd; limparBuffer();
                            cout << BRANCO_TEXTO << "Digite o preço do produto: R$ " << RESET;
                            cin >> preco; limparBuffer();
                            cadastrarProduto("Bala", qtd, preco);
                            estoque_bala += qtd;
                            cout << VERDE_SUCESSO << "Bala cadastrado!" << RESET << endl;
                            break;
                        case 3:
                            cout << BRANCO_TEXTO << "cadastrar Suco" << RESET << endl; 
                            cout << BRANCO_TEXTO << "Digite a quantidade a ser cadastrada: " << RESET;
                            cin >> qtd; limparBuffer();
                            cout << BRANCO_TEXTO << "Digite o preço do produto: R$ " << RESET;
                            cin >> preco; limparBuffer();
                            cadastrarProduto("Suco", qtd, preco);
                            estoque_suco += qtd;
                            cout << VERDE_SUCESSO << "Suco cadastrado!" << RESET << endl;
                            break;
                        case 4: 
                            cout << AMARELO_AVISO << "voltando ao menu anterior..." << RESET << endl; 
                            break;
                        default: 
                            cout << VERMELHO_ERRO << "opção invalida, tente novamente!" << RESET << endl; 
                            break;
                    }
                    pausar(); 
                } while (op1 != 4);
                break; 
            } 
            
            // --- CASE 2: VERIFICAR ESTOQUE ---
            case 2:{
                do{
                    limparTela();
                    cout << NEGRITO << AZUL_TITULO << "--- Verificar Estoque ---" << RESET << endl;
                    cout << CINZA_SEPARADOR << "---------------------------" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "1" << RESET << BRANCO_TEXTO << " - Verificar estoque do Chocolate" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "2" << RESET << BRANCO_TEXTO << " - Verificar estoque do Bala" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "3" << RESET << BRANCO_TEXTO << " - Verificar estoque do Suco" << RESET << endl;
                    cout << "  " << AMARELO_AVISO << "4" << RESET << BRANCO_TEXTO << " - Voltar ao menu anterior" << RESET << endl;
                    cout << "\n" << NEGRITO << BRANCO_TEXTO << "Escolha a opção desejada: " << RESET;
                    
                    op2 = lerOpcao<int>("Escolha a opção desejada: ");
                    limparBuffer();
                    
                    switch (op2){
                        case 1: 
                            cout << BRANCO_TEXTO << "Estoque do Chocolate é de: " << NEGRITO << VERDE_SUCESSO << verificarEstoque(estoque_chocolate) << RESET << endl; 
                            break;
                        case 2: 
                            cout << BRANCO_TEXTO << "Estoque do Bala é de: " << NEGRITO << VERDE_SUCESSO << verificarEstoque(estoque_bala) << RESET << endl; 
                            break;
                        case 3: 
                            cout << BRANCO_TEXTO << "Estoque do Suco é de: " << NEGRITO << VERDE_SUCESSO << verificarEstoque(estoque_suco) << RESET << endl; 
                            break;
                        case 4: 
                            cout << AMARELO_AVISO << "voltando ao menu anterior..." << RESET << endl; 
                            break;
                        default: 
                            cout << VERMELHO_ERRO << "opção invalida, tente novamente!" << RESET << endl; 
                            break;
                    }
                    pausar(); 
                } while (op2 != 4);
                break; 
            } 
            
            // --- CASE 3: CADASTRAR VENDA ---
            case 3:{
                do{
                    limparTela();
                    cout << NEGRITO << AZUL_TITULO << "--- Cadastrar Venda ---" << RESET << endl;
                    cout << CINZA_SEPARADOR << "-------------------------" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "1" << RESET << BRANCO_TEXTO << " - Vender Chocolate" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "2" << RESET << BRANCO_TEXTO << " - Vender Bala" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "3" << RESET << BRANCO_TEXTO << " - Vender Suco" << RESET << endl;
                    cout << "  " << AMARELO_AVISO << "4" << RESET << BRANCO_TEXTO << " - Voltar ao menu anterior" << RESET << endl;
                    cout << "\n" << NEGRITO << BRANCO_TEXTO << "Escolha a opção desejada: " << RESET;
                    
                    op3 = lerOpcao<int>("Escolha a opção desejada: ");
                    limparBuffer();
                    
                    switch (op3){
                        case 1: 
                            cout << BRANCO_TEXTO << "Vender Chocolate (Estoque: " << AMARELO_AVISO << estoque_chocolate << RESET << BRANCO_TEXTO << ")" << RESET << endl; 
                            cout << BRANCO_TEXTO << "Digite a quantidade a ser vendida: " << RESET; 
                            cin >> qtd; limparBuffer();

                            if(qtd <= estoque_chocolate){
                                estoque_chocolate -= qtd; 
                                cadastrarVenda("Chocolate", qtd); 
                                cout << VERDE_SUCESSO << "Venda realizada!" << RESET << endl;
                            } else {
                                cout << VERMELHO_ERRO << "Estoque insuficiente!" << RESET << endl;
                            }
                            break;
                        case 2: 
                            cout << BRANCO_TEXTO << "Vender Bala (Estoque: " << AMARELO_AVISO << estoque_bala << RESET << BRANCO_TEXTO << ")" << RESET << endl; 
                            cout << BRANCO_TEXTO << "Digite a quantidade a ser vendida: " << RESET; 
                            cin >> qtd; limparBuffer(); 

                            if(qtd <= estoque_bala){
                                estoque_bala -= qtd; 
                                cadastrarVenda("Bala", qtd); 
                                cout << VERDE_SUCESSO << "Venda realizada!" << RESET << endl;
                            } else {
                                cout << VERMELHO_ERRO << "Estoque insuficiente!" << RESET << endl;
                            }
                            break;
                        case 3: 
                            cout << BRANCO_TEXTO << "Vender Suco (Estoque: " << AMARELO_AVISO << estoque_suco << RESET << BRANCO_TEXTO << ")" << RESET << endl; 
                            cout << BRANCO_TEXTO << "Digite a quantidade a ser vendida: " << RESET; 
                            cin >> qtd; limparBuffer();

                            if(qtd <= estoque_suco){
                                estoque_suco -= qtd; 
                                cadastrarVenda("Suco", qtd); 
                                cout << VERDE_SUCESSO << "Venda realizada!" << RESET << endl;
                            } else {
                                cout << VERMELHO_ERRO << "Estoque insuficiente!" << RESET << endl;
                            }
                            break;
                        case 4: 
                            cout << AMARELO_AVISO << "voltando ao menu anterior..." << RESET << endl; 
                            break;
                        default: 
                            cout << VERMELHO_ERRO << "opção invalida, tente novamente!" << RESET << endl; 
                            break;
                    }
                    pausar(); 
                } while (op3 != 4);
                break; 
            }
            
            // --- CASE 4: EXCLUIR DADOS ---
            case 4:{
                do{
                    limparTela();
                    cout << NEGRITO << AZUL_TITULO << "--- Excluir Dados ---" << RESET << endl;
                    cout << CINZA_SEPARADOR << "---------------------" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "1" << RESET << BRANCO_TEXTO << " - Excluir estoque Chocolate" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "2" << RESET << BRANCO_TEXTO << " - Excluir estoque Bala" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "3" << RESET << BRANCO_TEXTO << " - Excluir estoque Suco" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "4" << RESET << BRANCO_TEXTO << " - Excluir nome do vendedor (memória)" << RESET << endl;
                    cout << "  " << VERMELHO_ERRO << "5" << RESET << BRANCO_TEXTO << " - Excluir TUDO (Memória e Arquivo)" << RESET << endl;
                    cout << "  " << AMARELO_AVISO << "6" << RESET << BRANCO_TEXTO << " - Voltar ao menu anterior" << RESET << endl;
                    cout << "\n" << NEGRITO << BRANCO_TEXTO << "Escolha a opção desejada: " << RESET;
                    
                    op4 = lerOpcao<int>("Escolha a opção desejada: ");
                    limparBuffer();

                    switch (op4){
                        case 1: {estoque_chocolate = 0; cout << VERDE_SUCESSO << "Estoque do Chocolate excluído!" << RESET << endl;} break; 
                        case 2: {estoque_bala = 0; cout << VERDE_SUCESSO << "Estoque do Bala excluído!" << RESET << endl;} break;
                        case 3: {estoque_suco = 0; cout << VERDE_SUCESSO << "Estoque do Suco excluído!" << RESET << endl;} break;
                        case 4: {nome[0] = '\0'; cout << VERDE_SUCESSO << "Nome deletado com sucesso!" << RESET << endl;} break; 
                        case 5: {
                            nome[0] = '\0'; estoque_chocolate = 0; estoque_bala = 0; estoque_suco = 0; 
                            cout << VERDE_SUCESSO << "Todos dados da memória excluídos!" << RESET << endl;

                            FILE *arquivoParaLimpar = fopen(ARQUIVO, "w");
                            if (arquivoParaLimpar == NULL) {
                                cout << VERMELHO_ERRO << "Erro ao tentar limpar o arquivo!" << RESET << endl;
                            } else {
                                fclose(arquivoParaLimpar);
                                cout << VERDE_SUCESSO << "Arquivo '" << ARQUIVO << "' limpo com sucesso!" << RESET << endl;
                            }
                        } break;
                        case 6:
                            cout << AMARELO_AVISO << "Voltando ao menu anterior..." << RESET << endl;
                            break;
                        default: 
                            cout << VERMELHO_ERRO << "Opção inválida, tente novamente." << RESET << endl;
                            break;
                    }
                    pausar();
                } while (op4 != 6);
                break; 
            } 
            
            // --- CASE 5: VER RELATÓRIO ---
            case 5: {
                verRelatorioVendas();
                pausar();
                break; 
            }

            // --- CASE 6: SAIR ---
            case 6: {
                limparTela();
                cout << AMARELO_AVISO << "Saindo do sistema... Até logo, " << nome_usuario << "!" << RESET << endl;
                break; 
            }

            // --- DEFAULT ---
            default: {
                cout << VERMELHO_ERRO << "Opção inválida, tente novamente." << RESET << endl;
                pausar(); 
                break;
            }

        } // Fim do switch(op)
        
    } while (op != 6); 
    
    return 0;
}
// --- FIM DO MAIN ---


// Função de Estoque Simples
int verificarEstoque(int estoque_atual) {
    return estoque_atual;
}

// Função de Cadastro (Salva no arquivo)
void cadastrarProduto(const char nome_produto[], int qtd, float preco){
    FILE *fp = fopen(ARQUIVO, "a");
    if (fp == NULL) {
        cout << VERMELHO_ERRO << "erro ao abir o arquivo para escrita!" << RESET << endl;
        return; 
    }
    fprintf(fp, "CADASTRO: %s, Quantidade: %d, Preço: R$ %.2f\n\n", nome_produto, qtd, preco);
    fclose (fp);
}

// --- Função para salvar a VENDA no arquivo ---
void cadastrarVenda(const char *nome_produto, int quantidade, const char *nome_usuario, float preco)
{
    FILE *fp = fopen("ARQUIVO.txt", "a");
    if (fp == NULL) {
        cout << "Erro ao abrir o arquivo!";
        return;
    }

    fprintf(fp, 
            "VENDA:\n"
            "Produto: %s\n"
            "Quantidade: %d\n"
            "Usuario: %s\n"
            "Preco: %.2f\n"
            "Total: %.2f\n\n",
            nome_produto,
            quantidade,
            nome_usuario,
            preco,
            preco * quantidade);

    fclose(fp);
}


// --- Função para LER o relatório de vendas ---
void verRelatorioVendas() {
    limparTela();
    cout << NEGRITO << AZUL_TITULO << "--- Relatório de Vendas (do " << ARQUIVO << ") ---" << RESET << endl << endl;

    FILE *fp = fopen(ARQUIVO, "r"); 
    if (fp == NULL) {
        cout << AMARELO_AVISO << "Nenhuma atividade registrada ainda." << RESET << endl;
        return;
    }
    
    char linha[255]; 
    bool encontrouVenda = false;
    
    while (fgets(linha, 255, fp) != NULL) {
        if (strstr(linha, "VENDA:") != NULL) {
            cout << BRANCO_TEXTO << "  " << linha << RESET; // Imprime a linha da venda
            encontrouVenda = true;
        }
    }
    
    if (!encontrouVenda) {
        cout << AMARELO_AVISO << "Nenhuma VENDA encontrada no relatório." << RESET << endl;
    }
    
    fclose(fp);
    cout << "\n" << CINZA_SEPARADOR << "--- Fim do Relatório ---" << RESET << endl;
}
