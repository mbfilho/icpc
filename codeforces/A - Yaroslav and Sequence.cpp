#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 500

int n;
bool mk[N];

int bfs(int neg){
	memset(mk, false, sizeof mk);
	mk[neg] = true;
	queue<int> fila;
	fila.push(neg);
	int menor = neg;
	
	while(!fila.empty()){
		int at = fila.front(); fila.pop();
		menor = min(menor, at);
		
		int pos = (2*n-1) - at;
		rep(i, 1+min(at, n)){
			if(n - i > pos) continue;
			
			int nt = (at - i) + (n - i);
			if(mk[nt]) continue;
			mk[nt] = true;
			fila.push(nt);
		}
	}
	
	return menor;
}

int num[N];

int main(){
	scanf("%d", &n);
	int soma;
	int neg = 0;
	rep(i, 2*n-1){
		scanf("%d", num+i);
		if(num[i] < 0) ++neg, num[i] *= -1;
	}
	
	int qtd = bfs(neg);
	sort(num, num+2*n-1);
	soma = 0;	
	rep(i, 2*n-1){
		if(qtd) soma -= num[i], --qtd;
		else soma += num[i];
	}
	printf("%d\n", soma);
}

