#include <iostream>
#include <math.h>
#include <ctime>
#include <cstdlib>

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
        void inserir(int n){
            heap[qtd] = n;
            ++qtd;
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
        int filhoAEsquerda(int pos){
            return 2*pos+1;
        }
        int filhoADireita(int pos){
            return 2*pos+2;
        }
        void minHeapify(){
            int qtdNosNaoFolhas; //quantidade de nos nao folhas
            if (tamanho % 2 == 0)
                qtdNosNaoFolhas = tamanho/2; 
            else 
                qtdNosNaoFolhas = (tamanho-1)/2;
            for (int pos = qtdNosNaoFolhas-1; pos > -1; --pos){ //para todos nos folhas ira aplicar o auxMinHeapify
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
};



int main(){
    int n;
    cin >> n;
    Heap h(n);
    for(int i = n; i >  0; --i){
        h.inserir(i);
    }
    h.minHeapify();
    h.imprimir();
    return 0;
}
