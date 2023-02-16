/****************************************************/
/*      FEH Software Development Project Code       */
/*              OSU FEH Autumn 2021                 */
/*                                                  */
/*          Steven Broaddus, David Szoke            */
/*                                                  */ 
/*         Appropriate credit is clarified          */
/*            above each part of code               */
/****************************************************/

#include "FEHLCD.h"
#include "FEHUtility.h"
#include <stdlib.h> // For exit() quit button
#include <FEHSD.h> // For reading/writing score data with SD card
#define LVLS 3 // defines LVLS as number of levels

// Define the amount of time for each level (in s)
#define LVL1TIME 30.0
#define LVL2TIME 25.0
#define LVL3TIME 20.0

// Defines the score time delay (how long the player has before their score starts to decrease)
#define SCOREDELAY 5.0

// Screen ID ints 
#define MAIN_MENU 0
#define LVL1SCREEN 1
#define LVL2SCREEN 2
#define LVL3SCREEN 3
#define STATS_SCREEN 4
#define INSTRUCTIONS_SCREEN 5
#define CREDITS_SCREEN 6
#define STATS_SCREEN2 7

// Defines the dimensions of the block
#define D1BLOCK 14


// Class Definitions

// Level 1 class (created by David, edited by Steven and David)
/*
    Purpose: has all game physics for  level 1
    Parameters: None
    Public Members:
        contructor
        void Play(); call to start level, will run until player wins or loses level
        bool BlockInBounds(); returns true if not touching wall, false if touching walls  
        bool BlockFinished(); returns true if block passed finish line, false otherwise
        void DisplayMaze(); displays map
        FEHIcon::Icon Block; creates a block that the user uses as their "player"
        bool Win; returns true if player finishes all levels
        float TimeComplete; stores the time it takes player to complete the level
        
    
    Private Members: 
        int BoundaryRects[4][4]; each row stores the x coord, y coord, width and height of a rectangle to be used with DrawRect();
        int FinishRect[4]; stores x coord, y coord, width and height OF FINISH LINE
        int BlockOrigin[2]; stores x coord, y coord OF BLOCK's origin (upper left corner)
        
*/

class LevelOne  {
    
    public:
    LevelOne(void);
    void Play();
    bool BlockInBounds();  
    bool BlockFinished(); 
    void DisplayMaze(); 
    FEHIcon::Icon Block;
    bool Win;
    float TimeComplete; 

    private: 
    int BoundaryRects[4][4];
    int FinishRect[4];
    int BlockOrigin[2];
    
    
}; 



// Level 2 Class (created by David, edited by Steven and David)
/*
    Purpose: has all game physics and data for  level 2
    Parameters: None
    Public Members:
        contructor
        void Play(); call to start level, will run until player wins or loses level
        bool BlockInBounds(); returns true if not touching wall, false if touching walls  
        bool BlockFinished(); returns true if block passed finish line, false otherwise
        void DisplayMaze(); displays map
        FEHIcon::Icon Block; creates a block that the user uses as their "player"
        bool Win; returns true if player finishes all levels
        float TimeComplete; stores the time it takes player to complete the level
        
    
    Private Members: 
        int BoundaryRects[4][4]; each row stores the x coord, y coord, width and height of a rectangle to be used with DrawRect();
        int FinishRect[4]; stores x coord, y coord, width and height OF FINISH LINE
        int BlockOrigin[2]; stores x coord, y coord OF BLOCK's origin (upper left corner)
        
*/

class LevelTwo  {
    
    public:
    LevelTwo(void);
    void Play();
    bool BlockInBounds();  
    bool BlockFinished(); 
    void DisplayMaze(); 
    FEHIcon::Icon Block;
    bool Win;
    float TimeComplete;


    private: 
    int BoundaryRects[8][4];
    int FinishRect[4];
    int BlockOrigin[2];
     
    
}; 


// Level 3 Class (created by David, edited by Steven and David)
/*
    Purpose: has all game physics and data for  level 3
    Parameters: None
    Public Members:
        contructor
        void Play(); call to start level, will run until player wins or loses level
        bool BlockInBounds(); returns true if not touching wall, false if touching walls  
        bool BlockFinished(); returns true if block passed finish line, false otherwise
        void DisplayMaze(); displays map
        FEHIcon::Icon Block; creates a block that the user uses as their "player"
        bool Win; returns true if player finishes all levels
        float TimeComplete; stores the time it takes player to complete the level
        
    
    Private Members: 
        int BoundaryRects[4][4]; each row stores the x coord, y coord, width and height of a rectangle to be used with DrawRect();
        int FinishRect[4]; stores x coord, y coord, width and height OF FINISH LINE
        int BlockOrigin[2]; stores x coord, y coord OF BLOCK's origin (upper left corner)
        
*/

class LevelThree    {       //(Created by David)
    public:
    LevelThree(void);
    void Play();
    bool BlockInBounds();  
    bool BlockFinished(); 
    void DisplayMaze(); 
    FEHIcon::Icon Block;
    float TimeComplete;
    bool Win;

    private: 
    int BoundaryRects[10][4];
    int FinishRect[4];
    int BlockOrigin[2]; 
}; 


// Player class (Created by David)
/*
    public members:
    constructor call
    void CalcSS(int level, float level_multiplier, float time); calculates subscores, subscore = multiplier*( (time limit-completion time) / time limit)
    void CalcS(); calculates scores using subscores[] as parameter and summing values of subscores[]
    LevelOne LvlOne; 
    LevelTwo LvlTwo;              --- All provide access for each player to play levels, and store their own data for the levels
    LevelThree LvlThree;
    int GetScore(); returns score (private member)
   

    private members: 
    int score: stores the score, calculated by CalcS() function
    float subscores[]: 1D array, size 3, stores subscore of level 1 in index 0, subscore level 2 in index 1...
    
*/

class Player {
    public:
    Player();
    void CalcSS(int level, float level_multiplier, float time);
    void CalcS();
    LevelOne LvlOne; 
    LevelTwo LvlTwo; 
    LevelThree LvlThree; 
    int GetScore();


    private:
    int score;
    float subscores[LVLS];
    
    

}; //end class Player



//Function Prototypes:
void DisplayMenu(FEHIcon::Icon menu_icons[]);   // Displays menu, created by David, edited by Steven 
void ButtonCheck(int *screen, int *x_coord, int *y_coord, FEHIcon::Icon menu_icons[], FEHIcon::Icon other_buttons[]);   // Checks which button has been clicked on menu or which back button has been clicked (created by Steven)
void DrawStatsScreen(FEHIcon::Icon other_buttons[]);    //Draws statistics screen for 1 player game(Created by Steven)
void DrawStatsScreen2(FEHIcon::Icon other_buttons[]);   //Draws statistics screen for 2 player game (created by Steven)
void DrawInstructionsScreen(FEHIcon::Icon other_buttons[]); //Draws instructions screen (created by Steven)
void DrawCreditsScreen(FEHIcon::Icon other_buttons[]);  // Draws credits screen (created by Steven)
void Play1P(Player P1); //gameplay for 1 player game, takes 1 Player object as parameter (created by David, edited by Steven and David)
void Play2P(Player P1, Player P2); //gameplay for 2 player game, takes 2 Player objects as parameters (created by David, edited by Steven and David)
void Display1PStats(bool playerWin, int playerscore); //displays Win or lose (boolean playerWin) and player score (playerscore) for 1 player game (created by David)
void Display2PStats(bool player1Win, int player1score, bool player2Win, int player2score); // displays which player wins (based off player scores) and which players beat the game for 2 player game (created by David)
void BlockMove(int *x_coord, int *y_coord, int *BlockOriginx, int *BlockOriginy, FEHIcon::Icon Block); //Redraws the block at the new coordinates with a defined size (created by David and Steven)
void BlockGravity(int *BlockOriginx, int *BlockOriginy, FEHIcon::Icon *Block, float time_gravity); //Redraws the block lower at increasing speed (created by Steven)
void P1Transition(); //displays P1 to the screen, waits, then a counting down screen, for use in multiplayer and single player between levels (Created by David)
void P2Transition(); //displays P2 to the screen, waits, then a counting down screen, for use in multiplayer between levels (Created by David)
void SaveScores(int playerscore, int flag); //calculates if the player's scores make it to leaderboards. Prints to SD card if yes. (created by Steven)


