#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SIS_ID
{
    int PID;
} SID;

struct Student
{
    int rollno;
    char name[30];
    char clas[20];
    char city[20];
} st, stt;

// Function declarations
void addStudent();
void showStudent();
int autoid();
void modifyStudent();
void deleteStudent();
void showRecycle();
void recycleRecover();
void searchStudent();

// ---------------- MAIN ----------------
int main()
{
    char c;

    while (1)
    {
        system("cls"); // use "clear" for Linux

        printf("===== Student Information System =====\n\n");
        printf("1. Add Student\n2. Show Student\n");
        printf("3. Modify Student\n4. Delete Student\n");
        printf("5. Show Recycle Bin\n6. Recover Recycle Bin\n");
        printf("7. Search Student\n8. Exit\n");

        printf("\nEnter Choice: ");
        scanf(" %c", &c);

        switch (c)
        {
        case '1': addStudent(); break;
        case '2': showStudent(); break;
        case '3': modifyStudent(); break;
        case '4': deleteStudent(); break;
        case '5': showRecycle(); break;
        case '6': recycleRecover(); break;
        case '7': searchStudent(); break;
        case '8': exit(0);
        default: printf("Invalid choice!\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }
}

// ---------------- AUTO ID ----------------
int autoid()
{
    FILE *fp;
    int m = 1000;

    fp = fopen("SIS_ID.bin", "a+");
    if (fp == NULL)
        return m + 1;

    while (fread(&SID, sizeof(SID), 1, fp))
    {
        if (SID.PID > m)
            m = SID.PID;
    }

    fclose(fp);
    return m + 1;
}

// ---------------- ADD ----------------
void addStudent()
{
    FILE *fp, *fp1;
    char c;

    printf("\n--- Add Student ---\n");

    st.rollno = autoid();
    SID.PID = st.rollno;

    printf("Roll No: %d\n", st.rollno);

    printf("Enter Name: ");
    scanf(" %[^\n]", st.name);

    printf("Enter Class: ");
    scanf(" %[^\n]", st.clas);

    printf("Enter City: ");
    scanf(" %[^\n]", st.city);

    printf("\nSave Record? (1 = Yes): ");
    scanf(" %c", &c);

    if (c == '1')
    {
        fp = fopen("SIS.bin", "ab");
        fp1 = fopen("SIS_ID.bin", "ab");

        if (fp == NULL || fp1 == NULL)
        {
            printf("File Error!\n");
            return;
        }

        fwrite(&st, sizeof(st), 1, fp);
        fwrite(&SID, sizeof(SID), 1, fp1);

        fclose(fp);
        fclose(fp1);

        printf("Student Added Successfully!\n");
    }
}

// ---------------- SHOW ----------------
void showStudent()
{
    FILE *fp;
    int found = 0;

    fp = fopen("SIS.bin", "rb");
    if (fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&st, sizeof(st), 1, fp))
    {
        printf("%d | %s | %s | %s\n", st.rollno, st.name, st.clas, st.city);
        found = 1;
    }

    if (!found)
        printf("No Data Found!\n");

    fclose(fp);
}

// ---------------- SEARCH ----------------
void searchStudent()
{
    FILE *fp;
    int id, found = 0;

    printf("\nEnter Roll No: ");
    scanf("%d", &id);

    fp = fopen("SIS.bin", "rb");
    if (fp == NULL)
    {
        printf("No Records!\n");
        return;
    }

    while (fread(&st, sizeof(st), 1, fp))
    {
        if (st.rollno == id)
        {
            printf("Found: %d | %s | %s | %s\n", st.rollno, st.name, st.clas, st.city);
            found = 1;
        }
    }

    if (!found)
        printf("Not Found!\n");

    fclose(fp);
}

// ---------------- MODIFY ----------------
void modifyStudent()
{
    FILE *fp, *temp;
    int id, found = 0;

    printf("\nEnter Roll No to Modify: ");
    scanf("%d", &id);

    fp = fopen("SIS.bin", "rb");
    temp = fopen("temp.bin", "wb");

    while (fread(&st, sizeof(st), 1, fp))
    {
        if (st.rollno == id)
        {
            found = 1;

            printf("Enter New Name: ");
            scanf(" %[^\n]", st.name);

            printf("Enter New Class: ");
            scanf(" %[^\n]", st.clas);

            printf("Enter New City: ");
            scanf(" %[^\n]", st.city);
        }

        fwrite(&st, sizeof(st), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("SIS.bin");
    rename("temp.bin", "SIS.bin");

    if (found)
        printf("Record Updated!\n");
    else
        printf("Record Not Found!\n");
}

// ---------------- DELETE ----------------
void deleteStudent()
{
    FILE *fp, *temp, *rec;
    int id, found = 0;

    printf("\nEnter Roll No to Delete: ");
    scanf("%d", &id);

    fp = fopen("SIS.bin", "rb");
    temp = fopen("temp.bin", "wb");
    rec = fopen("SIS_REC.bin", "ab");

    while (fread(&st, sizeof(st), 1, fp))
    {
        if (st.rollno == id)
        {
            found = 1;
            fwrite(&st, sizeof(st), 1, rec); // move to recycle
        }
        else
        {
            fwrite(&st, sizeof(st), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);
    fclose(rec);

    remove("SIS.bin");
    rename("temp.bin", "SIS.bin");

    if (found)
        printf("Deleted (Moved to Recycle Bin)\n");
    else
        printf("Record Not Found!\n");
}

// ---------------- SHOW RECYCLE ----------------
void showRecycle()
{
    FILE *fp;
    int found = 0;

    fp = fopen("SIS_REC.bin", "rb");

    if (fp == NULL)
    {
        printf("Recycle Bin Empty!\n");
        return;
    }

    printf("\n--- Recycle Bin ---\n");

    while (fread(&st, sizeof(st), 1, fp))
    {
        printf("%d | %s | %s | %s\n", st.rollno, st.name, st.clas, st.city);
        found = 1;
    }

    if (!found)
        printf("Empty!\n");

    fclose(fp);
}

// ---------------- RECOVER ----------------
void recycleRecover()
{
    FILE *fp, *rec;
    int id, found = 0;

    printf("\nEnter Roll No to Recover: ");
    scanf("%d", &id);

    fp = fopen("SIS.bin", "ab");
    rec = fopen("SIS_REC.bin", "rb");

    if (rec == NULL)
    {
        printf("Recycle Bin Empty!\n");
        return;
    }

    while (fread(&st, sizeof(st), 1, rec))
    {
        if (st.rollno == id)
        {
            fwrite(&st, sizeof(st), 1, fp);
            found = 1;
        }
    }

    fclose(fp);
    fclose(rec);

    if (found)
        printf("Recovered Successfully!\n");
    else
        printf("Record Not Found in Recycle Bin!\n");
}
