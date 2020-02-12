#include "TownGenerator.h"
#include "Town.h"
#include "Category.h"
#include "Race.h"
#include "Sector.h"
#include "Profession.h"
#include "NpcMold.h"

#include <random>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <iostream>

#define ENTROPY_PULL_FACTOR 1.0

std::random_device randomDevice;
std::default_random_engine rng(randomDevice());
std::uniform_real_distribution<double> rngDistribution(0.0, 1.0);

class ConstantSizeSelector
{
public:
   ConstantSizeSelector(std::vector<double>& weights)
      : mWeights(weights)
      , mSize((int)weights.size())
   {
      for(int i = 0; i < mSize; ++i)
         mEntropy.push_back(100.0);
   }

   int Select()
   {
      double selector = rngDistribution(rng);
      std::vector<double> workingWeights;
      double sum = 0.0;
      for(int i = 0; i < mSize; ++i)
      {
         double current = mWeights[i] * mEntropy[i];
         workingWeights.push_back(current);
         sum += current;
      }

      double accumulator = 0.0;
      for(int i = 0; i < mSize; ++i)
      {
         accumulator += workingWeights[i] / sum;
         if(accumulator > selector)
         {
            mEntropy[i] *= ENTROPY_PULL_FACTOR;
            return i;
         }
      }
      return mSize - 1;
   }
   
private:
   const int mSize;
   std::vector<double>& mWeights;
   std::vector<double> mEntropy;
};

#define DECLARE_CATEGORY_SELECTION_VARIABLES(classname, prefix)         \
   Category<classname>& prefix ## Category = classname::GetCategory();  \
   std::vector<double> prefix ## Weights;                               \
   prefix ## Weights.resize(prefix ## Category.Size());                 \
   ConstantSizeSelector prefix ## Selector(prefix ## Weights);

Town* TownGenerator::GenerateTown(int population)
{
   DECLARE_CATEGORY_SELECTION_VARIABLES(Race, race)
   DECLARE_CATEGORY_SELECTION_VARIABLES(Sector, sector)
   DECLARE_CATEGORY_SELECTION_VARIABLES(Profession, profession)

   std::vector<NpcMold> npcMolds;
   for(int i = 0; i < population; ++i)
   {
      for(int j = 0; j < raceCategory.Size(); ++j)
         raceWeights[j] = raceCategory[j].GetWeight();
      Race& chosenRace = raceCategory[raceSelector.Select()];
      
      for(int j = 0; j < sectorCategory.Size(); ++j)
         sectorWeights[j] = sectorCategory[j].GetWeight() * chosenRace.GetSectorScale(j);
      Sector& chosenSector = sectorCategory[sectorSelector.Select()];

      for(int j = 0; j < professionCategory.Size(); ++j)
         professionWeights[j] = professionCategory[j].GetWeight(chosenSector);
      Profession& chosenProfession = professionCategory[professionSelector.Select()];

      npcMolds.push_back(NpcMold(chosenRace, chosenProfession));
   }

   Town* town = new Town(npcMolds);
   return town;
}

TownGenerator* TownGenerator::Create(std::string sectorFilepath, std::string professionFilepath, std::string raceFilepath)
{
   std::cout << "Scanning sector file..." << std::endl;
   std::vector<Sector*> sectors;
   std::ifstream sectorFile;
   sectorFile.open(sectorFilepath);
   if(sectorFile.is_open())
   {
      std::string line;
      while(getline(sectorFile, line))
      {
         Sector* sector = Sector::ParseCsvLine(line);
         if(!sector)
            return nullptr;
         sectors.push_back(sector);
      }
   }
   else
      return nullptr;

   std::cout << "Scanning profession file..." << std::endl;
   std::ifstream professionFile;
   professionFile.open(professionFilepath);
   if(sectorFile.is_open())
   {
      std::string line;
      while(getline(professionFile, line))
      {
         if(!Profession::ParseCsvLine(line, sectors))
            return nullptr;
      }
   }
   else
      return nullptr;

   std::cout << "Scanning race file..." << std::endl;
   std::vector<Race*> races;
   std::ifstream raceFile;
   raceFile.open(raceFilepath);
   if(raceFile.is_open())
   {
      std::string line;
      while(getline(raceFile, line))
      {
         Race* race = Race::ParseCsvLine(line);
         if(!race)
            return nullptr;
         races.push_back(race);
      }
   }
   else
      return nullptr;

   return new TownGenerator();
}