#include <iostream> 
#include <cstdlib>
#include <locale.h>
#include <cstdio> 
#include <windows.h> 
#include <cstring> // --- ADICIONADO para utilizar (strstr)

#define ARQUIVO "startup.txt"


using namespace std;

// --- DECLARAÇÕES DAS FUNÇÕES ---
void cadastrarProduto (const char nome_produto[], int qtd, float preco);
int verificarEstoque(int estoque_atual);
void cadastrarVenda(const char nome_produto[], int qtd); // Modificada
void verRelatorioVendas(); // Modificada

// --- INÍCIO DO PROGRAMA ---
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
    char nome[30] = ""; // par asalvar nome do vendedor na exclusão

    // --- VARIÁVEIS DE ESTOQUE ---
    int estoque_x = 0;
    int estoque_y = 0;
    int estoque_z = 0;

    // --- BOAS VINDAS ---
    cout << "Digite seu nome:" << endl;
    cin.getline(nome_usuario, 30);
    cout << "Seja bem vindo(a) " << nome_usuario << endl; 

    system("pause"); 

    // --- LOOP PRINCIPAL DO MENU ---
    do {
        system("cls"); 
        cout << "Startup" << endl;
        cout << "---------------------------" << endl;
        cout << "1 - Cadastrar produto " << endl;
        cout << "2 - Verificar estoque" << endl;
        cout << "3 - Cadastrar venda " << endl;
        cout << "4 - Excluir Dados" << endl; // Renomeado para ficar mais claro
        cout << "5 - Ver Relatório de Vendas" << endl; 
        cout << "6 - Sair do sistema" << endl; 
        cout << "Digite a opção desejada: "; 
        
        cin >> op;
        
        // --- SWITCH PRINCIPAL (CORRIGIDO) ---
        switch (op) {
            
            // --- CASE 1: CADASTRO ---
            case 1: {
                do {
                    system("cls"); 
                    cout << "Cadastro de Produtos " << endl;
                    cout << "-----------------" << endl;
                    cout << "1 - produtos x" << endl;
                    cout << "2 - produtos y" << endl;
                    cout << "3 - produtos z" << endl;
                    cout << "4 - Voltar ao menu anterior" << endl;
                    cout << "Escolha a opção desejada: ";
                    
                    cin >> op1;
                    
                    switch (op1){
                        case 1:
                            cout << "cadastrar produto x" << endl; 
                            cout << "Digite a quantidade a ser cadastrada:"; 
                            cin >> qtd; 
                            cout << "Digite o preço do produto:";
                            cin >> preco;
                            cadastrarProduto("produto x", qtd, preco); 
                            estoque_x += qtd;
                            cout << "Produto X cadastrado!" << endl;
                            break;
                        case 2:
                            cout << "cadastrar produto y" << endl; 
                            cout << "Digite a quantidade a ser cadastrada:";
                            cin >> qtd;
                            cout << "Digite o preço do produto:";
                            cin >> preco;
                            cadastrarProduto("produto y", qtd, preco);
                            estoque_y += qtd;
                            cout << "Produto Y cadastrado!" << endl;
                            break;
                        case 3:
                            cout << "cadastrar produto z" << endl; 
                            cout << "Digite a quantidade a ser cadastrada:";
                            cin >> qtd;
                            cout << "Digite o preço do produto:";
                            cin >> preco;
                            cadastrarProduto("produto z", qtd, preco);
                            estoque_z += qtd;
                            cout << "Produto Z cadastrado!" << endl;
                            break;
                        case 4: 
                            cout << "voltando ao menu anterior" << endl; 
                            break;
                        default: 
                            cout << "opção invalida, tente novamente!" << endl; 
                            break;
                    }
                    system("pause"); 
                } while (op1 != 4);
                break; // Fim do case 1
            } 
            
            // --- CASE 2: VERIFICAR ESTOQUE ---
            case 2:{
                do{
                    system("cls");
                    cout << "Verificar estoque" << endl;
                    cout << "-----------------" << endl;
                    cout << "1 - Verificar estoque do produto x" << endl;
                    cout << "2 - Verificar estoque do produto y" << endl;
                    cout << "3 - Verificar estoque do produto z" << endl;
                    cout << "4 - Voltar ao menu anterior" << endl;
                    cout << "Escolha a opção desejada: ";
                    
                    cin >> op2;
                    
                    switch (op2){
                        case 1: 
                            cout << "Estoque do produto x é de: " << verificarEstoque(estoque_x) << endl; 
                            break;
                        case 2: 
                            cout << "Estoque do produto y é de: " << verificarEstoque(estoque_y) << endl; 
                            break;
                        case 3: 
                            cout << "Estoque do produto z é de: " << verificarEstoque(estoque_z) << endl; 
                            break;
                        case 4: 
                            cout << "voltando ao menu anterior" << endl; 
                            break;
                        default: 
                            cout << "opção invalida, tente novamente!" << endl; 
                            break;
                    }
                    system("pause"); 
                } while (op2 != 4);
                break; // Fim do case 2
            } 
            
            // --- CASE 3: CADASTRAR VENDA ---
            case 3:{
                do{
                    system("cls");
                    cout << "Cadastrar venda" << endl;
                    cout << "-----------------" << endl;
                    cout << "1 - Vender produto x" << endl;
                    cout << "2 - Vender produto y" << endl;
                    cout << "3 - Vender produto z" << endl;
                    cout << "4 - Voltar ao menu anterior" << endl;
                    cout << "Escolha a opção desejada: ";
                    
                    cin >> op3;
                    
                    switch (op3){
                        case 1: 
                            cout << "Vender produto x (Estoque: " << estoque_x << ")" << endl; 
                            cout << "Digite a quantidade a ser vendida:"; 
                            cin >> qtd; 

                            if(qtd <= estoque_x){
                                estoque_x -= qtd; 
                                cadastrarVenda("Produto X", qtd); // Registra a venda
                                cout << "Venda realizada!" << endl;
                            } else {
                                cout << "Estoque insuficiente!" << endl;
                            }
                            break;
                        case 2: 
                             cout << "Vender produto y (Estoque: " << estoque_y << ")" << endl; 
                            cout << "Digite a quantidade a ser vendida:"; 
                            cin >> qtd; 

                            if(qtd <= estoque_y){
                                estoque_y -= qtd; 
                                cadastrarVenda("Produto Y", qtd); // Registra a venda
                                cout << "Venda realizada!" << endl;
                            } else {
                                cout << "Estoque insuficiente!" << endl;
                            }
                            break;
                        case 3: 
                            cout << "Vender produto z (Estoque: " << estoque_z << ")" << endl; 
                            cout << "Digite a quantidade a ser vendida:"; 
                            cin >> qtd; 

                            if(qtd <= estoque_z){
                                estoque_z -= qtd; 
                                cadastrarVenda("Produto Z", qtd); // Registra a venda
                                cout << "Venda realizada!" << endl;
                            } else {
                                cout << "Estoque insuficiente!" << endl;
                            }
                            break;
                        case 4: 
                            cout << "voltando ao menu anterior" << endl; 
                            break;
                        default: 
                            cout << "opção invalida, tente novamente!" << endl; 
                            break;
                    }
                    system("pause"); 
                } while (op3 != 4);
                break; // Fim do case 3
            }
            
            // --- CASE 4: EXCLUIR DADOS (O seu código de exclusão) ---
            case 4:{
                do{
                    system("cls");
                    cout << "Excluir dados" << endl;
                    cout << "-----------------" << endl;
                    cout << "1 - Excluir estoque produto x" << endl;
                    cout << "2 - Excluir estoque produto y" << endl;
                    cout << "3 - Excluir estoque produto z" << endl;
                    cout << "4 - Excluir nome do vendedor (memória)" << endl;
                    cout << "5 - Excluir TUDO (Memória e Arquivo)" << endl;
                    cout << "6 - Voltar ao menu anterior" << endl;
                    cout << "Escolha a opção desejada: ";
                    cin >> op4;

                    switch (op4){
                        case 1: {estoque_x = 0; cout << "Estoque do produto x excluído!" << endl;} break; 
                        case 2: {estoque_y = 0; cout << "Estoque do produto y excluído!" << endl;} break;
                        case 3: {estoque_z = 0; cout << "Estoque do produto z excluído!" << endl;} break;
                        case 4: {nome[0] = '\0'; cout << "Nome deletado com sucesso!" << endl;} break; // Assumindo que 'nome' existe
                        case 5: {
                            // Limpa memória
                            nome[0] = '\0'; estoque_x = 0; estoque_y = 0; estoque_z = 0; 
                            cout << "Todos dados da memória excluídos!" << endl;

                            // Limpa o arquivo 'startup.txt' (produtos E vendas)
                            FILE *arquivoParaLimpar = fopen(ARQUIVO, "w");
                            if (arquivoParaLimpar == NULL) {
                                perror("Erro ao abrir o arquivo para limpeza");
                            } else {
                                fclose(arquivoParaLimpar);
                                cout << "Arquivo '" << ARQUIVO << "' limpo com sucesso!" << endl;
                            }
                            
                            // (Removida a limpeza do ARQUIVO_VENDAS, pois não o estamos a usar)

                        } break;
                        case 6:
                            cout << "Voltando ao menu anterior..." << endl;
                            break;
                        default: 
                            cout << "Opção inválida, tente novamente." << endl;
                            break;
                    }
                    system("pause");
                } while (op4 != 6);
                break; // Fim do case 4
            } 
            
            // --- CASE 5: VER RELATÓRIO ---
            case 5: {
                verRelatorioVendas();
                system("pause");
                break; // Fim do case 5
            }

            // --- CASE 6: SAIR ---
            case 6: {
                cout << "Saindo do sistema..." << endl;
                break; // Fim do case 6
            }

            // --- DEFAULT ---
            default: {
                cout << "Opção inválida, tente novamente." << endl;
                system("pause"); 
                break;
            }

        } // Fim do switch(op)
        
    } while (op != 6); // Loop principal sai com a opção 6
    
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
        cout << "erro ao abir o arquivo para escrita!" << endl;
        return; 
    }
    fprintf(fp, "Nome: %s\nQuantidade: %d\nPreço: %.2f\n\n", nome_produto, qtd, preco);
    fclose (fp);
}

