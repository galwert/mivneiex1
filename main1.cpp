#include <iostream>
#include "BinarySearchTree.h"
using namespace Ehsan;
#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <memory>
void printTree(BSTNode<int,int> * root) {
    std::cout.flush();
    if(root== nullptr)
        return;

    printTree(root->left);
    std::cout<<root->key;
    std::cout<<" BF: "<<BinarySearchTree<std::shared_ptr<Player>,int>::calcHeightDiff(root)<<" Height: "<<root->height-1<<std::endl;
    printTree(root->right);
}
int main1()
{
//    BinarySearchTree<int>* tree=new BinarySearchTree<int>();
//
//    /* Constructing tree given in
//    the above figure */
//    tree->insert(8);
//
//    tree->insert( 5);
//    tree->insert(10);
//    tree->insert(9);
//    tree->insert(0);
//    tree->insert( 6);
//    tree->insert( 11);
//    tree->insert( 1);
//    printBT(tree->root);
//    tree->insert(1);
//    printBT(tree->root);
//    tree->insert( 2);
//    printBT(tree->root);
//    /* The constructed AVL Tree would be
//            9
//        / \
//        1 10
//        / \ \
//    0 5 11
//    / / \
//    -1 2 6
//    */
//
//
//    tree->remove(tree->root, 10);
//
   printBT(tree->root);
}
int main1(){
    BinarySearchTree<int,int> tree;

    //Specific Cases

    /*correct output for the four next cases
    1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0 */

    //basic LL root change
    tree.insert(3,3);
    tree.insert(2,2);
    tree.insert(1,1);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;
    //basic LR root change
    tree.insert(3,3);
    tree.insert(1,1);
    tree.insert(2,2);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //basic RR root change
    tree.insert(1,1);
    tree.insert(2,2);
    tree.insert(3,3);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //basic RL root change
    tree.insert(1,1);
    tree.insert(3,3);
    tree.insert(2,2);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //basic LR not root change
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    4 BF: 1 Height: 2
    5 BF: 0 Height: 0
    6 BF: 1 Height: 3
    7 BF: 0 Height: 0
    8 BF: 1 Height: 1 */
    tree.insert(6,6);
    tree.insert(4,4);
    tree.insert(8,8);
    tree.insert(3,3);
    tree.insert(5,5);
    tree.insert(7,7);
    tree.insert(1,1);
    tree.insert(2,2);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //basic LL not root change
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    4 BF: 1 Height: 2
    5 BF: 0 Height: 0
    6 BF: 1 Height: 3
    7 BF: 0 Height: 0
    8 BF: 1 Height: 1 */
    tree.insert(6,6);
    tree.insert(4,4);
    tree.insert(8,8);
    tree.insert(3,3);
    tree.insert(5,5);
    tree.insert(7,7);
    tree.insert(2,2);
    tree.insert(1,1);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //basic RR not root change
    /*correct output
     * 1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    5 BF: 1 Height: 2
    7 BF: 0 Height: 0*/
    tree.insert(5,5);
    tree.insert(7,7);
    tree.insert(1,1);
    tree.insert(2,2);
    tree.insert(3,3);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //basic RL not root change
    /*correct output
     * 1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    5 BF: 1 Height: 2
    7 BF: 0 Height: 0*/
    tree.insert(5,5);
    tree.insert(7,7);
    tree.insert(1,1);
    tree.insert(3,3);
    tree.insert(2,2);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //root deletion no roll successor is a neighbour
    /*correct output
    2 BF: 0 Height: 0
    3 BF: 1 Height: 1
    5 BF: 1 Height: 2
    6 BF: 0 Height: 0*/
    tree.insert(4,4);
    tree.insert(5,5);
    tree.insert(3,3);
    tree.insert(2,2);
    tree.insert(6,6);
    tree.remove(4);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //root deletion no roll successor is not a neighbour
    /*correct output
    2 BF: 0 Height: 0
    3 BF: 1 Height: 1
    5 BF: 0 Height: 2
    6 BF: 0 Height: 0
    7 BF: 0 Height: 1
    8 BF: 0 Height: 0 */
    tree.insert(4,4);
    tree.insert(3,3);
    tree.insert(7,7);
    tree.insert(2,2);
    tree.insert(5,5);
    tree.insert(8,8);
    tree.insert(6,6);
    tree.remove(4);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //node deletion no roll successor is a neighbour case7
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 1 Height: 1
    4 BF: 1 Height: 2
    5 BF: 0 Height: 0
    7 BF: 1 Height: 3
    8 BF: -1 Height: 1
    9 BF: 0 Height: 0*/
    tree.insert(7,7);
    tree.insert(3,3);
    tree.insert(8,8);
    tree.insert(2,2);
    tree.insert(4,4);
    tree.insert(9,9);
    tree.insert(5,5);
    tree.insert(1,1);
    tree.remove(3);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //node deletion no roll successor is not a neighbour case8
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 1 Height: 1
    5 BF: 0 Height: 2
    6 BF: 0 Height: 0
    7 BF: 0 Height: 1
    8 BF: 0 Height: 0
    9 BF: 0 Height: 3
    10 BF: 0 Height: 0
    12 BF: -1 Height: 2
    13 BF: -1 Height: 1
    14 BF: 0 Height: 0*/
    tree.insert(9,9);
    tree.insert(3,3);
    tree.insert(12,12);
    tree.insert(2,2);
    tree.insert(7,7);
    tree.insert(10,10);
    tree.insert(13,13);
    tree.insert(1,1);
    tree.insert(5,5);
    tree.insert(8,8);
    tree.insert(14,14);
    tree.insert(6,6);
    tree.remove(3);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //node deletion causing LR case9
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    4 BF: 0 Height: 2
    7 BF: -1 Height: 1
    8 BF: 0 Height: 0*/
    tree.insert(7,7);
    tree.insert(2,2);
    tree.insert(8,8);
    tree.insert(1,1);
    tree.insert(4,4);
    tree.insert(9,9);
    tree.insert(3,3);
    tree.remove(9);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //node deletion causing LL case10
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 1 Height: 1
    3 BF: 0 Height: 2
    4 BF: 0 Height: 0
    7 BF: 0 Height: 1
    8 BF: 0 Height: 0*/
    tree.insert(7,7);
    tree.insert(3,3);
    tree.insert(8,8);
    tree.insert(2,2);
    tree.insert(4,4);
    tree.insert(9,9);
    tree.insert(1,1);
    tree.remove(9);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //node deletion causing RR case11
    /*correct output
    2 BF: 0 Height: 0
    3 BF: 0 Height: 1
    7 BF: 0 Height: 0
    8 BF: 0 Height: 2
    9 BF: -1 Height: 1
    10 BF: 0 Height: 0*/
    tree.insert(3,3);
    tree.insert(2,2);
    tree.insert(8,8);
    tree.insert(7,7);
    tree.insert(1,1);
    tree.insert(9,9);
    tree.insert(10,10);
    tree.remove(1);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //node deletion causing RL case12
    /*correct output
    * 2 BF: 0 Height: 0
    3 BF: 1 Height: 1
    7 BF: 0 Height: 2
    10 BF: 0 Height: 0
    13 BF: 0 Height: 1
    14 BF: 0 Height: 0*/
    tree.insert(3,3);
    tree.insert(2,2);
    tree.insert(13,13);
    tree.insert(7,7);
    tree.insert(1,1);
    tree.insert(14,14);
    tree.insert(10,10);
    tree.remove(1);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //double rotations RL and RR case 13
    /*correct output
    3 BF: 0 Height: 0
    5 BF: 0 Height: 1
    7 BF: 0 Height: 0
    9 BF: 0 Height: 2
    11 BF: 0 Height: 0
    13 BF: 1 Height: 1
    15 BF: 0 Height: 3
    17 BF: 0 Height: 0
    19 BF: -1 Height: 2
    21 BF: -1 Height: 1
    23 BF: 0 Height: 0*/
    tree.insert(9,9);
    tree.insert(3,3);
    tree.insert(15,15);
    tree.insert(1,1);
    tree.insert(7,7);
    tree.insert(13,13);
    tree.insert(19,19);
    tree.insert(5,5);
    tree.insert(11,11);
    tree.insert(17,17);
    tree.insert(21,21);
    tree.insert(23,23);
    tree.remove(1);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //double rotations RR and RR case 14
    /*correct output
    3 BF: 0 Height: 0
    7 BF: 0 Height: 1
    8 BF: 0 Height: 0
    9 BF: 0 Height: 2
    11 BF: 0 Height: 0
    13 BF: 1 Height: 1
    15 BF: 0 Height: 3
    17 BF: 0 Height: 0
    19 BF: -1 Height: 2
    21 BF: -1 Height: 1
    23 BF: 0 Height: 0*/
    tree.insert(9,9);
    tree.insert(3,3);
    tree.insert(15,15);
    tree.insert(1,1);
    tree.insert(7,7);
    tree.insert(13,13);
    tree.insert(19,19);
    tree.insert(8,8);
    tree.insert(11,11);
    tree.insert(17,17);
    tree.insert(21,21);
    tree.insert(23,23);
    tree.remove(1);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //double rotations RL and LL case 15
    /*correct output
    6 BF: 0 Height: 0
    7 BF: 1 Height: 1
    8 BF: 1 Height: 2
    9 BF: 0 Height: 0
    10 BF: 0 Height: 3
    11 BF: -1 Height: 1
    12 BF: 0 Height: 0
    15 BF: 0 Height: 2
    17 BF: 0 Height: 0
    18 BF: 0 Height: 1
    20 BF: 0 Height: 0
     */
    tree.insert(15,15);
    tree.insert(10,10);
    tree.insert(20,20);
    tree.insert(8,8);
    tree.insert(11,11);
    tree.insert(17,17);
    tree.insert(21,21);
    tree.insert(7,7);
    tree.insert(9,9);
    tree.insert(12,12);
    tree.insert(18,18);
    tree.insert(6,6);
    tree.remove(21);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //double rotations LR and LL case 16
    /*correct output
    6 BF: 0 Height: 0
    7 BF: 1 Height: 1
    8 BF: 1 Height: 2
    9 BF: 0 Height: 0
    10 BF: 0 Height: 3
    11 BF: -1 Height: 1
    12 BF: 0 Height: 0
    15 BF: 0 Height: 2
    20 BF: 0 Height: 0
    21 BF: 0 Height: 1
    22 BF: 0 Height: 0 */
    tree.insert(15,15);
    tree.insert(10,10);
    tree.insert(20,20);
    tree.insert(8,8);
    tree.insert(11,11);
    tree.insert(17,17);
    tree.insert(22,22);
    tree.insert(7,7);
    tree.insert(9,9);
    tree.insert(12,12);
    tree.insert(21,21);
    tree.insert(6,6);
    tree.remove(17);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //delete node cause LR
    /*correct output
     * 2 BF: 0 Height: 0
    3 BF: -1 Height: 2
    4 BF: 0 Height: 0
    6 BF: 1 Height: 1*/

    tree.insert(5,5);
    tree.insert(3,3);
    tree.insert(6,6);
    tree.insert(2,2);
    tree.insert(4,4);
    tree.remove(5);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    //delete node cause LR
    /*correct output
     * 2 BF: 0 Height: 0
    3 BF: 0 Height: 1
    6 BF: 0 Height: 0*/
    tree.insert(5,5);
    tree.insert(3,3);
    tree.insert(6,6);
    tree.insert(2,2);
    tree.remove(5);
    printTree(tree.root);
    std::cout<<std::endl;
    tree.treeDelete(tree.root);
    tree.root= nullptr;

    std::vector<int> vector;
    for (int i=1; i<=100; i++) vector.push_back(i);

    //Randomly insert and removes nodes
//    for (int k = 0; k < 20; ++k) {
//        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
//        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); it++){
//            tree.insert(*it,*it);
//
//        }
//        printTree(tree.root);
//        std::cout<<std::endl;
//        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
//        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
//
//            tree.remove(*it);
//
//
//        }
//                  printTree(tree.root);
//          std::cout<<std::endl;
//        tree.treeDelete(tree.root);
//        tree.root= nullptr;
//        std::cout<<std::endl;
//        std::cout << '\n';
//    }

    return 0;
}