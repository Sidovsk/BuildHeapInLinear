#include <iostream>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

class Heap{
    private:
        int* heap;
        int tamanho;
        int qtd;
    
    public:
        Heap(int n){
            heap = new int[n];
            tamanho = n;
            qtd = 0;
        }
        ~Heap(){
            delete[] heap;
        }
        void imprimir(){
            for(int i = 0; i < tamanho; ++i){
                cout << heap[i] << endl;
            }
        }
        void swap(int& a, int& b){
            int aux = a;
            a = b;
            b = aux;
        }
        //conta que nao recebera valor de raiz
        int pai(int pos){
            if(pos % 2 == 0)
                return (pos/2) -1;
            return pos/2;
        }
        int filhoAEsquerda(int pos){
            return 2*pos+1;
        }
        int filhoADireita(int pos){
            return 2*pos+2;
        }
        //construcao do heap otimizado utiliza os dois seguintes metodos
        void inserir(int n){
            heap[qtd] = n;
            ++qtd;
        }

        //heapify, neste caso corrigeDescendo
        void minHeapify(){
            int qtdNosNaoFolhas = tamanho/2; //quantidade de nos nao folhas
            for (int pos = qtdNosNaoFolhas-1; pos > -1; --pos){ //para todos nos NAO    folhas ira aplicar o auxMinHeapify
                int pai = pos;
                int i = filhoAEsquerda(pai);
                bool terminou = false;
                while((i <= tamanho-1) and !(terminou)){
                    if ((i < tamanho-1) and (heap[i] > heap[i+1]))
                        i = i+1;
                    if (heap[pai] <= heap[i])
                        terminou = true; //termina while
                    else {
                        swap(heap[pai], heap[i]);
                        pai = i;    
                        i = filhoAEsquerda(pai); //i <- 2*i+1
                    }
                }
            }
        }

        //construcao do heap comum utiliza o seguinte metodo
        void inserirHeapNormal(int n){
            heap[qtd] = n;
            ++qtd;
            //heapify neste caso, corrigeSubindo
            int i = qtd-1; //posicao de n
            int p = pai(i);
            while(i >= 1 and heap[p] > heap[i]){
                swap(heap[p], heap[i]);
                i = p;
                p = pai(i);
            }
        }
};



int main(){
    cout << "Digite a opcao de teste desejada: \n1. Teste com numeros randomicos (Heap otimizada) \n2. Teste no pior caso (Heap Otimizada)\n" 
         << "3. Teste com numeros randomicos (Heap comum)\n4. Teste no pior caso (Heap Comum)" << endl;
    int op;
    cin >> op;
    string fileName;
    
    if (op == 1)
        fileName = "tp1.txt";
    else if (op == 2)
        fileName = "tp2.txt";
    else if (op == 3)
        fileName = "tp3.txt";
    else 
        fileName = "tp4.txt";
    
    ofstream file(fileName);
    if(file.good()){
        if (op == 1){ 
            for (int i = 0; i < 1500000; i += 100){
                srand(time(0));
                clock_t inicioExec = clock(); //calculando tempo do buildHeap
                Heap h(i);
                for(int j = 1; j < i+1; ++j){
                    h.inserir(rand());
                }
                h.minHeapify();
                clock_t tempoTotal = clock() - inicioExec;
                inicioExec += tempoTotal;
                file << i << ", "<< (double)tempoTotal/CLOCKS_PER_SEC << '\n';
            }
        } else if (op == 2){
            for (int i = 5; i < 1500000; i += 100){
                srand(time(0));
                clock_t inicioExec = clock(); //calculando tempo do buildHeap
                Heap h(i);
                for(int j = i; j > -1; --j){
                    h.inserir(j);
                }
                h.minHeapify();
                clock_t tempoTotal = clock() - inicioExec;
                inicioExec += tempoTotal;
                file << i << ", "<< (double)tempoTotal/CLOCKS_PER_SEC << '\n';
            }
        } else if (op == 3){
            for (int i = 5; i < 1500000; i += 100){
                srand(time(0));
                clock_t inicioExec = clock(); //calculando tempo do buildHeap
                Heap h(i);
                for(int j = 1; j < i+1; ++j){
                    h.inserirHeapNormal(rand());
                }
                clock_t tempoTotal = clock() - inicioExec;
                inicioExec += tempoTotal;
                file << i << ", "<< (double)tempoTotal/CLOCKS_PER_SEC << '\n';
            }
        } else if (op == 4){
            for (int i = 5; i < 1500000; i += 100){
                srand(time(0));
                clock_t inicioExec = clock(); //calculando tempo do buildHeap
                Heap h(i);
                for(int j = i; j > -1; --j){
                    h.inserirHeapNormal(j);
                }
                clock_t tempoTotal = clock() - inicioExec;
                inicioExec += tempoTotal;
                file << i << ", "<< (double)tempoTotal/CLOCKS_PER_SEC << '\n';
            }
        }
    }  
    file.close();
    return 0;
}