// --- Função para salvar a VENDA no arquivo ---
void cadastrarVenda(const char nome_produto[], int qtd) {
    FILE *fp = fopen(ARQUIVO, "a"); 
    if (fp == NULL) {
        cout << "Erro ao abrir o arquivo de vendas!" << endl;
        return; 
    }
    // Adicionamos "VENDA:" 
    fprintf(fp, "VENDA: %s, Quantidade: %d\n\n", nome_produto, qtd); 
    fclose (fp);
}

// --- Função para LER o relatório de vendas ---
void verRelatorioVendas() {
    system("cls");
    cout << "--- Relatório de Vendas (do " << ARQUIVO << ") ---" << endl;

    FILE *fp = fopen(ARQUIVO, "r"); 
    if (fp == NULL) {
        cout << "Nenhuma atividade registrada ainda." << endl;
        return;
    }
    
    char linha[255]; // Um buffer para ler cada linha
    
    // Lê e imprime cada linha do arquivo até o final
    while (fgets(linha, 255, fp) != NULL) {
        
        // Só imprime a linha se ela contiver a palavra "VENDA:"
        if (strstr(linha, "VENDA:") != NULL) {
            cout << linha;
        }
    }
    
    fclose(fp);
    cout << "\n--- Fim do Relatório ---" << endl;
}