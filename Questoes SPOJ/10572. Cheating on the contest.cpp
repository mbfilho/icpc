#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int,int> afn;
typedef pair<int,char> edge;
#define mp make_pair
#define N 4000
#define pb push_back

vector<edge> adj[N];
int cont;

void add( int u, int v, char ch ){
	adj[u].pb( mp(v,ch) );
}


afn operator||( const afn& a, const afn& b ){
	afn ret;
	
	ret.first = cont++;
	ret.second = cont++;
	
	add( ret.first, a.first, 'e' );
	add( ret.first, b.first, 'e' );
	add( a.second, ret.second, 'e' );
	add( b.second, ret.second, 'e' );
	
	return ret;
}

afn operator&&( const afn& a, const afn& b ){
	afn ret;
	
	ret.first = a.first;
	ret.second = b.second;
	
	add( a.second, b.first, 'e' );
	return ret;
}

afn operator*( const afn& a ){

	afn ret = mp( a.first, a.first );
	add( a.second, ret.first, 'e' );
	return ret;
}

afn create( char ch ){
	afn ret;
	ret.first = cont++;
	ret.second = cont++;
	
	add( ret.first, ret.second, ch );
	
	return ret;
}

char str[N];

afn parse( int ini, int fim ){
	if( ini == fim ){
		return create( str[ini] );
	}else{
		int ind = -1;
		int c = 0;
		for( int i = ini; i <= fim; ++i ){
			if( str[i] == '(' ) ++c;
			else if( str[i] == ')') --c;
			else if( !c && (str[i] == '*' || str[i] == '|' || str[i] == '.') ){
				ind = i;
				break;
			}
		}
		
		if( ind == -1 ) return parse( ini + 1, fim - 1 );
		else{
			if( str[ind] != '*' ){
				afn a = parse( ini, ind - 1 ), b = parse( ind + 1, fim );
				if( str[ind] == '|' ) return a || b;
				else{
					return a && b;
				}
			}else{
				return *parse( ini, ind - 1 );
			}
		}
	}
}

int mk[N];
void dfs( int no, vector<int>& go ){
	if( mk[no] ) return;
	mk[no]++;
	go.pb(no);
	
	for( int i = 0; i < adj[no].size(); ++i ){
		edge nt = adj[no][i];
		if( nt.second == 'e' ) dfs(nt.first,go);
	}
}

int main(){
	int u = 0;
	
	while( scanf( "%s", str ) != EOF ){
		int letr = 0, ous = 0;
		for( int i = 0; i < N; ++i ) adj[i].clear();
		
		cont = 0;
		afn regex = parse( 0, strlen(str) - 1 );
		int qu;
		char rf;
		scanf( "%d%c", &qu, &rf );
		while(qu--){
			str[0] = 0;
			gets(str);
			vector<int> estados, tmp;
			memset( mk, 0, sizeof mk );
			dfs( regex.first, estados );
			for( int i = 0; i < str[i]; ++i ){
				tmp.clear();
				
				for( int j = 0; j < estados.size(); ++j ){
					int at = estados[j];

					for( int k = 0; k < adj[at].size(); ++k ){
						edge nt = adj[at][k];
						if( nt.second == str[i] ) tmp.pb(nt.first);
					}
				}

				estados.clear();
				if( !tmp.size() ) break;
				memset( mk, 0, sizeof mk );
				for( int j = 0; j < tmp.size(); ++j ){
					dfs(tmp[j], estados);
				}
				
			}
			
			memset( mk, 0, sizeof mk );
			for( int j = 0; j < tmp.size(); ++j ){
				dfs(tmp[j], estados);
			}
			
			bool aceita = false;
			for( int i = 0; i < estados.size(); ++i ){
				if( estados[i] == regex.second ) aceita = true;
			}
			
			if( aceita ) printf( "Y\n" );
			else printf( "N\n" );
		}
		printf( "\n" );		
	}
}



