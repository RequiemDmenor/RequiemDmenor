#include <stdio.h>

#include "basic_types.h"
#include "ccsds_pus_stdio.h"
#include "ccsds_pus_format.h"

void ccsds_pus_tmtc_print_packet_id(uint16_t packet_id) {

	printf("APID: 0x%X\n", ccsds_pus_tc_get_APID(packet_id));

}

void ccsds_pus_tmtc_print_packet_sequence_control(uint16_t packet_seq_ctrl) {

	printf ("Sequence Flags: 0x%X\n", ccsds_pus_tc_get_Sequence_Flags(packet_seq_ctrl));
	printf ("Sequence Count: %d\n", ccsds_pus_tc_get_Sequence_Count(packet_seq_ctrl));
}

void ccsds_pus_tmtc_print_df_header(uint32_t df_header) {

	printf ("ACK: 0x%X\n", ccsds_pus_tc_get_Ack(df_header));
	printf ("Service Type: %d\n", ccsds_pus_tc_get_Service_Type(df_header));
	printf ("Service Subtype: %d\n", ccsds_pus_tc_get_Service_Subtype(df_header));
	printf ("Source ID: 0x%X\n", ccsds_pus_tc_get_Source_ID(df_header));
}

uint16_t ccsds_pus_tc_read(int fd, uint8_t tc_bytes[]) {

    uint16_t nbytes = 0;
    uint16_t i = 0;
    uint16_t packet_len = 0;
    uint16_t packet_id;
    uint16_t packet_seq_ctrl;
    uint32_t df_header;
    uint32_t App_Data=0;
    uint16_t packet_err_ctrl;

    // Read the first initial six bytes of the TC (Packet Header)
    read(fd, &tc_bytes[0], 6);

    // Obtain Packet Length:

    // The Packet Length field is stored in bytes 4 and 5. To obtain the
    // actual value of the 16-bit field and store correctly into memory,
    // we have to deserialize it using function deserialize_uint16():
    packet_id = deserialize_uint16(&tc_bytes[0]);
    packet_seq_ctrl = deserialize_uint16(&tc_bytes[2]);
    packet_len = deserialize_uint16(&tc_bytes[4]);

    read(fd, &tc_bytes[6], 4);
    df_header = deserialize_uint32(&tc_bytes[0]);

    while(i<(packet_len-5)){
    	if(i==0){
    		read(fd, &tc_bytes[10], 1);
    		App_Data=tc_bytes[10];
    		i=i+1;
    	}
    	else{
    		read(fd, &tc_bytes[10+i], 1);
    		App_Data=App_Data | tc_bytes[10+i];
    		i=i+1;
    	}
    }
    read(fd, &tc_bytes[11+i], 2);
    packet_err_ctrl=deserialize_uint16(&tc_bytes[11+i]);
    // TODO: Read the remaining bytes and return the proper number of
    // bytes read. THE FUNCTION SHALL ALSO READ THE PACKET ERROR CONTROL
    // and store it into the vector.

}

