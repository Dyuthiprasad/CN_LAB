#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char rem[50], a[50], s[50], c, msj[50], gen[30];
    int i, genlen, t, j, flag = 0, k, n;

    printf("Enter the generator polynomial: ");
    gets(gen);

    printf("Generator polynomial is CRC-CCITT: %s\n", gen);
    genlen = strlen(gen);
    k = genlen - 1;

    printf("Enter the message bits: ");
    n = 0;
    while ((c = getchar()) != '\n' && c != EOF)
        msj[n++] = c;
    msj[n] = '\0';

    // Append k zeros to message
    strcpy(a, msj);
    for (i = 0; i < k; i++)
        a[n + i] = '0';
    a[n + k] = '\0';

    printf("\nMessage polynomial appended with zeros:\n");
    puts(a);

    // Division (Sender side)
    for (i = 0; i < n; i++) {
        if (a[i] == '1') {
            t = i;
            for (j = 0; j <= k; j++) {
                a[t] = (a[t] == gen[j]) ? '0' : '1';
                t++;
            }
        }
    }

    // Remainder
    for (i = 0; i < k; i++)
        rem[i] = a[n + i];
    rem[k] = '\0';

    printf("The checksum (CRC) is: ");
    puts(rem);

    // Append checksum to original message
    strcpy(a, msj);
    strcat(a, rem);
    printf("\nTransmitted codeword:\n");
    puts(a);

    // Receiver side
    printf("\nEnter the received message: ");
    n = 0;
    while ((c = getchar()) != '\n' && c != EOF)
        s[n++] = c;
    s[n] = '\0';

    for (i = 0; i < n - k; i++) {
        if (s[i] == '1') {
            t = i;
            for (j = 0; j <= k; j++) {
                s[t] = (s[t] == gen[j]) ? '0' : '1';
                t++;
            }
        }
    }

    // Check remainder
    flag = 0;
    for (i = n - k; i < n; i++) {
        if (s[i] == '1') {
            flag = 1;
            break;
        }
    }

    if (flag == 0)
        printf("\nReceived polynomial is error-free.\n");
    else
        printf("\nReceived polynomial contains error.\n");

    return 0;
}
