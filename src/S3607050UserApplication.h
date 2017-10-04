/*
  COSC1114 Assignment 2
  Author: Rei Ito (s3607050)
  NOTE: Heavily influenced by work done by: SolidusCode & Derek Molloy
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define DEVICE "/dev/S3607050Device" //device name
#define BUFFER_LEN 100 //max string size

// boolean type
typedef enum boolean
{
  false, true
} bool;

// function prototypes
bool valid_input(char *, unsigned);
