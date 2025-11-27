#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <vector>
using namespace std;

char lerLetraSegura() {
    string x;
    while (true) {
        cin >> x;
        if (x.size() == 1) {
            char c = toupper(x[0]);
            if (c=='A' || c=='B' || c=='C' || c=='D') return c;
        }
        cout << "Digite apenas A, B, C ou D: ";
    }
}

void salvarRanking(string nome, int pontos, long long tempo) {
    ofstream arq("ranking.txt", ios::app);
    arq << nome << ";" << pontos << ";" << tempo << "\n";
}

void mostrarRanking() {
    ifstream arq("ranking.txt");
    if (!arq) {
        cout << "\nRanking vazio!\n";
        return;
    }

    struct R {
        string nome;
        int pontos;
        long long tempo;
    };

    vector<R> lista;
    string linha;

    while (getline(arq, linha)) {
        size_t p1 = linha.find(';');
        size_t p2 = linha.find(';', p1 + 1);

        R r;
        r.nome = linha.substr(0, p1);
        r.pontos = stoi(linha.substr(p1 + 1, p2 - p1 - 1));
        r.tempo = stoll(linha.substr(p2 + 1));
        lista.push_back(r);
    }

    sort(lista.begin(), lista.end(), [](R a, R b) {
        if (a.pontos != b.pontos) return a.pontos > b.pontos;
        return a.tempo < b.tempo;
    });

    cout << "\n===== RANKING =====\n";
    for (auto &r : lista) {
        cout << r.nome << " - Pontos: " << r.pontos << " - Tempo: " << r.tempo << "s\n";
    }
}

void limparRanking() {
    ofstream arq("ranking.txt");
    cout << "\nRanking limpo!\n";
}

int quiz(int nivel) {
    int pontos = 0;
    char r;

    if (nivel == 1) {
        cout << "\n=== PERGUNTAS FÁCEIS ===\n";

        cout << "\n1) Maior país do mundo?\nA) Brasil\nB) EUA\nC) Rússia\nD) Índia\n";
        r = lerLetraSegura(); pontos += (r=='C');

        cout << "2) Capital da França?\nA) Roma\nB) Paris\nC) Londres\nD) Berlim\n";
        r = lerLetraSegura(); pontos += (r=='B');

        cout << "3) País do samba?\nA) Argentina\nB) Brasil\nC) Chile\nD) Peru\n";
        r = lerLetraSegura(); pontos += (r=='B');

        cout << "4) Maior oceano?\nA) Atlântico\nB) Índico\nC) Pacífico\nD) Ártico\n";
        r = lerLetraSegura(); pontos += (r=='C');

        cout << "5) Hemisfério do Brasil?\nA) Norte\nB) Sul\nC) Leste\nD) Oeste\n";
        r = lerLetraSegura(); pontos += (r=='B');
    }

    else if (nivel == 2) {
        cout << "\n=== PERGUNTAS MÉDIAS ===\n";

        cout << "\n1) Ponto mais profundo do oceano?\nA) Atlântico\nB) Groelândia\nC) Fossa das Marianas\nD) Mar Vermelho\n";
        r = lerLetraSegura(); pontos += (r=='C');

        cout << "2) Timbuktu fica em?\nA) Sudão\nB) Egito\nC) Mali\nD) Argélia\n";
        r = lerLetraSegura(); pontos += (r=='C');

        cout << "3) País sem saída pro mar?\nA) Bolívia\nB) Peru\nC) Canadá\nD) Noruega\n";
        r = lerLetraSegura(); pontos += (r=='A');
    }

    else {
        cout << "\n=== PERGUNTAS DIFÍCEIS ===\n";

        cout << "\n1) Local mais seco do mundo?\nA) Saara\nB) Atacama\nC) Gobi\nD) Antártica\n";
        r = lerLetraSegura(); pontos += (r=='B');

        cout << "2) País com mais lagos naturais?\nA) Rússia\nB) Canadá\nC) EUA\nD) Finlândia\n";
        r = lerLetraSegura(); pontos += (r=='B');
    }

    return pontos;
}

int main() {
    string nome;
    cout << "Digite seu nome: ";
    getline(cin, nome);

    int opc = 0;

    while (opc != 5) {
        cout << "\n===== SISTEMA DE GEOGRAFIA =====\n";
        cout << "Bem-vindo, " << nome << "!\n\n";
        cout << "1 - Fuso horário\n";
        cout << "2 - Quiz\n";
        cout << "3 - Ver Ranking\n";
        cout << "4 - Limpar Ranking\n";
        cout << "5 - Sair\n";
        cout << "Digite: ";
        cin >> opc;

        if (opc == 1) {
            int h;
            cout << "Digite a hora no Brasil (0-23): ";
            cin >> h;
            cout << "Em Portugal são: " << (h + 3) % 24 << "\n";
        }

        else if (opc == 2) {
            int nivel;
            cout << "\n1 - Fácil\n2 - Médio\n3 - Difícil\nEscolha: ";
            cin >> nivel;

            auto ini = chrono::steady_clock::now();
            int pontos = quiz(nivel);
            auto fim = chrono::steady_clock::now();

            long long tempo = chrono::duration_cast<chrono::seconds>(fim - ini).count();

            cout << "\n===== RESULTADO =====\n";
            cout << "Pontuação: " << pontos << "\n";
            cout << "Tempo: " << tempo << "s\n";

            salvarRanking(nome, pontos, tempo);
        }

        else if (opc == 3) mostrarRanking();
        else if (opc == 4) limparRanking();
        else if (opc != 5) cout << "Opção inválida!\n";
    }

    return 0;
}

