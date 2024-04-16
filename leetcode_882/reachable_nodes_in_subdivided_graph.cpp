#include <vector>
#include <queue>
#include <utility> // Para usar pair
#include <algorithm> // Para usar min
using namespace std;

class Solution {
public:
    // Função para contar os nós alcançáveis a partir do nó 0
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int numOfNodes) {
        // Lista de adjacência para representar o grafo
        vector<vector<pair<int, int>>> adjacencyList(numOfNodes);
        // Vetor para armazenar as distâncias mínimas de 0 até cada nó
        vector<int> distances(adjacencyList.size(), maxMoves + 1);

        // Preenche a lista de adjacência com as arestas e seus respectivos pesos
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cnt = edge[2];
            // Adiciona a aresta u-v com peso cnt na lista de adjacência
            adjacencyList[u].emplace_back(v, cnt);
            adjacencyList[v].emplace_back(u, cnt); // Como é um grafo não direcionado, adicionamos v-u também
        }

        // Calcula quantos nós podem ser alcançados a partir do nó 0
        int reachableNodes = calculateReachableNodes(adjacencyList, 0, maxMoves, distances);
        // Inicializa a contagem de nós alcançáveis nas subarestas
        int reachableSubnodes = 0;

        // Itera sobre todas as arestas para contar os nós alcançáveis nas subarestas
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cnt = edge[2];
            // Calcula quantos nós são alcançáveis na subaresta u-v
            int a = distances[u] > maxMoves ? 0 : min(maxMoves - distances[u], cnt);
            int b = distances[v] > maxMoves ? 0 : min(maxMoves - distances[v], cnt);
            // Adiciona o número de nós alcançáveis na subaresta u-v ao total de nós alcançáveis nas subarestas
            reachableSubnodes += min(a + b, cnt);
        }

        // Retorna o total de nós alcançáveis
        return reachableNodes + reachableSubnodes;
    }

private:
    // Função para calcular os nós alcançáveis a partir de um nó de origem usando Dijkstra
    int calculateReachableNodes(const vector<vector<pair<int, int>>>& graph, int source,
                                int maxMoves, vector<int>& distances) {
        // Fila de prioridade mínima para o algoritmo de Dijkstra
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

        // Inicializa as distâncias do nó de origem como 0
        distances[source] = 0;
        // Adiciona o nó de origem à fila de prioridade
        minHeap.emplace(distances[source], source);

        // Executa o algoritmo de Dijkstra para calcular as distâncias mínimas
        while (!minHeap.empty()) {
            auto [d, u] = minHeap.top();
            minHeap.pop();
            for (const auto& [v, w] : graph[u]) {
                // Relaxa a aresta e atualiza a distância mínima se necessário
                if (d + w + 1 < distances[v]) {
                    distances[v] = d + w + 1;
                    minHeap.emplace(distances[v], v);
                }
            }
        }

        // Conta quantos nós são alcançáveis dentro do limite de maxMoves
        return countIfReachable(distances, maxMoves);
    }

    // Função auxiliar para contar quantos nós são alcançáveis dentro do limite de maxMoves
    int countIfReachable(const vector<int>& distances, int maxMoves) {
        int reachableCount = 0;
        // Itera sobre todas as distâncias e conta quantas estão dentro do limite de maxMoves
        for (int d : distances) {
            if (d <= maxMoves) {
                reachableCount++;
            }
        }
        // Retorna o número total de nós alcançáveis
        return reachableCount;
    }
};