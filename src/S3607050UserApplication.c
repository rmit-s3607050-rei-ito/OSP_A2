/*
  COSC1114 Assignment 2
  Author: Rei Ito (s3607050)
  NOTE: Heavily influenced by work done by: SolidusCode & Derek Molloy
*/

#include "S3607050UserApplication.h"

static char recieve[BUFFER_LEN];

bool valid_input(char *string, unsigned len)
{
  bool valid = false; //valid flag
  char input[BUFFER_LEN+2]; //string
  char *usrInp; //user input
  int inpLen; //input length
  
  while (!valid) { //check valid input loop
    printf("UserApp: please input a string to send to the driver (100 char max):
      \n");
    usrInp = fgets(input, len+2, stdin); //user input
    inpLen = strlen(input); //length
    
    if (usrInp == NULL) { //empty input
      return false;
    }
      
    if (strcmp(usrInp, "\n") == 0) { //enter
      input[inpLen-1] = '\0';
      return false;
    }
    
    if (input[inpLen-1] != '\n') { //input too long
      printf("UserApp: invalid input (%s), try again\n", input);
      int ch;
      while (ch = getc(stdin), ch != '\n' && ch != EOF)
        ;
      clearerr(stdin);
    }
    else {
      valid = true;
    }
  }
  
  input[inpLen-1] = '\0'; //clear '\n'
  strcpy(string, input); //set new string
  return true;
}

int main()
{
  int ret, fd; //check, device
  char send[BUFFER_LEN]; //string to send
  printf("UserApp: starting test\n");
  fd = open(DEVICE, O_RDWR); // open device
  if (fd < 0) { //check valid open
    perror("UserApp: failed to open device");
    return errno;
  }
  
  if (!valid_input(send, BUFFER_LEN)) { //check valid input
    perror("UserApp: invalid input");
    return errno;
  }
  
  ret = write(fd, send, strlen(send)); //send to device
  if (ret < 0) { //check valid send
    perror("UserApp: failed to write to device");
    return errno;
  }
  
  ret = read(fd, recieve, BUFFER_LEN); //read from device
  if (ret < 0) { //check valid read
    perror("UserApp: failed to read from device");
    return errno;
  }

  //print & end
  printf("UserApp: 's' recieved from device\n", recieve);
  return 0;
}
