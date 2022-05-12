/*
 * main.c
 *
 *  Created on: Feb 17, 2022
 *      Author: atcsol
 */


//PARTE 1


/*

    int fd;
    int tms_fd;
    int fdr;
    int tcs_fd;
    uint8_t read_byte;
    uint8_t byte_to_write;
    uint8_t tc_bytes[256];

    uint16_t i = 0;



    /*uint16_t packet_id;*/
/*uint16_t packet_seq_ctrl;*/
/*uint16_t packet_len;*/
/*uint32_t df_header;*/
/*uint16_t packet_err_ctrl;*/
/*uint8_t DestinationID;
    uint32_t source_id;*/





/*uint16_t tm_packet_id = 0;
    uint16_t tm_packet_seq_ctrl;
    uint16_t tm_packet_len;
    uint32_t tm_df_header;
    uint32_t tm_source_data;
    uint8_t tm_DestinationID;*/
/*
    fd = open("multiple-tcs.bin", O_RDONLY);
    tms_fd = open("multiple-tms.bin", O_WRONLY | O_CREAT | O_TRUNC, 0664);

  //Campos principales del telecomando

    /* Read Packet ID and store it into packet_id */
/*
    uint8_t ntcs;
    read(fd, &read_byte, 1);
    ntcs = read_byte;
    uint16_t tm_count = 0;
    uint8_t tc = 0;
 */




/*while(tc < ntcs) {/
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
    }*/




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

//PRACTICA 3 PARTE 2//

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "basic_types.h"
#include "ccsds_pus_format.h"
#include "ccsds_pus_stdio.h"
#include "crc.h"
#include "serialize.h"
#include "epd_pus_tmtc.h"
#include "epd_pus_mission.h"
#include "system_tm_queue.h"
#include "system_tm_pool.h"

