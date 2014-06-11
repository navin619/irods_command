/* This is a very simple test of the irods standard IO emulation
  library.  When using standard i/o, include stdio.h; to change to
  using isio, change stdio.h to isio.h. */

/* include <stdio.h> */
#include "isio.h"   /* the irods standard IO emulation library */
#include <stdlib.h>
#include <string.h>
main(int argc, char **argv)
{
    FILE *FI, *FO;
    int i1,i2,i3;
    int count, rval, wval,filesize,readCount;
    int ichar;
    char buf[1000];
    int seekPos;
    if (argc < 3) {
      printf("test2 file-in file-out [seek-position]\n");
      exit(-1);
    }

    FI = fopen(argv[1],"r+");
    if (FI==0)
    {
        fprintf(stderr,"can't open input file %s\n",argv[1]);
        exit(-2);
    }

    FO = fopen(argv[2],"w+");
    if (FO==0) {
        fprintf(stderr,"can't open output file %s\n",argv[2]);
        exit(-3);
    }

    if (argc >= 4) {
       readCount=atoi(argv[3]);
    }

memset(buf, 0, sizeof(buf));

rval = fread(buf, 1, readCount, FI);
    printf("rval=%d\n",rval);
//memset(buf, NULL, sizeof(buf));
printf("%s",buf);


wval = fwrite(buf,sizeof(buf), 1, FO);



    fclose(FI);
    fclose(FO);
    exit(0);
}
