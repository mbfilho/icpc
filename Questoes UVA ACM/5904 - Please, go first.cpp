#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <cstdlib>
#include <ctime>
#include <queue>
using namespace std;
typedef pair<int,int> Frac;
typedef long long ll;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
#define N 300000

int qtd[300];
int last[300];
int first[300];
int normal[300];
ll opt[300];
int n;
char str[N];

struct No{
	int id;
	
	No(int a){
		id = a;
	}
	
	bool operator<(const No& a) const{
		return !(last[id] < last[a.id]);
	}
};

priority_queue<No> heap;

void faz(){
	while(!heap.empty()) heap.pop();
	for(int i = 0; i < 300; ++i){
		if(last[i] != -1)
			heap.push(No(i));
	}
	
	ll cont = 0;
	while(!heap.empty()){
		int at = heap.top().id;
		heap.pop();
		
		opt[at] = (cont + qtd[at]) * 5;
		cont += qtd[at];
	}
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	while(casos--){
		scanf("%d", &n );
		for(int i = 0; i < 300; ++i){
			qtd[i] = normal[i] = 0;
			last[i] = -1;
			first[i] = 1000000;
		}
		
		scanf("%s", str);
		for(int i = 0; i < n; ++i){
			char at = str[i];
			
			last[at] = i;
			first[at] = min(first[at], i);
			++qtd[at];
		}
		
		for(int i = 0; i < 300; ++i){
			if(last[i] == -1) continue;
			normal[i] = 5 * (last[i] + 1);
		}
		
		faz();
		
		ll dif = 0;
		for(int i = 0; i < 300; ++i){
			if(last[i] == -1) continue;
			dif += (normal[i] - opt[i]) * qtd[i];
		}
		
		printf( "%lld\n", dif );
		
	}
}







