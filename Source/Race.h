#ifndef RACE_H
#define RACE_H

#include "Category.h"

#include <vector>

class Race
{
   DECLARE_CLOSED_CATEGORY(Race)

public:
   Race(std::string name, std::vector<double>& sectorScales);

   std::string GetName() const { return mName; }
   double GetWeight() const;
   double GetSectorScale(int sectorIndex) const { return mSectorScales[sectorIndex]; }

   static Race* ParseCsvLine(std::string line);

private:
   static double _FactorizeSectorScale(double scale);

   std::string mName;
   std::vector<double> mSectorScales;
};

#endif