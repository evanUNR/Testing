////////////////////////////////////////////////////////////////////
//                                                                //
//                                                                // 
//           Welcome to the Operating System Simulator            //  
//                                                                //
//               Starting Date: March 24, 2014    	          //
//              Completion Date: April 18, 2014	    		  //
//    	      Group 7 - Doing Design Group 7's Design		  //
//			 Group Members:				  //
//  	Chris Scott, Evan West, Brandon Worl, Richard Lyday	  //
//                                                                //
//                                                                //
////////////////////////////////////////////////////////////////////

//////////////////Headers/////////////////////
// I added in some headers that I thought we might need. Add as needed. -Chris
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <pthread.h>


//////////////Global Constants////////////////
//Debugging
#define DEBUG__get_and_convert 0
#define DEBUG__get_config 0


///////////////////STRUCTS////////////////////
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


//////////////Function Prototypes////////////////
void get_meta_data(char *meta_data, char *meta_file);
void RR_scheduling( struct CONFIG config_data, struct PCB *pcb, char *config_file, char *meta_file);
void get_config(CONFIG * config_data, char * config_file);
int get_and_convert(FILE * infile, int seek_count);
void instruction(PROCESS * process, CONFIG config_data, INT * interrupt_head);

/* Struct Prototypes */


￼// Main
int main (int argc, char** argv)
  {
    // Variables
    
    // Check Command­Line arguments
    
    // Read in data
    
    // Run another program to get meta­data operations
    
        // Create PIDs while getting data using queue data struct
    
    // Loop until done (Main loop) ­­­­ ***** You will be timing EVERYTHING and printing // things when they are complete *****
    
    // Dequeue first PID
    
    // Check if there is an interrupt from I/O thread
    
        // Yes; Output the timing 
            
            // Kill thread
            
            // Re­poll ­­ Clear out all interrupts that are thrown
            
            // Execute instructions 
        
        // I/O
        
            // Create Thread
            
            // Since Thread runs by itself Enqueue PID
            
                // Dequeue another­ loop just starts over
            
            // Do Thread processing until it’s done
            
            // Record timing

            // Throw interrupt


    // Processes 
        
        // Loop

            // Check to see if the processes is finished 

                // Increment the process counter

                // Output stuff

                // Enqueue the PID onto the queue

           // If Processes is not finished
        
              // Check Quantum ­­ If another method then do that here
              
              // If quantum is hit ­­ Or whatever method you're doing
              
              // Save state and Enqueue the PID onto the queue
              
          // Quantum not hit

              // Process another chunk
              
// After any enqueue PID, dequeue PID and repeat steps above 

// When all processes/ I/O is complete in a PID
    
    // End PID, do not enqueue 
    
    // Dequeue another PID
return 0;
} 

/* Function Implementations */

