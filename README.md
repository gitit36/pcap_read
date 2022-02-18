# pcap_read
A program that reads payload of the UPD packet from a PCAP file

<img width="450" alt="Screen Shot 2022-02-18 at 11 56 21 AM" src="https://user-images.githubusercontent.com/24204239/154641618-11dac2d7-0eb4-479d-9c45-e925ec3c97e5.png">
The program will print the following information:

1. UDP Headers: Source Port #, Destination Port #, UDP Packet Length, Checksum
2. UDP payload

<img width="462" alt="Screen Shot 2022-02-18 at 11 56 50 AM" src="https://user-images.githubusercontent.com/24204239/154641719-b19525a6-9541-4838-a70f-90366690a62c.png">
The program will skip:

1. Global Header (24 bytes)
3. Record Header (16 bytes) + Ethernet Header (14 bytes) + ID header (20 bytes)

To Run:

1. Compile your program: 
'''
gcc read_pcap.c
'''
4. Run the exec file with the given PCAP file as an arg: ./a.out capture1.pcap
