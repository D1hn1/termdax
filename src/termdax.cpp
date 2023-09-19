#include <sys/ioctl.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string.h>

struct posList
{
    int type;
    int cord_x;
    int cord_y;
    int _width;
    int _height;
    char _char;
    const char* text;
};

struct Termdax
{   
    private:
        std::vector<posList> array;

    public:
        int windowSizeX;
        int windowSizeY;

        Termdax ()
        {
            struct winsize window;
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
            windowSizeX = window.ws_col;
            windowSizeY = window.ws_row;
        }

        void clearScreen ()
        {
            system("clear");
        }

        void printWidthAndHeight () {
            std::cout << "X: " << windowSizeX << std::endl;
            std::cout << "Y: " << windowSizeY << std::endl;
        }

        void fillConsoleWithCaracter ( char simbol )
        {
            for ( int y = 0; y < windowSizeY; y++ ) {
                for ( int x = 0; x < windowSizeX; x++ ) {
                    std::cout << simbol;
                };
            };
        }

        char getKeyPressed ()
        {
            char keyPressed;
            system("stty raw");
            keyPressed = getchar();
            system("stty cooked");
            return keyPressed;
        }

        void Draw ()
        {
            bool itemPrinted = false;
            int iterations = 0;
            for ( int y = 0; y < windowSizeY; y++ ) {
                for ( int x = 0; x < windowSizeX; x++ ) {
                    for ( posList element : array ) {
                        if ( element.type == 1 ) {
                            int width = element.cord_x + element._width;
                            int height = element.cord_y + element._height;
                            if ( x >= element.cord_x && y >= element.cord_y ) {
                                if ( x <= ( width - 1 ) && y <= ( height - 1 ) ) {
                                    std::cout << element._char;
                                    itemPrinted = true;
                                } else {
                                    itemPrinted = false;
                                };
                            };

                        } else if ( element.type == 2 ) {
                            if ( x >= element.cord_x && y >= element.cord_y && x <=  ( strlen(element.text) + element.cord_x ) && y <= element.cord_y) {
                                if ( iterations != strlen(element.text) ) {
                                    std::cout << element.text[iterations];
                                    iterations++;
                                    itemPrinted = true;
                                } else {
                                    iterations = 0;
                                    itemPrinted = false;
                                };
                            };
                         };
                    };
                    if ( !itemPrinted ) { std::cout << " "; };
                };
            };
        }

        void destroyAll()
        {
			array = {};
        }

        void createRectangle ( int x_rec, int y_rec, int width, int height, char fill )
        {
            array.push_back({1, x_rec, y_rec, width, height, fill, NULL});
        }

        void createText ( int x_pos, int y_pos, const char* text )
        {
            array.push_back({2, x_pos, y_pos, NULL, NULL, NULL, text});
        }

};