// Enter program here
int main() {    // Created by Steven

    int x_coord, y_coord;
    
    //Defines the screen the player is currently on.
    int screen = MAIN_MENU;

     // Declares array of 6 icons called menu_icons
    FEHIcon::Icon menu_icons[6];

    // Declares an array of other icons used throughout the game
    FEHIcon::Icon other_buttons[2];
    
    char back_button_label[] = "BACK"; // Prevents warning from popping up
    other_buttons[0].SetProperties(back_button_label, 10, 200, 75, 30, GRAY, BLACK);
    other_buttons[1].SetProperties("2P Stats", 180, 200, 125, 30, GRAY, BLACK);

    // Calls DisplayMenu() to display the menu to the screen
    DisplayMenu(menu_icons);


    // ****************************************************
    // Constantly checking

    while (1) {
        LCD.Update();

        // Checks if each of the menu buttons are pressed using ButtonCheck()
        if ((screen == MAIN_MENU) || (screen == STATS_SCREEN)  || (screen == STATS_SCREEN2) || (screen == INSTRUCTIONS_SCREEN) || (screen == CREDITS_SCREEN) || (screen  == LVL1SCREEN)){
            LCD.Touch(&x_coord, &y_coord);
            ButtonCheck(&screen, &x_coord, &y_coord, menu_icons, other_buttons);
        }
        
    }
    return 0;
}


// ****************************************************

// Displays the menu and all the buttons (Created by David, edited by Steven)
void DisplayMenu(FEHIcon::Icon menu_icons[]){

    // Declare and initialize array of strings (menu_labels) storing string values for each menu icon 
    char menu_labels[6][20] = {{"1 Player"}, {"2 Player"}, {"Stats"}, {"Instructions"}, {"Credits"}, {"Quit"}};

    // Sets the screen to black
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    // Write game title to top center of screen
    LCD.SetFontColor(RED);
    LCD.WriteAt("FEH MAZE GAME", 82, 30);

    // Draws menu icons
    FEHIcon :: DrawIconArray(menu_icons, 3, 2, 80, 5, 5, 5, menu_labels, CYAN, RED);
    
    LCD.Update();

}//End DisplayMenu()

// ****************************************************

// Checks if each of the menu buttons have been pressed (Created by Steven)
// 0 for title screen, 1 for level 1, 2 for level 2, and 3 for level 3
// 4 for Stats screen, 5 for Instructions, and 6 for Credits
void ButtonCheck(int *screen, int *x_coord, int *y_coord, FEHIcon::Icon menu_icons[], FEHIcon::Icon other_buttons[]){

    // *************
    // Buttons for main menu screen
    if (*screen == MAIN_MENU){
        // Highlights and unhighlights buttons when hovered over
        // menu_icon[0]
        if (menu_icons[0].Pressed(*x_coord, *y_coord, 0))
            menu_icons[0].Select();
        else
            menu_icons[0].Deselect();

        // menu_icon[1]
        if (menu_icons[1].Pressed(*x_coord, *y_coord, 0))
            menu_icons[1].Select();
        else
            menu_icons[1].Deselect();

        // menu_icon[2]
        if (menu_icons[2].Pressed(*x_coord, *y_coord, 0))
            menu_icons[2].Select();
        else
            menu_icons[2].Deselect();

        // menu_icon[3]
        if (menu_icons[3].Pressed(*x_coord, *y_coord, 0))
            menu_icons[3].Select();
        else
            menu_icons[3].Deselect();

        // menu_icon[4]
        if (menu_icons[4].Pressed(*x_coord, *y_coord, 0))
            menu_icons[4].Select();
        else
            menu_icons[4].Deselect();

        // menu_icon[5]
        if (menu_icons[5].Pressed(*x_coord, *y_coord, 0))
            menu_icons[5].Select();
        else
            menu_icons[5].Deselect();

        // Does something for each button when pressed
        while(LCD.Touch(x_coord, y_coord)){
            if (menu_icons[0].Pressed(*x_coord, *y_coord, 0)){
                static Player P1;
                Play1P(P1);
                LCD.Clear();
                DisplayMenu(menu_icons);
                Sleep(0.5);
                LCD.ClearBuffer();
                *screen = MAIN_MENU;
                
            }
            if (menu_icons[1].Pressed(*x_coord, *y_coord, 0)){
                //PLACEHOLDER
                LCD.Clear();
                static Player P1; 
                static Player P2;
                Play2P(P1, P2);
                DisplayMenu(menu_icons);
                Sleep(0.5);
                LCD.ClearBuffer();
                *screen = MAIN_MENU;
            }
            if (menu_icons[2].Pressed(*x_coord, *y_coord, 0)){
                DrawStatsScreen(other_buttons);
                *screen = STATS_SCREEN;
            }
            if (menu_icons[3].Pressed(*x_coord, *y_coord, 0)){
                DrawInstructionsScreen(other_buttons);
                *screen = INSTRUCTIONS_SCREEN;
            }
            if (menu_icons[4].Pressed(*x_coord, *y_coord, 0)){
                DrawCreditsScreen(other_buttons);
                *screen = CREDITS_SCREEN;
            }
            if (menu_icons[5].Pressed(*x_coord, *y_coord, 0)){
                exit(0);
            }
        }
    }// End MAIN_MENU Buttons

    // *************
    // Stats2 screen buttons
    
    
    // End STATS_SCREEN Buttons

    // *************
    // Back button detecting
    if ((*screen == STATS_SCREEN) || (*screen == INSTRUCTIONS_SCREEN) || (*screen == CREDITS_SCREEN) || (*screen == STATS_SCREEN2)){
        if ((*screen == INSTRUCTIONS_SCREEN) || (*screen == CREDITS_SCREEN)){
            if (other_buttons[0].Pressed(*x_coord, *y_coord, 0))
                other_buttons[0].Select();
            else
                other_buttons[0].Deselect();
            while(LCD.Touch(x_coord, y_coord)){
                if (other_buttons[0].Pressed(*x_coord, *y_coord, 0)){
                    DisplayMenu(menu_icons);
                    *screen = MAIN_MENU;
                }
            }
        }
        if (*screen == STATS_SCREEN){
            if (other_buttons[1].Pressed(*x_coord, *y_coord, 0))
                other_buttons[1].Select();
            else
                other_buttons[1].Deselect();
            if (other_buttons[0].Pressed(*x_coord, *y_coord, 0))
                other_buttons[0].Select();
            else
                other_buttons[0].Deselect();
            while(LCD.Touch(x_coord, y_coord)){
                if (other_buttons[1].Pressed(*x_coord, *y_coord, 0)){
                    DrawStatsScreen2(other_buttons);
                    *screen = STATS_SCREEN2;
                }
                if (other_buttons[0].Pressed(*x_coord, *y_coord, 0)){
                    DisplayMenu(menu_icons);
                    *screen = MAIN_MENU;
                    DisplayMenu(menu_icons);
                }
            }
            
        }
        if (*screen == STATS_SCREEN2){
            if (other_buttons[0].Pressed(*x_coord, *y_coord, 0))
                other_buttons[0].Select();
            else
                other_buttons[0].Deselect();
            while (LCD.Touch(x_coord, y_coord)){
                if (other_buttons[0].Pressed(*x_coord, *y_coord, 0)){
                    DrawStatsScreen(other_buttons);
                    *screen = STATS_SCREEN;
                }
            }
        }
    }// End back button detecting

}//End ButtonCheck()

