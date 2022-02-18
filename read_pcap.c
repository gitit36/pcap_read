#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

// Initializing a structure for udp packet header
struct _udp_packet
{
	u_short port_num;
    u_short dest_num;
    u_short len;
    u_short checksum; 
};

int DATA_MAX = 65535; // Maximum size for data section
int global_header = 24; // size of global header
int packet_header = 50; // size of packet header

int main(int argc, char* argv[])
{
    // Display error message if missing arguments
    if ( argc != 2){
        printf ("Please input 2 arguments \n");
        exit(1);
    }

    FILE *fp;
    if((fp = fopen(argv[1], "rb")) == NULL)
    { 
        perror("");
        exit(1);
    }
    
    fseek(fp, 0, SEEK_END); // set the pointer to the end of the file
    
    int fileSize = ftell(fp); // save the size of the file

    fseek(fp, 0, SEEK_SET); // reset pointer to the beginning of the file

    fseek(fp, global_header, SEEK_SET); // skip the global header (24 bytes)

    char data_buffer[DATA_MAX]; // character array used to read in the payload
    int data_size; // int variable to store the size of payload

    printf("\n\n");

    while (ftell(fp) < fileSize - global_header)
    {
        struct _udp_packet *udp;
        fseek(fp, packet_header, SEEK_CUR);             // skip ethernet record_header (24 bytes) + header(14 bytes) + ID header (20 bytes)
        fread(udp, sizeof(struct _udp_packet), 1, fp);  // store UDP packet header

        // print out the header
        printf("Src Port: %d\nDst Port: %d\nUDP Packet Length: %d\nChecksum: 0x%x\n",
		ntohs(udp->port_num),
		ntohs(udp->dest_num),
		ntohs(udp->len),
        ntohs(udp->checksum));

        // Now that the headers are identified and stored, 
        // I need to figure out what the size for the payload is.
        // After that, the payload will be read into the 'data_buffer'.
        // Next, each character within the buffer will be printed in ASCII.
        // Any ASCII control character will be converted to '.'
        
        data_size = ntohs(udp->len) - sizeof(struct _udp_packet); // size of the payload equals the length of the UDP datagram - 8-byte header

        fread(data_buffer, data_size, 1, fp); // store the payload into the character array for iteration

        int i = 0;
        unsigned char ch;
        while(i < data_size){
            ch = (unsigned char)data_buffer[i];
            if (ch >= '!' && ch <= '~') {printf("%c", ch);}
            else {printf(".");}
            i++;
        }
        printf("\n--------------------------------\n\n");
    }
    fclose(fp);
    return 0;
    
}
