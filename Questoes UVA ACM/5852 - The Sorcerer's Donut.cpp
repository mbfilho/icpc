#include <cstdio>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <string>
#include <algorithm>
using namespace std;
typedef unsigned long long hash;
#define N 25
#define B 1097

char ma[N][N];
map<hash, string> rev;
set<hash> conj;
int n, m;

bool marc[N][N];
string faz(){
	string resp = "0";
	conj.clear();
	rev.clear();
	
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			for(int dx = -1; dx <= 1; ++dx){
				for(int dy = -1; dy <= 1; ++dy){
					if(!dx && !dy) continue;
					
					int ti = i, tj = j;
					hash ha = 0;
					string tmp = "";
					memset(marc, false, sizeof marc);
					int cont = 0;
					while(1){
						if(marc[ti][tj]) break;
						marc[ti][tj] = true;
						ha = ha * B + ma[ti][tj];
						tmp += ma[ti][tj];
						++cont;
						
						if(cont > 1 && cont >= resp.size()){
							bool acc = conj.insert(ha).second;
							if(!acc){
								if(cont > resp.size())
									resp = tmp;
								else{
									if(tmp < resp)
										resp = tmp;
								}//igual
							}else
								rev[ha] = tmp;
						}
							
						ti = (ti + dx + n) % n;
						tj = (tj + dy + m) % m;
					}
				}
			}
		}
	}
	
	return resp;
}

int main(){
	while(scanf("%d%d", &n, &m) == 2 && (n|m)){
		for(int i = 0; i < n; ++i){
			scanf("%s", ma[i]);
//			printf(">%s\n", ma[i]);
		}
		string resp = faz();
		
		printf("%s\n", resp.c_str());
	}
}




