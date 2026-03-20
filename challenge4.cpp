#include <vector>
#include <bitset>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <utility>
#include <fstream>
#include <unistd.h>
#include <limits.h>

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

double check(std::string s){
    int score=s.length()*5;
    for(auto p:s){
        if('a'<=p && p<='z')continue;
        if('A'<=p && p<='Z')continue;
        if(p=='.' || p=='!' || p==',' || p==' ')continue;
        score-=5;
    }
    return (double)(score)/(double)(s.length()*5);
}

void solve(std::string s){
    auto hexVec=stringToHex(s);
    std::vector<std::byte> byteVec(hexVec.size()/2);
    for(int i=0;i<hexVec.size();i+=2){
        byteVec[i/2]=std::byte{to_int(hexVec[i])*16+to_int(hexVec[i+1])};
    }

    std::vector<int> freq(256,0);
    double mx=0;
    std::string best="";
    for(int key=0;key<256;key++){
        std::string temp="";
        // std:: cout << key << " ";
        auto _key=std::byte{key};
        for(auto p:byteVec){
            p^=_key;
            // std::cout << char(to_int(p));
            temp+=char(to_int(p));
        }
        // std::cout << std::endl;
        if(check(temp)>mx){
            mx=check(temp);
            best=temp;
        }
    }
    if(mx>0.9)std::cout << best << std::endl;
}

int main(){
    char buffer[PATH_MAX];
    getcwd(buffer, sizeof(buffer));
    std::string bufferStr(buffer);
    std::ifstream MyReadFile(bufferStr+"/challenge4inp.txt");
    std::string myText;

    while (std::getline (MyReadFile, myText)) {
        solve(myText);
    }
    MyReadFile.close();
}