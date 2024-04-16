#include <vector>  // Inclui a biblioteca para usar vetores
#include <queue>   // Inclui a biblioteca para usar filas
using namespace std;  // Permite usar nomes de funções da biblioteca padrão sem prefixo

class Solution {  // Define uma classe chamada Solution
public:
    // Função para percorrer o grafo utilizando BFS e verificar se é bipartido
    bool bfs(int node, vector<vector<int>>& graph, vector<int>& colors) {
        queue<int> q;  // Cria uma fila para BFS
        colors[node] = 0;  // Atribui a cor 0 ao nó inicial
        q.push(node);  // Adiciona o nó inicial à fila
        while (!q.empty()) {  // Enquanto a fila não estiver vazia
            int current = q.front();  // Pega o primeiro nó da fila
            q.pop();  // Remove o primeiro nó da fila
            for (int adjacent : graph[current]) {  // Para cada nó adjacente ao nó atual
                if (colors[adjacent] == -1) {  // Se o nó adjacente não estiver colorido
                    colors[adjacent] = !colors[current];  // Atribui a cor oposta ao nó adjacente
                    q.push(adjacent);  // Adiciona o nó adjacente à fila
                } else if (colors[adjacent] == colors[current]) {  // Se o nó adjacente tiver a mesma cor do nó atual
                    return false;  // Retorna falso, pois o grafo não é bipartido
                }
            }
        }
        return true;  // Se não houver conflitos, o grafo é bipartido
    }

    // Função principal para verificar se o grafo é bipartido
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();  // Obtém o número de nós no grafo
        vector<int> colors(n, -1);  // Cria um vetor de cores, inicializado como não colorido (-1)
        for (int i = 0; i < n; ++i) {  // Para cada nó no grafo
            if (colors[i] == -1 && !bfs(i, graph, colors)) {  // Se o nó não estiver colorido e não for bipartido
                return false;  // Retorna falso
            }
        }
        return true;  // Se todas as componentes conexas forem bipartidas, retorna verdadeiro
    }
};