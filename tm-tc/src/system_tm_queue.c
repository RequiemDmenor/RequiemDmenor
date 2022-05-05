#include "system_tm_queue.h"
#include "epd_pus_mission.h"

/**
 * \brief Type of the main structure that will be used to manage THE TM queue.
 */
struct tm_queue{
    uint8_t head_index;
    uint8_t queued_elements;
    tm_descriptor_t tm_descriptors[TM_QUEUE_MAX_NOE];
};

typedef struct tm_queue tm_queue_t;

/**
 * \brief THE one and only TM queue.
 */
static tm_queue_t system_tm_queue;

void init_system_tm_queue() {
	system_tm_queue.queued_elements=0;
	system_tm_queue.head_index=0;

}

uint8_t tm_queue_is_full() {

	uint8_t i=1;
    if(system_tm_queue.queued_elements==TM_QUEUE_MAX_NOE){
    	i=1;
    }else{
    	i=0;
    }
    return(i);
}

uint8_t tm_queue_is_empty() {

	 uint8_t i=1;
	 if(system_tm_queue.queued_elements==0){
	    	i=1;
	    }else{
	    	i=0;
	    }
	 return(i);
}

uint8_t tm_queue_extract_tm(tm_descriptor_t * p_tm_descriptor) {

    uint8_t is_empty = tm_queue_is_empty();

    if (!is_empty) {

        // Copy head_index element to *p_tm_descriptor
        *p_tm_descriptor =
                system_tm_queue.tm_descriptors[system_tm_queue.head_index];

        //Update head_index
        if(system_tm_queue.head_index !=19){
        	system_tm_queue.head_index=system_tm_queue.head_index+1;
        }else{
        	system_tm_queue.head_index=system_tm_queue.head_index-20;
        }

        //Decrease the number of queued elements
        system_tm_queue.head_index=system_tm_queue.head_index-1;

    }

    return (is_empty);

}


uint8_t tm_queue_insert_tm(tm_descriptor_t tm_descriptor) {

    uint8_t is_full = tm_queue_is_full();

    if (!is_full) {

        uint8_t next_tail_index;

        //Obtain the last used element of the queue and store its index into next_tail_index
        if((system_tm_queue.head_index + system_tm_queue.queued_elements)<19){
        	next_tail_index= system_tm_queue.head_index + system_tm_queue.queued_elements +1;
        }else{
        	next_tail_index= system_tm_queue.head_index + system_tm_queue.queued_elements -18;
        }


        // Store the descriptor
        system_tm_queue.tm_descriptors[next_tail_index] = tm_descriptor;

        // Increase the number of queued elements
        system_tm_queue.queued_elements = system_tm_queue.queued_elements + 1;

    }

    return (is_full);

}
