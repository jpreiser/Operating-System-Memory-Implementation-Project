#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "API.h"
#include "clock_list.h"
#include "list.h"


int i = -1;
struct Node *head = NULL;
struct ClockNode *clockHead = NULL;

int fifo()
{
		i++;
		return i % MAX_PFN;
}

int lru()
{
		return head->data;
}

int clock()
{
		while(clockHead->ref == 1) {
			int p = clockHead->ref;
			clockHead = cl_remove_head(clockHead);
			clockHead = cl_insert_tail(clockHead, p, 0);
		}
		return clockHead->data;
}

/*========================================================================*/

int find_replacement()
{
		int PFN;
		if(replacementPolicy == ZERO)  PFN = 0;
		else if(replacementPolicy == FIFO)  PFN = fifo();
		else if(replacementPolicy == LRU) PFN = lru();
		else if(replacementPolicy == CLOCK) PFN = clock();

		return PFN;
}

int pagefault_handler(int pid, int VPN, char reqType)
{
		int PFN;

		// find a free PFN.
		PFN = get_freeframe();
		
		// no free frame available. find a victim using a page replacement algorithm. ;
		if(PFN < 0) 
		{
			PFN = find_replacement();

			if (replacementPolicy == LRU) 
			{
				head = list_remove_head(head);
			} 
			else if (replacementPolicy == CLOCK) 
			{
				clockHead = cl_remove_head(clockHead);
			}

			IPTE ipte = read_IPTE(PFN);
			PTE pte = read_PTE(ipte.pid, ipte.VPN);
			swap_out(ipte.pid, ipte.VPN, pte.PFN);
			pte.valid = false;
			write_PTE(ipte.pid, ipte.VPN, pte);
		}
		
		if (replacementPolicy == LRU) 
		{

		}
		return PFN;
}

int get_PFN(int pid, int VPN, char reqType)
{
		/* Read page table entry for (pid, VPN) */
		PTE pte = read_PTE(pid, VPN);

		/* if PTE is valid, it is a page hit. Return physical frame number (PFN) */
		if(pte.valid) {
		/* Mark the page dirty, if it is a write request */
				if(reqType == 'W') {
						pte.dirty = true;
						write_PTE(pid, VPN, pte);
				}
				return pte.PFN;
		}
		
		/* PageFault, if the PTE is invalid. Return -1 */
		return -1;
}

int MMU(int pid, int virtAddr, char reqType, bool *hit)
{
		int PFN, physicalAddr;
		int VPN = 0, offset = 0;
		
		/* calculate VPN and offset */
		VPN = (virtAddr >> 8);
		offset = virtAddr - (VPN << 8);
		
		// read page table to get Physical Frame Number (PFN)
		PFN = get_PFN(pid, VPN, reqType);
		if(PFN >= 0) { // page hit
				stats.hitCount++;
				*hit = true;
		} else { // page miss
				stats.missCount++;
				*hit = false;
				PFN = pagefault_handler(pid, VPN, reqType);
		}

		physicalAddr = (PFN << 8) + offset;
		return physicalAddr;
}

