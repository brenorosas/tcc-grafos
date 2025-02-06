#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Função para calcular a média
double calcularMedia(const vector<double>& dados) {
    double soma = 0.0;
    for (double valor : dados) {
        soma += valor;
    }
    return soma / dados.size();
}

// Função para calcular a mediana
double calcularMediana(vector<double>& dados) {
    sort(dados.begin(), dados.end());
    int n = dados.size();
    if (n % 2 == 0) {
        return (dados[n / 2 - 1] + dados[n / 2]) / 2.0;
    } else {
        return dados[n / 2];
    }
}

// Função para calcular o desvio padrão
double calcularDesvio(const vector<double>& dados, double media) {
    double soma = 0.0;
    for (double valor : dados) {
        soma += (valor - media) * (valor - media);
    }
    return sqrt(soma / dados.size());
}

// Função para calcular o máximo
double calcularMaximo(const vector<double>& dados) {
    return *max_element(dados.begin(), dados.end());
}

// Função para calcular o mínimo
double calcularMinimo(const vector<double>& dados) {
    return *min_element(dados.begin(), dados.end());
}

int main() {
    const string algoritmos[] = {"grasp", "genetic", "memetic"};
    const int numInstancias = 100;
    const int numResultados = 30;

    // Abre o arquivo .out para escrita para todos os algoritmos
    ofstream outputFile("resultado_tempo.out");

    // Escreve o cabeçalho da tabela LaTeX
    // outputFile << "\\begin{sidewaystable}[ht!]" << endl;
    // outputFile << "\\centering" << endl;
    // outputFile << "\\renewcommand{\\arraystretch}{1.0}" << endl;
    // outputFile << "\\resizebox{\\textwidth}{!}{" << endl;
    // outputFile << "\\begin{tabular}{|p{2cm}|c|c|c|c|c|c|c|c|c|}" << endl;
    // outputFile << "\\hline" << endl;
    // outputFile << "\\multirow{2}{2cm}{\\textbf{Inst\\^ancia}} & \\multicolumn{3}{c|}{\\textbf{Grasp}} & \\multicolumn{3}{c|}{\\textbf{Genético}} & \\multicolumn{3}{c|}{\\textbf{Memetic}} \\\\" << endl;
    // outputFile << "\\cline{2-4} \\cline{5-7} \\cline{8-10}" << endl;
    // outputFile << "& \\textbf{M\\'edia} & \\textbf{Mediana} & \\textbf{Desvio Padr\\'ao} & \\textbf{M\\'edia} & \\textbf{Mediana} & \\textbf{Desvio Padr\\'ao} & \\textbf{M\\'edia} & \\textbf{Mediana} & \\textbf{Desvio Padr\\'ao} \\\\" << endl;
    // outputFile << "\\hline" << endl;

    // Loop sobre as instâncias
    for (int instancia = 1; instancia <= numInstancias; ++instancia) {
        // Escrever os resultados de cada instância
        // outputFile << instancia;

        // Loop sobre os algoritmos
        for (const string& algoritmo : algoritmos) {
            vector<double> fitnesses;
            vector<double> millisecondeses;

            // Loop sobre os resultados de cada algoritmo
            for (int resultado = 1; resultado <= numResultados; ++resultado) {
                stringstream arquivoNome;
                arquivoNome << "C:/Users/breno/tcc-grafos/testes/results/" << algoritmo
                            << "/instance" << (instancia < 10 ? "00" : instancia < 100 ? "0" : "") << instancia
                            << "/result" << (resultado < 10 ? "00" : resultado < 100 ? "0" : "") << resultado << ".out";

                ifstream arquivo(arquivoNome.str().c_str());
                if (!arquivo.is_open()) {
                    cerr << "Erro ao abrir o arquivo: " << arquivoNome.str() << endl;
                    continue;
                }

                double fitness, milliseconds;
                arquivo >> fitness >> milliseconds; // O primeiro valor em cada linha é o fitness, o segundo é milliseconds
                fitnesses.push_back(fitness);
                millisecondeses.push_back(milliseconds);
                arquivo.close();
            }

            // Calcular as estatísticas
            double media = calcularMedia(fitnesses);
            double mediana = calcularMediana(fitnesses);
            double desvio = calcularDesvio(fitnesses, media);
            double maximo = calcularMaximo(fitnesses);
            double minimo = calcularMinimo(fitnesses);
            double media_milliseconds = calcularMedia(millisecondeses);

            // Escrever os resultados para o algoritmo
            // outputFile << " & "
            //            << fixed << setprecision(2) << media << " & "
            //            << fixed << setprecision(2) << mediana << " & "
            //            << fixed << setprecision(2) << desvio;
                    //    << fixed << setprecision(2) << maximo << " & "
                    //    << fixed << setprecision(2) << minimo;

            outputFile << "algoritmo: " << algoritmo <<" instancia: " << instancia << " media: " << media_milliseconds << endl;
        }

        // Adiciona o \cline após cada linha de dados
        // outputFile << " \\\\" << endl;
        // outputFile << "\\cline{1-10}" << endl;
    }

    // Finaliza a tabela no arquivo .out
    // outputFile << "\\hline" << endl;
    // outputFile << "\\end{tabular}" << endl;
    // outputFile << "}" << endl;
    // outputFile << "\\caption{Resultados dos 3 algoritmos para N = 500}" << endl;
    // outputFile << "\\end{sidewaystable}" << endl;

    // Fecha o arquivo
    outputFile.close();

    cout << "Arquivo 'todos_algoritmos_estatisticas.out' gerado com sucesso!" << endl;

    return 0;
}
