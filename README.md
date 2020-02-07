| Brionna Franklin|
| :---              |
| s198017          |
| Assessment 3 - Player Profile Database Documentation|
| Player Profile Database Documentation |

## I. Requirements

1. **Description of Problem**: For this project you are to create a program that loads, updates, and saves player profile information to a binary file.

    - **Name**: PlayerProfileDatabase

    - **Problem Statement**: For this project you are to create a program that loads, updates, and saves player profile information to a binary file.For each player in your database you must store their name and high-score. When your program launches it will read previously saved profiles from a binary file, if such a file exists. If no file exists then one will be created.Your program will allow the user to create new profiles, or to search for a profile and update the containing information. When your program exists, any new or modified records will be written back to the binary file.When saving new or updated profiles you must ensure that you use random-access algorithms to ensure that only modified data is saved. You must not re-write the entire file every time your application runs.

    - **Problem Specifications**:

        - Store the name and high-score information of the player.
            - Store the player name in a fixed-length array so that the position of each record can be calculated. This will enable you to update individualrecords in the file.
            - The player profile data must be encapsulated in a user defined class.
        - After the data file has been read, player profiles are to be sorted alphabetically.
        - Your program must allow the user to search for and update an individual player profile.
            - You must implement binary search as the search algorithm (this must be a custom implementation, not a library function).
        - When a player profile is updated or created, it should be written to the data file. Only the data that has changed should be written.
            - You must use the file pointer (i.e., random access) to jump to the appropriate location in the file, and only overwrite the record that has changed.
        - You must test your program to ensure its correct function. Include a test data file with your program.

2. **Input Information**:

    - type save, exit, new, or edit to save the current players in the database, exit the program, create a new player, or edit a current player's info.
    - after typying edit, type the name of the player's profile to edit it's name and score
    - after typing new, type a name and score for the new player

3. **Output Information**:

    - **Startup**: prints the player profiles loaded from the save file, or the default if one is not available.
    - **Player Input Message**: outputs a message that asks the user for input.

## II. Design

