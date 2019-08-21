/*
 * calprint4.c
 *
 * Starter file provided to students for Assignment #4, SENG 265, by Prof Mike Zastre.
 * Summer 2019.
 *
 * Code by Ben Djukastein (V00907342)
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <math.h>
#include <time.h>
#include "emalloc.h"
#include "ics.h"
#include "listy.h"

#define MAX_LINE_LEN 80
#define MAX_EVENTS 500

//The first 2 functions below were entirely written by proffessor Michael Zastre, and used with his permission, and are NOT my own work.

void dt_format(char *formatted_time, const char *dt_time, const int len)
{
    struct tm temp_time;
    time_t    full_time;
 

    /*  
     * Ignore for now everything other than the year, month and date.
     * For conversion to work, months must be numbered from 0, and the 
     * year from 1900.
     */  
    memset(&temp_time, 0, sizeof(struct tm));
    sscanf(dt_time, "%4d%2d%2d",
        &temp_time.tm_year, &temp_time.tm_mon, &temp_time.tm_mday);
    temp_time.tm_year -= 1900;
    temp_time.tm_mon -= 1;
    full_time = mktime(&temp_time);
    strftime(formatted_time, len, "%B %d, %Y (%a)", 
        localtime(&full_time));
}//This function provided by Prof Michael Zastre


/*
 * Function dt_increment:
 *
 * Given a date-time, it adds the number of days in a way that
 * results in the correct year, month, and day. For example,
 * if the string in "before" corresponds to:
 *
 *   20190520T111500
 *
 * then the datetime string stored in "after", assuming that
 * "num_days" is 100, will be:
 *
 *   20190828T111500
 *
 * which is 100 days after May 20, 2019 (i.e., August 28, 2019).
 *
 */

void dt_increment(char after[], const char before[], int const num_days)
{
    struct tm temp_time;
    time_t    full_time;

    memset(&temp_time, 0, sizeof(struct tm));
    sscanf(before, "%4d%2d%2d", &temp_time.tm_year,
        &temp_time.tm_mon, &temp_time.tm_mday);
    temp_time.tm_year -= 1900;
    temp_time.tm_mon -= 1;
    temp_time.tm_mday += num_days;

    full_time = mktime(&temp_time);
    after[0] = '\0';
/* Apparently there is an 9 required as the second parameter,
 * not an 8...  MZ
    strftime(after, 8, "%Y%m%d", localtime(&full_time));
*/
    strftime(after, 9, "%Y%m%d", localtime(&full_time));
    strncpy(after + 8, before + 8, MAX_LINE_LEN - 8); 
    after[MAX_LINE_LEN - 1] = '\0';
}//This function provided by Prof Michael Zastre



int get_month(char start_time[MAX_LINE_LEN]){
    //This function extracts the month from the the start time datetime string, returning it as an integer.
    char month_string[MAX_LINE_LEN];
    // create string to store the month.

    month_string[0] = '0';
    month_string[1] = '\0';
    month_string[2] = '\0';
    month_string[0] = '0';
    month_string[1] = '\0';
    month_string[2] = '\0';
    //ensure the month string will be "month zero" if input is empty, and is otherwise cleared for fresh data.

    month_string[0] = start_time[4];
    month_string[1] = start_time[5];

    month_string[2] = '\0';

    int month = atoi(month_string);
    
    return month;
}//get_month

