#ifndef PROFESSION_H
#define PROFESSION_H

#include "Category.h"

#include <string>
#include <vector>

class Sector;

class Profession
{
   DECLARE_CLOSED_CATEGORY(Profession)

public:
   Profession(std::string name, Sector& sector, double weight, double urbanizationScale);

   std::string GetName() const { return mName; }
   const Sector& GetSector() const { return mSector; }
   double GetWeight(const Sector& sector) const;

   static bool ParseCsvLine(std::string line, const std::vector<Sector*>& sectors);

private:
   std::string mName;
   Sector& mSector;
   double mWeight;
   double mUrbanizationScale;
};

#endif