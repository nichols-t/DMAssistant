#include "Sector.h"

#include "Race.h"

#include <sstream>

#define FIELD_COUNT 3

DEFINE_CLOSED_CATEGORY(Sector)

Sector::Sector(std::string name, float weight, float urbanizationScale)
   : INITIALIZE_CLOSED_CATEGORY(Sector)
   , mName(name)
   , mWeight(weight)
   , mUrbanizationScale(urbanizationScale)
{}

double Sector::GetWeight()
{
   return mWeight;
}

Sector* Sector::ParseCsvLine(std::string line)
{
   std::string name;
   float weight;
   float urbanizationWeight;

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
         weight = stof(val);
         break;

      case 2:
         urbanizationWeight = stof(val);
         break;

      default:
         return nullptr;
      }

      ++linesRead;
   }
   
   if(linesRead < FIELD_COUNT)
      return nullptr;

   return new Sector(name, weight, urbanizationWeight);
}