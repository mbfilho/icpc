#include <iostream>
#include <string>
#include <map>
#include <cstdio>
using namespace std;

string get( string a, int rh ){
    if( rh == 0 )
        return a + "-";
    else if( rh == 1 )
        return a + "+";
    else
        return a + "+, " + a + "-";
}


string get( string p1, string p2, int rh ){
    string ret = "";

    if( p1 == "A" ){
        if( p2 == "AB" )
            ret = "{" + get( "AB", rh ) + ", " + get( "B", rh ) + ", " + get( "A", rh ) + "}";

        if( p2 == "A" )
            ret = "{" + get( "A", rh ) + ", " + get( "O", rh ) + "}";

        if( p2 == "B" )
            ret = "{" + get( "AB", rh ) + ", " + get( "O", rh ) + ", " + get( "A", rh ) + ", " + get( "B", rh ) + "}";

        if( p2 == "O" )
            ret = "{" + get( "A", rh ) + ", " + get( "O", rh ) + "}";

    }else if( p1 == "B" ){
        if( p2 == "B" )
            ret = "{" + get( "B", rh ) + ", " + get( "O", rh ) + "}";

        if( p2 == "A" )
            ret = "{" + get( "AB", rh ) + ", " + get( "O", rh ) + ", " + get( "A", rh ) + ", " + get( "B", rh ) + "}";

        if( p2 == "AB" )
            ret = "{" + get( "AB", rh ) + ", " + get( "B", rh ) + ", " + get( "A", rh ) + "}";

        if( p2 == "O" )
            ret = "{" + get( "B", rh ) + ", " + get( "O", rh ) + "}";

    }else if( p1 == "AB" ){
        if( p2 == "A" )
            ret = "{" + get( "AB", rh ) + ", " + get( "B", rh ) + ", " + get( "A", rh ) + "}";

        if( p2 == "AB" )
             ret = "{" + get( "AB", rh ) + ", " + get( "A", rh ) + ", " + get( "B", rh ) + "}";

        if( p2 == "B" )
            ret = "{" + get( "AB", rh ) + ", " + get( "B", rh ) + ", " + get( "A", rh ) + "}";

        if( p2 == "O" )
            ret = "{" + get( "A", rh ) + ", " + get( "B", rh ) + "}";

    }else if( p1 == "O" ){
        if( p2 == "A" )
            ret = "{" + get( "A", rh ) + ", " + get( "O", rh ) + "}";

        if( p2 == "O" ){
            if( rh > 1 )
               ret = "{" + get( "O", rh ) + "}";
            else
                ret = get( "O", rh );
        }

        if( p2 == "B" )
            ret = "{" + get( "B", rh ) + ", " + get( "O", rh ) + "}";

        if( p2 == "AB" )
            ret = "{" + get( "A", rh ) + ", " + get( "B", rh ) + "}";
    }

    return ret;

}

string get2( string p1, string p2, int rh ){
    string ret = "";

    if( p1 == "A" ){
        if( p2 == "AB" )
            ret = "{" + get( "AB", rh ) +  ", " + get( "B", rh ) + "}";

        if( p2 == "A" )
             ret = "{" + get( "AB", rh ) +  ", " + get( "A", rh ) + ", " + get( "O", rh ) + ", " + get( "B", rh ) + "}";

        if( p2 == "B" )
            ret = "{" + get( "AB", rh ) + ", " + get( "B", rh ) + "}";

        if( p2 == "O" )
             ret = "{" + get( "O", rh ) +  ", " + get( "A", rh ) + ", " + get( "B", rh ) + "}";


    }else if( p1 == "B" ){
        if( p2 == "AB" )
            ret = "{" + get( "AB", rh ) +  ", " + get( "A", rh ) + "}";

        if( p2 == "A" )
             ret = "{" + get( "AB", rh ) +  ", " + get( "A", rh ) +  "}";

        if( p2 == "B" )
            ret = "{" + get( "AB", rh ) +  ", " + get( "B", rh ) + ", " + get( "O", rh ) + ", " + get( "A", rh ) + "}";

        if( p2 == "O" )
             ret = "{" + get( "O", rh ) +  ", " + get( "A", rh ) + ", " + get( "B", rh ) + "}";

    }else if( p1 == "AB" ){    
        if( p2 == "AB" )
             ret = "{" + get( "AB", rh ) + ", " + get( "A", rh ) + ", " + get( "B", rh ) + "}";

        if( p2 == "B" )
           ret = "{" + get( "AB", rh ) +  ", " + get( "B", rh ) + ", " + get( "O", rh ) + ", " + get( "A", rh ) + "}";


        if( p2 == "A" )
            ret = "{" + get( "AB", rh ) +  ", " + get( "B", rh ) + ", " + get( "O", rh ) + ", " + get( "A", rh ) + "}";


        if( p2 == "O" )
            ret = "IMPOSSIBLE";

    }else if( p1 == "O" ){
        if( p2 == "B" ){
            ret = "{" + get( "AB", rh ) + ", " + get( "B", rh ) + "}";
        }

        if( p2 == "A" )
            ret = "{" + get( "AB", rh ) + ", " + get( "A", rh ) + "}";

        if( p2 == "O" )
            ret = "{" + get( "O", rh ) + ", " + get( "A", rh ) + ", " + get( "B", rh ) + "}";

        if( p2 == "AB" )
             ret = "IMPOSSIBLE";
    }

    return ret;

}

int main(){
    string p1, p2, f;
    int caso = 1;

    while( cin >> p1 >> p2 >> f && ( p1 != "E" && p2 != "N" && f != "D" ) ){

        cout << "Case " << caso << ": ";
        ++caso;

        if( f == "?" ){
            int rh;

            if( p2[ p2.size() - 1 ] == '+' || p1[ p1.size() - 1 ] == '+')
                rh = 3;
            else
                rh = 0;

            cout << p1 << " " << p2 << " " << get( p1.substr( 0, p1.size() - 1), p2.substr( 0, p2.size() - 1 ), rh ) << endl;

        }else{
            string pai;
            if( p1 == "?" )
                pai = p2;
            else
                pai = p1;

            int rh = 3;

            if( pai[ pai.size() - 1 ] == '+' )
                rh = 3;
            else if( pai[ pai.size() - 1 ] == '-' && f[ f.size() - 1 ] == '-' )
                rh = 3;
            else if( pai[ pai.size() - 1 ] == '-' && f[ f.size() - 1 ] == '+' )
                rh = 1;

            string p = get2( pai.substr( 0, pai.size() - 1 ), f.substr( 0, f.size() - 1 ), rh );

            if( p2 == "?" )
                p2 = p;
            else
                p1 = p;

            cout << p1 << " " << p2 << " " << f << endl;


        }

    }
}
