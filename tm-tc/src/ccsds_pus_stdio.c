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
