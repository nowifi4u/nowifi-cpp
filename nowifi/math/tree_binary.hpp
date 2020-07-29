#pragma once

#include <utility>

namespace nw {

	template <class Ty>
	struct TreeNode
	{
		using TreeNode_type = TreeNode<Ty>;

		Ty data;
		TreeNode_type* parent;
		TreeNode_type* left;
		TreeNode_type* right;

		TreeNode() = delete;

		TreeNode(const Ty& val)
			: data(val)
		{
			this->_nullall();
		}

		TreeNode(Ty&& val)
			: data(std::move(val))
		{
			this->_nullall();
		}

		TreeNode(const TreeNode_type& val)
			: data(val.data)
		{
			this->_nullall();
		}

		TreeNode(const Ty& val, const Ty& val_left)
			: data(val)
		{
			this->parent = nullptr;
			this->appendLeft(val_left);
			this->right = nullptr;
		}

		TreeNode(Ty&& val, Ty&& val_left)
			: data(std::move(val))
		{
			this->parent = nullptr;
			this->appendLeft(std::move(val_left));
			this->right = nullptr;
		}

		TreeNode(const Ty& val, const Ty& val_left, const Ty& val_right)
			: data(val)
		{
			this->parent = nullptr;
			this->appendLeft(val_left);
			this->appendRight(val_right);
		}

		TreeNode(Ty&& val, Ty&& val_left, Ty&& val_right)
			: data(std::move(val))
		{
			this->parent = nullptr;
			this->appendLeft(std::move(val_left));
			this->appendRight(std::move(val_right));
		}

		~TreeNode()
		{
			if (this->left != nullptr) this->left->~TreeNode();
			if (this->right != nullptr) this->right->~TreeNode();
			// this->data destructor
		}

	protected:

		void _nullall()
		{
			this->parent = nullptr;
			this->left = nullptr;
			this->right = nullptr;
		}

		void _appendLeft(TreeNode_type* cell)
		{
			this->left = cell;
			cell->parent = this;
		}

		void _appendRight(TreeNode_type* cell)
		{
			this->right = cell;
			cell->parent = this;
		}

	public:

		bool hasLeft() const
		{
			return this->left != nullptr;
		}

		bool noLeft() const
		{
			return this->left == nullptr;
		}

		bool hasRight() const
		{
			return this->right != nullptr;
		}

		bool noRight() const
		{
			return this->right == nullptr;
		}

		bool hasParent() const
		{
			return this->parent != nullptr;
		}

		bool noParent() const
		{
			return this->parent == nullptr;
		}

		bool isLeaf() const
		{
			return this->noLeft() && this->noRight();
		}


		bool appendLeft(TreeNode_type* child)
		{
			if (child == nullptr) return false;
			if (this->left == nullptr) return false;

			this->_appendLeft(child);
			return true;
		}

		bool appendLeft(const Ty& value)
		{
			if (this->left == nullptr) return false;

			auto child = new TreeNode_type(value);
			this->_appendLeft(child);
			return true;
		}

		bool appendLeft(Ty&& value)
		{
			if (this->left == nullptr) return false;

			auto child = new TreeNode_type(std::move(value));
			this->_appendLeft(child);
			return true;
		}



		void appendRight(TreeNode_type* cell)
		{
			if (cell == nullptr) return;
			this->right = cell;
			cell->parent = this;
		}

		bool appendRight(const Ty& value)
		{
			if (this->right == nullptr) return false;

			auto child = new TreeNode_type(value);
			this->_appendRight(child);
			return true;
		}

		bool appendRight(Ty&& value)
		{
			if (this->right == nullptr) return false;

			auto child = new TreeNode_type(std::move(value));
			this->_appendRight(child);
			return true;
		}



		TreeNode_type* disconnectLeft()
		{
			if (this->left == nullptr) return nullptr;
			auto child = this->left;
			this->left = nullptr;
			child->parent = nullptr;
			return child;
		}

		TreeNode_type* disconnectRight()
		{
			if (this->right == nullptr) return nullptr;
			auto child = this->right;
			this->right = nullptr;
			child->parent = nullptr;
			return child;
		}

		bool isLeftChild() const
		{
			if (this->parent == nullptr) return false;
			return this->parent->left == this;
		}

		bool isRightChild() const
		{
			if (this->parent == nullptr) return false;
			return this->parent->right == this;
		}

		TreeNode_type** getParentLink()
		{
			if (this->parent == nullptr) return nullptr;
			if (this->isLeftChild())
			{
				return &(this->parent->left);
			}
			if (this->isRightChild())
			{
				return &(this->parent->right);
			}
		}

		TreeNode_type* disconnectParent()
		{
			if (this->parent == nullptr) return nullptr;
			auto parent = this->parent;
			if (this->isLeftChild())
			{
				parent->disconnectLeft();
			}
			else if (this->isRightChild())
			{
				parent->disconnectRight();
			}
			return parent;
		}

		TreeNode_type* search(const Ty& value) const
		{
			if (this->data == value) return this;
			TreeNode_type* result = nullptr;
			if (this->left != nullptr) result = this->left->search(value);
			if (result != nullptr) return result;
			if (this->right != nullptr) result = this->right->search(value);
			return result;
		}

		template <class UnaryPredicate>
		TreeNode_type* search(UnaryPredicate f) const
		{
			if (f(this->data)) return this;
			TreeNode_type* result = nullptr;
			if (this->left != nullptr) result = this->left->search(f);
			if (result != nullptr) return result;
			if (this->right != nullptr) result = this->right->search(f);
			return result;
		}

	}; // class TreeNode

	//template <class Ty>
	//void swap(TreeNode<Ty>& node1, TreeNode<Ty>& node2)
	//{
		//std::swap(node1.data, node2.data);

		//auto node1_i_child = node1.getParentLink();
		//auto node2_i_child = node2.getParentLink();

		//std::swap(node1.parent, node2.parent);
		//if (node2_i_child != nullptr) *node2_i_child = &node1;
		//if (node1_i_child != nullptr) *node1_i_child = &node2;

		//std::swap(node1.left, node2.left);
		//if (node1.left != nullptr) node1.left->parent = &node1;
		//if (node2.left != nullptr) node2.left->parent = &node2;

		//std::swap(node1.right, node2.right);
		//if (node1.right != nullptr) node1.right->parent = &node1;
		//if (node2.right != nullptr) node2.right->parent = &node2;
	//}

} // namespace nw