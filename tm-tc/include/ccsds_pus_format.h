
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
/*void ccsds_pus_tc_get_fields(uint8_t tc_bytes[],
                             uint16_t * p_packet_id,
                             uint16_t * p_packet_seq_ctrl,
                             uint16_t * p_packet_len,
                             uint32_t * p_df_header,
                             uint16_t * p_packet_err_ctrl);*/

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

/*void ccsds_pus_tm_set_fields(uint8_t tm_bytes[],
                             uint16_t tm_packet_id,
                             uint16_t tm_packet_seq_ctrl,
                             uint16_t tm_packet_length,
                             uint32_t tm_df_header);*/

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
//#define ccsds_pus_tc_get_Service_Type(df_header) (df_header>>16 & 0x00FF)

/**
 * \brief Get Service Subtype from a telecommand's Data Field Header.
 *
 * \param tc_df_header the telecommand's Data Field Header
 *
 * \return the telecommand's Service Subtype
 */
//#define ccsds_pus_tc_get_Service_Subtype(df_header) (df_header>>8 & 0x000000FF)

/**
 * \brief Get Source ID from a telecommand's Data Field Header.
 *
 * \param df_header the telecommand's Data Field Header
 *
 * \return the telecommand's Source ID
 */
/*#define ccsds_pus_tc_get_Source_ID(df_header) (df_header & 0x0000FF)*/

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


/**
 * \brief Structure type to the Packet Header field of a TM/TC packet.
 */
struct ccds_pus_tmtc_packet_header {

    uint16_t packet_id;
    uint16_t packet_seq_ctrl;
	uint16_t packet_len;
};

/**
 * \brief Structure type to store the Data Field Header field of a TC packet.
 */
struct ccds_pus_tc_df_header {

    uint8_t flag_ver_ack;
    uint8_t tc_type;
    uint8_t tc_subtype;
    uint8_t sourceID;

};

/**
 * \brief Structure type to store the Data Field Header field of a TM packet.
 */
struct ccds_pus_tm_df_header {

    uint8_t version;
    uint8_t type;
    uint8_t subtype;
    uint8_t destinationID;

};

/**
 * \brief Get Ack from a telecommand's Data Field Header.
 *
 * \param flag_ver_ack the first byte of a telecommand's Data Field Header
 *
 * \return the telecommand's Ack
 */
#define ccsds_pus_tc_get_ack(flag_ver_ack) ((flag_ver_ack) & 0x0F)

/**
 * \brief Builds the most significant byte of the Data Field Header of a telmetry.
 *
 * \param version the value of the Version subfield
 *
 * \return the MSB of the Data Field Header
 */
#define ccsds_pus_tm_build_df_header_version(version) (((version) & 0x7) << 4)

/**
 * \brief Deserializes the fields of a telecommand stored in a vector
 *
 * \param tc_bytes vector that stores the bytes of the telecommand
 * \param p_tc_packet_header pointer to the struct that shall store the Packet
 *                           Header
 * \param p_tc_df_header pointer to the struct that shall store the Data Field
 *                       Header
 * \param p_tc_packet_err_ctrl pointer to the variable that shall store the
 *                             Packet Error Control
 */
void ccsds_pus_tc_get_fields(uint8_t tc_bytes[],
                        struct ccds_pus_tmtc_packet_header * p_tc_packet_header,
                        struct ccds_pus_tc_df_header * p_tc_df_header,
                        uint16_t * p_tc_packet_err_ctrl);

/**
 * \brief Serializes and stores into a vector the main fields of a TM packet.
 *
 * \param tm_bytes vector that will store the generated serialized telemetry
 * \param p_tm_packet_header const pointer to the struct that defines the
 *                           Packet Header
 * \param p_tm_df_header the const pointer to the struct that defines the
 *                           TM Data Field Header
 */
void ccsds_pus_tm_set_fields(uint8_t tm_bytes[],
                        const struct ccds_pus_tmtc_packet_header * p_tm_packet_header,
                        const struct ccds_pus_tm_df_header * p_tm_df_header);

#endif  INCLUDE_CCSDS_PUS_FORMAT_H_

