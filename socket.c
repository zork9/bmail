/*
# Copyright (C) Johan Ceuppens 2013
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <errno.h>
    #include <string.h>
    #include <netdb.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <sys/socket.h>

    #define PORT 110 
    // max number of bytes we can get at once
    #define MAXDATASIZE 300

    int clientsock(char **buffybuf)
    {

    char *hostname = "soft.vub.ac.be";
    char *user = "USER joe\r\n"; 
    char *password = "PASS joepass\r\n"; 

    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in their_addr;

    he=gethostbyname(hostname);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
     
    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(PORT);
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(their_addr.sin_zero), '\0', 8);

    connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr));

    numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0);
    memset(buf, MAXDATASIZE, 0);
    numbytes = send(sockfd, user, 15,0);
    numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0);
    memset(buf, MAXDATASIZE, 0);
    numbytes = send(sockfd, password, 15,0);
    numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0);
    sprintf(*buffybuf, "%s", buf);

    buf[numbytes] = '\0';
    close(sockfd);
    return 0;
}