// ****************************************************
// Draws the Stats screen (Created by Steven)
void DrawStatsScreen(FEHIcon::Icon other_buttons[]){ 
    
    int OnePlayer1PScores[3];
    int TwoPlayer1PScores[3];
    int TwoPlayer2PScores[3];
    int check = 0;

    // Opens the scores file for reading in one stream (fptrR)
    FEHFile *fptrR = SD.FOpen("Scores.txt", "r");

    // If reading file doesn't open, create and print initial values to file with new stream (fptrW)
    if (!fptrR){   //fptrR returns True if exists, False if doesn't
        SD.FClose(fptrR);
        FEHFile *fptrW = SD.FOpen("Scores.txt", "w");
        
        SD.FPrintf(fptrW, "%d %d %d", 0, 0, 0);
        SD.FPrintf(fptrW, " %d %d %d", 0, 0, 0);
        SD.FPrintf(fptrW, " %d %d %d", 0, 0, 0);
        
        SD.FClose(fptrW);
    }
    else {

        check += SD.FScanf(fptrR, "%d%d%d%d%d%d%d%d%d", &OnePlayer1PScores[0], &OnePlayer1PScores[1], &OnePlayer1PScores[2], &TwoPlayer1PScores[0], &TwoPlayer1PScores[1], &TwoPlayer1PScores[2], &TwoPlayer2PScores[0], &TwoPlayer2PScores[1], &TwoPlayer2PScores[2]);
        SD.FClose(fptrR);

        // If it doesn't read the proper amount of data from SD card, resets data
        if (check != 9){
            
            FEHFile *fptrW = SD.FOpen("Scores.txt", "w");
            
            SD.FPrintf(fptrW, "%d %d %d", 0, 0, 0);
            SD.FPrintf(fptrW, " %d %d %d", 0, 0, 0);
            SD.FPrintf(fptrW, " %d %d %d", 0, 0, 0);
            
            SD.FClose(fptrW);
        }
    }
    
    // Clears screen, adds back and 2P stats buttons
    LCD.Clear(DARKGRAY);
    other_buttons[0].Draw();
    other_buttons[1].Draw();

    // Writes top 6 1P game statistics
    LCD.WriteAt("Statistics", 94, 20);
    LCD.DrawLine(75,45,235,45);
    LCD.WriteAt("Single Player:", 75, 56);
    LCD.WriteAt("1)", 120, 85);
    LCD.WriteAt(OnePlayer1PScores[2], 150, 85);
    LCD.WriteAt("2)", 120, 105);
    LCD.WriteAt(OnePlayer1PScores[1], 150, 105);
    LCD.WriteAt("3)", 120, 125);
    LCD.WriteAt(OnePlayer1PScores[0], 150, 125);

    LCD.Update();

}//End DrawStatsScreen()

// ****************************************************
// Draws the second Stats screen    (Created by Steven)
void DrawStatsScreen2(FEHIcon::Icon other_buttons[]){
    
    int OnePlayer1PScores[3];
    int TwoPlayer1PScores[3];
    int TwoPlayer2PScores[3];
    int check = 0;

    // Opens the scores file for reading in one stream (fptrR)
    FEHFile *fptrR = SD.FOpen("Scores.txt", "r");

    // If reading file doesn't open, create and print initial values to file with new stream (fptrW)
    if (!fptrR){   //fptrR returns True if exists, False if doesn't
        SD.FClose(fptrR);
        FEHFile *fptrW = SD.FOpen("Scores.txt", "w");
        
        SD.FPrintf(fptrW, "%d %d %d", 0, 0, 0);
        SD.FPrintf(fptrW, " %d %d %d", 0, 0, 0);
        SD.FPrintf(fptrW, " %d %d %d", 0, 0, 0);
        
        SD.FClose(fptrW);
    }
    else {

        check += SD.FScanf(fptrR, "%d%d%d%d%d%d%d%d%d", &OnePlayer1PScores[0], &OnePlayer1PScores[1], &OnePlayer1PScores[2], &TwoPlayer1PScores[0], &TwoPlayer1PScores[1], &TwoPlayer1PScores[2], &TwoPlayer2PScores[0], &TwoPlayer2PScores[1], &TwoPlayer2PScores[2]);
        SD.FClose(fptrR);

        // If it doesn't read the proper amount of data from SD card, resets data
        if (check != 9){
            
            FEHFile *fptrW = SD.FOpen("Scores.txt", "w");
            
            SD.FPrintf(fptrW, "%d %d %d", 0, 0, 0);
            SD.FPrintf(fptrW, " %d %d %d", 0, 0, 0);
            SD.FPrintf(fptrW, " %d %d %d", 0, 0, 0);
            
            SD.FClose(fptrW);
        }
    }
    
    
    LCD.Clear(DARKGRAY);
    other_buttons[0].Draw();
    LCD.WriteAt("Statistics", 94, 20);
    LCD.DrawLine(75,45,235,45);
    LCD.WriteAt("Two Player:", 95, 56);
    LCD.WriteAt("P1:", 55, 80);
    LCD.WriteAt("1)", 80, 105);
    LCD.WriteAt(TwoPlayer1PScores[2], 110, 105);
    LCD.WriteAt("2)", 80, 125);
    LCD.WriteAt(TwoPlayer1PScores[1], 110, 125);
    LCD.WriteAt("3)", 80, 145);
    LCD.WriteAt(TwoPlayer1PScores[0], 110, 145);

    LCD.WriteAt("P2:", 185, 80);
    LCD.WriteAt("1)", 210, 105);
    LCD.WriteAt(TwoPlayer2PScores[2], 240, 105);
    LCD.WriteAt("2)", 210, 125);
    LCD.WriteAt(TwoPlayer2PScores[1], 240, 125);
    LCD.WriteAt("3)", 210, 145);
    LCD.WriteAt(TwoPlayer2PScores[0], 240, 145);

    LCD.Update();

}//End DrawStatsScreen2()

// ****************************************************
// Draws the Instructions screen
void DrawInstructionsScreen(FEHIcon::Icon other_buttons[]){ // Created by Steven
    LCD.Clear(DARKGRAY);
    
    // Draws back button
    other_buttons[0].Draw();

    // Prints instructions to the screen
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Instructions", 82, 20);
    LCD.DrawLine(75,45,235,45);
    LCD.WriteAt("GOAL: Drag the block to", 10, 60);
    LCD.WriteAt("the finish line. ", 10, 80);
    LCD.WriteAt("Points are awarded based ", 10, 110);
    LCD.WriteAt("on time.", 10, 130);
    LCD.WriteAt("DON'T TOUCH THE WALLS. ", 10, 160);
    LCD.WriteAt("Touching the walls RESETS", 10, 180);
    LCD.WriteAt("THE GAME", 215, 200);

    LCD.Update();

}//End DrawInstructionsScreen()

// ****************************************************
// Draws the Credits screen     (Created by Steven)
void DrawCreditsScreen(FEHIcon::Icon other_buttons[]){

    // Clears screen and draws back button
    LCD.Clear(DARKGRAY);
    other_buttons[0].Draw();

    // Prints credits header, developers and external resources
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Credits", 108, 20);
    LCD.DrawLine(75,45,235,45);

    LCD.WriteAt("Developers:", 95, 60);
    LCD.WriteAt("David Szoke", 90, 90);
    LCD.WriteAt("Steven Broaddus", 65, 110);

    LCD.Update();

}//End DrawInstructionsScreen()

