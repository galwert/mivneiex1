//
// Created by galwe on 24/11/2021.
//

#ifndef BINARYSEARCHTREE_H_GROUP_H
#define BINARYSEARCHTREE_H_GROUP_H
#include "player.h"
#include "BinarySearchTree.h"
#include <memory>
#include <iostream>


namespace Ehsan {
    class Group {

    public:
        int group_id;
        int num_of_players;
        BinarySearchTree<std::shared_ptr<Player>,IDRank> players_by_rank;
        std::shared_ptr<Player> champion;
        

        explicit Group(int group_id);
        ~Group()=default;

        void addPlayer(const std::shared_ptr<Player>& player);
        void RemovePlayer(int playerrank,int playerid);
        void ReplaceGroup(std::shared_ptr<Group>& replacement);
        void IncreaseLevel (int playerrank, int playerid, int LevelIncrease);
        void GetHighestLevel(int *PlayerID);
        void GetAllPlayersByLevel (int **Players_array, int *numOfPlayers);
        void fillArrayWithIdsInAscendingOrder(int *array,int* numOfPlayers, BSTNode<std::shared_ptr<Player>,IDRank> *node);

        static void updatePlayersGroupID(BSTNode<std::shared_ptr<Player>,IDRank> *node,int newgroupid)
        {
            if (node == nullptr)
            {
                return;
            }
            updatePlayersGroupID(node->left,newgroupid);
            node->data->groupid = newgroupid;
            updatePlayersGroupID(node->right,newgroupid);
        }
        void UpdateChampionBeforeGroupReplacement(const std::shared_ptr<Group>& replacement);
    };
}
#endif //BINARYSEARCHTREE_H_GROUP_H
