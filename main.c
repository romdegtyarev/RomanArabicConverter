#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Global constants */
#define ronamDigitCount    9
#define numberLen          80


/* Global Internal Struts */
typedef struct romanArabDigits {
    char    romanDigit;
    int     arabDigit;
} romanArabDigits_t;


/* Global Internal Variables */
romanArabDigits_t    romanArabDigitsArray[] = {
    {'I', 1},
    {'V', 5},
    {'X', 10},
    {'L', 50},
    {'C', 100},
    {'D', 500},
    {'M', 1000},
    {'(', -1},
    {')', -2}
};


int checkNumber(char *, int *);
int convertNumber(int *, int);


int main (int argc, char **argv) {
    /* Local variables */
    char    romanNumber_STR[numberLen] = {0};
    int     romanNumber[numberLen] = {0};
    int     digitCount = 0;
    int     arabNumber = 0;
    /* Function Logic */
    while (!digitCount) {                                           /* while (1) {*/
        printf("Enter Roman number: ");                             /* Введите римское число */
        scanf("%80s", romanNumber_STR);                             /* Считывем */
        digitCount = checkNumber(romanNumber_STR, romanNumber);     /* Функция, которая проверяет строку и записывает цифры в десячиной системе */
        if (digitCount) {                                           /* Функиця перевода десячиных цифр римского в арабское число */
            arabNumber = convertNumber(romanNumber, digitCount);
            if (arabNumber == 0) {
                digitCount = 0;
            }
            printf("\nYour Number is: %s in Arab: %d", romanNumber_STR, arabNumber);
        }
    }
    return (0);
}

int checkNumber(char *romanNumber_STR, int *romanNumber) {
    /* Local variables */
    int romanNumberLen = 0;
    int i, j;
    int findDigit = 0;
    /* Function Logic */
    romanNumberLen = strlen(romanNumber_STR);                                                         /* Считаем длину введенной строки */
    printf("checkNumber: Number Len is: %d\n", romanNumberLen);
    for (i = 0; i < romanNumberLen; i++) {                                                            /* Проходимся по всем цифрам римского числа */
        for (j = 0; j < ronamDigitCount; j++) {                                                       /* Сравниваем текущую цифру со всеми возможными */
            printf("STR1: %c STR2: %c\n", romanNumber_STR[i], romanArabDigitsArray[j].romanDigit);
            if (romanNumber_STR[i] == romanArabDigitsArray[j].romanDigit) {
                printf("checkNumber: Compare OK: %c\n", romanNumber_STR[i]);
                findDigit = 1;                                                                        /* Нашли совпадение в массиве возможных римских цифр */
                romanNumber[i] = romanArabDigitsArray[j].arabDigit;                                   /* Записали десячиное значение числа */
                break;
            }
        }
        if (!findDigit) {
            printf("checkNumber: Compare NOT OK: %c\n", romanNumber_STR[i]);
            return (0);
        }
        findDigit = 0;
    }
    return (romanNumberLen);
}

int convertNumber(int *romanNumber, int digitCount) {
    /* Local variables */
    int i;
    int arabNumber = 0;
    int digitRepeat = 0;
    int thousand = 0;
    int thousandNumber = 0;
    /* Function Logic */
    if (romanNumber[digitCount - 1] == -2) {
        thousand++;
    } else {
        arabNumber = romanNumber[digitCount - 1];
    }
    for (i = digitCount - 2; i >= 0; i--) {
        printf("convertNumber: %d sum arab: %d sum th: %d\n", romanNumber[i], arabNumber, thousandNumber);
        if (romanNumber[i] == -2) {
            thousand++;
        } else if (romanNumber[i] == -1) {
            thousandNumber = thousandNumber * 1000;
            arabNumber = arabNumber + thousandNumber;
            thousand--;
            printf("Arab after th: %d\n", arabNumber);
        } else if (romanNumber[i] > romanNumber[i + 1]) {
            if (!thousand) {
                arabNumber = arabNumber + romanNumber[i];
            } else {
                thousandNumber = thousandNumber + romanNumber[i];
            }
            digitRepeat = 0;
        } else if (romanNumber[i] < romanNumber[i + 1]) {
            if (!thousand) {
                arabNumber = arabNumber - romanNumber[i];
            } else {
                thousandNumber = thousandNumber - romanNumber[i];
            }
            digitRepeat = 0;
        } else if (romanNumber[i] == romanNumber[i + 1]) {
            if (!thousand) {
                arabNumber = arabNumber + romanNumber[i];
            } else {
                thousandNumber = thousandNumber + romanNumber[i];
            }
            digitRepeat++;
        } else {
            printf("convertNumber: Error in sequence in position: %d and %d\n", i + 1, i + 2);
            arabNumber = 0;
            break;
        }
        if (digitRepeat == 3) {
            printf("convertNumber: Error in sequence. Repeat digit more than 3 times in position: %d-%d-%d-%d\n", i + 1, i + 2, i + 3, i + 4);
            arabNumber = 0;
            break;
        }
    }
    if (thousand) {
        printf("convertNumber: Error in sequence. Illegal number of (");
    }
    return (arabNumber);
}


