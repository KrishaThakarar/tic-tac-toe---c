#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/**
 * display board
*/
void displayBoard(char a[3][3])
{
    printf("\n\n");
    for (int i = 0; i < 3; i++)
    {
        printf("|");
        for (int j = 0; j < 3; j++)
        {

            printf(" %c | ", a[i][j]);
        }
        printf("\n");
    }
}

void initBoard(char a[3][3])
{
    char initialValue = '1';
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            a[i][j] = initialValue++;
        }
    }
}

int getRow(char choose)
{
    if (choose == '1' || choose == '2' || choose == '3')
    {
        return 0;
    }
    else if (choose == '4' || choose == '5' || choose == '6')
    {
        return 1;
    }
    else if (choose == '7' || choose == '8' || choose == '9')
    {
        return 2;
    }
    return -1;
}

int getcolum(char choose)
{
    if (choose == '1' || choose == '4' || choose == '7')
    {
        return 0;
    }
    else if (choose == '2' || choose == '5' || choose == '8')
    {
        return 1;
    }
    else if (choose == '3' || choose == '6' || choose == '9')
    {
        return 2;
    }
    return -1;
}

/**
 * return won - 1
 * return draw - 2
 * return remaining game - 3
 */
int checkBoard(char a[3][3])
{

    for (int i = 0; i < 3; i++)
    {
        if (a[0][i] == a[1][i] && a[1][i] == a[2][i] && a[0][i] == a[2][i])
        {
            return 1;
        }
        if (a[i][0] == a[i][1] && a[i][1] == a[i][2] && a[i][0] == a[i][2])
        {
            return 1;
        }
    }

    // 00 ==11==22
    // 20==11==02

    if (a[0][0] == a[1][1] && a[1][1] == a[2][2] && a[0][0] == a[2][2])
    {
        return 1;
    }
    else if (a[2][0] == a[1][1] && a[1][1] == a[0][2] && a[2][0] == a[0][2])
    {
        return 1;
    }

    /// remaining
    char count = '1';

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a[i][j] == count)
            {
                // it means game remaining
                return 3;
            }
            count += 1;
        }
    }

    // if not wan or not incomplete then draw
    return 2;
}

void playerTurnPrint(int turn, char oneOrTwoPlayer)
{
    if (turn == 1)
    {
        if (oneOrTwoPlayer == 'o' && turn == 1)
        {
            printf("Enter value ");
        }
        else
        {
            printf("Enter value for first player ");
        }
    }
    else
    {
        if (oneOrTwoPlayer == 'o' && turn == 2)
        {
        }
        else
        {
            printf("Enter value for second player ");
        }
    }
}

int changeTurn(int turn)
{
    if (turn == 1)
    {
        // 2nd player next turs
        turn = 2;
    }
    else
    {
        turn = 1;
    }
    return turn;
}

void printWon(int turn, char oneOrTwoPlayer)
{
    if (oneOrTwoPlayer == 'o' && turn == 2)
    {
        printf("Computer is won\n");
    }
    else if (turn == 1)
    {

        printf("First player is won\n");
    }
    else
    {
        printf("Second player is won\n");
    }
}

char choose()
{
    char *firstplayer = (char *)malloc(50);
    printf("choose o or x : ");
    fflush(stdin);
    scanf("%s", firstplayer);

    while (strcmp(firstplayer, "o") != 0 && strcmp(firstplayer, "x") != 0)
    {
        printf("Please enter either o or x  \n");
        printf("choose o or x : ");
        fflush(stdin);
        scanf("%s", firstplayer);
    }

    return firstplayer[0];
}

int generateRandomNumber()
{
    srand(time(NULL));
    int randomNumber = (rand() % 9) + 1;

    return randomNumber;
}

