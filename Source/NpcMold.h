#ifndef NPC_MOLD_H
#define NPC_MOLD_H

class Race;
class Profession;

class NpcMold
{
public:
   NpcMold(Race& race, Profession& profession);
   
   const Race& GetRace() const { return mRace; }
   const Profession& GetProfession() const { return mProfession; }

private:
   Race& mRace;
   Profession& mProfession;
};

#endif