#ifndef BT_H_
#define BT_H_

#include <cassert>
#include<iostream>
#include <fstream>
#include<string>
#include <sstream>
using namespace std;
#include <cassert>

typedef string BTstr;



template <class BTElementType>
class BT {
public:
	BT();
	bool isEmpty() const;
	BTElementType getData();
	void insert(const BTElementType&);
	BT* Right();
	BT* Left();
	void MakeRight(BT* T1);
	void MakeLeft(BT* T1);
	int CountNum(BT*, int&);
	int height();

protected:
	bool NullTree;
	BTElementType TreeData;
	BT* RightTree;
	BT* LeftTree;
};

template <class BTElementType>
BT<BTElementType> :: BT(){
	NullTree = NULL;
	RightTree = NULL;
	LeftTree = NULL;
}

template <class BTElementType>
bool BT <BTElementType> :: isEmpty() const{
	return NullTree;
}

template <class BTElementType>
int BT<BTElementType> ::height(){
	assert(!NullTree);
	BT* ptr;
	ptr = this;
	int LHeight = ptr->LeftTree->height();
	int RHeight = ptr->RightTree->height();
	if(LHeight > RHeight)
		return LHeight+1;
	else
		return RHeight+1;
}

template <class BTElementType>
int BT<BTElementType> ::CountNum(BT* T, int &n){
	assert(!T->NullTree);
	n++;
	CountNum(T->LeftTree, n);
	CountNum(T->RightTree, n);
}

template <class BTElementType>
BTElementType BT <BTElementType> :: getData(){
	assert(!isEmpty());
	return TreeData;
}

template <class BTElementType>
void BT <BTElementType> :: insert(const BTElementType& Data){
	TreeData = Data;
	if (NullTree){
		NullTree = false;
		LeftTree = new BT;
		RightTree = new BT;
	}
}

template <class BTElementType>
BT <BTElementType>* BT <BTElementType> :: Right(){
	assert(!isEmpty());
	return RightTree;
}

template <class BTElementType>
BT <BTElementType>* BT <BTElementType> :: Left(){
	assert(!isEmpty());
	return LeftTree;
}

template <class BTElementType>
void BT <BTElementType> :: MakeRight(BT* T1){
	assert(!isEmpty());
	assert(Right()->isEmpty());
	delete Right();
	RightTree = T1;
}

template <class BTElementType>
void BT <BTElementType> :: MakeLeft(BT* T1){
	assert(!isEmpty());
	assert(Left()->isEmpty());
	delete Left();
	LeftTree = T1;
}

template <class BTElementType>
class BST : public BT <BTElementType>{
	using BT<BTElementType>::NullTree;
public:
	BST();
	void Add(const BTstr&, const BTElementType&, const BTElementType&);
	void Find(const BTElementType&, const BTElementType&);//,BST<BTElementType>*
	BST<BTElementType>* Retrieve(const BTElementType&, const BTElementType&);
	void MOD(const BTstr&, const BTElementType& , const BTElementType&); //Modify title
	BST<BTElementType>* Delete(const BTElementType&, const BTElementType&, BST<BTElementType>*);
	void Print();
	void EmptyPrint(const BTElementType&, const BTElementType&);
	bool IsBST(BST<BTElementType>* );

private:
	BST<BTElementType>* getMin();

	BTstr Title;
	int Hour;
	int Day;
	BST* BSTPTR;
	BST* RightTree;
	BST* LeftTree;
};

template <class BTElementType>
BST<BTElementType>::BST():BT<BTElementType>(){
	NullTree = true;
	RightTree = NULL;
	LeftTree = NULL;
	BSTPTR = NULL;
	Day = 0;
	Hour = 0;
}

template <class BTElementType>
void BST < BTElementType >:: Add(const BTstr& t, const BTElementType& d, const BTElementType& h){
	if(NullTree){
		NullTree = false;
		LeftTree = new BST;
		RightTree = new BST;
		Title = t;
		Day = d;
		Hour = h;
		return;
	}else if(d == Day && Hour == h){//d == Day && h == Hour
		cout<<"Conflict"<<" "<<d<<" "<<h<<endl;
		return;
	}else if(d > Day || (d == Day && h > Hour))
		RightTree->Add(t, d, h);
	else if(d < Day || (d == Day && h < Hour))
		LeftTree->Add(t, d, h);
	return;
}