void print_time(char start_time[MAX_LINE_LEN], char finish_time[MAX_LINE_LEN]){
    //Given input strings for the desired start and end times, print to the console the proper formatting for time for this assignment.
    char hour_string_start[MAX_LINE_LEN];
    char min_string_start[MAX_LINE_LEN];
    // create strings to store the hour and minute.
    hour_string_start[0] = '0';
    hour_string_start[1] = '\0';
    hour_string_start[2] = '\0';
    min_string_start[0] = '0';
    min_string_start[1] = '\0';
    min_string_start[2] = '\0';
    //I manually zero out these values

    hour_string_start[0] = start_time[9];
    hour_string_start[1] = start_time[10];
    min_string_start[0] = start_time[11];
    min_string_start[1] = start_time[12];
    min_string_start[2] = '\0';
    hour_string_start[2] = '\0';
    // store the proper hour and minute.
    int hour_start = atoi(hour_string_start);
    int min_start = atoi(min_string_start);
    //convert  hour and min to integers

    //if (hour_start > 24){
        //printf ("ERRORBOI: Hour String Start is %s\n", hour_string_start);
    //} HHH
    

    char hour_string_finish[MAX_LINE_LEN];
    char min_string_finish[MAX_LINE_LEN];
    // create strings to store the hour and minute of the end time.

    hour_string_finish[0] = '0';
    hour_string_finish[1] = '\0';
    hour_string_finish[2] = '\0';
    min_string_finish[0] = '0';
    min_string_finish[1] = '\0';
    min_string_finish[2] = '\0';

    hour_string_finish[0] = finish_time[9];
    hour_string_finish[1] = finish_time[10];
    min_string_finish[0] = finish_time[11];
    min_string_finish[1] = finish_time[12];
    min_string_finish[2] = '\0';
    hour_string_finish[2] = '\0';
    // store the proper hour and minute.
    int hour_finish = atoi(hour_string_finish);
    int min_finish = atoi(min_string_finish);
    //convert to integer

    // COMMENCE PRINTING:
    if(hour_finish >12 && hour_start >= 12)
    {
        hour_finish -= 12;
        if(hour_start > 12) hour_start-= 12;
        printf("%2d:%02d pm to ",hour_start, min_start);
        printf("%2d:%02d pm: ", hour_finish, min_finish);
    }//if it is "pm" hours

    else if (hour_finish >= 12 && hour_start < 12)
    {
        if(hour_finish > 12) hour_finish-= 12;//if its exactly 12 do not reduce to 0 oclock
        printf("%2d:%02d am to ",hour_start, min_start);
        printf("%2d:%02d pm: ", hour_finish, min_finish);
    }// if across noon hours

    else if (hour_finish < 12 && hour_start > 12)
    {
        hour_start-= 12;
        printf("%2d:%02d pm to ",hour_start, min_start);
        printf("%2d:%02d am: ", hour_finish, min_finish);
    }// if across midnight hours (probably wont be for this assignment)

    else
    {
        printf("%2d:%02d am to ",hour_start, min_start);
        printf("%2d:%02d am: ", hour_finish, min_finish);
    }// if "am" hours
}// print_time takes the starting time string, extracts the hour and minute as strings, converts to integers, then checks if am or pm before printing.



void print_event(node_t *head, int num_entries, char* begin_dt, char* finish_dt) {
    //This function prints all events in the linked list with the formatting desired for Assignment 4.
    assert(head != NULL);
    node_t *list_iterator = head;//establish an iterator to go through the list without losing pointer to the start of the list as you iterate.
    char prev_date[MAX_LINE_LEN];// constant used to store last week's date
    char formatted_dt_start[MAX_LINE_LEN];

    strcpy(prev_date, list_iterator->val->dtstart);

    int success = 0;//this increments whenever an item in the array is within the date boundaries for printing.
    
    for(; list_iterator != NULL ;list_iterator = list_iterator->next)
    {//if 2 values have the same starting value, compare their strings, and sort into alphabetical order.
        if(strncmp(list_iterator->val->dtstart,begin_dt,8) >= 0 && strncmp(list_iterator->val->dtstart, finish_dt, 8) <= 0)
        {//actions within this space only occur when the event is within the established time boundaries for printing.
            

            dt_format(formatted_dt_start, list_iterator->val->dtstart, MAX_LINE_LEN);
            //this sets the dates into a readable format.
            if (strncmp(list_iterator->val->dtstart, prev_date, 8) != 0 || success == 0)
            {
                if(success != 0)
                {
                    printf("\n");
                }
                
                puts(formatted_dt_start);
                printf("------------------");

                int month = get_month(list_iterator->val->dtstart);

                //now to add extra "-" dashes if the month is not May.

                if(month == 5)
                {
                     printf("\n");
                }// just may.
                else if(month == 6 || month == 7)
                {
                    printf("-\n");
                }//months with 4 letter names
                else if(month == 3 || month == 4)
                {
                    printf("--\n");
                }//months with 5 letter names
                else if(month == 8)
                {
                     printf("---\n");
                }// just August.
                else if(month == 1 || month == 10)
                {
                    printf("----\n");
                }//months with 7 letter names
                else
                {
                    printf("-----\n");
                }//months with 8 letter names
            }//for every new day
            

                print_time(list_iterator->val->dtstart, list_iterator->val->dtend);// this function takes the starting time string, extracts the hour and minute as strings, converts to integers, then checks if am or pm before printing.
        
                printf("%s [%s]\n",list_iterator->val->summary, list_iterator->val->location);

                success++;
           
                strcpy(prev_date, list_iterator->val->dtstart);

            // sets the previous date for comparison in the next loop.

        }//if inside date and time of desired output.  

    }// for each event
}//print events

