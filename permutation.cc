





#include<iostream>

#include<vector>


int factorial(int n){
    if(n == 1)
        return n;
    return n*factorial(n-1);
}


template<typename T>
void swap(T list[],int i,int j){
    T temp = list[i];
    list[i] = list[j];
    list[j] = temp;
}


template<typename T>
void permutation(T list[],int b,int e, std::vector<std::vector<T>>& res){

    static int idx = 0;
    if(b == e){
        for(int i=0;i<e;i++){
            res[idx].push_back(list[i]);
        }
        idx++;
        return ;
    }

    for(int i=b;i<e;i++){
        swap(list,b,i);
        permutation(list,b+1,e,res);
        swap(list,i,b);
    }
}


template<typename T>
void print_vector(const std::vector<T>& v){
    for(const auto& item : v){
        std::cout << item;
    }
    std::cout << std::endl;
}

template<typename T>
void print_vector_vector(const std::vector<std::vector<T>>& v){
    for(const auto& item : v){
        print_vector(item);
    }
    std::cout << std::endl;
}



int main(){
    int n = 4;
    char list[] = {'a','b','c','d'};
    std::vector<std::vector<char>> res(factorial(n));
    permutation(list,0,n,res);
    print_vector_vector(res);
}
