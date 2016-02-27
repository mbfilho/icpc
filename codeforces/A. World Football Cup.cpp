#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Time{
public:
string nome;
int pontos, golsP, golsC;

bool operator<( const Time& t ) const{
	if( pontos > t.pontos )
		return true;
	else if( pontos < t.pontos )
		return false;
	else if( pontos == t.pontos ){
		if( golsP - golsC > t.golsP - t.golsC )
			return true;
		else if( golsP - golsC < t.golsP - t.golsC )
			return false;
		else{
			return golsP > t.golsP;
		}
	}
	
}

}arr[ 200 ], aux[ 200 ];

bool lex( const Time& t1, const Time& t2 ){
	return t1.nome < t2.nome;
}

int main(){
	
	freopen( "in.txt", "r", stdin );
	
	int times;
	while( cin >> times ){
		map<string,int> mapa;
		string buffer;
		
		for( int i = 0; i < times; ++i ){
			cin >> buffer;
			mapa[ buffer ] = i;
			arr[ i ].nome = buffer;
			arr[ i ].golsP = arr[ i ].golsC = arr[ i ].pontos = 0;
		}
		
		string time1, time2;
		for( int i = 0; i < (times * ( times - 1 )) / 2; ++i ){
			cin >> buffer;
			time1 = "";
			time2 = "";
			
			int j = 0;
			while( buffer[ j ] != '-' ){
				time1 += buffer[ j ];
				++j;
			}
			++j;
			while( j < buffer.size() ){
				time2 += buffer[ j ];
				++j;
			}
			int t1 = mapa[ time1 ];
			int t2 = mapa[ time2 ];
			int g, g2;
			
			cin >> g;
			arr[ t1 ].golsP += g;
			arr[ t2 ].golsC += g;
			cin.ignore();
			cin >> g2;
			arr[ t2 ].golsP += g2;
			arr[ t1 ].golsC += g2;
			
			if( g == g2 ){
				arr[ t1 ].pontos += 1;
				arr[ t2 ].pontos += 1;
			}else if( g > g2 )
				arr[ t1 ].pontos += 3;
			else
				arr[ t2 ].pontos += 3;
					
		}
		
		sort( arr, arr + times );
		sort( arr, arr + times/2, lex );
		for( int i = 0; i < times/2; ++i ){
			cout << arr[ i ].nome << endl;
		}
	}
	
}


