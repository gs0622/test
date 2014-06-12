#include <stdio.h>

static char square[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
static char symbol[2] = {'O', 'X'};

static void board(void)
{
    int i;
    for (i=0;i<3;i++)
            printf("\t%c\t%c\t%c\n", square[i][0], square[i][1], square[i][2]);
}

static int check(void)
{
    int i;
    for (i=0;i<3;i++) {
        if (square[i][0]==square[i][1] && square[i][1]==square[i][2]) return 1;
        if (square[0][i]==square[1][i] && square[1][i]==square[2][i]) return 1;
    }
    if (square[0][0]==square[1][1] && square[1][1]==square[2][2]) return 1;
    if (square[2][0]==square[1][1] && square[1][1]==square[0][2]) return 1;
    return 0;
}

int main(int argc, char **argv)
{
    int n, t;
    for (t=0, board(); t<9;) {
        printf("player %c enter place: ", symbol[t%2]);
        if (scanf("%d", &n)==1 && n>0 && n<10) {
            n-=1, square[n/3][n%3] = symbol[t%2];
            board();
            if (check()) {
                printf("player %c win\n", symbol[t%2]);
                break;
            }
            t++;
        }
    }
    return 0;
}
