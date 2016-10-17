typedef struct
{
  char* buffer[HISTORY_SIZE][ARGS_ARRAY_SIZE];
  int currentcmd;
} history_t;

typedef struct
{
  char* buffer[HISTORY_SIZE][ARGS_ARRAY_SIZE];
  int currentjob;
} jobList;

  // Function Declarations:
  void printCommand (history_t* history);
  char* concatenate (char* array[], char* commandList);
  void add_spaces(char *dest, int num_of_spaces);
  void redirect (char* file);
  void piping (char* piping_args[]);
  char* retrieveCommand (history_t* history, int i);


history_t* history;
jobList* jobs;