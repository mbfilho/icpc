#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 1000001
#define pb push_back
#define MOD 1300031
typedef long long ll;

/*
O numero a ser somado eh uma sequencia de 1's
Então, uma solução valida eh:
	11(x_0)11(x_1)11111(x_2)
assumindo que x_0 = 2, x_1 = 2, x_2 = 5
Isso pode ser calculado como uma permutação com repeticoes. Tomar cuidado porque 
o ultimo elemento da permutação deve ser uma variável. Por isso, a permutação tem
N+C-1 elementos e C elementos 1's repetidos e (N-1) elementos X repetidos,
pois uma das variaveis eh fixada no final da sequencia.
*/
inline int euclides(int a, int b){
	int x2 = 1, y2 = 0;
	int x1 = 0, y1 = 1;
	int aa = a, bb = b;
	
	while(b){
		int mod = a % b;
		int quo = a / b;
		
		int tx = x2 - quo * x1;
		x2 = x1; x1 = tx;
		
		int ty = y2 - quo * y1;
		y2 = y1; y1 = ty;
		
		a = b;
		b = mod;
	}	
	return (x2 % MOD);
}

int inve[2*N];
ll fat[2*N];
int main(){
	int t, c, n;
	fat[0] = 1;
	fr(i, 1, 2*N) inve[i] = euclides(i, MOD),fat[i] = (i * fat[i-1])% MOD;
	
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &c);
		ll soma = fat[n+c-1] * inve[(fat[c] * fat[n-1]) % MOD];
		printf("%d\n", int(soma%MOD + MOD) % MOD);
	}	
}



