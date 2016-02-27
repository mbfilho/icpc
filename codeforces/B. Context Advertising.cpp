#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
typedef pair<int,int> pii;
#define mp make_pair
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 1000100
#define LOG 21
#define pb push_back
#define oo 1000000000

int next[N][LOG], pd[N][LOG];
vector<string> words;
int n, r, c;

void calcNext(){
	int j = n-1, last = n-1, cols = 0;
	
	while(j >= 0){
		while(last > j && cols + words[j].size() + (last-j) > c) cols -= words[last].size(), --last;
		
		if(cols + (last-j) + words[j].size() <= c){
			next[j][0] = last+1;
			cols += words[j].size();
		}else next[j][0] = -1, last = j - 1;
		
		--j;
	}
}

void fazPd(){
	rep(i, n) pd[i][0] = (~next[i][0]) ? (next[i][0] - i) : -oo;
	
	for(int tam = 1; (1<<tam) <= r; ++tam){
		rep(i, n){
			int nt = next[i][tam-1];
			if((~nt) && nt < n) pd[i][tam] = pd[i][tam-1] + pd[nt][tam-1], next[i][tam] = next[nt][tam-1];
			else next[i][tam] = -1, pd[i][tam] = -oo;
		}
	}
	
}

int main(){
	ios::sync_with_stdio(false);
	cin >> n >> r >> c;
	
	rep(i, n){
		string tmp;
		cin >> tmp;
		words.pb(tmp);
	}
	words.pb("(fim de string)");
	
	calcNext();
	fazPd();
	pii best = mp(-oo, -1);
	
	int pot = 0;
	while((1<<pot) <= r) ++pot;
	--pot;
	
	rep(i, n){
		int total = 0, aux = pot, at = i, num = 0;
		while(aux >= 0 && at < n){
			if((~next[at][aux]) && (num|(1<<aux)) <= r){
				total += pd[at][aux], at = next[at][aux];
				num |= 1 << aux;
			}
			--aux;
		}
		best = max(best, mp(total, i));
	}

	int prt = best.second, tot = 0;
	while(tot < best.first){
		tot += next[prt][0] - prt;
		
		fr(i, prt, next[prt][0]){
			if(i != prt) printf(" ");
			printf("%s", words[i].c_str());
		}
		printf("\n");
		prt = next[prt][0];
	}
}


