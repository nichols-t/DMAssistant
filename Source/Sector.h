#ifndef SECTOR_H
#define SECTOR_H

#include "Category.h"
#include "Profession.h"

#include <string>
#include <vector>

class Profession;
class Race;

class Sector
{
   DECLARE_CLOSED_CATEGORY(Sector)

public:
   Sector(std::string name, float weight, float urbanizationScale);

         double                     GetWeight();
         std::string                GetName()         { return mName; }
   const std::vector<Profession*>&  GetProfessions()  { return mProfessions; }

   void AddNewProfession(std::string name, double weight, double urbanizationScale) { mProfessions.push_back(new Profession(name, *this, weight, urbanizationScale)); }

   static Sector* ParseCsvLine(std::string line);

private:
   std::string mName;
   float mWeight;
   float mUrbanizationScale;

   std::vector<Profession*> mProfessions;
};

#endif