/*
 * main.c
 *
 *  Created on: Feb 17, 2022
 *      Author: atcsol
 */


//PARTE 1

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "basic_types.h"
int main() {

    int fd;
    int tms_fd;
    int tcs_fd;
    uint8_t read_byte;
    uint8_t byte_to_write;
    uint8_t tc_bytes[256];

    uint16_t i = 0;



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

    fd = open("multiple-tcs.bin", O_RDONLY);
    tms_fd = open("multiple-tms.bin", O_WRONLY | O_CREAT | O_TRUNC, 0664);

  //Campos principales del telecomando

    /* Read Packet ID and store it into packet_id */

    uint8_t ntcs;
    read(fd, &read_byte, 1);
    ntcs = read_byte;
    uint16_t tm_count = 0;
    uint8_t tc = 0;

    while (tc < ntcs) {
       uint16_t nbytes=0;
	   read(fd, &read_byte, 1);        // Read MSB
	       tc_bytes[0] = read_byte;
	       nbytes++;
	       packet_id = read_byte;
	       packet_id = packet_id << 8;     // Shift it 8 bits to the left

	       read(fd, &read_byte, 1);            // Read LSB
	       tc_bytes[1] = read_byte;
	       nbytes++;                           //Puedes poner o nbytes++ o nbytes=nybytes+1
	       packet_id = packet_id | read_byte;  // OR the MSB and the LSB

	       printf("Packet ID: 0x%X\n", packet_id);

	       read(fd, &read_byte, 1);        // Read MSB
	       tc_bytes[2] = read_byte;
	       nbytes++;

	       packet_seq_ctrl = read_byte;
	       packet_seq_ctrl = packet_seq_ctrl << 8;     // Shift it 8 bits to the left

	       read(fd, &read_byte, 1);            // Read LSB
	       tc_bytes[3] = read_byte;
	       nbytes++;
	       packet_seq_ctrl = packet_seq_ctrl | read_byte;  // OR the MSB and the LSB

	       printf("Packet Sequence Control: 0x%X\n", packet_seq_ctrl);

	       read(fd, &read_byte, 1);        // Read MSB
	       tc_bytes[4] = read_byte;
	       nbytes++;
	       packet_len = read_byte;
	       packet_len = packet_len << 8;     // Shift it 8 bits to the left

	       read(fd, &read_byte, 1);            // Read LSB
	       tc_bytes[5] = read_byte;
	       nbytes++;
	       packet_len = packet_len | read_byte;  // OR the MSB and the LSB

	       printf("Packet Length: 0x%X\n", packet_len);

	       read(fd, &read_byte, 1);        // Read MSB
	       tc_bytes[6] = read_byte;
	       nbytes++;
	       df_header = read_byte;
	       df_header = df_header <<8;     // Shift it 8 bits to the left
	       read(fd, &read_byte, 1);        // Read MSB
	       tc_bytes[7] = read_byte;
	       nbytes++;
	       df_header = df_header|read_byte;
	       df_header = df_header <<8;
	       read(fd, &read_byte, 1);        // Read MSB
	       tc_bytes[8] = read_byte;
	       nbytes++;
	       df_header = df_header|read_byte;
	       read(fd, &read_byte, 1);        // Read MSB
	       tc_bytes[9] = read_byte;
	       nbytes++;
	       df_header = df_header <<8;
	       df_header = df_header|read_byte;

	       printf("Data Field Header: 0x%X\n", df_header);

	       for (uint16_t i = 0; i < packet_len - 5; i = i + 1) {
	           	read(fd, &read_byte, 1);
	           	tc_bytes[10+i] = read_byte;
	           	nbytes++;
	           }

	       read(fd, &read_byte, 1);        // Read MSB
	       packet_err_ctrl = read_byte;
	       packet_err_ctrl = packet_err_ctrl << 8;     // Shift it 8 bits to the left
	       read(fd, &read_byte, 1);            // Read LSB
	       packet_err_ctrl = packet_err_ctrl | read_byte;  // OR the MSB and the LSB

	       printf("Packet Error Control: 0x%X\n", packet_err_ctrl);


	       uint16_t crc_value = 0xFFFF;

	       for (uint16_t i = 0; i < nbytes; i++ ) {

	           crc_value = crc_value ^ (tc_bytes[i] << 8);

	           for (uint8_t j = 0; j < 8; j++) {

	               if ((crc_value & 0x8000) != 0) {
	                   crc_value = (crc_value << 1) ^ 0x1021;
	               } else {
	                   crc_value = crc_value << 1;
	               }
	           }
	       }
	       if(crc_value==packet_err_ctrl) {
	                       	printf("OK\n");

	                       	tm_packet_id = tm_packet_id | (1 << 11);
	                       	tm_packet_id = tm_packet_id | (0x32C);
	                       	printf("TM_Packet ID: 0x%X\n", tm_packet_id);
	                       	byte_to_write=(tm_packet_id & 0xFF00) >> 8;
	                       	write(tms_fd, &byte_to_write, 1);
	                       	byte_to_write = (tm_packet_id & 0x00FF);
	                       	write(tms_fd, &byte_to_write, 1);

	                       	tm_packet_seq_ctrl=(packet_seq_ctrl & 0xC000) | tm_count;
	                       	printf("TM_Packet Sequence Control: 0x%X\n", tm_packet_seq_ctrl);
	                       	byte_to_write=(tm_packet_seq_ctrl & 0xFF00) >> 8;
	                       	write(tms_fd, &byte_to_write, 1);
	                       	byte_to_write = (tm_packet_seq_ctrl & 0x00FF);
	                       	write(tms_fd, &byte_to_write, 1);

	                       	tm_packet_len=4+sizeof(tm_packet_id)+sizeof(tm_packet_seq_ctrl)-1;
	                       	printf("TM_Packet Length: 0x%X\n", tm_packet_len);
	                       	byte_to_write=(tm_packet_len & 0xFF00) >> 8;
	                       	write(tms_fd, &byte_to_write, 1);
	                       	byte_to_write = (tm_packet_len & 0x00FF);
	                       	write(tms_fd, &byte_to_write, 1);

	                        tm_df_header=0x10;
	                        tm_df_header=tm_df_header <<8;
	                        tm_df_header=tm_df_header|0x01;
	                        tm_df_header=tm_df_header <<8;
	                        tm_df_header=tm_df_header|0x01;
	                        tm_df_header=tm_df_header <<8;
	                        tm_df_header=tm_df_header|0x78;
	                        printf("TM_Data Field Header: 0x%X\n", tm_df_header);
	                        byte_to_write=(tm_df_header) >> 24;
	                        write(tms_fd, &byte_to_write, 1);
	                        byte_to_write=(tm_df_header & 0xFF0000) >> 16;
	                        write(tms_fd, &byte_to_write, 1);
	                        byte_to_write=(tm_df_header & 0xFF00) >> 8;
	                        write(tms_fd, &byte_to_write, 1);
	                        byte_to_write = (tm_df_header & 0x00FF);
	                        write(tms_fd, &byte_to_write, 1);

	                        tm_source_data=packet_id;
	                        tm_source_data=tm_source_data <<16;
	                        tm_source_data=tm_source_data|tm_packet_seq_ctrl;
	                        printf("TM_Source Data: 0x%X\n", tm_source_data);
	                        byte_to_write=(tm_source_data) >> 24;
	                        write(tms_fd, &byte_to_write, 1);
	                        byte_to_write=(tm_source_data & 0xFF0000) >> 16;
	                        write(tms_fd, &byte_to_write, 1);
	                        byte_to_write=(tm_source_data & 0xFF00) >> 8;
	                        write(tms_fd, &byte_to_write, 1);
	                        byte_to_write = (tm_source_data & 0x00FF);
	                        write(tms_fd, &byte_to_write, 1);

	                       }else{
	                       	printf("FAIL");
	                       	tm_packet_id = tm_packet_id | (1 << 11);
	                       	tm_packet_id = tm_packet_id | (0x32C);
	                       	printf("TM_Packet ID: 0x%X\n", tm_packet_id);
	                       	byte_to_write=(tm_packet_id & 0xFF00) >> 8;
	                        write(tms_fd, &byte_to_write, 1);
	                       	byte_to_write = (tm_packet_id & 0x00FF);
	                       	write(tms_fd, &byte_to_write, 1);

	                       	tm_packet_seq_ctrl=(packet_seq_ctrl & 0xC000) | tm_count;
	                       	printf("TM_Packet Sequence Control: 0x%X\n", tm_packet_seq_ctrl);
	                       	byte_to_write=(tm_packet_seq_ctrl & 0xFF00) >> 8;
	                       	write(tms_fd, &byte_to_write, 1);
	                       	byte_to_write = (tm_packet_seq_ctrl & 0x00FF);
	                       	write(tms_fd, &byte_to_write, 1);

	                       	tm_source_data=packet_id;
	                       	tm_source_data=tm_source_data <<16;
	                       	tm_source_data=tm_source_data|tm_packet_seq_ctrl;
	                       	tm_source_data=tm_source_data <<16;
	                       	tm_source_data=tm_source_data|0x0002;
	                       	tm_source_data=tm_source_data <<16;
	                       	tm_source_data=tm_source_data|packet_err_ctrl;
	                       	tm_source_data=tm_source_data <<16;
	                       	tm_source_data=tm_source_data|crc_value;

	                       	tm_packet_len=4+sizeof(tm_source_data)-1;
	                       	printf("TM_Packet Length: 0x%X\n", tm_packet_len);
	                       	byte_to_write=(tm_packet_len & 0xFF00) >> 8;
	                       	write(tms_fd, &byte_to_write, 1);
	                       	byte_to_write = (tm_packet_len & 0x00FF);
	                        write(tms_fd, &byte_to_write, 1);

	                       	tm_df_header=0x10;
	                       	tm_df_header=tm_df_header <<8;
	                       	tm_df_header=tm_df_header|0x01;
	                       	tm_df_header=tm_df_header <<8;
	                       	tm_df_header=tm_df_header|0x02;
	                       	tm_df_header=tm_df_header <<8;
	                       	tm_df_header=tm_df_header|0x78;
	                        printf("TM_Data Field Header: 0x%X\n", tm_df_header);
	                        byte_to_write=(tm_df_header) >> 24;
	                        write(tms_fd, &byte_to_write, 1);
	                        byte_to_write=(tm_df_header & 0xFF0000) >> 16;
	                       	write(tms_fd, &byte_to_write, 1);
	                       	byte_to_write=(tm_df_header & 0xFF00) >> 8;
	                       	write(tms_fd, &byte_to_write, 1);
	                       	byte_to_write = (tm_df_header & 0x00FF);
	                       	write(tms_fd, &byte_to_write, 1);

	                       	tm_source_data=packet_id;
	                       	tm_source_data=tm_source_data <<16;
	                       	tm_source_data=tm_source_data|tm_packet_seq_ctrl;
	                       	tm_source_data=tm_source_data <<16;
	                       	tm_source_data=tm_source_data|0x0002;
	                       	tm_source_data=tm_source_data <<16;
	                       	tm_source_data=tm_source_data|packet_err_ctrl;
	                       	tm_source_data=tm_source_data <<16;
	                       	tm_source_data=tm_source_data|crc_value;
	                       	printf("TM_Source Data: 0x%X\n", tm_source_data);
	                       	byte_to_write=(packet_id) >> 8;
	                       	write(tms_fd, &byte_to_write, 1);
	                       	byte_to_write=(packet_id);
	                        write(tms_fd, &byte_to_write, 1);
	                        byte_to_write=(tm_packet_seq_ctrl) >> 8;
	                        write(tms_fd, &byte_to_write, 1);
	                        byte_to_write=(tm_packet_seq_ctrl);
	                        write(tms_fd, &byte_to_write, 1);
	                        byte_to_write=(0x0002) >> 8;
	                        write(tms_fd, &byte_to_write, 1);
	                        byte_to_write=(0x0002);
	                        write(tms_fd, &byte_to_write, 1);
	                        byte_to_write=(packet_err_ctrl) >> 8;
	                        write(tms_fd, &byte_to_write, 1);
	                        byte_to_write=(packet_err_ctrl);
	                        write(tms_fd, &byte_to_write, 1);
	                        byte_to_write=(crc_value) >> 8;
	                        write(tms_fd, &byte_to_write, 1);
	                        byte_to_write=(crc_value);
	                        write(tms_fd, &byte_to_write, 1);

	                       }

	               printf("Expected CRC value: 0x%X, Calculated CRC value: 0x%X\n", packet_err_ctrl, crc_value);

	        tm_count = tm_count + 1;
	        tc=tc + 1;
    }




    // Obtención de los campos de segundo nivel

    //printf("APID: 0x%X\n", (packet_id & 0x07FF));
    //printf("APID: 0x%X\n", ccsds_pus_tc_get_APID(packet_id));

    //printf("Sequence Flags: 0x%X\n", (packet_seq_ctrl >>14));
    //printf ("Sequence Flags: 0x%X\n", ccsds_pus_tc_get_Sequence_Flags(packet_seq_ctrl));

    //printf("Sequence Count: %d\n", (packet_seq_ctrl & 0x3FFF));
    //printf ("Sequence Count: %d\n", ccsds_pus_tc_get_Sequence_Count(packet_seq_ctrl));

    //printf("ACK: 0x%X\n", ((df_header >>24) & 0x00F));
    //printf ("ACK: 0x%X\n", ccsds_pus_tc_get_Ack(df_header));

    //printf("Service Type: %d\n", ((df_header>>16) & 0x00FF));
    //printf ("Service Type: %d\n", ccsds_pus_tc_get_Service_Type(df_header));

    //printf("Service Subtype: %d\n", ((df_header>>8) & 0x0000FF));
    //printf ("Service Subtype: %d\n", ccsds_pus_tc_get_Service_Subtype(df_header));

    //printf("Source ID: 0x%X\n", (df_header & 0xFF));
    //printf ("Source ID: 0x%X\n", ccsds_pus_tc_get_Source_ID(df_header));

    ccsds_pus_tmtc_print_packet_id(packet_id);

    ccsds_pus_tmtc_print_packet_sequence_control(packet_seq_ctrl);

    ccsds_pus_tmtc_print_df_header(df_header);

  //FIN DE LA PARTE 1






 //PARTE 2 - Telemetría de aceptación (EL F2 ES DE ESTA PARTE)







   //FIN DE LA PARTE 2

   close(fd);
   close(tms_fd);





    return 0;

}

