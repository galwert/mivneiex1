//
// Created by galwe on 24/11/2021.
//

#ifndef BINARYSEARCHTREE_H_SQUIDGAME_H
#define BINARYSEARCHTREE_H_SQUIDGAME_H

#include "group.h"
#include "library.h"

namespace Ehsan
{
    class SquidGame
    {
    public:
        int num_of_players;
        int num_of_groups_with_players;
        BinarySearchTree<std::shared_ptr<Player>,int> players_by_id;
        BinarySearchTree<std::shared_ptr<Player>,IDRank> players_by_level;
        BinarySearchTree<std::shared_ptr<Group>,int> groups;
        BinarySearchTree<std::shared_ptr<Group>,int> groups_with_players;
        std::shared_ptr<Player> champion;

        


        SquidGame();
        ~SquidGame() = default;
        SquidGame(const SquidGame&) = default;
        SquidGame& operator=(const SquidGame&) = default;

        void UpdateChampionAfterAddition(std::shared_ptr<Player>& player);

        void UpdateChampionAfterLevelIncrease(std::shared_ptr<Player> player);

        void fillArrayWithIdsInDescendingOrder(int *array,int* index,int max, BSTNode<std::shared_ptr<Player>,IDRank> *node);

        void fillArrayWithChampionIdsInAscendingOrder(int *array,int* index,int max, BSTNode<std::shared_ptr<Group>,int> *node);

        SquidGame *Init();

        StatusType AddGroup(int GroupID);

        StatusType AddPlayer(int PlayerID, int GroupID, int Level);

        StatusType RemovePlayer(int PlayerID);

        StatusType ReplaceGroup(int GroupID, int ReplacementID);

        StatusType IncreaseLevel(int PlayerID, int LevelIncrease);

        StatusType GetHighestLevel(int GroupID, int *PlayerID);

        StatusType GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers);

        StatusType GetGroupsHighestLevel(int numOfGroups, int **Players);

        void DeleteSquidGame();
    };
}
#endif //BINARYSEARCHTREE_H_SQUIDGAME_H
