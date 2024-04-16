#include <vector>
#include <utility>
using namespace std;

class Solution {
public:
    // A função maximalPathQuality calcula a qualidade máxima do caminho em um grafo
    int maximalPathQuality(vector<int>& valores, vector<vector<int>>& arestas, int tempoMaximo) {
        int n = valores.size();
        int resultado = valores[0]; // Inicializa o resultado com o valor do nó inicial
        vector<vector<pair<int,int>>> grafo(n); // Matriz de adjacência (lista de adjacência) para representar o grafo

        // Constrói o grafo a partir das informações de arestas
        for(int i = 0; i < arestas.size(); i++) {
            grafo[arestas[i][0]].push_back({arestas[i][1], arestas[i][2]}); // Adiciona a aresta de i para j com o peso
            grafo[arestas[i][1]].push_back({arestas[i][0], arestas[i][2]}); // Adiciona a aresta de j para i com o peso
        }
        
        vector<int> visitados(n, 0); // Vetor para manter o controle dos nós visitados durante a DFS
        dfs(grafo, valores, visitados, resultado, 0, 0, 0, tempoMaximo); // Chama a função de busca em profundidade (DFS)
        return resultado; // Retorna o resultado final, ou seja, a qualidade máxima do caminho
    }
    
    // Função de busca em profundidade (DFS)
    void dfs(vector<vector<pair<int,int>>>& grafo, vector<int>& valores, vector<int>& visitados, int& resultado, int no, int pontuacao, int tempo, int& tempoMaximo) {
        if(tempo > tempoMaximo) // Verifica se o tempo excede o tempo máximo permitido
            return; // Se exceder, retorna sem fazer mais nada
        
        if(visitados[no] == 0) // Se o nó ainda não foi visitado
            pontuacao += valores[no]; // Adiciona o valor do nó à pontuação
        
        visitados[no]++; // Marca o nó como visitado

        if(no == 0) // Se voltamos ao nó inicial
            resultado = max(resultado, pontuacao); // Atualiza o resultado com a pontuação máxima
        
        // Itera sobre todos os vizinhos do nó atual
        for(auto it : grafo[no]) {
            int vizinho = it.first; // Nó vizinho
            int novoTempo = tempo + it.second; // Tempo para alcançar o vizinho
            dfs(grafo, valores, visitados, resultado, vizinho, pontuacao, novoTempo, tempoMaximo); // Chama recursivamente a DFS para o vizinho
        }
        
        visitados[no]--; // Desmarca o nó após a exploração de todos os seus vizinhos
    }
};
