#include "game.h"

void displayCurrentPlayer(Player* p) {
    printf("%s [%d $]\t\t", (p->name), (p->currentTurnMoney));
}

void displayCurrentRound(int round) {
    printf("\033[1;31m\n################ ROUND %d ################\033[0m\n", round);
}

void loadingBar(int random) {
    printf("\n");
    random += 25;
    char load[27] = "[------------------------]";

    for (int i = 1; i < (random + 2); i++) {
        load[i % 25] = '|';

        printf("\r");
        for (int j = 0; j < 26; j++) {
            if (j == (i % 25))
                printf("\033[0m");
            else
                printf("\033[1;31m");
            printf("%c", load[j]);
        }
        Sleep(80);
        load[i % 25] = '-';
        if (i == 24) i++;
    }
    printf("\033[0m");
}

int compare(const Player* s1, const Player* s2) {
    Player* p1 = *(Player**)s1;
    Player* p2 = *(Player**)s2;

    if (p1->totalMoney < p2->totalMoney)
        return 1;
    else if (p1->totalMoney > p2->totalMoney)
        return -1;
    else
        return 0;
}

void endRound(Player** players, int playersNumber) {
    qsort(players, playersNumber, sizeof(Player*), compare);

    for (int i = 0; i < playersNumber; i++) {
        printf("\n %d. %s [%d $]", i + 1, players[i]->name, players[i]->totalMoney);
    }
    printf("\n\n");
}

void addMoney(Player* ptr_player, int money) {
    ptr_player->currentTurnMoney += money;
}

bool isVowel(char c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y')
        return true;
    return false;
}

int getOccurrence(char* puzzle, char* currentPuzzle, char c) {
    int occurrence = 0;

    for (int i = 0; i < strlen(puzzle); i++) {
        if (currentPuzzle[i] == '-' && tolower(c) == tolower(puzzle[i])) {
            occurrence++;
            c = puzzle[i] > 95 ? tolower(c) : toupper(c);
            currentPuzzle[i] = c;
        }
    }

    return occurrence;
}

bool buyVowel(Player* p, char* puzzle, char* currentPuzzle, char c) {
    p->currentTurnMoney -= 250;
    int occ = getOccurrence(puzzle, currentPuzzle, c);

    if (occ != 0) {
        printf("\nThere are %d '%c' in the puzzle!", occ, c);
        return true;
    }
    else {
        printf("\n%c is not in the puzzle.", c);
        return false;
    }
}

bool stringCompare(char* puzzle, char* guess) {
    for (int i = 0; i < strlen(guess); i++)
        if (tolower(puzzle[i]) != tolower(guess[i]))
            return false;
    return true;
}

int spinWheel(int wheel[]) {
    int random = rand() % 24;
    loadingBar(random);
    return wheel[random];
}

void hidePuzzle(char* currentPuzzle) {
    for (int i = 0; i < strlen(currentPuzzle); i++)
        if (currentPuzzle[i] != ' ')
            currentPuzzle[i] = '-';
    printf("\nThis will be the puzzle you need to guess: %s\n\n", currentPuzzle);
}

void displayPuzzle(char* currentPuzzle) {
    printf("\n\nCurrent Puzzle: %s\n", currentPuzzle);
}

bool onlyVowelsLeft(char* puzzle, char* currentPuzzle) {
    for (int i = 0; i < strlen(currentPuzzle); i++)
        if (currentPuzzle[i] == '-' && !isVowel(puzzle[i]))
            return false;
    return true;
}