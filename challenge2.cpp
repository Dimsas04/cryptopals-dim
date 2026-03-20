#include <vector>
#include <bitset>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <utility>

std::string hexLookup="0123456789abcdef";

int to_int(std::byte b){
    return std::to_integer<int>(b);
}

std::vector<std::byte> stringToHex(std::string& hex){
    std::vector<std::byte> res(hex.length());
    for(int i=0;i<hex.length();i++){
        if('0'<=hex[i] && hex[i]<='9')res[i]=std::byte{hex[i]-'0'};
        else res[i]=std::byte{hex[i]-'a'+10};
    }
    return res;
}

std::vector<std::byte> fixedXor(std::vector<std::byte>& v1,std::vector<std::byte>& v2){
    std::vector<std::byte> res(v1.size());
    for(int i=0;i<v1.size();i++){
        res[i]=v1[i]^v2[i];
    }
    return res;
}

std::string hexToStr(std::vector<std::byte>& vec){
    std::string res(vec.size(),'_');
    for(int i=0;i<vec.size();i++){
        res[i]=hexLookup[to_int(vec[i])];
    }
    return res;
}

int main(){
    std::string s1,s2;
    std::cin >> s1 >> s2;
    auto v1=stringToHex(s1);
    auto v2=stringToHex(s2);
    auto v3=fixedXor(v1,v2);
    std::cout << hexToStr(v3) << std::endl;
}