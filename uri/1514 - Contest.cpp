#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
#define mp make_pair
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 700


int c, p;
int ma[N][N];

int main(){
	while(cin >> c >> p && (c|p)){
		rep(i, c) rep(j, p) cin >> ma[i][j];
		int ans = 0;
		
		bool fechou = false, fezUm = true;
		rep(i, c){
			bool errou = false, acc = false;
			
			rep(j, p){
				if(ma[i][j] == 0) errou = true;
				acc |= (ma[i][j] == 1);
			}
			fezUm &= acc;
			fechou |= !errou;
		}
		if(!fechou) ++ans;
		if(fezUm) ++ans;
		
		bool everySolved = true, alguemErrou = true;
		rep(j, p){
			bool solved = false, wa = false;
			rep(i, c){
				solved |= (ma[i][j] == 1);
				wa |= (ma[i][j] == 0);
			}
			everySolved &= solved;
			alguemErrou &= wa;
		}
		
		if(everySolved) ++ans;
		if(alguemErrou) ++ans;
		cout << ans << endl;
		
		
	}
}
