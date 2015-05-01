#include "QuickUnion.h"


QuickUnion::QuickUnion(int N)
{
	size = N;
	id = new int[N];
	sz = new int[N];
	for( int i = 0; i < N; i++)
	{
		id[i]=i;
		sz[i]=1;
	}
}


QuickUnion::~QuickUnion(void)
{
	//delete [] id;
	//delete [] sz;
}

//chase parent pointers until root is reached
int QuickUnion::root(int i)
{
	while( i !=id[i] )
	{
		//id[i] = id[id[i]];
		i=id[i];
	}
	return i;
}

//Check if p and q have same root
bool QuickUnion::find(int p, int q)
{
	return root(p) == root(q);
}

//get the root of p
int QuickUnion::getRoot( int p)
{
	return id[p];
}

//change root of p to point to the root of q
void QuickUnion::unite(int p, int q)
{
	int i = root(p), j = root(q);
	//id[i] = j;

	//always sets 
	if( id[i] < id[j] )
	{
		for( int k = 0; k < size; k++)
			if( id[k] == j )
				id[k] = i;
		id[j] = i;
	}
	else
	{
		//sets all roots that have i as it's root to j
		for( int k = 0; k < size; k++)
			if( id[k] == i )
				id[k] = j;
		id[i] = j;
	}
	
	/*if( sz[i] < sz[j] )
	{
		id[i] = j;
		sz[j] += sz[i];
		root(p);
	}
	else
	{
		id[j] = i;
		sz[i] += sz[j];
		root(q);
	}*/
}
