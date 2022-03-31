
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

#endif  INCLUDE_CCSDS_PUS_FORMAT_H_
