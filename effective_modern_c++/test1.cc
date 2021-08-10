
#include <stddef.h>
#include <stdio.h>

template<typename T,size_t N>
constexpr size_t array_size(T (&) [N]){
    return N;
}

//接受数组,T被推导为数组的引用,包含尺寸信息 --> 在推导函数中获取
template<typename T>
constexpr size_t func(T& t){
    return array_size(t);
}

int main(){
    const char array[] = "hello world";
    int  n = func(array);
    printf("%d\n",n);
}
