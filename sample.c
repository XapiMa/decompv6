#define N 41
// 4 * 8 + 7 + 1 +1(改行記号)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char * argv[]){
    char addr[N];
    unsigned char buf[sizeof(struct in6_addr)];
    int i,j;

    int len;
    FILE * fp;
    fp = fopen(argv[1],"r");
    if( fp == NULL ) {
        // printf("%s file not open!\n", argv[1]);
        return -1;
    }
    // printf("%s file opened!\n", argv[1]);
    while(fgets(addr, N, fp) != NULL) {
        addr[strlen(addr)-1]='\0'; // 改行文字の削除
        inet_pton(AF_INET6, addr, buf);
        printf("%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x\n",buf[0],buf[1],buf[2],buf[3],buf[4],buf[5],buf[6],buf[7],buf[8],buf[9],buf[10],buf[11],buf[12],buf[13],buf[14],buf[15]);
    }
    fclose(fp);
    return 0;
}