// ****************************************************
// Calculates if player scores get saved to SD card or not      (Created by Steven)
// second argument is flag to determine what score is being calculated
// 0 -> single player 1p score
// 1 -> two player 1p score
// 2 -> two player 1p score
void SaveScores(int playerscore, int flag){
    
// Opens the scores file for reading in one stream (fptrR)
FEHFile *fptrR = SD.FOpen("Scores.txt", "r");

// If reading file doesn't open, create and print initial values to file with new stream (fptrW)
if (!fptrR){   //fptrR returns True if exists, False if doesn't
    SD.FClose(fptrR);
    FEHFile *fptrW = SD.FOpen("Scores.txt", "w");
    
    SD.FPrintf(fptrW, "%d %d %d", 0, 0, playerscore);
    SD.FPrintf(fptrW, " %d %d %d", 0, 0, 0);
    SD.FPrintf(fptrW, " %d %d %d", 0, 0, 0);
    
    SD.FClose(fptrW);
}

else {
    
    int OnePlayer1PScores[3];
    int TwoPlayer1PScores[3];
    int TwoPlayer2PScores[3];
    int check = 0;
    
    
    check += SD.FScanf(fptrR, "%d%d%d%d%d%d%d%d%d", &OnePlayer1PScores[0], &OnePlayer1PScores[1], &OnePlayer1PScores[2], &TwoPlayer1PScores[0], &TwoPlayer1PScores[1], &TwoPlayer1PScores[2], &TwoPlayer2PScores[0], &TwoPlayer2PScores[1], &TwoPlayer2PScores[2]);
    SD.FClose(fptrR);

    // If it doesn't read the proper amount of data from SD card, resets data
    if (check != 9){
        
        FEHFile *fptrW = SD.FOpen("Scores.txt", "w");
        
        SD.FPrintf(fptrW, "%d %d %d", 0, 0, playerscore);
        SD.FPrintf(fptrW, " %d %d %d", 0, 0, 0);
        SD.FPrintf(fptrW, " %d %d %d", 0, 0, 0);
        
        SD.FClose(fptrW);
    }
    //Else, print new scores to SD card
    else {

    //Calculates one player p1 scores if flag == 0
    if  (flag == 0){
        if (playerscore > OnePlayer1PScores[0]){
            if (playerscore > OnePlayer1PScores[1]){
                if (playerscore > OnePlayer1PScores[2]){
                    OnePlayer1PScores[0] = OnePlayer1PScores[1];
                    OnePlayer1PScores[1] = OnePlayer1PScores[2];
                    OnePlayer1PScores[2] = playerscore;
                }
                else {
                    OnePlayer1PScores[0] = OnePlayer1PScores[1];
                    OnePlayer1PScores[1] = playerscore;
                }
            }
            else {
                OnePlayer1PScores[0] = playerscore;
            }
        }
    } //End one player p1 calcs

    //Calculates two player p1 scores if flag == 1
    if  (flag == 1){
        if (playerscore > TwoPlayer1PScores[0]){
            if (playerscore > TwoPlayer1PScores[1]){
                if (playerscore > TwoPlayer1PScores[2]){
                    TwoPlayer1PScores[0] = TwoPlayer1PScores[1];
                    TwoPlayer1PScores[1] = TwoPlayer1PScores[2];
                    TwoPlayer1PScores[2] = playerscore;
                }
                else {
                    TwoPlayer1PScores[0] = TwoPlayer1PScores[1];
                    TwoPlayer1PScores[1] = playerscore;
                }
            }
            else {
                TwoPlayer1PScores[0] = playerscore;
            }
        }
    } //End two player p1 calcs

    //Calculates two player p2 scores if flag == 2
    if  (flag == 2){
        if (playerscore > TwoPlayer2PScores[0]){
            if (playerscore > TwoPlayer2PScores[1]){
                if (playerscore > TwoPlayer2PScores[2]){
                    TwoPlayer2PScores[0] = TwoPlayer2PScores[1];
                    TwoPlayer2PScores[1] = TwoPlayer2PScores[2];
                    TwoPlayer2PScores[2] = playerscore;
                }
                else {
                    TwoPlayer2PScores[0] = TwoPlayer2PScores[1];
                    TwoPlayer2PScores[1] = playerscore;
                }
            }
            else {
                TwoPlayer2PScores[0] = playerscore;
            }
        }
    } //End two player p2 calcs


        FEHFile *fptrW = SD.FOpen("Scores.txt", "w");

        
        SD.FPrintf(fptrW, "%d %d %d", OnePlayer1PScores[0], OnePlayer1PScores[1], OnePlayer1PScores[2]);
        SD.FPrintf(fptrW, " %d %d %d", TwoPlayer1PScores[0], TwoPlayer1PScores[1], TwoPlayer1PScores[2]);
        SD.FPrintf(fptrW, " %d %d %d", TwoPlayer2PScores[0], TwoPlayer2PScores[1], TwoPlayer2PScores[2]);
        

        SD.FClose(fptrW);
    }
}

}//End SaveScores()


// ****************************************************
// Displays results of one player game, 
void Display1PStats(bool playerWin, int playerscore) {  //Created by David, edited by Steven and David

    LCD.Clear(GRAY);
    
    // Print YOU WIN and score if player won game
    if (playerWin)    {
        LCD.SetFontColor(GOLD);
        LCD.WriteAt("YOU WIN", 118, 100);
        LCD.WriteAt("SCORE: ", 100, 135);
        LCD.WriteAt(playerscore, 198, 135);
    }
    
    // else Print YOU LOSE and score
    else    {
        LCD.SetFontColor(RED);
        LCD.WriteAt("YOU LOSE", 112, 100);
        LCD.WriteAt("SCORE: ", 100, 135);
        LCD.WriteAt(playerscore, 198, 135);
    }
    
    // calls SaveScores to determine if scores get saved to SD card
    // second argument is flag to determine what score is being calculated
    // 0 -> single player 1p score
    // 1 -> two player 1p score
    // 2 -> two player 1p score
    SaveScores(playerscore, 0);
    
    // Print messages to screen 
    LCD.Update();
    
    // Wait 1s, then prints click anywhere to continue
    Sleep(1.0);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Click anywhere to continue", 7, 200);
    LCD.Update();

    // wait for touch to exit function
    // x and y are throw-away ints
    int x, y;
    while (!LCD.Touch(&x, &y)) {}
}// End Display1PStats()

// ****************************************************
// Display2PStats
// Decides which player wins, and which beat the game, along with scores
void Display2PStats(bool player1Win, int player1score, bool player2Win, int player2score)   {   //Created by David
        
    // screen setup
    LCD.Clear(GRAY);

    // Print PLAYER X beat the game if a player beat the game
    LCD.SetFontColor(GOLD);

    if (player1Win) {
        LCD.WriteAt("PLAYER 1 BEAT THE GAME", 28, 40);
    }

    else if (player2Win) {
        LCD.WriteAt("PLAYER 2 BEAT THE GAME", 28, 40);
    }

    if (player1Win && player2Win) {
        LCD.WriteAt("PLAYER 1 & 2 BEAT THE GAME", 4, 40);
    }

    // Determine and print winner
    // Print scores with corresponding colors to indicate victory, loss or draw

    if (player1score == player2score)   {
        LCD.SetFontColor(BLUE);
        LCD.WriteAt("DRAW", 136, 100);
        LCD.WriteAt(player1score, 214, 155);
        LCD.WriteAt(player2score, 214, 175);
    }

    else if (player1score > player2score)    {
        LCD.SetFontColor(GREEN); 
        LCD.WriteAt("Player 1 Wins!", 76, 100);
        LCD.WriteAt(player1score, 214, 155);
        LCD.SetFontColor(RED);
        LCD.WriteAt(player2score, 214, 175);
    }

    else    {
        LCD.SetFontColor(GREEN); 
        LCD.WriteAt("Player 2 Wins!", 76, 100);
        LCD.WriteAt(player2score, 214, 175);
        LCD.SetFontColor(RED);
        LCD.WriteAt(player1score, 214, 155);
    }

    // Print Scores layout for both players
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Scores:",  118, 130);
    LCD.WriteAt("Player 1 :: ", 70, 155);
    LCD.WriteAt("Player 2 :: ", 70, 175);

    // Update screen and wait for exit
    LCD.Update();

    SaveScores(player1score, 1);
    SaveScores(player2score, 2);
    
    // Wait 1s, then prints click anywhere to continue
    Sleep(1.0);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Click anywhere to continue", 7, 210);
    LCD.Update();

    // wait for touch to exit function
    // x and y are throw-away ints
    int x, y;
    while (!LCD.Touch(&x, &y)) {}
}   //End Display2PStats()


// ****************************************************
// Block Move 
// Redraws block where cursor moves
void BlockMove(int *x_coord, int *y_coord, int *BlockOriginx, int *BlockOriginy, FEHIcon::Icon Block){

    LCD.SetFontColor(CYAN);
    LCD.FillRectangle(*BlockOriginx, *BlockOriginy, D1BLOCK, D1BLOCK);

    LCD.SetFontColor(RED);
    *BlockOriginx = *x_coord-(D1BLOCK/2);
    *BlockOriginy = *y_coord-(D1BLOCK/2);
    Block.SetProperties("", *BlockOriginx, *BlockOriginy, D1BLOCK, D1BLOCK, RED, RED); 
    Block.Draw();
    LCD.FillRectangle(*BlockOriginx, *BlockOriginy, D1BLOCK, D1BLOCK);

}

// ****************************************************
// Block Gravity    (Created by David, edited by Steven and David)
// Redraws block some pixels lower then sleeps for some time 
// Parameters are all pointers to previous block origin cooordinates, the block icon, and the time since the block started falling

void BlockGravity(int *BlockOriginx, int *BlockOriginy, FEHIcon::Icon *Block, float time_gravity){
    
    // Fills previous Block location with background color
    LCD.SetFontColor(CYAN);
    LCD.FillRectangle(*BlockOriginx, *BlockOriginy, D1BLOCK, D1BLOCK);

    // Redraws the block with the affected position based on the rate of change of gravity
    LCD.SetFontColor(RED);
    *BlockOriginy = *BlockOriginy+time_gravity;
    Block->SetProperties("", *BlockOriginx, *BlockOriginy, D1BLOCK, D1BLOCK, RED, RED); 
    Block->Draw();
    LCD.FillRectangle(*BlockOriginx, *BlockOriginy, D1BLOCK, D1BLOCK);
}//End BlockGravity()

