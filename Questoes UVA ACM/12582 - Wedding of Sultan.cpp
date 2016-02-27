#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for( __typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
typedef pair<int,int> pii;
typedef long long ll;
#define oo 100000000
#define X first
#define Y second
#define mp make_pair
#define N 60

int pilha[1000];
int sp;
char buf[1000];
bool tem[1000];
int qtd[1000];

int main(){
	int t;
	scanf("%d", &t);
	
	rep(cas, t){
		scanf("%s", buf);
		sp = 0;
		memset(tem, false, sizeof tem);
		memset(qtd, 0, sizeof qtd);
		for(int i = 0; buf[i]; ++i) tem[buf[i]] = true;
		
		pilha[sp++] = buf[0];
		int ind = 1;
		while(buf[ind]){
			int ch = buf[ind++];
			if(pilha[sp-1] == ch){
				--sp;
				if(sp) ++qtd[pilha[sp-1]];
			}else{
				++qtd[ch];
				pilha[sp++] = ch;
			}
		}
		printf("Case %d\n", cas+1);
		for(int i = 'A'; i <= 'Z'; ++i){
			if(tem[i]) printf("%c = %d\n", char(i), qtd[i]);
		}
		
		
	}
}



