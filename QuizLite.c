#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int marks = 0, right = 0, wrong = 0; //global static variables

//function prototypes
void load(int lineNumber, char *lineData);
void parseOption(char *line, int *ans, int an);
void checkAns(int *input, int* ans);

//main function
int main(){
    printf ("**Welcome to QuizLite!**\nDo you want to start quiz? [Y/n]: ");
    char line[256];
    int q, a, qn, an, ans;
    int input;
    qn = 0;
    q = 1;
    while (getch()!= 'n' && q<27){
        system("cls");  //clear screen after every question
        printf ("QuizLite\n--------\n");
        load(q, line);  //load question to character array line
        printf("\n[%d] %s\n",++qn, line);   //print character array line
        an = 0;
        //load options
        for (a=q+1;a<q+5;a++){
            memset (line, '\0', 256);   //to clear character array line
            load(a, line);  //load options to character array line
            parseOption(line, &ans, ++an);  //parse an option to check if right or wrong and print
        }
        printf("\n> ");
        scanf("%d", &input);    //input answer
        checkAns(&input, &ans); //check answer
        q+=5;
        printf ("\nProceed to Next Question? [Y/n]: \n");
    }

    system("cls");  //clear screen before printing score
    printf ("QuizLite\n--------\n");
    printf ("\n\nYour score is:  %d\n", marks);
    printf ("[%d Correct, %d Wrong]", right, wrong);
    return 0;
}

//stores specific line data to a character pointer
void load(int lineNumber, char *lineData){
    static const char filename[] = "qa_data.data";  //location of file containing formatted questions and options
    FILE *file = fopen(filename, "r");  //open file in read-only mode
    int count = 1;
    if ( file != NULL ) {
        char line[256];
        while (fgets(line, sizeof line, file) != NULL) {
            if (count == lineNumber) {
                strcpy(lineData, line); //copies specific line to character pointer lineData
                fclose(file);
            }
            else {
                count++;
                }
            }
        fclose(file);
        }
    else {
        strcpy(lineData, "Invalid File Request");   //if file is not found
  }
}

//checks if an option is right answer or not and print the options
void parseOption(char *line, int *ans, int an){
    int i;
    //search for '*' character before right answer
    if (line[0] == '*'){
        *ans = an;  //store the correct option number
    }

    printf ("(%d) ", an);   //print option number
    for (i=1;i<80;i++){
        putchar (line[i]);  //print option
    }
    printf("\n");
}

//checks if inputted answer is right or wrong.
void checkAns(int *input, int* ans){
    if (*input == *ans){
        marks+=10;
        right++;
        printf ("[Correct Answer]\n");
    }
    else {
        wrong++;
        printf("[Wrong Answer]\n");
        printf("Correct Answer is: %d\n", *ans);
    }
}

