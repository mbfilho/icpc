#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 200

typedef long long ll;
int n, m;
ll acc[N];
int qtd[N];

int main(){
	ios::sync_with_stdio(false);
	
	while(cin >> n >> m){
		rep(i, n) cin >> qtd[i];
		
		acc[0] = qtd[0] % m;
		ll soma = 0;
		
		fr(i, 1, n){
			acc[i] = 2 * acc[i-1] + qtd[i];
			acc[i] %= m;
		}
		
		for(int i = n - 1; i >= 0; --i){
			if(!i){
				soma += 2*qtd[i]-1;
				break;
			}
			
			if(qtd[i] == 1){
				soma += 2 * acc[i-1] + 1;
				soma %= m;
				break;
			}else{
				soma += 2*acc[i-1] + 2*qtd[i];
				soma %= m;
			}
		}
		
		soma = (soma + m) % m;
		cout << soma << endl;
	}
}


