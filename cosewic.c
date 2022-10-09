/* ****************************************************************************
                              Final Assessment
Full Name  : Rachit Chawla
Student ID#: 162759211
Email      : rchawla11@myseneca.ca
Section    : IPC144 ZDD

We declare this submission is the result of our own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of our own creation.
***************************************************************************** */

#include "cosewic.h"
//Datatypes used
struct place
{
    char province[50];
    char name[21];
    int extinct, extirpated, endangered, threatened, concern, total;
}place[13];

// Function to import data and return the number of records imported from the fil
int loadData(const char* datafile, struct FileData* data, int max)
{
    FILE* fp;
    fp = fopen(datafile, "r");
    int records = -1;
    if (fp != NULL)
    {
        while(records < max){
                    if(records == -1){
                        fscanf(fp, "%*s");
                    }
                    else
                    {
            fscanf(fp, "%d,%15[^,],%15[^,],%d,%2[^\n]\n",
                &data[records].year, data[records].taxon,
                data[records].status, &data[records].count,
                   data[records].province);
                    }
        {
            records++;
        }
        }}
    return records;
};

//UTILITY FUNCTIONS:
//Input a integer
int input_Int() {
    int keep_Going = 1;
    char nextCharactor = '\0';
    int Result = -1;

    do {
        scanf("%d%c", &Result, &nextCharactor);
        if (nextCharactor != '\n') {
            printf("Error! Input a whole number: ");
        }
        else {
            keep_Going = 0;
        }
    } while (keep_Going);
    return Result;
}

//Input a integer between a range
int int_Range(int Minim, int Maxim) {
    int result = Minim - 1;
        result = input_Int();
    printf("\n");
        if (result < Minim || result > Maxim) {
            printf("Invalid menu Selection!\n");
        }
    return result;
}
//Function to compare structs - We'll use it later while sorting the viewbyprovince function
int compare(const void  *a, const void *b)
{
    return (int)((*(struct place *)b).total - (*(struct place *)a).total);
}
//Main function with header and selections
void mainLogic(struct FileData* data,int records)
{
    int selection =1;
    while (selection!=0) {
        printf("=======================================================\n");
        printf("         Canada Species at Risk Analysis\n");
        printf("            (Data Years: 2010 - 2019)\n");
        printf("=======================================================\n");
        printf("1. View by year (sorted ASCENDING by year)\n");
        printf("2. View by province (sorted DESCENDING by totals)\n");
        printf("3. View by taxon (sorted ASCENDING by totals)\n");
        printf("4. View by province and taxon\n");
        printf("-------------------------------------------------------\n");
        printf("0. Exit\n");
        printf("-------------------------------------------------------\n");
        printf("Selection: ");
        selection = int_Range(0, 4);
        switch (selection) {
            case 1:
                viewbyyear(data, records);
                break;
            case 2:
                viewbyprovince(data, records);
                break;
            case 3:
                viewbytaxon(data, records);
                break;
            case 4:
                viewbyprovinceandtax(data, records);
                break;
        }
    }
    if (selection == 0) {
        printf("Application Terminated!\n");
    }

}
//View data by year sorted in acsending by year
void viewbyyear(struct FileData* data,int records)
{
    int extinct[10] = {0};
    int extirpated[10]= {0};
    int endangered[10]= {0};
    int threatened[10]= {0};
    int concern[10]= {0};
    int totalyear[10] = {0};
    int totalextinct=0,totalextirpated=0,totalendangered=0,totalthreatened=0,totalconcern=0,totalallyear=0;
    for(int i=0; i < records;i++)
        {
            for (int year=2010; year < 2020; year ++) {
                if (data[i].year == year) {
                    if (strcmp(data[i].status, "EXTINCT") == 0)
                    {
                        extinct[year-2010] += data[i].count;
                    }
                    else if (strcmp(data[i].status, "EXTIRPATED") == 0)
                    {
                        extirpated[year-2010] += data[i].count;
                    }
                    else if (strcmp(data[i].status, "ENDANGERED") == 0)
                    {
                        endangered[year-2010] += data[i].count;
                    }
                    else if (strcmp(data[i].status, "THREATENED") == 0)
                    {
                        threatened[year-2010] += data[i].count;
                    }
                    else if (strcmp(data[i].status, "SPECIAL CONCERN") == 0)
                    {
                        concern[year-2010] += data[i].count;
                    }
                }
            }
    }
    printf("YEAR EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN     TOTAL\n");
    printf("---- ------- ---------- ---------- ---------- ------- ---------\n");
    for (int i=0; i<10; i++) {
        totalextinct += extinct[i];
        totalextirpated += extirpated[i];
        totalendangered += endangered[i];
        totalthreatened += threatened[i];
        totalconcern += concern[i];
        totalyear[i]=extinct[i] + extirpated[i] + endangered[i] + threatened[i] + concern[i];
        totalallyear += totalyear[i];
        printf("%d    %d       %d       %d       %d    %d     %d\n",i+2010,extinct[i],extirpated[i],endangered[i],threatened[i],concern[i],totalyear[i]);
    }
        printf("     ------- ---------- ---------- ---------- ------- ---------\n");
        printf("       %d      %d      %d      %d   %d    %d\n\n",totalextinct,totalextirpated,totalendangered,totalthreatened,totalconcern,totalallyear);
};

