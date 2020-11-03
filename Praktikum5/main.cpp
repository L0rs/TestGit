#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>
#include <vector>
#include "Episode.h"
#include "IOManager.h"
int main()
{
   setlocale(LC_ALL, "");
   const std::string LOST_S1{ "Lost_Staffel_1.txt" };
   const std::string MAIN_CHARS{ "Hauptpersonen.txt" };
   auto episodes{ IOManager::readEpisodes(LOST_S1) };
   auto characters{ IOManager::readCharacters(MAIN_CHARS) };
   bool isRunning{ true };
   while (isRunning)
   {
      IOManager::printMenu();
      unsigned choice{IOManager::getUserInput()};
      isRunning = IOManager::handleRequest(episodes, characters, choice);
   }
   return 0;
}