node_t * add_repeating_event(node_t *head, node_t *repeating_node){
    event_t *temp_event = NULL;
    node_t *temp_node = NULL;
    char new_start_date[MAX_LINE_LEN];
    char new_end_date[MAX_LINE_LEN];
    char temp_start_dt[MAX_LINE_LEN];// used to help increment the start date
    char temp_end_dt[MAX_LINE_LEN];//used to help increment the end date

    strncpy(new_start_date, repeating_node->val->dtstart, 15);// this will increment the weeks until "repeat_until".
    strncpy(new_end_date, repeating_node->val->dtend, 15);// this will increment the weeks until "repeat_until".

    dt_increment( temp_start_dt,  new_start_date, 7);
    strncpy(new_start_date, temp_start_dt, 15);// increments the start date by 7 days

    dt_increment( temp_end_dt,new_end_date, 7);// increments the end date by 7 days.
    strncpy(new_end_date, temp_end_dt, 15);

                /*SET VALUES FOR THE NEXT REPEATED EVENT */

    while(strncmp(repeating_node->val->rrule, new_start_date, 8) >= 0){
        temp_event = emalloc(sizeof(event_t));
                    
        strncpy(temp_event->dtstart, new_start_date, 15);
        strncpy(temp_event->dtend, new_end_date, 15);
        strncpy(temp_event->location, repeating_node->val->location, MAX_LINE_LEN);
        strncpy(temp_event->summary, repeating_node->val->summary, MAX_LINE_LEN);
        strncpy(temp_event->rrule, temp_event->dtstart, 15);//set the values for the next repeated event to not repeat in and of itself!!
        temp_node = new_node(temp_event);
        if (head == NULL){
            head = add_front(head, temp_node);
            
        }//if
        else{
            head = add_inorder(head, temp_node);
        }//if the head is not empty, make sure you add the event to the right spot in the list based on start date and summary.
        
        dt_increment( temp_start_dt,  new_start_date, 7);
        strncpy(new_start_date, temp_start_dt, 15);// increments the start date by 7 days

        dt_increment( temp_end_dt,new_end_date, 7);// increments the end date by 7 days.
        strncpy(new_end_date, temp_end_dt, 15);
    }//while before the "repeat until" date, keep making weekly copies.  
    return head;
}// add repeating events for the specified event to the list in sorted chronological order.


int get_num_entries(node_t *head){
    //takes the head of the list, counts the number of events, and returns an integer value.
    assert(head != NULL);
    node_t *current_node = head;
    int num_entries = 1;

    for(;current_node->next != NULL;current_node = current_node->next){
        num_entries++;
    }//while
    return num_entries;
}


void trim_line(char *line,char * output, char * strip_from_here, char * strip_to_here, int strip_from_here_length)
    {//Trims the provided line string to whatever is between a colon and a \n, without any return value stores it in output.
    char*finish;
    char*begin;
    //output = NULL;

    finish = strstr (line, strip_to_here);
    begin = strip_from_here_length + strstr(line, strip_from_here);// the 1 moves the cursor past the colon.

    int temp = 0;

    int finish_trim = &finish[0] - &line[0];
    int begin_trim = &begin[0] - &line[0];//setting the boundaries of the string slice, or trim

    for(int counter = begin_trim; counter < finish_trim; counter++){
        for(int i = 0;i<1;i++)
        {
            output[temp] = line[counter];   
        }// end of 2nd for loop
        temp++;
    }//end of 1st for loop
    
}// end of trim__line


