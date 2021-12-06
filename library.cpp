#include "SquidGame.h"
#include "library.h"


    void *Init()
    {
        return(static_cast<void*> (new Ehsan::SquidGame()) );
    }   

    StatusType AddGroup(void *DS, int GroupID)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return(static_cast<Ehsan::SquidGame*>(DS)->AddGroup(GroupID));
    }

    StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int Level)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return(static_cast<Ehsan::SquidGame*>(DS)->AddPlayer( PlayerID, GroupID, Level));
    }

    StatusType RemovePlayer(void *DS, int PlayerID)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return(static_cast<Ehsan::SquidGame*>(DS)->RemovePlayer(PlayerID));
    }

    StatusType ReplaceGroup(void *DS, int GroupID, int ReplacementID)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return(static_cast<Ehsan::SquidGame*>(DS)->ReplaceGroup(GroupID, ReplacementID));
    }

    StatusType IncreaseLevel(void *DS, int PlayerID, int LevelIncrease)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return(static_cast<Ehsan::SquidGame*>(DS)->IncreaseLevel(PlayerID, LevelIncrease));
    }

    StatusType GetHighestLevel(void *DS, int GroupID, int *PlayerID)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return(static_cast<Ehsan::SquidGame*>(DS)->GetHighestLevel( GroupID, PlayerID));
    }

    StatusType GetAllPlayersByLevel(void *DS, int GroupID, int **Players, int *numOfPlayers)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return(static_cast<Ehsan::SquidGame*>(DS)->GetAllPlayersByLevel(GroupID,Players,numOfPlayers));
    }

    StatusType GetGroupsHighestLevel(void *DS, int numOfGroups, int **Players)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return(static_cast<Ehsan::SquidGame*>(DS)->GetGroupsHighestLevel(numOfGroups,Players));
    }

    void Quit(void** DS)
    {
        static_cast<Ehsan::SquidGame*>(*DS)->DeleteSquidGame();
        *DS = NULL;
    }
