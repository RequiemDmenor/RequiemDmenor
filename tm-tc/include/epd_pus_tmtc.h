#ifndef INCLUDE__EPD_PUS_TMTC_H_
#define INCLUDE__EPD_PUS_TMTC_H_
#include "basic_types.h"
#include "system_tm_queue.h"
/**
 * \brief Generates a Telemetry Packet (1,1) - Accept
 *
 * \param tm_bytes vector that will store the generated serialized telemetry
 * \param tm_seq_counter the Sequence Count of the telemetry packet
 * \param tc_packet_id the Packet ID of the accepted telecommand
 * \param tc_packet_seq_ctrl the Packet Sequence Control of the accepted
 *                           telecommand
 */
/*void epd_pus_build_tm_1_1(uint8_t tm_bytes[],
        uint16_t tm_seq_counter,
        uint16_t tc_packet_id,
        uint16_t tc_packet_seq_ctrl);*/

/**
 * \brief Generates a Telemetry Packet (1,2) - Reject
 *
 * \param tm_bytes vector that will store the generated serialized telemetry
 * \param tm_seq_counter the Sequence Count of the telemetry packet
 * \param tc_packet_id the Packet ID of the rejected telecommand
 * \param tc_packet_seq_ctrl the Packet Sequence Control of the rejected
 *                           telecommand
 * \param tc_packet_err_ctrl the Packet Error Control field of the rejected
 *                           telecommand
 * \param calculated_crc the locally-obtained value of the CRC
 */
/*void epd_pus_build_tm_1_2_crc_error(uint8_t tm_bytes[],
                          uint16_t tm_seq_counter,
                          uint16_t tc_packet_id,
                          uint16_t tc_packet_seq_ctrl,
						  uint16_t tc_packet_err_ctrl,
						  uint16_t calculated_crc);*/

/**
 * \brief Generates a Telemetry Packet (1,1) - Accept
 *
 * \param p_tm_descriptor pointer to the TM descriptor that will manage the
 *                        storage of the serialized generated telemetry
 * \param tm_seq_counter the Sequence Count of the telemetry packet
 * \param tc_packet_id the Packet ID of the accepted telecommand
 * \param tc_packet_seq_ctrl the Packet Sequence Control of the accepted
 *                           telecommand
 */
void epd_pus_build_tm_1_1(tm_descriptor_t *p_tm_descriptor,
        uint16_t tm_seq_counter,
        uint16_t tc_packet_id,
        uint16_t tc_packet_seq_ctrl);

/**
 * \brief Generates a Telemetry Packet (1,2) - Reject
 *
 * \param p_tm_descriptor pointer to the TM descriptor that will manage the
 *                        storage of serialized generated telemetry
 * \param tm_seq_counter the Sequence Count of the telemetry packet
 * \param tc_packet_id the Packet ID of the rejected telecommand
 * \param tc_packet_seq_ctrl the Packet Sequence Control of the rejected
 *                           telecommand
 * \param tc_packet_err_ctrl the Packet Error Control field of the rejected
 *                           telecommand
 * \param calculated_crc the locally-obtained value of the CRC
 */
//Declare function epd_pus_build_tm_1_2_crc_error
void epd_pus_build_tm_1_2_crc_error(tm_descriptor_t *p_tm_descriptor,
        uint16_t tm_seq_counter,
        uint16_t tc_packet_id,
        uint16_t tc_packet_seq_ctrl,
		uint16_t tc_packet_err_ctrl,
		uint16_t calculated_crc);


#endif /* INCLUDE__EPD_PUS_TMTC_H_ */
