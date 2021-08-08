// Archipelago class
// Created by: Sai Samarth
// Contains the archipelago network
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include "Island.h"
//#include "FilesList.h"
using namespace std;
class ArchipelagoExpedition
{
private:
  // Create the Data Members for the Archipelago Network here
  Island *islands;    // dynamic array islands
  int allocated;      // size of array
  MyList islandQueue; // Queue
  MyFList filenames;  // List of files

public:
  // constructor
  ArchipelagoExpedition()
  {
    // creates new dynamic array of size 10
    allocated = 10;
    islands = new Island[10];
  }
  // destructor
  ~ArchipelagoExpedition()
  {
    // deletes the dynamic array islands
    delete[] islands;
  }
  // The main loop for reading in input
  void processCommandLoop(FILE *inFile)
  {
    char buffer[300];
    char *input;

    input = fgets(buffer, 300, inFile); // get a line of input

    // loop until all lines are read from the input
    while (input != NULL)
    {
      // process each line of input using the strtok functions
      char *command;
      command = strtok(input, " \n\t");

      printf("*%s*\n", command);

      if (command == NULL)
      {
        printf("Blank Line\n");
      }
      else if (strcmp(command, "q") == 0)
      {
        return;
      }
      else if (strcmp(command, "?") == 0)
      {
        // calls function to show commands
        showCommands();
      }
      else if (strcmp(command, "t") == 0)
      {
        // calls function to do check if travel is possible
        doTravel();
      }
      else if (strcmp(command, "r") == 0)
      {
        // calls function to resize the array
        doResize();
      }
      else if (strcmp(command, "i") == 0)
      {
        // calls function to insert a new ferry ride
        doInsert();
      }
      else if (strcmp(command, "d") == 0)
      {
        // calls function to delete a ferry ride
        doDelete();
      }
      else if (strcmp(command, "l") == 0)
      {
        // calls function to print the whole list of islands
        doList();
      }
      else if (strcmp(command, "f") == 0)
      {
        // calls function that reads input from files
        doFile();
      }
      else if (strcmp(command, "#") == 0)
      {
        ;
      }
      else
      {
        printf("Command is not known: %s\n", command);
      }
      input = fgets(buffer, 300, inFile); // get the next line of input
    }
  }
  // function that prints the commands of network
  void showCommands()
  {
    printf("The commands for this project are:\n");
    printf("  q\n");
    printf("  ?\n");
    printf("  #\n");
    printf("  t <int1> <int2>\n");
    printf("  r <int>\n");
    printf("  i <int1> <int2>\n");
    printf("  d <int1> <int2>\n");
    printf("  l\n");
    printf("  f <filename>\n");
  }
  // function that does the travel between two islands
  void doTravel()
  {
    int val1 = 0;
    int val2 = 0;

    // get an integer value from the input
    char *next = strtok(NULL, " \n\t");

    if (next == NULL)
    {
      printf("Integer value expected\n");
      return;
    }
    val1 = atoi(next);
    if (val1 == 0 && strcmp(next, "0") != 0)
    {
      printf("Integer value expected\n");
      return;
    }

    // get another integer value from the input
    next = strtok(NULL, " \n\t");

    if (next == NULL)
    {
      printf("Integer value expected\n");
      return;
    }
    val2 = atoi(next);
    if (val2 == 0 && strcmp(next, "0") != 0)
    {
      printf("Integer value expected\n");
      return;
    }

    printf("Performing the Travel Command from %d to %d\n", val1, val2);
    // calls the breadthFirstSearchHelper function to find the path between two islands
    MyList temp = breadthFirstSearchHelper(val1, val2);
    // print the path of island if it exists
    if (!temp.isEmpty())
    {
      printf("shortest path from %d to %d: ", val1, val2);
      temp.showPath();
    }
  }
  // function to resize the array of islands
  void doResize()
  {
    int val1 = 0;
    // get an integer value from the input
    char *next = strtok(NULL, " \n\t");

    if (next == NULL)
    {
      printf("Integer value expected\n");
      return;
    }
    val1 = atoi(next);
    if (val1 == 0 && strcmp(next, "0") != 0)
    {
      printf("Integer value expected\n");
      return;
    }
    printf("Performing the Resize Command with %d\n", val1);
    // clearing the current list of islands
    for (unsigned int i = 0; i < allocated; i++)
    {
      MyList temp = islands[i].getList();
      temp.removeAll();
    }
    // deleting the islands array and creating a new array with given size
    delete[] islands;
    islands = new Island[val1];
    allocated = val1;
  }
  // function that inserts an edge for an island
  void doInsert()
  {
    int val1 = 0;
    int val2 = 0;
    // get an integer value from the input
    char *next = strtok(NULL, " \n\t");
    if (next == NULL)
    {
      printf("Integer value expected\n");
      return;
    }
    val1 = atoi(next);
    if (val1 == 0 && strcmp(next, "0") != 0)
    {
      printf("Integer value expected\n");
      return;
    }
    // get another integer value from the input
    next = strtok(NULL, " \n\t");
    if (next == NULL)
    {
      printf("Integer value expected\n");
      return;
    }
    val2 = atoi(next);
    if (val2 == 0 && strcmp(next, "0") != 0)
    {
      printf("Integer value expected\n");
      return;
    }
    if (val1 == val2)
    {
      printf("Cannot add ferry ride to self\n");
      return;
    }
    // performs the insert command if islands are in the list
    if (val1 <= allocated && val2 <= allocated)
    {
      printf("Performing the Insert Command for %d\n", val1);
      // insets the edge if the island does not exist in current list
      if (!islands[val1 - 1].doesExist(val2))
      {
        islands[val1 - 1].insertEdgeTo(val2);
      }
      // else print invalid statements
      else
      {
        printf("Ferry ride already added!\n");
      }
    }
    else
    {
      printf("Invalid value for island\n");
    }
  }
  // function to delete a ferry ride
  void doDelete()
  {
    int val1 = 0;
    int val2 = 0;

    // get an integer value from the input
    char *next = strtok(NULL, " \n\t");

    if (next == NULL)
    {
      printf("Integer value expected\n");
      return;
    }
    val1 = atoi(next);
    if (val1 == 0 && strcmp(next, "0") != 0)
    {
      printf("Integer value expected\n");
      return;
    }

    // get another integer value from the input
    next = strtok(NULL, " \n\t");

    if (next == NULL)
    {
      printf("Integer value expected\n");
      return;
    }
    val2 = atoi(next);
    if (val2 == 0 && strcmp(next, "0") != 0)
    {
      printf("Integer value expected\n");
      return;
    }
    printf("Performing the Delete Command for %d\n", val1);
    val1--;
    // delete the ferry ride if the island is present in the list
    if (val1 < allocated && val2 < allocated)
    {
      if (islands[val1].doesExist(val2))
      {
        islands[val1].deleteEdgeTo(val2);
      }
      // print error statements if not present
      else
      {
        printf("Ferry ride does not exist\n");
      }
    }
    else
    {
      // can do this after getting number too
      printf("Invalid value for island\n");
    }
  }
  // function to print the contents of the dynamic array islands
  void doList()
  {
    printf("Displaying the adjacency list:\n");
    if (allocated > 0)
    {
      for (unsigned int i = 0; i < allocated; i++)
      {
        MyList temp = islands[i].getList();
        if (!temp.isEmpty())
        {
          printf("%d -->  ", i + 1);
          temp.show();
        }
        else
        {
          printf("%d -->\n", i + 1);
        }
      }
    }
  }
  // function that gets input from a file
  void doFile()
  {
    // get a filename from the input
    char *fname = strtok(NULL, " \r\n\t");
    if (fname == NULL)
    {
      printf("Filename expected\n");
      return;
    }
    printf("Performing the File command with file: %s\n", fname);
    //  1. verify the file name is not currently in use
    string s(fname);
    if (!filenames.isEmpty())
    {
      if (filenames.doesE(s))
      {
        // print error if file is already in use
        printf("File is already in use\n");
        return;
      }
    }
    //  2. open the file using fopen creating a new instance of FILE*
    FILE *newFile;
    if ((newFile = fopen(fname, "r")) == NULL)
    {
      // print error statement if cannot open file
      printf("Cannot open the file\n");
      return;
    }
    filenames.insertAtEnd(s);
    char line[300];
    //  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
    this->processCommandLoop(newFile);
    //  4. close the file when processCommandLoop() returns
    fclose(newFile);
    filenames.remove(s);
  }
  // BFS helper function
  // Function collects the path from one island to another if present
  // Returns the path list
  MyList breadthFirstSearchHelper(int x, int y)
  {
    // reset every prev and visited in island array to -999 and false
    for (int i = 0; i < allocated; i++)
    {
      islands[i].setPrev(-999);
      islands[i].setVisited(false);
    }
    // remove everything from islandQueue and add x to the end
    islandQueue.removeAll();
    islandQueue.insertAtEnd(x);
    if (bfs(y) == false)
    {
      // print error if there is no path
      printf("You can NOT get from island %d to island %d\n", x, y);
      // return empty list since there is no path
      islandQueue.removeAll();
      return islandQueue;
    }
    else
    {
      // Get the path
      printf("You can get from island %d to island %d\n", x, y);
      // Create a stack for pathlist
      MyList pathList;
      int currentIsland = y;
      // insert the current island
      pathList.insertAtFront(currentIsland);
      do
      {
        // add the prev of current island until current island is not x
        currentIsland = islands[currentIsland - 1].getPrev();
        pathList.insertAtFront(currentIsland);
      } while (currentIsland != x);
      // return the stack pathList
      return pathList;
    }
    // Or return the empty list
    islandQueue.removeAll();
    return islandQueue;
  }
  // Function that searches the [ath from one island to another
  bool bfs(int b)
  {
    // loop till the islandQueue is empty
    while (!islandQueue.isEmpty())
    {
      // get first value from islandQueue and pop
      int a = islandQueue.getVal();
      islandQueue.removeFromFront();
      if (a <= allocated)
      {
        // loop through the linked list of island
        MyList tmp = islands[a - 1].getList();
        for (int i = 0; i < islands[a - 1].getSize(); i++)
        {
          int c = tmp.getNthElem(i);
          if (c <= allocated)
          {
            // if the island in linked list is not visited
            if (!islands[c - 1].getVisited())
            {
              // set it to visited and set the previous island to a
              islands[c - 1].setVisited(true);
              islands[c - 1].setPrev(a);
              // if the current island is the same as destination
              if (c == b)
              {
                // return true
                return true;
              }
              // otherwise insert the island to the queue
              islandQueue.insertAtEnd(c);
            }
          }
        }
      }
      // else return false
      else
      {
        return false;
      }
    }
    return false;
  }
};

int main(int argc, char **argv)
{
  // set up the varqiable inFile to read from standard input
  FILE *inFile = stdin;
  // set up the data needed for the island adjcency list
  ArchipelagoExpedition islandData;
  // call the method that reads and parses the input
  islandData.showCommands();
  printf("\nEnter commands at blank line\n");
  printf("    (No prompts are given because of f command)\n");
  islandData.processCommandLoop(inFile);
  return 0;
}