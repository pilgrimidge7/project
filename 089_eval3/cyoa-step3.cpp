#include "Story.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        err_exit("Invalid Usage\n");
    }
    Story story(argv[1]);
    for (size_t unreachable_page : story.unreachable_pages){
        std::cout << "Page " << unreachable_page << " is not reachable\n";
    }
    for (auto & it : story.reachable_map){
        std::cout << "Page " << it.first << ":" << it.second << std::endl;
    }
    return EXIT_SUCCESS;
}
