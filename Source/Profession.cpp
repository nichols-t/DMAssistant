#include "Profession.h"
#include "Sector.h"

#include <sstream>

#define FIELD_COUNT 4

DEFINE_CLOSED_CATEGORY(Profession)

Profession::Profession(std::string name, Sector& sector, double weight, double urbanizationScale)
   : INITIALIZE_CLOSED_CATEGORY(Profession)
   , mName(name)
   , mSector(sector)
   , mWeight(weight)
   , mUrbanizationScale(urbanizationScale)
{}

double Profession::GetWeight(const Sector& sector) const
{
   return mWeight * (mSector == sector) ? 1.0 : 0.0;
}

bool Profession::ParseCsvLine(std::string line, const std::vector<Sector*>& sectors)
{
   std::string name;
   Sector* sector = nullptr;
   float weight;
   float urbanizationScale = 0.0;

   std::string val;
   std::istringstream iline(line);
   int linesRead = 0;
   while(getline(iline, val, ','))
   {
      switch(linesRead)
      {
      case 0:
         name = val;
         break;

      case 1:
      {
         int sectorIndex = stoi(val) - 1;
         if(sectorIndex < sectors.size())
            sector = sectors[sectorIndex];
         else
            return false;
         break;
      }

      case 2:
         weight = stof(val);
         break;

      case 3:
      //   urbanizationScale = stof(val);
         break;

      //default:
      //   return false;
      }

      ++linesRead;
   }

   //if(linesRead < FIELD_COUNT)
   //   return false;

   sector->AddNewProfession(name, weight, urbanizationScale);
   return true;
}