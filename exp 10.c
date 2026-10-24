#include <stdio.h>
#include <stdlib.h>
struct Product {
    int id;
    float price;
    int quantity;
};
int main() {
    FILE *fp, *temp;
    struct Product p;
    int choice, id, found;
    do {
        printf("\n--- TEXT FILE MENU ---\n");
        printf("1. Write Records\n");
        printf("2. Read Records\n");
        printf("3. Append Record\n");
        printf("4. Search Record\n");
        printf("5. Delete Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            fp = fopen("product.txt", "w");
            if (fp == NULL) {
                printf("Error opening file!\n");
                break;
            }
            printf("Enter Product ID, Price, Quantity\n");
            printf("Enter ID 0 to stop.\n");
            while (1) {
                printf("Enter ID: ");
                scanf("%d", &p.id);

                if (p.id == 0)
                    break;

                printf("Enter Price and Quantity: ");
                scanf("%f%d", &p.price, &p.quantity);

                fprintf(fp, "%d %.2f %d\n",p.id, p.price, p.quantity);
            }
            fclose(fp);
            printf("Records written successfully.\n");
            break;
        case 2:
            fp = fopen("product.txt", "r");
            if (fp == NULL) {
                printf("File not found!\n");
                break;
            }
            printf("\nID\tPrice\tQuantity\n");

            while (fscanf(fp, "%d%f%d",&p.id, &p.price,&p.quantity) == 3) {
                printf("%d\t%.2f\t%d\n",p.id, p.price, p.quantity);
            }
            fclose(fp);
            break;
        case 3:
            fp = fopen("product.txt", "a");
            if (fp == NULL) {
                printf("Error opening file!\n");
                break;
            }
            printf("Enter Product ID, Price, Quantity: ");
            scanf("%d%f%d", &p.id, &p.price, &p.quantity);
            fprintf(fp, "%d %.2f %d\n",
                    p.id, p.price, p.quantity);
            fclose(fp);
            printf("Record appended successfully.\n");
            break;
        case 4:
            fp = fopen("product.txt", "r");
            if (fp == NULL) {
                printf("File not found!\n");
                break;
            }
            printf("Enter Product ID to search: ");
            scanf("%d", &id);
            found = 0;
            while (fscanf(fp, "%d%f%d",
                          &p.id, &p.price,
                          &p.quantity) == 3) {
                if (p.id == id) {
                    printf("Record Found!\n");
                    printf("ID: %d, Price: %.2f, Quantity: %d\n",
                           p.id, p.price, p.quantity);
                    found = 1;
                    break;
                }
            }
            if (!found)
                printf("Product not found.\n");

            fclose(fp);
            break;
        case 5:
            fp = fopen("product.txt", "r");
            if (fp == NULL) {
                printf("File not found!\n");
                break;
            }
            temp = fopen("temp.txt", "w");
            if (temp == NULL) {
                printf("Error creating temporary file!\n");
                fclose(fp);
                break;
            }
            printf("Enter Product ID to delete: ");
            scanf("%d", &id);
            found = 0;
            while (fscanf(fp, "%d%f%d",
                          &p.id, &p.price,
                          &p.quantity) == 3) {
                if (p.id == id) {
                    found = 1;
                } else {
                    fprintf(temp, "%d %.2f %d\n",
                            p.id, p.price, p.quantity);
                }
            }
            fclose(fp);
            fclose(temp);
            if (found) {
                if (remove("product.txt") == 0 &&
                    rename("temp.txt", "product.txt") == 0)
                    printf("Record deleted successfully.\n");
                else
                    printf("Error replacing file.\n");
            } else {
                remove("temp.txt");
                printf("Product not found.\n");
            }
            break;

        case 6:
            printf("Exiting program.\n");
            break;

        default:
            printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}
