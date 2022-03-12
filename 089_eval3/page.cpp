#include "page.hpp"

// check whether the story is at the end(has win/lose), if not, store the choices and choice numbers
void Page::storeChoices(std::string & line){
    if (line == "WIN") {
        type = 0;
    }else if (line == "LOSE") {
        type = 1;
    } else {
        size_t sz;
        int page_num = std::stoi(line, &sz);
        if (page_num < 1) {
            err_exit("Available page num should be larger than one\n");
        }
        pagesNumberTo.push_back(page_num);
        if (line[sz] != ':') {
            err_exit("There is no colon found in the page\n");
        }
        choices.push_back(line.substr(sz + 1));
    }
}

//print the whole page as required
void Page::printPage(){
    for (unsigned long i = 0; i < story.size(); ++ i){
        std::cout << story[i] << std::endl;
    }
    if (type == 2){
        std::cout <<"\nWhat would you like to do?\n" << std::endl;
        for (unsigned long i = 0; i < choices.size(); i++) {
            std::cout << ' ' << i + 1 << ". ";
            std::cout << choices[i] <<std::endl;
        }
    } else if (type == 0){
        std::cout << "\nCongratulations! You have won. Hooray!\n";
    }else{
        std::cout << "\nSorry, you have lost. Better luck next time!\n";
    }
}




