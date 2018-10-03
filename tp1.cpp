#include <iostream>

using Int32 = int;
using Int64 = long;
using Uint32 = unsigned;
using Uint64 = unsigned long;

template <typename T>
T inline distance(const T& p, const T& q){
    return std::abs(q-p);
}

template <>
Uint32 inline distance(const Uint32& p, const Uint32& q){
    return std::abs((Int32)q-(Int32)p);
}

template <>
Uint64 inline distance(const Uint64& p, const Uint64& q){
    return std::abs((Int64)q-(Int64)p);
}

// 5.


template <typename T>
class TInfo{

};






int main(int argc, char const *argv[])
{
    std::cout << distance<double>(8.0, 5.0);
    
    return 0;
}