/*
function:  boot_system()
boot_system()
Parameters:
➢ CONFIG config_data: holds all configuration data
➢ PROCESS * head: points to first process in queue
➢ char * config_file: holds name of configuration file
➢ char * meta_file: holds name of metadata
file
Variables:
➢ Timer tim: for timing length of booting the process
➢ int procID: holds ID of process
➢ char out_string[50] = “SYSTEM boot,
set up ”: holds string for output file
➢ double elapsed_time: holds the duration of “booting” the system (inputing data and
creating new process)
Pseudocode:
➢ tim.start()
➢ Call get_config(), passing in config_data by (reference) and config_file
➢ fork()
➢ tim.stop()
➢ If in child (if procID ==0):
○ elapsed_time = tim.getElaspedTime() //This function returns the difference
between start and stop of timer
○ call output(), send in config_data.out_path, config_data.log, out_string, and
elapsed_time.
END

*/
void boot_system(CONFIG config_data, PROCESS* head, char* config_file_name, char* meta_file_name)
{
	//  variables
	Timer tim;
	int procID;
	char out_string[50] = "System boot, set up ";
	double elapsed_time = 0.0;
	
	// start timer
	tim.start();
	
	// call get_config( CONFIG & config_data,  )
	

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

  //Get log locations: F is to File, T is to Terminal, B is to Both
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


/*
function: start_processes()
Parameters:
➢ PCB * pcb: holds pointers to first and last processes in queue
➢ char * meta_file: holds metadata
filename
➢ char * config_data: holds all configuration data
Variables:
➢ char * meta_data: holds raw data from meta_file
➢ Timer tim: for timing length of “starting” each process
*/
void start_processes(PCB *pcb, char *meta_file, CONFIG config_data)
{
    char *meta_data;
    Timer tim;
    
    // Get the meta data from the meta data file
    get_meta_data(meta_data, meta_file);
    
    // Tokenize meta_data and assign to process instruction queues
    int width = 11;
    int height = 0;
    
    bool next = true; // flag indicates we have gone to the next process
    int command_num = 0;
    int process_num = 0;

    int i = 0;
    int i2 = 0;
    int j = 0;
    PROCESS *current; // = pcb->head;
    
    // Skip leading "S(start)" command
    while (meta_data[i] != '\0' && meta_data[i] != ';')
    {
        i++;
    }
    i++;
    
    // Handle system start
    
    // Build command lists & create processes
    while (meta_data[i] != '\0')
    {
        // Count number of commands
        while (next == true && meta_data[i2] != '\0')
        {
            // New command, increment height
            if (meta_data[i2] == ";")
            {
                height++;
            }
            
            i2++;
            if (meta_data[i2] == "A")
            {
                next = false;
                
                // If first process, set pcb head to new PROCESS object
                if (process_num == 0)
                {
                    current = new PROCESS();
                    pcb->head = current;
                }
                
                // Allocate the 1D array
                current->commands = new char[height*width];
                
                break;
            }
        }
        
        // reached the delimiter between commands
        if (meta_data[i] != ";")
        {
            current->commands[command_num*width + j] = meta_data[i];
            j++;
        }
        else
        {
            command_num++;
            j = 0;
        }
        
        // Check if the current process's commands have all been covered
        if (meta_data[i] == "A")
        {
            current = current->next;
            command_num = 0;
            process_num++;
            next = true;
        }
        else if (meta_data[i] == "S")
        {
            // Handle simulation end
        }
            
        i++;
    }
    
    // set PCB tail
    pcb->tail = current;
    
    // Deallocate meta_data
    delete [] meta_data;
}

/*
function: output()

output()
Parameters:
➢ char * out_path: holds output file (if needed)
➢ char * log: holds output method
➢ char * out_string: holds string to output
➢ double elapsed_time: holds the time to output. Contains 1
if there is no time
Pseudocode:
➢ If log contains “log to both” or “log to file”
○ open out_path file in append mode
○ output out_string to file
○ If elapsed_time does not contain 1:
■ output: “ (“ << elasped_time << “)” << endl
○ else
■ output: endl
➢ If log contains “log to both” or “log to monitor”
○ output out_string to monitor
○ If elapsed_time does not contain 1:
■ output: “ (“ << elasped_time << “)” << endl
○ else
■ output: endl
➢ close file
END

*/
void output()
{

} 


/*
function: interrupt()

interrupt()
Parameters:
➢ INT * interrupt: holds interrupt information
➢ char * out_path: holds path of output file
➢ char * log: holds output method
Pseudocode:
➢ Call output() and send in out_path, log, interrupt.out_string, and interrupt.duration
END
instruction()
Parameters:
➢ PROCESS * process: holds process to execute
➢ CONFIG config_data: holds configuration data
➢ INT * interrupt_head: holds pointer to head of interrupt queue
Pseudocode:
8
➢ Get current instruction from process.
➢ If the instruction is I/O:
○ Call I_O() and send in process, config_data, and interrupt_head
➢ Otherwise the instruction is processing
○ Call processing() and send in process and config_data
END
*/
void interrupt()
{

}


// get_meta_data
// THIS FIXED AND FUNCTION IS DONE. I REMOVED THE SPACES FROM THE META_DATA. 
void get_meta_data(char *meta_data, char *meta_file)
{
    // initialize variables
    FILE *fin;              // file pointer
    int counter = 0;        // counter
    char data;              // data item
    
    // open file
    fin = fopen(meta_file, "r");
    
    // check if file is okay
    if(fin == NULL)
    {
        exit(1);
    }
    
    // skip header info
    fseek(fin, 25, SEEK_CUR);
    
    // while we haven't hit the end of the file find out how much is in there
    while ((data = fgetc(fin)) != EOF)
    {
        // if a data item is a space don't count it
        if(data != ' ')
        {
            counter += 1;
        }
    }
    
    // reset to beginning of the file
    rewind(fin);
    
    // set position to metadata
    fseek(fin, 25, SEEK_CUR);
    
    // allocate memory for meta data
    meta_data = (char*) malloc(counter+1);
    // reset counter
    counter = 0;
    
    // while we haven't reached the end of the file
    while ((data = fgetc(fin)) != EOF)
    {
        // if data item is not a space add it to the meta_data
        if(data != ' ')
        {
            meta_data[counter]=data;
            counter+=1;
        }
    }
    
    // close file
    fclose(fin);

}


//RR_schedualing( )
void RR_scheduling( struct CONFIG config_data, struct PCB *pcb, char *config_file, char *meta_file)
{
    time_t start, end;      // timer variables
    double elapsed_time;    // elapsed time for operations
    char *out_string;       // holds output to file
    PROCESS *popped;        // holds a process popped from queue
    INT *interrupt_head;    // holds pointer to interrupt queue
    INT *popped_int;        // popped interrupt
    
    // check if in child process
    if(PCB->head.pid == 0)
    {
        // call start processes - PASS In config_data?
        start_processes(pcb, config_file, meta_file);
        
        // while there are processes in the queue
        while(pcb->head != NULL)
        {
            // pop a process
            popped = pcb.head;
            // set head to next
            pcb.head = pcb.head->next;
            // set popped to NULL
            popped->next = NULL;
            // if there are interrupts in the queue process them
            while(interrupt_head != NULL)
            {
                // pop an interrupt off the queue
                popped_int = interrupt_head;
                // set the head to the next interrupt
                interrupt_head = interrupt_head->next;
                // call interrupt function
                interrupt(interrupt_head, config_data.out_path, config_data.log);
            }
            // call instruction function
            instruction(popped, config_data, interrupt_head);
            // if the popped process is not finished put it at the end of the queue
            if(popped.completion_counter != 0)
            {
                popped = PCB.tail->next;
            }
            
        }
    }
    
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

