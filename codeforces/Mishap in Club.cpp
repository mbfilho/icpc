#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)

char buf[1000];

int maior, tam;
bool faz(int saldo){
    maior = saldo;
    rep(i, tam){
        if(buf[i] == '+') ++saldo;
        else --saldo;
        if(saldo < 0) return false;
        maior = max(maior, abs(saldo));
    }
    return true;
}

int main(){
    scanf("%s", buf);
    tam = strlen(buf);
    
    fr(i, 0, tam+1){
        if(faz(i)) break;
    }
    
    printf("%d\n", maior);
    
}
