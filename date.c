#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

typedef struct customDate {
    char *date;
    char *naturalDate;
    int year;
    int month;
    int day;
    long unsigned int hash;
} CustomDate;

CustomDate *convertDate(const char *date);
char *getNaturalDate(const CustomDate const *customDate);
//genero un hash unico por cada fecha, lo uso para busquedas binarias
long unsigned int *generataHashOfDate(const CustomDate const *customDate);

char *listMonth[12] ={
		"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio",
		"agosto", "septiembre", "octubre", "noviembre", "diciembre"
};

int daysOfMonth[12] = {31, 28, 31, 30, 31, 30, 31, 30, 30, 31, 30, 31};

void testDates() {
    char *date = "8-7-2020";
	CustomDate *structDate = convertDate(date);

    printf("date: %s\n", structDate->date);
    printf("natural date: %s\n", structDate->naturalDate);
    printf("hash: %lu\n", structDate->hash);
}

CustomDate *convertDate(const char *date) {

    CustomDate *customDate = malloc(sizeof(CustomDate));
    customDate->naturalDate = malloc(sizeof(char) * 50);

    char *tmpDate = malloc(sizeof(strlen(date)) * 12);
    strcpy(tmpDate, date);
    
    char *stringDate = malloc(sizeof(char) * 40);
    int i=0;

	if(strlen(date) > 10)
		return NULL;
		
    //valido que los dias sean digitos
    char *token = strtok(tmpDate, "-");
    int lengthToken = strlen(token);
    for(i=0; i<lengthToken; i++) 
        if(!isdigit(token[i]))
            return NULL;

    int day = atoi(token);

    //valido que los meses sean digitos
    token = strtok(NULL, "-");
    lengthToken = strlen(token);
    for(i=0; i<lengthToken; i++) 
        if(!isdigit(token[i]))
            return NULL;

	int month = atoi(token);

    //mesess fuera de rango
    if(month == 0 || month > 12)
        return NULL;

    //dias fuera de rango
    if(day > daysOfMonth[month - 1] && month != 2)
        return NULL;

    //valido que los years sean digitos
	token = strtok(NULL, "-");
    lengthToken = strlen(token);
    for(i=0; i<lengthToken; i++)
        if(!isdigit(token[i]))
            return NULL;

	int year = atoi(token);

    //valido year bisiesto
    if(month == 2) {
        //febrero de 29 dias
        if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
            if(day > 29) 
                return NULL;
        }
        //febrero de 28 dias
        else if(day > 28) {
            return NULL;
        }
    }

    customDate->year = year;
    customDate->month = month;
    customDate->day = day;
    customDate->date = date;
    customDate->hash = generataHashOfDate(customDate);
    customDate->naturalDate = getNaturalDate(customDate);
    return customDate;
}

char *getNaturalDate(const CustomDate const *customDate) {
    char *naturalDate = malloc(sizeof(char) * 50);
    sprintf(naturalDate, "%d de %s de %d", customDate->day, listMonth[customDate->month - 1], customDate->year);
    return naturalDate;
}

long unsigned int *generataHashOfDate(const CustomDate const *customDate) {
    return (long) (pow(customDate->year / 2.0, 2) + pow(customDate->month + 1, 3) + customDate->day + 1);
}

CustomDate *now() {
	time_t t = time(NULL);
	struct tm *tm;
	tm = localtime(&t);

    char *date = malloc(sizeof(char) * 10);
    sprintf(date, "%d-%d-%d",  tm->tm_mday,  tm->tm_mon + 1, tm->tm_year + 1900);

    CustomDate *today = convertDate(date);
    return today;
}
