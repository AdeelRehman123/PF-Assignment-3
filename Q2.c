#include <stdio.h>
#include <string.h>

struct Player {
    int ballScores[12];
    char playerName[50];
    int totalScore;
};

void playGame(struct Player *player);
int validateScore(int score);
void findWinner(struct Player player1, struct Player player2);
void displayMatchScoreboard(struct Player player1, struct Player player2);

void playGame(struct Player *player) {
    for (int i = 0; i < 12; i++) {
        int score;
        printf("Enter score for ball %d: ", i + 1);
        scanf("%d", &score);

        if (validateScore(score)) {
            player->ballScores[i] = score;
            player->totalScore += score;
        } else {
            player->ballScores[i] = 0;
            printf("Invalid score! Score must be between 0 and 6. This ball is marked as 0.\n");
        }
    }
}

int validateScore(int score) {
    return (score >= 0 && score <= 6);
}

void findWinner(struct Player player1, struct Player player2) {
    printf("\nMatch Result:\n");
    if (player1.totalScore > player2.totalScore) {
        printf("%s wins with %d runs!\n", player1.playerName, player1.totalScore);
    } else if (player2.totalScore > player1.totalScore) {
        printf("%s wins with %d runs!\n", player2.playerName, player2.totalScore);
    } else {
        printf("It's a tie! Both players scored %d runs.\n", player1.totalScore);
    }
}

void displayMatchScoreboard(struct Player player1, struct Player player2) {
    printf("\nMatch Scoreboard:\n");

    printf("\n%s's Scores:\n", player1.playerName);
    for (int i = 0; i < 12; i++) {
        printf("Ball %d: %d\n", i + 1, player1.ballScores[i]);
    }
    printf("Total Score: %d\n", player1.totalScore);
    printf("Average Score: %.2f\n", player1.totalScore / 12.0);

    printf("\n%s's Scores:\n", player2.playerName);
    for (int i = 0; i < 12; i++) {
        printf("Ball %d: %d\n", i + 1, player2.ballScores[i]);
    }
    printf("Total Score: %d\n", player2.totalScore);
    printf("Average Score: %.2f\n", player2.totalScore / 12.0);
}


int main() {
    struct Player player1;
    struct Player player2;

    char p1[50];
    char p2[50];
    printf("Enter Player 1 Name(Without Gap):");
    scanf("%s", p1);
    printf("Enter Player 2 Name(Without Gap):");
    scanf("%s", p2);

    strcpy(player1.playerName, p1);
    player1.totalScore = 0;
    strcpy(player2.playerName, p2);
    player2.totalScore = 0;

    printf("Welcome to 2 Overs Cricket Match!\n\n");

    printf("%s's turn:\n", player1.playerName);
    playGame(&player1);

    printf("\n%s's turn:\n", player2.playerName);
    playGame(&player2);

    char ans;
    getchar();
    printf("Do You Want To See Winner(Y,y for Yes):");
    scanf("%c", &ans);

    if (ans == 'y' || ans == 'Y') {
        findWinner(player1, player2);
        printf("\n");

        char ans2;
        getchar(); 
        printf("Do You Want To See Score(Y,y for Yes): ");
        scanf("%c", &ans2);

        if (ans2 == 'y' || ans2 == 'Y') {
            displayMatchScoreboard(player1, player2);
        }
    }
    return 0;
}

