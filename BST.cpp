#include "BST.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

/**************************************************************/
/* These are the methods you are to write for a BST           */
/* More Detailed Instructions can be found in the doc and in  */
/* the BST.hpp file                                           */
/**************************************************************/

BST::BST(string n, string st, string descr, bool Xtra) {
//you write
	root = new BSTNode(n,st,descr);
	Xt = Xtra;
}

bool BST::insert(string n, string st, string descr) {
// you write

		if(root==NULL) {
			root = new BSTNode(n,st,descr);
			setHeight(root);
			return true;
		}

			BSTNode *temp = root;
			while(temp!=NULL) {
				if(n < temp->animal->name ) {
					if(temp->left==NULL) {
						temp->left = new BSTNode(n,st,descr);
						temp->left->parent = temp;
						setHeight(temp->left);
						return true;
					}
					temp = temp->left;
				} // end of if it is less than the parent
				else if(n > temp->animal->name ) {
					if(temp->right==NULL) {
						temp->right = new BSTNode(n,st,descr);
						temp->right->parent = temp;
						setHeight(temp->right);
						return true;
					}
					temp = temp->right;
				}//end of if it is greater than the parent
				else {
					return false;
				} // if not greater or less than, then it is a duplicate so returns false
			}
			return false;
}


BSTNode *BST::find(string n) {
//you write
	if(root==NULL) {
		return NULL;
	}

	BSTNode *temp = root;

	while(temp!=NULL) {
		if(n == temp->animal->name) {
			cout<<"Found: ";
			temp->printNode(false);
			return temp;
		}else if(temp->animal->name > n) {
			temp = temp->left;
		}else {
			temp = temp->right;
		}
	}

	cout<<n<<": Not Found"<<endl;
	return NULL;

}

void BST::updateStatus(string n, string st) {
// you write
	BSTNode *temp = root;

	while(temp!=NULL) {
		if(n == temp->animal->name) {
			temp->animal->status = st;
			temp->printNode(true);
			return;
		}else if(temp->animal->name > n) {
			temp = temp->left;
		}else {
			temp = temp->right;
		}
	}
}
void BST::printTreeIO(BSTNode *tmp) {
// you write
	if(tmp!=NULL) {
		printTreeIO(tmp->left);
		tmp->printNode(false);
		printTreeIO(tmp->right);
	}

}

void BST::printTreePre(BSTNode *tmp) {
// you write
	if(tmp!=NULL) {
		tmp->printNode(false);
		printTreePre(tmp->left);
		printTreePre(tmp->right);
	}

}

void BST::printTreePost(BSTNode *tmp) {
//you write
	if(tmp!=NULL) {
		printTreePost(tmp->left);
		printTreePost(tmp->right);
		tmp->printNode(false);
	}

}

void BST::setHeight(BSTNode *tmp) {
// you write
	if(tmp==NULL) {
		return;
	}

	// case 1 ... the left child is null but the right one has values
	if(tmp->left==NULL and tmp->right!=NULL){
		tmp->height = 1 + tmp->right->height;
	}
	//case 2 is case 1 reverse
	else if(tmp->left!=NULL and tmp->right==NULL){
		tmp->height = 1 + tmp->left->height;
	}
	//case 3, both nodes are present
	else if(tmp->left!=NULL and tmp->right!=NULL) {
		tmp->height = max(tmp->right->height,tmp->left->height) + 1;
	}
	else if(tmp->left==NULL and tmp->right==NULL) {
		tmp->height = 1;
	}

	setHeight(tmp->parent);

}

BSTNode *BST::removeNoKids(BSTNode *tmp) {
// you write
	//case 1: this is the parents Left node
	if(tmp->parent->left == tmp) {
		tmp->parent->left = NULL;
		cout<<"Removing: ";
		tmp->printNode(true);
		setHeight(tmp->parent);
		delete tmp;
	}
	//case 2: this is the parents Right node
	else {
		tmp->parent->right = NULL;
		cout<<"Removing: ";
		tmp->printNode(true);
		setHeight(tmp->parent);
		delete tmp;
	}

}

BSTNode *BST::removeOneKid(BSTNode *tmp,bool leftFlag) {
// you write
	//case 1: the child is on the left hand side
	if(tmp->parent->left == tmp) {
		if(leftFlag) {
			tmp->parent->left = tmp->left;
			tmp->left->parent = tmp->parent;
			setHeight(tmp->parent);
			delete tmp;
		}else {
			tmp->parent->right = tmp->right;
			tmp->right->parent = tmp->parent;
			setHeight(tmp->parent);
			delete tmp;
		}
	}

	//case 2, the tmp node is the parents right child
	else {
		if(leftFlag) {
			tmp->parent->right = tmp->left;
			tmp->left->parent = tmp->parent;
			setHeight(tmp->parent);
			delete tmp;
		}else {
			tmp->parent->right = tmp->right;
			tmp->right->parent = tmp->parent;
			setHeight(tmp->parent);
			delete tmp;
		}
	}
}

BSTNode *BST::remove(string s){
// you write
	//Step 1:
	//find the tmp node that has s as its animal name
	//Step 2:
	//Check if the tmp node has 0/1/2 nodes
	//Step 3:
	//If 0 or 1 node, call helper functions, other use the deletion method for 2 children in here

	BSTNode *temp = find(s);

	//the above finds the node with the animal name as string s
	// now we check the number of nodes
	if(temp->left==NULL and temp->right==NULL) {
		removeNoKids(temp);

	}
	else if(temp->left!=NULL and temp->right==NULL) {
		removeOneKid(temp, true);
	}
	else if(temp->left==NULL and temp->right!=NULL) {
		removeOneKid(temp, false);
	}

	//remove node with 2 kids
	else {
		BSTNode *curr = temp->left;;
		while(curr->right!=NULL) {
			curr = curr->right;
		}


		if(curr->parent->left == curr) {
			curr->parent->left = NULL;
		}else {
			curr->parent->right = NULL;
		}
		setHeight(curr->parent);

		//swap values with temp
		curr->parent = temp->parent;
		curr->left = temp->left;
		curr->right = temp->right;

		//make temps parent points to curr
		//if its the root, we dont have to do anything since its parent doesnt point to anything

		if(temp->parent->left == temp) {
			temp->parent->left = curr;
		}else if(temp->parent->right == temp){
			temp->parent->right = curr;
		}

		setHeight(curr);
		delete temp;
	}

}

/**************** Written for you  ***********************/

BST::BST(bool Xtra) {
	root = NULL;
	Xt = Xtra;
}


void BST::clearTree() {
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}
void BST::clearTree(BSTNode *tmp) {
	if (tmp == NULL) {
		return;
	}
	else {
		clearTree(tmp->left);
		clearTree(tmp->right);
		tmp->printNode(Xt);
		delete(tmp);
	}
}
void BST::printTreePost() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PostOrder:" <<endl;
		printTreePost(root);
	}
}

void BST::printTreePre() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PreOrder:" <<endl;
		printTreePre(root);
	}
}

void BST::printTreeIO() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing In Order:" <<endl;
		printTreeIO(root);
	}
}






