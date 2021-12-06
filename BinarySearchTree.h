//
// Created by galwe on 19/11/2021.
//

#ifndef AVL_BINARYSEARCHTREE_H
#define AVL_BINARYSEARCHTREE_H

#include <cstdlib>
#include <algorithm>
#include <ctgmath>
namespace Ehsan {


    template<class T,class S>
    class BSTNode//---------------BSTNode-----------------------------
    {
    public:
        S key;
        T data;
        BSTNode *left;
        BSTNode *right;
        BSTNode *parent;
        int height;



        explicit BSTNode(S key, T data);

        BSTNode()=default;
        BSTNode(const BSTNode<T,S> &node);

        BSTNode *roll();


        BSTNode &operator=(const BSTNode &node);

        ~BSTNode() = default;
    };//-------------------------------BSTNode END---------------------------


    template<class T,class S>
    class BinarySearchTree//-------------------------------BinarySearchTree---------------------------
    {
    public:
        BSTNode<T,S> *root;

        BinarySearchTree();
        static int countNodes(BSTNode<T,S> * node)
        {
            if(node== nullptr)
            {
                return 0;
            }
            return (countNodes(node->left) + countNodes(node->right) + 1);
        }
        BSTNode<T,S> *removeInternal(BSTNode<T,S> *node);

        static BSTNode<T,S> *leftRotate(BSTNode<T,S> *x) {

            BSTNode<T,S> *y = x->right;
            BSTNode<T,S> *T2 = y->left;

            y->left = x;
            x->right = T2;
            if (x->parent != nullptr) {
                if (x->parent->right == x) {
                    x->parent->right = y;
                } else {
                    x->parent->left = y;
                }
            }
            y->parent = x->parent;
            x->parent = y;

            x->height = getHeight(x);
            y->height = getHeight(y);
            return y;

        }

        static BSTNode<T,S> *rightRotate(BSTNode<T,S> *y) {
            BSTNode<T,S> *x = y->left;
            BSTNode<T,S> *T2 = x->right;

            x->right = y;
            y->left = T2;
            if (y->parent != nullptr) {
                if (y->parent->right == y) {
                    y->parent->right = x;
                } else {
                    y->parent->left = x;
                }
            }
            x->parent = y->parent;
            y->parent = x;

            y->height = getHeight(y);
            x->height = getHeight(x);
            return x;
        }

        static void arrayToTree(BSTNode<T,S>* tree,S *keys, T *datas,int* index)
        {
            if (tree == nullptr)
            {
                return;
            }
            arrayToTree(tree->left,keys,datas,index);
            tree->data = datas[*index];
            tree->key = keys[*index];
            (*index)++;
            arrayToTree(tree->right,keys,datas,index);

        }
        static void treeToArray(S *keys, T *data,int * index, BSTNode<T,S> *tree_root)
        {
            if( tree_root == nullptr)
            {
                return;
            }
            //index has to start from 0!
            treeToArray(keys,data,index,tree_root->left);
            data[*index] = tree_root->data;
            keys[*index] = tree_root->key;
            (*index)++;
            treeToArray(keys,data,index,tree_root->right);
        }

        void merge(T *a, S *a_h , int na, T *b,S *b_h, int nb, T *c,S *c_h);

//        static void ArrayofKey(S *keys, BSTNode<T,S> *tree,int* index) {
//
//            if(tree== nullptr)
//            {
//                return;
//            }
//
//                treeToArray(keys,tree->left,index);
//                keys[*index]=tree->key;
//                (*index)++;
//                treeToArray(keys,tree,index);
//        }
        BSTNode<T,S>* getMaxNode()
        {
            BSTNode<T,S>*node=this->root;
            while( (node != nullptr) && (node->right!= nullptr) )//(node != nullptr) added by saleh, necessary?
            {
                node=node->right;
            }
            return node;
        }
        void clearLeaves(BSTNode<T,S>* root,int height, int* numberofleaves);

        void uniteTrees(BinarySearchTree<T,S> &other);

        BinarySearchTree(const BinarySearchTree &tree);

        BinarySearchTree &operator=(const BinarySearchTree &tree);

        void treeDelete(BSTNode<T,S> *toDelete);

        ~BinarySearchTree();

        BSTNode<T,S>* insert(S key, T data);