node_t * get_events_from_file(FILE *fp) {//This function returns the head of a linked list containing all events from the file, added in_order as per lab 10.
    event_t *temp_event = NULL;
    node_t  *temp_node  = NULL;
    node_t  *head = NULL;
    char line[MAX_LINE_LEN]; // stores each line while it is being processed HHH try emallocing this later
    char stripped_unformatted_line[MAX_LINE_LEN]; // stores each stripped line temporarily.

    while(1)
    {//loops until there are no more lines in the file to read.
        if(fgets (line, MAX_LINE_LEN, fp)!= NULL)
        {/*this fgets moves the cursor to the end of the DTSTART line*/
            if(strncmp(line, "BEGIN:VEVENT", 12) == 0)
            {//if we have sound the start of an event..
                
	            int rrule_flag = 0;
                temp_event = emalloc(sizeof(event_t));
                //allocate space for a new event.

                fgets (line, MAX_LINE_LEN, fp);// moves cursor to end of DTSTART, stores in "line";
                trim_line(line,stripped_unformatted_line, ":","\n",1);//strips the excess characters from the input line, leaving only the unformatted datetime.
                strncpy(temp_event->dtstart, stripped_unformatted_line, 15);

                fgets (line, MAX_LINE_LEN, fp);
                trim_line(line, stripped_unformatted_line,":","\n",1);
                strncpy(temp_event->dtend, stripped_unformatted_line, 15);//stores the dt_end string  HHH make this consistent with start date
                
                                fgets (line, MAX_LINE_LEN, fp);// checks for RRULE line, or reads the "location" line.
                if(strncmp(line,"RRULE:",6) >= 0){
                    trim_line(line,temp_event->rrule,"UNTIL=",";BYDAY", 6);
		            rrule_flag = 1;//this event has an RRULE
                    fgets (line, MAX_LINE_LEN, fp);//moves to the next line.
                }//if this event has an RRULE..
                else{
                    strncpy(temp_event->rrule, temp_event->dtstart, 15);//stores the dt_start string in the new RRULE 
                }
                
                trim_line(line,temp_event->location,":","\n", 1);
                //either way, trim the location line, storing in the temp event's location field.

                fgets (line, MAX_LINE_LEN, fp);
                trim_line(line,temp_event->summary,":","\n", 1);
                //trim the summary line, storing in the temp event's summary field.
                

                temp_node = new_node(temp_event);

		        if (rrule_flag == 1){
		        head = add_repeating_event(head, temp_node); //adds all the repeating events for this event.
		        }//if its a repeating event...

                head = add_inorder(head, temp_node);
            }//if an event is occurring..

        }//if the current line is not null
        else
        {
            return head;
        }//when you run out of lines, or if the file is empty, just return the head of whatever linked list you have.
    }//while loop  
}//geteventsfromfile

void free_memory(node_t *head) {
    //this function manually clears the dynamic memory allocated to the linked list.
    event_t *temp_event = NULL;
    node_t  *temp_node  = NULL;
    
    while (head != NULL){
        temp_node = head;
        assert(temp_node != NULL);
        head = remove_front(head);
        temp_event = temp_node->val;
        assert(temp_event != NULL);
        free(temp_event);
        free(temp_node);
    }   
    assert(head == NULL); 
    //This function takes the input file and creates a linked list of /
    // unsorted properly formatted events out of the provided events.
}

#ifdef DEBUG

/*
 * Just showing the use of the linked-list routines.
 */

