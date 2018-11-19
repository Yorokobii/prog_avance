#include <iostream>
#include <vector>
#include <new>

template <typename T>
struct Page{
    T* arr;
    int size;
};

template <typename T>
class Mydeck{
    private:
        int arr_size = 10;
        std::vector<Page<T>> pages;
        typename std::vector<Page<T>>::iterator page_it;

    public:
        Mydeck(int _arr_size = 10)
            :arr_size(_arr_size)
        {
            Page<T> page;
            page.arr = new T[arr_size];
            page.size = 0;
            pages.push_back(page);
        };

        ~Mydeck(){
            page_it = std::vector<Page<T>>::begin;
            while(page_it != std::vector<Page<T>>::end){
                delete[] page_it->arr;
            }
        };


}