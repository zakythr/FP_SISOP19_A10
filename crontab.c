#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pthread.h>

pthread_t tid[1000];
char filename[1000]="/home/gede/efpe/crontab.data";

void* doSomeThing(void *arg)
{
    char kk[1000], delim[]=" ";
    sprintf(kk, "%s", (char*)arg);
    int menit=-1, jam=-1, hari=-1, bulan=-1, harii=-1;
    int menit2=-1, jam2=-1, hari2=-1, bulan2=-1, harii2=-1;
    char perintah[1000];
    char *hasil[1000];
    char *command;
    int hu=0;

    char *ptr = strtok(kk, delim);

    if(strcmp(ptr, "*")!=0)
    {
        menit=atoi(ptr);
        if((menit==0 && strcmp(ptr, "0")!=0) || (menit>59 || menit<0))
        {
            return NULL;
        }
    }

    ptr = strtok(NULL, delim);
    if(strcmp(ptr, "*")!=0)
    {
        jam=atoi(ptr);
        if((jam==0 && strcmp(ptr, "0")!=0)||(jam>23 || jam<0))
        {
            return NULL;
        }
    }

    ptr = strtok(NULL, delim);
    if(strcmp(ptr, "*")!=0)
    {
        hari=atoi(ptr);
        if(hari==0 && strcmp(ptr, "0")!=0)
        {
            return NULL;
        }
    }

    ptr = strtok(NULL, delim);
    if(strcmp(ptr, "*")!=0)
    {
        bulan=atoi(ptr);
        if((bulan==0 && strcmp(ptr, "0")!=0) || (bulan<1 || bulan>12))
        {
            return NULL;
        }
    }

    ptr = strtok(NULL, delim);
    if(strcmp(ptr, "*")!=0)
    {
        harii=atoi(ptr);
        
        if((harii==0 && strcmp(ptr, "0")!=0) || (harii>6 || harii<0))
        {
            return NULL;
        }
    }

    ptr = strtok(NULL, delim);
    sprintf(perintah, "%s", ptr);
    char perintah2[1000];
    sprintf(perintah2, "%s", perintah);
    command=strrchr(perintah2, '/');
    for(int cc=0; cc<strlen(command); cc++)
	{
		command[cc]=command[cc+1];
	}
    hasil[hu]=command;
    hu++;
    while (ptr != NULL)
    {
        if(hu!=1)
        {
            hasil[hu-1]=ptr;
        }
        hu++;
        ptr = strtok(NULL, delim);
    }
    hu--;

    while(1)
    {
        char lala[1000]="/home/gede/efpe/lala";
        mkdir(lala, 0777);

        time_t now;
        time(&now);
        
        struct tm *local = localtime(&now);

        if(menit != -1)
        {
            if(menit==local->tm_min)
            {
                menit2=1;
            }
            else
            {
                menit2=0;
            }
        }
        if(jam != -1)
        {
            if(jam==local->tm_hour)
            {
                jam2=1;
            }
            else
            {
                jam2=0;
            }
        }
        if(hari != -1)
        {
            if(hari==local->tm_mday)
            {
                hari2=1;
            }
            else
            {
                hari2=0;
            }
        }
        if(bulan != -1)
        {
            if(bulan==local->tm_mon+1)
            {
                bulan2=1;
            }
            else
            {
                bulan2=0;
            }
        }
        if(harii != -1)
        {
            if(harii==local->tm_wday)
            {
                harii2=1;
            }
            else
            {
                harii2=0;
            }
        }

        if(menit2!=0 && jam2!=0 && hari2!=0 && bulan2!=0 && harii2!=0 && local->tm_sec==0)
        {
            pid_t child;
            child=fork();
            if(child==0)
            {
                execv(perintah, hasil);
            }
            sleep(1);
        }
        sleep(1);
    }
    return NULL;
}

void buat_thread(char *filenya, int n)
{
    pthread_create(&(tid[n]), NULL, &doSomeThing, filenya);
    char yeay[1000]="/home/gede/efpe/yeay";
    mkdir(yeay, 0777);
}

void baca_isi()
{
    char c;
    char lama[1000];
    FILE *fptr;
    int angka=0;
    fptr = fopen(filename, "r");
    c = fgetc(fptr); 
    while (c != EOF) 
    {
        lama[angka]=c;
        angka++;
        c = fgetc(fptr); 
    } 
    fclose(fptr);
    lama[angka]='\0';

    int init_size = strlen(lama);
	char delim[] = "\n";
    char *simpen[1000];
    char semen[1000];
    sprintf(semen, "%s", lama);
	char *ptr = strtok(semen, delim);
    int seq=0;

    while(ptr != NULL)
    {
        simpen[seq]=strdup(ptr);
        ptr = strtok(NULL, delim);
        seq++;    
    }

    for(int ii=0; ii<seq; ii++)
    {
        buat_thread(simpen[ii], ii);
    }
}

void kensel_thread(int n)
{
    pthread_cancel(tid[n]);
}

int main() {
    int err;
    
    pid_t pid, sid;
    struct stat sb;
    long int gettime;
    
    int seq=0;
    stat(filename, &sb);
    gettime=sb.st_mtime;

    pid = fork();

    baca_isi();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();

    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/home/gede/")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while(1) {
        char lalp[1000]="/home/gede/efpe/lalp";
        mkdir(lalp, 0777);
        
        stat(filename, &sb);
        printf("--%ld--%ld\n", gettime, sb.st_mtime);
    
        if(gettime<sb.st_mtime)
        {
            char lals[1000]="/home/gede/efpe/lals";
            mkdir(lals, 0777);
            gettime=sb.st_mtime;
            sleep(1);

            for(int ii=0; ii<seq; ii++)
            {
                kensel_thread(ii);
            }

            baca_isi();
            printf("yeay\n");
        }
        sleep(1);
    }

    exit(EXIT_SUCCESS);
}