void _demo() {
    event_t *temp_event = NULL;
    node_t  *temp_node  = NULL;
    node_t  *head = NULL;

    /* Add one event, without an RRULE */

    temp_event = emalloc(sizeof(event_t));
    strncpy(temp_event->dtstart, "20190706T120000", 17);
    strncpy(temp_event->dtend, "20190706T160000", 17);
    strncpy(temp_event->summary, "summary 1", SUMMARY_LEN);
    strncpy(temp_event->location, "location 1", LOCATION_LEN);
    temp_event->rrule[0] = '\0';
    temp_node = new_node(temp_event);
    head = add_front(head, temp_node);

    /* Add a second event, with an RRULE */

    temp_event = emalloc(sizeof(event_t));
    strncpy(temp_event->dtstart, "20190707T093000", 17);
    strncpy(temp_event->dtend, "20190707T102000", 17);
    strncpy(temp_event->summary, "uvwxyz 1234567", SUMMARY_LEN);
    strncpy(temp_event->location, "abcde 1234567", LOCATION_LEN);
    strncpy(temp_event->rrule, "yada RULE yada UNTIL yada", RRULE_LEN);
    temp_node = new_node(temp_event);
    head = add_front(head, temp_node);

    /* Print the list of events. */

    apply(head, print_event, NULL);

    /* Free up the memory. This is done rather deliberately
     * and manually. A full-featured function might better
     * serve for this. Asserts are liberally used here as they
     * express state that *must* be true if all of the code is
     * correctly working.
     */

    temp_node = head;
    assert(temp_node != NULL);
    head = remove_front(head);
    temp_event = temp_node->val;
    assert(temp_event != NULL);
    free(temp_event);
    free(temp_node);

    temp_node = head;
    assert(temp_node != NULL);
    head = remove_front(head);
    temp_event = temp_node->val;
    assert(temp_event != NULL);
    free(temp_event);
    free(temp_node);
   
    assert(head == NULL); 
    
}

#endif


int main(int argc, char *argv[])
{

//this first chuck of code is Prof Zastre's work:
    int from_y = 0, from_m = 0, from_d = 0;
    int to_y = 0, to_m = 0, to_d = 0;
    char *filename = NULL;
    int i; 

    for (i = 0; i < argc; i++) {
        if (strncmp(argv[i], "--start=", 7) == 0) {
            sscanf(argv[i], "--start=%d/%d/%d", &from_d, &from_m, &from_y);
        } else if (strncmp(argv[i], "--end=", 5) == 0) {
            sscanf(argv[i], "--end=%d/%d/%d", &to_d, &to_m, &to_y);
        } else if (strncmp(argv[i], "--file=", 7) == 0) {
            filename = argv[i]+7;
        }
    }

    if (from_y == 0 || to_y == 0 || filename == NULL) {
        fprintf(stderr, 
            "usage: %s --start=dd/mm/yyyy --end=dd/mm/yyyy --file=icsfile\n",
            argv[0]);
        exit(1);
    }


/* 
 * Showing some simple usage of the linked-list routines.
 */

#ifdef DEBUG
    _demo();
#endif
    //Above this line is all Prof Zastre's code within MAIN






    //Ben Djukastein's main code starts here:

    char begin_dt[16];//this will store the datetime for the desired day to begin printing events from.
    char finish_dt[16];

    sprintf(finish_dt,"%04d%02d%02dT000000",to_y, to_m, to_d);//actually sets the datetime of finish_dt
    sprintf(begin_dt,"%04d%02d%02dT000000",from_y, from_m, from_d);

    int num_entries = 0;// stores the number of entries
    node_t  *head = NULL;//This stores the head of the linked list.

    //open the file...
    FILE * fp;
    fp = fopen (filename, "r");

    if(fp == NULL)
    {
        printf("file didn't open properly, check out the file, bro."); 
        exit(1);
    }//if file doesn't open, exit.

    head = get_events_from_file(fp);
    
    fclose(fp);// never forget to close your files! :)

    num_entries = get_num_entries(head);//this counts the number of events in the linked list, starting from HEAD.

    print_event(head, num_entries, begin_dt, finish_dt);// prints the events to the console.

    free_memory(head);// frees allocated memory.

    exit(0);
}

