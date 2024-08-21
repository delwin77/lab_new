#include <stdio.h>

void fifo(){
	int num_frames, num_pages, i, j, page_faults = 0, current_frame = 0;

	printf("Enter the number of frames: ");
	scanf("%d", &num_frames);

	printf("Enter the number of pages: ");
	scanf("%d", &num_pages);

	int frames[num_frames], pages[num_pages], frame_in_use[num_frames];

	printf("Enter the page reference string:\n");

	for (i = 0; i < num_pages; i++) {
		scanf("%d", &pages[i]);
	}

	for (i = 0; i < num_frames; i++) {
		frames[i] = -1; 
		frame_in_use[i] = 0; 
	}

	printf("\nPage Reference String: ");
	for (i = 0; i < num_pages; i++) {
		printf("%d ", pages[i]);
	}
	printf("\n");
	
	printf("\nFIFO Page Replacement Algorithm:\n");

	for (i = 0; i < num_pages; i++) {
		int page_found = 0;
		for (j = 0; j < num_frames; j++) {
			if (frames[j] == pages[i]) {
				page_found = 1;
				break;
			}
		}

		if (!page_found) {
			printf("\nPage Fault: Page %d\n", pages[i]);
			page_faults++;
			frames[current_frame] = pages[i];
			frame_in_use[current_frame] = 1;
			current_frame = (current_frame + 1) % num_frames;
		}

		printf("Frames: ");
		for (j = 0; j < num_frames; j++) {
			printf("%d ", frames[j]);
		}
		printf("\n");
	}

	printf("\nTotal Page Faults: %d\n", page_faults);
}

void lru(){
	int num_frames, num_pages, i, j, page_faults = 0, current_frame = 0, least_recently_used;

	printf("Enter the number of frames: ");
	scanf("%d", &num_frames);
	
	printf("Enter the number of pages: ");
	scanf("%d", &num_pages);

	int frames[num_frames], pages[num_pages], last_used[num_frames];

	printf("Enter the page reference string:\n");
	for (i = 0; i < num_pages; i++) {
		scanf("%d", &pages[i]);
	}

	for (i = 0; i < num_frames; i++) {
		frames[i] = -1;
		last_used[i] = 0; 
	}

	printf("\nPage Reference String: ");
	for (i = 0; i < num_pages; i++) {
		printf("%d ", pages[i]);
	}
	printf("\n");
	
	printf("\nLRU Page Replacement Algorithm:\n");
	for (i = 0; i < num_pages; i++) {
		int page_found = 0;
		for (j = 0; j < num_frames; j++) {
			if (frames[j] == pages[i]) {
				page_found = 1;
				last_used[j] = i + 1; 
				break;
			}
		}

		if (!page_found) {
			printf("\nPage Fault: Page %d\n", pages[i]);
			page_faults++;
			least_recently_used = 0;
			
			for (j = 1; j < num_frames; j++) {
				if (last_used[j] < last_used[least_recently_used]) {
					least_recently_used = j;
				}
			}

			frames[least_recently_used] = pages[i]; 
			last_used[least_recently_used] = i + 1;
		}

		printf("Frames: ");
		for (j = 0; j < num_frames; j++) {
			printf("%d ", frames[j]);
		}
		printf("\n");
	}
	
	printf("\nTotal Page Faults: %d\n", page_faults);
}

void lfu(){
	int num_frames, num_pages, i, j, page_faults = 0;

	printf("Enter the number of frames: ");
	scanf("%d", &num_frames);
	
	printf("Enter the number of pages: ");
	scanf("%d", &num_pages);

	int frames[num_frames], pages[num_pages], page_frequency[num_pages];

	printf("Enter the page reference string:\n");
		for (i = 0; i < num_pages; i++) {
		scanf("%d", &pages[i]);
		page_frequency[i] = 0;
	}

	for (i = 0; i < num_frames; i++) {
		frames[i] = -1;
	}

	printf("\nPage Reference String: ");
	for (i = 0; i < num_pages; i++) {
		printf("%d ", pages[i]);
	}
	printf("\n");

	printf("\nLFU Page Replacement Algorithm:\n");
	for (i = 0; i < num_pages; i++) {
		int page_found = 0;
		int least_frequency_frame = 0;
		int least_frequency = page_frequency[frames[0]]; 
		
		for (j = 0; j < num_frames; j++) {
			if (frames[j] == pages[i]) {
				page_found = 1;
				page_frequency[pages[i]]++; 
				break;
			}
			if (page_frequency[frames[j]] < least_frequency) {
				least_frequency = page_frequency[frames[j]];
				least_frequency_frame = j;
			}
		}
		
		if (!page_found) {
			printf("\nPage Fault: Page %d\n", pages[i]);
			page_faults++;
			frames[least_frequency_frame] = pages[i]; 
			page_frequency[pages[i]] = 1; 
		}
		
		printf("Frames: ");
		for (j = 0; j < num_frames; j++) {
			printf("%d ", frames[j]);
		}
		printf("\n");
	}
	
	printf("\nTotal Page Faults: %d\n", page_faults);
}

int main(){
	int option, flag=1;

	while(flag){
		printf("\nEnter your choice:\n1:FIFO\n2:LRU (LEAST RECENTLY USED)\n3:LFU (LEAST FREQUENTLY USED)\n4:Exit\nYou choose:");
		scanf("%d", &option);
		switch(option){
			case 1:
				fifo();
				break;
			case 2:
				lru();
				break;
			case 3:
				lfu();
				break;
			case 4:
				flag = 0;
				break;
			default:
				printf("\nEnter valid option!\n");
		}
	}

	return 0;
}
