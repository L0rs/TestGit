#pragma once
#include <string>
#include <map>
#include <vector>
class Episode
{
public:
   Episode(std::string number, std::string german, std::string english, std::vector<std::string> content);
   std::string getEpisodeNumber() const;
   std::string getGermanTitle() const;
   std::string getEnglishTitle() const;
   std::string getContent() const;
   std::string getFlashback() const;
   std::vector<std::pair<unsigned,std::string>> getHighscore() const;
private:
   std::string episodeNumber;
   std::string germanTitle;
   std::string englishTitle;
   std::string content;
   std::string flashback;
   std::map<std::string, unsigned> highscore;
};

