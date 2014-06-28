/* This is a very simple test of the irods standard IO emulation
  library.  When using standard i/o, include stdio.h; to change to
  using isio, change stdio.h to isio.h. */

/* include <stdio.h> */
#include "isio.h"   /* the irods standard IO emulation library */
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
/*
 * filefrom : The input file from irods to  be transfered 
 * fileto   : The output file to be written to in the local drive
 * start    : the offset position from where the file has to be copied
 * finish   : the final offset position to which the file has to be copied
*/
void partial_transfer(char *filefrom,char *fileto , int start, int finish)
{
FILE *FI, *FO;
    int i1,i2,i3;
    int count, rval, wval,filesize,readCount;
    int ichar;
	 readCount =finish;
    char buf[readCount];
    int seekPos;



   	printf("The partial file in irods is %s and %s",filefrom,fileto);
	 FI = fopen(filefrom,"r");
    if (FI==0)
    {
        fprintf(stderr,"can't open input file %s\n",filefrom);
        exit(-2);
    }

       seekPos=start;
       fseek(FI, seekPos, SEEK_SET);

    FO = fopen(fileto,"w");
    if (FO==0) {
        fprintf(stderr,"can't open output file %s\n",fileto);
        exit(-3);
    }
 
	memset(buf, 0, sizeof(buf));

       rval = fread(buf, 1, readCount, FI);
       printf("rval=%d\n",rval);
        printf("%s",buf);


        wval = fwrite(buf,sizeof(buf), 1, FO);



    fclose(FI);
    fclose(FO);
}

/*
 * filefrom : The input file from irods to  be transfered 
 * fileto   : The output file to be written to in the local drive
 */
void full_transfer(char *filefrom,char *fileto )
{
	FILE *FI, *FO;
        int count, rval, wval;
	char buf[1024*100];
        int bufsize;

//   	printf("The full file in irods is %s and %s",filefrom,fileto);

    FI = fopen(filefrom,"r");
    if (FI==0)
    {
        fprintf(stderr,"can't open input file %s\n",filefrom);
        exit(-2);
    }

    FO = fopen(fileto,"w");
    if (FO==0) {
        fprintf(stderr,"can't open output file %s\n",fileto);
        exit(-3);
    }



    bufsize = sizeof(buf);

     do {
      memset(buf, 0, sizeof(buf));
     // printf("buffer size=%d\n",bufsize);
      rval = fread(&buf[0], 1, bufsize, FI);
      //printf("rval=%d\n",rval);
      if (rval < 0) {
	perror("read stream message");
      }
      if (rval > 20) {
	wval = fwrite(&buf[0], 1, rval, FO);
	if (wval < 0) {
	  perror("fwriting data:");
	}
      }
    } while (rval > 0);
    fclose(FI);
    fclose(FO);

}

main(int argc, char **argv)
{


    FILE *FI, *FO;
    int i1,i2,i3,c;
    int count, rval, wval;
    int pflag=0, fflag=0,hflag = 0,rflag=0, range=0;
    char buf[1024*100];
    char *inputfile;
    char * outputfile;
    int bufsize;
    char *from;
    char *to;
    char *search = "-";
     char *irods = "irods:";
     int pipefd[2];
	char *result;

/*char *result = (char*)malloc((strlen(inputfile) + strlen(irods) + 1));
strcpy(result, irods);
	strcat(result, inputfile);
	strcat(irods,inputfile);
	printf("the input file %s\n",result);*/
while ((c = getopt(argc, argv, "i:o:r:h")) != -1)
{
switch (c) {
   // input file from irods
   case 'i':
	//printf("we are in the ---i loop");
	inputfile=optarg;
	pflag = 1;
	break;
   // output file in the local drive
    case 'o':
	outputfile=optarg;
	fflag = 1;
//	printf("the output file %s\n",optarg);
	break;
   // help command
     case 'h':
	hflag = 1;
	printf("-i <irods :filename> -o < local drive filename> (for full transfer of a file from irods to local directory )\n");
	printf("-i <irods :filename> -o < local drive filename> -r <range ofnumber of characters> (for partial transfer of a file from irods to local directory )\n");		
	break;
   // range to be copied
     case 'r':
//	printf("the range file %s \n",optarg);
	from=strtok(optarg, search);
	to =strtok(NULL, search);
//	printf("the range file from %d to %d \n",atoi(from),atoi(to));
	rflag=1;
	break;

}


}

if(pflag==1)
{
//	printf("we are in the loop");
	result = (char*)malloc((strlen(inputfile) + strlen(irods) + 1));
	strcpy(result, irods);
	strcat(result, inputfile);
	//strcat(irods,inputfile);
	//inputfile=
	//printf("the input file %s\n",result);
}


if(pflag == 0 && hflag == 0)
{
	printf("Please enter the input file in format -i <filename>\n");
	exit(0);
}

// file to be copied completly
if(rflag == 0 && fflag == 1 && pflag == 1)
{
     full_transfer(result, outputfile);

}

// file to be copied partially
if(rflag == 1 && fflag == 1 && pflag == 1)
{
      partial_transfer(inputfile, outputfile,atoi(from),atoi(to));

}

if(fflag == 0 && rflag == 0 && pflag == 1 )
{
//printf("the files are in pipe and are and ++++\n");


 FI = fopen(inputfile,"r");
    if (FI==0)
    {
        fprintf(stderr,"can't open input file %s\n",inputfile);
        exit(-2);
    }
//printf("after opening the file\n");
int c;
  if(FI)
	{
		while((c=fgetc(FI))!=EOF)
		 putchar(c);
    fclose(FI);
}
}
if(hflag = 1 )
{

}


}


