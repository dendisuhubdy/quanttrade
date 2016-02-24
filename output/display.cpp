/*************************************************************************
	> File Name: display.cpp
	> Author: Dendi Suhubdy 
	> Mail: dasuhubd@ncsu.edu
	> Created Time: Sat 16 Jan 2016 07:39:01 PM EST
 ************************************************************************/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

template <class V> void print(const vector<v>& v)
{
    cout << endl << "V: [";

    vector<V>::const_iterator i;

    for (i= v.begin(); i!=v.end(); i++)
    {
        cout << (*i) << ",";
    }
    cout << "]";
}

template <class V> void print(vector<vector<V> >& mat)
{
    vector<vector<v> >::const_iterator i;

    for(i=mat.begin(); i!=mat.end(); i++) 
    {
        print (*i);
    }
    cout << endl;
}
