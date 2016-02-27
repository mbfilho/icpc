#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 100100
#define LIM 100100
typedef long long ll;
typedef pair<int,int> pii;
#define mp make_pair
#define pb push_back

/*
F[n] -> a resposta da questão para n vertices livres (tirando o 1)
G[n] ->  uma sequencia parecida com F[n], mas que exige que exatamente 1 par de elementos vizinhos sejam iguais

F[n]: vc pega uma sequencia com F[n-1] e insere um elemento na frente. O segundo elemento fica livre. Fica faltando
pegar uma sequencia bugada (G[n-1]) e colocar um dos elementos no meio do par igual. O outro fica na frente

G[n]: vc pega uma sequencia de F[n-1] e coloca 1 par de elementos iguais juntos, nos locais disponiveis. Ou vc pega
uma sequencia bugada e colocar o par de elementos entre os pares de elementos já repetidos.

*/
ll F[N], G[N];

int main(){
	F[1] = 0;
	G[1] = 1;
	
	int n, mod;
	scanf("%d%d", &n, &mod);
	
	fr(i, 2, n){
		F[i] = (i * (((2*i - 2) * F[i-1]) % mod  + G[i-1])) % mod;
		G[i] = (i * (((2*i - 1) * F[i-1]) % mod  + G[i-1]))% mod;
	}
	
	cout << F[n-1] % mod << endl;
}


