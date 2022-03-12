#include "Story.hpp"

//print the first page then get the input from users thus then print the next page
void main_loop(char * arg){
    Story story(arg);
    size_t current_page = 1;
    while(story.pages[current_page - 1].type == 2){
        story.pages[current_page - 1].printPage();
        current_page = story.inputConvert(current_page);
    }
    story.pages[current_page - 1].printPage();
}

int main(int argc, char** argv) {
    if (argc != 2) {
        err_exit("Invalid Usage\n");
    }
    main_loop(argv[1]);
    return EXIT_SUCCESS;
}
