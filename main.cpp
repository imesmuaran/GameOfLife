#include <iostream>
#include <stdlib.h>

class Board
{
  private:
    int size_x;
    int size_y;
    char** board;
  public:
    Board(int x, int y) {
      if (x % 2 == 0 && y % 2 == 0) {
        size_x = x;
        size_y = y;
        board = (char**) calloc(sizeof(char*), size_x);
        for (int i = 0; i < size_x; i++) {
          board[i] = (char*) calloc(sizeof(char), size_y);
        }
      }
      else {
        std::cerr << "Size is not a multiple of 2: (" << x << "," << y << ")" << std::endl;
      }
    }

    void set_living(int x, int y) {
      if ( (x > -1 && x <= size_x) && (y > -1 && y <= size_y)) {
        board[x][y] = 1;
      }
      
    }

    ~Board() {
      for (int i = 0; i < size_x; i++) {
        free(board[i]);
      }
      free(board);
    }
};

class Control
{
  private:
  public:
};

class GUI
{
  private:
  public:
};

int main(void)
{
    Board b1 = Board(100,100);

    return 0;
}