
#ifndef INCLUDE_SYSTEM_TM_QUEUE_H_
#define INCLUDE_SYSTEM_TM_QUEUE_H_

#include "basic_types.h"

/**
 * \brief Structure that stores a single TM descriptor. It contains a pointer
 *        to the allocated memory that stores the TM packet and the number of
 *        bytes that are actually in use by the TM packet.
 */
struct tm_descriptor {

    uint8_t * p_tm_bytes;
    uint16_t tm_num_bytes;

};

typedef struct tm_descriptor tm_descriptor_t;

/**
 * \brief Initializes THE TM queue. This function has to be called BEFORE the
 *        rest of the queue management functions are actually used.
 */
void init_system_tm_queue();

/**
 * \brief Checks whether THE queue is full or not.
 *
 * @return returns 1 if the queue is full, 0 if not.
 */
uint8_t tm_queue_is_full();

/**
 * \brief Checks whether THE queue is empty or not.
 *
 * @return returns 1 if the queue is empty, 0 if not.
 */
uint8_t tm_queue_is_empty();

/**
 * \ brief Extracts the first TM descriptor from the queue.
 *
 * @param p_tm_descriptor reference to the structure into which the descriptor
 *                        will be stored.
 * @return returns 1 if there was an error during extraction (if the queue was
 *         empty), 0 if the extraction was successful.
 */
uint8_t tm_queue_extract_tm(tm_descriptor_t * p_tm_descriptor);

/**
 * \ brief Inserts a TM descriptor at the end of the queue.
 *
 * @param tm_descriptor pointer to the descriptor to be stored.
 *
 * @return returns 1 if there was an error during insertion (if the queue was
 *         full), 0 if the insertion was successful.
 */
uint8_t tm_queue_insert_tm(tm_descriptor_t tm_descriptor);


#endif /* INCLUDE_SYSTEM_TM_QUEUE_H_ */
