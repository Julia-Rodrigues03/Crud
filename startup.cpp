#include <iostream> 
#include <cstdlib> // Para system()
#include <locale.h>
#include <cstdio> 
#include <windows.h> 
#include <cstring> // Para strstr
#include <limits>   // Para limpar o buffer de entrada (cin)

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


// --- DECLARAÇÕES DAS FUNÇÕES DO CRUD ---
void cadastrarProduto (const char nome_produto[], int qtd, float preco);
int verificarEstoque(int estoque_atual);
void cadastrarVenda(const char nome_produto[], int qtd);
void verRelatorioVendas(); 

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
    int estoque_x = 0;
    int estoque_y = 0;
    int estoque_z = 0;

    // --- BOAS VINDAS ---
    cout << BRANCO_TEXTO << "Digite seu nome: " << RESET;
    cin.getline(nome_usuario, 30); // getline é seguro aqui (primeiro input)
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
                    cout << "  " << CIANO_OPCAO << "1" << RESET << BRANCO_TEXTO << " - produtos x" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "2" << RESET << BRANCO_TEXTO << " - produtos y" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "3" << RESET << BRANCO_TEXTO << " - produtos z" << RESET << endl;
                    cout << "  " << AMARELO_AVISO << "4" << RESET << BRANCO_TEXTO << " - Voltar ao menu anterior" << RESET << endl;
                    cout << "\n" << NEGRITO << BRANCO_TEXTO << "Escolha a opção desejada: " << RESET;
                    
                    cin >> op1;
                    limparBuffer();
                    
                    switch (op1){
                        case 1:
                            cout << BRANCO_TEXTO << "cadastrar produto x" << RESET << endl; 
                            cout << BRANCO_TEXTO << "Digite a quantidade a ser cadastrada: " << RESET; 
                            cin >> qtd; limparBuffer();
                            cout << BRANCO_TEXTO << "Digite o preço do produto: R$ " << RESET;
                            cin >> preco; limparBuffer();
                            cadastrarProduto("produto x", qtd, preco); 
                            estoque_x += qtd;
                            cout << VERDE_SUCESSO << "Produto X cadastrado!" << RESET << endl;
                            break;
                        case 2:
                            cout << BRANCO_TEXTO << "cadastrar produto y" << RESET << endl; 
                            cout << BRANCO_TEXTO << "Digite a quantidade a ser cadastrada: " << RESET;
                            cin >> qtd; limparBuffer();
                            cout << BRANCO_TEXTO << "Digite o preço do produto: R$ " << RESET;
                            cin >> preco; limparBuffer();
                            cadastrarProduto("produto y", qtd, preco);
                            estoque_y += qtd;
                            cout << VERDE_SUCESSO << "Produto Y cadastrado!" << RESET << endl;
                            break;
                        case 3:
                            cout << BRANCO_TEXTO << "cadastrar produto z" << RESET << endl; 
                            cout << BRANCO_TEXTO << "Digite a quantidade a ser cadastrada: " << RESET;
                            cin >> qtd; limparBuffer();
                            cout << BRANCO_TEXTO << "Digite o preço do produto: R$ " << RESET;
                            cin >> preco; limparBuffer();
                            cadastrarProduto("produto z", qtd, preco);
                            estoque_z += qtd;
                            cout << VERDE_SUCESSO << "Produto Z cadastrado!" << RESET << endl;
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
                    cout << "  " << CIANO_OPCAO << "1" << RESET << BRANCO_TEXTO << " - Verificar estoque do produto x" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "2" << RESET << BRANCO_TEXTO << " - Verificar estoque do produto y" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "3" << RESET << BRANCO_TEXTO << " - Verificar estoque do produto z" << RESET << endl;
                    cout << "  " << AMARELO_AVISO << "4" << RESET << BRANCO_TEXTO << " - Voltar ao menu anterior" << RESET << endl;
                    cout << "\n" << NEGRITO << BRANCO_TEXTO << "Escolha a opção desejada: " << RESET;
                    
                    cin >> op2;
                    limparBuffer();
                    
                    switch (op2){
                        case 1: 
                            cout << BRANCO_TEXTO << "Estoque do produto x é de: " << NEGRITO << VERDE_SUCESSO << verificarEstoque(estoque_x) << RESET << endl; 
                            break;
                        case 2: 
                            cout << BRANCO_TEXTO << "Estoque do produto y é de: " << NEGRITO << VERDE_SUCESSO << verificarEstoque(estoque_y) << RESET << endl; 
                            break;
                        case 3: 
                            cout << BRANCO_TEXTO << "Estoque do produto z é de: " << NEGRITO << VERDE_SUCESSO << verificarEstoque(estoque_z) << RESET << endl; 
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
                    cout << "  " << CIANO_OPCAO << "1" << RESET << BRANCO_TEXTO << " - Vender produto x" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "2" << RESET << BRANCO_TEXTO << " - Vender produto y" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "3" << RESET << BRANCO_TEXTO << " - Vender produto z" << RESET << endl;
                    cout << "  " << AMARELO_AVISO << "4" << RESET << BRANCO_TEXTO << " - Voltar ao menu anterior" << RESET << endl;
                    cout << "\n" << NEGRITO << BRANCO_TEXTO << "Escolha a opção desejada: " << RESET;
                    
                    cin >> op3;
                    limparBuffer();
                    
                    switch (op3){
                        case 1: 
                            cout << BRANCO_TEXTO << "Vender produto x (Estoque: " << AMARELO_AVISO << estoque_x << RESET << BRANCO_TEXTO << ")" << RESET << endl; 
                            cout << BRANCO_TEXTO << "Digite a quantidade a ser vendida: " << RESET; 
                            cin >> qtd; limparBuffer();

                            if(qtd <= estoque_x){
                                estoque_x -= qtd; 
                                cadastrarVenda("Produto X", qtd); 
                                cout << VERDE_SUCESSO << "Venda realizada!" << RESET << endl;
                            } else {
                                cout << VERMELHO_ERRO << "Estoque insuficiente!" << RESET << endl;
                            }
                            break;
                        case 2: 
                            cout << BRANCO_TEXTO << "Vender produto y (Estoque: " << AMARELO_AVISO << estoque_y << RESET << BRANCO_TEXTO << ")" << RESET << endl; 
                            cout << BRANCO_TEXTO << "Digite a quantidade a ser vendida: " << RESET; 
                            cin >> qtd; limparBuffer(); 

                            if(qtd <= estoque_y){
                                estoque_y -= qtd; 
                                cadastrarVenda("Produto Y", qtd); 
                                cout << VERDE_SUCESSO << "Venda realizada!" << RESET << endl;
                            } else {
                                cout << VERMELHO_ERRO << "Estoque insuficiente!" << RESET << endl;
                            }
                            break;
                        case 3: 
                            cout << BRANCO_TEXTO << "Vender produto z (Estoque: " << AMARELO_AVISO << estoque_z << RESET << BRANCO_TEXTO << ")" << RESET << endl; 
                            cout << BRANCO_TEXTO << "Digite a quantidade a ser vendida: " << RESET; 
                            cin >> qtd; limparBuffer();

                            if(qtd <= estoque_z){
                                estoque_z -= qtd; 
                                cadastrarVenda("Produto Z", qtd); 
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
                    cout << "  " << CIANO_OPCAO << "1" << RESET << BRANCO_TEXTO << " - Excluir estoque produto x" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "2" << RESET << BRANCO_TEXTO << " - Excluir estoque produto y" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "3" << RESET << BRANCO_TEXTO << " - Excluir estoque produto z" << RESET << endl;
                    cout << "  " << CIANO_OPCAO << "4" << RESET << BRANCO_TEXTO << " - Excluir nome do vendedor (memória)" << RESET << endl;
                    cout << "  " << VERMELHO_ERRO << "5" << RESET << BRANCO_TEXTO << " - Excluir TUDO (Memória e Arquivo)" << RESET << endl;
                    cout << "  " << AMARELO_AVISO << "6" << RESET << BRANCO_TEXTO << " - Voltar ao menu anterior" << RESET << endl;
                    cout << "\n" << NEGRITO << BRANCO_TEXTO << "Escolha a opção desejada: " << RESET;
                    cin >> op4;
                    limparBuffer();

                    switch (op4){
                        case 1: {estoque_x = 0; cout << VERDE_SUCESSO << "Estoque do produto x excluído!" << RESET << endl;} break; 
                        case 2: {estoque_y = 0; cout << VERDE_SUCESSO << "Estoque do produto y excluído!" << RESET << endl;} break;
                        case 3: {estoque_z = 0; cout << VERDE_SUCESSO << "Estoque do produto z excluído!" << RESET << endl;} break;
                        case 4: {nome[0] = '\0'; cout << VERDE_SUCESSO << "Nome deletado com sucesso!" << RESET << endl;} break; 
                        case 5: {
                            nome[0] = '\0'; estoque_x = 0; estoque_y = 0; estoque_z = 0; 
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
void cadastrarVenda(const char nome_produto[], int qtd) {
    FILE *fp = fopen(ARQUIVO, "a"); 
    if (fp == NULL) {
        cout << VERMELHO_ERRO << "Erro ao abrir o arquivo de vendas!" << RESET << endl;
        return; 
    }
    fprintf(fp, "VENDA: %s, Quantidade: %d\n\n", nome_produto, qtd); 
    fclose (fp);
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