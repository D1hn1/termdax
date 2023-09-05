#include <sys/ioctl.h>
#include <iostream>
#include <unistd.h>

// make a array that holds the position of all rectangles and shapes
// when you call termdax.makeRectangle() it saves the position in the array and then
// when you call termdax.draw() it draws it in to the screen

struct Termdax
{
    int windowSizeX;
    int windowSizeY;
    int array[]; // IN THIS ARRAY ( IT HAS TO ALLOCATE THE MEMORY DINAMICLY )

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

    void fillConsoleWithCaracter ( const char* simbol )
    {
        for ( int y = 0; y < windowSizeY; y++ ) {
            for ( int x = 0; x < windowSizeX; x++ ) {
                std::cout << simbol;
            };
        };
    }

    char getKeyPressed ( )
    {
        char keyPressed;
        system("stty raw");
        keyPressed = getchar();
        system("stty cooked");
        return keyPressed;
    }

    void drawRectangle ( int x_rec, int y_rec, int _width, int _height, const char* fill )
    {
        int width = x_rec + _width;
        int height = y_rec + _height;
        for ( int y = 0; y < windowSizeY; y++ ) {
            for ( int x = 0; x < windowSizeX; x++ ) {
                // HERE CREATE ANOTHER FOR LOOP TO LOOP EACH ONE OF THE SHAPES 
                // THAT ARE IN THE ARRAY TO DRAW IN TO THE SCREEN
                if ( x >= x_rec && y >= y_rec ) {
                    if ( x <= ( width - 1 ) && y <= ( height - 1 ) ) {
                        std::cout << fill;
                        continue;
                    };
                };
                std::cout << " ";

            };
        };
    }

    void draw ()
    {
        std::cout << "Hello World" << std::endl;
    }
};

int main() {
    Termdax termdax;
    int upDown = 0;
    int leftRight = 0;
    while ( true ) {
        char keyPressed = termdax.getKeyPressed();
        termdax.clearScreen();
        if ( keyPressed == 'w' ) {
            upDown--;
            termdax.drawRectangle( leftRight, upDown, 2, 2, "$");
        } else if ( keyPressed == 's' ) {
            upDown++;
            termdax.drawRectangle( leftRight, upDown, 2, 2, "$");
        } else if ( keyPressed == 'a' ) {
            leftRight--;
            termdax.drawRectangle( leftRight, upDown, 2, 2, "$");
        } else if ( keyPressed == 'd' ) {
            leftRight++;
            termdax.drawRectangle( leftRight, upDown, 2, 2, "$");
        } else if ( keyPressed == 'q' ) {
            exit(0);
        };
    };
    return 0;
}