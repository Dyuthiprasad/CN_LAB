#include <stdio.h>

int min(int x, int y) {
    return (x < y) ? x : y;
}

int main() {
    int drop = 0, mini, nsec, cap, count = 0, i, inp[25], process;

    printf("Enter the bucket size: ");
    scanf("%d", &cap);

    printf("Enter the processing rate: ");
    scanf("%d", &process);

    printf("Enter the number of seconds you want to simulate: ");
    scanf("%d", &nsec);

    for (i = 0; i < nsec; i++) {
        printf("Enter the size of the packet entering at %d sec: ", i + 1);
        scanf("%d", &inp[i]);
    }

    printf("\nSecond | Packet Received | Packet Sent | Packet Left | Dropped\n");
    printf("---------------------------------------------------------------\n");

    for (i = 0; i < nsec; i++) {
        count += inp[i];

        if (count > cap) {
            drop = count - cap;
            count = cap;
        }

        printf("%4d\t%8d", i + 1, inp[i]);

        mini = min(count, process);
        printf("\t\t%8d", mini);

        count -= mini;
        printf("\t\t%8d\t\t%8d\n", count, drop);
        drop = 0;
    }

    // After simulation, process remaining packets in bucket
    while (count != 0) {
        if (count > cap) {
            drop = count - cap;
            count = cap;
        }

        printf("%4d\t%8d", ++i, 0);

        mini = min(count, process);
        printf("\t\t%8d", mini);

        count -= mini;
        printf("\t\t%8d\t\t%8d\n", count, drop);
        drop = 0;
    }

    return 0;
}
