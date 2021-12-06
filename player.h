//
// Created by galwe on 24/11/2021.
//

#ifndef BINARYSEARCHTREE_H_PLAYER_H
#define BINARYSEARCHTREE_H_PLAYER_H
#include "BinarySearchTree.h"
#include <memory>
#include <algorithm>

namespace Ehsan {

    class IDRank
        {
        public:
            int rank;
            int ID;
            IDRank()=default;
            explicit IDRank(int rank,int id):
                rank(rank),
                ID(id)
            {}
            bool operator==(const IDRank& other)const
            {
                return( (this->ID == other.ID) && (this->rank == other.rank) );
            }
            bool operator!=(const IDRank& other)const
            {
                return( !( (*this) == other) );
            }
            bool operator<(const IDRank& other) const
            {
                if(this->rank != other.rank)
                {
                    return ( this->rank < other.rank );
                }
                return (this->ID < other.ID);
            }
            bool operator>=(const IDRank& other) const
            {
                return (!( (*this) < other));
            }
            bool operator>(const IDRank& other) const
            {
                // if(this->rank != other.rank)
                // {
                //     return ( this->rank > other.rank );
                // }
                // return (this->ID > other.ID);
                return ( ( (*this) >= other ) &&  !( (*this) == other )  );
            }
             bool operator<=(const IDRank& other) const
            {
                return (!( (*this) > other));
            }
        };

    class Player {
    public:
    
        int playerid;
        int playerlevel;
        int groupid;

        Player(int playerid, int groupid,int playerlevel):
            playerid(playerid),
            playerlevel(playerlevel),
            groupid(groupid)
        {}
        Player(const Player& copy) = default;
        Player& operator=(const Player& copy) = default;
        ~Player() = default;
    
    };
    
    

}
#endif //BINARYSEARCHTREE_H_PLAYER_H
