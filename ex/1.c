/**
 * @file 1.c
 * @brief XXX
 * @author XXX
 * @details XXX
 * @date XXX
 * @version XXX
 */

#include<stdio.h>
#include<stdlib.h>
#define FILEPATH "D:\\C0\\ex\\instance10.txt"
main()
{
    struct CE{
        int p;
        int e;
        int c;
        } * jobs;
    FILE *fp;
    if(!(fp=fopen(FILEPATH,"rb"))){
        puts("Fail to open file!");
        exit(-1);}

    int jobnum,i;
    fscanf(fp, "%d", &jobnum);
    printf("%d\n", jobnum);
    jobs = (struct CE *)calloc(jobnum,sizeof(struct CE));
    for (i = 0; i < jobnum;i++)
        fscanf(fp,"%d %d\n", &jobs[i].p, &jobs[i].e);
    for (i = 0; i < jobnum;i++)
        printf("%d\t%d\n", jobs[i].p,jobs[i].e);

    fclose(fp);   
    system("pause");
    return 0;
}