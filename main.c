#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
        char ownerName[40];
        char carNo[40];
        char vehType[40];
        char vehColor[40];
        char contactNum[40];
        char entryTime[40];
        char tokenNumer[40];
}Car;

void WelcomePrint();
void EndingPrint();
void CarInfoEntry(char PassInfo[1000][20],int countPInfo);

Car car[100];

int main()
{
    time_t second ;
    int  startMinute , endMinute , count=0, elapsedMinute;
    char startMinStr[20];
    char endMinStr[20];
    char elapsedMinStr[20];
    char tokenNumStr[20];

    char words[20];
    char InfoList[1000][20];

    int carPosition[10][10];
    int i,j, tokenNumber;
    int payment;


    FILE *writeCarInfo;
    FILE *CarStatus;
    FILE *readCarInfo;

    char userName[20] = {"user"};
    char password[20] = {"pass"};

    char tempUserName[20];
    char tempPassword[20];

     printf("<<<  Enter User Name And Password >>>\n");

    konkhane:

    printf("Enter User Name : ");
    scanf("%s",&tempUserName);
    printf("Enter Password : ");
    scanf("%s",&tempPassword);

    if(((strcmp(userName,tempUserName) != 0)) && (strcmp(password,tempPassword) != 0))
    {
            printf("<< Invalid Entry >>\n\n");
            goto konkhane;
    }

    while(1)
    {
        WelcomePrint();

        printf("Vehicle Entry                           >>>  press 1\n");
        printf("Vehicle Exit                            >>>  press 2\n");
        printf("Current Parking Situation      \t\t>>>  press 3\n" );
        printf("ALL Parking Situation       \t\t>>>  press 4\n" );
        printf("To Exit                                 >>>  press 5\n");

        printf("<< Please Enter Valid Code >>\n");

        char choose;
        scanf("%c",&choose);

        system("cls");

        if(choose == '1')
        {
                printf("<< Welcome To The Car Parking Portion >>\n");

                writeCarInfo = fopen("CarInfoEntry.txt","a");
                CarStatus = fopen("CheckCarStatus.txt","a");

                int countInfo = 0,i;
                char c;

                second = time(NULL);
                startMinute = second/60;

                itoa(startMinute,startMinStr,10);

                for(i=0; (c = getchar())!=EOF;  i++)
                {
                        //owner name
                        printf("<< Enter Your Name >>\n");
                        gets(car[i].ownerName);
                        fputs("Name              :: ",writeCarInfo);
                        fputs(car[i].ownerName,writeCarInfo);
                        fputs("\n",writeCarInfo);
                        //fputs("\n",CarStatus);
                        fputs(car[i].ownerName,CarStatus);
                        fputs("\n",CarStatus);


                        //car number
                        printf("<< Enter Your Car Number >>\n");
                        gets(car[i].carNo);
                        fputs("Car Number       :: ",writeCarInfo);
                        fputs(car[i].carNo,writeCarInfo);
                        fputs("\n",writeCarInfo);
                        //fputs("\n",CarStatus);
                        fputs(car[i].carNo,CarStatus);
                        fputs("\n",CarStatus);


                        //Vehicle Type
                        printf("<< Enter Vehicle Type >>\n");
                        gets(car[i].vehType);
                        fputs("Vehicle Type     :: ",writeCarInfo);
                        fputs(car[i].vehType,writeCarInfo);
                        fputs("\n",writeCarInfo);
                        fputs(car[i].vehType,CarStatus);
                        fputs("\n",CarStatus);

                        //Vehicle Color
                        printf("<< Enter Vehicle Color >>\n");
                        gets(car[i].vehColor);
                        fputs("Vehicle Color     :: ",writeCarInfo);
                        fputs(car[i].vehColor,writeCarInfo);
                        fputs("\n",writeCarInfo);
                        fputs(car[i].vehColor,CarStatus);
                        fputs("\n",CarStatus);

                        //Contact Number
                        printf("<< Enter Contact Number >>\n");
                        gets(car[i].contactNum);
                        fputs("Contact Number     :: ",writeCarInfo);
                        fputs(car[i].contactNum,writeCarInfo);
                        fputs("\n",writeCarInfo);
                        fputs(car[i].contactNum,CarStatus);
                        fputs("\n",CarStatus);




                        //Time entry
                        fputs("Time              :: ",writeCarInfo);
                        fputs(startMinStr,writeCarInfo);
                        fputs("\n",writeCarInfo);
                        fputs(startMinStr,CarStatus);
                        fputs("\n",CarStatus);



                        count = 0;
                        readCarInfo = fopen("CheckCarStatus.txt","r");

                        for(i=0; fgets(words,sizeof(words),readCarInfo) != NULL; i++)
                        {
                            strcpy(InfoList[i],words);
                            count++;
                        }

                        CarInfoEntry(InfoList,count);

                        int temp,dec=0,unit=0;

                        for(i=0;i<count/7;i++)
                        {
                            temp = atoi(car[i].tokenNumer) - 1;
                            dec = temp / 10;
                            unit = temp % 10;
                            carPosition[dec][unit] = 1;
                        }

                        for(i=0;i<10;i++)
                        {
                            for(j=0;j<10;j++)
                            {
                                if(carPosition[i][j] == 0)
                                {
                                    tokenNumber = ((i*10) + j)+1;

                                    itoa(tokenNumber,tokenNumStr,10);
                                    carPosition[i][j] = 1;
                                    printf("Light is On at Position %d\n",tokenNumber);
                                    break;
                                }
                            }
                            break;
                        }

                        //Token  Number
                        printf("<< Vehicle Token Number  : %s\n",tokenNumStr);
                        fputs("Token Number     :: ",writeCarInfo);
                        fputs(tokenNumStr,writeCarInfo);
                        fputs("\n",writeCarInfo);
                        fputs(tokenNumStr,CarStatus);
                        fputs("\n",CarStatus);

                        here:
                        printf("<< Do You Want to Book Again , (Type n->no or y->yes) >>\n");
                        scanf("%c",&choose);

                        printf("%c",choose);

                        if(choose == 'n')
                        {
                            printf("%c",choose);
                            break;
                        }
                        else if(choose == 'y')
                        {
                            count++;
                            system("cls");
                        }
                        else
                        {
                            printf("<< Please Enter Valid Input >>\n");
                            goto here;
                        }
                }

                fclose(writeCarInfo);
                fclose(CarStatus);
                fclose(readCarInfo);
        }

        else if(choose == '2')
        {

                printf("<< Welcome To The Vehicle Exit Portion >>\n\n");

                printf("Enter your Token Number\n");
                scanf("%s",&tokenNumStr);

                count = 0;
                readCarInfo = fopen("CheckCarStatus.txt","r");

                for(i=0; fgets(words,sizeof(words),readCarInfo) != NULL; i++)
                {
                    strcpy(InfoList[i],words);
                    count++;
                }
                fclose(readCarInfo);

                CarInfoEntry(InfoList,count);

                second = time(NULL);
                endMinute = second/60;

                int index;

                for(i=0;i<count/7;i++)
                {
                    if(atoi(car[i].tokenNumer) == atoi(tokenNumStr))
                    {
                        elapsedMinute = endMinute - atoi(car[i].entryTime);


                        printf("<< Total Elapsed Time :   %d minute>>\n",elapsedMinute);


                        if(elapsedMinute > 180)
                        {
                                printf("<< You have crossed Maximum time limit of 180 minute >>\n");
                                printf("Total Cost    :   %d\n",(elapsedMinute*10));
                        }
                        else
                        {
                                printf("Total Cost    :   %d\n",(elapsedMinute*5));
                        }

                        printf("<< Please Pay First >>\n");
                        scanf("%d",&payment);
                        index = i;

                        break;
                    }
                }

                there:
                if(payment == (elapsedMinute*5))
                {
                        printf("<< Thank you >> \n");

                        int temp,dec=0,unit=0;
                        temp = atoi(car[index].tokenNumer) - 1;
                        dec = temp / 10;
                        unit = temp % 10;
                        carPosition[dec][unit] = 0;

                        strcpy(car[index].ownerName,"");
                        strcpy(car[index].carNo,"");
                        strcpy(car[index].contactNum,"");
                        strcpy(car[index].entryTime,"");
                        strcpy(car[index].tokenNumer,"");
                        strcpy(car[index].vehColor,"");
                        strcpy(car[index].vehType,"");

                        readCarInfo = fopen("CheckCarStatus.txt","w");

                        for(i=0;i<count/7;i++)
                        {
                            fputs(car[i].ownerName,readCarInfo);
                            fputs(car[i].carNo,readCarInfo);
                            fputs(car[i].vehType,readCarInfo);
                            fputs(car[i].vehColor,readCarInfo);
                            fputs(car[i].contactNum,readCarInfo);
                            fputs(car[i].entryTime,readCarInfo);
                            fputs(car[i].tokenNumer,readCarInfo);
                        }

                        fclose(readCarInfo);
                }
                else
                {
                        printf("<< Please Pay Full Payment >>\n");
                        scanf("%d",&payment);
                        goto there;
                }

                oikhane:
                printf("<< Press 1 to continue >>\n");
                scanf("%d",&i);

                if(i == 1)
                {
                    continue;
                }
                else
                {
                    goto oikhane;
                }
        }

        else if(choose == '3')
        {
                FILE *Endingtxt;
                Endingtxt = fopen("CheckCarStatus.txt","r");
                char EndChar;

                while((EndChar = fgetc(Endingtxt)) != EOF)
                {
                    printf("%c",EndChar);
                }
                printf("\n");

                seikhane:
                printf("<< Press 1 to continue >>\n");
                scanf("%d",&i);

                if(i == 1)
                {
                    continue;
                }
                else
                {
                    goto seikhane;
                }
        }

        else if(choose == '4')
        {
                FILE *Endingtxt;
                Endingtxt = fopen("CarInfoEntry.txt","r");
                char EndChar;

                while((EndChar = fgetc(Endingtxt)) != EOF)
                {
                    printf("%c",EndChar);
                }
                printf("\n");

                jeikhane:
                printf("<< Press 1 to continue >>\n");
                scanf("%d",&i);

                if(i == 1)
                {
                    continue;
                }
                else
                {
                    goto jeikhane;
                }
        }
        else if(choose == '5')
        {
            system("cls");
            break;
        }
    }

    EndingPrint();

    return 0;
}