        void remove(S key);

        BSTNode<T,S> *find(S key);

        BSTNode<T,S> *copyTreeInternal(BSTNode<T,S>* tree, BSTNode<T,S>* toCopy);
        BSTNode<T,S>* createEmptyFullTree(S* keys,T*data,int min,int max);

        static int calcHeightDiff(BSTNode<T,S> *node);

        static int getHeight(BSTNode<T,S> *node) {
            if (node == nullptr) {
                return 0;
            }
            if (node->left == nullptr && node->right == nullptr) {
                return 1;
            } else if (node->left == nullptr) {
                return 1 + node->right->height;
            } else if (node->right == nullptr) {
                return 1 + node->left->height;
            } else {
                return 1 + std::max(node->left->height,
                                    node->right->height);
            }
        }

    }; //-------------------------------BinarySearchTree END---------------------------


    template<class T,class S>
    BSTNode<T,S>::BSTNode(const BSTNode &node):
            key(node.key),
            data(node.data),
            left(node.left),
            right(node.right),
            parent(node.parent),
            height(node.height)
            {

    }

    template<class T,class S>
    BSTNode<T,S>::BSTNode(S key, T data):
        key(key),
        data(data),
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        height(1)


    {}

    template<class T,class S>
    BSTNode<T,S> &BSTNode<T,S>::operator=(const BSTNode &node) {
        if (this == &node)
            return *this;
        delete this;
        this->data = node.data;
        this->left = node.left;
        this->right = node.right;
        this->height = node.height;
        this->key = node.key;
        this->height=node.height;
        return *this;
    }

    template<class T,class S>
    BinarySearchTree<T,S>::BinarySearchTree():root(nullptr) {
    }

    template<class T,class S>
    BinarySearchTree<T,S>::BinarySearchTree(const BinarySearchTree<T,S> &tree) {
        this->root = copyTreeInternal(this->root, tree.root);
        // delete this;//why is this delete necessary?-saleh?
    }

    template<class T,class S>
    BinarySearchTree<T,S> &BinarySearchTree<T,S>::operator=(const BinarySearchTree &tree) {
        if (this == &tree)
            return *this;
        treeDelete(this->root);
        copyTreeInternal(this, tree);
        return *this;
    }

    template<class T,class S>
    BSTNode<T,S> *BSTNode<T,S>::roll() {
        int BF = BinarySearchTree<T,S>::calcHeightDiff(this);

        // Left Left Case
        if (BF > 1 &&
            BinarySearchTree<T,S>::calcHeightDiff(this->left) >= 0) {
            return BinarySearchTree<T,S>::rightRotate(this);
        }

        // Left Right Case
        if (BF > 1 &&
            BinarySearchTree<T,S>::calcHeightDiff(this->left) < 0) {
            BinarySearchTree<T,S>::leftRotate(this->left);
            return BinarySearchTree<T,S>::rightRotate(this);
        }

        // Right Right Case
        if (BF < -1 &&
            BinarySearchTree<T,S>::calcHeightDiff(this->right) <= 0)
            return BinarySearchTree<T,S>::leftRotate(this);

        // Right Left Case
        if (BF < -1 &&
            BinarySearchTree<T,S>::calcHeightDiff(this->right) > 0) {
            BinarySearchTree<T,S>::rightRotate(this->right);
            return BinarySearchTree<T,S>::leftRotate(this);
        }
        // if( BF == 0)//added by saleh, necessary?
        // {
        //     return (this);
        // }
        return nullptr;
    }


    template<class T,class S>
    BSTNode<T,S> *BinarySearchTree<T,S>::copyTreeInternal(BSTNode<T,S>* tree,
                                                      BSTNode<T,S>* toCopy) {
        if (toCopy == nullptr) {
            tree = nullptr;
        } else {
            tree = new BSTNode<T,S>(toCopy->key,toCopy->data);
            tree->height = toCopy->height;
            copyTreeInternal(tree->left, toCopy->left);
            copyTreeInternal(tree->right, toCopy->right);
            if ( (tree->right != nullptr) && (tree->left != nullptr) )
            {
                tree->right->parent = tree;
                tree->left->parent = tree;
            }
            

        }
        return tree;
    }

    template<class T,class S>
    BinarySearchTree<T,S>::~BinarySearchTree() {

        treeDelete(this->root);
    }

