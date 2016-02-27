#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define X first
#define Y second
#define N 16
#define mp make_pair
#define pb push_back
#define B 1097
typedef unsigned long long hash;
using namespace std;

int n;
char words[N][50];
hash nos[100][40];
int match[100][100];
int size[100];
hash pot[50];

hash get(int i, int ini, int fim){
	i = max(i, i - n);
	
	hash aux = ini == 0 ? 0 : nos[i][ini-1];
	
	return nos[i][fim] - aux * pot[fim-ini+1];
}

vector<int> mot;

bool exc[100];
void pre(){
	mot.clear();
	memset(exc, false, sizeof exc);
	memset(match, 0, sizeof match);
	memset(nos, 0, sizeof nos);
	pot[0] = 1;
	for(int i = 1; i < 50; ++i) pot[i] = B * pot[i-1];
	for(int i = 0; i < n; ++i){
		size[i] = size[i+n] = strlen(words[i]);
		
		nos[i][0] = words[i][0];
		for(int j = 1; j < size[i]; ++j){
			nos[i][j] = nos[i][j-1] * B + words[i][j];
		}
		
		nos[i+n][0] = words[i][size[i]-1];
		for(int j = 1; j < size[i]; ++j)
			nos[i+n][j] = nos[i+n][j-1] * B + words[i][size[i]-1-j];
	}
	
	for(int i = 0; i < 2*n; ++i){
		for(int j = 0; j < 2*n; ++j){
			if(j != i + n && i != j + n && i != j && !exc[i] && !exc[j]){
				int a = i, b = j;
				if(size[i] > size[j]) swap(a,b);
				for(int k = 0; k + size[a] <= size[b]; ++k){
					if(get(b, k, k+size[a]-1) == get(a,0,size[a]-1)){
						exc[a] = true;
						if(a>=n) exc[a-n] = true;
						else exc[a+n] = true;
						break;
					}
				}
			}
			
			for(int k = 1; k <= min(size[i], size[j]); ++k){
				hash suf = get(i, size[i] - k, size[i] - 1);
				hash pre = get(j, 0, k-1);
				if(suf == pre) match[i][j] = k;
			}
			
			int a = i, b = j;
			if(a >= n) a = a -= n;
			if(b>=n) b = b -= n;
		}
	}
	for(int i = 0; i < n; ++i){
		if(!exc[i])
			mot.pb(i);//, printf( "> %s\n", words[i]);
	}
}
int pd[1<<N][N][2];
int dois[20];

struct Trio{
	int mask, last, inv;
	Trio(int a, int b, int c):mask(a), last(b), inv(c){}
	Trio(){}
};
Trio fila[(1<<N) * N * 2];
Trio pred[1<<N][N][2];

int prt;
char buf[10000];
void montar(int mask, int at, int inv){
	Trio ant = pred[mask][at][inv];
	if(ant.mask == 0){
		if(inv){
			for(prt = 0; prt < size[at]; ++prt) buf[prt] = words[at][size[at] - prt - 1];
		}else{
			for(prt = 0; prt < size[at]; ++prt) buf[prt] = words[at][prt];
		}
	}else{
		montar(ant.mask, ant.last, ant.inv);
		for(int i = match[ant.last + ant.inv*n][at + inv*n]; i < size[at]; ++i){
			if(inv)
				buf[prt++] = words[at][size[at] - 1 - i];
			else
				buf[prt++] = words[at][i];
		}
	}
}

void faz(){
	int ini = 0, fim = -1;
	memset(pd, 0, sizeof pd);
	
	for(int i = 0; i < mot.size(); ++i){
		int at = mot[i];
		fila[++fim] = Trio(dois[at], at, 0);
		fila[++fim] = Trio(dois[at], at, 1);
		pd[dois[at]][at][0] = pd[dois[at]][at][1] = size[at];
		
		pred[dois[at]][at][0] = Trio(0,0,0);
		pred[dois[at]][at][1] = Trio(0,0,0);
	}
	
	while(ini <= fim){
		int mask = fila[ini].mask;
		int last = fila[ini].last;
		int inv = fila[ini++].inv;
		for(int i = 0; i < mot.size(); ++i){
			int at = mot[i];
			if(dois[at] & mask) continue;
			if(!pd[dois[at]|mask][at][0]){
				fila[++fim] = Trio(dois[at]|mask, at, 0);
			}
			if(!pd[dois[at]|mask][at][1]){
				fila[++fim] = Trio(dois[at]|mask, at, 1);
			}
			if(!pd[mask|dois[at]][at][0] || pd[mask|dois[at]][at][0] > pd[mask][last][inv] + size[at] - match[last+inv*n][at]){
				pd[mask|dois[at]][at][0] = pd[mask][last][inv] + size[at] - match[last+inv*n][at];
				pred[mask|dois[at]][at][0] = Trio(mask, last, inv);
			}
			
			if(!pd[mask|dois[at]][at][1] || pd[mask|dois[at]][at][1] > pd[mask][last][inv] + size[at] - match[last + inv*n][at + n]){
				pd[mask|dois[at]][at][1] = pd[mask][last][inv] + size[at] - match[last + inv*n][at + n];
				pred[mask|dois[at]][at][1] = Trio(mask, last, inv);
			}
		}
	}
	
	int mask = fila[fim].mask;
	int best = 1000000;
	int palavra = -1;
	int sentido;
	for(int i = 0; i < mot.size(); ++i){
		int at = mot[i], tam = size[at];
		int c0 = pd[mask][at][0], c1 = pd[mask][at][1];
		if(c0){
			if(best > 2 * c0 - match[at][at+n]){
				best = 2 * c0 - match[at][at+n];
				palavra = at;
				sentido = 0;
			}
		}
		
		if(c1){
			if(best > 2*c1 - match[at+n][at]){
				best = 2*c1 - match[at+n][at];
				palavra = at+n;
				sentido = 1;
			}
		}
	}
	montar(mask, palavra - sentido*n, sentido);
	buf[prt] = 0;
	int inverso = palavra + n;
	if(palavra >= n) inverso = palavra - n;
	int tam = prt;
	buf[prt] = 0;
	for(int i = tam - match[palavra][inverso] - 1; ~i ; --i) buf[prt++] = buf[i];
	buf[prt] = 0;
}

int main(){

	dois[0] = 1;
	for(int i = 1; i < 20; ++i) dois[i] = 2 * dois[i-1];
	
	scanf("%d", &n);
		
	for(int i = 0; i < n; ++i){
		scanf("%s", words[i]);
	}
	pre();
	faz();
	printf( "%s\n", buf );
}



