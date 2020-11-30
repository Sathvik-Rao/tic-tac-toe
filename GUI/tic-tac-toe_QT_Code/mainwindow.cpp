#include "mainwindow.h"
#include "ui_mainwindow.h"

std::string playerName;	//player name
char playerCharacter, computerCharacter;  // O or X

constexpr short O = 0, X = 10;

short playerNumber;	//player move number

short level ;	//easy,moderate,hard -1,0,1,2

constexpr short winnerLoactions[8][3] {		//win locations
{0,1,2} ,
{3,4,5} ,
{6,7,8} ,
{0,3,6} ,
{1,4,7} ,
{2,5,8} ,
{0,4,8} ,
{2,4,6}
};

static bool flag = false;	//false -> player turn (or) true -> computer turn [for tree]
static bool flag1 = true;	//false -> player turn (or) true -> computer turn [for game]
static bool endGame = false;    //game ends when endGame is true
static bool gameStarted = false;    //gameStarts when gameStarted is true

std::fstream file;
std::string fileName;
std::string *fileData;
long fileDataSize;

static Ui::MainWindow *uI;  //duplicate ui pointer (So, that it is accesible throught mainwindow.cpp)

std::string past {};

//Tree node data type
struct tree
{
    tree *p[8] {nullptr};
    short a[9];
    short points = 0;
};

tree *root;     //root pointer

void display(tree *t)
{
    for(short i=0;i<9;i++)
    {
        if(uI->pushButton_1->isEnabled() && i==0)
        {
            if(t-> a[i] == X || t-> a[i] == O)
            {
                if(computerCharacter == 'X')
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/x.png"));
                    uI->pushButton_1->setIcon(ButtonIcon);
                    uI->pushButton_1->setIconSize(QSize(40, 40));
                }
                else
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/o.png"));
                    uI->pushButton_1->setIcon(ButtonIcon);
                    uI->pushButton_1->setIconSize(QSize(40, 40));
                }
                uI->pushButton_1->setDisabled(true);
                break;
            }
        }
        else if(uI->pushButton_2->isEnabled() && i==1)
        {
            if(t-> a[i] == X || t-> a[i] == O)
            {
                if(computerCharacter == 'X')
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/x.png"));
                    uI->pushButton_2->setIcon(ButtonIcon);
                    uI->pushButton_2->setIconSize(QSize(40, 40));
                }
                else
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/o.png"));
                    uI->pushButton_2->setIcon(ButtonIcon);
                    uI->pushButton_2->setIconSize(QSize(40, 40));
                }
                uI->pushButton_2->setDisabled(true);
                break;
            }
        }
        else if(uI->pushButton_3->isEnabled() && i==2)
        {
            if(t-> a[i] == X || t-> a[i] == O)
            {
                if(computerCharacter == 'X')
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/x.png"));
                    uI->pushButton_3->setIcon(ButtonIcon);
                    uI->pushButton_3->setIconSize(QSize(40, 40));
                }
                else
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/o.png"));
                    uI->pushButton_3->setIcon(ButtonIcon);
                    uI->pushButton_3->setIconSize(QSize(40, 40));
                }
                uI->pushButton_3->setDisabled(true);
                break;
            }
        }
        else if(uI->pushButton_4->isEnabled() && i==3)
        {
            if(t-> a[i] == X || t-> a[i] == O)
            {
                if(computerCharacter == 'X')
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/x.png"));
                    uI->pushButton_4->setIcon(ButtonIcon);
                    uI->pushButton_4->setIconSize(QSize(40, 40));
                }
                else
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/o.png"));
                    uI->pushButton_4->setIcon(ButtonIcon);
                    uI->pushButton_4->setIconSize(QSize(40, 40));
                }
                uI->pushButton_4->setDisabled(true);
                break;
            }
        }
        else if(uI->pushButton_5->isEnabled() && i==4)
        {
            if(t-> a[i] == X || t-> a[i] == O)
            {
                if(computerCharacter == 'X')
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/x.png"));
                    uI->pushButton_5->setIcon(ButtonIcon);
                    uI->pushButton_5->setIconSize(QSize(40, 40));
                }
                else
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/o.png"));
                    uI->pushButton_5->setIcon(ButtonIcon);
                    uI->pushButton_5->setIconSize(QSize(40, 40));
                }
                uI->pushButton_5->setDisabled(true);
                break;
            }
        }
        else if(uI->pushButton_6->isEnabled() && i==5)
        {
            if(t-> a[i] == X || t-> a[i] == O)
            {
                if(computerCharacter == 'X')
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/x.png"));
                    uI->pushButton_6->setIcon(ButtonIcon);
                    uI->pushButton_6->setIconSize(QSize(40, 40));
                }
                else
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/o.png"));
                    uI->pushButton_6->setIcon(ButtonIcon);
                    uI->pushButton_6->setIconSize(QSize(40, 40));
                }
                uI->pushButton_6->setDisabled(true);
                break;
            }
        }
        else if(uI->pushButton_7->isEnabled() && i==6)
        {
            if(t-> a[i] == X || t-> a[i] == O)
            {
                if(computerCharacter == 'X')
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/x.png"));
                    uI->pushButton_7->setIcon(ButtonIcon);
                    uI->pushButton_7->setIconSize(QSize(40, 40));
                }
                else
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/o.png"));
                    uI->pushButton_7->setIcon(ButtonIcon);
                    uI->pushButton_7->setIconSize(QSize(40, 40));
                }
                uI->pushButton_7->setDisabled(true);
                break;
            }
        }
        else if(uI->pushButton_8->isEnabled() && i==7)
        {
            if(t-> a[i] == X || t-> a[i] == O)
            {
                if(computerCharacter == 'X')
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/x.png"));
                    uI->pushButton_8->setIcon(ButtonIcon);
                    uI->pushButton_8->setIconSize(QSize(40, 40));
                }
                else
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/o.png"));
                    uI->pushButton_8->setIcon(ButtonIcon);
                    uI->pushButton_8->setIconSize(QSize(40, 40));
                }
                uI->pushButton_8->setDisabled(true);
                break;
            }
        }
        else if(uI->pushButton_9->isEnabled() && i==8)
        {
            if(t-> a[i] == X || t-> a[i] == O)
            {
                if(computerCharacter == 'X')
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/x.png"));
                    uI->pushButton_9->setIcon(ButtonIcon);
                    uI->pushButton_9->setIconSize(QSize(40, 40));
                }
                else
                {
                    QIcon ButtonIcon(QPixmap(":/resources/images/o.png"));
                    uI->pushButton_9->setIcon(ButtonIcon);
                    uI->pushButton_9->setIconSize(QSize(40, 40));
                }
                uI->pushButton_9->setDisabled(true);
                break;
            }
        }
    }
}   //end of diaplay function

