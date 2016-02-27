#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,a) fr(i,0,a)
#define N 200
typedef long long ll;

int marc[1<<13];
int input[N];
char buf[N];
int n, m;
int pot[20];

int contar(int num){
	int cnt = 0;
	
	while(num){
		++cnt;
		num -= num & (-num);		
	}
	return cnt;
}

int pd[1<<11][1<<11];

int faz(int livres, int resp, vector<int> con){
	if(con.size() == 1) return 0;
	if(!livres) return 1000;

	int& best = pd[livres][resp];
	if(~best) return best;
	best = 1000;
	
	rep(i, m){
		if(livres & pot[i]){
			vector<int> yes, no;
			rep(j, con.size()){
				if(con[j] & pot[i]) yes.push_back(con[j]);
				else no.push_back(con[j]);
			}
			
			best = min(best, 1 + max(faz(livres ^ pot[i], resp | pot[i], yes), faz(livres ^pot[i], resp, no)));
		}
	}
	
	return best;
}


int main(){
	pot[0] = 1;
	rep(i, 19) pot[1+i] = pot[i] * 2;
	
	while(scanf("%d%d", &m, &n) == 2 && (n|m)){
		rep(i, n){
			scanf("%s", buf);
			input[i] = 0;
			for(int j = 0; buf[j]; ++j)
				input[i] = 2*input[i] + buf[j] - '0';
		}
		
		if(n == 1)
			printf("0\n");
		else{
			vector<int> todos;
			rep(i, n) todos.push_back(input[i]);
			memset(pd, -1, sizeof pd);
			
			int menor = faz(pot[m] - 1, 0, todos);
			printf("%d\n", menor);
		}
	}
}

