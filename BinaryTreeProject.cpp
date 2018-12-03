/* CS 501 Project 5 by Geoff Gaugler. Inputs 20 strings into a binary tree. 
Prints out the inorder, preorder and postorder traversals indicating the 
level of each node as it's printed out. Also prints the number of leaves
in the tree, the number of nodes with one child, number of nodes with two children,
maximum and minimum leaf levels, height of tree, and whether or not the tree is balanced.*/

#include <iostream>
#include <string>
using namespace std;
const int nil = 0;
class treenode_type		    // declaration of class//
{
public:						// Tree node type//
	string info;
	treenode_type *left;
	treenode_type *right;
};

void input();
void setleft(string x);
void setright(string x);
void inorder(treenode_type *p);
void preorder(treenode_type *p);
void postorder(treenode_type *p);
int levelcounter(treenode_type *p);
treenode_type *p, *q, *root;
string number;
int maxleaflevel, maxlevel, leafcounter, onechild, twochild = 0;
int minleaflevel = 20;

void main()
{
	input();
	cout << "The tree traversed INORDER is \n";
	p = root;
	inorder(p);
	cout << "The tree traversed PREORDER is \n";
	p = root;
	preorder(p);
	cout << "The tree traversed POSTORDER is \n";
	p = root;
	postorder(p);
	cout << "Nodes with one child: " << onechild << ", Leaf nodes: " << leafcounter << ", Nodes with two children: " << twochild << "\n";
	cout << "Height is " << maxlevel << "\n";
	cout << "Maximum leaf level is: " << maxlevel << ", minimum leaf level is: " << minleaflevel << "\n";
	if (maxlevel == 4)
		cout << "Tree is balanced. \n";
	else
		cout << "Tree is not balanced. \n";
}
void input() // takes 20 user inputted strings and puts them into a binary tree
{
	cout << "Enter first string: \n";
	cin >> number;
	cout << number << " is the root. \n";
	root = new treenode_type;
	(*root).info = number;
	(*root).left = nil;
	(*root).right = nil;
	int i = 1;
	while (i < 20)
	{
		cout << "Enter remaining strings: \n";
		cin >> number;
		p = root;
		q = p;
		while ((number != (*p).info) && (q != nil))
		{
			p = q;
			if (number < (*p).info)
				q = (*p).left;
			else
				q = (*p).right;
		}
		if (number == (*p).info)
			cout << number << " is a duplicate \n";
		else if (number < (*p).info)     // Sets node to left if number less than p.info//
		{
			setleft(number);
			cout << number << " is a left child of " << (*p).info << "\n";
		}
		else    // Sets node to right if number greater than p.info//
		{
			setright(number);
			cout << number << " is a right child of " << (*p).info << "\n";
		}
		i = i + 1;
	}
}
void setleft(string x)   // Sets node to left //
{
	treenode_type *q;
	q = new treenode_type;
	(*q).info = x;
	(*q).left = nil;
	(*q).right = nil;
	(*p).left = q;
}
void setright(string x)
{
	treenode_type *q;
	q = new treenode_type;
	(*q).info = x;
	(*q).left = nil;
	(*q).right = nil;
	(*p).right = q;
}
void inorder(treenode_type *r)
{
	if (r != nil)
	{
		inorder((*r).left);
		cout << (*r).info << " on line " << levelcounter(r) << "\n";
		inorder((*r).right);
	}
}
void preorder(treenode_type *r)
{
	if (r != nil)
	{
		cout << (*r).info << " on line " << levelcounter(r) << "\n";
		if ((*r).left == nil and (*r).right == nil) //counters for nodes with one child, two children and no children
		{
			leafcounter += 1;
			if (levelcounter(r) < minleaflevel) 
				minleaflevel = levelcounter(r);
		}	
		else if ((*r).left != nil and (*r).right != nil)
			twochild += 1;
		else
			onechild += 1;
		if (levelcounter(r) > maxlevel)
			maxlevel = levelcounter(r);
		preorder((*r).left);
		preorder((*r).right);
	}
}
void postorder(treenode_type *r)
{
	if (r != nil)
	{
		postorder((*r).left);
		postorder((*r).right);
		cout << (*r).info << " on line " << levelcounter(r) << "\n";
	}
}
int levelcounter(treenode_type *r) //returns tree level of a given node
{
	string x = (*r).info;
	int counter = 0;
	p = root;
	while (x != (*p).info)
	{
		counter += 1;
		if (x > (*p).info)
			p = (*p).right;
		else
			p = (*p).left;
	}
	return counter;
}