// ****************************************************
// void CalcSS() member function definition (player class)      (Created by David)
//parameters: level describes which level to enter subscore 
//            level_multiplier is self descriptive
//            time is the amount of time spent on the level

void Player :: CalcSS(int level, float level_multiplier, float time)   { 
  
   // Determines which level to enter subscore for (level 1 = 0, level 2 = 1 ...), then calculates subscore
    switch (level - 1)  {
        case 0:
            subscores[0] = level_multiplier*((LVL1TIME-time+SCOREDELAY)/LVL1TIME);
        break; 

         case 1:
            subscores[1] = level_multiplier*((LVL2TIME-time+SCOREDELAY)/LVL2TIME);
        break;

        case 2:
            subscores[2] = level_multiplier*((LVL3TIME-time+SCOREDELAY)/LVL3TIME);
        break;
    }
}
// ******************************************************
// void CalcS() member function of class player (Created by David) 
// Purpose: sets player.score to the players score
// 

void Player :: CalcS() { 
    for (int n = 0; n < LVLS; n++) {
        score += subscores[n];
    }

    // Applies bonus for finishing all levels
    if (LvlThree.Win){
        score += 200;
    }
    
}

// ****************************************************
// GetScore function in PLAYER class (Created by David)
// returns score value 

int Player :: GetScore()   {
    return score;
}

// ****************************************************
// P1Transition (Created by David)
// Provides transition screen between levels for player 1

void P1Transition() {
    // Aesthetics setup
    LCD.Clear(BLACK);
    LCD.SetFontColor(RED);

    // print P1 to the screen
    LCD.WriteAt("Player 1", 112, 100);
    LCD.Update();

    // Waits 1s
    Sleep(1.0);

    // Warns player not to be clicking screen 
    LCD.WriteAt("(Don't Click)", 82, 140);
    LCD.Update();

    Sleep(.5);
    
    // Countdown initiates
    LCD.Clear();
    LCD.WriteAt("3", 154, 111);
    LCD.Update();

    Sleep(.75);

    LCD.Clear();
    LCD.WriteAt("2", 154, 111);
    LCD.Update();

    Sleep(.75);

    LCD.Clear();
    LCD.WriteAt("1", 154, 111);
    LCD.Update();

    Sleep(.25);

}//End P1Transition

// **************************************************
// P2Tranistion function (Created by David)
// provides transition buffer for player 2 in multiplayer game

void P2Transition() {
    // Aesthetics setup
    LCD.Clear(BLACK);
    LCD.SetFontColor(RED);

    // print P1 to the screen
    LCD.WriteAt("Player 2", 112, 100);
    LCD.Update();

    // Waits 1s
    Sleep(1.0);

    // Warns player
    LCD.WriteAt("(Don't Click)", 82, 140);
    LCD.Update();

    Sleep(.5);
    
    // Countdown
    LCD.Clear();
    LCD.WriteAt("3", 154, 111);
    LCD.Update();

    Sleep(.75);

    LCD.Clear();
    LCD.WriteAt("2", 154, 111);
    LCD.Update();

    Sleep(.75);

    LCD.Clear();
    LCD.WriteAt("1", 154, 111);
    LCD.Update();

    Sleep(.25);
}//end P2Transiti()


// ****************************************************
// Single player playing function. This calls all of the 
// level functions that create and set up the levels
// Parameters: A player object
// Created by David

void Play1P(Player P1){ 
    P1Transition(); 
    P1.LvlOne.Play();
    if (P1.LvlOne.Win){
        P1.CalcSS(1, 100, P1.LvlOne.TimeComplete);
        P1.CalcS();
        P1Transition();
        P1.LvlTwo.Play();
        if (P1.LvlTwo.Win) {
            P1.CalcSS(2, 300, P1.LvlTwo.TimeComplete);
            P1.CalcS();
            P1Transition();
            P1.LvlThree.Play();
            if (P1.LvlThree.Win)    {
                P1.CalcSS(3, 400, P1.LvlThree.TimeComplete); 
                P1.CalcS();
            }
                   
        }
    }    
    Display1PStats(P1.LvlThree.Win, P1.GetScore()); 
}//End Play1P()

// *****************************************************
// Two player playing function, this provides the structure for determining which 
// player is next, and determining which player beats the other
// Parameters: 2 player objects
// Created by David
void Play2P(Player P1, Player P2)   {
    
    // Lets P1 play level 1 first, then lets P2 play level 1. Then, if players finish levels, they can move on to next level, 
    // if both players move on, they continue to alternate
    
    P1Transition();
    P1.LvlOne.Play();
    P2Transition();
    P2.LvlOne.Play();
    if (P1.LvlOne.Win)  {
        P1Transition();
        P1.LvlTwo.Play();
        P1.CalcSS(1, 100, P1.LvlOne.TimeComplete);
        P1.CalcS();
    }
    if (P2.LvlOne.Win)  {
        P2Transition();
        P2.LvlTwo.Play();
        P2.CalcSS(1, 100, P2.LvlOne.TimeComplete);
        P2.CalcS();
    }
    if (P1.LvlTwo.Win)  {
        P1Transition();
        P1.LvlThree.Play();
        P1.CalcSS(2, 300, P1.LvlTwo.TimeComplete);
        P1.CalcS();
    }
    if (P2.LvlTwo.Win)  {
        P2Transition();
        P2.LvlThree.Play();
        P2.CalcSS(2, 300, P2.LvlTwo.TimeComplete);
        P2.CalcS();
    }
    if (P1.LvlThree.Win)  {
        P1.CalcSS(3, 400, P1.LvlThree.TimeComplete);
        P1.CalcS();
    }
    if (P2.LvlThree.Win)    {
        P2.CalcSS(3, 400,  P2.LvlThree.TimeComplete);
        P2.CalcS();
    }

    // Determine who won, and print screens accordingly 
    Display2PStats(P1.LvlThree.Win, P1.GetScore(), P2.LvlThree.Win, P2.GetScore());
}//End Play2P
// ****************************************************




//              LevelOne Member Functions
// ****************************************************

// Play function for level 1
// See flow chart for visualization: https://u.osu.edu/fehsdp2021bcm0800g1/project-planning/
// Parameters: None
// Created by David, edited by Steven and David
void LevelOne::Play()   {
    
    
    // Keeps track of when game started
    float time_gravity = 0;
    float time_start = TimeNow();

    // Stores coordinates of touches
    int x_coord, y_coord;

    // Stores if player clicked at beginning of game
    bool InitTouch = false;

    // Clears any touches 
    LCD.ClearBuffer();
    

    // Displays map and Block in starting position
    DisplayMaze();

    // Detects if user should exit Play() function (has won or lost the level)
    while( TimeNow() < time_start + LVL1TIME  && !BlockFinished() && BlockInBounds()) {   

        // Returns true at first touch
        InitTouch = LCD.Touch(&x_coord, &y_coord);

        LCD.SetFontColor(BLACK);
        // Draws rectangles using the BoundaryRects[][] array, which create a maze
        for (int n = 0; n < 4; n++)    {
            LCD.FillRectangle(BoundaryRects[n][0], BoundaryRects[n][1], BoundaryRects[n][2], BoundaryRects[n][3]);
        }

        // Writes time to screen
        LCD.SetFontColor(RED);
        LCD.WriteAt("Time:", 160, 200);
        LCD.WriteAt((LVL1TIME-(TimeNow()-time_start)), 230, 200);
        
        LCD.Update();

        // Checks if player should exit function, and if initial touch has been made  (game physics don't begin until init touch made)
        while( ((TimeNow() < time_start + LVL1TIME)  && !BlockFinished()) && InitTouch && BlockInBounds())  {
            
            LCD.SetFontColor(BLACK);
            // Draws rectangles using the BoundaryRects[][] array, which create a maze
            for (int n = 0; n < 4; n++)    {
                LCD.FillRectangle(BoundaryRects[n][0], BoundaryRects[n][1], BoundaryRects[n][2], BoundaryRects[n][3]);
            }
            
            LCD.SetFontColor(RED);
            LCD.WriteAt("Time:", 160, 200);
            LCD.WriteAt((LVL1TIME-(TimeNow()-time_start)), 230, 200);
            
            LCD.Update();
            
            // Waits for player to touch screen
            if (LCD.Touch(&x_coord, &y_coord))    {
                    
                // Checks player touch is inside of Block
                if (Block.Pressed(x_coord, y_coord, 0))  {
                    while ((TimeNow() < time_start + LVL1TIME  && !BlockFinished()) && LCD.Touch(&x_coord, &y_coord) && BlockInBounds())   {  
                        // Sets the velocity from gravity to 0
                        time_gravity = 0;
                        
                        // Moves block to where next touch detected
                        //BlockMove(&x_coord, &y_coord);
                        BlockMove(&x_coord, &y_coord, &BlockOrigin[0], &BlockOrigin[1], Block);

                        LCD.SetFontColor(BLACK);
                        // Draws rectangles using the BoundaryRects[][] array, which create a maze
                        for (int n = 0; n < 4; n++)    {
                            LCD.FillRectangle(BoundaryRects[n][0], BoundaryRects[n][1], BoundaryRects[n][2], BoundaryRects[n][3]);
                        }
                        LCD.SetFontColor(RED);
                        LCD.WriteAt("Time:", 160, 200);
                        LCD.WriteAt((LVL1TIME-(TimeNow()-time_start)), 230, 200);
                        
                        LCD.Update();
                    }
                }
                else {
                    // Increases the time since the block was last moved (rate of change of gravity)
                    time_gravity += 0.15; 
                    
                    BlockGravity(&BlockOrigin[0], &BlockOrigin[1], &Block, time_gravity);
                }
            }
            if (!LCD.Touch(&x_coord, &y_coord)) {
                // Increases the time since the block was last moved (rate of change of gravity)
                time_gravity += 0.15; 

                BlockGravity(&BlockOrigin[0], &BlockOrigin[1], &Block, time_gravity);
            }
        }
    }

    // Sets win to true if player wins level in Time 
    if (BlockFinished())  {
        Win = true;
        TimeComplete = TimeNow() - time_start;
    }
}


