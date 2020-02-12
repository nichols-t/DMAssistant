#include "Race.h"

#include "Sector.h"

#include <sstream>

#define CENTERING_COEF 0.3

DEFINE_CLOSED_CATEGORY(Race)

Race::Race(std::string name, std::vector<double>& sectorScales)
   : INITIALIZE_CLOSED_CATEGORY(Race)
   , mName(name)
   , mSectorScales(sectorScales)
{}

double Race::GetWeight() const
{
   return 1.0;
}

Race* Race::ParseCsvLine(std::string line)
{
   std::string name;
   std::vector<double> sectorScales;

   std::string val;
   std::istringstream iline(line);
   int linesRead = 0;
   while(getline(iline, val, ','))
   {
      if(linesRead == 0)
         name = val;
      else if(linesRead <= Sector::GetCategory().Size())
         sectorScales.push_back(_FactorizeSectorScale(stod(val)));

      ++linesRead;
   }

   if(linesRead < Sector::GetCategory().Size() + 1)
      return nullptr;

   return new Race(name, sectorScales);
}

double Race::_FactorizeSectorScale(double scale)
{
   return scale * CENTERING_COEF + 1;
}