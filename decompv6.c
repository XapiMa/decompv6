#define N 41
// 4 * 8 + 7 + 1 +1(改行記号)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char * add_zero(char * str,char * now);
void zeroPrint(char *,int);

char zero[] = "0000:0000:0000:0000:0000:0000:0000:0000";

int main(int argc, char * argv[]){
    char addr[N];
    int len;
    FILE * fp;
    fp = fopen(argv[1],"r");
    if( fp == NULL ) {
        // printf("%s file not open!\n", argv[1]);
        return -1;
    } else {
        time_t befor = time(NULL);
        // printf("%s file opened!\n", argv[1]);
        while(fgets(addr, N, fp) != NULL) {
            len = strlen(addr);
            addr[len-1]=':'; // 文末の余計な改行文字の削除
            zeroPrint(addr,len);
        }
        time_t after = time(NULL);
        printf("%fs\n",(double)after-(double)befor);
    }
    fclose(fp);

    return 0;
}

void zeroPrint(char * plane,int len){
    char tmp[N],* now;
    int Colon_Count;

    // コロンの数を数える
    Colon_Count = 0;
    while(1) {
        if(*plane==':') {
            if(*(plane + 1) == '\0' ) {
                *plane='\0';
                break;
            }
            Colon_Count++;
        }
        plane++;
    }
    plane -= len-1;

    char *tp, *head, *tail;

    // :: の場合
    if(Colon_Count == 2) {
        puts(zero);
        return;
    }

    strcpy(tmp,zero);
    now = tmp;

    //strtokもどき
    tp = strstr(plane,"::");
    if(tp) {
        *tp = '\0';
        head = plane;
        tail = tp + 2;

        if(*head != '\0') {
            tp = strtok(head,":");
            now = add_zero(tp,now);
            while ( tp != NULL ) {
                tp = strtok( NULL,":" );
                if ( tp != NULL ) {
                    now = add_zero(tp,now);
                }
            }
        }else{
            // :: 前後どちらかがない場合余分にpaddingが必要
            now+=5;
        }

        now += (8 - Colon_Count)*5;

        if(*tail != '\0') {
            tp = strtok(tail,":");
            now = add_zero(tp,now);
            while ( tp != NULL ) {
                tp = strtok( NULL,":" );
                if ( tp != NULL ) {
                    now = add_zero(tp,now);
                }
            }
        }
    }else{
        tp = strtok(plane,":");
        now = add_zero(tp,now);
        while ( tp != NULL ) {
            tp = strtok( NULL,":" );
            if ( tp != NULL ) {
                now = add_zero(tp,now);
            }
        }
    }
    puts(tmp);
    return;
}

char *  add_zero(char * str,char * now){
    int n = strlen(str);
    strncpy(now + (4 - n),str,n);
    return now + 5;
}
