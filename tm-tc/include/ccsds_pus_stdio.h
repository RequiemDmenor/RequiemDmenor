#ifndef INCLUDE_CCSDS_PUS_STDIO_H_
#define INCLUDE_CCSDS_PUS_STDIO_H_

#include "basic_types.h"

void ccsds_pus_tmtc_print_packet_id(uint16_t packet_id);

void ccsds_pus_tmtc_print_packet_sequence_control(uint16_t packet_seq_ctrl);

void ccsds_pus_tmtc_print_df_header(uint32_t df_header);

#endif INCLUDE_CCSDS_PUS_STDIO_H
