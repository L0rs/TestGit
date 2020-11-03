#include "Episode.h"
#include <algorithm>
#include <iostream>
Episode::Episode(std::string number, std::string german, std::string english, std::vector<std::string> words)
   :episodeNumber{ number }, germanTitle{ german }, englishTitle{ english }
{
   bool isFlashback{ false };
   for (auto word : words) {
      content += word + " ";
      if (word == "<FLASHBACK>")
         isFlashback = true;
      else if (word == "</FLASHBACK>")
         isFlashback = false;
      else if (isFlashback)
      {
         auto iter = highscore.find(word);
         if (iter != highscore.end())
            highscore[word]++;
         else
            highscore.insert(std::make_pair(word, 1));
         flashback += word + " ";
      }
   }
}

std::string Episode::getEpisodeNumber() const
{
   return episodeNumber;
}

std::string Episode::getGermanTitle() const
{
   return germanTitle;
}

std::string Episode::getEnglishTitle() const
{
   return englishTitle;
}

std::string Episode::getContent() const
{
   return content;
}

std::string Episode::getFlashback() const
{
   return flashback;
}

std::vector<std::pair<unsigned, std::string>> Episode::getHighscore() const
{
   std::vector<std::pair<unsigned, std::string>> pairs;
   for (auto iter = highscore.begin(); iter != highscore.end(); ++iter) {
      pairs.push_back(std::make_pair(iter->second, iter->first));
   }

   std::sort(pairs.rbegin(), pairs.rend(), [](std::pair<unsigned, std::string>& a, std::pair<unsigned, std::string>& b)
      {
         return a.first < b.first;
      }
   );
   return pairs;
}


