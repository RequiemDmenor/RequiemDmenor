#ifndef INCLUDE_SYSTEM_TM_POOL_H_
#define INCLUDE_SYSTEM_TM_POOL_H_

#include "basic_types.h"

#include "system_tm_queue.h"

/**
 * \brief Initializes THE TM memory pool. This function has to be called BEFORE
 *        the rest of the pool management functions are actually used. The pool
 *        has a fixed size of 20 elements. The allocated blocks will have a
 *        fixed size of 256 bytes.
 */
void init_system_tm_pool();

/**
 * \brief Allocates a memory block to store a TM packet and assigns it to a TM
 *        descriptor.
 *
 * @param p_tm_descriptor references the descriptor to which the TM block
 *                        will be assigned.
 *
 * @return returns 1 if there was an error during allocation (if the pool was
 *         empty), 0 if the allocation was successful.
 */
uint8_t tm_pool_alloc_tm(tm_descriptor_t * p_tm_descriptor);

/**
 * \brief Frees a previously allocated TM memory block.
 *
 * @param p_tm_descriptor references the descriptor whose TM block will be
 *                        freed.
 *
 * @return returns 1 if there was an error when trying to free the TM block
 *         (if the block had already been freed), 0 if the operation was
 *         successful.
 */
uint8_t tm_pool_free_tm(tm_descriptor_t * p_tm_descriptor);


#endif /* INCLUDE_SYSTEM_TM_POOL_H_ */
