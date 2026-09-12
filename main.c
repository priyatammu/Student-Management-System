#include <stdio.h>
#include <string.h>

struct Student
{
    int id;
    char name[50];
    int age;
    float marks;
};

// Save all students to file
void saveStudents(struct Student students[], int count)
{
    FILE *file = fopen("students.txt", "w");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d|%s|%d|%.2f\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].marks);
    }

    fclose(file);
}

// Load students from file
int loadStudents(struct Student students[])
{
    FILE *file = fopen("students.txt", "r");
    int count = 0;

    if (file == NULL)
    {
        return 0;
    }

    while (fscanf(file, "%d|%49[^|]|%d|%f\n",
                  &students[count].id,
                  students[count].name,
                  &students[count].age,
                  &students[count].marks) == 4)
    {
        count++;

        if (count >= 100)
        {
            break;
        }
    }

    fclose(file);

    return count;
}

// Calculate grade
char calculateGrade(float marks)
{
    if (marks >= 90)
        return 'A';
    else if (marks >= 80)
        return 'B';
    else if (marks >= 70)
        return 'C';
    else if (marks >= 60)
        return 'D';
    else
        return 'F';
}

int main()
{
    struct Student students[100];

    int count = loadStudents(students);
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("       STUDENT MANAGEMENT SYSTEM\n");
        printf("========================================\n");

        printf("\n1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("7. Student Results\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        // ADD STUDENT
        if (choice == 1)
        {
            if (count < 100)
            {
                int newID;
                int duplicate = 0;

                printf("\nEnter Student ID: ");
                scanf("%d", &newID);

                // Check duplicate ID
                for (int i = 0; i < count; i++)
                {
                    if (students[i].id == newID)
                    {
                        duplicate = 1;
                        break;
                    }
                }

                if (duplicate == 1)
                {
                    printf("\nStudent ID already exists!\n");
                    printf("Please use a different ID.\n");
                }
                else
                {
                    students[count].id = newID;

                    printf("Enter Student Name: ");
                    scanf(" %49[^\n]", students[count].name);

                    printf("Enter Student Age: ");
                    scanf("%d", &students[count].age);

                    printf("Enter Student Marks: ");
                    scanf("%f", &students[count].marks);

                    count++;

                    saveStudents(students, count);

                    printf("\nStudent added successfully!\n");
                }
            }
            else
            {
                printf("\nStudent limit reached!\n");
            }
        }

        // VIEW ALL STUDENTS
        else if (choice == 2)
        {
            if (count == 0)
            {
                printf("\nNo students found.\n");
            }
            else
            {
                printf("\n========== ALL STUDENTS ==========\n");

                for (int i = 0; i < count; i++)
                {
                    printf("\nStudent %d\n", i + 1);
                    printf("ID: %d\n", students[i].id);
                    printf("Name: %s\n", students[i].name);
                    printf("Age: %d\n", students[i].age);
                    printf("Marks: %.2f\n", students[i].marks);
                }
            }
        }

        // SEARCH STUDENT
        else if (choice == 3)
        {
            int searchID;
            int found = 0;

            printf("\nEnter Student ID to search: ");
            scanf("%d", &searchID);

            for (int i = 0; i < count; i++)
            {
                if (students[i].id == searchID)
                {
                    printf("\n========== STUDENT FOUND ==========\n");
                    printf("ID: %d\n", students[i].id);
                    printf("Name: %s\n", students[i].name);
                    printf("Age: %d\n", students[i].age);
                    printf("Marks: %.2f\n", students[i].marks);

                    found = 1;
                    break;
                }
            }

            if (found == 0)
            {
                printf("\nStudent not found.\n");
            }
        }

        // UPDATE STUDENT
        else if (choice == 4)
        {
            int updateID;
            int found = 0;

            printf("\nEnter Student ID to update: ");
            scanf("%d", &updateID);

            for (int i = 0; i < count; i++)
            {
                if (students[i].id == updateID)
                {
                    printf("\nEnter New Name: ");
                    scanf(" %49[^\n]", students[i].name);

                    printf("Enter New Age: ");
                    scanf("%d", &students[i].age);

                    printf("Enter New Marks: ");
                    scanf("%f", &students[i].marks);

                    saveStudents(students, count);

                    found = 1;

                    printf("\nStudent updated successfully!\n");
                    break;
                }
            }

            if (found == 0)
            {
                printf("\nStudent not found.\n");
            }
        }

        // DELETE STUDENT
        else if (choice == 5)
        {
            int deleteID;
            int found = 0;

            printf("\nEnter Student ID to delete: ");
            scanf("%d", &deleteID);

            for (int i = 0; i < count; i++)
            {
                if (students[i].id == deleteID)
                {
                    for (int j = i; j < count - 1; j++)
                    {
                        students[j] = students[j + 1];
                    }

                    count--;

                    saveStudents(students, count);

                    found = 1;

                    printf("\nStudent deleted successfully!\n");
                    break;
                }
            }

            if (found == 0)
            {
                printf("\nStudent not found.\n");
            }
        }

        // EXIT
        else if (choice == 6)
        {
            printf("\nThank you for using Student Management System!\n");
        }

        // STUDENT RESULTS
        else if (choice == 7)
        {
            if (count == 0)
            {
                printf("\nNo students found.\n");
            }
            else
            {
                float total = 0;

                printf("\n========== STUDENT RESULTS ==========\n");

                for (int i = 0; i < count; i++)
                {
                    char grade = calculateGrade(students[i].marks);

                    printf("\nID: %d\n", students[i].id);
                    printf("Name: %s\n", students[i].name);
                    printf("Marks: %.2f\n", students[i].marks);
                    printf("Grade: %c\n", grade);

                    total = total + students[i].marks;
                }

                float average = total / count;

                printf("\n=====================================\n");
                printf("Average Marks: %.2f\n", average);
                printf("=====================================\n");
            }
        }

        // INVALID CHOICE
        else
        {
            printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}