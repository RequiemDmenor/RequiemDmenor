#include "epd_pus_tmtc.h"
#include "epd_pus_mission.h"
#include "ccsds_pus_format.h"
#include "serialize.h"
#include "system_tm_queue.h"

/*void epd_pus_build_tm_1_1(uint8_t tm_bytes[],
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

}*/

/*void epd_pus_build_tm_1_2_crc_error(uint8_t tm_bytes[],
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
	    serialize_uint16(calculated_crc, &tm_bytes[16]);

	    return;
}*/

/*void epd_pus_build_tm_1_1(uint8_t tm_bytes[],
                          uint16_t tm_seq_counter,
                          uint16_t tc_packet_id,
                          uint16_t tc_packet_seq_ctrl) {


    struct ccds_pus_tmtc_packet_header tm_packet_header;
    struct ccds_pus_tm_df_header df_header;

    tm_packet_header.packet_id = ccsds_pus_tm_build_packet_id(EPD_APID);

    tm_packet_header.packet_seq_ctrl = ccsds_pus_tm_build_sequence_control(0x3,
            tm_seq_counter);

    tm_packet_header.packet_len = 0x07;

    df_header.version = ccsds_pus_tm_build_df_header_version(0x1);
    df_header.type = 1;
    df_header.subtype = 1;
    df_header.destinationID = EPD_DESTINATION_ID;

    ccsds_pus_tm_set_fields(&tm_bytes[0], &tm_packet_header, &df_header);

    serialize_uint16(tc_packet_id, &tm_bytes[10]);
    serialize_uint16(tc_packet_seq_ctrl, &tm_bytes[12]);

    return;

}*/

/*void epd_pus_build_tm_1_2_crc_error(uint8_t tm_bytes[],
                          uint16_t tm_seq_counter,
                          uint16_t tc_packet_id,
                          uint16_t tc_packet_seq_ctrl,
						  uint16_t tc_packet_err_ctrl,
						  uint16_t calculated_crc) {

	struct ccds_pus_tmtc_packet_header tm_packet_header;
	struct ccds_pus_tm_df_header df_header;

	tm_packet_header.packet_id = ccsds_pus_tm_build_packet_id(EPD_APID);

	tm_packet_header.packet_seq_ctrl = ccsds_pus_tm_build_sequence_control(0x3, tm_seq_counter);

	tm_packet_header.packet_len = 0x0D;

	df_header.version = ccsds_pus_tm_build_df_header_version(0x1);
	    df_header.type = 1;
	    df_header.subtype = 2;
	    df_header.destinationID = EPD_DESTINATION_ID;

	    ccsds_pus_tm_set_fields(&tm_bytes[0], &tm_packet_header, &df_header);

	    serialize_uint16(tc_packet_id, &tm_bytes[10]);
	    serialize_uint16(tc_packet_seq_ctrl, &tm_bytes[12]);
	    serialize_uint16(tc_packet_err_ctrl, &tm_bytes[14]);
	    serialize_uint16(calculated_crc, &tm_bytes[16]);

	    return;
}*/

void epd_pus_build_tm_1_1(tm_descriptor_t *p_tm_descriptor,
        uint16_t tm_seq_counter,
        uint16_t tc_packet_id,
        uint16_t tc_packet_seq_ctrl) {

    struct ccds_pus_tmtc_packet_header tm_packet_header;
    struct ccds_pus_tm_df_header df_header;

    tm_packet_header.packet_id = (ccsds_pus_tm_build_packet_id(EPD_APID));

    tm_packet_header.packet_seq_ctrl =
    		ccsds_pus_tm_build_sequence_control(0x3, tm_seq_counter);

    tm_packet_header.packet_len = 0x07;

    df_header.version = 0x10;
    df_header.type = 1;
    df_header.subtype = 1;
    df_header.destinationID = EPD_DESTINATION_ID;

    ccsds_pus_tm_set_fields(p_tm_descriptor->p_tm_bytes,
            &tm_packet_header, &df_header);
    // This is equivalent to the previous call:
    // ccsds_pus_tm_set_fields(&tm_descriptor.p_tm_bytes[0],
    //     &tm_packet_header, &df_header);

    serialize_uint16(tc_packet_id, &p_tm_descriptor->p_tm_bytes[10]);
    // This is equivalent to the previous call:
    // serialize_uint16(tc_packet_id, tm_descriptor.p_tm_bytes+10);

    serialize_uint16(tc_packet_seq_ctrl, p_tm_descriptor->p_tm_bytes + 12);
    // This is equivalent to the previous call:
    // serialize_uint16(tc_packet_seq_ctrl, &tm_descriptor.p_tm_bytes[12]);

    // Calculate p_tm_descriptor->tm_num_bytes
    p_tm_descriptor->tm_num_bytes = 6 + tm_packet_header.packet_len + 1;

    return;

}


void epd_pus_build_tm_1_2_crc_error(tm_descriptor_t *p_tm_descriptor,
        uint16_t tm_seq_counter,
        uint16_t tc_packet_id,
        uint16_t tc_packet_seq_ctrl,
		uint16_t tc_packet_err_ctrl,
		uint16_t calculated_crc) {

    struct ccds_pus_tmtc_packet_header tm_packet_header;
    struct ccds_pus_tm_df_header df_header;

    tm_packet_header.packet_id = (ccsds_pus_tm_build_packet_id(EPD_APID));

    tm_packet_header.packet_seq_ctrl =
    		ccsds_pus_tm_build_sequence_control(0x3, tm_seq_counter);

    tm_packet_header.packet_len = 0x0D;

    df_header.version = 0x10;
    df_header.type = 1;
    df_header.subtype = 2;
    df_header.destinationID = EPD_DESTINATION_ID;

    ccsds_pus_tm_set_fields(p_tm_descriptor->p_tm_bytes,
            &tm_packet_header, &df_header);
    // This is equivalent to the previous call:
    // ccsds_pus_tm_set_fields(&tm_descriptor.p_tm_bytes[0],
    //     &tm_packet_header, &df_header);

    serialize_uint16(tc_packet_id, &p_tm_descriptor->p_tm_bytes[10]);
    // This is equivalent to the previous call:
    // serialize_uint16(tc_packet_id, tm_descriptor.p_tm_bytes+10);

    serialize_uint16(tc_packet_seq_ctrl, p_tm_descriptor->p_tm_bytes + 12);
    // This is equivalent to the previous call:
    // serialize_uint16(tc_packet_seq_ctrl, &tm_descriptor.p_tm_bytes[12]);
    serialize_uint16(tc_packet_err_ctrl, p_tm_descriptor->p_tm_bytes + 14);
    serialize_uint16(calculated_crc, p_tm_descriptor->p_tm_bytes + 16);
    // Calculate p_tm_descriptor->tm_num_bytes
    p_tm_descriptor->tm_num_bytes = 6 + tm_packet_header.packet_len + 1;

    return;

}
