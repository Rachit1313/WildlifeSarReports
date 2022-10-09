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

#ifndef cosewic_h
#define cosewic_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//User-Defined Data Structures
struct FileData
{
    int year;
    char taxon[20];
    char status[20];
    int count;
    char province[3];
};
struct TaxonStruct
{
    char* taxon;
    int extinct;
    int extirpated;
    int endangered;
    int threatened;
    int concern;
    int total;
};
//integer function to import data from file
int loadData(const char* datafile, struct FileData* data, int max);

//main function
void mainLogic(struct FileData* data,int records);

//Input a integer between a range 
int int_Range(int Minim, int Maxim);

//Input a Integer
int input_Int(void);

//Compare function
int compare(const void  *a, const void  *b);

//View data by year
void viewbyyear(struct FileData* data,int records);

//View data by province
void viewbyprovince(struct FileData* data,int records);

//View by province and records
void viewbyprovinceandtax(struct FileData* data,int records);

//View by taxon
void viewbytaxon(struct FileData* data, int records);
#endif /* cosewic_h */
