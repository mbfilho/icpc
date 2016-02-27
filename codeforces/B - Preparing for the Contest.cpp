#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define mp make_pair
#define ability first.first
#define cost first.second
#define complexity first
#define id second

typedef pair<int,int> pii;
typedef pair<pii, int> ppi;
#define N 100100

int n, m, s;
pii bug[N];
ppi stu[N];
int resp[N], aux[N];

// (LogM) * (N*LogN)

bool pode(int dias){	
	int d = m-1, soma = 0, cont = n - 1;
	priority_queue<pii> heap;
	
	while(d >= 0){
		while(cont >= 0 && stu[cont].ability >= bug[d].complexity)
			heap.push(mp(-stu[cont].cost, stu[cont].id)), --cont;
			
		if(heap.empty()) return false;
		pii best = heap.top();
		best.complexity *= -1;

		heap.pop();
		if(soma + best.complexity <= s){
			rep(i, dias) if(i <= d) aux[bug[d-i].second] = best.second; else break;
			d -= dias;
			soma += best.complexity;
		}		
	}
	
	rep(i, m) resp[i] = aux[i];
	return true;
}

int main(){
	scanf("%d%d%d", &n, &m, &s);
	
	rep(i, m) scanf("%d", &bug[i].complexity), bug[i].second = i;
	sort(bug, bug + m);
	
	rep(i, n) scanf("%d", &stu[i].ability), stu[i].id = i+1;
	rep(i, n) scanf("%d", &stu[i].cost);
	sort(stu, stu + n);
	
	int ini = 1, fim = m;
	
	while(ini <= fim){
		int mid = (ini+fim)>>1;
		if(pode(mid)) fim = mid - 1;
		else ini = mid + 1;
	}		
	
	if(fim != m){
		printf("YES\n");
		printf("%d", resp[0]);
		fr(i, 1, m) printf(" %d", resp[i]);
		printf("\n");
	}else printf("NO\n");
}