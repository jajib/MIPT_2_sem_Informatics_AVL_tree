#include "stdlib.h"
#include <iostream>
#include <vector>
#include <cmath>

struct Tree_Node
{
	int value;
	Tree_Node* left;
	Tree_Node* right;
		
	Tree_Node(int temp_value = 0, Tree_Node* left_n = nullptr, Tree_Node* right_n = nullptr)
	{
		value = temp_value;
		left = left_n;
		right = right_n;
	};
	
	int Height(int level = 0)
	{
		if (this == nullptr)
		{
			return 0;
		}
		
		int left_h = 0;
		int right_h = 0;
		
		if (left == nullptr && right == nullptr)
		{
			return level;
		}
		
		if (left != nullptr)
		{
			left_h += left->Height(level+1);
		}
		if (right != nullptr)
		{
			right_h += right->Height(level+1);
		}
		
		return (left_h < right_h ? right_h : left_h);
	}
	
	int Balance()
	{
		return left->Height() - right->Height();
	}
	
	Tree_Node* Copy()
	{	
		if (this == nullptr)
		{
			return nullptr;
		}
		
		
		Tree_Node* copy_node = new Tree_Node(value);
		
		if (left == nullptr && right == nullptr)
		{
			return copy_node;
		}
		
		if (left != nullptr)
		{
			copy_node->left = left->Copy();
		}
		
		if (right != nullptr)
		{
			copy_node->right = right->Copy();
		}
		
		return copy_node;
	}
	
	Tree_Node* R()
	{
		Tree_Node* z = new Tree_Node(value, left->right->Copy(), right->Copy());
		Tree_Node* ret = new Tree_Node(left->value, left->left->Copy(), z);
		
		return ret;
	}
	
	Tree_Node* LR()
	{
		Tree_Node* y = new Tree_Node(left->value, left->left->Copy(), left->right->left->Copy());
		Tree_Node* x = new Tree_Node(left->right->value, y, left->right->right->Copy());
		Tree_Node* ret = new Tree_Node(value, x, right->Copy());
		
		return ret;
	}
	
	Tree_Node* RR()
	{
		Tree_Node* z = new Tree_Node(value, left->Copy(), right->left->Copy());
		Tree_Node* x = new Tree_Node(right->right->value, right->right->left->Copy(),
		                             right->right->right->Copy());
		Tree_Node* ret = new Tree_Node(right->value, z, x);
		
		return ret;
	}
	
	Tree_Node* RL()
	{
		Tree_Node* y = new Tree_Node(right->value, right->left->right->Copy(), right->right->Copy());
		Tree_Node* x = new Tree_Node(right->left->value, right->left->left->Copy(), y);
		Tree_Node* ret = new Tree_Node(value, left->Copy(), x);
		
		return ret;
	}
	
	int BalanceNode()
	{
		if ((right->Height() - left->Height()) == 2 && right->left->Height() <= right->right->Height())
		{
			Tree_Node* buf = RR();
				
			value = buf->value;
			left = buf->left;
			right = buf->right;
		}
		else if ((right->Height() - left->Height()) == 2 && right->left->Height() > right->right->Height())
		{
			Tree_Node* buf = RL()->RR();
				
			value = buf->value;
			left = buf->left;
			right = buf->right;
		}
		else if ((left->Height() - right->Height()) == 2 && left->right->Height() <= left->left->Height())
		{
			Tree_Node* buf = R();
				
			value = buf->value;
			left = buf->left;
			right = buf->right;
		}
		else if ((left->Height() - right->Height()) == 2 && left->right->Height() > left->left->Height())
		{
			Tree_Node* buf = LR()->R();
				
			value = buf->value;
			left = buf->left;
			right = buf->right;
		}
	}
	
