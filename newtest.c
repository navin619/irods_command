/* This is a very simple test of the irods standard IO emulation
  library.  When using standard i/o, include stdio.h; to change to
  using isio, change stdio.h to isio.h. */

/* include <stdio.h> */
#include "isio.h"   /* the irods standard IO emulation library */
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

void partial_transfer(char *filefrom,char *fileto , char *content)
{
FILE *FI, *FO;
    int i1,i2,i3;
    int count, rval, wval,filesize,readCount;
    int ichar;
	 readCount =atoi(content);
    char buf[readCount];
    int seekPos;

   	printf("The partial file in irods is %s and %s",filefrom,fileto);
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
 
	memset(buf, 0, sizeof(buf));

       rval = fread(buf, 1, readCount, FI);
       printf("rval=%d\n",rval);
       //memset(buf, NULL, sizeof(buf));
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

/*if (argc >= 4) {
       long seekPos;
       seekPos=atol(argv[3]);
       fseek(FO, seekPos, SEEK_CUR);
    }*/

    bufsize = sizeof(buf);

   /* if (argc >= 5) {
      // int i;
     //  i = atoi(argv[4]);
       if (i > bufsize) {
	  perror("buffer size is too big");
	  exit(-4);
       }
       if (i <= 0) {
	  perror("invalid buffer size");
	  exit(-5);
       }
       bufsize=i;
    }*/

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
    int pflag=0, fflag=0;
    char buf[1024*100];
    int bufsize;

while ((c = getopt(argc, argv, "pf")) != -1)
{
switch (c) {
             
   case 'p':
             pflag = 1;
             partial_transfer(argv[2], argv[3],argv[4]);
         	break;

    case 'f':
	     fflag = 1;
printf("Call the fuction\n");
		full_transfer(argv[2], argv[3]);
		
	       break;

}
}

 /*   if (argc < 3) {
      printf("newtest file-in file-out [seek-position] [buffersize] \n");
      exit(-1);
    }

     FI = fopen(argv[1],"r");
    if (FI==0)
    {
        fprintf(stderr,"can't open input file %s\n",argv[1]);
        exit(-2);
    }

    FO = fopen(argv[2],"w");
    if (FO==0) {
        fprintf(stderr,"can't open output file %s\n",argv[2]);
        exit(-3);
    }
    
    if (argc >= 4) {
       long seekPos;
       seekPos=atol(argv[3]);
       fseek(FO, seekPos, SEEK_CUR);
    }

    bufsize = sizeof(buf);

    if (argc >= 5) {
       int i;
       i = atoi(argv[4]);
       if (i > bufsize) {
	  perror("buffer size is too big");
	  exit(-4);
       }
       if (i <= 0) {
	  perror("invalid buffer size");
	  exit(-5);
       }
       bufsize=i;
    }

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
    exit(0);*/
}


