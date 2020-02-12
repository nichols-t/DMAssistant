#include "TownGenerator.h"
#include "Town.h"

#include <iostream>

#define SECTOR_FILEPATH "Sectors.dma"
#define PROFESSION_FILEPATH "Professions.dma"
#define RACE_FILEPATH "Races.dma"

using namespace std;

int main()
{
   TownGenerator* generator = TownGenerator::Create(SECTOR_FILEPATH, PROFESSION_FILEPATH, RACE_FILEPATH);
   if(!generator)
   {
      cout << "Unable to create TownGenerator!" << endl;
      return -1;
   }
   Town* town = generator->GenerateTown(10000);
   town->Print();

   return 0;
}