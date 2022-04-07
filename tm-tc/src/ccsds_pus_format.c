#include "basic_types.h"
#include "ccsds_pus_format.h"

uint16_t ccsds_pus_tc_get_APID(uint16_t packet_id) {

    return (packet_id & 0x07FF);

}

uint16_t ccsds_pus_tc_get_Sequence_Flags(uint16_t packet_seq_ctrl) {

    return (packet_seq_ctrl >>14);

}

uint16_t ccsds_pus_tc_get_Sequence_Count(uint16_t packet_seq_ctrl) {

    return (packet_seq_ctrl & 0x3FFF);

}

uint16_t ccsds_pus_tc_get_Ack(uint32_t df_header) {

    return ((df_header >>24) & 0x00F);

}

uint16_t ccsds_pus_tc_get_Service_Type(uint32_t df_header) {

    return ((df_header>>16) & 0x00FF);

}

uint16_t ccsds_pus_tc_get_Service_Subtype(uint32_t df_header) {

    return ((df_header>>8) & 0x0000FF);

}

uint16_t ccsds_pus_tc_get_Source_ID(uint32_t df_header) {

    return (df_header & 0xFF);

}

uint16_t i = 0;
uint32_t App_Data=0;
void ccsds_pus_tc_get_fields(uint8_t tc_bytes[],
                             uint16_t * p_packet_id,
                             uint16_t * p_packet_seq_ctrl,
                             uint16_t * p_packet_len,
                             uint32_t * p_df_header,
                             uint16_t * p_packet_err_ctrl) {

    // Deserialize Packet ID and store it at p_packet_id
    p_packet_id = deserialize_uint16(&tc_bytes[0]);
    p_packet_seq_ctrl= deserialize_uint16(&tc_bytes[2]);
    p_packet_len= deserialize_uint16(&tc_bytes[4]);
	p_df_header= deserialize_uint32(&tc_bytes[0]);
	while(i<(p_packet_len-5)){
	    	if(i==0){
	    		App_Data=tc_bytes[10];
	    		i=i+1;
	    	}
	    	else{
	    		App_Data=App_Data | tc_bytes[10+i];
	    		i=i+1;
	    	}
	    }
	p_packet_err_ctrl= deserialize_uint16(&tc_bytes[11+i]);

}