1. _System Architecture_
|
|:-----------
Game Function Diagram
|
![User Interface gif](https://i.imgur.com/104qwXa.png)

2. Object Information

    **File**: DataBase.cpp

        Description: Where most of the main functions extist; contains the main game loop

            Operations:

                -Name: DataBase
                Description: creates default players and adds them to the database
                Type: constructer
                Visibility: public

                -Name: DataBase
                Description: default deconstucter
                Type: deconstucter
                Visibility: public

                -Name: start
                Description: calls the main functions; loops until you exit the game
                Type: void
                Visibility: public

                -Name: draw
                Description: prints the players in the database along with their scores
                Type: void
                Visibility: public

                -Name: addPlayer
                Description: adds a new player the the array
                Type: void
                Visibility: public

                -Name: bubbleSort
                Description: sorts the players by letter
                Type: void
                Visibility: public

                -Name: swap
                Description: switches 2 players' positions in the array
                Type: void
                Visibility: public

                -Name: getCommand
                Description: takes in input from the user and calls the appropriate function based on it
                Type: void
                Visibility: private

                -Name: edit
                Description: searches for an inputted profile and allows the user to edit it
                Type: void
                Visibility: private

                -Name: save
                Description: saves the players in the database to a save file
                Type: void
                Visibility: private

                -Name: load
                Description: loads the save file if one exists
                Type: bool
                Visibility: private

                -Name: newPlayer
                Description: creates a new player profle and adds it to the batabase
                Type: void
                Visibility: private

                -Name: binarySearch
                Description: searches the database for the inputted player by name
                Type: int
                Visibility: private

    **File**: DataBase.h

        Description: Where most of the main functions are declared

            Attributes:

                -Name: DataBase
                Description: creates default players and adds them to the database
                Type: constructer
                Visibility: public

                -Name: DataBase
                Description: default deconstucter
                Type: deconstucter
                Visibility: public

                -Name: start
                Description: calls the main functions; loops until you exit the game
                Type: void
                Visibility: public

                -Name: draw
                Description: prints the players in the database along with their scores
                Type: void
                Visibility: public

                -Name: addPlayer
                Description: adds a new player the the array
                Type: void
                Visibility: public

                -Name: bubbleSort
                Description: sorts the players by letter
                Type: void
                Visibility: public

                -Name: swap
                Description: switches 2 players' positions in the array
                Type: void
                Visibility: public

                -Name: m_players
                Description: pointer to the players in the database
                Type: Player pointer
                Visibility: private

                -Name: bubbleSort
                Description: sorts the players by letter
                Type: void
                Visibility: public

                -Name: swap
                Description: switches 2 players' positions in the array
                Type: void
                Visibility: public

                -Name: m_players
                Description: pointer to the players in the database
                Type: Player pointer
                Visibility: private

                -Name: getCommand
                Description: takes in input from the user and calls the appropriate function based on it
                Type: void
                Visibility: private

                -Name: edit
                Description: searches for an inputted profile and allows the user to edit it
                Type: void
                Visibility: private

                -Name: save
                Description: saves the players in the database to a save file
                Type: void
                Visibility: private

                -Name: load
                Description: loads the save file if one exists
                Type: bool
                Visibility: private

                -Name: newPlayer
                Description: creates a new player profle and adds it to the batabase
                Type: void
                Visibility: private

                -Name: binarySearch
                Description: searches the database for the inputted player by name
                Type: int
                Visibility: private

                -Name: gameover
                Description: a bool that returns true when the game is over
                Type: bool
                Visibility: private

                -Name: m_playerCount
                Description: an int that represents the length of the array of players
                Type: int
                Visibility: private

                -Name: m_tempPlayerCount
                Description: an int that represents the length of the array of players but only temperarily
                Type: int
                Visibility: private

                -Name: m_tempPlayers
                Description: pointer to the players in the database thats temperary
                Type: Player pointer
                Visibility: private

    **File**: Player.cpp

        Description: stores a name and a score

            Operations:

                -Name: Player
                Description: default constructer
                Type: constructer
                Visibility: public

                -Name: Player
                Description: constructer; takes in name as a const char array and score as an int
                Type: constructer
                Visibility: public

                -Name: Player
                Description: default deconstructer
                Type: deconstructer
                Visibility: public

                -Name: Player
                Description: constructer; takes in a pointer to name and score as an int
                Type: constructer
                Visibility: public

               -Name: setName
                Description: sets the name of the player
                Type: void
                Visibility: public

                -Name: setScore
                Description: sets the score of the player
                Type: void
                Visibility: public

                -Name: save
                Description: saves the player's name and score
                Type: void
                Visibility: public

                -Name: load
                Description: loads the players name and score
                Type: bool
                Visibility: public

    **File**: Player.h

        Description: declares the everything in Player

            Attributes:

                -Name: Player
                Description: default constructer
                Type: constructer
                Visibility: public

                -Name: Player
                Description: constructer; takes in name as a const char array and score as an int
                Type: constructer
                Visibility: public

                -Name: Player
                Description: default deconstructer
                Type: deconstructer
                Visibility: public

                -Name: Player
                Description: constructer; takes in a pointer to name and score as an int
                Type: constructer
                Visibility: public

                -Name: setName
                Description: sets the name of the player
                Type: void
                Visibility: public

                -Name: setScore
                Description: sets the score of the player
                Type: void
                Visibility: public

                -Name: save
                Description: saves the player's name and score
                Type: void
                Visibility: public

                -Name: load
                Description: loads the players name and score
                Type: bool
                Visibility: public

                -Name: m_name
                Description: character array that hold the player's name
                Type: char array
                Visibility: public

                -Name: m_score
                Description: intiger that holds the player's score
                Type: int
                Visibility: public

    **File**: Player.cpp

        Description: stores a name and a score

            Operations:

                -Name: main
                Description: runs when programs start
                Type: int
                Visibility: private
