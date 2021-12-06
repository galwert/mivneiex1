//
// Created by galwe on 24/11/2021.
//

#include "group.h"

namespace Ehsan
{

    Group::Group(int group_id):
        group_id(group_id),
        num_of_players(0),
        players_by_rank(),
        champion(nullptr)

    {}

    void Group::addPlayer(const std::shared_ptr<Player>& player)
    {
        this->players_by_rank.insert(IDRank(player->playerlevel,player->playerid),player);
        (this->num_of_players)++;
        if ( (this->champion) == nullptr)
        {
            this->champion = player;
            return;
        }
        if( (this->champion->playerlevel) < (player->playerlevel) ) {
            this->champion =player;
            return;
        }
        if( (this->champion->playerlevel) == (player->playerlevel) && (this->champion->playerid) < (player->playerid) )
        {
            this->champion =player;
            return;
        }
        return;
    }

    void Group::RemovePlayer(int playerrank,int playerid)
    {
        (this->num_of_players)--;
        if( (this->champion->playerid) == playerid)
        {
            BSTNode<std::shared_ptr<Player>,IDRank> *maxnode = this->players_by_rank.getMaxNode();
            if (maxnode != nullptr)
            {
                this->champion = maxnode->data;
            }
            else
            {
                this->champion = nullptr;//added by saleh, necessary?
            }
        }
        this->players_by_rank.remove(IDRank(playerrank,playerid));
        return;
    }

    void Group::UpdateChampionBeforeGroupReplacement(const std::shared_ptr<Group>& replacement)
    {
        if(this->champion== nullptr)
        {
            return;
        }
        if( (replacement->champion) == nullptr )
        {
            replacement->champion = this->champion;
            return;
        }
        if( (this->champion->playerlevel) > (replacement->champion->playerlevel) )
        {
            replacement->champion = this->champion;
            return;
        }
        if ( ((this->champion->playerlevel) == (replacement->champion->playerlevel))
                 && (((this->champion->playerid) < (replacement->champion->playerid))) )
        {
            replacement->champion = this->champion;
        }
        return;
    }

    void Group::ReplaceGroup(std::shared_ptr<Group>& replacement)
    {
        this->UpdateChampionBeforeGroupReplacement(replacement);
        (replacement->num_of_players) += (this->num_of_players);
        updatePlayersGroupID(this->players_by_rank.root,replacement->group_id);
        this->players_by_rank.uniteTrees(replacement->players_by_rank);
        // int *index = new int(); 
        // replacement->updatePlayersGroupID(replacement->players_by_rank.root,index,replacement->group_id);
        // delete index;
        return;
    }

    void Group::IncreaseLevel (int playerrank, int playerid, int LevelIncrease)
    {
        std::shared_ptr<Player> player = this->players_by_rank.find(IDRank(playerrank,playerid))->data;//this player should definitely exist
        int newlevel = LevelIncrease + (player->playerlevel);
        this->players_by_rank.remove(IDRank(player->playerlevel,playerid));
        this->players_by_rank.insert(IDRank( newlevel,playerid),player);
        // player->playerlevel = newlevel; this addition is done in SquidGame
        if( newlevel > (this->champion->playerlevel) )
        {
            this->champion = player;
        }
        if( newlevel == this->champion->playerlevel && (player->playerid) < (this->champion->playerid) )
        {
            this->champion = player;
        }
        return;
    }

    void Group::GetHighestLevel(int *PlayerID)
    {
        (*PlayerID) = this->champion->playerid;
        return;
    }
    void Group::GetAllPlayersByLevel (int **Players_array, int *numOfPlayers)
    {
        *Players_array = (int*)malloc(sizeof(int) *(*numOfPlayers));
        fillArrayWithIdsInAscendingOrder(*Players_array,numOfPlayers, this->players_by_rank.root );
        return;
    }

    void Group::fillArrayWithIdsInAscendingOrder(int *array,int* numOfPlayers, BSTNode<std::shared_ptr<Player>,IDRank> *node)
    {
        //I'm assuming there's enough room for every player.
        //It is the responsibility of the calling function to make that there's enough room for each player.
        if (node == nullptr||*numOfPlayers==0)
        {
            return;
        }
        fillArrayWithIdsInAscendingOrder(array,numOfPlayers,node->right);
        if(*numOfPlayers==0)
        {
            return;
        }
        array[*numOfPlayers] = (node->data->playerid);
        (*numOfPlayers)--;
        fillArrayWithIdsInAscendingOrder(array,numOfPlayers,node->left);
    }
}