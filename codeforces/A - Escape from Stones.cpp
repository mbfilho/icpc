#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <string>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
#define mp make_pair
#define X first
#define Y second
#define pb push_back
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for(__typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
#define N 1001000

struct no{
	int nt, pv, v;
	void init(int vv){
		nt = pv = 0;
		v = vv;
	}
}nos[N];
char buf[N];

int main(){
	ios::sync_with_stdio(false);
	int at = 1;
	scanf("%s", buf);
	int tam = strlen(buf);
	nos[1].init(1);
	nos[0].init(0);
	int head = 1;
	
	rep(i, tam-1){
		int novo = at + 1;
		int ant = nos[at].pv;
		int depois = nos[at].nt;
		
		nos[novo].init(novo);
		
		if(buf[i] == 'l'){
			nos[novo].nt = at;
			nos[at].pv = novo;
			
			nos[novo].pv = ant;
			nos[ant].nt = novo;
			if(at == head)
				head = novo;
		}else{
			nos[novo].nt = depois;
			nos[depois].pv = novo;
			
			nos[at].nt = novo;
			nos[novo].pv = at;
		}
		++at;
		nos[0].init(0);
	}
	
	at = head;
	while(at){
		printf("%d\n", nos[at].v);
		at = nos[at].nt;
	}
}


