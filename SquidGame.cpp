#include "SquidGame.h"
// #include "library.h"

#include <iostream>
#include <memory>
namespace Ehsan
{

    SquidGame::SquidGame(): 
        num_of_players(0),
        num_of_groups_with_players(0),
        players_by_id(),
        players_by_level(),
        groups(),
        groups_with_players(),
        champion()
    {}

    SquidGame *Init()
    {
        return( new SquidGame() );
    }

    StatusType SquidGame::AddGroup(int GroupID)
    {
        if( GroupID <= 0 )
        {
            return INVALID_INPUT;
        }
        BSTNode<std::shared_ptr<Group>,int> *group_node = this->groups.find(GroupID);
        // std::shared_ptr<Group> group_to_find = group_node->data;//find should be in BST
        if (group_node != nullptr)
        {
            //a group with this identifier already exists
            return FAILURE;
        }

        try{
            std::shared_ptr<Group> group_to_add = std::make_shared<Group>(GroupID);
            this->groups.insert(GroupID,group_to_add);//insert should be in BST
        }
        catch(const std::bad_alloc& e){
            return ALLOCATION_ERROR;//allocation failed
        }

        return SUCCESS;
    }

    StatusType SquidGame::AddPlayer(int PlayerID, int GroupID, int Level)
    {
        if( PlayerID <= 0 || GroupID <= 0 || Level < 0)
        {
            return INVALID_INPUT;
        }

        BSTNode<std::shared_ptr<Player>,int> *player_to_find_node = this->players_by_id.find(PlayerID);//find should be in BST
        BSTNode<std::shared_ptr<Group>,int> *group_to_find_node = this->groups.find(GroupID);//find should be in BST
        if (player_to_find_node != nullptr || group_to_find_node == nullptr)
        {
            // a player with that identifier already exists
            //or a group with that identifier doesn't exist in the Game
            return FAILURE;
        }

        std::shared_ptr<Group> group_to_find = group_to_find_node->data;
        try{
            std::shared_ptr<Player> player_to_add = std::make_shared<Player>(PlayerID,GroupID,Level);
            IDRank playerinfo = IDRank(Level,PlayerID);

            this->players_by_id.insert(PlayerID,player_to_add);
            this->players_by_level.insert(playerinfo,player_to_add);
            (this->num_of_players)++;
            if ( group_to_find->num_of_players == 0)
            {       
                //in case this is the first player added to the group
                this->groups_with_players.insert(GroupID,group_to_find);
                (this->num_of_groups_with_players)++;
            }
            group_to_find->addPlayer(player_to_add);
            UpdateChampionAfterAddition(player_to_add);
        }
        catch(const std::bad_alloc&){
            return ALLOCATION_ERROR;
        }

        return SUCCESS;

    }

    StatusType SquidGame::RemovePlayer(int PlayerID)
    {
        if( PlayerID <= 0)
        {
            return INVALID_INPUT;
        }
        BSTNode<std::shared_ptr<Player>,int> *player_to_remove_node = this->players_by_id.find(PlayerID);//find should be in BST

        if (player_to_remove_node == nullptr)
        {
            return FAILURE;
        }
        std::shared_ptr<Player> player_to_remove = player_to_remove_node->data;
        std::shared_ptr<Group> group_to_find = this->groups_with_players.find(player_to_remove->groupid)->data;
        group_to_find->RemovePlayer(player_to_remove->playerlevel,player_to_remove->playerid);
        if ( group_to_find->num_of_players <= 0)
        {       
            //in case this is the last player in the group
            this->groups_with_players.remove(player_to_remove->groupid);
            (this->num_of_groups_with_players)--;
        }
        
        //and then use player_to_find and do the appropriate rotation for the specific case
        IDRank playerinfo = IDRank(player_to_remove->playerlevel,PlayerID);
        //need to check if the player is group champion / champion and remove accordingly!
        this->players_by_id.remove(PlayerID);
        this->players_by_level.remove(playerinfo);//problem occured here!
        (this->num_of_players)--;
        BSTNode<std::shared_ptr<Player>,IDRank> *maxnode = this->players_by_level.getMaxNode();
        if (maxnode != nullptr)
        {
            this->champion = maxnode->data;
        }
        else
        {
            this->champion = nullptr;//added by saleh, necessary?
        }
        return  SUCCESS;
    }