// LevelOne DisplayMaze() function      
// Draws maze for level 1 to screen
// Parameters: None
// Created by David

void LevelOne::DisplayMaze()  {
    
    // Set background color to CYAN and clear screen 
    LCD.SetBackgroundColor(CYAN);
    LCD.Clear();
    
    LCD.SetFontColor(BLACK);    //Sets font to black

    // Draws rectangles using the BoundaryRects[][] array, which create a maze
    for (int n = 0; n < 4; n++)    {
        LCD.FillRectangle(BoundaryRects[n][0], BoundaryRects[n][1], BoundaryRects[n][2], BoundaryRects[n][3]);
    }

    LCD.SetFontColor(RED);
    //Draw Finish
    LCD.FillRectangle(FinishRect[0], FinishRect[1], FinishRect[2], FinishRect[3]);

    // Fills a rectangle at same spot as icon 
    LCD.FillRectangle( BlockOrigin[0], BlockOrigin[1], D1BLOCK, D1BLOCK);
   
    Block.Draw();
} // end DisplayMaze()


// BlockFinished()      
// returns true if Block is passed finish line, otherwise returns false
// Parameters: None
// Created by David, edited by Steven and David

bool LevelOne :: BlockFinished()    {
    if  ((BlockOrigin[0] > FinishRect[0]) && (BlockOrigin[0] + D1BLOCK < FinishRect[0] + FinishRect[2]) && (BlockOrigin[1] <= FinishRect[1] + FinishRect[3]))
    {
        return true;
    }
    else {
        return false;
    }
}


// BlockInBounds()      
// returns true if Block is not touching any walls, otherwise returns false
// Parameters: NONE
// Created by David

bool LevelOne :: BlockInBounds()    {
    // Keeps track of how many conditions met, check == pass to return true
    int check = 0, pass;
    // Check every boundary
    for (int n = 0; n < 4; n++) {
        // Increments check by 1 if all 4 corners of block are outside of boundary walls        
        if(!( (BlockOrigin[0] > BoundaryRects[n][0] && BlockOrigin[0] < BoundaryRects[n][0]+BoundaryRects[n][2]) && (BlockOrigin[1] > BoundaryRects[n][1] && BlockOrigin[1] < BoundaryRects[n][1] + BoundaryRects[n][3])))  {
            if (!( (BlockOrigin[0] + D1BLOCK > BoundaryRects[n][0] && BlockOrigin[0] + D1BLOCK < BoundaryRects[n][0]+BoundaryRects[n][2]) && (BlockOrigin[1] > BoundaryRects[n][1] && BlockOrigin[1] < BoundaryRects[n][1] + BoundaryRects[n][3]))) {
                if(!( (BlockOrigin[0] > BoundaryRects[n][0] && BlockOrigin[0] < BoundaryRects[n][0]+BoundaryRects[n][2]) && (BlockOrigin[1] + D1BLOCK > BoundaryRects[n][1] && BlockOrigin[1] + D1BLOCK < BoundaryRects[n][1] + BoundaryRects[n][3]))) {
                    if(!( (BlockOrigin[0] + D1BLOCK > BoundaryRects[n][0] && BlockOrigin[0] + D1BLOCK < BoundaryRects[n][0]+BoundaryRects[n][2]) && (BlockOrigin[1] + D1BLOCK > BoundaryRects[n][1] && BlockOrigin[1] + D1BLOCK < BoundaryRects[n][1] + BoundaryRects[n][3])))   {
                        check +=1;
                    }
                }
            }
             
        }
        // Increments pass by 1 for each boundary rectangle 
        pass += 1;
    }
    
    if (check == pass)  {
        if ((BlockOrigin[0] > 0) && (BlockOrigin[0] + D1BLOCK < 320) && (BlockOrigin[1] > 0) && (BlockOrigin[1] + D1BLOCK < 240)){
            return true;
        }
    }
    return false;
}


//              LevelTwo Member Functions
// ****************************************************
//     Member functions copied from LevelOne class
//     and corrected for level 2 (change vars etc.)
//     Done by Steven 


// Play function for level 2
// See flow chart for visualization: https://u.osu.edu/fehsdp2021bcm0800g1/project-planning/
// Parameters: None

void LevelTwo::Play()   {
    
    
    // Keeps track of when game started
    float time_gravity = 0;
    float time_start = TimeNow();

    // Stores coordinates of touches
    int x_coord, y_coord;

    // Stores if player clicked at beginning of game
    bool InitTouch = false;

    // Clears any touches
    LCD.ClearBuffer();
    

    // Displays map and Block in starting position
    DisplayMaze();

    // Detects if user should exit Play() function (has won or lost the level)
    while( TimeNow() < time_start + LVL2TIME  && !BlockFinished() && BlockInBounds()) {   

        // Returns true at first touch
        InitTouch = LCD.Touch(&x_coord, &y_coord);
        LCD.SetFontColor(RED);
        LCD.WriteAt("Time:", 160, 200);
        LCD.WriteAt(LVL2TIME, 230, 200);

        LCD.SetFontColor(BLACK);
        // Draws rectangles using the BoundaryRects[][] array, which create a maze
        for (int n = 0; n < 8; n++)    {
            LCD.FillRectangle(BoundaryRects[n][0], BoundaryRects[n][1], BoundaryRects[n][2], BoundaryRects[n][3]);
        }
        LCD.SetFontColor(RED);
        LCD.WriteAt("Time:", 160, 200);
        LCD.WriteAt((LVL2TIME-(TimeNow()-time_start)), 230, 200);
        
        LCD.Update();

        // Checks if player should exit function, and if initial touch has been made  (game physics don't begin until init touch made)
        while( ((TimeNow() < time_start + LVL2TIME)  && !BlockFinished()) && InitTouch && BlockInBounds())  {
       
            LCD.SetFontColor(BLACK);
            // Draws rectangles using the BoundaryRects[][] array, which create a maze
            for (int n = 0; n < 8; n++)    {
                LCD.FillRectangle(BoundaryRects[n][0], BoundaryRects[n][1], BoundaryRects[n][2], BoundaryRects[n][3]);
            }
            LCD.SetFontColor(RED);
            LCD.WriteAt("Time:", 160, 200);
            LCD.WriteAt((LVL2TIME-(TimeNow()-time_start)), 230, 200);
            
            LCD.Update();
            
            // Waits for player to touch screen
            if (LCD.Touch(&x_coord, &y_coord))    {
                    
                // Checks if initial player touch is inside of Block
                if (Block.Pressed(x_coord, y_coord, 0))  {
                    while ((TimeNow() < time_start + LVL2TIME  && !BlockFinished()) && LCD.Touch(&x_coord, &y_coord) && BlockInBounds())   {  
                        // Sets the velocity from gravity to 0
                        time_gravity = 0;
                        
                        // Moves block to where next touch detected
                        //BlockMove(&x_coord, &y_coord);
                        BlockMove(&x_coord, &y_coord, &BlockOrigin[0], &BlockOrigin[1], Block);
                    
                        LCD.SetFontColor(BLACK);
                        // Draws rectangles using the BoundaryRects[][] array, which create a maze
                        for (int n = 0; n < 8; n++)    {
                            LCD.FillRectangle(BoundaryRects[n][0], BoundaryRects[n][1], BoundaryRects[n][2], BoundaryRects[n][3]);
                        }
                        LCD.SetFontColor(RED);
                        LCD.WriteAt("Time:", 160, 200);
                        LCD.WriteAt((LVL2TIME-(TimeNow()-time_start)), 230, 200);
                        
                        LCD.Update();
                    }
                }
                else {
                    // Increases the time since the block was last moved (rate of change of gravity)
                    time_gravity += 0.15; 
                    
                    BlockGravity(&BlockOrigin[0], &BlockOrigin[1], &Block, time_gravity);
                }
            }
            if (!LCD.Touch(&x_coord, &y_coord)) {
                // Increases the time since the block was last moved (rate of change of gravity)
                time_gravity += 0.15; 

                BlockGravity(&BlockOrigin[0], &BlockOrigin[1], &Block, time_gravity);
            }
        }
    }

    // Sets win to true if player wins level in Time 
    if (BlockFinished())  {
        TimeComplete = TimeNow() - time_start;
        Win = true;
    }
}


