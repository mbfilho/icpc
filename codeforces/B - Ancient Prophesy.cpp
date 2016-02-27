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

string line;

int dias[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool eh(string arg){
	int d = 0, m = 0, y = 0;
	if(arg[2] != '-') return false;
	if(arg[5] != '-') return false;
	rep(i, 2){
		d = d * 10 + arg[i] - '0';
		if(arg[i]  < '0' || arg[i] > '9') return false;
	}
	fr(i, 3, 5){
		m = m * 10 + arg[i] - '0';
		if(arg[i]  < '0' || arg[i] > '9') return false;
	}
	fr(i, 6, 10){
		y = y * 10 + arg[i] - '0';
		if(arg[i]  < '0' || arg[i] > '9') return false;
	}
	if(y >= 2013 && y <= 2015 && m >= 1 && m <= 12 && d >= 1 && d <= dias[m]) return true;
	return false;
}

map<string,int> mapa;

string best;
int cont;
void add(string arg){
	int& cnt = mapa[arg];
	++cnt;
	
	if(cnt > cont) cont = cnt, best = arg;
}

int main(){
	ios::sync_with_stdio(false);
	cin >> line;
	
	int tam = line.size();
	rep(i, tam){
		if(i+10 > tam) break;
		
		string arg = "";
		arg = line.substr(i, 10);
		if(eh(arg)){
			add(arg);
		}
	}
	
	cout << best << endl;
}