char getChoose(char a[3][3], char oneOrTwoPlayer, int turn)
{
    char *choose = (char *)malloc(50);
retry:
    fflush(stdin);
    if (oneOrTwoPlayer == 'o' && turn == 2)
    {
        // choose = "1\0"  or "2\0"
        int randomeNumer = generateRandomNumber();
        choose[0] = '0' + randomeNumer;
        choose[1] = '\0';
    }
    else
    {
        scanf("%s", choose);
    }

    // choose = "1 or "2" or "3"

    int value = atoi(choose);

    while (value < 1 || value > 9)
    {
        printf("Enter between 1 to 9 value ");
        goto retry;
    }

    int row = getRow(choose[0]);
    int colum = getcolum(choose[0]);

    // 1-9 already used
    if (a[row][colum] == 'x' || a[row][colum] == 'o')
    {
        if (oneOrTwoPlayer == 'o' && turn == 2)
        {
        }
        else
        {
            printf("Position already taken. Choose another one.\n");
        }

        goto retry;
    }

    return choose[0];
}

char wantToPlayMatchAgain()
{

    char *again = (char *)malloc(50);
    fflush(stdin);
    printf("Do you want to play again ? \n (Use yes for y and no for n)");
    scanf("%s", again);
    while (strcmp(again, "y") != 0 && strcmp(again, "n") != 0)
    {
        printf("Please enter y or n\n");
        fflush(stdin);
        printf("Do you want to play again ? \n (Use yes for y and no for n)");
        scanf("%s", again);
    }
    return again[0]; // 'n'
}

char onePlayerOrTwoPlayer()
{
    char *again = (char *)malloc(50);
    fflush(stdin);
    printf("Please enter o or t \n (use o for one player and t for two player )");
    scanf("%s", again);

    while (strcmp(again, "o") != 0 && strcmp(again, "t") != 0)
    {
        printf("Please enter o or t \n (use o for one player and t for two player )");
        fflush(stdin);
        scanf("%s", again);
    }
    return again[0]; // 'n'
}

int main()
{
    char welcome[] =
        " _    _      _                          \n"
        "| |  | |    | |                         \n"
        "| |  | | ___| | ___ ___  _ __ ___   ___ \n"
        "| |\\/| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\\n"
        "\\  /\\  /  __/ | (_| (_) | | | | | |  __/\n"
        " \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|\n"
        "                                        \n";

    char a[3][3];

    initBoard(a);
    printf("%s", welcome);

    char oneOrTwoPlayer = onePlayerOrTwoPlayer(); //  "o" -> one player "t" -> two player

    displayBoard(a);
    char firstplayer, secondplayer;
    firstplayer = choose();
    if (firstplayer == 'o')
    {
        secondplayer = 'x';
    }
    else
    {
        secondplayer = 'o';
    }

    char wantToPlay = 'y';

    int turn = 1;
    char choose;
    do
    {

        playerTurnPrint(turn, oneOrTwoPlayer);
        choose = getChoose(a, oneOrTwoPlayer, turn);

        int row = getRow(choose);
        int colum = getcolum(choose);

        if (turn == 1)
        {
            a[row][colum] = firstplayer;
        }
        else
        {
            a[row][colum] = secondplayer;
        }

        displayBoard(a);

        // check if won / draw

        int wonCondition = checkBoard(a);

        if (wonCondition == 1)
        {
            printWon(turn, oneOrTwoPlayer);
            turn = 1;

            initBoard(a);

            wantToPlay = wantToPlayMatchAgain();
            displayBoard(a);
            continue;
            // ask want to play
        }
        else if (wonCondition == 2)
        {
            // match draw
            printf("Match is draw\n");
            turn = 1;

            initBoard(a);

            wantToPlay = wantToPlayMatchAgain();
            displayBoard(a);
            continue;
            // ask want to play
        }

        turn = changeTurn(turn);

    } while (wantToPlay == 'y');

    char thankyou[] =
        " ____ _                 _                        \n"
        "|_   _| |               | |                       \n"
        "  | | | |__   __ _ _ __ | | __  _   _  ___  _   _ \n"
        "  | | | '_ \\ / _` | '_ \\| |/ / | | | |/ _ \\| | | |\n"
        "  | | | | | | (_| | | | |   <  | |_| | (_) | |_| |\n"
        "  \\_/ |_| |_|\\__,_|_| |_|_|\\_\\  \\__, |\\___/ \\__,_|\n"
        "                                 __/ |             \n"
        "                                |___/              \n";

    printf("%s", thankyou);
}
