#include <iostream>
#include <cstdlib>
#include <utility>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include "page.hpp"

/*
 * @para folderName: story's name e.g. story1
 * @para winnable: 0 for cannot win and 1 for having possibility to win
 * @func starter: load pages and compute the necessary data of this game
 * @func pages_format_check: pages checker and catch exceptions for invalid pages
 * @func generate_reachable: store reachable pages
 * */

class Story{
private:
    std::string folderName;
    int winnable = 0;
    void starter();
    unsigned long get_input();
    void pages_format_check();
    void generate_reachable();
    void paths_to_win(unsigned long thisPage, std::vector<std::pair<unsigned long, unsigned long>> path);

public:
    std::vector<Page> pages;
    std::map<unsigned long, unsigned long> reachable_map;
    std::vector<unsigned long> unreachable_pages;
    explicit Story(std::string directory_name) : folderName(std::move(directory_name)) {starter();}
    void paths_to_win();
    unsigned long inputConvert(unsigned long page_from);
};