tree *ref;	//back track reference
void createFullTree(tree *t)
{
    tree *temp = new tree;
    short noRepeat;
    for(short i = 0; i < 8; i++)	//check available pointers in previous node
    {
        if(t->p[i] == nullptr)
        {
            t -> p[i] = temp;
            noRepeat = i;
            break;
        }
    }
    flag = !flag;
    for(short i = 0; i < 9; i++)	//dublicate previous array
    {
        temp -> a[i] = t -> a[i];
    }
    for(short i = 0; i < 9; i++)	//replace number with X or O
    {
        if(temp -> a[i] != O && temp -> a[i] != X && noRepeat-- == 0)
        {
            if(flag)	//true -> computer
            {
                if(computerCharacter == 'O')
                  temp -> a[i] = O;
                else
                  temp -> a[i] = X;
            }
            else		//false -> player
            {
                if(playerCharacter == 'O')
                  temp -> a[i] = O;
                else
                  temp -> a[i] = X;
            }
            break;
        }
    }
    //check win or lose
    for(short i = 0; i < 8; i++)	//winnerLoactions[8][3]
    {
        short c = 0;	//count matching (+3 win, -3 lose)
        for(short j = 0; j < 3; j++)	//winnerLoactions[8][3]
        {
            short t = temp -> a[ winnerLoactions[i][j] ];
            if(computerCharacter == 'O')
            {
                if(t == 0)
                  ++c;
            }
            else if(computerCharacter == 'X')
            {
                if(t == 10)
                  ++c;
            }
            if(playerCharacter == 'O')
            {
                if(t == 0)
                  --c;
            }
            else if(playerCharacter == 'X')
            {
                if(t == 10)
                  --c;
            }
        }
        if(c == 3)	//computer win
        {
            ref = temp;
            temp -> points += 1;
            flag = !flag;
            return;
        }
        if(c == -3)	//computer lose
        {
            ref = temp;
            temp -> points -= 1;
            flag = !flag;
            return;
        }
    }
    //check if end of line for leaf nodes
    short s = 0;
    for(short i = 0; i < 9; i++)
    {
        if(temp -> a[i] != O && temp -> a[i] != X)
          s++;
    }
    if(s == 0)	//if last node
    {
        ref = temp;
        flag = !flag;
        return;
    }

    for(short i = 0; i < 9; i++)
    {
        if(temp -> a[i] != O && temp -> a[i] != X)
        {
            createFullTree(temp);
            temp -> points += ref -> points;
        }
    }
    flag = !flag;
}//end of createFullTree function