template <class BTElementType>
bool BST<BTElementType>:: IsBST(BST<BTElementType>* Tree){
	if(Tree->NullTree())	return true;
	if((!Tree->LeftTree->isEmpty() && Tree->LeftTree->getData() > Tree->getData()) || (!Tree->RightTree->isEmpty() && Tree->RightTree->getData() < Tree->getData()))
		return false;
	return isBST(Tree->LeftTree) && isBST(Tree->RightTree);
}


template <class BTElementType>
void BST<BTElementType>:: Find(const BTElementType& d, const BTElementType& h){//, BST<BTElementType>* root
	if(!NullTree){
		if(d == Day && h == Hour){
			cout<<Title<<endl;
			return;
		}
		else if(d > Day || (d == Day && h > Hour))
			RightTree->Find(d, h);
		else if(d < Day || (d == Day && h < Hour))
			LeftTree->Find(d, h);
	}else
		cout<<"Empty"<<" "<<d<<" "<<h<<endl;
	return;
}

template <class BTElementType>
BST<BTElementType>* BST<BTElementType>:: Retrieve(const BTElementType& d, const BTElementType& h){//,
	if (NullTree == true )
		return this;
	else if(d == Day && h == Hour)
		return this;
	else if ( d < Day || ( d == Day && h<Hour))
		return LeftTree->Retrieve(d,h);
	else if ( d > Day || ( d == Day && h > Hour))
		return RightTree->Retrieve(d,h);
}

template <class BTElementType>
void BST<BTElementType>:: MOD(const BTstr& t, const BTElementType& d, const BTElementType& h){
	if(!NullTree){
		if(d == Day && h == Hour)
			Title = t;
		else if(d< Day || ( d == Day && h<Hour))
			LeftTree->MOD(t, d, h);
		else if(d > Day || ( d == Day && h > Hour))
			RightTree->MOD(t, d, h);
	}
	else
		cout<<"Empty"<<" "<<d<<" "<<h<<endl;
}

template <class BTElementType>
BST<BTElementType>* BST<BTElementType>:: getMin(){
	BST* Node;
	Node = this;
    while(!Node->LeftTree->NullTree)
    	Node = Node->LeftTree;
    return Node;
}

template <class BTElementType> //Recheck
BST<BTElementType>* BST<BTElementType>:: Delete(const BTElementType& d, const BTElementType& h, BST<BTElementType>* root){
	if(NullTree)
		return root;
	else if(d > Day || (d == Day && h > Hour))
			RightTree = root->RightTree->Delete(d, h, root->RightTree);
	else if(d < Day || (d == Day && h < Hour)){
			LeftTree = root->LeftTree->Delete(d, h, root->LeftTree);
	}else{
			if(root->LeftTree->NullTree == true && root->RightTree->NullTree == true){// == NULL
				root->NullTree = true;
				delete root;
				return RightTree;
			}else if(root->LeftTree->NullTree == true){
				BST* Node = root;
				root = root->RightTree;
				delete Node;
			}else if(root->RightTree->NullTree == true){
				BST* Node = root;
				root = root->LeftTree;
				delete Node;
			}else{
				BST* Node = root->RightTree;
				Node = Node->getMin();
				Title = Node->Title;
				Day = Node->Day;
				Hour = Node->Hour;
				root->RightTree = root->RightTree->Delete(Node->Day, Node->Hour, root->RightTree);
			}
		}

	return root;
}

template <class BTElementType>
void BST<BTElementType>:: Print(){
	if(!NullTree){
		LeftTree->Print();
		cout<<Title<<" "<<Day<<" "<<Hour<<endl;
		RightTree->Print();
	}
}

template <class BTElementType>
void BST<BTElementType>:: EmptyPrint(const BTElementType& d, const BTElementType& h){
	cout<<"Empty"<<" "<<d<<" "<<h<<endl;
}
#endif
