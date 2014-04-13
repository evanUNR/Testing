/*
Group 7 - Doing Design Group 7's Design
Chris Scott
Evan West
Brandon Worl
Richard Lyday
*/

/* Headers */
#include "stdio.h"


/* Global Constants */
#define DEBUG__get_config 1
#define DEBUG__get_and_convert 0


////////////////STRUCTS////////////////
/*********************************************
Name: Config
Purpose: Hold configuration information
Variables: 	Quantum - Holds time quantum for system
		proc_scheduling_type - Holds type of scheduling used by sytem. For initial implementation, 
				       this holds "RR" (Round Robin)
		out_path - Holds the file path for the output
		proc_cycle_time - Holds the time (in milliseconds) to access the hard drive
		monitor_display_time - Holds time (in milliseconds) to display a message to the monitor
		harddrive_cycle_time - Holds time it takes (in milliseconds) to access the hard drive
		printer_cycle_time - Holds time it takes (in milliseconds) to send a message to the printer
		keyboard_cycle_time - Holds time it takes (in milliseconds) to receive a message from the keyboard
		memory_type - Holds type of memory. If holds ‘F’, then memory is fixed
		log - Holds where to output information. If holds ‘B’, outputs to both terminal and file. 
		      If ‘F’, outputs to just file. If ‘T’, outputs to terminal
**********************************************/
struct CONFIG
{
  int Quantum;
  char proc_scheduling_type[10];
  char out_path[50];
  int  proc_cycle_time;
  int monitor_display_time;
  int hardrive_cycle_time;
  int printer_cycle_time;
  int keyboard_cycle_time;
  char memory_type;
  char log;
};
typedef struct CONFIG CONFIG;

/**********************************************
Name: PROCESS
Purpose: HOlds the informaitohn for a single application
Variables: 	pid - Holds process ID. This is determined by the order in which the processes are created. 
		      The first process has a pid of 0, the second process has a pid of 1, ect.
		commands - Holds entire list of commands. This is a 2­D array in 1­D format. Each row is a different command
		instruction_counter - Holds index (row) of current instruction
		completion_counter - Holds how much of current instruction has been completed.
		next - points to the process directly behind current precess in queue. If this is the last process in the queue, 
		       next points to NULL.
***********************************************/
typedef struct PROCESS PROCESS;
struct PROCESS
{
  int pid; 
  char * commands;
  int instruction_counter;
  int completion_counter;
  PROCESS * next;
};

/***********************************************
Name: PCB
Purpose: Holds pointers to first and last process in queue
Variables:	head - points to first process in queue
		tail - points to last process in queue
***********************************************/
typedef struct
{
  struct PROCESS * head;
  struct PROCESS * tail;
} PCB;

/***********************************************
Name: INT
Purpose: Holds interrupt information.EAch interrupt is added to a queue which is then emptied before every time quantum
Variables: 	out_string - Holds message to output to file
		duration: HOlds the length of time the I/O executed
		next: points to next interrupt in queue
***********************************************/
typedef struct INT INT;
struct INT
{
  char out_string[50];
  int duration;
  INT * next;
};


/* Function Prototypes */
void get_config(CONFIG * config_data, char * config_file);
int get_and_convert(FILE * infile, int seek_count);
void instruction(PROCESS * process, CONFIG config_data, INT * interrupt_head);

int main()
{
  CONFIG temp;
  get_config(&temp, "Configuration.txt");
}


