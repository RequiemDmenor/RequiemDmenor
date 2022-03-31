#include "basic_types.h"
#include "ccsds_pus_format.h"

uint16_t ccsds_pus_tc_get_APID(uint16_t packet_id) {

    return (packet_id & 0x07FF);

}

uint16_t ccsds_pus_tc_get_Sequence_Flags(uint16_t packet_seq_ctrl) {

    return (packet_seq_ctrl >>14);

}

uint16_t ccsds_pus_tc_get_Sequence_Count(uint16_t packet_seq_ctrl) {

    return (packet_seq_ctrl & 0x3FFF);

}

uint16_t ccsds_pus_tc_get_Ack(uint32_t df_header) {

    return ((df_header >>24) & 0x00F);

}

uint16_t ccsds_pus_tc_get_Service_Type(uint32_t df_header) {

    return ((df_header>>16) & 0x00FF);

}

uint16_t ccsds_pus_tc_get_Service_Subtype(uint32_t df_header) {

    return ((df_header>>8) & 0x0000FF);

}

uint16_t ccsds_pus_tc_get_Source_ID(uint32_t df_header) {

    return (df_header & 0xFF);

}
