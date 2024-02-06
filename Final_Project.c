//////////////////////////////  Clinic Mangement System  //////////////////////////////

#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include "../MACROS/STD_TYPES.h"
#include "../MACROS/BIT_MATH.h"

#define PASSWORD 1234
#define MAX_PATIENTS 100
#define MAX_SLOTS 5

// u32 mode, Mode;
//  ADD a New Patient Record
typedef struct New_Patient_Record
{
	u8 name[50];
	u8 gender[10];
	u32 age;
	u32 ID;

} Sadd_patient;

// Reserve a slot with the doctor
typedef struct Reservation
{
	u32 slot;
	u32 patientID;
} Sreserve_patient;

Sadd_patient patients[MAX_PATIENTS];
Sreserve_patient reservations[MAX_SLOTS];
u32 Patient_Count = 0;
u32 Reservation_Count = 0;

// Prototypes
u32 Start_Menu();
void thank_you();
void anythingElse();

void ADMIN_MENU();
void ADMINMode();
void UserMode();
void USER_MENU();

u32 isPatientIDExists(u32 ID); // Is Patient ID Exists?
u32 isSlotAvailable(u32 slot); // Is slot Available?
void addPatient();			   // Add Patients
void editPatient();			   // Is Edit Patient ?
void reserveSlot();			   // reserve Slot
void cancelReservation();	   // Cancel reservation.

//////////////////////////////////////////////////////////////// Main ////////////////////////////////////////////////////////////////
int main()
{
	// Variables
	u32 mode, password, option, i, flag = 0;
	printf("\n////////////// Welcome to Clinic Mangement System  //////////////  \n\n");
	do
	{
		mode = Start_Menu();

		if (mode == 1)
		{
			ADMINMode();
			// Start_Menu();
			// anythingElse();
		}
		else if (mode == 2)
		{
			UserMode();
			// Start_Menu();
			//  anythingElse();
		}
		else if (mode == 3)
		{
			thank_you();
		}

	} while (mode < 3);
}

//////////////////////////////////////////////////////////////// End Main ////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////// Functions ////////////////////////////////////////////////////////////////

void thank_you()
{
	u32 mode;
	printf("\n");
	printf("\nThank you for choosing our app! We appreciate your support and hope you had a great experience.\n");
	printf("If you have any feedback or suggestions, please feel free to share them with us.\n");
	printf("Have a wonderful day!.\n");
}

u32 Start_Menu()
{
	u32 mode;
	printf("\n	<Main Meun>	\n");
	printf("\nChoose between: \n(1) 'Admin Mode' \n(2) 'User Mode' \n(3) 'Exit App' \n>>> Enter Your Option: ");
	scanf("%d", &mode);
	return mode;
}

///////// Any thing else /////////
void anythingElse()
{
	char option, mode = 0;
	printf("\n**** Do you need to do any other prosess? ****\n");
	printf(">>> Enter [Y] of yes or [N] of no: ");
	scanf(" %c", &option);
	if (option == 'y' || option == 'Y')
	{
		printf(" \n");
		// Start_Menu();
	}
	else if (option == 'n' || option == 'N')
	{
		thank_you();
		mode = 3;
	}
}

///////// Patient ID Exists /////////
u32 isPatientIDExists(u32 ID)
{
	u32 i;
	for (i = 0; i < Patient_Count; i++)
	{
		if (ID == patients[i].ID)
		{
			return 1;
		}
	}
	return 0;
}

///////// slot Available /////////
u32 isSlotAvailable(u32 slot)
{
	u32 i;
	for (i = 0; i < Reservation_Count; i++)
	{
		if (slot == reservations[i].slot)
		{
			return 0;
		}
	}
	return 1;
}

///////// Add Patients /////////
void addPatient()
{
	Sadd_patient newPatient;
	printf("\n\n		<Add Patient>\n\n");
	printf(">>> Enter patient name: ");
	scanf(" %[^\n]%*c", newPatient.name);
	printf(">>> Enter patient age: ");
	scanf(" %d", &newPatient.age);
	printf(">>> Enter patient gender: ");
	scanf(" %s", newPatient.gender);
	printf(">>> Enter patient ID: ");
	scanf(" %d", &newPatient.ID);

	if (isPatientIDExists(newPatient.ID))
	{
		printf("\n____ Patient with the same ID already exists. Record not added. ____ \n\n");
	}
	else
	{
		patients[Patient_Count] = newPatient;
		Patient_Count++;
		printf("\n____ Patient record added successfully. ____ \n\n");
	}
}

///////// Edit Patient /////////
void editPatient()
{
	u32 i, edit_ID, found = 0;
	printf("\n\n		<Edit Patient>\n\n");
	printf(">>> Please Enter Patient ID to Edit: ");
	scanf("%d", &edit_ID);

	for (i = 0; i < Patient_Count; i++)
	{
		if (patients[i].ID == edit_ID)
		{
			printf(">>> Enter new patient name: ");
			scanf(" %[^\n]%*c", patients[i].name);
			printf(">>> Enter new patient age: ");
			scanf("%d", &patients[i].age);
			printf(">>> Enter new patient gender: ");
			scanf("%s", patients[i].gender);
			printf("\n____ Patient record edited successfully. ____\n\n");
			found = 1;
			break;
		}
	}
	if (!found)
	{
		printf("___ Patient ID Not Found ____\n");
	}
}