    StatusType SquidGame::ReplaceGroup(int GroupID, int ReplacementID)
    {
        if (GroupID<= 0 || ReplacementID <= 0 || GroupID == ReplacementID)
        {
            return INVALID_INPUT;
        }
        int count=this->groups_with_players.countNodes(this->groups_with_players.root);
        BSTNode<std::shared_ptr<Group>,int> *group_to_remove_node = this->groups.find(GroupID);//->ind should be in BST
        if(count==6)
        {
            std::cout<<"";
        }
        BSTNode<std::shared_ptr<Group>,int> *replacement_group_node = this->groups.find(ReplacementID);//find should be in BST
        if (replacement_group_node == nullptr || group_to_remove_node == nullptr)
        {
            return FAILURE;
        }
        std::shared_ptr<Group> group_to_remove = group_to_remove_node->data;
        std::shared_ptr<Group> replacement_group = replacement_group_node->data;

        if ( (group_to_remove->num_of_players) > 0)
        {
            // replacement_group->num_of_players += (group_to_remove->num_of_players);
            this->groups_with_players.remove(group_to_remove->group_id);
            (this->num_of_groups_with_players)--;
        }
        try
        {

            if(replacement_group->num_of_players==0&&group_to_remove->num_of_players>0)
            {
                this->groups_with_players.insert(ReplacementID,replacement_group);
                (this->num_of_groups_with_players)++;
            }
            count=this->groups_with_players.countNodes(this->groups_with_players.root);
            group_to_remove->ReplaceGroup(replacement_group);
            count=this->groups_with_players.countNodes(this->groups_with_players.root);
            this->groups.remove(group_to_remove->group_id);
            count=this->groups_with_players.countNodes(this->groups_with_players.root);
        }catch(const std::bad_alloc& e){
            return ALLOCATION_ERROR;
        }
        
        return SUCCESS;
    }

    StatusType SquidGame::IncreaseLevel(int PlayerID, int LevelIncrease)
    {
        if (PlayerID <= 0 || LevelIncrease <= 0)
        {
            return INVALID_INPUT;
        }
        BSTNode<std::shared_ptr<Player>,int> *player_to_find_node = this->players_by_id.find(PlayerID);//find should be in BST
        if (player_to_find_node == nullptr)
        {
            //a player with this identifier doesnt exist
            return FAILURE;
        }

        std::shared_ptr<Player> player_to_find = player_to_find_node->data;
        if(PlayerID==1525827268)
        {
            std::cout<<"dfgb";
        }
        std::shared_ptr<Group> group_to_find = this->groups_with_players.find(player_to_find->groupid)->data;
        this->players_by_level.remove(IDRank(player_to_find->playerlevel,PlayerID));

        group_to_find->IncreaseLevel(player_to_find->playerlevel,PlayerID,LevelIncrease);
        //incresing the actual level
        (player_to_find->playerlevel) += LevelIncrease;
        this->players_by_level.insert(IDRank(player_to_find->playerlevel,PlayerID),player_to_find);
        UpdateChampionAfterLevelIncrease(player_to_find);

        return SUCCESS;
    }

    StatusType SquidGame::GetHighestLevel(int GroupID, int *PlayerID)//DONE!
    {
        if ( PlayerID == nullptr || GroupID == 0)
        {
            return INVALID_INPUT;
        }
        if (GroupID < 0)
        {
            if (this->champion == nullptr)
            {
                (*PlayerID) = -1;
            }
            else
            {
                (*PlayerID) = this->champion->playerid;
            }        
            return SUCCESS;
        }
        BSTNode<std::shared_ptr<Group>,int> *group_to_find_node = this->groups.find(GroupID);//find should be in BST
        if (group_to_find_node == nullptr)
        {
            //a group with this identifier doesn't exist
            return FAILURE;
        }
        std::shared_ptr<Group> group_to_find = group_to_find_node->data;
        if (group_to_find->champion == nullptr)
        {
            (*PlayerID) = -1;
        }
        else
        {
            (*PlayerID) = group_to_find->champion->playerid;
        }
        return SUCCESS;
    }

