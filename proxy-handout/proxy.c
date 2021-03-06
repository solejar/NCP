/*
 * proxy.c - A Simple Sequential Web proxy
 *
 * Course Name: 14:332:456-Network Centric Programming
 * Assignment 2
 * Student Name: Sean Olejar
 *
 * IMPORTANT: Give a high level description of your code here. You
 * must also provide a header comment at the beginning of each
 * function that describes what that function does.
 */

#include "csapp.h"

/*
 * Function prototypes
 */
void format_log_entry(char *logstring, struct sockaddr_in *sockaddr, char *uri, int size);

void parseRequest(char * request, char *infoName, char * outputStr){

    int index = 0;
    //skip first line

    char *iter = request;

    int spaces = 0;
    printf("about to skip the first line \n");
    while (*iter!='\n'){
        printf("char: %c\n",*iter);
        if(*iter==' '){
            spaces++;
        }else if(spaces==1){
            printf("char: %c\n",*iter);
            if(strcmp(infoName,"url")==0){
                outputStr[index] = *iter;
                printf("tempstr: %s\n",outputStr);
            }

        }else if(spaces==2){
            if(strcmp(infoName,"url")==0){
                return;
            }
        }

        iter++;
    }
    iter++; //this is now at the second line
    int colons = 0;

    //let's parse the second line for port and hostname
    while(*iter!='\n'){

        if(colons==0){
            while(*iter!=':'){
                iter++;
            }

        }else if(colons==1){
            iter+=2;
            while(*iter!=':'){
                if(*iter=='\n'||*iter==' '||*iter==13){
                    return;
                }else if(strcmp(infoName,"host")==0){

                    outputStr[index] = *iter;
                    index++;
                }

                iter++;
            }


        }else if(colons==2){
            printf("colons are 2");
            while(*iter!=':'){
                if(*iter=='\n'||*iter==' '||*iter==13){
                    return;
                }else if(strcmp(infoName,"port")==0){
                    outputStr[index] = *iter;
                    index++;
                };

                iter++;
            }

        }else if(colons==3){
            return;
        }

        colons++;
    }
}
/*
 * main - Main routine for the proxy program
 */
int main(int argc, char **argv)
{

    int listenfd, browserfd, port, clientlen;
    struct sockaddr_in clientaddr;

    int serverfd,bytesRead;
    char buffer[MAXLINE];

    /* Check arguments */
    if (argc != 2) {
	       fprintf(stderr, "Usage: %s <port number>\n", argv[0]);
	       exit(0);
    }

    port = atoi(argv[1]);

    listenfd = Open_listenfd(port); //create a socket and bind it to a given port.
    FILE *logfile = fopen("requestLog.txt","a");

    printf("port: %d\n", port);

    while(1){

        clientlen = sizeof(clientaddr);

        printf("Server is listening for client connection requests...\n");

        browserfd = Accept(listenfd,(SA *) &clientaddr, &clientlen);

        bytesRead = read(browserfd, buffer, sizeof(buffer));

        if(bytesRead<0){
            perror("no bytes were read");
            exit(0);
        }

        //the request is in buffer at this point and time
        buffer[bytesRead] = 0;
        printf("bytesRead: %d\n",bytesRead);
        printf("buffer: %s\n",buffer);

        char reqHost[MAXLINE];
        char reqPort[MAXLINE];
        char reqUrl[MAXLINE];

        parseRequest(buffer,"host",reqHost);
        parseRequest(buffer,"port",reqPort);
        //parseRequest(buffer,"url",reqUrl)

        int portno;
        if(strcmp(reqPort,"")==0){
            portno = 80;
        }else{
            portno = atoi(reqPort);
        }

        printf("host as: %s\n",reqHost);
        printf("port as int: %d\n", portno);
        printf("url: %s\n",reqUrl);

        int serverfd = open_clientfd(reqHost,portno);

        if(serverfd<0){
            printf("serverfd: %d",serverfd);
            exit(-1);
        }

        if(write(serverfd,buffer,bytesRead)<0){
            perror("write");
            exit(-1);
        }

        bytesRead = 0;
        int lastRead = 0;
        while((lastRead = read(serverfd,buffer,MAXLINE))>0){
            if ( write(browserfd, buffer, lastRead) < 0 ){
                perror("write");
                exit(-1);
            }

            bytesRead += lastRead;
        }

        // log the request and how many bytes were sent back

        printf("%d bytes sent\n", bytesRead);

        close(browserfd);
    }

    exit(0);
}

/*
 * format_log_entry - Create a formatted log entry in logstring.
 *
 * The inputs are the socket address of the requesting client
 * (sockaddr), the URI from the request (uri), and the size in bytes
 * of the response from the server (size).
 */
void format_log_entry(char *logstring, struct sockaddr_in *sockaddr,
		      char *uri, int size)
{
    time_t now;
    char time_str[MAXLINE];
    unsigned long host;
    unsigned char a, b, c, d;

    /* Get a formatted time string */
    now = time(NULL);
    strftime(time_str, MAXLINE, "%a %d %b %Y %H:%M:%S %Z", localtime(&now));

    /*
     * Convert the IP address in network byte order to dotted decimal
     * form. Note that we could have used inet_ntoa, but chose not to
     * because inet_ntoa is a Class 3 thread unsafe function that
     * returns a pointer to a static variable (Ch 13, CS:APP).
     */
    host = ntohl(sockaddr->sin_addr.s_addr);
    a = host >> 24;
    b = (host >> 16) & 0xff;
    c = (host >> 8) & 0xff;
    d = host & 0xff;


    /* Return the formatted log entry string */
    sprintf(logstring, "%s: %d.%d.%d.%d %s", time_str, a, b, c, d, uri);
}