///////// reserve Slot /////////
void reserveSlot()
{
	u32 patientID, slot;
	printf("\n\n		<Reserve Patient>\n\n");
	printf(">>> Enter patient ID: ");
	scanf("%d", &patientID);

	if (!isPatientIDExists(patientID))
	{
		printf("___ Patient ID Not Found ____ Reservation failed.\n");
		return;
	}

	printf("Available slots:\n");
	printf("1. 2pm - 2:30pm\n");
	printf("2. 2:30pm - 3pm\n");
	printf("3. 3pm - 3:30pm\n");
	printf("4. 4pm - 4:30pm\n");
	printf("5. 4:30pm - 5pm\n");
	printf(">>> Enter slot number (1-5): ");
	scanf("%d", &slot);

	if (slot < 1 || slot > 5 || !isSlotAvailable(slot))
	{
		printf("\n____ Invalid slot or slot already reserved. Reservation failed. ____ \n\n");
	}
	else
	{
		reservations[Reservation_Count].slot = slot;
		reservations[Reservation_Count].patientID = patientID;
		Reservation_Count++;
		printf("\n____ Reservation successful. ____\n\n");
	}
}

///////// Cancel reservation /////////
void cancelReservation()
{
	u32 i, patientID;

	printf("\n\n		<Cancel Patient>\n\n");
	printf(">>> Enter patient ID to cancel reservation: ");
	scanf("%d", &patientID);

	for (i = 0; i < Reservation_Count; i++)
	{
		if (reservations[i].patientID == patientID)
		{
			reservations[i].patientID = 0;
			printf("\n____ Reservation canceled successfully.____ \n\n");
			return;
		}
	}
	printf("\n____ Reservation not found for the given patient ID.____ \n\n");
}

//////////////////////////////////////// Admin Mode ////////////////////////////////////////
void ADMIN_MENU()
{
	printf("\n1. Add new patient record\n");
	printf("2. Edit patient record\n");
	printf("3. Reserve a slot with the doctor\n");
	printf("4. Cancel reservation\n");
	printf("5. Back to Main Menu\n");
}

void ADMINMode()
{
	u32 i = 0, password, option, flag = 3;

	printf("\n...** Login to Admin Mode **...\n\n");
	while (i < 3)
	{
		printf(">>> Please Enter Password: ");
		scanf("%d", &password);

		if (password == PASSWORD)
		{
			printf("\n\n		 'Admin Mode'\n");
			ADMIN_MENU();
			printf(">>> Enter a number of your option: ");
			scanf("%d", &option);

			if (option == 1)
			{
				addPatient();
				break;
			}
			else if (option == 2)
			{
				editPatient();
				break;
			}
			else if (option == 3)
			{
				reserveSlot();
				break;
			}
			else if (option == 4)
			{
				cancelReservation();
				break;
			}
			else if (option == 5)
			{
				break;
			}
			else
			{
				printf("\n____ Invalid choice. Please try again. ____ \n\n");
			}

			/*
					switch (option)
					{
					case 1:
						addPatient();
						// Start_Menu();
						break;
					case 2:
						editPatient();
						break;
					case 3:
						reserveSlot();
						break;
					case 4:
						cancelReservation();
						break;
					// case 5:
					// 	Start_Menu();
					// 	break;
					default:
						printf("Invalid choice. Please try again.\n");
						break;
					}
				*/
		}
		else
		{
			printf("\n____ Incorrect Password____ \n\n");
			i++;
			--flag;
			if (flag == 0)
			{
				printf("\n____ Too many incorrect attempts. Exiting...\n\n");
			}
		}
	}
}

//////////////////////////////////////// User Mode ////////////////////////////////////////
void USER_MENU()
{
	printf("\n\n		 'User Mode'\n\n");
	printf("1. View patient record\n");
	printf("2. View today's reservations\n");
	printf("3. Back to Main Menu\n");
}

void UserMode()
{

	u32 i = 0, choice, patient_id, found = 0, flag = 0;
	do
	{
		printf("\n");
		USER_MENU();

		printf(">>> Enter your choice: ");
		scanf("%d", &choice);
		printf("\n");

		if (choice == 1)
		{
			printf("... Patient Record ... \n\n");
			printf(">>> Enter patient ID: ");
			scanf("%d", &patient_id);
			printf("\n");

			for (i = 0; i < Patient_Count; i++)
			{
				if (patient_id == patients[i].ID)
				{
					printf("Patient Name: %s\n", patients[i].name);
					printf("Patient Age: %d\n", patients[i].age);
					printf("Patient Gender: %s\n", patients[i].gender);
					printf("\n");
					found = 1;
					flag = 1;
				}
			}
			if (!found)
			{
				printf(".. ___ Patient ID Not Found ____ .. \n\n");
			}
		}
		else if (choice == 2)
		{
			printf("\n");
			printf("\n... [ Today's Reservations ] ... \n\n");
			for (i = 0; i < Reservation_Count; i++)
			{
				if (reservations[i].patientID != 0)
				{
					printf("Slot: %d ... Patient ID: %d\n", reservations[i].slot, reservations[i].patientID);
					printf("\n");
					flag = 2;
				}
			}
		}
		else
		{
			if (flag != 0)
			{
				printf("Invalid choice. Please try again.\n");
			}
		}
	} while (choice < 3);
}