// LevelTwo DisplayMaze() function      
// Draws maze for level 1 to screen
// Parameters: None

void LevelTwo::DisplayMaze()  {
    
    // Set background color to CYAN and clear screen 
    LCD.SetBackgroundColor(CYAN);
    LCD.Clear();
    
    LCD.SetFontColor(BLACK);    //Sets font to black

    // Draws rectangles using the BoundaryRects[][] array, which create a maze
    for (int n = 0; n < 8; n++)    {
        LCD.FillRectangle(BoundaryRects[n][0], BoundaryRects[n][1], BoundaryRects[n][2], BoundaryRects[n][3]);
    }

    LCD.SetFontColor(RED);
    //Draw Finish
    LCD.FillRectangle(FinishRect[0], FinishRect[1], FinishRect[2], FinishRect[3]);

    // Fills a rectangle at same spot as icon 
    LCD.FillRectangle( BlockOrigin[0], BlockOrigin[1], D1BLOCK, D1BLOCK);
   
    Block.Draw();
} // end DisplayMaze()


// BlockFinished()      
// returns true if Block is passed finish line, otherwise returns false
// Parameters: None

bool LevelTwo :: BlockFinished()    {
    if  ((BlockOrigin[0] > FinishRect[0]) && (BlockOrigin[0] + D1BLOCK < FinishRect[0] + FinishRect[2]) && (BlockOrigin[1] <= FinishRect[1] + FinishRect[3]) && (BlockOrigin[1] >= FinishRect[1]))
    {
        return true;
    }
    else {
        return false;
    }
}

// BlockInBounds()      
// returns true if Block is not touching any walls, otherwise returns false
// Parameters: NONE

bool LevelTwo :: BlockInBounds()    {
    // Keeps track of how many conditions met, check must == pass to return true
    int check = 0, pass;
    for (int n = 0; n < 8; n++) {
        // Increments check by 1 if all 4 corners of block are outside of walls
        if(!( (BlockOrigin[0] > BoundaryRects[n][0] && BlockOrigin[0] < BoundaryRects[n][0]+BoundaryRects[n][2]) && (BlockOrigin[1] > BoundaryRects[n][1] && BlockOrigin[1] < BoundaryRects[n][1] + BoundaryRects[n][3])))  {
            if (!( (BlockOrigin[0] + D1BLOCK > BoundaryRects[n][0] && BlockOrigin[0] + D1BLOCK < BoundaryRects[n][0]+BoundaryRects[n][2]) && (BlockOrigin[1] > BoundaryRects[n][1] && BlockOrigin[1] < BoundaryRects[n][1] + BoundaryRects[n][3]))) {
                if(!( (BlockOrigin[0] > BoundaryRects[n][0] && BlockOrigin[0] < BoundaryRects[n][0]+BoundaryRects[n][2]) && (BlockOrigin[1] + D1BLOCK > BoundaryRects[n][1] && BlockOrigin[1] + D1BLOCK < BoundaryRects[n][1] + BoundaryRects[n][3]))) {
                    if(!( (BlockOrigin[0] + D1BLOCK > BoundaryRects[n][0] && BlockOrigin[0] + D1BLOCK < BoundaryRects[n][0]+BoundaryRects[n][2]) && (BlockOrigin[1] + D1BLOCK > BoundaryRects[n][1] && BlockOrigin[1] + D1BLOCK < BoundaryRects[n][1] + BoundaryRects[n][3])))   {
                        check +=1;
                    }
                }
            }
             
        }
        // Increments pass by 1 for each boundary rectangle 
        pass += 1;
    }
    
    if (check == pass)  {
        if ((BlockOrigin[0] > 0) && (BlockOrigin[0] + D1BLOCK < 320) && (BlockOrigin[1] > 0) && (BlockOrigin[1] + D1BLOCK < 240)){
            return true;
        }
    }
    return false;
}

//              LevelThree Member Functions
// ****************************************************
//     Member functions copied from LevelOne class
//     and corrected for level 3 (change vars etc.)
//     Done by Steven 

// Play function for level 2
// See flow chart for visualization: https://u.osu.edu/fehsdp2021bcm0800g1/project-planning/
// Parameters: None

void LevelThree::Play()   {
    
    
    // Keeps track of when game started
    float time_gravity = 0;
    float time_start = TimeNow();

    // Stores coordinates of touches
    int x_coord, y_coord;

    // Stores if player clicked at beginning of game
    bool InitTouch = false;

    // Clears any previous touches
    LCD.ClearBuffer();
    

    // Displays map and Block in starting position
    DisplayMaze();

    // Detects if user should exit Play() function (has won or lost the level)
    while( TimeNow() < time_start + LVL3TIME  && !BlockFinished() && BlockInBounds()) {   

        // Returns true at first touch
        InitTouch = LCD.Touch(&x_coord, &y_coord);
        LCD.SetFontColor(RED);
        LCD.WriteAt("Time:", 160, 200);
        LCD.WriteAt(LVL3TIME, 230, 200);
        
        LCD.SetFontColor(BLACK);
        // Draws rectangles using the BoundaryRects[][] array, which create a maze
        for (int n = 0; n < 10; n++)    {
            LCD.FillRectangle(BoundaryRects[n][0], BoundaryRects[n][1], BoundaryRects[n][2], BoundaryRects[n][3]);
        }
        LCD.SetFontColor(RED);
        LCD.WriteAt("Time:", 160, 200);
        LCD.WriteAt((LVL3TIME-(TimeNow()-time_start)), 230, 200);
        
        LCD.Update();

        // Checks if player should exit function, and if initial touch has been made  (game physics don't begin until init touch made)
        while( ((TimeNow() < time_start + LVL3TIME)  && !BlockFinished()) && InitTouch && BlockInBounds())  {
       
            LCD.SetFontColor(BLACK);
            // Draws rectangles using the BoundaryRects[][] array, which create a maze
            for (int n = 0; n < 10; n++)    {
                LCD.FillRectangle(BoundaryRects[n][0], BoundaryRects[n][1], BoundaryRects[n][2], BoundaryRects[n][3]);
            }

            LCD.SetFontColor(RED);
            LCD.WriteAt("Time:", 160, 200);
            LCD.WriteAt((LVL3TIME-(TimeNow()-time_start)), 230, 200);
            
            LCD.Update();
            
            // Waits for player to touch screen
            if (LCD.Touch(&x_coord, &y_coord))    {
                    
                // Checks if initial player touch is inside of Block
                if (Block.Pressed(x_coord, y_coord, 0))  {
                    while ((TimeNow() < time_start + LVL3TIME  && !BlockFinished()) && LCD.Touch(&x_coord, &y_coord) && BlockInBounds())   {  
                        // Sets the velocity from gravity to 0
                        time_gravity = 0;
                        
                        // Moves block to where next touch detected
                        //BlockMove(&x_coord, &y_coord);
                        BlockMove(&x_coord, &y_coord, &BlockOrigin[0], &BlockOrigin[1], Block);
                    
                        LCD.SetFontColor(BLACK);
                        // Draws rectangles using the BoundaryRects[][] array, which create a maze
                        for (int n = 0; n < 10; n++)    {
                            LCD.FillRectangle(BoundaryRects[n][0], BoundaryRects[n][1], BoundaryRects[n][2], BoundaryRects[n][3]);
                        }
                        LCD.SetFontColor(RED);
                        LCD.WriteAt("Time:", 160, 200);
                        LCD.WriteAt((LVL3TIME-(TimeNow()-time_start)), 230, 200);
                        
                        LCD.Update();
                    }
                }
                else {
                    // Increases the time since the block was last moved (rate of change of gravity)
                    time_gravity += 0.15; 
                    
                    BlockGravity(&BlockOrigin[0], &BlockOrigin[1], &Block, time_gravity);
                }
            }
            if (!LCD.Touch(&x_coord, &y_coord)) {
                // Increases the time since the block was last moved (rate of change of gravity)
                time_gravity += 0.15; 

                BlockGravity(&BlockOrigin[0], &BlockOrigin[1], &Block, time_gravity);
            }
        }
    }

    // Sets win to true if player wins level in Time 
    if (BlockFinished())  {
        TimeComplete = TimeNow() - time_start;
        Win = true;
    }
}


