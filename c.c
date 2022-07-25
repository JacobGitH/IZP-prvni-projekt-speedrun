#include <stdio.h>
#include <stdlib.h>

//checks if string contains [a-z][A-Z]
int funcLevel1(char arr[]){
    int upper = 0;
    int lower = 0;
    
    for (int i = 0; arr[i] != '\0'; i++){
        if((arr[i] >= 'a' && arr[i] <= 'z')){
            upper = 1;
        }else if((arr[i] >= 'A' && arr[i] <= 'Z')){
            lower = 1;
        }
    }
    if(upper > 0 && lower > 0){
        return 1;
    }else{
        return 0;
    }
}

//checks if string contains [a-z][A-Z][0-9]
int funcLevel2(char arr[], int param){
    int param1 = 0;
    int param2 = 0;
    int param3 = 0;
    int param4 = 0;

    for (int i = 0; arr[i] != '\0'; i++)
    {
        if(arr[i] >= 'a' && arr[i] <= 'z')
            param1 = 1;
        if(arr[i] >= 'A' && arr[i] <= 'Z')
            param2 = 1;
        if(arr[i] >= 48 && arr[i] <= 57)
            param3 = 1;
        if ((arr[i] >= 32 && arr[i]<= 47)  || (arr[i] >=58 && arr[i] <= 64) || (arr[i] >=91 && arr[i] <= 96) || (arr[i] >= 123 && arr[i] <= 126))
            param4 = 1;    
    }

    if(param1 + param2 + param3 + param4 == 4 && param > 4){
        return 1;
    }else if(param1 + param2 + param3 + param4 >= param && param <=4) {
        return 1;
    }else{
        return 0;
    }
    
}

//repeatability
int funcLevel3(char arr[], int param){
    int repeatingLetter = 0;
    for (int i = 0; arr[i] != '\0'; i++)
    { 

        if(repeatingLetter >= param - 1){
            return 0;
        }
        
        if(arr[i] == arr[i + 1]){
            repeatingLetter++;
        }else{
            repeatingLetter = 0;
        }
        
    }
    return 1;
}

int funcLevel4(char arr[], int param){
  char pol[100][100];
  int numOfSubs = 0;
  

  // count of substrings
  for (int i = 0; arr[i] != '\0'; i++)
  {
    numOfSubs++;
    for (int j = 0; j < param; j++)
    {
      pol[i][j] = arr[i + j];
    }
  }


  for (int i = 0; i < numOfSubs - param + 1; i++)
  {
    int totalSameSubs = 0;
    for (int j = 0; j < numOfSubs - param +1; j++)
    {
    if(totalSameSubs > 1){
      return 0;
    }
      int sameSub = 0;
      for (int k = 0; k < param; k++)
      {
        if(pol[i][k] == pol[j][k]){
          sameSub++; 
       }
       if(sameSub == param)
        totalSameSubs++; 
      }
    }
    
  }

  return 1;
}

//check if the strings are the same
int statsCheck(char buffer[]){
    char realStats[20] = "--stats";

    for (int i = 0; buffer[i] != '\0'; i++)
    {
        if(buffer[i] != realStats[i]){
            return 0;
        }
    }
    return 1;
}
// random ass counter i made like 6 minutes before deadline
int counter(char arr[]){
    int num = 0;
    for (int i = 0; arr[i] != '\0'; i++)
    {
        num++;
    }
    return num;
}

//checks form strings maximum
int maxHesla(char arr[]){
    int theNum = 0;
    for (int i = 0; arr[i] != '\0'; i++){
        theNum++;
    }
    
    if (theNum > 100)
    {
        return 0;
    }else{
        return 1;
    }
}


int main(int argc, char *argv[]){
   
    //checks for right amount of arguments
    if(argc < 3 || argc > 4){
        fprintf(stderr, "Prilis mnoho nebo prilis malo argumentu \n");
        return EXIT_FAILURE;
    }

    //argv to int
    char *p;
    const int LEVEL = strtoul(argv[1], &p, 10);
    if (p[0] != '\0')
    {
        fprintf(stderr, "Level byl spatne zadan");
        return EXIT_FAILURE;
    }

    const int PARAM = strtoul(argv[2], &p, 10);
    if (p[0] != '\0')
    {
        fprintf(stderr, "Argument byl spatne zadan");
        return EXIT_FAILURE;
    }
    

    //stats
    if(argc == 4){
        if(!statsCheck(argv[3])){
            fprintf(stderr, "Argument pro stats byl zadan spatne. Pro zobrazeni stats zadejte: --stats");
            return EXIT_FAILURE;
        }
    }

    
    //input checkup
    if(LEVEL < 1 || LEVEL > 4){
        fprintf(stderr, "Zadany level neodpovida zadani \n");
        return EXIT_FAILURE;
    }
    
    if(PARAM < 1){
        fprintf(stderr, "Zadany parametr neodpovida zadani \n");
        return EXIT_FAILURE;
    }

    //buffer
    char buffer[150];
    int minZnaku = 1001;
    int pocetZnaku = 0;
    int pocetHesel = 0;
    
    // promena pro vypocet kolik je ruznych zanku
    int nZnak[128] = {0};

    while(fgets(buffer, 150, stdin) != NULL){

        //number of pwd, min amount of chars, maping of n number of chars
        if(counter(buffer) < minZnaku)
            minZnaku = counter(buffer);

        pocetHesel++;
        pocetZnaku = pocetZnaku + counter(buffer) -1;
        
        for (int i = 0; i < counter(buffer); i++)
        {
            nZnak[(int)buffer[i]] = 1;
        }
        //pwd max check
        if(!maxHesla(buffer)){
            fprintf(stderr, "Heslo prilis dlouhe \n");
            return EXIT_FAILURE;
        }
        
        //validation
        if(LEVEL == 1 && maxHesla(buffer) && funcLevel1(buffer)){
                    printf("%s", buffer);
        }else if(LEVEL == 2 && maxHesla(buffer) && funcLevel1(buffer) && funcLevel2(buffer, PARAM)){
                        printf("%s", buffer);
        }else if(LEVEL == 3 && maxHesla(buffer) && funcLevel1(buffer) && funcLevel2(buffer, PARAM) && funcLevel3(buffer, PARAM)){
                            printf("%s", buffer);
        }else if(LEVEL == 4 && maxHesla(buffer) && funcLevel1(buffer) && funcLevel2(buffer, PARAM) && funcLevel3(buffer, PARAM)
        && funcLevel3(buffer, PARAM) && funcLevel4(buffer, PARAM)){
                                printf("%s", buffer);
        }
    }
    // check for char duplication
    int finnalCislo = 0;
    for (int i = 0; i < 128; i++)
    {
        finnalCislo += nZnak[i];
    }
    //stats 
    float avgZnaku = (float)pocetZnaku / (float)pocetHesel;
    if(argc == 4){
        if(statsCheck(argv[3])){
            printf("Statistika:\n");
            printf("Ruznych znaku: %d\n", finnalCislo - 1);
            printf("Minimalni delka: %d\n", minZnaku - 1);
            printf("Prumerna delka: %.1f\n", avgZnaku);
        }
    }
    
}