/***********************************************
Name: get_config
Purpose: Get configuration information from a file and store it in config_data
Parameters: 	config_data - holds configuration data
		config_file - holds filename for configuration data
Returns: Nothing
***********************************************/
void get_config(CONFIG * config_data, char * config_file)
{
  FILE * infile;
  infile=fopen(config_file, "r");

  //Get Quantum
  config_data->Quantum = get_and_convert(infile, 67);
  #if DEBUG__get_config 
    printf("Quantum: %i\n", config_data->Quantum);
  #endif
  
  //Get proc_schedualing_type
  fseek(infile, 22, SEEK_CUR);
  fscanf(infile, "%[^\n]", config_data->proc_scheduling_type);
  #if DEBUG__get_config 
    printf("scheduling type: %s\n", config_data->proc_scheduling_type);
  #endif

  //Get output path
  fseek(infile, 11, SEEK_CUR);
  fscanf(infile, "%[^\n]", config_data->out_path);
  #if DEBUG__get_config 
    printf("out_path: %s\n", config_data->out_path);
  #endif

  //Get the processor cycle time 
  config_data->proc_cycle_time = get_and_convert(infile, 30);
  #if DEBUG__get_config 
  printf("Proc cycle time: %i\n", config_data->proc_cycle_time);
  #endif

  //Get the monitor's display time
  config_data->monitor_display_time = get_and_convert(infile,29);
  #if DEBUG__get_config 
    printf("Monitor display time: %i\n", config_data->monitor_display_time);
  #endif

  //Get the harddrive's cycle time
  config_data->hardrive_cycle_time = get_and_convert(infile,30);
  #if DEBUG__get_config 
    printf("Hardrive cycle time: %i\n", config_data->hardrive_cycle_time);
  #endif

  //Get the printer's cycle time
  config_data->printer_cycle_time = get_and_convert(infile, 27);
  #if DEBUG__get_config 
    printf("Printer cycle time: %i\n", config_data->printer_cycle_time);
  #endif

  //Get the Keyboard's cycle time
  config_data->keyboard_cycle_time = get_and_convert(infile, 28);
  #if DEBUG__get_config 
  printf("Keyboard cycle time: %i\n", config_data->keyboard_cycle_time);
  #endif

  //Get the memory type: F for Fixed and D for Dynamic
  fseek(infile, 13, SEEK_CUR);
  config_data->memory_type = fgetc(infile);
  #if DEBUG__get_config 
  printf("Memory Type: %c\n", config_data->memory_type);
  #endif

  //Holds where to log data: F is to File, T is to Terminal, B is to Both
  fseek(infile, 6, SEEK_CUR);
  config_data->log = fgetc(infile);
  #if DEBUG__get_config 
    printf("Log: %c\n", config_data->log); 
  #endif

  fclose(infile);
}


/***********************************************
Name: get_and_convert
Purpose: Get information from file and convert it to an integer
Parameters: 	infile - points to input file
		seek_count - holds distance cursor is to move from current position to get 
			     to next data
Returns: 	return_val - holds data from file in integer form
***********************************************/
int get_and_convert(FILE * infile, int seek_count)
{
  //Declare a 1-D array long enough hold the data from any 
  //line of infile
  char data[50];

  //Get Quantum
  fseek(infile, seek_count, SEEK_CUR);
  
  int return_val = 0;

  #if DEBUG__get_and_convert 
    printf("Char Quantum ");
  #endif
  
  //counters
  int data_count_1, data_count_2, data_flip_1, data_flip_2, tens_place_count; 

  //Determins place (10's place, 100's place, ect.).  
  int place;
 
  //Quantum value may be multiple characters long, so get all of them
  for(data_count_1 = 0; (data[data_count_1] = fgetc(infile)) != '\n'; data_count_1++)
  {
    #if DEBUG__get_and_convert
      printf("%c", data[data_count_1]);
    #endif
  }

  for(data_count_2 = 0; data_count_2 < data_count_1; data_count_2++)
  {
    //Calculate the ten's place where this particular character should be palce
    place = 0;
    for(tens_place_count = 0; tens_place_count < data_count_1 - data_count_2; tens_place_count++)
    {
      if(tens_place_count == 0)
      {
        place = 1;
      }
      else
      {
        place = place*10;
      }
    }
  
    #if DEBUG__get_and_convert 
      printf("\nDigit: %c", data[data_count_2]);
      printf(" Place: %i", place);
      printf("\n");
    #endif
    
    //place character into Quantum;
    return_val += (data[data_count_2] - '0')*place;
    
    #if DEBUG__get_and_convert 
      printf("Quantum: %i\n", return_val);
    #endif
  }
 
  #if DEBUG__get_and_convert 
    printf(" Int Quantum: '%i' \n", return_val);
  #endif

  return return_val;
}


/***********************************************
Name: instruction
Purpose: Determine whether the instruction is an I/O instruction or a processing 
         instruction and call the appropriate function
Parameters: 	process - holds the process to execute
		config_data - holds the configuration data
		interrupt_head - holds the head to the interrupt queue
Returns: 	Nothing
***********************************************/
void instruction(PROCESS * process, CONFIG config_data, INT * interrupt_head)
{
  //Stuff here!
}



