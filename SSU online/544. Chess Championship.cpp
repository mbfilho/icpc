#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
typedef long long ll;
typedef pair<int,int> pii;
#define MOD ll(1e9+9)
#define N 610

ll pd[2][N][N];
int n, k;

pii caras[2*N];
int first[2*N], second[2*N];

int main(){
	cin >> n >> k;
	rep(j, 2) rep(i, n){
		cin >> caras[j*n + i].first;
		caras[j*n + i].second = j;
	}
	
	if((n + k) % 2) cout << "0" << endl;
	else{
		sort(caras, caras + 2*n);
		first[0] = (caras[0].second == 0);
		fr(i, 1, 2*n) first[i] = first[i-1] + (caras[i].second == 0);
		
		second[0] = (caras[0].second == 1);
		fr(i, 1, 2*n) second[i] = second[i-1] + (caras[i].second == 1);
		
		k = (n + k)/2;
		memset(pd, 0, sizeof pd);
		int at = 0;
		pd[1][0][0] = 1;
		
		rep(i, 2*n){
			rep(d, 1+n){
				rep(v, 1+n){
					pd[at][d][v] = 0;
					
					if(caras[i].second == 0){
						pd[at][d][v] = pd[1-at][d][v]; //perdi
						if(v)
							pd[at][d][v] += (d+1) * pd[1-at][d+1][v-1];	//ganhei
					}else{
						ll qtd = (first[i]-v)-(second[i]-d-v-1);
						if(qtd > 0)
							pd[at][d][v] = qtd * pd[1-at][d][v]; 
						//ganhei
						
						if(d)
							pd[at][d][v] += pd[1-at][d-1][v]; //perdi
					}
					pd[at][d][v] %= MOD;
				}
			}
			at = 1 - at;
		}

		at = 1 - at;
		if(pd[at][0][k] < 0) throw 1;
		cout << pd[at][0][k] << endl;
	}
  
}
