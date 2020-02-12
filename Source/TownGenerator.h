#ifndef TOWN_GENERATOR_H
#define TOWN_GENERATOR_H

#include <vector>
#include <string.h>

class Town;
class Sector;
class Profession;

class TownGenerator
{
public:
   Town* GenerateTown(int size); 

   static TownGenerator* Create(std::string sectorFilepath, std::string professionFilepath, std::string raceFilepath);
};

#endif