void deleteFullTree(tree *t)
{
    for(short i = 0; i < 8; i++)
    {
        if(t->p[i] != nullptr)
        {
            deleteFullTree(t->p[i]);
            delete(t->p[i]);
        }
    }
}//end of deleteFullTree function

tree *workingNode ;	//reference node
void MainWindow::startGame()
{
    gameStarted = true;
    root = new tree; //create root node
    //root node array
    for(short i = 0; i < 9; i++)
    {
        if(i+1 == playerNumber)
        {
            if(playerCharacter == 'O')
              root -> a[i] = O;
            else
              root -> a[i] = X;
        }
        else
          root -> a[i] = i + 1;
    }
    //create tree
    for(short i = 1; i < 9; i++)	//8 nodes to root node
    {
        createFullTree(root);
    }
    fileDataSize = 0;
    if(level == 2)	//Open file
    {
        fileName = std::to_string(playerNumber) + ".txt";
        file.open(fileName, std::ios::in );
        if(file)
        {
            std::string waste;
            while(!file.eof()) 	//find no of lines in file
            {
                getline(file, waste);
                fileDataSize++;
            }
            fileData = new std::string[fileDataSize];
            long dummy = 0;
            file.clear();  //clear pointer flags
                    file.seekg (0, std::ios::beg);  //rewind to starting position
            while(!file.eof()) 	//dublicate each line as array
            {
                getline(file, fileData[dummy++]);
            }
            fileDataSize--;	//get exact size
        }
        file.close();
    }
    workingNode = root;
    past = {};
    gamePlayByComputer();
}// end of startGame function

