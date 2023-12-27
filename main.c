#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1001
#define SIZE 25
int N = 10; // LIMIT FOR NUMBER TEAMS
size_t L = 20; //LIMIT FOR LENGTH NAME
struct magician { // INITIALIZE STRUCT
    char name[SIZE];
    int team;
    int power;
    int visibility;
}players[MAX];
int tea = 0;
void reducetestr(char c[]){ // reduce string
    if (c[strlen(c) - 1] == '\n') {
        c[strlen(c) - 1] = '\0';
    }
}
int checkingWord(char s[]){ // THIS FUNCTION CHECK LETTERS AND LENGTH IN NAMES
    int flag = 1;
    if ((strlen(s) >  L)||(strlen(s) < 2)){ // interval for length of names
        flag = 0;
    }
    if (s[0] < 65 || s[0] > 90){ // 65 IS 'A' FROM ASCII AND 90 IS 'Z' TOO
        flag = 0;
    }
    if (flag == 1) {
        for (size_t i = 1; i < strlen(s); i++) {
            if ((s[i] < 65 && s[i] > 90)  || (s[i] < 97 && s[i] > 122) || s[i] == '\0' || s[i] == '\n') {
                flag = 0;
                break;
            }
        }
    }
    return flag;
}
void result(int n, int m, int k) { // CALCULATE RESULT OF THE WIZARD OF THE TEAM WHICH HAS THE GREATEST POWER
    int powers[n];
    memset(powers, 0, sizeof(powers));
    for (int i = 0; i < m + k+1; i++) {
        powers[players[i].team] += players[i].power;
    }
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (powers[i] > max) {
            max = powers[i];
            tea = i;
        }
    }
    int k1 = 0;
    for (int i = 0; i < n; i++) {
        if (powers[i] == max) {
            k1++;
        }
    }
    if (k1 > 1) { // IF MORE ONE TEAM HAVE THE GREATEST POWER
        tea = -1;
    }
}
int main() {
    FILE *fo, *fc;
    fo = fopen("input.txt", "r"); // OPEN FILE FOR READ
    fc = fopen("output.txt", "w"); // OPEN FILE FOR WRITE
    short flag = 1; // THIS FLAG IS NECESSARY TO UNDERSTAND WHETHER THERE ARE ERRORS IN OUR FILE OR NOT
    int n; // COUNT OF TEAMS
    char num[SIZE];
    fgets(num, SIZE, fo);
    reducetestr(num);
    n = atoi(num); //TRANSLATION FROM A STRING TO A NUMBER
    if (n < 1 || n > 10) {
        flag = 0;
    } else {
        char names[n][SIZE]; // ARRAY OF TEAM NAMES
        char name[SIZE];
        for (int i = 0; i < n; i++) {
            fgets(name, SIZE, fo);
            reducetestr(name);
            if (checkingWord(name) == 0) { // INCORRECT INPUT WORD
                flag = 0;
                break;
            } else {
                strcpy(names[i], name); // COPY STRING IN ARRAY NAMES
            }
        }
        int m; // NUMBER OF PLAYERS
        char mnum[SIZE];
        fgets(mnum, SIZE, fo);
        m = atoi(mnum); //TRANSLATION FROM A STRING TO A NUMBER
        if (m > 100 || m < n) {
            flag = 0;
        } else {
            char team[SIZE]; // ARRAY OF CHARS FOR INPUT TEAM
            char power[SIZE]; // ARRAY OF CHARS FOR INPUT POWER
            char visibility[SIZE];// ARRAY OF CHARS FOR INPUT VISIBILITY
            for (int i = 0; i < m; i++) {
                fgets(name, SIZE, fo);
                reducetestr(name);
                if (checkingWord(name) == 0) {// INCORRECT INPUT WORD
                    flag = 0;
                    break;
                }
                strcpy(players[i].name, name); // COPY NAME IN STRUCT .NAME                }
                fgets(team, SIZE, fo);
                reducetestr(team);
                int nn;
                nn = atoi(team); //TRANSLATION FROM A STRING TO A NUMBER
                if (nn >= N || nn < 0) { // CHECK LIMIT  FOR NUMBER OF TEAM
                    flag = 0;
                    break;
                }
                players[i].team = nn; // COPY NUMBER TEAM IN STRUCT .TEAM
                fgets(power, SIZE, fo);
                reducetestr(power);
                int p;
                p = atoi(power);// TRANSLATION FROM A STRING TO A NUMBER
                if (p > 1000 || p < 0) { // CHECK LIMIT FOR OF POWER
                    flag = 0;
                    break;
                }
                players[i].power = p; // COPY POWER IN STRUCT .POWER
                fgets(visibility, SIZE, fo);
                reducetestr(visibility);
                if ((strcmp(visibility, "True") != 0) &&
                    (strcmp(visibility, "False") != 0)) { // CHECK THAT INPUT STRING IS VISIBILITY
                    flag = 0;
                    break;
                }
                if (strcmp(visibility, "True") == 0)
                    players[i].visibility = 1; // COPY VISIBILITY IN STRUCT .VISIBILITY
                else players[i].visibility = 0;
            }
            if (flag == 1) {
                char actions[SIZE]; // ARRAY OF CHARS FOR ACTIONS
                int k = 0; // NUMBER K FOR SUPER PLAYER
                int count = 0; // QUANTITY FOR ACTION
                char name1[SIZE]; // ARRAY OF CHARS FOR NAME
                char name2[SIZE]; // ARRAY OF CHARS FOR NAME
                while (fscanf(fo, "%s\n", actions) != EOF) { // READ STRINGS FROM FILE WHILE FILE IS NOT EMPTY
                    count++; // +1 COUNT ACTIONS
                    reducetestr(actions);
                    if (strcmp("flip_visibility", actions) != 0 && strcmp("attack", actions) != 0 && strcmp("heal", actions) != 0 && strcmp("super", actions) != 0) { //CHECK THAT INPUT STRING IS ACTION
                        flag = 0;
                        break;
                    }
                    if (strcmp("flip_visibility", actions) == 0) { // IF ACTION IS FLIP_VISIBILITY
                        fscanf(fo, "%s\n", name1); // WRITE FIRST NAME IN NAME1
                        short flag3 = 1;
                        for (int i = 0; i < m + k; i++) { // SEARCH NAME IN STRUCT
                            if (strcmp(players[i].name, name1) == 0) { // IF NAME WAS FOUND
                                flag3 = 0;
                                if (players[i].power == 0) { // IF PLAYER IS FROZEN
                                    fprintf(fc, "%s\n", "This player is frozen");
                                    break;
                                } else {
                                    if (players[i].visibility == 1) players[i].visibility = 0; // FLIP_VISIBILITY
                                    else players[i].visibility = 1;
                                    break;
                                }
                            }
                        }
                        if (flag3 == 1) { // NAME WAS FOUND
                            flag = 0;
                            break;
                        }
                    } else if (strcmp("attack", actions) == 0) { // IF ACTION IS ATTACK
                        fscanf(fo, "%s\n%s\n", name1, name2); // WRITE FIRST AND SECOND NAMES IN NAME1 AND NAME2
                        int player1 = 0, player2 = 0, pow1 = 0, pow2 = 0, flag1 = 1, flag2 = 1;
                        for (int i = 0; i < m + k; i++) {  // SEARCH NAMES IN STRUCT
                            if ((strcmp(players[i].name, name1) == 0) && flag1 == 1) { //IF NAME1 WAS FOUND
                                player1 = i;
                                pow1 = players[i].power;
                                flag1 = 0;
                            }
                            if ((strcmp(players[i].name, name2) == 0) && flag2 == 1) {// IF NAME2 WAS FOUND
                                player2 = i;
                                pow2 = players[i].power;
                                flag2 = 0;
                            }
                            if (flag1 == 0 && flag2 == 0) { // IF NAMES WERE FOUND
                                break;
                            }
                        }
                        if (flag1 == 1 || flag2 == 1) {// IF NAMES WERE NOT FOUND
                            flag = 0;
                            break;
                        }
                        if (players[player1].visibility == 0) // CHECK THAT FIRST PLAYER IS NOT VISIBILITY
                            fprintf(fc, "%s\n", "This player can't play");
                        else if (players[player1].power == 0) { // CHECK THAT FIRST PLAYER IS FROZEN
                            fprintf(fc, "%s\n", "This player is frozen");
                        } else {
                            if (players[player2].visibility == 0) { // IF SECOND PLAYER IS NOT VISIBILITY THEN FIRST IS FROZEN
                                players[player1].power = 0;
                            } else if (pow1 > pow2) { //THE STRENGTH OF THE FIRST PLAYER IS GREATER THAN THE SECOND
                                players[player1].power += pow1 - pow2;
                                players[player2].power = 0;
                            } else if (pow1 < pow2) {//THE STRENGTH OF THE SECOND PLAYER IS GREATER THAN THE FIRST
                                players[player2].power += pow2 - pow1;
                                players[player1].power = 0;
                            } else if (pow1 == pow2) { // THE STRENGTH OF THE SECOND PLAYER EQUAL TO THE FIRST
                                players[player2].power = 0;
                                players[player1].power = 0;
                            }
                            if (players[player1].power > 1000) // CHECK THAT FIRST POWER IS GREATER THAN 1000, THEN FIRST POWER EQUAL TO 100
                                players[player1].power = 1000;
                            if (players[player2].power > 1000)// CHECK THAT SECOND  POWER IS GREATER THAN 1000, THEN SECOND POWER EQUAL TO 100
                                players[player2].power = 1000;
                        }
                    } else if (strcmp("heal", actions) == 0) { // IF ACTION IS HEAL
                        fscanf(fo, "%s\n%s\n", name1, name2);  // WRITE FIRST AND SECOND NAMES IN NAME1 AND NAME2
                        int player1 = 0, player2 = 0, flag1 = 1, flag2 = 1;
                        for (int i = 0; i < m + k; i++) { // SEARCH NAMES IN STRUCT
                            if ((strcmp(players[i].name, name1) == 0) && flag1 == 1) { // IF NAME1 WAS FOUND
                                player1 = i;
                                flag1 = 0;
                            }
                            if ((strcmp(players[i].name, name2) == 0) && flag2 == 1) { // IF NAME2 WAS FOUND
                                player2 = i;
                                flag2 = 0;
                            }
                            if (flag1 == 0 && flag2 == 0) { // IF NAMES WERE FOUND
                                break;
                            }
                        }
                        if (flag1 == 1 || flag2 == 1) { // IF NAMES WERE NOT FOUND
                            flag = 0;
                            break;
                        }
                        if (players[player1].visibility == 0)// CHECK THAT FIRST PLAYER IS NOT VISIBILITY
                            fprintf(fc, "%s\n", "This player can't play");
                        else if (players[player1].power == 0)// CHECK THAT FIRST PLAYER IS FROZEN
                            fprintf(fc, "%s\n", "This player is frozen");
                        else if (players[player1].team != players[player2].team) { // CHECKING THAT BOTH PLAYERS ARE NOT FROM THE SAME TEAM
                            fprintf(fc, "%s\n", "Both players should be from the same team");
                        } else if (strcmp(players[player1].name, players[player2].name) == 0) { // CHECKING THAT BOTH PLAYERS HAVE THE SAME NAMES
                            fprintf(fc, "%s\n", "The player cannot heal itself");
                        } else { // IN THIS SITUATION WE CAN FIRST PLAYER CAN HEAL SECOND
                            int tmp;
                            tmp = (players[player1].power + (players[player1].power % 2)) / 2;
                            players[player1].power = (players[player1].power + (players[player1].power % 2)) / 2; //
                            players[player2].power += tmp;
                        }
                        if (players[player1].power > 1000)// CHECK THAT FIRST POWER IS GREATER THAN 1000, THEN FIRST POWER EQUAL TO 100
                            players[player1].power = 1000;
                        if (players[player2].power > 1000)// CHECK THAT SECOND  POWER IS GREATER THAN 1000, THEN SECOND POWER EQUAL TO 100
                            players[player2].power = 1000;
                    } else if (strcmp("super", actions) == 0) { // IF ACTION IS SUPER
                        fscanf(fo, "%s\n%s\n", name1, name2); // WRITE FIRST AND SECOND NAMES IN NAME1 AND NAME2
                        int player1 = 0, player2 = 0, flag1 = 1, flag2 = 1;
                        for (int i = 0; i < m + k; i++) {
                            if ((strcmp(players[i].name, name1) == 0) && flag1 == 1) {
                                player1 = i;
                                flag1 = 0;
                            }
                            if ((strcmp(players[i].name, name2) == 0) && flag2 == 1) {
                                player2 = i;
                                flag2 = 0;
                            }
                            if (flag1 == 0 && flag2 == 0) {
                                break;
                            }
                        }
                        if (flag1 == 1 || flag2 == 1) {
                            flag = 0;
                            break;
                        }
                        if (players[player1].visibility == 0)// CHECK THAT FIRST PLAYER IS NOT VISIBILITY
                            fprintf(fc, "%s\n", "This player can't play");
                        else if (players[player1].power == 0)// CHECK THAT FIRST PLAYER IS FROZEN
                            fprintf(fc, "%s\n", "This player is frozen");
                        else if (players[player1].team != players[player2].team)// CHECKING THAT BOTH PLAYERS ARE NOT FROM THE SAME TEAM
                            fprintf(fc, "%s\n", "Both players should be from the same team");
                        else if (strcmp(players[player1].name, players[player2].name) == 0)// CHECKING THAT BOTH PLAYERS HAVE THE SAME NAMES
                            fprintf(fc, "%s\n", "The player cannot do super action with itself");
                        else {
                            sprintf(players[m + k].name, "%s%d", "S_", k); // CREATE NEW SUPER PLAYER IN STRUCT
                            players[m + k].power = players[player1].power + players[player2].power; //ADDITION POWER TO NEW SUPER PLAYER
                            players[player1].power = 0; // AFTER ADDITION SUPER PLAYER IN STRUCT WE SHOULD DELETE OLDER PLAYERS FROM STRUCT
                            players[player2].power = 0;// AFTER ADDITION SUPER PLAYER IN STRUCT WE SHOULD DELETE OLDER PLAYERS FROM STRUCT
                            strcpy(players[player1].name, "\0");// AFTER ADDITION SUPER PLAYER IN STRUCT WE SHOULD DELETE OLDER PLAYERS FROM STRUCT
                            strcpy(players[player2].name, "\0");// AFTER ADDITION SUPER PLAYER IN STRUCT WE SHOULD DELETE OLDER PLAYERS FROM STRUCT
                            if (players[m + k].power > 1000) players[m + k].power = 1000; // CHECK THAT SUPER PLAYER POWER IS GREATER THAN 1000, THEN SUPER PLAYER POWER EQUAL TO 100
                            players[m + k].team = players[player1].team; // COPY TEAM OLDER PLAYERS FOR SUPER PLAYER
                            players[m + k].visibility = 1; // WRITE TRUE VISIBILITY FOR SUPER PLAYER
                            k++; // ADD 1 FOR NEXT SUPER PLAYER
                        }
                    }
                    if (count > 1000) { // // CHECK THAT THE NUMBER OF ACTIONS IS GREATER THAN 1000
                        flag = 0;
                        break;
                    }
                }
                result(n, m, k); // CALCULATE RESULT
                if (tea == -1) { // IF MORE ONE TEAM HAVE THE GREATEST POWER
                    fprintf(fc, "%s\n", "It's a tie");
                } else { // ELSE WE PRINT WINNER TEAM
                    fprintf(fc, "%s %s\n", "The chosen wizard is", names[tea]);
                }
            }
        }
    }
    fclose(fo);
    if (flag == 0) { // IF INPUT WORDS IS INCORRECT
        fclose(fc);
        fc = fopen("output.txt", "w");
        fprintf(fc, "%s\n", "Invalid inputs"); // PRINT "INVALID INPUTS
    }
    fclose(fc);
}