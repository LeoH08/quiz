#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <locale>

using namespace std;

// ===============================================
// Limpar tela no Windows
// ===============================================
void limparTela() {
    system("CLS");
}

// ===============================================
// Pausar para o usuário ver a mensagem
// ===============================================
void pausar() {
    cout << "\nPressione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

// ===============================================
// Ler alternativa A/B/C/D
// ===============================================
char lerAlternativa() {
    string s;
    while (true) {
        cin >> s;
        if (s.size() == 1) {
            char c = toupper(s[0]);
            if (c=='A' || c=='B' || c=='C' || c=='D')
                return c;
        }
        cout << "Digite apenas A, B, C ou D: ";
    }
}

// ===============================================
// Estrutura para ranking
// ===============================================
struct Resultado {
    string nome;
    int pontos;
    long tempo;
    string dificuldade;  // "Facil", "Medio", "Dificil"
};

// ===============================================
// Função para salvar ranking
// ===============================================
void salvarRanking(string nome, int pontos, long tempo, string dificuldade) {
    ofstream arq("ranking.txt", ios::app);
    arq << nome << ";" << pontos << ";" << tempo << ";" << dificuldade << "\n";
}

// ===============================================
// Função para carregar ranking
// ===============================================
vector<Resultado> carregarRanking() {
    vector<Resultado> lista;
    ifstream arq("ranking.txt");
    if (!arq) return lista;

    string linha;
    while (getline(arq, linha)) {
        stringstream ss(linha);
        string nome, pontosStr, tempoStr, dificuldade;
        if (!getline(ss, nome, ';')) continue;
        if (!getline(ss, pontosStr, ';')) continue;
        if (!getline(ss, tempoStr, ';')) continue;
        if (!getline(ss, dificuldade, ';')) continue;

        Resultado res;
        res.nome = nome;
        res.pontos = atoi(pontosStr.c_str());
        res.tempo = atol(tempoStr.c_str());
        res.dificuldade = dificuldade;

        lista.push_back(res);
    }

    return lista;
}

// ===============================================
// Mostrar ranking ordenado
// ===============================================
void verRanking() {
    limparTela();
    vector<Resultado> lista = carregarRanking();

    if (lista.empty()) {
        cout << "\nNenhum ranking salvo ainda.\n";
        pausar();
        return;
    }

    auto dificuldadeValor = [](const string& dif) {
        if (dif == "Facil") return 1;
        if (dif == "Medio") return 2;
        if (dif == "Dificil") return 3;
        return 0;
    };

    sort(lista.begin(), lista.end(), [&](const Resultado& a, const Resultado& b) {
        int da = dificuldadeValor(a.dificuldade);
        int db = dificuldadeValor(b.dificuldade);
        if (da != db) return da < db;
        return a.pontos > b.pontos;
    });

    cout << "\n===== RANKING =====\n";
    for (size_t i=0; i < lista.size(); i++) {
        cout << (i+1) << " - " << lista[i].nome << " | Dificuldade: " << lista[i].dificuldade
             << " | Pontos: " << lista[i].pontos
             << " | Tempo: " << lista[i].tempo << "s\n";
    }
    pausar();
}

// ===============================================
// Limpar ranking com senha
// ===============================================
void limparRanking() {
    limparTela();
    cout << "===== APAGAR RANKING =====\n";
    cout << "Digite a senha para apagar o ranking: ";
    string senha;
    cin >> senha;
    cin.ignore();
    if (senha == "89402297") {
        ofstream arq("ranking.txt");
        cout << "\nRanking apagado com sucesso!\n";
    } else {
        cout << "\nSenha incorreta! Ranking nao apagado.\n";
    }
    pausar();
}

// ===============================================
// Estrutura para pergunta
// ===============================================
struct Pergunta {
    string texto;
    string opA, opB, opC, opD;
    char correta;
};

// ===============================================
// Estrutura para respostas erradas
// ===============================================
struct RespostaErrada {
    Pergunta pergunta;
    char respostaUsuario;
};

// ===============================================
// Iniciar quiz com perguntas e registrar erros
// ===============================================
int iniciarQuizComPerguntas(const vector<Pergunta>& perguntas, vector<RespostaErrada>& erros) {
    int pontos = 0;
    char r;
    erros.clear(); // Limpar vetor de erros antes de começar

    for (size_t i = 0; i < perguntas.size(); i++) {
        limparTela();
        cout << "===== PERGUNTA " << i+1 << " =====\n";
        cout << perguntas[i].texto << "\n";
        cout << "A) " << perguntas[i].opA << "\n";
        cout << "B) " << perguntas[i].opB << "\n";
        cout << "C) " << perguntas[i].opC << "\n";
        cout << "D) " << perguntas[i].opD << "\n";

        r = lerAlternativa();

        if (r == perguntas[i].correta) {
            pontos++;
        } else {
            erros.push_back({perguntas[i], r});
        }
    }
    return pontos;
}

// ===============================================
// Funções para perguntas por dificuldade
// ===============================================
vector<Pergunta> perguntasFacil() {
    vector<Pergunta> p;
    p.push_back((Pergunta){"Qual a capital do Brasil?", "Brasília", "Rio de Janeiro", "São Paulo", "Salvador", 'A'});
    p.push_back((Pergunta){"Qual o maior oceano do planeta?", "Atlântico", "Pacífico", "Índico", "Ártico", 'B'}); 
    p.push_back((Pergunta){"Qual continente é o Brasil?", "América do Sul", "América do Norte", "Europa", "Ásia", 'A'}); 
    p.push_back((Pergunta){"Qual país é conhecido por ter a Torre Eiffel?", "Itália", "França", "Espanha", "Alemanha", 'B'}); 
    p.push_back((Pergunta){"Qual é o maior país do mundo em extensão territorial?", "Canadá", "China", "Rússia", "Estados Unidos", 'C'}); 
    p.push_back((Pergunta){"Em qual continente está o Egito?", "África", "Ásia", "Europa", "Oceania", 'A'}); 
    p.push_back((Pergunta){"Qual o maior deserto do mundo?", "Saara", "Gobi", "Kalahari", "Antártico", 'D'}); 
    p.push_back((Pergunta){"Qual rio é o maior em volume de água?", "Nilo", "Amazonas", "Yangtzé", "Mississippi", 'B'}); 
    p.push_back((Pergunta){"Qual país tem a maior população do mundo?", "Índia", "China", "Estados Unidos", "Indonésia", 'A'}); 
    p.push_back((Pergunta){"Qual é a capital da França?", "Paris", "Londres", "Berlim", "Roma", 'A'});
    return p;
}

vector<Pergunta> perguntasMedio() {
    vector<Pergunta> p;
    p.push_back((Pergunta){"Qual é a capital da Austrália?", "Sydney", "Melbourne", "Canberra", "Perth", 'C'}); 
    p.push_back((Pergunta){"Qual país possui a maior quantidade de ilhas?", "Noruega", "Indonésia", "Filipinas", "Suécia", 'D'});
    p.push_back((Pergunta){"Qual é o ponto mais alto da África?", "Kilimanjaro", "Monte Quênia", "Atlas", "Drakensberg", 'A'}); 
    p.push_back((Pergunta){"Qual é o maior lago de água doce do mundo?", "Lago Vitória", "Lago Superior", "Lago Tanganica", "Lago Baikal", 'B'}); 
    p.push_back((Pergunta){"Qual país tem o maior número de fusos horários?", "Rússia", "França", "Estados Unidos", "China", 'B'}); 
    p.push_back((Pergunta){"Qual país é atravessado pelo Trópico de Capricórnio?", "Brasil", "Argentina", "Austrália", "Todas as anteriores", 'D'}); 
    p.push_back((Pergunta){"Qual é a capital da Islândia?", "Reykjavik", "Oslo", "Helsinque", "Copenhague", 'A'}); 
    p.push_back((Pergunta){"Qual é o país com mais fronteiras terrestres?", "China", "Rússia", "Brasil", "Alemanha", 'A'}); 
    p.push_back((Pergunta){"Qual é a capital da Índia?", "Nova Délhi", "Mumbai", "Kolkata", "Chennai", 'A'}); 
    p.push_back((Pergunta){"Qual é o menor país do mundo em área?", "Mônaco", "Nauru", "Vaticano", "San Marino", 'C'});
    return p;
}

vector<Pergunta> perguntasDificil() {
    vector<Pergunta> p;
    p.push_back((Pergunta){"Qual é a capital da Mauritânia?", "Nouakchott", "Bamako", "Nairobi", "Dakar", 'A'});
    p.push_back((Pergunta){"Qual é a maior ilha do Mediterrâneo?", "Sicília", "Sardenha", "Chipre", "Creta", 'A'}); 
    p.push_back((Pergunta){"Qual é o deserto mais frio do mundo?", "Gobi", "Karakum", "Antártico", "Atacama", 'C'});
    p.push_back((Pergunta){"Qual é o maior país da América Central em território?", "Guatemala", "Honduras", "Nicarágua", "Panamá", 'C'}); 
    p.push_back((Pergunta){"Qual é o rio mais longo da Europa?", "Danúbio", "Volga", "Reno", "Tâmisa", 'B'});
    p.push_back((Pergunta){"Qual é a capital do Uzbequistão?", "Tashkent", "Bishkek", "Ashgabat", "Dushanbe", 'A'}); 
    p.push_back((Pergunta){"Qual país possui a maior quantidade de lagos naturais?", "Canadá", "Finlândia", "Rússia", "Suécia", 'A'});
    p.push_back((Pergunta){"Qual montanha é conhecida como 'Topo do Mundo'?", "Everest", "K2", "Kangchenjunga", "Lhotse", 'A'});
    p.push_back((Pergunta){"Qual é a capital do Camboja?", "Vientiane", "Phnom Penh", "Bangkok", "Hanoi", 'B'});
    p.push_back((Pergunta){"Qual país não faz fronteira com o Brasil?", "Uruguai", "Chile", "Venezuela", "Peru", 'B'});
    return p;
}

// ===============================================
// Estrutura para fuso horario
// ===============================================
struct Pais {
    string nome;
    int difHora;
    int difMin;
};

vector<Pais> criarListaPaises() {
    vector<Pais> lista;
    lista.push_back({"Portugal", 3,0});
    lista.push_back({"Japao", 12,0});
    lista.push_back({"EUA - Nova York",-1,0});
    lista.push_back({"Australia - Sydney",13,0});
    lista.push_back({"Reino Unido",3,0});
    lista.push_back({"India",8,30});
    lista.push_back({"Argentina",0,0});
    lista.push_back({"Mexico",-3,0});
    lista.push_back({"Africa do Sul",5,0});
    lista.push_back({"China",11,0});
    return lista;
}

// ===============================================
// Mostrar fuso horário
// ===============================================
void mostrarFuso() {
    limparTela();
    vector<Pais> paises = criarListaPaises();

    cout << "===== FUSO HORARIO =====\n";
    for (size_t i = 0; i < paises.size(); i++) {
        cout << i+1 << " - " << paises[i].nome 
             << " (Dif: " << paises[i].difHora;
        if(paises[i].difMin>0) cout << "h30";
        else cout << "h";
        cout << ")\n";
    }

    cout << "\nEscolha o pais: ";
    int opc;
    cin >> opc;
    cin.ignore();
    if(opc < 1 || opc > (int)paises.size()){
        cout << "Opcao invalida!\n";
        pausar();
        return;
    }

    Pais p = paises[opc-1];
    time_t agora = time(NULL);
    tm *info = localtime(&agora);

    int hBrasil = info->tm_hour;
    int mBrasil = info->tm_min;
    int h = hBrasil + p.difHora;
    int m = mBrasil + p.difMin;

    if(m>=60){ m-=60; h++; }
    while(h<0) h+=24;
    while(h>=24) h-=24;

    cout << "\nHorario em Brasilia: " << hBrasil << ":" << (mBrasil<10?"0":"") << mBrasil << "\n";
    cout << "Horario em " << p.nome << ": " << h << ":" << (m<10?"0":"") << m << "\n";
    pausar();
}

// ===============================================
// MAIN
// ===============================================
int main() {
    setlocale(LC_ALL,"Portuguese");
    limparTela();
    string nome;
    cout << "===== BEM-VINDO AO QUIZ GEOGRAFIA =====\n";
    cout << "Digite seu nome: ";
    getline(cin,nome);

    while (true) {
        limparTela();
        cout << "===== MENU PRINCIPAL =====\n";
        cout << "Ola, " << nome << "!\n\n";
        cout << "1 - Fuso horario\n";
        cout << "2 - Iniciar Quiz\n";
        cout << "3 - Ver Ranking\n";
        cout << "4 - Limpar Ranking\n";
        cout << "5 - Sair\n";
        cout << "Escolha: ";

        string entrada;
        getline(cin, entrada);

        if (entrada.size() != 1 || entrada[0] < '1' || entrada[0] > '5') {
            cout << "Opcao invalida!\n";
            pausar();
            continue;
        }

        int opc = entrada[0] - '0';

        if (opc == 1) mostrarFuso();
        else if (opc == 2) {
            limparTela();
            cout << "===== ESCOLHA A DIFICULDADE =====\n";
            cout << "1 - Facil\n2 - Medio\n3 - Dificil\nEscolha: ";

            string diffEntrada;
            getline(cin, diffEntrada);
            if (diffEntrada.size() != 1 || diffEntrada[0] < '1' || diffEntrada[0] > '3') {
                cout << "Dificuldade invalida!\n";
                pausar();
                continue;
            }

            int diff = diffEntrada[0]-'0';
            vector<Pergunta> perguntas;
            string difTexto;
            if(diff==1){ perguntas = perguntasFacil(); difTexto="Facil"; }
            else if(diff==2){ perguntas = perguntasMedio(); difTexto="Medio"; }
            else{ perguntas = perguntasDificil(); difTexto="Dificil"; }

            vector<RespostaErrada> erros;
            time_t inicio = time(NULL);
            int pontos = iniciarQuizComPerguntas(perguntas, erros);
            time_t fim = time(NULL);
            long tempo = long(fim-inicio);

            limparTela();
            cout << "===== RESULTADO DO QUIZ =====\n";
            cout << "Dificuldade: " << difTexto << "\n";
            cout << "Pontuacao: " << pontos << "/" << perguntas.size() << "\n";
            cout << "Tempo: " << tempo << "s\n";

            if (!erros.empty()) {
                cout << "\n===== QUESTOES ERRADAS =====\n";
                for (size_t i = 0; i < erros.size(); i++) {
                    Pergunta q = erros[i].pergunta;
                    cout << "\nPergunta: " << q.texto << "\n";
                    cout << "Sua resposta: " << erros[i].respostaUsuario;
                    switch(erros[i].respostaUsuario) {
                        case 'A': cout << ") " << q.opA; break;
                        case 'B': cout << ") " << q.opB; break;
                        case 'C': cout << ") " << q.opC; break;
                        case 'D': cout << ") " << q.opD; break;
                    }
                    cout << "\nResposta correta: " << q.correta;
                    switch(q.correta) {
                        case 'A': cout << ") " << q.opA; break;
                        case 'B': cout << ") " << q.opB; break;
                        case 'C': cout << ") " << q.opC; break;
                        case 'D': cout << ") " << q.opD; break;
                    }
                    cout << "\n";
                }
            }

            salvarRanking(nome, pontos, tempo, difTexto);
            pausar();
        }
        else if(opc==3) verRanking();
        else if(opc==4) limparRanking();
        else if(opc==5) break;
    }

    limparTela();
    cout << "Obrigado por jogar, " << nome << "! Ate mais!\n";
    return 0;
}