void MainWindow::gamePlayByComputer()
{
    while(1)
    {
        if(flag1) //computer turn
        {
            short c = 0, loc = 0;
            short arr[9];
            for(short i = 0; i < 9; i++)
            {
                arr[i] = workingNode -> a[i];
            }
            if(level == 2 || level == 1)	//ML, hard level
            {
                //win if two computer characters are near
                short k;
                for( k = 0; k < 8; k++)	//winnerLoactions[8][3]
                {
                    c = 0;
                    for(short j = 0; j < 3; j++)	//winnerLoactions[8][3]
                    {
                        short t = workingNode -> a[ winnerLoactions[k][j] ];
                        if(playerCharacter == 'O')
                        {
                            if(t == 0)
                               --c;
                        }
                        else
                        {
                            if(t == 10)
                               --c;
                        }
                        if(computerCharacter == 'O')
                        {
                            if(t == 0)
                               ++c;
                        }
                        else
                        {
                            if(t == 10)
                               ++c;
                        }
                        if(t > 0 && t < 10)
                           loc = t;
                    }
                    if(c == 2)
                       break;
                }
                if(c == 2)
                {
                    if(computerCharacter == 'O')
                        arr[loc-1] = O;
                    else
                        arr[loc-1] = X;
                    for(short i = 0; i < 9; i++)
                    {
                        workingNode -> a[i] = arr[i];
                    }
                    display(workingNode);
                    uI->statusbar->showMessage("computer won!");
                    repaint();
                    //fancy button colours
                    for(short j = 0; j < 3; j++)
                    {
                        if (winnerLoactions[k][j] == 0)
                            uI->pushButton_1->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 1)
                            uI->pushButton_2->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 2)
                            uI->pushButton_3->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 3)
                            uI->pushButton_4->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 4)
                            uI->pushButton_5->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 5)
                            uI->pushButton_6->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 6)
                            uI->pushButton_7->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 7)
                            uI->pushButton_8->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 8)
                            uI->pushButton_9->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        repaint();
                        QThread::msleep(300);   //sleep for 300ms
                    }
                    endGame = true;
                    break;
                }
            }
            if(level == 2 || level == 1 || level == 0)	//ML / hard level / moderate
            {
                //defend if player two characters are near to winning
                for(short k = 0; k < 8; k++)	//winnerLoactions[8][3]
                {
                   c = 0;
                   for(short j = 0; j < 3; j++)	//winnerLoactions[8][3]
                   {
                      short t = workingNode -> a[ winnerLoactions[k][j] ];
                      if(playerCharacter == 'O')
                      {
                         if(t == 0)
                            ++c;
                      }
                      else
                      {
                        if(t == 10)
                           ++c;
                      }
                      if(computerCharacter == 'O')
                      {
                          if(t == 0)
                             --c;
                      }
                      else
                      {
                         if(t == 10)
                            --c;
                      }
                      if(t > 0 && t < 10)
                         loc = t;
                    }
                    if(c == 2)
                       break;
                }
            }
            if(c == 2)
            {
                if(computerCharacter == 'O')
                   arr[loc-1] = O;
                else
                   arr[loc-1] = X;
                short count;
                for(short i = 0; i < 8; i++)
                {
                    if(workingNode->p[i] != nullptr)
                    {
                        count = 0;
                        for(short j = 0; j < 9; j++)
                        {
                            if( (workingNode->p[i])->a[j] == arr[j] )
                                count++;
                        }
                        if(count == 9)
                        {
                            workingNode = workingNode -> p[i];
                            past += std::to_string(i);
                            break;
                         }
                    }
                }
            }
            else
            {
                //BASED ON "COST OF NODE"
                short cost = 0, number = 0, negativeCost = -9999, negativeNumber = 0 ;
                short i;
                bool countFlag = false;
                for( i = 0; i < 8; i++)
                {
                    if(workingNode->p[i] != nullptr)
                    {
                        //MACHINE LEARNING FROM PAST EXPERIENCE
                        if(level == 2)
                        {
                            if(past.length() == 0)  //second level(after root)
                            {
                                for(long j = 0; j < fileDataSize; j++)
                                {
                                    if( fileData[j].substr(0,1) == std::to_string(i) )
                                        (workingNode -> p[i]) -> points -= 99;
                                }
                             }
                             else	//third - else level
                             {
                                for(long j = 0; j < fileDataSize; j++)
                                {
                                    if( fileData[j].substr(0,past.length()+1) == (past + std::to_string(i)) )
                                        (workingNode -> p[i]) -> points -= 99;
                                }
                             }
                        }
                        if(cost <= ((workingNode->p[i])->points))
                        {
                            cost = (workingNode->p[i])->points;
                            number = i;
                            countFlag = true;
                        }
                        if( ((workingNode->p[i])->points) < 0 && ((workingNode->p[i])->points) > negativeCost )
                        {
                            negativeCost = (workingNode->p[i])->points;
                            negativeNumber = i;
                        }
                    }
                    else
                      break;
                }
                if(!countFlag)  //if all points are negative
                   number = negativeNumber;
                workingNode = workingNode -> p[number];
                past += std::to_string(number);
            }
            display(workingNode);
            //check win or lose
            for(short k = 0; k < 8; k++)	//winnerLoactions[8][3]
            {
                c = 0;
                for(short j = 0; j < 3; j++)	//winnerLoactions[8][3]
                {
                    short t = workingNode -> a[ winnerLoactions[k][j] ];
                    if(computerCharacter == 'O')
                    {
                        if(t == 0)
                           ++c;
                    }
                    else
                    {
                        if(t == 10)
                           ++c;
                    }
                }
                if(c == 3)
                {
                    uI->statusbar->showMessage("computer won!");
                    repaint();
                    //fancy button colours
                    for(short j = 0; j < 3; j++)
                    {
                        if (winnerLoactions[k][j] == 0)
                            uI->pushButton_1->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 1)
                            uI->pushButton_2->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 2)
                            uI->pushButton_3->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 3)
                            uI->pushButton_4->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 4)
                            uI->pushButton_5->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 5)
                            uI->pushButton_6->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 6)
                            uI->pushButton_7->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 7)
                            uI->pushButton_8->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 8)
                            uI->pushButton_9->setStyleSheet("background-color: rgba(255, 0, 0, 0.3)");
                        repaint();
                        QThread::msleep(300);   //sleep for 300ms
                    }
                    break;
                }
            }
            if(c == 3)
            {
                endGame = true;
                  break;
            }
            if(workingNode->p[0] == nullptr)
            {
                uI->statusbar->showMessage("game draw!");
                repaint();
                endGame = true;
                break;
            }
            flag1 = !flag1;
            break;
        }
    }
    if(endGame)
    {
        uI->pushButton_1->setEnabled(true);
        uI->pushButton_2->setEnabled(true);
        uI->pushButton_3->setEnabled(true);
        uI->pushButton_4->setEnabled(true);
        uI->pushButton_5->setEnabled(true);
        uI->pushButton_6->setEnabled(true);
        uI->pushButton_7->setEnabled(true);
        uI->pushButton_8->setEnabled(true);
        uI->pushButton_9->setEnabled(true);
    }
}// end of startGame function

