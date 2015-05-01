#pragma once
class QuickUnion
{
public:
	QuickUnion(int);
	~QuickUnion(void);
private:
	//chase parent pointers until root is reached
	int root(int i);
public:
	//Check if p and q have same root
	bool find(int p, int q);

	//get the root of p
	int getRoot( int p);

	//change root of p to point to the root of q
	void unite(int p, int q);
private:
	int size;
	int *id;
	int *sz;
};

