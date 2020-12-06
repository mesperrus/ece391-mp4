#include "sched.h"
#include "lib.h"
#include "paging.h"

// Find the current process id which the OS is currently giving CPU time to
int32_t cur_proc() {
    // TODO
    return -1;
}

// Find the next process id which the OS will give CPU time to next
int32_t next_proc() {
    // TODO
    return -1;
}

// Return whether a process is currently open in a terminal. False: 0, True: 1
int32_t proc_in_term() {
    // TODO
    return -1;
}

// Gets the address for non-display memory for a specific process
uint32_t proc_non_disp_addr(uint32_t p_id) {
    // TODO
    return NULL;
}

/* cycle_task
   DESCRIPTION: function to call for the OS to move to another task,
                  to be called periodically by PIT
   INPUTS: none
   OUTPUTS: none
   RETURNS: -1 on failure, 0 on success
   SIDE EFFECTS: switches tasks running in CPU
*/
uint32_t cycle_task() {
    /* Get next process id which we will switch to */
    uint32_t cur_p_id = cur_proc();
    uint32_t next_p_id = next_proc();
    /* Map virtual memory to appriate physical location */

    // if next process is in open terminal, map virtual video memory to
    //   physical video memory
    if (proc_in_term(next_p_id)) {
        map_v_p(VIDEO, VIDEO, 0, 1, 1);
    }

    // if next process is not in open terminal, map virtual video memory
    //   to task's non-display memory
    else {
        map_v_p(VIDEO, proc_non_disp_addr(next_p_id), 0, 1, 1);
    }

    /* TASK SWITCH (do something similar to HALT) */
    /* Initialize variables */
	uint32_t esp;
	uint32_t ebp;
    uint32_t cur_pcb_ptr = find_PCB(cur_p_id);
	uint32_t next_pcb_ptr = find_PCB(next_p_id);

	/* NOT closing all the files in the pcb (like we do in halt)*/

    // TODO: DO SOMETHING WITH VIDMAP?
    //  if it was previously called on the incoming task, do we have to remap it?
    //  And if it was called on the outgoing task, do we have to unmap it?


    /* === CONTEXT SWITCH === */
	/* Update stack pointers and base pointers */
    // TODO: PROBLEM:
    //  currently a task's esp and ebp is stored on its child's PCB.
    //  To make scheduling work, it needs to be stored on its own PCB
    //  so that it can restore itself with a round-robin approach rather
    //  than a parent-child approach

    // asm volatile ("                               \n\
	// 	movl %%esp, %0                            \n\
	// 	movl %%ebp, %1                            \n\
	// 	"
	// 	: "=r"(cur_pcb_ptr->esp), "=r"(cur_pcb_ptr->ebp)
	// 	: /* no inputs */
	// 	: "cc"
	// );
	// esp = next_pcb_ptr->esp;
	// ebp = next_pcb_ptr->ebp;

    /* Update TSS */
    // tss.esp0 = (KERNEL_MEMORY_ADDR + MB_4) - (next_p_id) * PCB_SIZE - 4;

	/* Jump to execute return */
	/* exec_ret jumps to assembly in execute */
    // flush_tlb();
	// asm volatile("           		  	\n\
    // 	movb    %0, %%bl				\n\
	// 	movl    %1, %%esp               \n\
	// 	movl    %2, %%ebp               \n\
	// 	jmp		exec_ret				\n\
	// 	"
	// 	:
	// 	: "r"(status), "r"(esp), "r"(ebp)
	// 	: "cc", "memory"
	// );
	// return 0;
    return -1;
}