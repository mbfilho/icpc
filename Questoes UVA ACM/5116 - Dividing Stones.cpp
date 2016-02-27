#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;



int primos[80], prt;
bool crivo[80];

void pre(){
	primos[0] = 1;
	prt = 1;
	for(int i = 1; i < 80; ++i) crivo[i] = true;
	crivo[0] = false;
	
	for(int i = 2; i < 80; ++i){
		for(int j = 2; crivo[i] && j < i; ++j){
			if(i % j == 0) crivo[i] = false;
		}
		if(crivo[i]) primos[prt++] = i;
	}

}

set<int> conj;
int MOD;

void rec(int soma, int acc, int maior, int mod){
	if(!soma && !acc) conj.insert(mod);
	if(!soma) return;
	
	if(crivo[acc+1] && acc + 1 >= maior){
		ll tmp = (mod * ll(acc+1)) % MOD;
		rec(soma - 1, 0, max(maior, acc+1), (int) tmp);
	}
	
	rec(soma - 1, acc + 1, maior, mod);
}

int main(){
	pre();
	int t;
	scanf("%d", &t);
	
	while(t--){
		int n;
		scanf("%d%d", &n, &MOD);
		conj.clear();
		
		rec(n, 0, 0, 1);
		
		printf("%d\n", conj.size());
	}
}






