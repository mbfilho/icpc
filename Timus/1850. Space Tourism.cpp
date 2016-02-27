#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
typedef pair<int,int> pii;
#define mp make_pair
#define X first
#define Y second
#define N 100100
#define T (2*N)
#define SOMA 1000100
#define LOG 18
#define oo 10000000

int value[N], qual[N], B[N], E[N];
pii planet[N];
int mk[SOMA], caso;
int cont;
int n, d;
int pd[N][LOG];

void calcComps(){
	++caso;
	cont = 0;
	value[0] = 0;
	B[0] = 0;
	
	rep(ind, n){
		int r = planet[ind].second;
		qual[ind] = cont;
		if(mk[r] != caso){
			mk[r] = caso;
			++value[cont];
		}
		if(ind + 1 == n || planet[ind+1].first - planet[ind].first > d){
			E[cont] = ind;
			++caso;
			value[++cont] = 0;
			B[cont] = ind+1;
		}
	}
	
	rep(i, cont) pd[i][0] = value[i];
	
	for(int tam = 1; (1 << tam) <= cont; ++tam){
		rep(i, cont){
			int nt = min(i + (1<<(tam-1)), cont-1);
			pd[i][tam] = max(pd[i][tam-1], pd[nt][tam-1]);
		}
	}
}

int range[N];
void buildRange(){
	memset(mk, -1, sizeof mk);
	
	rep(i, n){
		int r = planet[i].second;
		range[i] = mk[r];
		mk[r] = i;
	}
}

int esq[T], dir[T], tree;
vector<int> num[T];

int build(int no, int x, int y){
	num[no].resize(y-x+1);
	
	if(x != y){
		int mid = (x+y)/2;
		esq[no] = build(tree++, x, mid);
		dir[no] = build(tree++, mid+1, y);
		merge(num[esq[no]].begin(), num[esq[no]].end(), num[dir[no]].begin(), num[dir[no]].end(), num[no].begin());
	}else{
		num[no][0] = range[x];
		esq[no] = dir[no] = -1;
	}
	
	return no;
}

int ini, fim;
int querySeg(int no, int x, int y){
	if(ini > y || fim < x) return 0;
	
	if(ini <= x && fim >= y){
		int qtd = lower_bound(num[no].begin(), num[no].end(), ini) - num[no].begin();
		return qtd;
	}else{
		int mid = (x+y)/2;
		return querySeg(esq[no], x, mid) + querySeg(dir[no], mid+1, y);
	}
}

int queryPd(int x, int y){
	int tam = y - x + 1, maior = 0, xp = 0;
	int nx = x, ny = y;
	while(tam){
		if(tam & 1) maior = max(maior, pd[x][xp]), x += 1 << xp;
		++xp;
		tam >>= 1;
	}
	return maior;
}

int main(){
	int s, q;
	scanf("%d%d%d", &n, &s, &d);
	rep(i, n) scanf("%d%d", &planet[i].first, &planet[i].second);
	sort(planet, planet + n);
	calcComps();
	buildRange();
	tree = 1;
	build(0, 0, n-1);
	scanf("%d", &q);
	
	while(q--){
		int a, b, pa, pb;
		scanf("%d%d", &a, &b);
		
		pa = lower_bound(planet, planet + n, mp(a, -1)) - planet;
		pb = upper_bound(planet, planet + n, mp(b, oo)) - planet - 1;
		if(pa > pb){
			printf("0\n");
			continue;
		}
		int resp = 0;
		if(qual[pb] - 1 >= 1 + qual[pa])
			resp = queryPd(qual[pa]+1, qual[pb]-1);
		
		ini = pa, fim = min(E[qual[pa]], pb);
		resp = max(resp, querySeg(0, 0, n-1));
		
		if(qual[pa] < qual[pb]){
			ini = B[qual[pb]], fim = pb;
			resp = max(resp, querySeg(0, 0, n-1));
		}
		
		printf("%d\n", resp);
	}
}