int main() {
	int fd;
	int fdr;
	uint8_t write_byte, tc_bytes[256], ntcs=0, tmc=0, tm_bytes[256];
	uint16_t packet_id, packet_seq_ctrl, packet_len, packet_err_ctrl, Rpacket_id, Rpacket_seq_control, Rpacket_len, i=0, crc_value = 0xFFFF;
	uint32_t df_header, Rdf_header, Rsource_data;

	fd = open("multiple-tcs.bin", O_RDONLY);
	fdr = open("multiple-tms.bin", O_WRONLY | O_CREAT | O_TRUNC, 0664);

	read(fd, &tc_bytes[0], 1);
	ntcs=tc_bytes[0];
	// Initialize TM queue
	init_system_tm_queue();

	// Initialize TM pool
	init_system_tm_pool();

	for (uint8_t tc = 0; tc < ntcs; tc = tc + 1) {
		printf("x\n");

		struct ccds_pus_tmtc_packet_header tc_packet_header;
		struct ccds_pus_tc_df_header tc_df_header;

		uint8_t nbytes=0;

		/*uint16_t tc_packet_id;
        uint16_t tc_packet_seq_ctrl;
        uint16_t tc_packet_len;
        uint32_t tc_df_header;
        uint16_t tc_packet_err_ctrl;

        uint16_t crc_value;
        uint8_t nbytes = 0;

        uint8_t tc_bytes[256];
        uint8_t tm_bytes[256];*/

		// Read telecommand from file
		nbytes = ccsds_pus_tc_read(fd, tc_bytes);

		// Deserialize primary fields
		ccsds_pus_tc_get_fields(tc_bytes, &tc_packet_header,
				&tc_df_header,
				&packet_err_ctrl);

		// Print the contents of all the fields
		ccsds_pus_tmtc_print_packet_id(tc_packet_header.packet_id);
		ccsds_pus_tmtc_print_packet_sequence_control(tc_packet_header.packet_seq_ctrl);
		ccsds_pus_tc_print_df_header_fields(tc_df_header);


		// Calculate CRC
		// We need to calculate the CRC with nbytes - 2, since the vector
		// ALSO STORES the Packet Error Control field
		crc_value = cal_crc_16(tc_bytes, nbytes -2);

		/*if (crc_value == packet_err_ctrl) {

            printf("Expected CRC value 0x%X, Calculated CRC value 0x%X: OK\n",
                   packet_err_ctrl, crc_value);

            // Generate TM (1,1) - Accept
            epd_pus_build_tm_1_1(tm_bytes, tmc,
                    tc_packet_header.packet_id,
                    tc_packet_header.packet_seq_ctrl);
            i=14;
        } else {
            printf("Expected CRC value 0x%X, Calculated CRC value 0x%X: FAIL\n",
                   packet_err_ctrl, crc_value);

            epd_pus_build_tm_1_2_crc_error(tm_bytes, tmc,
                    tc_packet_header.packet_id,
                    tc_packet_header.packet_seq_ctrl,
                    packet_err_ctrl, crc_value);
            i=20;
        }*/

		if (crc_value == packet_err_ctrl) {

			uint8_t alloc_error;
			tm_descriptor_t tm_descriptor;

			printf("Expected CRC value 0x%X, Calculated CRC value 0x%X: OK\n",
					packet_err_ctrl, crc_value);

			alloc_error = tm_pool_alloc_tm(&tm_descriptor);

			if(!alloc_error){

				// Generate TM (1,1) - Accept
				epd_pus_build_tm_1_1(&tm_descriptor, tmc,
						tc_packet_header.packet_id,
						tc_packet_header.packet_seq_ctrl);

				tm_queue_insert_tm(tm_descriptor);

			}

		} else {
			uint8_t alloc_error;
			tm_descriptor_t tm_descriptor;

			printf("Expected CRC value 0x%X, Calculated CRC value 0x%X: FAIL\n",
					packet_err_ctrl, crc_value);

			alloc_error = tm_pool_alloc_tm(&tm_descriptor);

			if(!alloc_error){
				epd_pus_build_tm_1_2_crc_error(&tm_descriptor, tmc,
						tc_packet_header.packet_id,
						tc_packet_header.packet_seq_ctrl,
						packet_err_ctrl, crc_value);

				tm_queue_insert_tm(tm_descriptor);

			}



		}


			}


	while(!tm_queue_is_empty()){
			tm_descriptor_t tm_descriptor;

			if(!tm_queue_extract_tm(&tm_descriptor)){
		    ccsds_pus_tm_write(fdr, tm_descriptor);
			tm_pool_free_tm(&tm_descriptor);

		}


}







	//leer telecomando
	/*for (uint8_t tc = 0; tc < ntcs; tc = tc + 1) {
        printf("x/n");
        uint8_t nbytes = 0;
        // Read telecommand from file
        nbytes = ccsds_pus_tc_read(fd, tc_bytes);

        // Deserialize primary fields
        ccsds_pus_tc_get_fields(tc_bytes,
        		&packet_id,
                &packet_seq_ctrl,
                &packet_len,
                &df_header,
                &packet_err_ctrl);
    // Print the contents of all the fields
    ccsds_pus_tmtc_print_packet_id(packet_id);

    ccsds_pus_tmtc_print_packet_sequence_control(packet_seq_ctrl);

    ccsds_pus_tmtc_print_df_header(df_header);

    // Calculate CRC
        // We need to calculate the CRC with nbytes - 2, since the vector
        // ALSO STORES the Packet Error Control field
        crc_value = cal_crc_16(tc_bytes, nbytes - 2);
     if(crc_value == packet_err_ctrl){
    	 printf("Expected CRC value 0x%X, Calculated CRC value 0x%X: OK\n",packet_err_ctrl,crc_value);

     }else{
    	 printf("Expected CRC value 0x%X, Calculated CRC value 0x%X: FAIL\n",packet_err_ctrl,crc_value);
     }

     //generar telemetría de respuesta
   /*  Rpacket_id=packet_id & 0x0FFF;
     Rpacket_seq_control=(packet_seq_ctrl & 0xC000) | tmc;
     if(crc_value == packet_err_ctrl){
    	 Rdf_header= 0x10010100 | (df_header & 0x000000FF);
    	 Rsource_data= packet_id<<16 | packet_seq_ctrl;
     }else{
    	 Rdf_header= 0x10010200 | (df_header & 0x000000FF);
    	 Rsource_data= packet_id<<64 | packet_seq_ctrl<<48 | 0002<<32 | packet_err_ctrl<<16 | crc_value;
     }
     Rpacket_len=0x04 + sizeof(Rsource_data) - 0x01;

     write_byte=Rpacket_id>>8;
     write(fdr, &write_byte, 1);

     write_byte=Rpacket_id & 0x00FF;
     write(fdr, &write_byte, 1);

     write_byte=Rpacket_seq_control>>8;
     write(fdr, &write_byte, 1);

     write_byte=Rpacket_seq_control & 0x00FF;
     write(fdr, &write_byte, 1);

     write_byte=Rpacket_len>>8;
     write(fdr, &write_byte, 1);

     write_byte=Rpacket_len & 0x00FF;
     write(fdr, &write_byte, 1);

     write_byte=(Rdf_header>>24);
     write(fdr, &write_byte, 1);

     write_byte=(Rdf_header>>16) & 0x00FF;
     write(fdr, &write_byte, 1);

     write_byte=(Rdf_header>>8) & 0x0000FF;
     write(fdr, &write_byte, 1);

     write_byte=Rdf_header & 0x000000FF;
     write(fdr, &write_byte, 1);

     if(crc_value == packet_err_ctrl){
    	 write_byte = (packet_id>>8);
    	 write(fdr, &write_byte, 1);

    	 write_byte = packet_id & 0x00FF;
    	 write(fdr, &write_byte, 1);

    	 write_byte = (packet_seq_ctrl>>8);
    	 write(fdr, &write_byte, 1);

         write_byte = packet_seq_ctrl & 0x00FF;
         write(fdr, &write_byte, 1);
     }else{
    	 write_byte=(packet_id>>8);
    	 write(fdr, &write_byte, 1);

    	 write_byte=packet_id & 0x00FF;
    	 write(fdr, &write_byte, 1);

    	 write_byte=(packet_seq_ctrl>>8);
    	 write(fdr, &write_byte, 1);

    	 write_byte=packet_seq_ctrl & 0x00FF;
    	 write(fdr, &write_byte, 1);

    	 write_byte= 00;
    	 write(fdr, &write_byte, 1);

    	 write_byte=02;
    	 write(fdr, &write_byte, 1);

    	 write_byte=(packet_err_ctrl>>8);
    	 write(fdr, &write_byte, 1);

    	 write_byte=packet_err_ctrl& 0x00FF;
    	 write(fdr, &write_byte, 1);

    	 write_byte=(crc_value>>8);
    	 write(fdr, &write_byte, 1);

    	 write_byte=crc_value& 0x00FF;
    	 write(fdr, &write_byte, 1);
     }*/



	close(fd);
	close(fdr);
	return 0;

}



