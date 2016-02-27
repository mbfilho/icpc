#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <map>
using namespace std;
typedef pair<int,int> Ponto;
#define mp make_pair
#define X first
#define Y second
int prt;

struct No{
	string nome;
	int id;
	int pts;
	int gols;
	int sof;
	
	No(){
		pts = gols = sof = 0;
	}
	
	bool operator<(const No& h) const{
		if(pts != h.pts) return pts > h.pts;
		if(gols - sof != h.gols - h.sof) return gols - sof > h.gols - h.sof;
		if(gols != h.gols) return gols > h.gols;
		
		return nome < h.nome;
	}
}nos[10];

bool vence(int x, int y, int other){
	int ber;
	for(int i = 0; i < prt; ++i){
		if(nos[i].nome == "BERLAND") ber = i;
	}
	
	No tmp[10];
	for(int i = 0; i < prt; ++i) tmp[i] = nos[i];
	
	tmp[ber].gols += x;
	tmp[other].gols += y;
	tmp[ber].sof += y;
	tmp[other].sof += x;
	tmp[ber].pts += 3;
	
	sort(tmp, tmp + prt);
	
	if(tmp[0].nome == "BERLAND" || tmp[1].nome == "BERLAND") return true;
	
	return false;
}

map<string,int> mapa;
char na[100], nb[100];
bool match[10][10];
int main(){
	prt = 0;
	memset(match, false, sizeof match);
	
	for(int i = 0; i < 5; ++i){
		int ga, gb;
		scanf("%s %s %d:%d", na, nb, &ga, &gb);
		if(mapa.find(na) == mapa.end()) mapa[na] = prt++;
		if(mapa.find(nb) == mapa.end()) mapa[nb] = prt++;
		int a = mapa[na], b = mapa[nb];

		match[a][b] = match[b][a] = true;
		
		nos[a].nome = na;
		nos[b].nome = nb;
		nos[a].id = a;
		nos[b].id = b;
		
		nos[a].gols += ga;
		nos[b].gols += gb;
		
		nos[a].sof += gb;
		nos[b].sof += ga;
		
		if(ga > gb){
			nos[a].pts += 3;
		}else if(ga < gb) 
			nos[b].pts += 3;
		else{
			++nos[a].pts;
			++nos[b].pts;
		}
	}
	int ber = mapa["BERLAND"], other;

	sort(nos, nos + prt);
	
	for(int i = 0; i < prt; ++i){
		if(nos[i].id == ber) continue;
		if(!match[ber][nos[i].id]) other = i;
	}
	
	int bb = -1, oo = -1;
	for(int x = 1; x <= 200; ++x){
		for(int y = 0; y < x; ++y){
			if(vence(x,y,other)){
				if(bb == -1 || ((x - y) < (bb - oo))){
					bb = x;
					oo = y;
				}else if((x-y) == (bb - oo) && y < oo){
					bb = x;
					oo = y;
				}
			}
		}
	}
	
	if(~bb) printf( "%d:%d\n", bb, oo);
	else printf("IMPOSSIBLE\n");
	
	
}

