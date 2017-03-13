#include <iostream>
#include <sstream>
#include <stdlib.h>

class Board
{
  private:
    unsigned int size_x;
    unsigned int size_y;
    char** board;
  public:
    Board(unsigned int x, unsigned int y) {
      if (x % 2 == 0 && y % 2 == 0) {
        size_x = x;
        size_y = y;
        board = (char**) calloc(sizeof(char*), size_x);
        for (unsigned int i = 0; i < size_x; i++) {
          board[i] = (char*) calloc(sizeof(char), size_y);
        }
      }
      else {
        std::cerr << "Size is not a multiple of 2: (" << x << "," << y << ")" << std::endl;
      }
    }

    ~Board() {
      for (unsigned int i = 0; i < size_x; i++) {
        free(board[i]);
      }
      free(board);
    }

    unsigned int get_size_x() {
      return size_x;
    }

    unsigned int get_size_y() {
      return size_y;
    }

    char get_state(unsigned int x, unsigned int y) {
      if (x <= size_x && y <= size_y) {
        return board[x][y];
      }
      else {
        throw std::out_of_range("Position not on Board!");
      }
    }

    void set_living(unsigned int x, unsigned int y) {
      if (x <= size_x && y <= size_y) {
        board[x][y] = 1;
      }
    }

    void set_dead(unsigned int x, unsigned int y) {
      if (x <= size_x && y <= size_y) {
        board[x][y] = 0;
      }
    }

    unsigned char count_living_neigbors(unsigned int x, unsigned int y) {
      unsigned char c = 0;
      
      for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
          if (i == 0 && j == 0) { continue;}
          try {
            c += get_state(x+i, y+j);
          }
          catch (std::out_of_range e) {
            continue;
          }
        }
      }

      return c;
    }
};

class Control
{
  private:
    Board *board;
  public:
    void set_new_board(unsigned int x, unsigned int y) {
      board = new Board(x,y);
    }

    Board* get_board() {
      return board;
    }

    void do_single_tick() {
      for (unsigned int i = 0; i < board->get_size_x(); i++) {
        for (unsigned int j = 0; j < board->get_size_y(); j++) {
          if (board->get_state(i,j)) {
            unsigned char c = board->count_living_neigbors(i,j);
            if (!(c == 2 || c == 3)) {
              board->set_dead(i,j);
            }
          }
          else {
            unsigned char c = board->count_living_neigbors(i,j);
            if (c == 3) {
              board->set_living(i,j);
            }
          }
        }
      }
    }
};

class GUI
{
  private:
    Control* control;
  public:
    GUI(Control* c) {
      control = c;
    }

    void print_board() {
      Board *b = control->get_board();
      std::ostringstream s;
      s << "Board: \n";
      for (unsigned int i = 0; i < b->get_size_x(); i++) {
        for (unsigned int j = 0; j < b->get_size_y(); j++) {
          int state = b->get_state(i,j);
          s << state;
          s << " ";
        }
        s << "\n";
      }
      std::cout << s.str();
    }
};

int main(void)
{
    Control c;
    GUI g = GUI(&c);
    c.set_new_board(10,10);
    g.print_board();
    return 0;
}