    StatusType SquidGame::GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers)
    {
        if( GroupID == 0 || Players == nullptr || numOfPlayers == nullptr )
        {
            return INVALID_INPUT;
        }
        BSTNode<std::shared_ptr<Group>,int> *group_to_find_node = this->groups.find(GroupID);//find should be in BST
        if (group_to_find_node == nullptr && (GroupID > 0))
        {
            //a group with this identifier doesn't exist
            return FAILURE;
        }

        try{
            int* index = new int();
            if (GroupID < 0 )
            {
                if (this->num_of_players <= 0)
                {
                    *(numOfPlayers) = 0;
                    *Players = nullptr;
                }
                else
                {
                *(numOfPlayers) = this->num_of_players;
                int* myarray=((int*)malloc(sizeof(int)* (this->num_of_players)));
                    if(myarray== nullptr)
                    {
                        throw std::bad_alloc();
                    }
                fillArrayWithIdsInDescendingOrder(myarray,index,this->num_of_players,this->players_by_level.root);
                    *Players=myarray;
                }
                delete index;
                return SUCCESS;
            }
            else
            {
                std::shared_ptr<Group> group_to_find = group_to_find_node->data;
                if (group_to_find->num_of_players <= 0)
                {
                    *(numOfPlayers) = 0;
                    *Players = nullptr;
                }
                else
                {
                    *(numOfPlayers) = group_to_find->num_of_players;
                    int* myarray=(int*)malloc(sizeof(int)* (*numOfPlayers));
                    if(myarray== nullptr)
                    {
                        throw std::bad_alloc();
                    }
                    fillArrayWithIdsInDescendingOrder(myarray,index,group_to_find->num_of_players,group_to_find->players_by_rank.root);
                    *Players=myarray;
                }
            }
            delete index;
        }catch(const std::bad_alloc& e){
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
    }

    StatusType SquidGame::GetGroupsHighestLevel(int numOfGroups, int **Players)
    {
        if ( (Players == nullptr) || (numOfGroups < 1) )
        {
            return INVALID_INPUT;
        }
        
        if ( numOfGroups > (this->num_of_groups_with_players) )
        {
            return FAILURE;
        }
        try{
            int *index = new int();
            int* myarray=(int*)malloc( sizeof(int) * (numOfGroups));
            if(myarray== nullptr)
            {
                delete index;//an error occured!
                throw std::bad_alloc();
            }
            fillArrayWithChampionIdsInAscendingOrder(myarray,index,numOfGroups,this->groups_with_players.root);
            *Players=myarray;
            delete index;
        }catch(const std::bad_alloc& e){
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
    }

    void SquidGame::DeleteSquidGame()
    {

        /*this->groups_with_players.treeDelete(this->groups_with_players.root);
        this->groups.treeDelete((this->groups.root));
        this->players_by_id.treeDelete(this->players_by_id.root);
        this->players_by_level.treeDelete(this->players_by_level.root);*/
        delete this;
    }

    void SquidGame::UpdateChampionAfterAddition( std::shared_ptr<Player>& player)
    {
        if ( (this->champion) == nullptr)
        {
            this->champion = player;
            return;
        }
           
        if ( (player->playerlevel) > (this->champion->playerlevel))
        {
            this->champion = player;
            return;
        }

        if ( ( (player->playerlevel) == (this->champion->playerlevel) )
                 && ( (player->playerid) < (this->champion->playerid) ) )
        {
            this->champion = player;
            return;
        }
        return;
    }

    void SquidGame::UpdateChampionAfterLevelIncrease(std::shared_ptr<Player> player)
    {
        if ( (player->playerlevel) == (this->champion->playerlevel) )
        {
            if ( (player->playerid) < (this->champion->playerid) )
            {
                this->champion = player;
            }   
        }
        if ( (player->playerlevel) > (this->champion->playerlevel) )
        {
            this->champion = player;
        }
        return;
    }

    void SquidGame::fillArrayWithIdsInDescendingOrder(int *array,int* index,int max, BSTNode<std::shared_ptr<Player>,IDRank> *node)
    {
        //I'm assuming there's enough room for every player.
        //It is the responsibility of the calling function to make that there's enough room for each player.
        if (node == nullptr||(*index)==max)
        {
            return;
        }
        fillArrayWithIdsInDescendingOrder(array,index,max,node->right);
        if ((*index)==max)
        {
            return;
        }
        array[*index] = (node->data->playerid);
        (*index)++;
        fillArrayWithIdsInDescendingOrder(array,index,max,node->left);
        return;
    }

    void SquidGame::fillArrayWithChampionIdsInAscendingOrder(int *array,int *index,int max, BSTNode<std::shared_ptr<Group>,int> *node)
    {
        //I'm assuming there's enough room for every player.
        //It is the responsibility of the calling function to make that there's enough room for each player.
        if (node == nullptr||(*index)==max)
        {
            return;
        }
        fillArrayWithChampionIdsInAscendingOrder(array,index,max,node->left);
        if((*index)==max)
        {
            return;
        }
        array[*index] = (node->data->champion->playerid);
        (*index)++;
        fillArrayWithChampionIdsInAscendingOrder(array,index,max,node->right);
        return;
    }

    SquidGame *SquidGame::Init() {
        return nullptr;
    }

}
