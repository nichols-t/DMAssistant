#ifndef TOWN_H
#define TOWN_H

#include <vector>

class NpcMold;

class Town
{
public:
   Town(std::vector<NpcMold>& npcMolds);

   void Print() const;

private:
   std::vector<NpcMold> mNpcMolds;
};

#endif