void MainWindow::gamePlayByPlayer()
{
    if(!gameStarted)
      startGame();
    else
    {
        while(1)
        {
            short arr[9];
            for(short i = 0; i < 9; i++)
            {
                arr[i] = workingNode -> a[i];
            }
            if(playerCharacter == 'O')
               arr[playerNumber-1] = O;
            else
               arr[playerNumber-1] = X;
            short i, count = 0;
            for( i = 0; i < 8; i++)
            {
                if(workingNode->p[i] != nullptr)
                {
                    count = 0;
                    for(short j = 0; j < 9; j++)
                    {
                        if( (workingNode->p[i])->a[j] == arr[j] )
                           count++;
                    }
                    if(count == 9)
                    {
                        workingNode = workingNode -> p[i];
                        past += std::to_string(i);
                        break;
                    }
                }
            }
            //check win or lose
            short c;
            for(short k = 0; k < 8; k++)	//winnerLoactions[8][3]
            {
                c = 0;
                for(short j = 0; j < 3; j++)	//winnerLoactions[8][3]
                {
                    short t = workingNode -> a[ winnerLoactions[k][j] ];
                    if(playerCharacter == 'O')
                    {
                        if(t == 0)
                          ++c;
                    }
                    else
                    {
                        if(t == 10)
                          ++c;
                    }
                }
                if(c == 3)
                {
                    if(level == 2)	//save pointer path's to file.
                    {
                        file.open(fileName, std::ios::out | std::ios::app ); //if file is past append or create.
                        if(file)
                          file << past << "\n";
                        file.close();
                    }
                    std::string dummy = playerName + " won!";
                    uI->statusbar->showMessage( &dummy[0] );   //playerName + " Won!"
                    repaint();
                    //fancy button colours
                    for(short j = 0; j < 3; j++)
                    {
                        if (winnerLoactions[k][j] == 0)
                            uI->pushButton_1->setStyleSheet("background-color: rgba(0, 255, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 1)
                            uI->pushButton_2->setStyleSheet("background-color: rgba(0, 255, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 2)
                            uI->pushButton_3->setStyleSheet("background-color: rgba(0, 255, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 3)
                            uI->pushButton_4->setStyleSheet("background-color: rgba(0, 255, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 4)
                            uI->pushButton_5->setStyleSheet("background-color: rgba(0, 255, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 5)
                            uI->pushButton_6->setStyleSheet("background-color: rgba(0, 255, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 6)
                            uI->pushButton_7->setStyleSheet("background-color: rgba(0, 255, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 7)
                            uI->pushButton_8->setStyleSheet("background-color: rgba(0, 255, 0, 0.3)");
                        else if(winnerLoactions[k][j] == 8)
                            uI->pushButton_9->setStyleSheet("background-color: rgba(0, 255, 0, 0.3)");
                        repaint();
                        QThread::msleep(300);
                    }
                    QMovie *movie = new QMovie(":/resources/images/confetti_popper.gif");   //player won gif
                    uI->label->setMovie(movie);
                    movie->start();
                    repaint();
                    break;
                }
            }
            if(c == 3)
            {
                endGame = true;
                break;
            }
            if(workingNode->p[0] == nullptr)
            {
                uI->statusbar->showMessage( "game draw!" );
                repaint();
                endGame = true;
                break;
            }
            flag1 = !flag1;
            break;
        }
        if(!endGame)
           gamePlayByComputer();
        else
        {
            uI->pushButton_1->setEnabled(true);
            uI->pushButton_2->setEnabled(true);
            uI->pushButton_3->setEnabled(true);
            uI->pushButton_4->setEnabled(true);
            uI->pushButton_5->setEnabled(true);
            uI->pushButton_6->setEnabled(true);
            uI->pushButton_7->setEnabled(true);
            uI->pushButton_8->setEnabled(true);
            uI->pushButton_9->setEnabled(true);
        }
    }
}//end of gamePlayByPlayer function

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    uI = ui;

    //PLAYER NAME
    bool ok;
    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton); //disable ? mark in QInputDialog
    do
    {
        playerName =  QInputDialog::getText(this,"TIC-TAC-TOE","ENTER YOUR NAME :",  QLineEdit::Normal, QString(), &ok).toStdString();
        if(!ok) //if cancel or closed
        {
            closeAll = true; //close all
            QApplication::quit(); //close present window
        }
        if(playerName.length() > 42)
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("NAME TOO LONG");
            msgBox.setText("NAME SHOULD NOT EXCEED <b>42</b> CHARACTERS!!!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
    } while(playerName.length() > 42);

    //PLAYABLE CHARACTER
    QStringList items;
    items << "X" << "O";
    QString item = QInputDialog::getItem(this,"TIC-TAC-TOE","PLAYABLE CHARACTER :", items, 0, false, &ok);    //false = no edit
    if(!ok)
    {
        closeAll = true;
        QApplication::quit();
    }
    if (item == "X")
    {
        playerCharacter = 'X';
        computerCharacter = 'O';
    }
    else
    {
        playerCharacter = 'O';
        computerCharacter = 'X';
    }

    //LEVEL (easy/moderate/hard/ML)
    items.clear();
    items << "Easy" << "Moderate" << "Hard" << "Machine Learning";
    item = QInputDialog::getItem(this,"TIC-TAC-TOE","GAME PLAY :", items, 0, false, &ok);    //false = no edit
    if(!ok)
    {
        closeAll = true;
        QApplication::quit();
    }
    if (item == "Easy")
        level = -1;
    else if (item == "Moderate")
        level = 0;
    else if (item == "Hard")
        level = 1;
    else
        level = 2;

    //background image
    ui->label->setPixmap( QPixmap(":/resources/images/Tic-tac-toe.png" ) );
    ui->label->setScaledContents( true );
    ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    //disable resize option for status bar
    this->statusBar()->setSizeGripEnabled(false);

    //make all buttons transparent
     ui->pushButton_1->setStyleSheet("QPushButton{background: transparent;}");
     ui->pushButton_2->setStyleSheet("QPushButton{background: transparent;}");
     ui->pushButton_3->setStyleSheet("QPushButton{background: transparent;}");
     ui->pushButton_4->setStyleSheet("QPushButton{background: transparent;}");
     ui->pushButton_5->setStyleSheet("QPushButton{background: transparent;}");
     ui->pushButton_6->setStyleSheet("QPushButton{background: transparent;}");
     ui->pushButton_7->setStyleSheet("QPushButton{background: transparent;}");
     ui->pushButton_8->setStyleSheet("QPushButton{background: transparent;}");
     ui->pushButton_9->setStyleSheet("QPushButton{background: transparent;}");
} // end of MainWindow constructor

MainWindow::~MainWindow()
{
    delete ui;
} // end of MainWindow destructor

//PLAY AGAIN
void MainWindow::playAgain()
{
    gameStarted = false;
    endGame = false;
    flag = false;
    flag1 = true;
    past = {};
    uI->pushButton_1->setEnabled(true);
    uI->pushButton_2->setEnabled(true);
    uI->pushButton_3->setEnabled(true);
    uI->pushButton_4->setEnabled(true);
    uI->pushButton_5->setEnabled(true);
    uI->pushButton_6->setEnabled(true);
    uI->pushButton_7->setEnabled(true);
    uI->pushButton_8->setEnabled(true);
    uI->pushButton_9->setEnabled(true);
    uI->pushButton_1->setIcon(QIcon());
    uI->pushButton_2->setIcon(QIcon());
    uI->pushButton_3->setIcon(QIcon());
    uI->pushButton_4->setIcon(QIcon());
    uI->pushButton_5->setIcon(QIcon());
    uI->pushButton_6->setIcon(QIcon());
    uI->pushButton_7->setIcon(QIcon());
    uI->pushButton_8->setIcon(QIcon());
    uI->pushButton_9->setIcon(QIcon());
    uI->pushButton_1->setStyleSheet("QPushButton{background: transparent;}");
    uI->pushButton_2->setStyleSheet("QPushButton{background: transparent;}");
    uI->pushButton_3->setStyleSheet("QPushButton{background: transparent;}");
    uI->pushButton_4->setStyleSheet("QPushButton{background: transparent;}");
    uI->pushButton_5->setStyleSheet("QPushButton{background: transparent;}");
    uI->pushButton_6->setStyleSheet("QPushButton{background: transparent;}");
    uI->pushButton_7->setStyleSheet("QPushButton{background: transparent;}");
    uI->pushButton_8->setStyleSheet("QPushButton{background: transparent;}");
    uI->pushButton_9->setStyleSheet("QPushButton{background: transparent;}");
    uI->label->setPixmap( QPixmap(":/resources/images/Tic-tac-toe.png" ) );
    uI->label->setScaledContents( true );
    uI->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    deleteFullTree(root);
    delete root;
    uI->statusbar->clearMessage();
    repaint();
}//end of playAgain function

//PLAY AGAIN MOUSE EVENT
void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if(endGame)
       if(ev->button() == Qt::LeftButton || ev->button() == Qt::RightButton)
          playAgain();
}

//BUTTONS ON CLICK ACTIONS
void MainWindow::on_pushButton_1_clicked()
{
    if(endGame)
      playAgain();
    else
    {
        ui->pushButton_1->setDisabled(true);
        playerNumber = 1;
        if(playerCharacter == 'X')
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/x.png"), QIcon::Disabled); //disabled button icon
            ui->pushButton_1->setIcon(ButtonIcon);
            ui->pushButton_1->setIconSize(QSize(40, 40));
        }
        else
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/o.png"), QIcon::Disabled);
            ui->pushButton_1->setIcon(ButtonIcon);
            ui->pushButton_1->setIconSize(QSize(40, 40));
        }
        repaint();
        gamePlayByPlayer();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(endGame)
      playAgain();
    else
    {
        ui->pushButton_2->setDisabled(true);
        playerNumber = 2;
        if(playerCharacter == 'X')
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/x.png"), QIcon::Disabled);
            ui->pushButton_2->setIcon(ButtonIcon);
            ui->pushButton_2->setIconSize(QSize(40, 40));
        }
        else
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/o.png"), QIcon::Disabled);
            ui->pushButton_2->setIcon(ButtonIcon);
            ui->pushButton_2->setIconSize(QSize(40, 40));
        }
        repaint();
        gamePlayByPlayer();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if(endGame)
      playAgain();
    else
    {
        ui->pushButton_3->setDisabled(true);
        playerNumber = 3;
        if(playerCharacter == 'X')
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/x.png"), QIcon::Disabled);
            ui->pushButton_3->setIcon(ButtonIcon);
            ui->pushButton_3->setIconSize(QSize(40, 40));
        }
        else
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/o.png"), QIcon::Disabled);
            ui->pushButton_3->setIcon(ButtonIcon);
            ui->pushButton_3->setIconSize(QSize(40, 40));
        }
        repaint();
        gamePlayByPlayer();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    if(endGame)
      playAgain();
    else
    {
        ui->pushButton_4->setDisabled(true);
        playerNumber = 4;
        if(playerCharacter == 'X')
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/x.png"), QIcon::Disabled);
            ui->pushButton_4->setIcon(ButtonIcon);
            ui->pushButton_4->setIconSize(QSize(40, 40));
        }
        else
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/o.png"), QIcon::Disabled);
            ui->pushButton_4->setIcon(ButtonIcon);
            ui->pushButton_4->setIconSize(QSize(40, 40));
        }
        repaint();
        gamePlayByPlayer();
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    if(endGame)
      playAgain();
    else
    {
        ui->pushButton_5->setDisabled(true);
        playerNumber = 5;
        if(playerCharacter == 'X')
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/x.png"), QIcon::Disabled);
            ui->pushButton_5->setIcon(ButtonIcon);
            ui->pushButton_5->setIconSize(QSize(40, 40));
        }
        else
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/o.png"), QIcon::Disabled);
            ui->pushButton_5->setIcon(ButtonIcon);
            ui->pushButton_5->setIconSize(QSize(40, 40));
        }
        repaint();
        gamePlayByPlayer();
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    if(endGame)
      playAgain();
    else
    {
        ui->pushButton_6->setDisabled(true);
        playerNumber = 6;
        if(playerCharacter == 'X')
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/x.png"), QIcon::Disabled);
            ui->pushButton_6->setIcon(ButtonIcon);
            ui->pushButton_6->setIconSize(QSize(40, 40));
        }
        else
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/o.png"), QIcon::Disabled);
            ui->pushButton_6->setIcon(ButtonIcon);
            ui->pushButton_6->setIconSize(QSize(40, 40));
        }
        repaint();
        gamePlayByPlayer();
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    if(endGame)
      playAgain();
    else
    {
        ui->pushButton_7->setDisabled(true);
        playerNumber = 7;
        if(playerCharacter == 'X')
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/x.png"), QIcon::Disabled);
            ui->pushButton_7->setIcon(ButtonIcon);
            ui->pushButton_7->setIconSize(QSize(40, 40));
        }
        else
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/o.png"), QIcon::Disabled);
            ui->pushButton_7->setIcon(ButtonIcon);
            ui->pushButton_7->setIconSize(QSize(40, 40));
        }
        repaint();
        gamePlayByPlayer();
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    if(endGame)
      playAgain();
    else
    {
        ui->pushButton_8->setDisabled(true);
        playerNumber = 8;
        if(playerCharacter == 'X')
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/x.png"), QIcon::Disabled);
            ui->pushButton_8->setIcon(ButtonIcon);
            ui->pushButton_8->setIconSize(QSize(40, 40));
        }
        else
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/o.png"), QIcon::Disabled);
            ui->pushButton_8->setIcon(ButtonIcon);
            ui->pushButton_8->setIconSize(QSize(40, 40));
        }
        repaint();
        gamePlayByPlayer();
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    if(endGame)
      playAgain();
    else
    {
        ui->pushButton_9->setDisabled(true);
        playerNumber = 9;
        if(playerCharacter == 'X')
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/x.png"), QIcon::Disabled);
            ui->pushButton_9->setIcon(ButtonIcon);
            ui->pushButton_9->setIconSize(QSize(40, 40));
        }
        else
        {
            QIcon ButtonIcon;
            ButtonIcon.addPixmap(QPixmap(":/resources/images/o.png"), QIcon::Disabled);
            ui->pushButton_9->setIcon(ButtonIcon);
            ui->pushButton_9->setIconSize(QSize(40, 40));
        }
        repaint();
        gamePlayByPlayer();
    }
}
