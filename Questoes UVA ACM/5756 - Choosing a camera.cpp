#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#define fr(i,a,b) for(int i=a;i<b;i++)
#define rep(i,b) fr(i,0,b)
using namespace std;
int n, m;
#define N 200000
#define conj kdsjhfsdjf
#define pb push_back
#define EPS 1e-7

struct no{
	int p, id, c;
	double z;
}nos[N];

struct Cmp{
	bool operator()(int a, int b){
		if(nos[a].p != nos[b].p) return nos[a].p < nos[b].p;
		if(nos[a].z != nos[b].z) return nos[a].z < nos[b].z;
		return nos[a].id < nos[b].id;
	}
};

struct Cmp2{
	bool operator()(int a, int b){
		if(nos[a].c != nos[b].c) return nos[a].c < nos[b].c;
		return nos[a].id < nos[b].id;
	}
};

set<int, Cmp> coast;
set<int, Cmp2> menor;

bool cover(int a, int b){
	if(nos[a].p == nos[b].p && abs(nos[a].z - nos[b].z) <= EPS){
		if(nos[a].c != nos[b].c) return nos[a].c < nos[b].c;
		return a < b;
	}
	return nos[a].p >= nos[b].p && (nos[a].z >= nos[b].z);
}

void insert(int q){
	set<int, Cmp>::iterator it = coast.upper_bound(q);
	
	if(it != coast.end() && cover(*it, q)) return;
	
	if(it != coast.begin()){
		vector<int> tmp;
		
		while(it != coast.begin()){
			--it;
			if(cover(q, *it)) tmp.pb(*it);
			else break;
		}
		
		rep(i, tmp.size()){
			menor.erase(tmp[i]);
			coast.erase(tmp[i]);
		}
	}
	
	coast.insert(q);
	menor.insert(q);
}


int main(){
	int t, prt;
	scanf("%d", &t);
	
	while(t--){
		coast.clear();
		menor.clear();
		prt = 0;
		
		int n;
		scanf("%d", &n);
		bool f = true;
		char buf[1000];
		
		rep(q, n){
			scanf("%s", buf);
			if(buf[0] == 'P'){
				scanf("%d %lf %d", &nos[prt].p, &nos[prt].z, &nos[prt].c);
				nos[prt].id = q;
				insert(prt);
				++prt;
			}else{
				if(f) f = false;
				else printf(" ");
				
				if(!menor.size()) printf("-1");
				else
					printf("%d", 1 + nos[*menor.begin()].id);
			}
		}
		printf("\n");
	}
}











