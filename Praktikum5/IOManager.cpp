#include "IOManager.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include <iomanip>
#include <cstdio>


std::vector<Episode> IOManager::readEpisodes(std::string inputFile)
{
   const std::regex RE_TITLE{ "(.+)\\s\\((.+)\\)" };
   const std::regex RE_NUMBER{ ".+\\s(\\d+\\.\\d+)" };
   std::string line;
   std::ifstream in{ inputFile, std::ios::in };
   std::vector<Episode> episodes;
   std::getline(in, line); //ignore first line
   while (std::getline(in, line)) {
      std::string germanTitle;
      std::string englishTitle;
      std::string episodeNumber;
      std::vector<std::string> episodeContent;
      std::smatch matches;
      if (std::regex_search(line, matches, RE_NUMBER)) {
         episodeNumber = matches[1];
      }
      else {
         std::cerr << "Structure not as expected" << std::endl;
      }
      std::getline(in, line);
      if (std::regex_search(line, matches, RE_TITLE)) {
         germanTitle = matches[1];
         englishTitle = matches[2];
      }
      else {
         std::cerr << "Structure not as expected" << std::endl;
      }
      while (in >> line) {
         if (line != "****") {
            episodeContent.push_back(line);
         }
         else {
            std::getline(in, line);
            episodeContent.push_back("\n");
            break;
         }
      }
      episodes.push_back({
         episodeNumber,
         germanTitle,
         englishTitle,
         episodeContent
         });
   }
   return episodes;
}

std::vector<std::string> IOManager::readCharacters(std::string inputFile)
{
   std::vector<std::string> characters;
   std::ifstream in{ inputFile, std::ios::in };
   std::string character;
   while (in >> character) {
      characters.push_back(character);
   }
   return characters;
}

void IOManager::printMenu()
{
   std::cout << "[1] " << "Englische Episodentitel und Inhalt einer beliebigen Episode ausgeben\n";
   std::cout << "[2] " << "Nur Rückblicke einer beliebigen Episode ausgeben\n";
   std::cout << "[3] " << "Die 15 häufigsten Wörter der Rückblicke einer Episode ausgeben\n";
   std::cout << "[4] " << "Hauptpersonen aller Episoden ausgeben\n\n";
   std::cout << "[9] " << "Programm beenden\n";
   std::cout << "Ihre Wahl: ";
}

unsigned IOManager::getUserInput()
{
   unsigned choice;
   std::cin >> choice;
   return choice;
}



bool IOManager::handleRequest(const std::vector<Episode>& episodes, const std::vector<std::string>& characters, unsigned choice)
{
   const std::regex RE_NUMBER{ "\\d\\.(\\d+)" };
   std::smatch matches;
   std::string strEpisodeNumber;
   unsigned episodeNumber{ 0 };
   switch (choice) {
   case 1:
   {
      for (Episode e : episodes) {
         std::cout << e.getEpisodeNumber() << " " << e.getEnglishTitle() << "\n";
      }
      std::cout << "\nVon welcher Episode möchten Sie den Inhalt sehen?\n"
         << "Ihre Wahl: ";
      std::cin >> strEpisodeNumber;
      if (std::regex_search(strEpisodeNumber, matches, RE_NUMBER)) {
         std::string tmp{ matches[1] };
         episodeNumber = std::atoi(tmp.c_str());
      } 
      else{
         std::cerr << "Structure not as expected" << std::endl;
      }
      if (episodeNumber <= episodes.size()) {
         auto& e = episodes[episodeNumber - 1];
         std::cout << "Episode " << episodeNumber << ": deutsch: " << e.getGermanTitle()
            << "\nenglisch: " << e.getEnglishTitle() << "\n" << e.getContent() << std::endl;
      }
      else
         std::cerr << "Wrong input!\n";
      break;
   }
   case 2:
   {
      std::cout << "****Nur Rückblicke einer Episode ausgeben****"
         << "Von welcher episode sollen die Rückblicke ausgegeben werden: ";
      std::cin >> strEpisodeNumber;
      if (std::regex_search(strEpisodeNumber, matches, RE_NUMBER)) {
         std::string tmp{ matches[1] };
         episodeNumber = std::atoi(tmp.c_str());
      }
      else {
         std::cerr << "Structure not as expected" << std::endl;
      }
      if (episodeNumber <= episodes.size())
         std::cout << episodes[episodeNumber].getFlashback() << std::endl;
      else
         std::cerr << "Wrong input!\n";
      break;
   }
   case 3:
   {
      std::cout << "****Die 15 häufigsten Wörter ausgeben****\n";
      std::cout << "Von welcher Episode sollen die 15 häufigsten Wörter ausgegeben werden: ";
      std::cin >> strEpisodeNumber;
      if (std::regex_search(strEpisodeNumber, matches, RE_NUMBER)) {
         std::string tmp{ matches[1] };
         episodeNumber = std::atoi(tmp.c_str());
      }
      else {
         std::cerr << "Structure not as expected" << std::endl;
      }
      if (episodeNumber <= episodes.size()) {
         auto highscore = episodes[episodeNumber].getHighscore();
         for (size_t i{ 0 }; i < 15 && i < highscore.size(); i++) {
            std::cout << highscore[i].first << " " << highscore[i].second << std::endl;
         }
      }
      else
         std::cerr << "Wrong input!\n";
      break;
   }
   case 4:
   {
      std::cout << "****Hauptpersonen aller Episoden ausgeben****\n";
      std::cout << std::setw(10) << "Episode" << std::setw(20) << "Titel" << std::setw(20) << "Hauptpersonen (en)\n";
      for (auto episode: episodes) {
         std::stringstream out;
         auto highscore = episode.getHighscore();
         for (auto item : highscore) {
            for (auto character : characters) {
               if (item.second == character && item.first >= 5)
               {
                  if (out.str() == "")
                     out << character;
                  else
                     out << ", " << character;
               }
            }
         }
         std::string charOut = out.str() == "" ? "keine spezielle" : out.str();
         std::cout << std::setw(10) << episode.getEpisodeNumber() 
            << std::setw(30) << episode.getGermanTitle() 
            << std::setw(30) << charOut<<std::endl;
      }
      break;
   }
   case 9: return false;
   default: std::cerr << "Wrong input!\n";
   }
   return true;
}