	int add_elem (int new_value, bool balance = true)
	{	
		if (new_value <= value)
		{
			
			if(left != nullptr)
			{	
				left->add_elem(new_value, false);
				
				left->BalanceNode();
			}
			else
			{		
				Tree_Node* buf = new Tree_Node(new_value);
				
				left = buf;
			}
		}
		else
		{	
			if(right != nullptr)
			{
				right->add_elem(new_value, false);
				
				right->BalanceNode();
			}
			else
			{
				Tree_Node* buf = new Tree_Node(new_value);
				
				right = buf;
			}
		}
		
		if (balance == true)
		{
			BalanceNode();
		}
	};
	
	Tree_Node* find_value(int find_num)
	{	
		if (find_num == value)
		{
			return this;
		}
		else if (find_num < value && left != nullptr)
		{
			return left->find_value(find_num);
		}
		else if (find_num >= value && right != nullptr)
		{
			return right->find_value(find_num);
		}
		
		return nullptr;
	};
	
	Tree_Node* find_prev(int find_num)
	{
		if ((left != nullptr && find_num == left->value) || (right != nullptr && find_num == right->value))
		{
			return this;
		}

		if (find_num < value && left != nullptr)
		{
			return left->find_prev(find_num);
		}
		else if (find_num >= value && right != nullptr)
		{
			return right->find_prev(find_num);
		}
		
		return nullptr;
	};
	
	Tree_Node* find_nearest (int find_num)
	{
		if (left == nullptr && right == nullptr)
		{
			return this;
		}
		
		Tree_Node* first_node = (left == nullptr ? right : left);
		Tree_Node* second_node = (right == nullptr ? left : right);
		
		return (abs(first_node->value-find_num) < abs(second_node->value-find_num) ? first_node->Copy() : second_node->Copy());
	}
	
	Tree_Node* remove_by_value(int remove_num, bool check_root = true)
	{		
		
		if (value == remove_num && check_root == true)
		{
			return nullptr;
		}
			
		Tree_Node* prev_node = find_prev(remove_num);
		
		if (prev_node == nullptr)
		{
			return nullptr;
		}
		
		Tree_Node* del_node = (prev_node->left->value == remove_num ? prev_node->left : prev_node->right);
		Tree_Node* buf = new Tree_Node (del_node->value);
		
		if (del_node->left == nullptr && del_node->right == nullptr)
		{
			if (prev_node->left->value == del_node->value)
			{
				prev_node->left = nullptr;
			}
			else
			{
				prev_node->right = nullptr;
			}
			
			return buf;
		}
		
		Tree_Node* nearest = del_node->find_nearest(remove_num);
		
		if (del_node->value == prev_node->left->value)
		{
			prev_node->left = new Tree_Node(nearest->value, prev_node->left->left, prev_node->left->right);

			prev_node->left->remove_by_value(nearest->value, false);
		}
		else
		{
			prev_node->right = new Tree_Node(nearest->value, prev_node->right->left, prev_node->right->right);

			prev_node->right->remove_by_value(nearest->value, false);
		}
		
		return buf;
	}
	
	int print(int level = 0)
	{
		if (this == nullptr)
		{
			return -1;
		}
		
		for (int i = 0; i < level; i++)
		{
			std::cout << "\t";	
		}	
			
		std::cout << value << "\n";
		
            	
    	if (right != nullptr)
		{
			right->print(level+1);       
		}
		else
		{
			for (int i = 0; i <= level; i++)
    		{
    			std::cout << "	";
    		}
			
			std::cout << "#\n";
		}
		
		if (left != nullptr)
		{
			left->print(level+1);        
    	}
    	else
    	{
    		for (int i = 0; i <= level; i++)
    		{
    			std::cout << "	";
    		}
    		
			std::cout << "#\n";
    	}
	};
};

int main()
{
	Tree_Node my_tree = Tree_Node(0);
	
	std::vector<int> tree_data = {101, 102, 110, 199, 124, 137, 186, 1100};
	
	for (int k = 0; k < 10; k++)
	{
		tree_data.push_back(rand() % 99 + 1);
	}
	
	for (auto cnt: tree_data)
	{
		my_tree.add_elem(cnt);
		//my_tree.print();
	}
	
	my_tree.print();
		
	my_tree.remove_by_value(199)->print();
	my_tree.remove_by_value(124)->print();
	
	my_tree.print();
}