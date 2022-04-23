#include "basic_types.h"
#include "ccsds_pus_format.h"
#include "serialize.h"

uint16_t ccsds_pus_tc_get_APID(uint16_t packet_id) {

    return (packet_id & 0x07FF);

}

uint8_t ccsds_pus_tc_get_Sequence_Flags(uint16_t packet_seq_ctrl) {

    return (packet_seq_ctrl >>14);

}

uint16_t ccsds_pus_tc_get_Sequence_Count(uint16_t packet_seq_ctrl) {

    return (packet_seq_ctrl & 0x3FFF);

}

uint8_t ccsds_pus_tc_get_Ack(uint32_t df_header) {

    return ((df_header >>24) & 0x0F);

}

uint8_t ccsds_pus_tc_get_Service_Type(uint32_t df_header) {

    return ((df_header>>16) & 0x00FF);

}

uint8_t ccsds_pus_tc_get_Service_Subtype(uint32_t df_header) {

    return ((df_header>>8) & 0x0000FF);

}

uint8_t ccsds_pus_tc_get_Source_ID(uint32_t df_header) {

    return (df_header & 0x000000FF);

}

uint16_t ccsds_pus_tc_read(int fd, uint8_t tc_bytes[]){
	uint16_t nbytes=0;
	uint16_t packet_id=0, packet_seq_ctrl=0, packet_len=0, packet_err_ctrl=0, i=0, p_packet_id=0, p_packet_seq_ctrl=0, p_packet_len=0, p_packet_err_ctrl=0;
	uint32_t df_header=0, App_Data=0, p_df_header=0;
	read(fd, &tc_bytes[0], 6);
	packet_len = deserialize_uint16(&tc_bytes[4]);
	read(fd, &tc_bytes[6], 4);
	while(i<(packet_len-5)){
		if(i==0){
			read(fd, &tc_bytes[10], 1);
			i=i+1;
		}else{
			read(fd, &tc_bytes[10+i],1);
			i=i+1;
		}
	}

	read(fd, &tc_bytes[11+i], 2);
	nbytes=12+i;
	return(nbytes);
}
void ccsds_pus_tc_get_fields(uint8_t tc_bytes[],
                             uint16_t * p_packet_id,
                             uint16_t * p_packet_seq_ctrl,
                             uint16_t * p_packet_len,
                             uint32_t * p_df_header,
                             uint16_t * p_packet_err_ctrl) {
       uint8_t i=0;

    // Deserialize Packet ID and store it at p_packet_id
    * p_packet_id = deserialize_uint16(&tc_bytes[0]);
    * p_packet_seq_ctrl= deserialize_uint16(&tc_bytes[2]);
    * p_packet_len= deserialize_uint16(&tc_bytes[4]);
	* p_df_header= deserialize_uint32(&tc_bytes[6]);
	i=(*p_packet_len-5);
	* p_packet_err_ctrl= deserialize_uint16(&tc_bytes[11+i]);
}

uint16_t ccsds_pus_tm_build_packet_id(uint16_t apid) {

	uint16_t tm_packet_id;
	tm_packet_id = (1 << 11) | (apid & 0x07FF);
	return tm_packet_id;

}

uint16_t ccsds_pus_tm_build_packet_seq_ctrl(uint8_t sequence_flags, uint16_t sequence_count) {
	uint16_t tm_packet_seq_ctrl;
	tm_packet_seq_ctrl = (sequence_flags & 0xC000) | (sequence_count);
	return tm_packet_seq_ctrl;
}

uint32_t ccsds_pus_tm_build_df_header(uint8_t service_type, uint8_t service_subtype, uint8_t destination_id, uint16_t crc, uint16_t packet_err_ctrl){
	uint32_t tm_df_header;
	service_type = 0x01;
    if(crc == packet_err_ctrl){
    	service_subtype = 0x01;
    }else{
    	service_subtype = 0x02;
    }
    tm_df_header = 0x10000000 | service_type << 16 | service_subtype <<8 | destination_id;
	return tm_df_header;
}


void ccsds_pus_tm_set_fields(uint8_t tm_bytes[],
                             uint16_t tm_packet_id,
                             uint16_t tm_packet_seq_ctrl,
                             uint16_t tm_packet_length,
                             uint32_t tm_df_header) {

    serialize_uint16(tm_packet_id, &tm_bytes[0]);
    serialize_uint16(tm_packet_seq_ctrl, &tm_bytes[2]);
    serialize_uint16(tm_packet_length, &tm_bytes[4]);
    serialize_uint32(tm_df_header, &tm_bytes[6]);

}










