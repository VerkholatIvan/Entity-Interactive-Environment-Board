#include <iomanip>
#include <string>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;


// ==========================================
//  CLASSES ヾ(•ω•`)o
// ==========================================


class entity{
    public:
    int loc_r, loc_c;
    entity(){
        // random locations on the map for setting entities
        loc_r = rand()%10; 
        loc_c = rand()%10;
    }

    void show_info(){
        cout << "Entity info:" << endl;
    }
};

// ------------------------------------------

class stone: public entity{
    public:
    char symbol = 'S'; // entity symbol on the map
    stone(): entity(){} // constructor 

    void show_info(){
        entity::show_info();
        cout << "Type: Stone" << endl;
    }
};

// ------------------------------------------

class hole: public entity{
    public:
    int depth;
    char symbol = 'O'; // entity symbol on the map
    hole(): entity(){depth = rand()%21;} // constructor with random depth for every hole /// each hole has different depth

    void show_info(){
        entity::show_info();
        cout << "Type: Stone" << endl;
        cout << "Depth: " << depth << endl;
    }
};

// ------------------------------------------

class animated_ent: public entity{
    public:
    int health;
    animated_ent(): entity(){health = 100;}
    virtual void move(char (*map)[10]) = 0; // dunno

    void show_info(){
        entity::show_info();
        cout << "Health: " << health << endl;
    }
};

// ------------------------------------------

class human: public animated_ent{
    public:
    string Name;
    human(string input = "uknown"): animated_ent(){Name = input;}
    char symbol = '@'; // entity symbol on the map
    void move(char (*map)[10]){
        if ((map[loc_r][loc_c + 1] == '.') && ((loc_c + 1) < 10)){ // move right
            map[loc_r][loc_c] = '.';
            loc_c++;
            health--;
        }

        else{
            bool action = false;
            while (!action){
                srand(time(0));
                int choose_move = rand()%3;
                switch(choose_move){
                    case 0: // move up
                        if ((map[loc_r - 1][loc_c] == '.') && (-1 < (loc_r - 1))){map[loc_r][loc_c] = '.'; loc_r--; health--; action = true; break;}
                        else{break;}

                    case 1: // move left 
                        if ((map[loc_r][loc_c - 1] == '.') && (-1 < (loc_c - 1))){map[loc_r][loc_c] = '.'; loc_c--; health--; action = true; break;}
                        else{break;}

                    case 2: // move down
                        if ((map[loc_r + 1][loc_c] == '.') && ((loc_r + 1) < 10)){map[loc_r][loc_c] = '.'; loc_r++; health--; action = true; break;}
                        else{break;}

                    }

                }
            }
        }

    void show_info(){
        animated_ent::show_info();
        cout << "Type: Human" << endl;
        cout << "Name: " << Name << "\n" << endl;
    }
};

// ------------------------------------------

class dragon: public animated_ent{
    public:
    dragon(): animated_ent(){}
    char symbol = '#'; // entity symbol on the map
    void move(char (*map)[10]){
        bool action = false;
        while (!action){
                    int choose_move = rand()%4;
                    switch(choose_move){
                        case 0: // move up
                            if ((map[loc_r - 1][loc_c] == '.') && ( -1 < (loc_r - 1))){map[loc_r][loc_c] = '.'; loc_r--; health = health - rand()%6; action = true; break;}
                            else{break;}
                            
                        case 1: // move right
                            if ((map[loc_r][loc_c - 1] == '.') && ( -1 < (loc_c - 1))){map[loc_r][loc_c] = '.'; loc_c--; health = health - rand()%6; action = true; break;}
                            else{break;}

                        case 2: // move down
                            if ((map[loc_r + 1][loc_c] == '.') && ((loc_r + 1) < 10)){map[loc_r][loc_c] = '.'; loc_r++; health = health - rand()%6; action = true; break;}
                            else{break;}

                        case 3: // move left
                            if ((map[loc_r][loc_c + 1] == '.') && ((loc_c + 1) < 10)){map[loc_r][loc_c] = '.'; loc_c++; health = health - rand()%6; action = true; break;}
                            else{break;}

                    }
        }
    }

    void show_info(){
        animated_ent::show_info();
        cout << "Type: Dragon\n" << endl;
    }
};

// ------------------------------------------

class monster: public animated_ent{
    public:
    monster(): animated_ent(){}
    char symbol = '*'; // entity symbol on the map
    int distance;
    void move(char (*map)[10]){
        bool action = false;
        while (!action){
                    int choose_move = rand()%4;
                    switch(choose_move){
                        case 0: // move up
                            distance = rand()%6;
                            if ((map[loc_r - distance][loc_c] == '.') && (-1 < (loc_r - distance))){map[loc_r][loc_c] = '.'; loc_r = loc_r - distance; health = health - rand()%6; action = true; break;}
                            else{break;}
                            
                        case 1: // move right
                            distance = rand()%6;
                            if ((map[loc_r][loc_c - distance] == '.') && (-1 < (loc_c - distance))){map[loc_r][loc_c] = '.'; loc_c = loc_c - distance; health = health - rand()%6; action = true; break;}
                            else{break;}

                        case 2: // move down
                            distance = rand()%6;
                            if ((map[loc_r + distance][loc_c] == '.') && ((loc_r + distance) < 10)){map[loc_r][loc_c] = '.'; loc_r = loc_r + distance; health = health - rand()%6; action = true; break;}
                            else{break;}

                        case 3: // move left
                            distance = rand()%6;
                            if ((map[loc_r][loc_c + distance] == '.') && ((loc_c + distance) < 10)){map[loc_r][loc_c] = '.'; loc_c = loc_c + distance; health = health - rand()%6; action = true; break;}
                            else{break;}

                    }
        }        
    }

