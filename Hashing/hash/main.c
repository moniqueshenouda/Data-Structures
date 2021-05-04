#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct {
int img_arr [784];
}image;
int collision=0;
typedef struct {
image data;
int key;
}data_item;

data_item hashtable[1000];

void initialize(){
    int i;
    for(i=0;i<1000;i++){
    hashtable[i].key=-1;}
}

int get(image img){
    int x=hashCode(img);

    int i,c=0,count=0;
while((count<=1000)){
        c=0;
        count++;
    for(i=0;i<784;i++){
    if(hashtable[x].data.img_arr[i]==img.img_arr[i]){
       c++;
        }

    }

if(c!=784){
    x++;
    if(x==1000)
        x=0;
    }

    }

    if(count>1000)
          return -1;

 else if(c==784){


return hashtable[x].key;}
}
void put (int id, image current_image){

int current;
current=hashCode(current_image);

if(hashtable[current].key==-1){
    hashtable[current].key=id;
    hashtable[current].data=current_image;

}
else{{
 while (hashtable[current].key!=-1){
        current++;
        collision++;
        if(current>1000)
            current=0;}

}
    hashtable[current].key=id;
    hashtable[current].data=current_image;

}

}
int removeImg( image img){
   int x=hashCode(img);
    int i,required,c=0,count=0;
while((c!=784)&&(x<=1000)&&(count<=1000)){
        c=0;
        count++;
    for(i=0;i<784;i++){
    if(hashtable[x].data.img_arr[i]==img.img_arr[i]){
       c++;
        }

    }

if(c!=784){
    x++;
    if(x==1000)
        x=0;
    }

    }

    if(count>1000)
          return -1;

 else if(c==784){
    required=hashtable[x].key;
    hashtable[x].key=-1;
}
return required;}

int hashCode(image img){
int i,j,a[28]={0},sum=0,c=0;

for(i=0;i<28;i++){
    for(j=0;j<28;j++){
        a[i]+=img.img_arr[c];
        c++;
    }

}

for(i=0;i<28;i++){
        a[i]=a[i]*(i+1);

}

for (i=0;i<28;i++){
    sum+=a[i];
}


return sum%1000;
}
int main()
{
    image image1 ,chimage;
    clock_t start,end;
    double time;
    int a[1000][28],b,i,j,id,choice,result;
    FILE *f;
    f=fopen("new.txt","r");
    initialize();
    start=clock();
    if(f!=NULL)
    {
        while(!feof(f))
        {

           for(i=0;i<784;i++){
           fscanf(f,"%d",&image1.img_arr[i]);

           }
           fscanf(f,"%d",&id);

           put(id,image1);

        }
    }
    fclose(f);
    end=clock();
    time=(double)(end-start)/CLOCKS_PER_SEC;
    printf("Collisions=%d\n",collision);
    printf("Time of insertion=%.3f\n",time);
printf("Select your path \n\n1-Search for image \n2-Delete image\n\nEnter your destination :");
scanf("%d",&choice);
switch(choice){
case 1:
    printf("\nEnter image:");
    for(i=0;i<784;i++){
    scanf("%d",&chimage.img_arr[i]);}

    result=get(chimage);

    if(result==-1)
        printf("Image not found");
    else printf("Image is found with ID:%d\n",result);

    break;
case 2:
     printf("\nEnter image:");for(i=0;i<784;i++){
    scanf("%d",&chimage.img_arr[i]);}
    result=removeImg(chimage);
    if(result==-1)
        printf("Image not found");
    else printf("Image is found with ID:%d and deleted",result);
    break;
    }

    return 0;
}
