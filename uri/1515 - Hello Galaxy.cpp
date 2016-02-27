#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
#define mp make_pair
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)

pair<int, string> civs[200];
int n;

int main(){
	while(cin >> n && n){
		rep(i, n){
			int inc;
			cin >> civs[i].second >> civs[i].first >> inc;
			civs[i].first -= inc;
		}
		
		pair<int, string>* tmp = min_element(civs, civs + n);
		cout << tmp->second << endl;
		
	}
	
}
