#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <peekpoke.h>

#define README_FILENAME "D:README.DOC"
#define BUFSIZE 8192

static char device[12];
static char ch;
static short i;
static short len;
static FILE* sfp;
static FILE* dfp;
static char* buf;

void press_any_key(void)
{
  cprintf("\r\n\r\n Press any key to return to DOS. ");
  ch=cgetc();
}

void output_screen(void)
{
  POKE(82,2);
  clrscr();
  putchar(' ');
  putchar(' ');
  sfp=fopen(README_FILENAME,"r");
  while (len=fread(buf,sizeof(unsigned char),BUFSIZE,sfp))
    {
      for (i=0;i<len;++i)
	{
	  putchar(buf[i]);
	}
    }
  fclose(sfp);
  press_any_key();
}

void output_printer(void)
{
  sfp=fopen(README_FILENAME,"r");
  dfp=fopen(device,"w");

  cprintf("\r\n\r\n             Printing...");
  
  while (len=fread(buf,sizeof(unsigned char),BUFSIZE,sfp))
    {
      if (fwrite(buf,sizeof(unsigned char),len,dfp) != len)
	{
	  fclose(sfp);
	  fclose(dfp);
	  exit(1);
	}
    }
  fclose(sfp);
  fclose(dfp);

  press_any_key();

}

void main(void)
{
  buf=malloc(BUFSIZE);
  clrscr();
  revers(1);
  cprintf("                                        ");
  cprintf("        PLATOTerm Documentation         ");
  cprintf("                                        ");
  revers(0);
  cprintf("\n\n");
  cprintf("        Send Documentation to:          \r\n");
  cprintf("\n");
  cprintf("             (S)creen                   \r\n");
  cprintf("             (P)rinter                  \r\n");
  cprintf("             (Q)uit                     \r\n");
  cprintf("\n");
  cprintf("             Select: ");
  cursor(1);
  ch=cgetc();
  cursor(0);
  switch(ch)
    {
    case 'S':
    case 's':
      output_screen();
      break;
    case 'P':
    case 'p':
      strcpy(device,"P:");
      output_printer();
      break;
    case 'Q':
    case 'q':
      exit(0);
    }

  free(buf);
}
