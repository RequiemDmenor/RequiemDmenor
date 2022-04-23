#include "epd_pus_tmtc.h"
#include "epd_pus_mission.h"
#include "ccsds_pus_format.h"
#include "serialize.h"

void epd_pus_build_tm_1_1(uint8_t tm_bytes[],
                          uint16_t tm_seq_counter,
                          uint16_t tc_packet_id,
                          uint16_t tc_packet_seq_ctrl,
						  uint16_t crc,
						  uint16_t packet_err_ctrl) {

    uint16_t packet_id;
    uint16_t packet_seq_ctrl;
    uint16_t packet_length;
    uint32_t df_header;

    packet_id = ccsds_pus_tm_build_packet_id(EPD_APID);

    packet_seq_ctrl = ccsds_pus_tm_build_sequence_control(0x3, tm_seq_counter);

    packet_length = 0x07;

    df_header = ccsds_pus_tm_build_df_header(01);


    ccsds_pus_tm_set_fields(&tm_bytes[0], packet_id,
                            packet_seq_ctrl, packet_length, df_header);

    serialize_uint16(tc_packet_id, &tm_bytes[10]);
    serialize_uint16(tc_packet_seq_ctrl, &tm_bytes[12]);

    return;

}

void epd_pus_build_tm_1_2_crc_error(uint8_t tm_bytes[],
                          uint16_t tm_seq_counter,
                          uint16_t tc_packet_id,
                          uint16_t tc_packet_seq_ctrl,
						  uint16_t tc_packet_err_ctrl,
						  uint16_t calculated_crc) {
	uint16_t packet_id;
	    uint16_t packet_seq_ctrl;
	    uint16_t packet_length;
	    uint32_t df_header;

	    packet_id = ccsds_pus_tm_build_packet_id(EPD_APID);

	    packet_seq_ctrl = ccsds_pus_tm_build_sequence_control(0x3, tm_seq_counter);

	    packet_length = 0x0D;

	    df_header = ccsds_pus_tm_build_df_header(02);

	    ccsds_pus_tm_set_fields(&tm_bytes[0], packet_id,
	                            packet_seq_ctrl, packet_length, df_header);

	    serialize_uint16(tc_packet_id, &tm_bytes[10]);
	    serialize_uint16(tc_packet_seq_ctrl, &tm_bytes[12]);
	    /*serialize_uint16(tc_packet_err_ctrl, &tm_bytes[14]);
	    serialize_uint16(calculated_crc, &tm_bytes[16]);*/

	    return;
}
