#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    bool fl;
    char start;
    char end;
    int weight;       // вес
    int straight;        // ост. поток вперёд
    int back;           // ост. поток назад
};

bool compare(Edge first, Edge second)
{
    if(first.start == second.start)
        return first.end < second.end;
    return first.start < second.start;
}

class Graph
{
private:
    vector <Edge> graph;
    char source;
    char finish;
    int N;
    vector <char> visited;
    vector <char> result;

public:
    Graph()
    {
        cin >> N;
        cin >> source >> finish;
        for(int i = 0; i < N; i++)
        {
            Edge element;
            cin >> element.start >> element.end >> element.weight;
            element.straight = element.weight;
            element.back = 0;
            element.fl = false;
            bool flag = true;
            for(int i = 0; i < graph.size(); i++)                   // заполняет граф рёбрами
            {
                if(graph[i].start == element.end && graph[i].end == element.start)
                {
                    graph[i].back += element.straight;
                    flag = false;
                    graph[i].fl = true;
                    break;
                }
            }
            if(!flag)
                continue;
            graph.push_back(element);
        }
    }

    bool isVisited(char peak)
    {
        for(size_t i = 0; i < visited.size(); i++)
            if(visited[i] == peak)
                return true;
        return false;
    }

    bool Search(char peak, int& min)       // поиск минимальной пропускной способности в потоке
    {
        if(peak == finish)
        {
            result.push_back(peak);
            cout << "\nCurrent flow: ";
            int flow = 0;

            for(int i = 1; i < result.size(); i++)
            {
                for(int j = 0; j < graph.size(); j++)
                {
                    if(graph[j].start == result[i-1] && graph[j].end == result[i])        // пересчёт пропускных способностей
                    {
                        flow += graph[j].straight;
                    }
                    if(graph[j].end == result[i-1] && graph[j].start == result[i])
                    {
                        flow += graph[j].back;
                    }
                }
            }

            for (int k = 0; k < result.size()-1; k++){
                cout << result[k];
            }
            cout << " " << flow;
            cout << "\n\n";
            return true;
        }
        visited.push_back(peak);          // peak - очередная вершина
        for(size_t i(0); i < graph.size(); i++) // проход по графу
        {
            if(peak == graph[i].start)    // если равна вершине-началу очередного ребра
            {
                if(isVisited(graph[i].end) || graph[i].straight == 0){  // если ещё не были в вершине-конце этого ребра или остат. проп. способ. вперёд равна 0
                    if (i != 0){
                     //  cout << "Returning\n";
                    }
                    continue;
                }
                cout << "Next Edge: " << graph[i].start << graph[i].end << "(" << graph[i].straight << ")" << endl;
                result.push_back(graph[i].start);      // вершина-начало добавляется к ответу
                bool flag = Search(graph[i].end, min);       // идёт рекурсия в глубину графа(подаётся вершина-конец этого графа)
                if(flag)        // вернет тру только когда дойдёт до конечной вершины, и только тогда, возвращаясь из рекурсии, зайдёт в этот иф
                {
                   if(graph[i].straight < min)
                       min = graph[i].straight;
                   return true;
                }
                result.pop_back();
            }
            if(peak == graph[i].end)     // если равна вершине-концу очередного ребра
            {
                if(isVisited(graph[i].start) || graph[i].back == 0) { // если ещё не были в вершине-конце этого ребра или остат. проп. способ. назад равна 0
                    if (i != 0){
                    //   cout << "Returning\n";
                    }
                    continue;
                }
                cout << "Next Edge: " << graph[i].end << graph[i].start << "(" << graph[i].back << ")"  << endl;
                result.push_back(graph[i].end);  // вершина-конец добавляется к ответу
                bool flag = Search(graph[i].start, min);
                if(flag)
                {
                    cout << "\n\n";
                   if(graph[i].back < min)
                        min = graph[i].back;
                   return true;
                }
                result.pop_back();
            }
        }
        return false;
    }


    void FFSearch()
    {
        int res = 0;
        int min = 9999;

        while(Search(source, min))
        {
            cout << "\n\nCurrent min :" << min << "\n\n";
            for(int i = 1; i < result.size(); i++)
            {
                cout << "\nRecount:\n";
                for(int j = 0; j < graph.size(); j++)
                {
                    if(graph[j].start == result[i-1] && graph[j].end == result[i])        // пересчёт пропускных способностей
                    {
                        cout << "straight: ";
                        cout << graph[j].start << graph[j].end << "(" << graph[j].straight << " - " << min;
                        graph[j].straight -= min;
                        cout << " = " << graph[j].straight << ")\n";
                        cout << "Back: ";
                        cout << graph[j].end << graph[j].start << "(" << graph[j].back << " + " << min;
                        graph[j].back += min;
                        cout << " = " << graph[j].back << ")\n\n";
                    }
                    if(graph[j].end == result[i-1] && graph[j].start == result[i])
                    {
                        graph[j].straight += min;
                        graph[j].back -= min;
                    }
                }
            }
            res += min;
            visited.clear();
            result.clear();
            min = 9999;
        }

        sort(graph.begin(), graph.end(), compare);
        cout << "\n" << res << endl;
        for(int i = 0; i < graph.size(); i++)
        {
            int peak = max(graph[i].weight - graph[i].straight, 0 - graph[i].back);
            if(graph[i].fl == true)
            {
                if(peak < 0)
                    peak = 0;
                cout << graph[i].start << " " << graph[i].end << " " << peak << endl;
                swap(graph[i].start, graph[i].end);
                swap(graph[i].back, graph[i].straight);
                graph[i].fl = false;
                sort(graph.begin(), graph.end(), compare);
                i--;
            }
            else
            {
                cout << graph[i].start << " " << graph[i].end << " " << peak << endl;
            }
        }
    }
};

int main()
{

    Graph element;
    element.FFSearch();

    return 0;
}

/*
7
a
f
a b 7
a c 6
b d 6
c f 9
d e 3
d f 4
e c 2


19
a
j
a b 2
a c 9
a d 3
a e 5
b e 4
b h 7
c d 8
c f 5
c g 4
d g 6
e g 8
e h 1
e j 6
f g 3
f i 2
g j 4
g i 9
h j 5
i j 8

 */

