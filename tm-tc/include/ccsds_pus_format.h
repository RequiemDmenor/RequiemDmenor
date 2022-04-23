
#ifndef INCLUDE_CCSDS_PUS_FORMAT_H_
#define INCLUDE_CCSDS_PUS_FORMAT_H_

#include "basic_types.h"

/*uint16_t ccsds_pus_tc_get_APID(uint16_t packet_id);

uint8_t ccsds_pus_tc_get_Sequence_Flags(uint16_t packet_seq_ctrl);

uint16_t ccsds_pus_tc_get_Sequence_Count(uint16_t packet_seq_ctrl);

uint8_t ccsds_pus_tc_get_Ack(uint32_t df_header);

uint8_t ccsds_pus_tc_get_Service_Type(uint32_t df_header);

uint8_t ccsds_pus_tc_get_Service_Subtype(uint32_t df_header);

uint8_t ccsds_pus_tc_get_Source_ID(uint32_t df_header);*/

uint16_t ccsds_pus_tc_read(int fd, uint8_t tc_bytes[]);
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

/**
 * \brief Builds the Packet ID of a telmetry.
 *
 * \param apid the value of the APID subfield
 *
 * \return the Packet ID field
 */
/*uint16_t ccsds_pus_tm_build_packet_id(uint16_t apid);*/

/**
 * \brief Builds the Packet Sequence Control of a telmetry.
 *
 * \param flags the value of the Sequence Flags subfield
 * \param count the value of the Sequence Count subfield
 *
 * \return the Packet Sequence Control field
 */
/*uint16_t ccsds_pus_tm_build_packet_seq_ctrl(uint8_t sequence_flags, uint16_t sequence_count);*/

/**
 * \brief Builds the Data Field Header of a telmetry.
 *
 * \param type the value of the Type subfield
 * \param subtype the value of the Subtype subfield
 * \param dest the value of the Destination ID subfield
 *
 * \return the Data Field Header
 */
/*uint32_t ccsds_pus_tm_build_df_header(uint8_t service_type, uint8_t service_subtype, uint8_t destination_id, uint16_t crc, uint16_t packet_err_ctrl);*/

void ccsds_pus_tm_set_fields(uint8_t tm_bytes[],
                             uint16_t tm_packet_id,
                             uint16_t tm_packet_seq_ctrl,
                             uint16_t tm_packet_length,
                             uint32_t tm_df_header);

/**
 * \brief Get APID from a telecommand's Packet ID.
 *
 * \param tc_packet_id the telecommand's Packet ID
 *
 * \return the telecommand's APID
 */
#define ccsds_pus_tc_get_APID(packet_id) (packet_id & 0x07FF)

/**
 * \brief Get Sequence Count from a telecommand's Packet Sequence Control.
 *
 * \param tc_packet_seq_ctrl the telecommand's Packet Sequence Control
 *
 * \return the telecommand's Sequence Flags
 */
#define ccsds_pus_tc_get_Sequence_Flags(packet_seq_ctrl) (packet_seq_ctrl >> 14)

/**
 * \brief Get Sequence Count from a telecommand's Packet Sequence Control.
 *
 * \param tc_packet_seq_ctrl the telecommand's Packet Sequence Control
 *
 * \return the telecommand's Sequence Count
 */
#define ccsds_pus_tc_get_Sequence_Count(packet_seq_ctrl) (packet_seq_ctrl & 0x3FFF)

/**
 * \brief Get Ack from a telecommand's Data Field Header.
 *
 * \param tc_df_header the telecommand's Data Field Header
 *
 * \return the telecommand's Ack
 */
#define ccsds_pus_tc_get_Ack(df_header) (df_header>>24 & 0x0F)

/**
 * \brief Get Service Type from a telecommand's Data Field Header.
 *
 * \param tc_df_header the telecommand's Data Field Header
 *
 * \return the telecommand's Service Type
 */
#define ccsds_pus_tc_get_Service_Type(df_header) (df_header>>16 & 0x00FF)

/**
 * \brief Get Service Subtype from a telecommand's Data Field Header.
 *
 * \param tc_df_header the telecommand's Data Field Header
 *
 * \return the telecommand's Service Subtype
 */
#define ccsds_pus_tc_get_Service_Subtype(df_header) (df_header>>8 & 0x000000FF)

/**
 * \brief Get Source ID from a telecommand's Data Field Header.
 *
 * \param df_header the telecommand's Data Field Header
 *
 * \return the telecommand's Source ID
 */
#define ccsds_pus_tc_get_Source_ID(df_header) (df_header & 0x0000FF)

/**
 * \brief Builds the Packet ID of a telmetry.
 *
 * \param apid the value of the APID subfield
 *
 * \return the Packet ID field
 */
#define ccsds_pus_tm_build_packet_id(apid) ((1 << 11) | (apid) & 0x07FF)

/**
 * \brief Builds the Packet Sequence Control of a telmetry.
 *
 * \param flags the value of the Sequence Flags subfield
 * \param count the value of the Sequence Count subfield
 *
 * \return the Packet Sequence Control field
 */
#define ccsds_pus_tm_build_sequence_control(seq_flags, seq_count) ((seq_flags & 0xC000) | seq_count)

/**
 * \brief Builds the Data Field Header of a telmetry.
 *
 * \param type the value of the Type subfield
 * \param subtype the value of the Subtype subfield
 * \param dest the value of the Destination ID subfield
 *
 * \return the Data Field Header
 */
#define ccsds_pus_tm_build_df_header(Service_Subtype) (0x10010000 | Service_Subtype << 8 | EPD_DESTINATION_ID)

#endif  INCLUDE_CCSDS_PUS_FORMAT_H_

