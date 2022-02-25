/*
 * main.c
 *
 *  Created on: Feb 17, 2022
 *      Author: atcsol
 */




#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
int main() {

    int fd;
    int fd2;

    uint8_t read_byte;
    uint8_t byte_to_write;
    
    uint16_t packet_id;
    uint16_t packet_seq_ctrl;
    uint16_t packet_len;
    uint32_t df_header;
    uint16_t packet_err_ctrl;
    uint8_t DestinationID;
    uint32_t source_id;
    
	uint16_t tm_packet_id = 0;
    uint16_t tm_packet_seq_ctrl;
    uint16_t tm_packet_len;
    uint32_t tm_df_header;
    uint32_t tm_source_data;
    uint8_t tm_DestinationID;

    fd = open("single-tc.bin", O_RDONLY);
    fd2 = open("single-tm.bin", O_WRONLY | O_CREAT | O_TRUNC, 0664);

    /* Read Packet ID and store it into packet_id */
    
    read(fd, &read_byte, 1);        // Read MSB
    packet_id = read_byte;
    packet_id = packet_id << 8;     // Shift it 8 bits to the left
    
    read(fd, &read_byte, 1);            // Read LSB
    packet_id = packet_id | read_byte;  // OR the MSB and the LSB
    
    printf("Packet ID: 0x%X\n", packet_id);
    
    read(fd, &read_byte, 1);        // Read MSB
    packet_seq_ctrl = read_byte;
    packet_seq_ctrl = packet_seq_ctrl << 8;     // Shift it 8 bits to the left

    read(fd, &read_byte, 1);            // Read LSB
    packet_seq_ctrl = packet_seq_ctrl | read_byte;  // OR the MSB and the LSB

    printf("Packet Sequence Control: 0x%X\n", packet_seq_ctrl);

    read(fd, &read_byte, 1);        // Read MSB
    packet_len = read_byte;
    packet_len = packet_len << 8;     // Shift it 8 bits to the left

    read(fd, &read_byte, 1);            // Read LSB
    packet_len = packet_len | read_byte;  // OR the MSB and the LSB

    printf("Packet Length: 0x%X\n", packet_len);

    read(fd, &read_byte, 1);        // Read MSB
    df_header = read_byte;
    df_header = df_header <<8;     // Shift it 8 bits to the left
    read(fd, &read_byte, 1);        // Read MSB
    df_header = df_header|read_byte;
    df_header = df_header <<8;
    read(fd, &read_byte, 1);        // Read MSB
    df_header = df_header|read_byte;
    read(fd, &read_byte, 1);        // Read MSB
    df_header = df_header <<8;
    df_header = df_header|read_byte;

    printf("Data Field Header: 0x%X\n", df_header);

    read(fd, &read_byte, 1);        // Read MSB
    packet_err_ctrl = read_byte;
    packet_err_ctrl = packet_err_ctrl << 8;     // Shift it 8 bits to the left

    read(fd, &read_byte, 1);            // Read LSB
    packet_err_ctrl = packet_err_ctrl | read_byte;  // OR the MSB and the LSB

    printf("Packet Error Control: 0x%X\n", packet_err_ctrl);

 // Obtención de los campos de segundo nivel
    printf("APID: 0x%X\n", (packet_id & 0x07FF));
    printf("Sequence Flags: 0x%X\n", (packet_seq_ctrl >>14));
    printf("Sequence Count: %d\n", (packet_seq_ctrl & 0x3FFF));
    printf("ACK: 0x%X\n", ((df_header >>24) & 0x00F));
    printf("Service Type: %d\n", ((df_header>>16) & 0x00FF));
    printf("Service Subtype: %d\n", ((df_header>>8) & 0x0000FF));
    printf("Source ID: 0x%X\n", (df_header & 0xFF));



  //FIN DE LA PARTE 1








   tm_packet_id = tm_packet_id | (1 << 11);
   tm_packet_id = tm_packet_id | (0x32C);
   printf("TM_Packet ID: 0x%X\n", tm_packet_id);
   byte_to_write=(tm_packet_id & 0xFF00) >> 8;
   write(fd2, &byte_to_write, 1);
   byte_to_write = (tm_packet_id & 0x00FF);
   write(fd2, &byte_to_write, 1);

   tm_packet_seq_ctrl=packet_seq_ctrl;
   printf("TM_Packet Sequence Control: 0x%X\n", tm_packet_seq_ctrl);
   byte_to_write=(tm_packet_seq_ctrl & 0xFF00) >> 8;
   write(fd2, &byte_to_write, 1);
   byte_to_write = (tm_packet_seq_ctrl & 0x00FF);
   write(fd2, &byte_to_write, 1);

   tm_packet_len=4+sizeof(tm_packet_id)+sizeof(tm_packet_seq_ctrl)-1;
   printf("TM_Packet Length: 0x%X\n", tm_packet_len);
   byte_to_write=(tm_packet_len & 0xFF00) >> 8;
   write(fd2, &byte_to_write, 1);
   byte_to_write = (tm_packet_len & 0x00FF);
   write(fd2, &byte_to_write, 1);

   tm_df_header=0x10;
   tm_df_header=tm_df_header <<8;
   tm_df_header=tm_df_header|0x01;
   tm_df_header=tm_df_header <<8;
   tm_df_header=tm_df_header|0x01;
   tm_df_header=tm_df_header <<8;
   tm_df_header=tm_df_header|0x78;
   printf("TM_Data Field Header: 0x%X\n", tm_df_header);
   byte_to_write=(tm_df_header) >> 24;
   write(fd2, &byte_to_write, 1);
   byte_to_write=(tm_df_header & 0xFF0000) >> 16;
   write(fd2, &byte_to_write, 1);
   byte_to_write=(tm_df_header & 0xFF00) >> 8;
   write(fd2, &byte_to_write, 1);
   byte_to_write = (tm_df_header & 0x00FF);
   write(fd2, &byte_to_write, 1);

   tm_source_data=packet_id;
   tm_source_data=tm_source_data <<16;
   tm_source_data=tm_source_data|tm_packet_seq_ctrl;
   printf("TM_Source Data: 0x%X\n", tm_source_data);
   byte_to_write=(tm_source_data) >> 24;
   write(fd2, &byte_to_write, 1);
   byte_to_write=(tm_source_data & 0xFF0000) >> 16;
   write(fd2, &byte_to_write, 1);
   byte_to_write=(tm_source_data & 0xFF00) >> 8;
   write(fd2, &byte_to_write, 1);
   byte_to_write = (tm_source_data & 0x00FF);
   write(fd2, &byte_to_write, 1);

   close(fd);
   close(fd2);





    return 0;

}

