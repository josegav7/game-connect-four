#include <iostream>
#include "ConnectFour.h"


ConnectFour::ConnectFour(char _emptyToken,std::vector<char>_playerTokens,std::vector<char> initTokens,int _startingPlayerId) : emptyToken(_emptyToken), playerTokens(_playerTokens), currentPlayerId(_startingPlayerId)
{
  if(initTokens.empty())
  {                            //If there are not initial tokens,
  for (int r=0; r<numRows; r++) //initialize an empty board
  {
    board.push_back({});
     for(int c=0; c<numCols; c++)
     {
       board[r].push_back(emptyToken);
     }
  }
}
  else 
    for(int r=0; r<numRows; r++) //If there are initial tokens,
      {                          //place them in the board
        board.push_back({});
        for(int c=0; c<numCols; c++)
          {
            board[r].push_back(initTokens[r*7 + c]);
          }
      } 
}


void ConnectFour :: play(){
      bool isGoodMove = false;
      this->printInstructions(); // print instructions
      this->printBoard(); // print the board
      while( !this->isWin() && !this->isTie()) { // keep playing as long as the game is not won or tied
        isGoodMove = this->takeTurn(); // current player takes a turn
           if (isGoodMove) {
             this->printBoard(); // print the board if that was a good move
             if (this->isWin())  break; // if that was a winning move, quit the game
             if(this->isTie())  break;// else if the game is tied, quit the game
             this->nextPlayer(); // else, advance to the next player in the game.
             } // else that was an illegal move
      } // end while: game over
      if (this->getWinningPlayerId() == -1)
        std::cout << "Sorry - It looks like the game was a tie." << std::endl;
      else
        std::cout << "Congratulation: Player #" << this->getCurrentPlayerToken() << " has won the game!" << std::endl;
      std::cout << "Goodbye!" << std::endl;
    } // end play

void ConnectFour :: printInstructions() {
  std::cout << "The rules are simple: Try to build a row, column, or diagonal of four tokens while keeping your opponent(s) from doing the same. Sounds easy, but it is not! Enjoy the game! :)" << std::endl << std::endl;
}

void ConnectFour :: printBoard() //just printing the board row by row
{
  std::cout<<"1 2 3 4 5 6 7" <<std::endl;
  for(int r=0; r<board.size(); r++)
    {
      for(int c=0; c<board[r].size(); c++)
        {
          std::cout <<board[r][c] << " ";
        }
      std::cout<<std::endl;
    }
  std::cout<<std::endl;
}

 char ConnectFour::getCurrentPlayerToken()
{
  return playerTokens[currentPlayerId];
}

 void ConnectFour::nextPlayer()
{
  currentPlayerId++;
  currentPlayerId = currentPlayerId % playerTokens.size(); //Here we use modulo to find the sequence of turns given the number of players
}

 bool ConnectFour::takeTurn()
{
  int columnNumber;
  std::cout<<"select a column number between 1-7" << std::endl;
  std::cin>> columnNumber;

  if (columnNumber < 1 || columnNumber > 7) //Check if it is a valid number
    { 
    std::cout<<"Sorry, this is not a valid column number." 
    <<std::endl <<std::endl;
    return false; //If it is not valid, let the player know 
    }

  
  if (board[0][columnNumber-1] != emptyToken)
  {
    std::cout<<"Sorry, this column is full." << std::endl <<std::endl;
    return false;
  }
    //if the location for the token is not empty, let the player 
    //know and return false

  else 
  {
    for(int r=numRows-1; r > -1; r--)
    {
      if (board[r][columnNumber-1] == emptyToken)
      { 
        board[r][columnNumber-1] = getCurrentPlayerToken();
        return true;
      }
    }
  } //if there is space on the column, drop the token to the 
    //bottom of the column and return true 
  
  return false;
}; 


    bool ConnectFour::isWin()
   {
     for(int r=0; r<numRows;r++)  //Check each row
       {
         int count=0; //if checking a new row, set the count to 0
         for (int c=0; c<numCols; c++)
           {
             if (board[r][c] == getCurrentPlayerToken())
             {
               count++;     //Increase count every time we find 
                           //successive tokens of the current 
                          //player to check if it was a winning
                         // move.
               if(count == 4) {return true;} //If 4 are found, 
                                            //he/she won
             }
             else count=0; //If a different token is found, 
                          //set the count back to zero
           }
       }

     for(int c=0; c<numCols;c++) //Same idea but checking each 
                                 //column
       {
         int count=0; 
         for (int r=0; r<numRows; r++)
           {
             if (board[r][c] == getCurrentPlayerToken())
             {
               count++;
               if(count == 4) {return true;}
             }
             else count=0;
           }
       }

     {
      int count = 0;
      for(int rx=numRows-1,cx=0; cx<numCols;(rx >0? rx-- 
          :cx++)) //Same idea but checking diagonals
      {
          for(int r=rx, c=cx; r<numRows; r++, c++)
          { 
            if (r<numRows && c<numCols)
            {
              if (board[r][c] == getCurrentPlayerToken())
              {
               count++;
               if(count == 4) {return true;}
                }
              else count = 0;
              }
            }
        }
       }
     
     return false; //It wasn't a winning move
     
     };
       
     
    int ConnectFour::getWinningPlayerId()
    {
      return currentPlayerId;
    }; 


    bool ConnectFour::isTie() //If there are not empty spaces, 
                             //return true, it is a tie.
    {
      for (int r=0; r<numRows; r++)
      {
      for (int c=0; c<numCols; c++)
        {
          if (board[r][c] == emptyToken) {return false;}
        }
      }
      return true;
    }; 
   
  
