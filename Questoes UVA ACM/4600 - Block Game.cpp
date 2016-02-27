#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int,int> pii;
typedef unsigned long long hash;
#define mp make_pair
#define dx first
#define dy second
#define Fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) Fr(i,0,n)
hash pot[50];

map<hash,int> marc;

char especial;
int saida;
int get(int a, int b){
	return a*6+b;
}

bool valido(int a, int b){
	return a >= 0 && a < 6 && b >= 0 && b < 6;
}

pii pecas[300];

void print(string& a){
	hash ha = 0;
	rep(i, a.size())
		ha += a[i] * pot[i];
	printf("Hash %llu\n", ha);
	rep(i, 6){
		rep(j, 6){
			printf( "%c", a[get(i,j)]);
		}
		printf("\n");
	}
}

queue<string> fila;
int bfs(string ini){
	while(!fila.empty()) fila.pop();
	fila.push(ini);
	marc.clear();
	int visto[300];
	memset(visto, 0, sizeof visto);
	int it = 1;
	
	while(!fila.empty()){
		string at = fila.front();
		fila.pop();
		
//		print(at);
		
		hash ha = 0;
		rep(i, 6*6)
			ha += at[i] * pot[i];
		int dist = marc[ha];
		for(int i = 5; ~i; --i){
			char ch = at[get(saida, i)];
			if(ch != '.'){
				if(ch == especial) return 1 + dist;
				break;
			}
		}
		rep(i, 6){
			rep(j, 6){
				char ch = at[get(i,j)];
				if(ch != '.' && visto[ch] != it){
					visto[ch] = it;
					int inc[] = {-1, 1};
					rep(k, 2){
						string nt = at;
						hash novo = ha;
						
						int a = i, b = j;
						int ia = i, ib = j;
						while(valido(ia,ib) && at[get(ia,ib)] == ch){
							ia -= inc[k] * pecas[ch].dx;
							ib -= inc[k] * pecas[ch].dy;
						}
						ia += inc[k] * pecas[ch].dx;
						ib += inc[k] * pecas[ch].dy;

						while(valido(a,b) && at[get(a,b)] == ch){
							a += inc[k] * pecas[ch].dx;
							b += inc[k] * pecas[ch].dy;
						}
						while(valido(a,b) && (at[get(a,b)] == '.')){
							if(nt[get(ia,ib)] != ch) throw 'z';
							nt[get(ia,ib)] = '.';
							nt[get(a,b)] = ch;
							novo -= ch * pot[get(ia,ib)];
							novo += '.' * pot[get(ia,ib)];
							novo += ch * pot[get(a,b)];
							novo -= '.' * pot[get(a,b)];
//							printf("sim(%d,%d)\n", a,b);
//							fflush(stdout);
							
							ia += inc[k] * pecas[ch].dx;
							ib += inc[k] * pecas[ch].dy;
							if(nt[get(ia,ib)] != ch) throw true;
							a += inc[k] * pecas[ch].dx;
							b += inc[k] * pecas[ch].dy;
							
							hash h = 0;
							rep(l, nt.size())
								h += nt[l] * pot[l];
							if(h != novo) throw 2;
							
							if(marc.find(novo) == marc.end()){
								fila.push(nt);
								marc[novo] = 1 + dist;
							}else{
//								printf( "Again %llu\n", novo);
							}
						}
					}
				}
			}
		}
		++it;
	}
	
	return -1;
}

char buf[10];
int main(){
	pot[0] = 1;
	Fr(i,1,50)
		pot[i] = pot[i-1] * 1097;
	while(scanf("%s", buf) != EOF && strcmp(buf, "*")){
		especial = buf[0];
		string ini = "";
		rep(i, 6){
			scanf("%s", buf);
			ini += buf;
		}
		
		rep(i, 300)
			pecas[i] = mp(0,0);
		
		rep(i, 6){
			rep(j, 6){
				if(ini[get(i,j)] != '.'){
					if(ini[get(i,j)] == especial) saida = i;
					
					if(valido(i-1,j) && ini[get(i-1,j)] == ini[get(i,j)])
						pecas[ini[get(i,j)]] = mp(1,0);
					else if(valido(i+1,j) && ini[get(i+1,j)] == ini[get(i,j)])
						pecas[ini[get(i,j)]] = mp(1,0);
					else if(valido(i,j-1) && ini[get(i,j-1)] == ini[get(i,j)])
						pecas[ini[get(i,j)]] = mp(0,1);
					else if(valido(i,j+1) && ini[get(i,j+1)] == ini[get(i,j)])
						pecas[ini[get(i,j)]] = mp(0,1);
				}
			}
		}
		
		printf( "%d\n", bfs(ini));
	}
}

