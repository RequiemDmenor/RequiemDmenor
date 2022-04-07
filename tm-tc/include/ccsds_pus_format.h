
#ifndef INCLUDE_CCSDS_PUS_FORMAT_H_
#define INCLUDE_CCSDS_PUS_FORMAT_H_

#include "basic_types.h"

uint16_t ccsds_pus_tc_get_APID(uint16_t packet_id);

uint16_t ccsds_pus_tc_get_Sequence_Flags(uint16_t packet_seq_ctrl);

uint16_t ccsds_pus_tc_get_Sequence_Count(uint16_t packet_seq_ctrl);

uint16_t ccsds_pus_tc_get_Ack(uint32_t df_header);

uint16_t ccsds_pus_tc_get_Service_Type(uint32_t df_header);

uint16_t ccsds_pus_tc_get_Service_Subtype(uint32_t df_header);

uint16_t ccsds_pus_tc_get_Source_ID(uint32_t df_header);

/**
 * \brief Deserializes the fields of a telecommand stored in a vector
 *
 * \param tc_bytes vector that stores the bytes of the telecommand
 * \param p_packet_id pointer to the variable that shall store the Packet ID
 * \param p_packet_seq_ctrl pointer to the variable that shall store the
 *                          Packet Sequence Control field
 * \param p_packet_len pointer to the variable that shall store the Packet
 *                     Length field
 * \param p_df_header pointer to the variable that shall store the Data Field
 *                    Header
 * \param p_packet_err_ctrl pointer to the variable that shall store the
 *                          Packet Error Control
 */
void ccsds_pus_tc_get_fields(uint8_t tc_bytes[],
                             uint16_t * p_packet_id,
                             uint16_t * p_packet_seq_ctrl,
                             uint16_t * p_packet_len,
                             uint32_t * p_df_header,
                             uint16_t * p_packet_err_ctrl);

#endif  INCLUDE_CCSDS_PUS_FORMAT_H_

