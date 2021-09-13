#include<stdio.h>
#include<math.h>
#include<string.h>

struct details
{
    char name[25];
    char profession[50];
    double phoneno;
    int deets[7];
    int id;
    int pref[6];
    float compat;

}user, user1, userArr[200], userArr2[200], shortlisted[200], temp;

int main()
{
    char yesno;
    int age, count, registerID, f=0;

    FILE *ptr;
    FILE *ptr1;
    
    // Initializing 1 in Final_ID.dat for first user entry
    // user.id=0;                                      
    // ptr1 = fopen("Final_ID.dat","w");
    // fwrite(&user.id,sizeof(user.id),1,ptr1);
    // fclose(ptr1);

    ptr1 = fopen("Final_ID.dat","r");                   //fetching the previous ID
    fread(&count,sizeof(count),1,ptr1);
    count++;
    fclose(ptr1);

    start:
    printf("\nWELCOME TO DJS MATRIMONY \nAre you a registered user?(y/n)\n");
    scanf("%c",&yesno);
    if(yesno=='y')
    {
        enterID:
        printf("\nEnter your ID: ");
        scanf("%d", &registerID);
        ptr = fopen("details.txt","r");
        while(fread(&user,sizeof(struct details),1,ptr)==1)             //iterating through all previously existing users
        {
            if(registerID < 1 || registerID >= count)
            {
                printf("\nInvalid ID. Please enter your ID again: ");     //No user found of the given input ID
                fclose(ptr);
                goto enterID;
            }
            if(registerID == user.id)                                       //Skipping the enter details section
            {
                printf("\nWelcome back %s!\n", user.name);
                fclose(ptr);
                goto reg_user;
            }
        }
    }
    else if (yesno!='n')
    {
        getchar();
        printf("Invalid value, enter your choice again.\n");
        goto start;
    }
    else
    {
        printf("\n**** Enter your details ****\n ");

        // ptr = fopen("details.txt","a");
        user.id = count;
        printf("\nUser ID = %d", user.id);

        ptr1 = fopen("Final_ID.dat","w");
        fwrite(&user.id,sizeof(user.id),1,ptr1);
        fclose(ptr1);

        printf("\nEnter your name: ");
        getchar();
        gets(user.name);
        printf("\nEnter your age: ");
        scanf("%d", &age);
        user.deets[6] = age;
        if (age<18)
        {
            printf("\nYou are not eligible. Thank You, come back in %d years ;)", 18-age);
            goto end;
        }
        else
        {
            if (age<25)
            {
                user.deets[0]=1;
            }
            else if (age<32)
            {
                user.deets[0]=2;
            }
            else if (age<40)
            {
                user.deets[0]=3;
            }
            else if (age<49)
            {
                user.deets[0]=4;
            }
            else if (age<59)
            {
                user.deets[0]=5;
            }
            else if (age<69)
            {
                user.deets[0]=6;
            }
            else if (age>=69)
            {
                user.deets[0]=7;
            }
        }

        sex:
        printf("\nEnter your sex: \n1. Male\n2. Female\n3. Other\nEnter the number corresponding to your choice: ");
        scanf("%d",&user.deets[1]);
        if (user.deets[1]!=1 && user.deets[1]!=2 && user.deets[1]!=3)
        {
            printf("Invalid value, enter your choice again.");
            goto sex; 
        }
      
        phoneno:
        printf("\nEnter your phone no.: ");
        scanf("%lf", &user.phoneno);
        if(pow(10,9)>user.phoneno || pow(10,10)<=user.phoneno)
        {
            printf("Invalid value, enter your number again.");
            goto phoneno;
        }

        printf("\nWhat's your profession?\n");
        getchar();
        gets(user.profession);

        sex_orient:
        printf("\nWhat's your sexual orientation?\n1. Straight\n2. Gay\n3. Lesbian\n4. Bisexual\nEnter the number corresponding to your choice: ");
        scanf("%d", &user.deets[2]);
        if (user.deets[2]!=1 && user.deets[2]!=2 && user.deets[2]!=3 && user.deets[2]!=3 && user.deets[2]!=4)
        {
            printf("Invalid value, enter your choice again.");
            goto sex_orient; 
        }

        vert:
        printf("\nWhat best describes you? : \n1. Introvert\n2. Extrovert\n3. Ambivert\nEnter the number corresponding to your choice: ");
        scanf("%d", &user.deets[3]);
        if (user.deets[3]!=1 && user.deets[3]!=2 && user.deets[3]!=3)
        {
            printf("Invalid value, enter your choice again.");
            goto vert; 
        }

        pet:
        printf("\nDo you have a pet/pets? \n1. Yes \n2. No\nEnter the number  corresponding to your choice: ");
        scanf("%d",&user.deets[4]);
        if (user.deets[4]!=1 && user.deets[4]!=2)
        {
            printf("Invalid value, enter your choice again.");
            goto pet; 
        }

        date:
        printf("\nWhich is the closest to your idea of a perfect date? \n1. Spending an evening at a beach.\n2. Watching a movie at a theatre.\n3. Having brunch at a restaurant.\n4. Playing games at an arcade.\n5. Spending a day at an amusement park.\n6. Going on a trek.\nEnter the number corresponding to your choice: ");
        scanf("%d",&user.deets[5]);
        if (user.deets[5]!=1 && user.deets[5]!=2 && user.deets[5]!=3 && user.deets[5]!=4 && user.deets[5]!=5 && user.deets[5]!=6 )
        {
            printf("Invalid value, enter your choice again.");
            goto date; 
        }
      
        ptr = fopen("details.txt","a");
        fwrite(&user,sizeof(struct details),1,ptr);
        fclose(ptr);
    } //Details

    reg_user :
    printf("\n\n**** Enter your preferences for a partner ****\n");

    pref_age:
    printf("\nWhat is your preferred age group for a partner?\n1. 18-24\n2. 25-31\n3. 32-39\n4. 40-48\n5. 49-58\n6. 59-69\n7. 69+\nEnter the number corresponding to your choice : ");
    scanf("%d",&user.pref[0]);
    if (user.pref[0]<1 || user.pref[0]>7)
    {
        printf("Invalid value, enter your choice again.");
        goto pref_age;
    }
    user.pref[1] = user.deets[1];  //copying sex
    user.pref[2] = user.deets[2];  //copying sexual orientation
    pref_vert:
    printf("\nDo you want your partner to be an introvert, extrovert or an ambivert?\n1. Introvert\n2. Extrovert\n3. Ambivert\nEnter the number corresponding to your choice : ");
    scanf("%d",&user.pref[3]);
    if (user.pref[3]<1 || user.pref[3]>3)
    {
        printf("Invalid value, enter your choice again.");
        goto pref_vert;
    }
    pref_pet:
    printf("\nAre you comfortable with your partner having a pet?\n1. Yes\n2. No\nEnter the number corresponding to your choice : ");
    scanf("%d", &user.pref[4]);
    if (user.pref[4]!=1 && user.pref[4]!=2)
    {
        printf("Invalid value, enter your choice again.");
        goto pref_pet;
    }
    user.pref[5] = user.deets[5];  //copying perfect date

    //object retrieving
    ptr = fopen("details.txt","r");

    int k = 0, i = 1;
    while(i<count)
    {
        fread(&userArr2[i-1],sizeof(struct details),1,ptr);
        if (user.id != userArr2[i-1].id)
        {
            userArr[k] = userArr2[i-1];
            k++;
        }
        i++;
    }
    fclose(ptr);

    i=1;
    int c = 0;
    while(i<count)
    {
        if(user.pref[0]==userArr[i-1].deets[0])  //age
        {
            if(user.pref[1]==1)  //male
            {
                if(user.pref[2]==1)  //straight
                {
                    if(userArr[i-1].deets[1]==2 && (userArr[i-1].deets[2]==1 || userArr[i-1].deets[2]==4) ) 
                    {
                        shortlisted[c] = userArr[i-1];
                        c++;
                    }   
                }
                else if(user.pref[2]==2)  //gay
                {
                    if(userArr[i-1].deets[1]==1 && (userArr[i-1].deets[2]==2 || userArr[i-1].deets[2]==4) ) 
                    {
                        shortlisted[c] = userArr[i-1];
                        c++;
                    }
                }
                else  //bisexual
                {
                    if((userArr[i-1].deets[1]==1 && (userArr[i-1].deets[2]==2 || userArr[i-1].deets[2]==4)) || (userArr[i-1].deets[1]==2 && (userArr[i-1].deets[2]==1 || userArr[i-1].deets[2]==4)) ) 
                    {
                        shortlisted[c] = userArr[i-1];
                        c++;
                    }
                }  
            }

            else if(user.pref[1]==2)  //female
            {
                if(user.pref[2]==1)  //straight
                {
                    if(userArr[i-1].deets[1]==1 && (userArr[i-1].deets[2]==1 || userArr[i-1].deets[2]==4) ) 
                    {
                        shortlisted[c] = userArr[i-1];
                        c++;
                    }   
                }
                else if(user.pref[2]==3)  //lesbian
                {
                    if(userArr[i-1].deets[1]==2 && (userArr[i-1].deets[2]==3 || userArr[i-1].deets[2]==4) ) 
                    {
                        shortlisted[c] = userArr[i-1];
                        c++;
                    }
                }
                else  //bisexual
                {
                    if((userArr[i-1].deets[1]==1 && (userArr[i-1].deets[2]==1 || userArr[i-1].deets[2]==4)) || (userArr[i-1].deets[1]==2 && (userArr[i-1].deets[2]==3 || userArr[i-1].deets[2]==4)) ) 
                    {
                        shortlisted[c] = userArr[i-1];
                        c++;
                    }
                }
            }

            else  //other
            {
                if(user.pref[2]==1)  //straight
                {
                    if(userArr[i-1].deets[1]==3 && (userArr[i-1].deets[2]==1 || userArr[i-1].deets[2]==4) ) 
                    {
                        shortlisted[c] = userArr[i-1];
                        c++;
                    }   
                }
                else if(user.pref[2]==2)  //gay
                {
                    if(userArr[i-1].deets[1]==3 && (userArr[i-1].deets[2]==2 || userArr[i-1].deets[2]==4) ) 
                    {
                        shortlisted[c] = userArr[i-1];
                        c++;
                    }
                }
                else if(user.pref[2]==3)  //lesbian
                {
                    if(userArr[i-1].deets[1]==3 && (userArr[i-1].deets[2]==3 || userArr[i-1].deets[2]==4) ) 
                    {
                        shortlisted[c] = userArr[i-1];
                        c++;
                    }
                }
                else  //bisexual
                {
                    if(userArr[i-1].deets[1]==3 && (userArr[i-1].deets[2]==1 || userArr[i-1].deets[2]==2 || userArr[i-1].deets[2]==3 || userArr[i-1].deets[2]==4))
                    {
                        shortlisted[c] = userArr[i-1];
                        c++;
                    }
                }
            }
        }
        i++;
    }
    if(c==0)
    {
        printf("\nSorry! No matches found.");
        goto end;
    }
     
    i=0;
    while(i<c)
    {
        float num = 0;
        for(int j=3; j<=5; j++)
        {
            if(user.pref[j]==shortlisted[i].deets[j])
                num++;
        }
        shortlisted[i].compat = num*100/3;
        i++;
    }

    i=0;
    for(i = 0; i<c; i++)  
    {  
        for(int j = i+1; j<c; j++)  
        {  
            if(shortlisted[j].compat > shortlisted[i].compat)  
            {  
                temp = shortlisted[i];  
                shortlisted[i] = shortlisted[j];  
                shortlisted[j] = temp;   
            }   
        }   
    }   

    more_prof:
    printf("\n\n**** Following are the profiles sorted in the order of their compatibility with your profile :)  ****\n");
    i=0;
    char yn;
    int choice;
    
    printf("\nUSER ID\t\tNAME\t\tAGE\t\tCOMPATIBILITY\n");
    while(i<c)
    {
        printf("\n%d\t\t%s\t\t%d\t\t%0.3f %%", shortlisted[i].id, shortlisted[i].name, shortlisted[i].deets[6], shortlisted[i].compat);
        i++;
    }
    invalid1:
    printf("\n\nDo you want to view any profile? (y/n) : ");
    getchar();
    scanf("%c",&yn);
    if(yn=='y')
    {
        printf("\nEnter ID of the profile of your choice for more details: ");
        scanf("%d",&choice);

        i=0;
        while(choice!=shortlisted[i].id)
        {
            i++;
        }
        char sex[10];
        if(shortlisted[i].deets[1] == 1)
            strcpy(sex, "Male");
        else if(shortlisted[i].deets[1] == 2)
            strcpy(sex, "Female");
        else
            strcpy(sex, "Other");
        
        printf("\nID: %d\nName: %s\nAge: %d\nSex: %s\nPhone no.: %0.0lf\nProfession: %s\n",shortlisted[i].id, shortlisted[i].name, shortlisted[i].deets[6], sex, shortlisted[i].phoneno, shortlisted[i].profession );
        invalid:
        printf("\n\nDo you want to see the details from more profiles? (y/n) : ");
        getchar();
        scanf("%c",&yn);
        if(yn=='y')
        {   
            goto more_prof;
        }
        else if(yn!='n')
        {
            printf("\nInvalid value, enter again : ");
            goto invalid;
        }
    }
    else if(yn!='n')
    {
        printf("\nInvalid value, enter again : ");
        goto invalid1;
    }
    printf("\n\n**** THANK YOU FOR USING OUR PROGRAM, HOPE YOU FOUND YOUR MATCH <3 ****");
    end:
    return 0;
}