    template<class T,class S>
    void BinarySearchTree<T,S>::treeDelete(BSTNode<T,S>* toDelete) {
        if (toDelete == nullptr) {
            return;
        }
        treeDelete(toDelete->right);
        treeDelete(toDelete->left);
        delete toDelete;
    }

    template<class T,class S>
    BSTNode<T,S> *insertInternal(BSTNode<T,S> *node, S key, T data) {
        if (key <= node->key) {
            if (node->left == nullptr) {
                node->left = new BSTNode<T,S>(key, data);
                node->left->parent = node;
                return node;
            } else {
                return insertInternal(node->left, key, data);
            }
        } else {
            if (node->right == nullptr) {
                node->right = new BSTNode<T,S>(key, data);
                node->right->parent = node;
                return node;
            } else {
                return insertInternal(node->right, key, data);
            }
        }


    }

    template<class T,class S>
    BSTNode<T,S> *BinarySearchTree<T,S>::insert(S key, T data) {

        if (this->root == nullptr) {
            BSTNode<T,S> *newnode= new BSTNode<T,S>(key, data);
            this->root=newnode;
            return this->root;
        }
        BSTNode<T,S> *node = insertInternal(this->root, key, data);
        BSTNode<T,S>* place=node;
        while (node->parent != nullptr) {
            node->roll();
            node->height = BinarySearchTree<T,S>::getHeight(node);
            node = node->parent;
        }
        if (node->roll() != nullptr) {
            this->root = this->root->parent;
        }
        node->height = BinarySearchTree<T,S>::getHeight(node);
        return place;
    }

    template<class T,class S>
    BSTNode<T,S> *BinarySearchTree<T,S>::find(S key) {
        BSTNode<T,S> *curr = this->root;
        while (curr != nullptr) {
            if (curr->key > key) {
                curr = curr->left;
            } else if (curr->key < key) {
                curr = curr->right;
            } else
                return curr;
        }
        return curr;
    }

    template<class T,class S>
    int BinarySearchTree<T,S>::calcHeightDiff(BSTNode<T,S> *node) {
        return getHeight(node->left) - getHeight(node->right);
    }

    template<class T,class S>
    void BinarySearchTree<T,S>::remove(S key) {
        BSTNode<T,S> *toDelete = find(key); 
        if (toDelete == nullptr) {
            return;
        }
        BSTNode<T,S> *node = removeInternal(toDelete);
        if (node == nullptr)
        {
            //which means that node is the root and the only node in the tree - saleh?
            this->root = nullptr;
        }
        
        while (node != this->root && node != nullptr) {//added nullptr check by saleh, necessary?
            node->roll();
            node->height = BinarySearchTree<T,S>::getHeight(node);
            if (node->parent == nullptr)
            {
                this->root = node;
            }
            node = node->parent;
        }
        if ( (node != nullptr) && (node->roll() != nullptr) ) {
            this->root = this->root->parent;//problem occurs here - saleh?
        }
        if (node != nullptr)
        {
            node->height = BinarySearchTree<T,S>::getHeight(node);//saleh?
        }
        
    }

    template<class T,class S>
    BSTNode<T,S> *BinarySearchTree<T,S>::removeInternal(BSTNode<T,S> *node) {
        if ((node->left == nullptr) ||
            (node->right == nullptr)) {
            BSTNode<T,S> *successor = node->left ?
                                    node->left :
                                    node->right;
            if (node->parent != nullptr) {

                if (node->parent->right == node) {
                    node->parent->right = successor;
                } else {
                    node->parent->left = successor;
                }
            }
            if (successor != nullptr) {
                successor->parent = node->parent;

            } else {

                successor = node->parent;

            }
            //delete node;
            return successor;
        } else {
            BSTNode<T,S> *successor = node->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            node->key = successor->key;
            node->data = successor->data;
            BSTNode<T,S> *temp1 = removeInternal(successor);

            return temp1;
        }
    }

