typedef struct customDate {
    char *date;
    char *naturalDate;
    int year;
    int month;
    int day;
    long unsigned int hash;
} CustomDate;

CustomDate *convertDate(char *date);
char *getNaturalDate(CustomDate *customDate);