//view data by province
void viewbyprovince(struct FileData* data, int records)
{
    int total[5] = {0};
    char provincefullname[13][21] = {"Alberta             ", "British Columbia    ", "Manitoba            ", "New Brunswick       ", "Newfoundland        ", "Nova Scotia         ", "Northwest Territory ", "Nunavut             ", "Ontario             ", "Prince Edward Island", "Quebec              ", "Saskatchewan        ", "Yukon Territory     "};
    char provinceshortname[13][3] = {"AB", "BC", "MB", "NB", "NL", "NS", "NT", "NU", "ON", "PE", "QC", "SK", "YT"};
    for (int i = 0; i < 13; i++)
    {
        strcpy(place[i].province, provinceshortname[i]);
        strcpy(place[i].name, provincefullname[i]);
        place[i].extinct = 0;
        place[i].extirpated = 0;
        place[i].endangered = 0;
        place[i].threatened = 0;
        place[i].concern = 0;
    }
    for (int i = 0; i < records; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (strcmp(data[i].province, place[j].province) == 0)
            {
                if (strcmp(data[i].status, "EXTINCT") == 0)
                {
                    place[j].extinct += data[i].count;
                }
                else if (strcmp(data[i].status, "ENDANGERED") == 0)
                {
                    place[j].endangered += data[i].count;
                }
                else if (strcmp(data[i].status, "EXTIRPATED") == 0)
                {
                    place[j].extirpated += data[i].count;
                }
                else if (strcmp(data[i].status, "SPECIAL CONCERN") == 0)
                {
                    place[j].concern += data[i].count;
                }
                else if (strcmp(data[i].status, "THREATENED") == 0)
                {
                    place[j].threatened += data[i].count;
                }
            }
        }
    }
    printf("PROVINCE             EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN     TOTAL\n");
    printf("-------------------- ------- ---------- ---------- ---------- ------- ---------\n");
    for (int i = 0; i < 13; i++)
    {
        place[i].total = place[i].extinct + place[i].extirpated + place[i].endangered + place[i].threatened + place[i].concern;
    }
    qsort(place, 13, sizeof(struct place), compare);
    for (int i = 0; i < 13; i++)
    {
        printf("%s %7d %10d %10d %10d %7d %9d\n",place[i].name,place[i].extinct,place[i].extirpated,place[i].endangered,place[i].threatened,place[i].concern,place[i].total);
        total[0] += place[i].extinct;
        total[1] += place[i].extirpated;
        total[2] += place[i].endangered;
        total[3] += place[i].threatened;
        total[4] += place[i].concern;
    }
    printf("-------------------- ------- ---------- ---------- ---------- ------- ---------\n");
    printf("                       %d      %d      %d      %d   %d    %d\n\n",total[0],total[1],total[2],total[3],total[4],total[0] + total[1] + total[2] + total[3] + total[4]);
};
void viewbyprovinceandtax(struct FileData* data, int records)
{
    int provincechoice, taxonchoice;
    char species[10][16] = {"Mammals", "Birds", "Reptiles", "Amphibians", "Fishes", "Arthropods", "Molluscs", "Vascular Plants", "Mosses", "Lichens"};
    char provincefullname[13][21] = {"Alberta             ", "British Columbia    ", "Manitoba            ", "New Brunswick       ", "Newfoundland        ", "Nova Scotia         ", "Northwest Territory ", "Nunavut             ", "Ontario             ", "Prince Edward Island", "Quebec              ", "Saskatchewan        ", "Yukon Territory     "};
    char provinceshortname[13][3] = {"AB", "BC", "MB", "NB", "NL", "NS", "NT", "NU", "ON", "PE", "QC", "SK", "YT"};
    int extinct = 0, extirpated = 0, endangered = 0, threatened = 0, concern = 0, total = 0;
    do
    {
        printf("\nChoose a Province\n----------------------------------\n 1) AB (Alberta)\n 2) BC (British Columbia)\n 3) MB (Manitoba)\n 4) NB (New Brunswick)\n 5) NL (Newfoundland)\n 6) NS (Nova Scotia)\n 7) NT (Northwest Territories)\n 8) NU (Nunavut)\n 9) ON (Ontario)\n10) PE (Prince Edward Island)\n11) QC (Quebec)\n12) SK (Saskatchewan)\n13) YT (Yukon Territory)\nSelection: ");
        provincechoice = int_Range(1, 13);
    }while(provincechoice <1 || provincechoice > 13);
    do
    {
        printf("\nChoose a Taxon\n---------------\n 1) Mammals\n 2) Birds\n 3) Reptiles\n 4) Amphibians\n 5) Fishes\n 6) Arthropods\n 7) Molluscs\n 8) Vascular Plants\n 9) Mosses\n10) Lichens\nSelection: ");
        taxonchoice = int_Range(1, 10);
    }while(taxonchoice < 1 || taxonchoice > 10);
    provincechoice--;
    taxonchoice--;
    for (int i = 0; i < records; i++)
    {
        if (strcmp(data[i].province, provinceshortname[provincechoice]) == 0 && strcmp(data[i].taxon, species[taxonchoice]) == 0)
        {
            if (strcmp(data[i].status, "EXTINCT") == 0)
            {
                extinct += data[i].count;
            }
            else if (strcmp(data[i].status, "EXTIRPATED") == 0)
            {
                extirpated += data[i].count;
            }
            else if (strcmp(data[i].status, "ENDANGERED") == 0)
            {
                endangered += data[i].count;
            }
            else if (strcmp(data[i].status, "THREATENED") == 0)
            {
                threatened += data[i].count;
            }
            else if (strcmp(data[i].status, "SPECIAL CONCERN") == 0)
            {
                concern += data[i].count;
            }
        }
    }
    total = extinct + extirpated + endangered + threatened + concern;
    printf("\n*** Data filtered by PROVINCE and TAXON ***\n\n");
    printf("    Province: %s\n", provincefullname[provincechoice]);
    printf("    Taxon   : %s\n", species[taxonchoice]);
    printf("EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN     TOTAL\n");
    printf("------- ---------- ---------- ---------- ------- ---------\n");
    printf("%7d %10d %10d %10d %7d %9d\n\n", extinct,extirpated,endangered,threatened,concern,total);
}
void viewbytaxon(struct FileData* data, int records)
{
        printf("View by taxon selected\n");
        printf("TAXON           EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN     TOTAL\n");
        printf("--------------- ------- ---------- ---------- ---------- ------- ---------\n");
        struct TaxonStruct taxonData[10] = {{0}};
        taxonData[0].taxon = "Molluscs";
        taxonData[1].taxon = "Lichens";
        taxonData[2].taxon = "Amphibians";
        taxonData[3].taxon = "Vascular Plants";
        taxonData[4].taxon = "Reptiles";
        taxonData[5].taxon = "Mammals";
        taxonData[6].taxon = "Arthropods";
        taxonData[7].taxon = "Mosses";
        taxonData[8].taxon = "Birds";
        taxonData[9].taxon = "Fishes";
    
        int Total = 0,totalExtinct=0,totalExtirpated=0,totalThreadtened=0,totalEndangered=0,totalConcern=0;
    
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < records; j++ ){
                if(!strcmp(data[j].taxon, taxonData[i].taxon)){
                    if(!strcmp("EXTINCT", data[j].status)){
                        taxonData[i].extinct += data[j].count;
                    }
                    else if(!strcmp("EXTIRPATED", data[j].status)){
                        taxonData[i].extirpated += data[j].count;
                    }
                    else if(!strcmp(data[j].status, "THREATENED")){
                        taxonData[i].threatened += data[j].count;
                    }
                    else if(!strcmp(data[j].status, "ENDANGERED")){
                        taxonData[i].endangered += data[j].count;
                    }
                    else if(!strcmp(data[j].status, "SPECIAL CONCERN")){
                        taxonData[i].concern += data[j].count;
                    }
        
                }
            }
            taxonData[i].total = taxonData[i].extinct + taxonData[i].extirpated + taxonData[i].threatened + taxonData[i].concern + taxonData[i].endangered;
            totalExtinct += taxonData[i].extinct;
            totalExtirpated += taxonData[i].extirpated;
            totalThreadtened += taxonData[i].threatened;
            totalEndangered += taxonData[i].endangered;
            totalConcern += taxonData[i].concern;
            Total += taxonData[i].total;
        }
    
        //sorting in ascending order
        struct TaxonStruct temp[10];
        for(int i = 0;i < 10; i++){
            for(int j = i+1; j < 10; j++){
                if(taxonData[j].total < taxonData[i].total){
                    temp[j] = taxonData[j];
                    taxonData[j] = taxonData[i];
                    taxonData[i] = temp[j];
                }
            }
        }
        for(int i = 0; i < 10; i++){
            if(!strcmp(taxonData[i].taxon, "Lichens") || !strcmp(taxonData[i].taxon, "Mammals")){
                printf("%s%16d%11d%11d%11d%8d%10d\n",taxonData[i].taxon, taxonData[i].extinct, taxonData[i].extirpated, taxonData[i].endangered, taxonData[i].threatened, taxonData[i].concern, taxonData[i].total);
                }
            else if(!strcmp(taxonData[i].taxon, "Vascular Plants")){
                printf("%s%8d%11d%11d%11d%8d%10d\n",taxonData[i].taxon, taxonData[i].extinct, taxonData[i].extirpated, taxonData[i].endangered, taxonData[i].threatened, taxonData[i].concern, taxonData[i].total);
                }
            else if(!strcmp(taxonData[i].taxon, "Mosses") || !strcmp(taxonData[i].taxon, "Fishes")){
                printf("%s%17d%11d%11d%11d%8d%10d\n",taxonData[i].taxon, taxonData[i].extinct, taxonData[i].extirpated, taxonData[i].endangered, taxonData[i].threatened, taxonData[i].concern, taxonData[i].total);
                }
            else if(!strcmp(taxonData[i].taxon, "Birds")){
                printf("%s%18d%11d%11d%11d%8d%10d\n",taxonData[i].taxon, taxonData[i].extinct, taxonData[i].extirpated, taxonData[i].endangered, taxonData[i].threatened, taxonData[i].concern, taxonData[i].total);
                }
            else if(!strcmp(taxonData[i].taxon, "Arthropods") || !strcmp(taxonData[i].taxon, "Amphibians")){
                printf("%s%13d%11d%11d%11d%8d%10d\n",taxonData[i].taxon, taxonData[i].extinct, taxonData[i].extirpated, taxonData[i].endangered, taxonData[i].threatened, taxonData[i].concern, taxonData[i].total);
                }
            
            else{
            printf("%s%15d%11d%11d%11d%8d%10d\n",taxonData[i].taxon, taxonData[i].extinct, taxonData[i].extirpated, taxonData[i].endangered, taxonData[i].threatened, taxonData[i].concern, taxonData[i].total);
            }
        }

        printf("--------------- ------- ---------- ---------- ---------- ------- ---------\n");
        printf("%23d%11d%11d%11d%8d%10d\n", totalExtinct, totalExtirpated, totalEndangered,totalThreadtened, totalConcern, Total );
};