// LevelThree DisplayMaze() function      
// Draws maze for level 1 to screen
// Parameters: None

void LevelThree::DisplayMaze()  {
    
    // Set background color to CYAN and clear screen 
    LCD.SetBackgroundColor(CYAN);
    LCD.Clear();
    
    LCD.SetFontColor(BLACK);    //Sets font to black

    // Draws rectangles using the BoundaryRects[][] array, which create a maze
    for (int n = 0; n < 10; n++)    {
        LCD.FillRectangle(BoundaryRects[n][0], BoundaryRects[n][1], BoundaryRects[n][2], BoundaryRects[n][3]);
    }

    LCD.SetFontColor(RED);
    //Draw Finish
    LCD.FillRectangle(FinishRect[0], FinishRect[1], FinishRect[2], FinishRect[3]);

    // Fills a rectangle at same spot as icon 
    LCD.FillRectangle( BlockOrigin[0], BlockOrigin[1], D1BLOCK, D1BLOCK);
   
    Block.Draw();
} // end DisplayMaze()


// BlockFinished()      
// returns true if Block is passed finish line, otherwise returns false
// Parameters: None

bool LevelThree :: BlockFinished()    {
    if  ((BlockOrigin[0] + D1BLOCK >= FinishRect[0]) && (BlockOrigin[1] <= FinishRect[1]) && (BlockOrigin[1] + D1BLOCK <= FinishRect[1] + FinishRect[3]))
    {
        return true;
    }
    else {
        return false;
    }
}

// BlockInBounds()      
// returns true if Block is not touching any walls, otherwise returns false
// Parameters: NONE

bool LevelThree :: BlockInBounds()    {
    // Keeps track of how many conditions met, check must == pass to return true
    int check = 0, pass;
    for (int n = 0; n < 10; n++) {
        // Increments check by 1 if all 4 corners of block are outside of walls
        if(!( (BlockOrigin[0] > BoundaryRects[n][0] && BlockOrigin[0] < BoundaryRects[n][0]+BoundaryRects[n][2]) && (BlockOrigin[1] > BoundaryRects[n][1] && BlockOrigin[1] < BoundaryRects[n][1] + BoundaryRects[n][3])))  {
            if (!( (BlockOrigin[0] + D1BLOCK > BoundaryRects[n][0] && BlockOrigin[0] + D1BLOCK < BoundaryRects[n][0]+BoundaryRects[n][2]) && (BlockOrigin[1] > BoundaryRects[n][1] && BlockOrigin[1] < BoundaryRects[n][1] + BoundaryRects[n][3]))) {
                if(!( (BlockOrigin[0] > BoundaryRects[n][0] && BlockOrigin[0] < BoundaryRects[n][0]+BoundaryRects[n][2]) && (BlockOrigin[1] + D1BLOCK > BoundaryRects[n][1] && BlockOrigin[1] + D1BLOCK < BoundaryRects[n][1] + BoundaryRects[n][3]))) {
                    if(!( (BlockOrigin[0] + D1BLOCK > BoundaryRects[n][0] && BlockOrigin[0] + D1BLOCK < BoundaryRects[n][0]+BoundaryRects[n][2]) && (BlockOrigin[1] + D1BLOCK > BoundaryRects[n][1] && BlockOrigin[1] + D1BLOCK < BoundaryRects[n][1] + BoundaryRects[n][3])))   {
                        check +=1;
                    }
                }
            }
             
        }
        // Increments pass by 1 for each boundary rectangle 
        pass += 1;
    }
    
    if (check == pass)  {
        if ((BlockOrigin[0] > 0) && (BlockOrigin[0] + D1BLOCK < 320) && (BlockOrigin[1] > 0) && (BlockOrigin[1] + D1BLOCK < 240)){
            return true;
        }
    }
    return false;
}

// ****************************************************
//            Class Constructors                     //
// ****************************************************

// Player constructor (Created by David)
Player :: Player() {
    
    //Initialize values of data members
    score = 0; 
    for (int n = 0; n < LVLS; n++ )    {
        subscores[n] = 0;
    }
    LevelOne LvlOne;
    LevelTwo LvlTwo; 
    LevelThree LvlThree; 

} 

// Level 1 constructor      (Created by David, edited by Steven and David)

LevelOne :: LevelOne()  
: FinishRect {285, 0, 25, 5},   // from https://stackoverflow.com/questions/10694689/how-to-initialize-an-array-in-c-objects
  BoundaryRects { {0,0, 20, 180}, {0, 180, 320, 60}, {50, 0, 235, 155}, {310, 0, 10, 180} } 
{
    // Sets initial properties and draws Block icon in starting position
    BlockOrigin[0] = 28;
    BlockOrigin[1] = 10;
    Block.SetProperties("", BlockOrigin[0], BlockOrigin[1], D1BLOCK, D1BLOCK, RED, RED);
    TimeComplete = LVL1TIME; 
    Win = false;
}  


// Level 2 constructor      (Created by Steven)
LevelTwo :: LevelTwo()  
: FinishRect {110, 150, 18, 5},   // from https://stackoverflow.com/questions/10694689/how-to-initialize-an-array-in-c-objects
  BoundaryRects { {0,0, 70, 95}, {0, 95, 110, 90}, {0, 185, 320, 55}, {70, 0, 250, 5}, {95, 35, 225, 38}, {110, 95, 18, 55}, {128, 95, 132, 71}, {280, 73, 40, 163}} 
{
    // Sets initial properties and draws Block icon in starting position
    BlockOrigin[0] = 280;
    BlockOrigin[1] = 15;
    Block.SetProperties("", BlockOrigin[0], BlockOrigin[1], D1BLOCK, D1BLOCK, RED, RED);
    TimeComplete = LVL2TIME; 
    Win = false;
}  


// Level 3 constructor      (Created by Steven, edited by Steven and David)
LevelThree :: LevelThree()  
: FinishRect {315, 113, 5, 14},   // from https://stackoverflow.com/questions/10694689/how-to-initialize-an-array-in-c-objects
  BoundaryRects { {0, 0, 64, 105}, {0, 135, 64, 105} ,{64, 0, 64, 107}, {64, 133, 64, 107}, {128, 0, 64, 109}, {128, 131, 64, 109}, {192, 0, 64, 111}, {192, 129, 64, 111}, {256, 0, 64, 113}, {256, 127, 64, 113} } 
{
    // Sets initial properties and draws Block icon in starting position
    BlockOrigin[0] = 5;
    BlockOrigin[1] = 113;
    Block.SetProperties("", BlockOrigin[0], BlockOrigin[1], D1BLOCK, D1BLOCK, RED, RED);
    TimeComplete = LVL3TIME; 
    Win = false;
}  
//other classes use default constructor