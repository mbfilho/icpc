#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define C 1000100
typedef pair<int,int> pii;
#define mp make_pair
#define pb push_back
#define oo 0x3f
typedef long long ll;

struct no{
	int b, qtd, tipo;
	bool operator<(const no& ot) const{
		if(qtd != ot.qtd) return qtd > ot.qtd;
		int t = tipo == 'H', tot = ot.tipo == 'H';	
		return t > tot;
	}
};

vector<no> pir;

char pd[C];
ll lista[C];//roubo baseado no fato de que sao necessarias no max 6 piramides
	
void faz(){
	memset(pd, 63, sizeof pd);
	pd[0] = 0;
	lista[0] = 0;
	
	rep(x, pir.size()){
		for(int i = C - 1; i >= pir[x].qtd; --i){
			int val = pd[i-pir[x].qtd] + 1;
			if(pd[i] > val && val < 7){
				lista[i] = lista[i-pir[x].qtd] * 320 + x;
				pd[i] = val;
			}else if(pd[i] == val){
				ll novo = lista[i-pir[x].qtd] * 320 + x;
				if(novo < lista[i]) lista[i] = novo;
			}
		}
	}
}

void gera(){

	ll soma = 1;	
	fr(i, 2, 1000){
		soma += i*i;
		if(soma > C) break;
		pir.pb((no) {i, (int) soma, 'H'});
	}
	
	soma = 4;
	for(int i = 4; i < 1000; i += 2){
		soma += i * i;
		if(soma > C) break;
		pir.pb((no) {i, (int) soma, 'L'});
	}
	
	soma = 1;
	for(int i = 3; i < 1000; i += 2){
		soma += i * i;
		if(soma > C) break;
		pir.pb((no) {i, (int) soma, 'L'});
	}
	sort(pir.begin(), pir.end());
}


int main(){
	gera();
	faz();

	int c, caso = 0;
	while(scanf("%d", &c) == 1 && c){
		printf("Case %d:", ++caso);
		
		if(pd[c] >= oo)
			printf(" impossible\n");
		else{
			vector<no> resp;
			ll tmp = lista[c];
			rep(i, pd[c]){
				resp.pb(pir[tmp%320]);
				tmp /= 320;
			}
			for(int i = resp.size() - 1; i >= 0; --i)
				printf(" %d%c", resp[i].b, (char) resp[i].tipo);
			
			printf("\n");
		}
	}
}

