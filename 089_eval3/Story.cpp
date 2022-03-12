#include "Story.hpp"

void Story::starter(){
    try{
        //store every page in pages
        unsigned long i = 0;
        while(true){
            i++;
            std::string filePath = (folderName + "/page" + std::to_string(i) + ".txt");
            Page page(filePath);
            pages.push_back(page);
        }
    }
    catch(const unreachable_file & e) {}
    pages_format_check();
    generate_reachable();
    for (unsigned long i = 2; i <= pages.size(); ++ i)  {
        if (reachable_map.find(i) == reachable_map.end()){
            unreachable_pages.push_back(i);
        }
    }
}

void Story::pages_format_check(){
    bool there_is_a_win = false;
    bool there_is_a_lose = false;
    for (unsigned long curr_page_num = 2; curr_page_num <= pages.size(); ++ curr_page_num) {
        if (pages[curr_page_num - 1].type != 2){
            if (pages[curr_page_num - 1].type == 0){
                there_is_a_win = true;
            }else{
                there_is_a_lose = true;
            }
        }
    }
    if (!(there_is_a_win && there_is_a_lose)){
        err_exit("There is no win or lose page\n");
    }
}

// store each page and corresponding depth
void Story::generate_reachable(){
    std::pair<unsigned long, unsigned long> thisPair (1, 0);
    reachable_map.insert(thisPair);
    unsigned long depth = 1;
    auto iteratorA = reachable_map.begin();
    auto iteratorB = iteratorA;
    while (iteratorA != reachable_map.end()) {
        for (unsigned long j : pages[iteratorA->first - 1].pagesNumberTo) {
            thisPair.first = j;
            thisPair.second = depth;
            reachable_map.insert(thisPair);
        }
        if (iteratorA == iteratorB) {
            iteratorB = reachable_map.end();
            -- iteratorB;
            ++depth;
        }
        ++iteratorA;
    }
}

// this function is to get the input from users
unsigned long Story::get_input() {
    try {
        std::string input_str;
        if (!getline(std::cin, input_str)) {
            return 0;
        }
        unsigned long int_sz;
        int input = stoi(input_str, &int_sz);
        if (std::cin.good() && input > 0 && int_sz == input_str.length()) {
            return input;
        }
    }catch (std::exception & e){}
    return 0;
}

//this function is to get users' input and convert to page number
unsigned long Story::inputConvert(unsigned long page_from){
    while(true) {
        unsigned long input = 0;
        input = get_input();
        while (input == 0 || input > pages[page_from - 1].pagesNumberTo.size()){
            std::cout << "That is not a valid choice, please try again\n";
            input = get_input();
        }

        unsigned long ans = pages[page_from - 1].pagesNumberTo[(unsigned long) input - 1];
        return ans;
    }
}

void Story::paths_to_win(){
    std::vector<std::pair<size_t, size_t> >  path;
    paths_to_win(1, path);
    if (winnable == 0) {
        std::cout << "This story is unwinnable!\n";
    }
}

//this function is to use iterator using BFS to find the path to win
void Story::paths_to_win(unsigned long this_page, std::vector<std::pair<size_t, size_t> >  path) {
    bool intoALoop = false;
    for (auto i : path){
        if (i.first == this_page){
            intoALoop = true;
        }
    }
    if (intoALoop == false) {
        // print if it reaches the win page
        if (pages[this_page - 1].type == 2) {
            // record this page and go to next page
            unsigned long i = 1;
            for (auto next_page: pages[this_page - 1].pagesNumberTo) {
                if (i == 1) {
                    std::pair<unsigned long, unsigned long> temp_pair(this_page, 1);
                    path.push_back(temp_pair);
                } else {
                    path.pop_back();
                    std::pair<unsigned long, unsigned long> temp_pair(this_page, i);
                    path.push_back(temp_pair);
                }
                paths_to_win(next_page, path);
                ++i;
            }
        } else {
            if (pages[this_page - 1].type == 0) {
                for (auto it: path) {
                    std::cout << it.first << "(" << it.second << "),";
                }
                std::cout << this_page << "(win)" << std::endl;
                winnable = true;
            }

        }
    }
}