    template<class T,class S>
    BSTNode<T,S>* BinarySearchTree<T,S>::createEmptyFullTree(S* keys,T*data,int min,int max)
    {
        if(min==max)
        {
            BSTNode<T,S>* newroot =new BSTNode<T,S>(keys[min],data[min]);
            newroot->height=1;
            return newroot;
        }
        else if(min>max)
        {
            return nullptr;
        }
        int mid=(min+max)/2;
        BSTNode<T,S>* newroot = new BSTNode<T,S>(keys[mid],data[mid]);
        newroot->left = createEmptyFullTree(keys,data,min,mid-1);
        newroot->right = createEmptyFullTree(keys,data,mid+1,max);
        newroot->height = getHeight(newroot);
        if(newroot->right!= nullptr)
        {
            newroot->right->parent=newroot;
        }
        if(newroot->left!= nullptr)
        {
            newroot->left->parent=newroot;
        }
        return newroot;
    }

    template<class T,class S>
   void BinarySearchTree<T,S>::clearLeaves(BSTNode<T,S>* root,int height, int* numberofleaves)
    {
        if (root == nullptr)
        {
            return;
        }
        
        if( (height == 1) && (*numberofleaves) > 0 )
        {
            if(root->parent!= nullptr)
            {
                if (root->parent->right == root) 
                {
                    root->parent->right = nullptr;
                    // root->parent->height = calcHeightDiff(root->parent);
                }
                else
                {
                    root->parent->left = nullptr;
                    // root->parent->height = calcHeightDiff(root->parent);
                }
                delete root;
                root = nullptr;//necessary? - saleh
                (*numberofleaves)--;
            }
            
        }
        if (root != nullptr)//necessary? - saleh
        {
            clearLeaves(root->right,height-1,numberofleaves);
            clearLeaves(root->left,height-1,numberofleaves);
        }
        
    }


    template<class T, class S>
    void BinarySearchTree<T, S>::merge(T *a, S *a_h , int na, T *b,S *b_h, int nb, T *c,S *c_h) 
    {   
        int ia, ib, ic;
        for(ia = ib = ic = 0; (ia < na) && (ib < nb); ic++)
        {
            if(a_h[ia] < b_h[ib]) 
            {
                c[ic] = a[ia];
                c_h[ic] = a_h[ia];
                ia++;
            }
            else 
            {
                c[ic] = b[ib];
                c_h[ic] = b_h[ib];
                ib++;
            }
        }
        for(;ia < na; ia++, ic++)
        {
            c[ic] = a[ia];
            c_h[ic] = a_h[ia];
        }
        for(;ib < nb; ib++, ic++)
        { 
            c[ic] = b[ib];
            c_h[ic] = b_h[ib];
        }
    }

    template<class T, class S>
    void BinarySearchTree<T, S>::uniteTrees(BinarySearchTree<T, S> &other)
    {
        int this_nodes = countNodes(this->root);
        int other_nodes =  countNodes(other.root);
        if(this_nodes+other_nodes==0)
        {
            return;
        }
        if(this_nodes+other_nodes==1)
        {
            if(this_nodes==1)
            {
                other.root=this->root;
            }
            return;
        }
        int *index = new int();
        S this_keys [this_nodes];
        T this_data [this_nodes];
        treeToArray(this_keys,this_data,index,this->root);
        (*index) = 0;
        S other_keys [other_nodes];
        T other_data [other_nodes];
        treeToArray(other_keys,other_data,index,other.root);
        (*index) = 0;
        S total_keys [this_nodes + other_nodes];
        T total_data[this_nodes + other_nodes];
        merge(this_data,this_keys,this_nodes,other_data,other_keys,other_nodes,total_data,total_keys);
        // treeDelete(this->root);// I believe this is donw later, inside the group destructor!
        treeDelete(other.root);
        int height=(int)ceil(log2(this_nodes + other_nodes));
        BSTNode<T,S> *newtree = createEmptyFullTree(total_keys,total_data,0,this_nodes + other_nodes-1);
       // int *numberofleaves = new int();//the number of nodes to remove
        //(*numberofleaves) = ((int)pow(2,height+1)) - (this_nodes + other_nodes + 1) ;
        //clearLeaves(newtree,height+1,numberofleaves);//problem is here, continue from here!
        //arrayToTree(newtree,total_keys,total_data,index);
        other.root = newtree;
//        delete[] this_data;
//        delete[] this_keys;
//        delete[] other_data;
//        delete[] other_keys;
//        delete[] total_keys;
//        delete[] total_data;
        delete index;
    }
}
#endif //AVL_BINARYSEARCHTREE_H