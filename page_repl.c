#include <stdio.h>
#include <limits.h>

#define MAX_FRAMES 10
#define MAX_PAGES 30

// Function to find the LRU page
int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;
    for (i = 1; i < n; ++i) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

// Function to find the LFU page
int findLFU(int freq[], int n) {
    int i, minimum = freq[0], pos = 0;
    for (i = 1; i < n; ++i) {
        if (freq[i] < minimum) {
            minimum = freq[i];
            pos = i;
        }
    }
    return pos;
}

void LRU(int pages[], int no_of_pages, int no_of_frames) {
    int frames[MAX_FRAMES], time[MAX_FRAMES], counter = 0, flag1, flag2, i, j, pos, faults = 0;

    for (i = 0; i < no_of_frames; ++i) {
        frames[i] = -1;
    }

    for (i = 0; i < no_of_pages; ++i) {
        flag1 = flag2 = 0;

        for (j = 0; j < no_of_frames; ++j) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            for (j = 0; j < no_of_frames; ++j) {
                if (frames[j] == -1) {
                    counter++;
                    faults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0) {
            pos = findLRU(time, no_of_frames);
            counter++;
            faults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }

        printf("\n");

        for (j = 0; j < no_of_frames; ++j) {
            if (frames[j] != -1) {
                printf("%d\t", frames[j]);
            } else {
                printf("-\t");
            }
        }
    }

    printf("\n\nTotal Page Faults (LRU) = %d\n", faults);
}

void FIFO(int pages[], int no_of_pages, int no_of_frames) {
    int frames[MAX_FRAMES], flag1, flag2, i, j, k, pos = 0, faults = 0;

    for (i = 0; i < no_of_frames; ++i) {
        frames[i] = -1;
    }

    for (i = 0; i < no_of_pages; ++i) {
        flag1 = flag2 = 0;

        for (j = 0; j < no_of_frames; ++j) {
            if (frames[j] == pages[i]) {
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            if (frames[pos] == -1) {
                frames[pos] = pages[i];
                pos = (pos + 1) % no_of_frames;
            } else {
                frames[pos] = pages[i];
                pos = (pos + 1) % no_of_frames;
            }
            faults++;
        }

        printf("\n");

        for (k = 0; k < no_of_frames; ++k) {
            if (frames[k] != -1) {
                printf("%d\t", frames[k]);
            } else {
                printf("-\t");
            }
        }
    }

    printf("\n\nTotal Page Faults (FIFO) = %d\n", faults);
}

void LFU(int pages[], int no_of_pages, int no_of_frames) {
    int frames[MAX_FRAMES], freq[MAX_FRAMES], flag1, flag2, i, j, pos, faults = 0;

    for (i = 0; i < no_of_frames; ++i) {
        frames[i] = -1;
        freq[i] = 0;
    }

    for (i = 0; i < no_of_pages; ++i) {
        flag1 = flag2 = 0;

        for (j = 0; j < no_of_frames; ++j) {
            if (frames[j] == pages[i]) {
                flag1 = flag2 = 1;
                freq[j]++;
                break;
            }
        }

        if (flag1 == 0) {
            for (j = 0; j < no_of_frames; ++j) {
                if (frames[j] == -1) {
                    frames[j] = pages[i];
                    freq[j]++;
                    faults++;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0) {
            pos = findLFU(freq, no_of_frames);
            frames[pos] = pages[i];
            freq[pos] = 1;
            faults++;
        }

        printf("\n");

        for (j = 0; j < no_of_frames; ++j) {
            if (frames[j] != -1) {
                printf("%d\t", frames[j]);
            } else {
                printf("-\t");
            }
        }
    }

    printf("\n\nTotal Page Faults (LFU) = %d\n", faults);
}

int main() {
    int no_of_frames, no_of_pages, pages[MAX_PAGES], i, choice;

    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);

    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);

    printf("Enter reference string: ");
    for (i = 0; i < no_of_pages; ++i) {
        scanf("%d", &pages[i]);
    }

    printf("\nChoose a page replacement algorithm:\n");
    printf("1. LRU\n");
    printf("2. FIFO\n");
    printf("3. LFU\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            LRU(pages, no_of_pages, no_of_frames);
            break;
        case 2:
            FIFO(pages, no_of_pages, no_of_frames);
            break;
        case 3:
            LFU(pages, no_of_pages, no_of_frames);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    return 0;
}
