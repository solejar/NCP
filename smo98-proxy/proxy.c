/*
 * proxy.c - A Simple Sequential Web proxy
 *
 * Course Name: 14:332:456-Network Centric Programming
 * Assignment 2
 * Student Name: Sean Olejar
 *
 * IMPORTANT: Give a high level description of your code here
 1) opens up file descriptor to socket on provided portno
 2) sit and poll for a request on the socket.
 3) when a request is received, parse out it's URI components (URL, hostname, portno)
 4) open up the client connection to the requested resource
 5) receive the response in chunks, send those chunks back to the browser
 6) write a log of the request/response size/ time
 7) close all necessary fd's

 */

#include "csapp.h"

/*
 * Function prototypes
 */
void format_log_entry(char *logstring, struct sockaddr_in *sockaddr, char *uri, int size);

//A function I wrote that allows me to parse out specific components of the request url
//currently it can parse out the "url" (url for a specific resource),"host", or "port"
//it stores the parsed component into the outputStr
void parseRequest(char * request, char *infoName, char * outputStr){

    int index = 0;
    char *iter = request;
    int spaces = 0;

    //this is the first line
    while (*iter!='\n'){
        if(*iter==' '){
            spaces++;
        }else if(spaces==1){
            //parse out the URL
            if(strcmp(infoName,"url")==0){
                outputStr[index] = *iter;
                index++;
            }

        }else if(spaces==2){
            if(strcmp(infoName,"url")==0){
                return;
            }
        }

        iter++;
    }
    iter++;
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
                    //parsing the hostname
                    outputStr[index] = *iter;
                    index++;
                }

                iter++;
            }

        }else if(colons==2){

            iter++;
            while(*iter!=':'){

                if(*iter=='\n'||*iter==' '||*iter==13){
                    return;
                }else if(strcmp(infoName,"port")==0){
                    //parsing the portno
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

    //declare some variables ahead of time
    int listenfd, browserfd, bytesRead, port;
    socklen_t clientlen;
    struct sockaddr_in clientaddr;
    char buffer[MAXLINE];

    /* Check arguments */
    if (argc != 2) {
	       fprintf(stderr, "Usage: %s <port number>\n", argv[0]);
	       exit(0);
    }

    //turn port into an int
    port = atoi(argv[1]);

    //open the connection to the socket
    listenfd = Open_listenfd(port);

    printf("Listening on port: %d\n", port);

    while(1){

        clientlen = sizeof(clientaddr);
        printf("Server is listening for requests...\n");

        browserfd = Accept(listenfd,(SA *) &clientaddr, &clientlen);

        //wait until a request is read in
        bytesRead = read(browserfd, buffer, sizeof(buffer));

        if(bytesRead<0){
            perror("no bytes were read");
            exit(0);
        }

        //the request is in buffer at this point and time
        buffer[bytesRead] = 0;

        //some strings to hold the parsed URI components
        char reqHost[MAXLINE];
        char reqPort[MAXLINE];
        char reqUrl[MAXLINE];

        //parse the URI components
        parseRequest(buffer,"host",reqHost);
        parseRequest(buffer,"port",reqPort);
        parseRequest(buffer,"url",reqUrl);

        int portno;
        //logic to use the default portno if none is specified
        printf("port: %s\n",reqPort);
        if(strcmp(reqPort,"")==0){
            portno = 80;
        }else{
            portno = atoi(reqPort);
        }

        //some basic print statements showing what request was encountered
        printf("host: %s\n",reqHost);
        printf("port as int: %d\n", portno);
        printf("url: %s\n",reqUrl);

        //open up the connection to the requested host/port
        int serverfd = open_clientfd(reqHost,portno);

        if(serverfd<0){
            printf("serverfd: %d",serverfd);
            exit(-1);
        }

        //write the request to the server
        if(write(serverfd,buffer,bytesRead)<0){
            perror("write");
            exit(-1);
        }

        //read in the response in chunks
        bytesRead = 0;
        int lastRead = 0;
        while((lastRead = read(serverfd,buffer,MAXLINE))>0){
            //write back what is read to the browser
            if ( write(browserfd, buffer, lastRead) < 0 ){
                perror("write");
                exit(-1);
            }

            bytesRead += lastRead;
        }

        // log the request and how many bytes were sent back

        printf("%d bytes sent\n", bytesRead);
        char logStr[200];

        //generate the log string
        format_log_entry(logStr, &clientaddr,reqUrl, bytesRead );

        //write it to the file
        FILE *logfile = fopen("requestLog.txt","a");
        if(logfile==NULL){
            perror("error opening log file");
            exit(-1);
        }
        fprintf(logfile,"%s\n",logStr);
        fclose(logfile);

        //close fd before starting again
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
