#include <iostream>
#include <cstdlib>
#include <utility>
#include <vector>
#include <fstream>
#include "exception.hpp"

class Page{
private:
    std::vector<std::string> choices;
    std::vector<std::string> story;
    void storeChoices(std::string & line);
public:
    std::vector<unsigned long> pagesNumberTo;
    int type = 2; //win for 0, lose for 1, navigation for 2
    explicit Page(std::string filename) : type(2){
        std::string line;
        std::ifstream ifs(filename);
        if (!ifs.is_open()) {
            throw unreachable_file();
        }
        bool key = false;
        while (std::getline(ifs, line)) {
            if (line[0] == '#'){
                key = true;
                continue;
            }
            else if (!key && type == 2) {
                storeChoices(line);
            }else{
                story.push_back(line);
            }
        }
        ifs.close();
        if (type != 2) {
            if (pagesNumberTo.size() != 0) {
                err_exit("Invalid page: There is navigation part in ending page\n");
            }
        }
        else if (!key) {
            err_exit("Invalid page: There is no # in the page\n");
        }
        else {
            if (pagesNumberTo.size() == 0){
                err_exit("Invalid page: No type satisfied\n");
            }
        }
    };

    void printPage();
};
