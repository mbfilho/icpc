#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <string>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define pb push_back
#define N 20000
typedef long long ll;

struct Arq{
	int n, m;
	vector<string> rows;
};
struct Css{
	int x, y, pai, file, layer;
	string dad;
	Css(){
		x = y = 0;
	}
};
Arq files[N];
int f;

vector<Css> css;
map<string,int> mapa, arquivos;

char grid[6000000];
int r, c;
int get(int i, int j){
	return i * c + j;
}

bool mk[N];

char linha[100000];

bool isblank(char c){
	return c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\r\n';
}

void readFiles(){
	rep(i, f){
		scanf("%s %d %d", linha, &files[i].n, &files[i].m);
		arquivos[linha] = i;
		files[i].rows.clear();
		rep(a, files[i].n){
			scanf("%s", linha);
			files[i].rows.pb(linha);
		}
	}
}

void readLine(char* buf){
	while(gets(buf) && !buf[0]);
}

char* spaces(char* prt){
	while(*prt && isblank(*prt)) ++prt;
	return prt;
}

char* readField(char* prt, string& aqui){
	aqui = "";
	prt = spaces(prt);
	while(!isblank(*prt) && *prt != ':') aqui += *prt, ++prt;
	while(*prt != ':') ++prt;
	++prt;
	return spaces(prt);
}

void dfs(int no){
	if(mk[no]) return;
	
	dfs(css[no].pai);
	int p = css[no].pai;
	css[no].x += css[p].x, css[no].y += css[p].y;
	mk[no] = true;
}

vector<int> perm;
bool cmp(int a, int b){
	if(css[a].layer != css[b].layer) return css[a].layer < css[b].layer;
	return a < b;
}

int main(){
	int t;
	scanf("%d", &t);
	
	rep(cas, t){
		mapa.clear();
		css.clear();
		arquivos.clear();
		memset(mk, false, sizeof mk);
		perm.clear();
		
		scanf("%d", &f);
		readFiles();
		{
		int c;
		scanf("%d", &c);
		css.pb(Css());
		fr(cc, 1, c+1){
			Css tmp;

			readLine(linha);
			char* prt = spaces(linha);
			string name = "";
			++prt; //'#'
			prt = spaces(prt);
			while(*prt != '{' && !isblank(*prt)) name += *prt, ++prt;
			mapa[name] = cc;
			rep(i, 5){
				readLine(prt);
				prt = readField(prt, name);
				
				if(name == string("pos-x")){
					sscanf(prt, "%d", &tmp.x);
				}else if(name == string("pos-y")){
					sscanf(prt, "%d", &tmp.y);
				}else if(name == string("position")){
					string value = "";
					while(!isblank(*prt) && *prt != '=' && *prt != ';') value += *prt, ++prt;
					
					if(value == string("absolute")){
						tmp.pai = 0;
					}else if(value == string("relative")){
						prt = spaces(prt);
						++prt; //'=';
						prt = spaces(prt);
						
						value = "";
						while(!isblank(*prt) && *prt != ';') value += *prt, ++prt;
						tmp.dad = value;
					}else while(1);
				}else if(name == string("file")){
					string value = "";
					while(*prt != ';' && !isblank(*prt)) value += *prt, ++prt;
					tmp.file = arquivos[value];
				}else if(name == string("layer")){
					sscanf(prt, "%d", &tmp.layer);
				}else{
					while(1);
				}
			}
			readLine(linha);//}
			css.pb(tmp);
		}
		}
		fr(i, 1, css.size()) css[i].pai = mapa[css[i].dad];
		mk[0] = true;
		fr(i, 1, css.size()){
			if(!mk[i]) dfs(i);
		}
		r = c = 0;
		fr(i, 1, css.size()){
			int ff = css[i].file;
			c = max(c, css[i].x + files[ff].m);
			r = max(r, css[i].y + files[ff].n);
		}
		rep(i, r) rep(j, c) grid[get(i,j)] = ' ';
		
		fr(i, 1, css.size()) perm.pb(i);
		sort(perm.begin(), perm.end(), cmp);

		rep(cc, perm.size()){
			int p = perm[cc];
			Css& tmp = css[p];
			Arq& a = files[tmp.file];
			
			rep(i, a.rows.size()){
				rep(j, a.rows[i].size()){
					 if(a.rows[i][j] != '.') grid[get(i+tmp.y, j+tmp.x)] = a.rows[i][j];//, printf("(%d,%d) %c\n", i, j, a.rows[i][j]);
				}
			}
		}
		
		printf("Scenario #%d:\n", cas+1);
		rep(i, r){
			rep(j, c){
				printf("%c", grid[get(i,j)]);
			}
			printf("\n");
		}
		printf("\n");
	}
}

