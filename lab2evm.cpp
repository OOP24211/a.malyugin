#include <iostream>
#include <cstdlib>

using namespace std;

void Swap(int *a, int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void Generate_Array(int N, int *array){
    for(int i=0; i<N; i++){
        array[i]=rand()%100;
    }
}

void BubbleSort(int *array, int N){
    for(int i=0; i<(N-1); i++){
        for(int j=0; j<(N-i-1); j++){
            if (array[j]>array[j+1]){
                Swap(&array[j], &array[j+1]);
            }
        }
    }

}
void Print_Array(int N, int *array){
    for(int i=0; i<N; i++){
        cout << array[i] << " ";
    }
}

int main(void){
    int N;
    cin >> N;
    int *array = new int[N];
    if (!array){
        cout << "ошибка ввода";
        return 1;
    }
    Generate_Array(N, array);
    BubbleSort(array, N);
    Print_Array(N, array);
    delete[] array;
    return 0;
}