void CarInfoEntry(char PassInfo[1000][20],int countPInfo)
{
    int i,j;

    j=0;
    for(i=0;i<countPInfo;i=i+7)
    {
        strcpy(car[j].ownerName,PassInfo[i]);
        //printf("%s",PassInfo[i]);
        j++;
    }

    j=0;
    for(i=1;i<countPInfo;i=i+7)
    {
        strcpy(car[j].carNo,PassInfo[i]);
        //printf("%s",PassInfo[i]);
        j++;
    }

    j=0;
    for(i=2;i<countPInfo;i=i+7)
    {
        strcpy(car[j].vehType,PassInfo[i]);
        //printf("%s",PassInfo[i]);
        j++;
    }

    j=0;
    for(i=3;i<countPInfo;i=i+7)
    {
        strcpy(car[j].vehColor,PassInfo[i]);
        //printf("%s",PassInfo[i]);
        j++;
    }

    j=0;
    for(i=4;i<countPInfo;i=i+7)
    {
        strcpy(car[j].contactNum,PassInfo[i]);
        //printf("%s",PassInfo[i]);
        j++;
    }

    j=0;
    for(i=5;i<countPInfo;i=i+7)
    {
        strcpy(car[j].entryTime,PassInfo[i]);
       // printf("%s",PassInfo[i]);
        j++;
    }

    j=0;
    for(i=6;i<countPInfo;i=i+7)
    {
        strcpy(car[j].tokenNumer,PassInfo[i]);
        //printf("%s",PassInfo[i]);
        j++;
    }

}

void WelcomePrint()
{
    FILE *welcometxt;
    welcometxt = fopen("welcome.txt","r");
    char WelcomeChar;

    while((WelcomeChar = fgetc(welcometxt)) != EOF)
    {
        printf("%c",WelcomeChar);
    }
    printf("\n");
    printf("\n");
}







void EndingPrint()
{
    FILE *Endingtxt;
    Endingtxt = fopen("Thanks.txt","r");
    char EndChar;

    while((EndChar = fgetc(Endingtxt)) != EOF)
    {
        printf("%c",EndChar);
    }
    printf("\n");
    printf("\n");
}
