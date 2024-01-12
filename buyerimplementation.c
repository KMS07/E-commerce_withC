#include "buyer.h"
#include <stdio.h>
#include <stdlib.h>

int numOfOrders = 0;
// int itemId, int sId,int quantity,char *buyerName
void makeOrder(float gst,int bid){
    FILE *fp,*fp1,*fp2;
    fp = fopen("cart.txt","r");
    fp1 = fopen("orders.txt","a");
    fp2 = fopen("data.txt","r");
    if (fp == NULL || fp1 == NULL) {
        printf("File opening failed.\n");
        return ;
    }

    // Skip the first line in orders file
    char buffer1[100];
    fgets(buffer1,sizeof(buffer1),fp1);

    int shkId, id,bId;
    char name[100];
    int itemquantity,quantityTaken;
    int price;
    // Read each record from the input file
    while (fscanf(fp, "%d %d %s %d %d", &bId, &id, name, &shkId, &quantityTaken) == 5 && fscanf()) {
        if (bid == bId) {
            deletefromcart(bid,id);
            fprintf(fp1, "%d %s %d %d %d\n", bid, name,id, quantityTaken,itemquantity - quantity , price);
        }   
    }
    // Creating the order
    // Find current date
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);        
    localTime = localtime(&currentTime);

    // Adding order to the file
    fprintf(fp1,"%s %d %d %d %d %d/%d/%d",buyerName,itemId,quantity,price*quantity,sId,localTime->tm_mday,localTime->tm_mon+1,localTime->tm_year+1900);
    printf("Order placed successfully");
    numOfOrders++;
}

int addBuyer(char *bname){
    // create new shopkeeper
    int randomId;
    // seed the random number generator
    srand(time(NULL));

    // Generate a random 3-digit number
    randomId = rand() % 900 + 100;

    FILE *fp = fopen("buyers.txt","a");
    fprintf(fp,"%d %s\n",randomId,bname);
    fclose(fp);

    return randomId;
}


int checkBuyer(int bid){
    FILE *fp = fopen("buyers.txt","r");
    int id;
    char bname[100];
    while(fscanf(fp,"%d %s",&id,bname) == 2){
        if(bid == id){
            return 1;
        }
    }
    return 0;
}

void deletefromcart(int buyerIdToDelete,int itemIdToDelete){
    FILE *file = fopen("cart.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    FILE *tempFile = fopen("temp_cart.txt", "w");

    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return 1;
    }


    int buyerId, itemId, shopkeeperId, quantityTaken;
    char itemName[100];

    // Read the content and write to the temporary file excluding the item to be deleted
    while (fscanf(file, "%d %d %s %d %d", &buyerId, &itemId, itemName, &shopkeeperId, &quantityTaken) == 5) {
        if (!(buyerId == buyerIdToDelete && itemId == itemIdToDelete)) {
            fprintf(tempFile, "%d %d %s %d %d\n", buyerId, itemId, itemName, shopkeeperId, quantityTaken);
        }
    }

    // Close both files
    fclose(file);
    fclose(tempFile);

    // Remove the original file
    remove("cart.txt");

    // Rename the temporary file to the original file
    if (rename("temp_cart.txt", "cart.txt") != 0) {
        perror("Error renaming file");
        return 1;
    }
}

void addtocart(int itemid,int sid,int bid,int quantityTaken){
    FILE *fp = fopen("cart.txt","a");
    FILE *fp1 = fopen("data.txt","r+");

    char buffer[100];
    // Skip the first line
    fgets(buffer,sizeof(buffer),fp1);

    int shkId, id;
    char name[100];
    int itemquantity;
    int price;

    // Read each record from the input file 
    while (fscanf(fp1, "%d %d %s %d %d", &shkId, &id, name, &itemquantity, &price) == 5) {
        if (shkId == sid && id == itemid) {
            if(quantityTaken > itemquantity){
                printf("Enter less than %d quantity",itemquantity);
            }else{
                fprintf(fp,"%d %d %s %d %d\n",bid,itemid,name,sid,quantityTaken); // add to the cart file
                break;
            }
        }   
    }
    printf("Added to cart successfully!!\n");
    fclose(fp);
}

void viewcart(int bid){
    FILE *fp = fopen("cart.txt","r");
    int buyerid,itemid,quantityTaken;
    char itemname[100];
    printf("Itemid name Selected quantity\n");
    while(fscanf(fp,"%d %d %s %*d %d\n",&buyerid,&itemid,itemname,&quantityTaken) == 4){
        if(bid == buyerid){
            printf("%d %s %d\n",itemid,itemname,quantityTaken);
        }
    }
    fclose(fp);
}