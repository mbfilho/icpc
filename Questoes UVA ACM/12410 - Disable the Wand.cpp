#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i) 
#define rep(i,n) fr(i,0,n)
#define mp make_pair
typedef long long ll;
typedef pair<ll, ll> pii;


char limite[303], perf[330];
bool mk[33][33][3][7][33][2];
pii pd[33][33][3][7][33][2];

int tam = 32;

pii memo(int no, int k, ll pot, int mod3, int mod7, int ones, bool tight, bool zero){
	if(no == tam){
		if(zero) return mp(0,0);
		if(!mod3 && mod7) {return mp(0,1);}	
		return mp(0,0);
	}
	
	if(!tight && mk[tam-no][k][mod3][mod7][ones][zero])
		return pd[tam-no][k][mod3][mod7][ones][zero];
	
	ll soma = 0, qtd = 0;
	
	rep(dig, 2){
		if(!k && (perf[no] - '0') != dig) continue;
		if(!ones && dig) continue;
		if(tight && dig > (limite[no] - '0')) break;
		
		pii rec = memo(no+1, k - ((perf[no] - '0') != dig), pot>>1, (mod3 + (pot%3) * dig) % 3, (mod7 + (pot%7) * dig) % 7, ones - dig, tight && dig == (limite[no] - '0'), zero && !dig);
		soma += rec.second * (pot * dig) + rec.first;
		qtd += rec.second;
	}
	
	if(!tight){
		mk[tam-no][k][mod3][mod7][ones][zero] = true;
		return pd[tam-no][k][mod3][mod7][ones][zero] = mp(soma,qtd);
	}
	
	return mp(soma, qtd);
}


void faz(ll num, char* resp){
	ll pot = 1LL << (tam-1);
	
	rep(i, tam){
		if(num & pot) resp[i] = '1';
		else resp[i] = '0';
		pot >>= 1;
	}
	resp[tam] = 0;
}

int main(){
	int t;
	scanf("%d", &t);
	cout.sync_with_stdio(false);
	int st, end, maxOne, ideal, k;
	rep(cas, t){
		scanf("%d%d%d%d%d", &st, &end, &maxOne, &ideal, &k);
		k = min(k, tam);
		maxOne = min(maxOne, tam);
		faz(ideal, perf);
		
		memset(mk, false, sizeof mk);
		faz(end, limite); 
		pii rec = memo(0, k, 1LL << (tam-1), 0, 0, maxOne, true, true);
		faz(st-1 >= 0 ? st-1 : 0, limite);
		pii rec2 = memo(0, k, 1LL << (tam-1), 0, 0, maxOne, true, true);
		cout << "Case " << (cas+1) << ": " << (rec.first - rec2.first) << endl;
	}
}


