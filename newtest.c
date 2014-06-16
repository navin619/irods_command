/* This is a very simple test of the irods standard IO emulation
  library.  When using standard i/o, include stdio.h; to change to
  using isio, change stdio.h to isio.h. */

/* include <stdio.h> */
#include "isio.h"   /* the irods standard IO emulation library */
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

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

void full_transfer(char *filefrom,char *fileto )
{
	FILE *FI, *FO;
        int count, rval, wval;
	char buf[1024*100];
        int bufsize;

   	printf("The full file in irods is %s and %s",filefrom,fileto);

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
      printf("buffer size=%d\n",bufsize);
      rval = fread(&buf[0], 1, bufsize, FI);
      printf("rval=%d\n",rval);
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
while ((c = getopt(argc, argv, "i:o:d:r:")) != -1)
{
switch (c) {
             
   case 'i':
	inputfile=optarg;
	printf("the input file %s\n",optarg);
	pflag = 1;
	break;

    case 'o':
	outputfile=optarg;
	fflag = 1;
	printf("the output file %s\n",optarg);
	break;

     case 'h':
	hflag = 1;
	printf("-f <irods :filename> <filename> (for full transfer of a file from irods to local directory )\n");
	printf("-p <irods :filename> <filename> <number of characters> (for partial transfer of a file from irods to local directory )\n");		
	break;

case 'r':
	printf("the range file %s \n",optarg);
	from=strtok(optarg, search);
	to =strtok(NULL, search);
	printf("the range file from %d to %d \n",atoi(from),atoi(to));
	rflag=1;
	break;




}


}


if(rflag == 0)
{
     full_transfer(inputfile, outputfile);

}
if(rflag == 1)
{
     partial_transfer(inputfile, outputfile,atoi(from),atoi(to));

}

}


