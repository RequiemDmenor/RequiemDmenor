#ifndef INCLUDE_CCSDS_PUS_STDIO_H_
#define INCLUDE_CCSDS_PUS_STDIO_H_
#include "basic_types.h"
#include "ccsds_pus_format.h"

void ccsds_pus_tmtc_print_packet_id(uint16_t packet_id);
void ccsds_pus_tmtc_print_packet_sequence_control(uint16_t packet_seq_ctrl);
/*void ccsds_pus_tmtc_print_df_header(uint32_t df_header);*/

/*uint16_t ccsds_pus_tc_read(int fd,uint8_t tc_bytes[]);*/

/**
 * \brief Stores a serialized telemetry packet into a file
 *
 * \param fd descriptor of the file into which the packet will be stored
 * \param tm_bytes vector that contains the generated serialized telemetry
 */
void ccsds_pus_tm_write(int fd, uint8_t tm_bytes[], uint8_t x);

/**
 * \brief Print data field header
 *
 * \param tc_df_header telecommand data field header
 */
void ccsds_pus_tc_print_df_header_fields(struct ccds_pus_tc_df_header tc_df_header);

#endif /*INCLUDE_CCSDS_PUS_STDIO_H */
