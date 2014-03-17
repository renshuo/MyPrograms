#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define DATA_LENGTH 32


char divisor[DATA_LENGTH+2];
char dividend[DATA_LENGTH+2];

char divResult[DATA_LENGTH+2];
int resultLen = 0;


void inputData(char* dataName, char* data){
  printf("input %s: ", dataName);
  int i=0;
  for (i=0; i<DATA_LENGTH; i++){
    scanf("%c", &data[i]);
    if (data[i]==10){
      i--;
    }
    if ((data[i]=='0') & (data[i-1]=='\\')){
      data[i-1]='\0';
      break;
    }
  }
  //reverseStr(data);
  printf("get data: %s\n", data);
  
}

void initArray(int a[], int alen){
  int i;
  for (i=0; i<alen; i++){
    a[i]=0;
  }
}
void printArray(char* name, int a[], int alen);
  

int borrow1(int result[], int resultlen, int currentBit){
  //printArray("borrow1: ", result, resultlen);
  if (currentBit==1){ //top
    return 0;
  }
  int upBitPoint = resultlen-currentBit+1;
  if (result[upBitPoint]>0){
      result[upBitPoint] = result[upBitPoint]-1;
      return 1;
  }else if (result[upBitPoint]==0){
    int upupBit = borrow1(result, resultlen, currentBit-1);
    if (upupBit==0){
      return 0;
    }else if (upupBit==1){
     result[upBitPoint]=9;
     return 1;
    }
  }else {
    return 0;
  }
}
int minus(int minuend[], int subtractor[], int result[], int mlen){
  int i=1;
  for (; i<=mlen; i++){
    int temp = minuend[mlen-i]-subtractor[mlen-i];
    //printArray("borrow: ", result, mlen);
    int borrowed = borrow1(result, mlen, i);
    //printf("br: %d \n" , borrowed);
    if (temp<0 & borrowed==1){
      result[mlen-i] = 10+temp;
    }else{
      result[mlen-i] = temp;
    }
  }
  return checkResultGreat0(result,mlen);
}



int checkResultGreat0(int result[], int len){
  int i=len-1;
  for (;i>=0;i--){
    if (result[i]<0){
      return 0;
    }
  }
  return 1;
}

void arrayCopy(int a[], int b[], int len){
  int i=0; 
  for (; i<len; i++){
    b[i]=a[i];
  }
}
void arraySubCopy(int a[], int start, int b[], int len){
    int i=0; 
  for (; i<len; i++){
    b[i]=a[start+i];
  }
}

void printArray(char* name, int a[], int len){
    int i=0; 
    printf("%s:", name);
  for (; i<len; i++){
    printf("%d,", a[i]);
  }
  printf("\n");
}

  
int mod(int a[], int alen, int b[]){
  int i=0;
  int result[alen];
  initArray(result, alen);
  //printArray("a", a, alen);
 // printArray("b", b, alen);
  while (minus(a,b,result,alen)){
   // printArray("minusResult:", a, alen);
    arrayCopy(result, a, alen);
    i++;
  }
  return i;
}

void movePoint(int t[], int len, int nextValue){
    int top = t[len-1];
    int i=len-1;
    for (; i>0; i--){
      t[i] = t[i-1];
    }
    t[0] = nextValue;
    t[len-1] = t[len-1]+top*10;
}
handle4s5r(){
  if (divResult[resultLen-1]>=53){
    divResult[resultLen-2]++;
  }
   divResult[resultLen-1]='\0';
}

void divData(int a[], int alen, int b[], int blen){
  int start = alen-blen;
  int temp[blen];
  initArray(temp, blen);
  arraySubCopy(a, start, temp, blen);
  while(start>=0){
    int mresult = mod(temp, blen, b);
    divResult[resultLen] = 48+mresult;
    resultLen++;
    start--;
    movePoint(temp, blen, a[start]);
  }
  handle4s5r();
}



int* str2intAry(char* data, int a[]){
    int len = strlen(data);
    int i=0;
    for (; i<len; i++){
      a[i] = data[i]-48;
    }
}
void add0atBegin(char* data, char* data1){
   int len = strlen(data);
   int i=0; 
   data1[0]=48;
   for (; i<len+1; i++){
     data1[i+1] = data[i];
   }
 }
 
 
void check0(char* ds){
    int i=0;
    while(ds[i]==48){
      i++;
    }
    if (ds[i]==0){
      printf("div 0.\n");
      exit(-1);
    }
}
  

main(char* args){
  inputData("dividend", dividend);
  int dlen = strlen(dividend)+1;
  char dividend0[dlen]; 
  add0atBegin(dividend, dividend0);
  inputData("divisor", divisor);
  check0(divisor);
  int rlen = strlen(divisor);
  int divd[dlen], divr[rlen];
  str2intAry(dividend0, divd);
  str2intAry(divisor, divr);
  divData(divd, dlen, divr, rlen);
  printf("result: %s", divResult);
 
  
}



