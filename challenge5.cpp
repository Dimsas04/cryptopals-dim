#include <vector>
#include <bitset>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <utility>
#include <fstream>
#include <unistd.h>
#include <limits.h>

std::string hexLookup="0123456789abcdef";

int to_int(std::byte b){
    return std::to_integer<int>(b);
}

std::vector<std::byte> encodeStringToHex(std::string s){
    std::vector<std::byte> res(s.length()*2);
    for(int i=0;i<s.length();i++){
        res[2*i]=std::byte{s[i] >> 4};
        res[2*i+1]=std::byte{s[i] & 15};
    }
    return res;
}

std::vector<std::byte> repeatingXor(std::vector<std::byte>& v1,std::vector<std::byte>& v2){
    std::vector<std::byte> res(v1.size());
    for(int i=0;i<v1.size();i++){
        res[i]=v1[i]^v2[i%v2.size()];
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
    std::string key;
    std::cin >> key;

    char buffer[PATH_MAX];
    getcwd(buffer, sizeof(buffer));
    std::string bufferStr(buffer);

    std::ifstream MyReadFile(bufferStr+"/challenge5inp.txt");
    std::string myText,fileText="";
    while (std::getline (MyReadFile, myText)) {
        fileText+=myText;
        fileText+="\n";
    }
    fileText.pop_back();
    auto v1=encodeStringToHex(fileText);
    auto v2=encodeStringToHex(key);
    auto v3=repeatingXor(v1,v2);
    std::cout << hexToStr(v3) << std::endl;
}