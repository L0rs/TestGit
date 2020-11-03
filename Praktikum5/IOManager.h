#pragma once
#include <map>
#include <string>
#include "Episode.h"
class IOManager
{
public:
   static std::vector<Episode> readEpisodes(std::string inputFile);
   static std::vector<std::string> readCharacters(std::string inputFile);
   static void printMenu();
   static unsigned getUserInput();
   static bool handleRequest(const std::vector<Episode>& episodes, const std::vector<std::string>& characters, unsigned choice);
};

