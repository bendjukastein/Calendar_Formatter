#!/usr/bin/env python3

# UVic SENG 265, Summer 2019, Assignment #3
# Student work is to appear in this module.
# Ben Djukastein V00907342

import re
import datetime

class Event:
    def __init__(self, start_dt, summary, fin_dt, location, until):
        '''initializes all of the variables for the event class.'''
        self.start_dt = start_dt
        self.fin_dt = fin_dt
        self.summary = summary
        self.location = location
        self.until = until # if the event does not repeat, this will be a zero.


class Calprint:

    def __init__(self, filename):
        '''Initializes the Calprint class with the given filename'''
        self.filename = filename

    def event_to_linked_list(self, events):
        '''This function groups the lines that describe each event from file_lines, and strips unneeded characters from each group before adding them to a new event and appending it to the events list'''
        regex_start_dt = re.compile("DTSTART:((\d{4})(\d{2})(\d{2})T(\d{2})(\d{2})(\d{2}))")
        regex_summary = re.compile("SUMMARY:(.*)")
        regex_fin_dt = re.compile("DTEND:((\d{4})(\d{2})(\d{2})T(\d{2})(\d{2})(\d{2}))") #compiles the regex search strings I will use to extract the event data.
        regex_location = re.compile("LOCATION:(.*)")
        regex_until = re.compile("RRULE:.*((\d{4})(\d{2})(\d{2})T(\d{2})(\d{2})(\d{2})).*")

        counter = 0; #counter starts at zero because I look for the dt_start line, and want to begin by extracting from that same line, i.e from file_lines[counter+0] 
        
        for line in self.file_lines:
            
            line = line.rstrip("\n")
            if re.search(regex_start_dt, line): # searches for a date 

                self.str_start = regex_start_dt.match(self.file_lines[counter]).group(1)
                self.str_end = regex_fin_dt.match(self.file_lines[counter+1]).group(1)
                
                #self.str_start = self.file_lines[counter].rstrip("\n").strip("DTSTART").strip(":")# isolating the start and end strings of the form "YYYYMMDDTHHmmSS"
                #self.str_end = self.file_lines[counter+1].rstrip("\n").strip("DTEND").strip(":")

                self.start_dt = datetime.datetime.strptime(self.str_start, "%Y%m%dT%H%M%S") #turns the start_dt from a string into a datetime
                self.fin_dt = datetime.datetime.strptime(self.str_end, "%Y%m%dT%H%M%S")

                if self.file_lines[counter+2].find('RRULE') != -1:#For events that repeat...
                    self.until = regex_until.match(self.file_lines[counter+2]).group(1)#get the repeat until value
                    self.location = regex_location.match(self.file_lines[counter+3]).group(1)#get the location string
                    self.summary = regex_summary.match(self.file_lines[counter+4]).group(1)# get the summary string

                    events.append(Event(self.start_dt, self.summary, self.fin_dt,self.location, self.until))# and add a new event to the event_list, with the acquired data.

                else:# For events that do NOT repeat...

                    self.location = regex_location.match(self.file_lines[counter+2]).group(1)#get the location string
                    self.summary = regex_summary.match(self.file_lines[counter+3]).group(1)# get the summary string
                    events.append(Event(self.start_dt, self.summary, self.fin_dt,self.location, 0))# add to the event_list, and set the repeat until value to zero, showing that the event does not repeat.
                    # summary is put as the second item so that when sorting, alphabetical order comes after chronological order.
            
            #This takes each instance of BEGIN:VEVENT and stores the next few lines into a new "event" class, which is then added to the list of all events, "event_list".
            
            counter += 1# increment the counter

        return events


    def add_repeating_events(self, events):
        '''This function adds copies of repeating events to the events list'''
        for event in events:
            if event.until != 0:
                self.until = datetime.datetime.strptime(event.until, "%Y%m%dT%H%M%S") # turn the repeat until string into a datetime

                self.dt_start = event.start_dt # copies the start and end dates so they can be iterated by a week for the repeated versions of the same event.
                self.dt_end = event.fin_dt
               
                self.next_start_dt = self.dt_start + datetime.timedelta(days = 7)#initializes a value representing next week's start date to check if the next week is past the repeat until date.
               
                while self.next_start_dt <= self.until: # While next week is not yet past the repeat until date..
                    self.dt_start = self.dt_start + datetime.timedelta(days = 7)
                    self.next_start_dt = self.dt_start+ datetime.timedelta(days = 7) #   increment the dt_start, dt_end and next_dt_start values by a week
                    self.dt_end = self.dt_end + datetime.timedelta(days = 7)
                    
                    events.append(Event(self.dt_start, event.summary, self.dt_end, event.location, 0)) # add the weekly duplicates to the event_list

        return events


    def todays_events_to_string(self, events, dt):
        '''this function checks which events occur on the given day, and returns a string containing the output that should be printed to the console'''
        formatted_events_string = '' #by the end of this function, this string will consist of the entire day's formatted output
        todays_output_event_list = [] #this list will store each event's formatted output for the entire day

        event_counter = 1
        current_event_number = 0 # these flags will allow me to ensure no newline is added to the final event of the day

        first_event = 0 #this flag ensures that the date and dashes only appear for the first event of the day.


        for event in events:

            event_string = '' #this will be used as the separator between lines in the output_lines_list
            output_lines_list = []

            
            if event.start_dt.year == self.dt.year and event.start_dt.month == self.dt.month and event.start_dt.day == self.dt.day:
                event_counter += 1  #this incrementer counts how many events occur on the given day, to be used for formatting the final event of the day differently.

            if event.start_dt.year == self.dt.year and event.start_dt.month == self.dt.month and event.start_dt.day == self.dt.day:
                current_event_number += 1 # this incremementer is later compared to event_counter in the function to check whether the current event is the last event of the day.

                if (first_event == 0): #If this is the first event occurring today:
                    output_lines_list.append(event.start_dt.strftime("%B %d, %Y (%a)\n")) # print out the start date.
                       
                    self.append_dashes( output_lines_list) #this function appends the correct number of dashes.

                    first_event = 1 #Now any more events occurring on this day will not print out the date and line of dashes.
                    
                    
                self.append_time(event.start_dt, event.fin_dt, output_lines_list) # this function appends the correct 12 hour time based on start and end 24 hour time.

                output_lines_list.append(event.summary+" ["+event.location+"]") #Add the line describing the summary and location to the list.

                if current_event_number != event_counter:
                    output_lines_list.append("\n") #For all events other than the last event, add a newline

                event_string = event_string.join(output_lines_list) #Join all of the output lines together for this event into a single string

                todays_output_event_list.append(event_string) # append this string as one event in today's console output

        formatted_events_string = formatted_events_string.join(todays_output_event_list)# join all of the event strings in the list into one large string.

        formatted_events_string = formatted_events_string.rstrip("\n") #remove the final newline from the last event of the large string.

        return formatted_events_string


    def append_time(self, start, fin, output_lines_list): # This function prints out the time with proper formatting.
        
        if ((start.hour + 11) % 12) + 1 < 10: #this line checks if the starting hour is a single digit number in 12 hour time
            output_lines_list.append(" ") # append an extra space if it's a single digit hour

        start_meridiem = start.strftime("%p").lower()# this sets the AM or PM given by %p to am or pm.
        fin_meridiem = fin.strftime("%p").lower()
        
        
        output_lines_list.append(start.strftime("%-I:%M ")) 
        output_lines_list.append(start_meridiem) # appends the formatted start time
        output_lines_list.append(" to ") 
        
        if ((fin.hour + 11) % 12) + 1 < 10: 
            output_lines_list.append(" ") # as above
            
        output_lines_list.append(fin.strftime("%-I:%M "))
        output_lines_list.append(fin_meridiem) # appends the formatted end time
        output_lines_list.append(": ")  


    def append_dashes(self, output_lines_list): 
        '''This appends the proper number of dashes based on the length of the date string, which changes with the differing months'''

        regex_any_char = re.compile("(.)")
        dash_line = output_lines_list[-1][:]
        dash_line = re.sub(regex_any_char, "-" ,dash_line)

        output_lines_list.append(dash_line) # I realized that I could base the number of dashes on string length later, but this seemed more visually entertaining when I scroll through my code :)



    def get_events_for_day(self, dt):
        '''Reads each line of files, if you find start date equals dt: take the following lines and store them in as an event:'''
        self.fp = open(self.filename, "r")
        self.file_lines = self.fp.readlines()#Stores the lines of the input file into the file_lines list.
        self.fp.close() #We are now finished with reading from the file, so I close it.

        #Open the file and store each line in the file_lines list.

        self.dt = dt

        events = [] #this list will store all the events.

        events = self.event_to_linked_list(events) #Reads each line relevant to a given event, and strips everything except the pertininent info, before adding it to a new event in the events list.

        events = self.add_repeating_events(events) # adds all copies of repeating events to the events list

        events.sort(key = lambda event: (event.start_dt, event.summary)) #This sorts the events primarily by start date, but secondly by summary.

        formatted_events_string = self.todays_events_to_string(events, self.dt) #This searchs through each event in the event list, and if it occurs on the given date, prints it with proper formatting.

        #if formatted_events_string == '': #if the output string is empty, return None instead.
            #return None 
        #return formatted_events_string

        is_empty_regex = re.compile('.*')

        if not is_empty_regex.search(formatted_events_string): #if the output string is empty, return None instead.
            return None 
        return formatted_events_string








