#include "Story.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        err_exit("Invalid Usage\n");
    }
    Story story(argv[1]);
    story.paths_to_win();
    return EXIT_SUCCESS;
}
