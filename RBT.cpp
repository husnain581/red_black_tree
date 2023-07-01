#include<iostream>
#include<fstream>
using namespace std;
template<class t>
struct node
{
	t data;
	node<t> *leftchild;
	node<t> *rightchild;
	int count = 1;
	char colour;
};
template<class t>
class Red_Black_Tree
{
	node<t> *root;
	void LNR(node<t>* temp)
	{
		if (temp != nullptr)
		{
			LNR(temp->leftchild);
			cout << temp->data << "   " << temp->colour << "   " << temp->count << endl;
			LNR(temp->rightchild);
		}
	}
	void NLR(node<t>* temp)
	{
		if (temp != nullptr)
		{
			cout << temp->data << "   " << temp->colour << "   " << temp->count << endl;
			LNR(temp->leftchild);
			LNR(temp->rightchild);
		}
	}
	void LRN(node<t>* temp)
	{
		if (temp != nullptr)
		{
			LNR(temp->leftchild);
			LNR(temp->rightchild);
			cout << temp->data << "   " << temp->colour << "   " << temp->count << endl;
		}
	}
	void NRL(node<t>* temp)
	{
		if (temp != nullptr)
		{
			cout << temp->data << "   " << temp->colour << "   " << temp->count << endl;
			LNR(temp->rightchild);
			LNR(temp->leftchild);
		}
	}
	void RNL(node<t>* temp)
	{
		if (temp != nullptr)
		{
			LNR(temp->rightchild);
			cout << temp->data << "   " << temp->colour << "   " << temp->count << endl;
			LNR(temp->leftchild);
		}
	}
	void RLN(node<t>* temp)
	{
		if (temp != nullptr)
		{
			LNR(temp->rightchild);
			LNR(temp->leftchild);
			cout << temp->data << "   " << temp->colour << "   " << temp->count << endl;
		}
	}
	void colouring(node<t> *grand_parent)
	{
		if (grand_parent != root)
			grand_parent->colour = 'r';
		grand_parent->leftchild->colour = 'b';
		grand_parent->rightchild->colour = 'b';
	}
	void left_rotation(node<t> *&grand_parent, node<t> *&parent)
	{
		if (root == grand_parent)
		{
			root = parent;
			if (parent->rightchild != nullptr)
			{
				grand_parent->leftchild = parent->rightchild;
				parent->rightchild = grand_parent;
			}
			else
			{
				parent->rightchild = grand_parent;
				grand_parent->leftchild = nullptr;
			}
			grand_parent->colour = 'r';
			root->colour = 'b';
			
			parent = root->rightchild;
			grand_parent = root;
		}
		else if (root->leftchild == grand_parent)
		{
			root->leftchild = parent;
			if (parent->rightchild != nullptr)
			{
				grand_parent->leftchild = parent->rightchild;
				parent->rightchild = grand_parent;
			}
			else
			{
				parent->rightchild = grand_parent;
				grand_parent->leftchild = nullptr;
			}
			parent->colour = 'b';
			parent->rightchild->colour = 'r';

			parent = parent->rightchild;
			grand_parent = root->leftchild;
		}
		else
		{
			node<t> *temp = root;
			while (1)
			{
				if (temp->leftchild == grand_parent)
					break;
				else if (temp->rightchild == grand_parent)
					break;
				if (temp->data < grand_parent->data)
					temp = temp->rightchild;
				else
					temp = temp->leftchild;

			}
			if (grand_parent==temp->leftchild)
				temp->leftchild = parent;
			else
				temp->rightchild = parent;
			if (parent->rightchild != nullptr)
			{
				grand_parent->leftchild = parent->rightchild;
				parent->rightchild = grand_parent;
			}
			else
			{
				parent->rightchild = grand_parent;
				grand_parent->leftchild = nullptr;
			}

			parent->colour = 'b';
			parent->rightchild->colour = 'r';

			parent = parent->rightchild;
			grand_parent = temp->leftchild;
		}
	}
	void right_rotation(node<t> *&grand_parent, node<t> *&parent)
	{
		if (root == grand_parent)
		{
			root = parent;
			if (parent->leftchild!=nullptr)
			{
				grand_parent->rightchild = parent->leftchild;
				parent->leftchild = grand_parent;
			}
			else
			{
				parent->leftchild = grand_parent;
				grand_parent->rightchild = nullptr;
			}
			
			parent->colour = 'b';
			grand_parent->colour = 'r';

			parent = parent->leftchild;
			grand_parent = root;
		}
		else if (root->rightchild == grand_parent)
		{
			root->rightchild = parent;
			if (parent->leftchild != nullptr)
			{
				grand_parent->rightchild = parent->leftchild;
				parent->leftchild = grand_parent;
			}
			else
			{
				parent->leftchild = grand_parent;
				grand_parent->rightchild = nullptr;
			}

			parent->colour = 'b';
			parent->leftchild->colour = 'r';

			parent = parent->leftchild;
			grand_parent = root->rightchild;
		}
		else
		{
			node<t> *temp = root;
			while (1)
			{
				if (temp->rightchild == grand_parent)
					break;
				else if (temp->leftchild == grand_parent)
					break;
				if (temp->data < grand_parent->data)
					temp = temp->rightchild;
				else
					temp = temp->leftchild;

			}
			if (grand_parent==temp->leftchild)
				temp->leftchild = parent;
			else
				temp->rightchild = parent;
			if (parent->leftchild != nullptr)
			{
				grand_parent->rightchild = parent->leftchild;
				parent->leftchild = grand_parent;
			}
			else
			{
				parent->leftchild = grand_parent;
				grand_parent->rightchild = nullptr;
			}

			parent->colour = 'b';
			parent->leftchild->colour = 'r';

			parent = parent->leftchild;
			grand_parent = temp->rightchild;
		}
	}
	void convert_right(node<t> *&grand_parent, node<t> *&parent)
	{
		grand_parent->rightchild = parent->leftchild;
		grand_parent->rightchild->rightchild = parent;
		parent->leftchild = nullptr;
		parent = grand_parent->rightchild;
		right_rotation(grand_parent, parent);
	}
	void convert_left(node<t> *&grand_parent, node<t> *&parent)
	{
		grand_parent->leftchild = parent->rightchild;
		grand_parent->leftchild->leftchild = parent;
		parent->rightchild = nullptr;
		parent = grand_parent->leftchild;
		left_rotation(grand_parent, parent);
	}
	void des(node<t> *temp)
	{
		if (temp != nullptr)
		{
			des(temp->leftchild);
			des(temp->rightchild);
			delete temp;
		}
	}
	void duplicate(node<t> *temp)
	{
		if (temp != nullptr)
		{
			temp->count = 1;
			duplicate(temp->leftchild);
			duplicate(temp->rightchild);
		}
	}
public:
	Red_Black_Tree()
	{
		root = nullptr;
	}
	void insert_in_tree(t value)
	{
		bool duplicate = false;
		node<t> *new_node = new node < t > ;
		new_node->data = value;
		new_node->colour = 'r';
		new_node->leftchild = nullptr;
		new_node->rightchild = nullptr;
		node<t> *parent;
		node<t> *grand_parent;
		if (root == nullptr)
		{
			root = new_node;
			root->colour = 'b';
			parent = root;
			grand_parent = root;
		}
		else
		{
			parent = root;
			grand_parent = root;
			while (true)
			{
				if (new_node->data < parent->data)
				{
					if (parent->leftchild == nullptr)
					{
						parent->leftchild = new_node;
						break;
					}
					grand_parent = parent;
					parent = parent->leftchild;
				}
				else
				{
					if (parent->data == new_node->data)
					{
						duplicate = true;
						parent->count++;
						break;
					}
					else
					{
						if (parent->rightchild == nullptr)
						{
							parent->rightchild = new_node;
							break;
						}
						grand_parent = parent;
						parent = parent->rightchild;
					}
				}
			}
		}
		if (duplicate == false)
		{
			if (new_node != root && new_node != root->leftchild && new_node != root->rightchild)
			{
				if (grand_parent->leftchild == parent&&grand_parent->rightchild != nullptr)
				{
					if (grand_parent->rightchild->colour == 'r')
					{
						colouring(grand_parent);
					}
				}
			   else if (grand_parent->rightchild == parent&&grand_parent->leftchild != nullptr)
				{
				   if (grand_parent->leftchild->colour == 'r')
				   {
					   colouring(grand_parent);
				   }
				}
				else if (grand_parent->leftchild == parent&&new_node == parent->leftchild)
				{
					if (grand_parent->rightchild == nullptr || grand_parent->rightchild->colour == 'b')
					{
						left_rotation(grand_parent, parent);
					}
				}
				else if (grand_parent->leftchild == parent&&new_node == parent->rightchild)
				{
					convert_left(grand_parent, parent);
				}
				else if (grand_parent->rightchild == parent&&new_node == parent->rightchild)
				{
					if (grand_parent->leftchild == nullptr || grand_parent->leftchild->colour == 'b')
					{
						right_rotation(grand_parent, parent);
					}
				}
				else if (grand_parent->rightchild == parent&&new_node == parent->leftchild)
				{
					if (grand_parent->leftchild == nullptr || grand_parent->leftchild->colour == 'b')
					{
						convert_right(grand_parent, parent);
					}
				}
				else if (grand_parent->leftchild == parent&&new_node == parent->rightchild)
				{
					if (grand_parent->rightchild == nullptr || grand_parent->rightchild->colour == 'b')
					{
						convert_left(grand_parent, parent);
					}
				}
			}
			if (new_node != root && new_node != root->leftchild && new_node != root->rightchild)
			{
				while (1)
				{
					node<t> *temp = root;
					while (1)
					{
						if (root == grand_parent)
							break;
						else if (temp->rightchild == grand_parent)
							break;
						else if (temp->leftchild == grand_parent)
							break;
						if (temp->data < grand_parent->data)
							temp = temp->rightchild;
						else
							temp = temp->leftchild;
					}
					new_node = parent;
					parent = grand_parent;
					grand_parent = temp;
					if (parent->colour == 'r' && (parent->leftchild->colour == 'r' || parent->rightchild->colour == 'r'))
					{
						if (parent->leftchild!=nullptr && parent->leftchild->colour == 'r'&& parent == grand_parent->leftchild)
						{
							if (grand_parent->rightchild != nullptr && grand_parent->rightchild->colour == 'r')
							{
								colouring(grand_parent);
							}
							else
							{
								left_rotation(grand_parent, parent);
							}
						}
						else if (parent->leftchild!=nullptr && parent->leftchild->colour == 'r'&& parent == grand_parent->rightchild)
						{
							if (grand_parent->leftchild == nullptr || grand_parent->leftchild->colour == 'b')
								convert_left(grand_parent, parent);
							else
								colouring(grand_parent);
						}
						else if (parent->rightchild->colour == 'r'&&parent == grand_parent->leftchild)
						{
							if (grand_parent->rightchild == nullptr || grand_parent->rightchild->colour == 'b')
							{
								convert_right(grand_parent, parent);
							}
							else
							{
								colouring(grand_parent);
							}
						}
						else if (parent->rightchild->colour == 'r'&&parent == grand_parent->rightchild)
						{
							if (grand_parent->leftchild->colour == 'r')
								colouring(grand_parent);
							else
							{
								right_rotation(grand_parent, parent);
							}
						}
					}
					if (temp == root)
						break;
				}
			}
		}
	}
	void delete_from_tree(t value)
	{
		if (root == nullptr)
			cout << "the tree is empty" << endl;
		else if (root->data == value&&root->leftchild == nullptr&&root->rightchild == nullptr)
		{
			delete root;
			root = nullptr;
		}
		else
		{
			bool result;
			node<t> *deletion_node = root;
			node<t> *parent_deletion_node = root;
			node<t> *parent = root;
			node<t> *grand_parent = root;
			if (root->data == value)
				result = true;
			else
			{
				while (1)
				{
					parent_deletion_node = deletion_node;
					if (deletion_node->data > value)
						deletion_node = deletion_node->leftchild;
					else
						deletion_node = deletion_node->rightchild;
					if (deletion_node == nullptr)
					{
						result = false;
						break;
					}
					if (deletion_node->data == value)
					{
						result = true;
						break;
					}
				}
			}
			if (result == true)
			{
				if (deletion_node->count > 1)
				{
					deletion_node->count--;
					result = false;
				}
				else
				{
					if (deletion_node == root)
					{
						if (root->leftchild != nullptr)
						{
							node<t> *replacement = deletion_node->leftchild;
							node<t> *parent_replacement = deletion_node;
							while (replacement->rightchild != nullptr)
							{
								parent_replacement = replacement;
								replacement = replacement->rightchild;
							}
							if (deletion_node->leftchild == replacement)
							{
								deletion_node->data = replacement->data;
								deletion_node->count = replacement->count;
								deletion_node->leftchild = replacement->leftchild;
								replacement->leftchild = nullptr;
								delete replacement;
							}
							else
							{
								deletion_node->data = replacement->data;
								deletion_node->count = replacement->count;
								parent_replacement->rightchild = replacement->leftchild;
								delete replacement;
							}
						}
						else
						{
							node<t> *replacement = deletion_node->rightchild;
							node<t> *parent_replacement = deletion_node;
							while (replacement->leftchild != nullptr)
							{
								parent_replacement = replacement;
								replacement = replacement->leftchild;
							}
							if (deletion_node->rightchild == replacement)
							{
								deletion_node->data = replacement->data;
								deletion_node->count = replacement->count;
								deletion_node->rightchild = replacement->rightchild;
								replacement->rightchild = nullptr;
								delete replacement;
							}
							else
							{
								deletion_node->data = replacement->data;
								deletion_node->count = replacement->count;
								parent_replacement->leftchild = replacement->rightchild;
								delete replacement;
							}
						}
					}
					else if (deletion_node->leftchild != nullptr&&deletion_node->rightchild != nullptr)
					{
						node<t> *replacement = deletion_node->leftchild;
						node<t> *parent_replacement = deletion_node;
						while (replacement->rightchild != nullptr)
						{
							parent_replacement = replacement;
							replacement = replacement->rightchild;
						}
						if (deletion_node->leftchild == replacement)
						{
							deletion_node->data = replacement->data;
							deletion_node->count = replacement->count;
							deletion_node->leftchild = replacement->leftchild;
							replacement->leftchild = nullptr;
							delete replacement;
						}
						else
						{
							deletion_node->data = replacement->data;
							deletion_node->count = replacement->count;
							parent_replacement->rightchild = replacement->leftchild;
							delete replacement;
						}
					}
					else if (deletion_node->rightchild == nullptr&&deletion_node->leftchild == nullptr)
					{
						if (deletion_node->data < parent_deletion_node->data)
						{
							delete deletion_node;
							parent_deletion_node->leftchild = nullptr;
						}
						else
						{
							delete deletion_node;
							parent_deletion_node->rightchild = nullptr;
						}
						grand_parent = parent_deletion_node;
					}
					else if (deletion_node->leftchild != nullptr&&deletion_node->rightchild == nullptr)
					{
						if (deletion_node->data < parent_deletion_node->data)
						{
							parent_deletion_node->leftchild = deletion_node->leftchild;
							delete deletion_node;
						}
						else
						{
							parent_deletion_node->rightchild = deletion_node->leftchild;
							delete deletion_node;
						}
						grand_parent = parent_deletion_node;
					}
					else if (deletion_node->leftchild == nullptr&&deletion_node->rightchild != nullptr)
					{
						if (deletion_node->data < parent_deletion_node->data)
						{
							parent_deletion_node->leftchild = deletion_node->rightchild;
							delete deletion_node;
						}
						else
						{
							parent_deletion_node->rightchild = deletion_node->rightchild;
							delete deletion_node;
						}
						grand_parent = parent_deletion_node;
					}
				}
			}
			else
				cout << "the value is not found" << endl;
			
		}
	}
	void searching_value(t value)
	{
		if (root == nullptr)
			cout << "the tree is empty" << endl;
		else if (root->data == value)
			cout << "the value is present in tree" << endl;
		else
		{
			node<t> *temp = root;
			while (1)
			{
				if (value > temp->data)
					temp = temp->rightchild;
				else
					temp = temp->leftchild;
				if (temp == nullptr)
				{
					cout << "the value is not found" << endl;
					break;
				}
				else if (temp->data == value)
				{
					cout << "the value is found" << endl;
					break;
				}
			}
		}
	}
	void lnr()
	{
		if (root == nullptr)
		{
			cout << "the tree is empty" << endl;
		}
		else
		{
			node<t>* temp = root;
			LNR(temp);
		}
	}
	void nlr()
	{
		if (root == nullptr)
		{
			cout << "the tree is empty" << endl;
		}
		else
		{
			node<t>* temp = root;
			NLR(temp);
		}
	}
	void lrn()
	{
		if (root == nullptr)
		{
			cout << "the tree is empty" << endl;
		}
		else
		{
			node<t>* temp = root;
			LRN(temp);
		}
	}
	void nrl()
	{
		if (root == nullptr)
		{
			cout << "the tree is empty" << endl;
		}
		else
		{
			node<t>* temp = root;
			NRL(temp);
		}
	}
	void rnl()
	{
		if (root == nullptr)
		{
			cout << "the tree is empty" << endl;
		}
		else
		{
			node<t>* temp = root;
			RNL(temp);
		}
	}
	void rln()
	{
		if (root == nullptr)
		{
			cout << "the tree is empty" << endl;
		}
		else
		{
			node<t>* temp = root;
			RLN(temp);
		}
	}
	void destructor()
	{
		if (root == nullptr)
			cout << "the tree is empty" << endl;
		else
		{
			des(root);
			root = nullptr;
			cout << "the tree is deleted" << endl;
		}
	}
	void delete_greater(t value)
	{
		if (root == nullptr)
			cout << "the tree is empty" << endl;
		else
		{
			node<t> *temp = root;
			node<t> *parent_temp = root;
			while (1)
			{
				parent_temp = temp;
				if (temp->data<value)
					temp = temp->rightchild;
				else
					temp = temp->leftchild;
				if (temp->data <= value)
					break;
				else if (temp == nullptr)
				{
					cout << "no greater value is found" << endl;
					break;
				}
			}
			if (temp->data >= root->data)
			{
				des(temp->rightchild);
				temp->rightchild = nullptr;
				
			}
			else
			{
				parent_temp->leftchild = nullptr;
				parent_temp = root;
				root = temp;
			}
		}
	}
	void parent_display(t value)
	{
		if (root == nullptr)
			cout << "the tree is empty" << endl;
		else if (root->data == value)
			cout << "its is a root so it has no parents" << endl;
		else
		{
			node<t> *temp = root;
			node<t> *parent_temp = root;
			while (1)
			{
				parent_temp = temp;
				if (value > temp->data)
					temp = temp->rightchild;
				else
					temp = temp->leftchild;
				if (temp == nullptr)
				{
					cout << "the value is not present in the tree" << endl;
					break;
				}
				else if (temp->data == value)
				{
					cout << "the parent of the node is  " << parent_temp->data << " " << parent_temp->colour << " " << parent_temp->count << endl;
					break;
				}
			}
		}
	}
	void delete_duplicate()
	{
		if (root == nullptr)
			cout << "the tree is empty" << endl;
		else
			duplicate(root);
	}
};
int main()
{
	int choice;
	Red_Black_Tree<int> tree;
	while (1)
	{
		cout << "enter 1 to insert in tree" << endl;
		cout << "enter 2 to delete from tree" << endl;
		cout << "enter 3 to search value from tree" << endl;
		cout << "enter 4 for nlr" << endl;
		cout << "enter 5 for lnr" << endl;
		cout << "enter 6 for lrn" << endl;
		cout << "enter 7 for nrl" << endl;
		cout << "enter 8 for rnl" << endl;
		cout << "enter 9 for rln" << endl;
		cout << "enter 10 for destroy the tree" << endl;
		cout << "enter 11 for delete all values greater the value entered" << endl;
		cout << "enter 12 for displaying parent of the node present in tree" << endl;
		cout << "enter 13 for read integer values from file" << endl;
		cout << "enter 14 to delete all duplicate values from tree" << endl;
		cout << "enter 15 to exit" << endl;
		cin >> choice;

		if (choice == 1)
		{
			int value;
			cout << "enter value to insert" << endl;
			cin >> value;
			tree.insert_in_tree(value);
		}
		else if (choice == 2)
		{
			int value;
			cout << "enter value to delete" << endl;
			cin >> value;
			tree.delete_from_tree(value);
		}
		else if (choice == 3)
		{
			int value;
			cout << "enter value to search" << endl;
			cin >> value;
			tree.searching_value(value);
		}
		else if (choice == 4)
		{
			tree.nlr();
		}
		else if (choice == 5)
		{
			tree.lnr();
		}
		else if (choice == 6)
		{
			tree.lrn();
		}
		else if (choice == 7)
		{
			tree.nrl();
		}
		else if (choice == 8)
		{
			tree.rnl();
		}
		else if (choice == 9)
		{
			tree.rln();
		}
		else if (choice == 10)
		{
			tree.destructor();
		}
		else if (choice == 11)
		{
			int value;
			cout << "enter the value" << endl;
			cin >> value;
			tree.delete_greater(value);
		}
		else if (choice == 12)
		{
			int value;
			cout << "enter the value of node" << endl;
			cin >> value;
			tree.parent_display(value);
		}
		else if (choice == 13)
		{
			int data;
			fstream fin("input.txt");
			while (!fin.eof())
			{
				fin >> data;
				tree.insert_in_tree(data);
			}
		}
		else if (choice == 14)
		{
			tree.delete_duplicate();
		}
		else if (choice == 15)
		{
			break;
		}
	}
	return 0;
}