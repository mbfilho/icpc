#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define LENGTH 10100
#define N 1100
#define oo 1000000
typedef pair<int,bool> pii;
#define mp make_pair

struct no{
	int L, R, size, ind;

	bool operator<(const no& outro) const{
		int meu = L - R, dele = outro.L - outro.R;
		if(meu == dele && meu == 0) return false;
		
		if(meu * dele <= 0) return meu > dele;
		
		if(meu > 0){
			return R < outro.R;
		}else{
			return L > outro.L;
		}
		
	}
}nos[N];
char word[LENGTH];
int n;
int pd[N][LENGTH];
vector<int> resp;

void pre(int i){
	no& at = nos[i];
	at.ind = i+1;
	at.L = 0, at.R = 0, at.size = strlen(word);

	rep(i, at.size){
		if(word[i] == '(') ++at.L;
		else{
			if(at.L) --at.L;
			else ++at.R;
		}
	}
}



void refaz(){
	int w = n-1, ind = 0;
	while(~w){
		int com = -oo, sem = -oo;
		int vim = ind - nos[w].L + nos[w].R;
		if(vim >= nos[w].R){
			if(w) com = pd[w-1][vim] + nos[w].size;
			else com = (vim==0) ? nos[w].size : (-oo);
		}
		if(w) sem = pd[w-1][ind];
		
		if(com > sem && com > 0) resp.push_back(w), ind = vim;
		--w;
	}
}

int main(){
	scanf("%d", &n);
	int soma = 0;
	rep(i, n) scanf("%s", word), pre(i), soma += nos[i].size;//, printf("%s\n", word);

	sort(nos, nos + n);
	
	rep(i, n) rep(j, soma+1) pd[i][j] = -oo;
	pd[0][0] = 0;
	
	int at = 0;
	rep(i, n){
		
		rep(j, soma+1){
			if(i)
				pd[i][j] = pd[i-1][j] < 0 ? -oo : pd[i-1][j];
		}

		for(int j = nos[i].R; j - nos[i].R + nos[i].L <= soma; ++j){
			int last;
			if(i) last = pd[i-1][j];
			else{
				if(!j) last = 0;
				else last = -oo;
			}
			
			int ind = j - nos[i].R+nos[i].L;
			int sem = pd[i][ind], com = last + nos[i].size;
			pd[i][ind] = max(sem, com);
		}
	}

	printf("%d", max(0, pd[n-1][0]));
	refaz();
	printf(" %d\n", resp.size());
	
	if(max(0,pd[n-1][0])){
		rep(i, resp.size()){
			if(i) printf(" ");
			printf("%d", nos[resp[resp.size()-1-i]].ind );
		}
		printf("\n");
	}

}