    void show_info(){
        animated_ent::show_info();
        cout << "Type: Monster\n" << endl;
    }
};

// ------------------------------------------

class room{
    public:
    // Entities objects
    stone S1; stone S2;
    hole O1; hole O2;
    human H1; human H2; human H3;
    dragon D1; dragon D2;
    monster M1; monster M2; monster M3;

    // Board creation
    char map[10][10];
    room(){ 
        for (int x=0; x<10; x++){
            for (int y=0; y<10; y++){
                map[x][y] = '.';
            }
        }
        // setting human's names
        H1 = human("Jay");
        H2 = human("Damir");
        H3 = human("Abbas");
    }


    
    void replace_all(){ // Sets all entities on the board
        
        map[S1.loc_r][S1.loc_c] = S1.symbol;    map[S2.loc_r][S2.loc_c] = S2.symbol;
        
        map[O1.loc_r][O1.loc_c] = O1.symbol;    map[O2.loc_r][O2.loc_c] = O2.symbol;
        
        map[H1.loc_r][H1.loc_c] = H1.symbol;    map[H2.loc_r][H2.loc_c] = H2.symbol;    map[H3.loc_r][H3.loc_c] = H3.symbol;
        
        map[D1.loc_r][D1.loc_c] = D1.symbol;    map[D2.loc_r][D2.loc_c] = D2.symbol;

        map[M1.loc_r][M1.loc_c] = M1.symbol;    map[M2.loc_r][M2.loc_c] = M2.symbol;    map[M3.loc_r][M3.loc_c] = M3.symbol;
    }

    void move_all(){ // Move all entities
        H1.move(map);
        H2.move(map);
        H3.move(map);
        D1.move(map);
        D2.move(map);
        M1.move(map);
        M2.move(map);
        M3.move(map);
    }

    // show the information about the entity
    void show_info(int row, int col){
        if ((row == S1.loc_r) && (col == S1.loc_c)){S1.show_info();}
        else if ((row == S2.loc_r) && (col == S2.loc_c)){S2.show_info();}
        else if ((row == O1.loc_r) && (col == O1.loc_c)){O1.show_info();}
        else if ((row == O2.loc_r) && (col == O2.loc_c)){O2.show_info();}
        else if ((row == H1.loc_r) && (col == H1.loc_c)){H1.show_info();}
        else if ((row == H2.loc_r) && (col == H2.loc_c)){H2.show_info();}
        else if ((row == H3.loc_r) && (col == H3.loc_c)){H3.show_info();}
        else if ((row == D1.loc_r) && (col == D1.loc_c)){D1.show_info();}
        else if ((row == D2.loc_r) && (col == D2.loc_c)){D2.show_info();}
        else if ((row == M1.loc_r) && (col == M1.loc_c)){M1.show_info();}
        else if ((row == M2.loc_r) && (col == M2.loc_c)){M2.show_info();}
        else if ((row == M3.loc_r) && (col == M3.loc_c)){M3.show_info();}
        else{cout << "Invalid input" << endl;}
    }

    void show_room(){ // Show the room
        cout << "   ";
        for (int i=0; i < 10; i++){ // setting horizontaly numbers to the map for easier row and column choice
            cout << setw(2.5) << i << " ";
        }
        cout << endl;
        for (int x=0; x<10; x++){ // setting vertically numbers to the map for easier row and column choice
            cout << setw(2.5) << x;
            for (int y=0; y<10; y++){
                cout << setw(3) << map[x][y];
            }   
            cout << endl;
        }
        cout << endl;
    }

};


// ==========================================
//  MAIN CODE (⊙x⊙;)
// ==========================================

int main(){
    // Main environment board creation
    srand(time(0)); 
    
    room *r; // creating the object as a pointer
    r = new room;

    
    // Interaction bar
    int user; // user case option
    bool start = true; // loop stopper
    int r_user, c_user; // for row and column choice in case 3

    cout << "\nGame Interaction Menu\n---------------------------\n" << endl;

    cout << "1.Display Room " << endl;
    cout << "2.Move all the animated entities " << endl;
    cout << "3.Display the entity state by coordinates " << endl;
    cout << "4.Reset the room " << endl;
    cout << "5.Finish\n" << endl;
    cout << "---------------------------\n" << endl;\

    // Main while loop for interaction with the environment
    while (start){
            cout << ">> ";
            cin >> user;
            cout << endl;
            r->replace_all();

            if (cin.fail()){ // "If" to prevent error with the  infinite loop 
                cin.clear(); // Cleans the input
                cin.ignore(); // Ignores wrong type input 
                cout << "Unexpected input\nPlease try again\n" << endl;
            } 
        
            else
            {
                switch(user){
                    case 1: // Display Room 
                        // r->replace_all();
                        r->show_room();
                        break;

                    case 2: // Move all the animated entities 
                        cout << "Moving all entities ...\n" << endl;
                        r->move_all();
                        break;

                    case 3: // Display the entity state by coordinates
                        cout << "Enter the row number \n>> ";
                        cin >> r_user;
                        cout << "\nEnter the column number \n>> ";
                        cin >> c_user;
                        cout << "\n" << endl;
                        r->show_info(r_user, c_user);
                        break;

                    case 4: // Reset the room/Create new room
                        cout << "Resetting the the board ... \n" << endl;
                        delete r;
                        r = new room(); 
                        break;

                    case 5: // Finish/Exit 
                        start = false;
                        break; 
            
                    default: // Unexpected input error
                        cout << "Unexpected input\nPlease try again\n" << endl;
                        break;
        
                }
            }            
    }  
   
}        