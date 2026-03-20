#include <vector>
#include <bitset>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <utility>

int to_int(std::byte b){
    return std::to_integer<int>(b);
}

std::string lookup="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::vector<std::byte> stringToHex(std::string& hex){
    std::vector<std::byte> res(hex.length());
    for(int i=0;i<hex.length();i++){
        if('0'<=hex[i] && hex[i]<='9')res[i]=std::byte{hex[i]-'0'};
        else res[i]=std::byte{hex[i]-'a'+10};
    }
    return res;
}


std::vector<std::byte> hexToB64(std::vector<std::byte>& rawByteVector){
    while(rawByteVector.size()%3)rawByteVector.push_back(std::byte{0});
    std::vector<std::byte> res(2*(rawByteVector.size()/3));
    for(int i=0;i<rawByteVector.size();i+=3){
        res[2*(i/3)]=std::byte{to_int(rawByteVector[i] << 2) + to_int(rawByteVector[i+1] >> 2)};
        res[2*(i/3)+1]=std::byte{to_int((rawByteVector[i+1] & std::byte{3}) << 4) + to_int(rawByteVector[i+2])};
    }
    return res;
}

std::string b64ToString(std::vector<std::byte>& rawByteVector){
    std::string res(rawByteVector.size(),'_');
    for(int i=0;i<rawByteVector.size();i++){
        res[i]=lookup[to_int(rawByteVector[i])];
    }
    return res;
}

std::string hexStrToB64str(std::string s){
    auto byteVec=stringToHex(s);
    auto b64vec=hexToB64(byteVec);
    return b64ToString(b64vec);
}

int main(){
    std::string s;
    std::cin >> s;
    std::cout << hexStrToB64str(s) << std::endl;
}