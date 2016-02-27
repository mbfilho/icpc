#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#define N 300000

ll x[N], y[N], z[N], k[N];
char buf[1000];
int prt;

int main(){
	while(1){
		prt = 0;
		char* aux;
		while((aux = gets(buf)) && strlen(buf) > 2){
			sscanf(buf, "%lld %lld %lld", x + prt, y + prt, z + prt );
			k[prt] = (y[prt] - x[prt])/z[prt] + 1;
			y[prt] = z[prt] * (k[prt] - 1) + x[prt];
			
			++prt;
		}
		if(aux && !prt) continue;
		if(!aux && !prt) break;
		
		
		ll ini = 0, fim = 1LL << 33, best;
		while(ini <= fim){
			ll meio = (ini + fim) / 2;
			int cont = 0;
			
			for(int i = 0; i < prt; ++i){
				if(meio - 1 >= y[i]) cont += k[i];
				else if(meio - 1 >= x[i]) cont += (meio - x[i] - 1) / z[i] + 1;
			}
			if((cont % 2) == 0){
				best = meio;
				ini = meio + 1;
			}else
				fim = meio - 1;
		}
		
		int cont = 0;
		for(int i = 0; i < prt; ++i){
			if(best >= x[i] && best <= y[i] && ((best-x[i]) % z[i]) == 0) ++cont;
		}
		
		if(cont % 2)
			printf("%lld %d\n", best, cont);
		else
			printf("no corruption\n");
		
	}	
}


