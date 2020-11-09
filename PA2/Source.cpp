#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include<time.h>
void display_user_menu() {
	printf("(1) load\n");
	printf("(2) store\n");
	printf("(3) display\n");
	printf("(4) insert\n");
	printf("(5) delete\n");
	printf("(6) edit\n");
	printf("(7) sort\n");
	printf("(8) rate\n");
	printf("(9) play\n");
	printf("(10) shuffle\n");
	printf("(11) exit\n");
}

struct duration {
	int seconds;
	int minutes;
};

typedef struct record {
	char artist[256];
	char albumTitle[256];
	char songTitle[256];
	char genre[256];
	struct duration songLength;
	int numberOfTimesPlayed;
	int rating;
}Record;

// Struct Node - which will be an element in the Doubly linked list having pointers to the next node(element and previous element)
// First Node in DLL will have prev = null and last node in DLL will have next = null
struct Node {
	struct record data;
	struct Node* next;
	struct Node* prev;
};

// insert at beginning of DLL method
// head is pointer to pointer of the first node in DLL
// data is object of struct record which we have to insert in the DLL
void insert_in_front(struct Node** head, struct record data) {

	// Dynamically initialising a new node - dynamic memory allocation using malloc keyword
	struct Node * new_node = (struct Node*) malloc(sizeof(struct Node));
	new_node->data = data;

	// dereferencing head pointer - we get address of the first Node in the DLL
	new_node->next = (*head);

	// first node in DLL has prev pointer as NULL
	new_node->prev = NULL;

	// changing previous of head_node from null to new_node as new node is being inserted in the beginning.
	// checking for (*head != NULL) to avoid runtime errors
	if ((*head) != NULL) {
		(*head)->prev = new_node;
	}
	// As new node is inserted in front head pointer will now store address of the new node.
	(*head) = new_node;
}

void display_all(struct Node* head) {
	int count = 1;
	while (head != NULL) {
		printf("%d . \n", count);
		struct record current = head->data;
		printf("artist : %s\n", current.artist);
		printf("album title : %s\n", current.albumTitle);
		printf("song title : %s\n", current.songTitle);
		printf("genre : %s\n", current.genre);
		printf("songLength: %d:%d\n", current.songLength.minutes, current.songLength.seconds);
		printf("numberOfTimesPlayed :%d\n", current.numberOfTimesPlayed);
		printf("rating %d\n", current.rating);
		count++;
		head = head->next;
	}
}

int compare_string(char *first, char *second) {
	while (*first == *second) {
		if (*first == '\0' || *second == '\0')
			break;
		first++;
		second++;
	}

	if (*first == '\0' && *second == '\0')
		return 0;
	else
		return -1;
}

void display_matching_artist_playlist(struct Node* head, char* str) {
	while (head != NULL) {
		struct record current = head->data;
		if (compare_string(current.artist, str) == 0) {
			printf("artist : %s\n", current.artist);
			printf("album title : %s\n", current.albumTitle);
			printf("song title : %s\n", current.songTitle);
			printf("genre : %s\n", current.genre);
			printf("songLength : %d:%d\n", current.songLength.minutes, current.songLength.seconds);
			printf("numberOfTimesPlayed :%d", current.numberOfTimesPlayed);
			printf("rating %d", current.rating);
		}
		head = head->next;
	}
}

void load(struct Node ** pHead)
{
	//opening File
	//FILE * dataFile = fopen("musicPlaylist.csv", "r");
	FILE *dataFile;
	dataFile = fopen("musicPlaylist.csv", "r");
	//Buffer to read from file
	char buffer[1024];
	if (dataFile != 0)
	{

		// Now parse each line in the file using strtok
		char *tok;
		char *next_token;
		printf("Success File Open \n");

		while (fgets(buffer, 1024, dataFile)) {

			printf("%s ", buffer);

			Record *newRecord = (Record *)malloc(sizeof(Record));

			/*
			int count = 0;
			//tok = strtok_s(buffer, "\"");
			for (int i = 0; i < strlen(tok); i++) {
			if (tok[i] == ',')
			count++;
			if (count > 1)
			break;
			}
			if (count > 1) {
			tok = strtok_s(buffer, ",", &next_token);
			//tok = strtok(buffer, ",");
			}
			*/

			tok = strtok_s(buffer, ",:", &next_token);
			strcpy_s(newRecord->artist, tok);

			tok = strtok_s(0, ",", &next_token);
			strcpy_s(newRecord->albumTitle, tok);

			tok = strtok_s(0, ",", &next_token);
			strcpy_s(newRecord->songTitle, tok);

			tok = strtok_s(0, ",", &next_token);
			strcpy_s(newRecord->genre, tok);

			tok = strtok_s(0, ":", &next_token);
			newRecord->songLength.minutes = atoi(tok);

			tok = strtok_s(0, ",", &next_token);
			newRecord->songLength.seconds = atoi(tok);

			tok = strtok_s(0, ",", &next_token);
			newRecord->numberOfTimesPlayed = atoi(tok);

			tok = strtok_s(0, ",", &next_token);
			newRecord->rating = atoi(tok);

			insert_in_front(pHead, *newRecord);

		}

		// close the file
		fclose(dataFile);

	}

}

void store(struct Node * pHead)
{
	//opening File
	// * dataFile = fopen_s("musicPlaylist.csv", "w");
	FILE *dataFile;
	fopen_s(&dataFile, "musicPlaylist.csv", "w");
	if (dataFile != NULL)
	{
		printf("Success File Open \n");

		// Now write data values from the liked list in the file
		while (pHead != NULL) {
			Record data = pHead->data;
			fprintf(dataFile, "%s\",%s,%s,%s,%d:%d,%d,%d\n", data.artist,
				data.albumTitle, data.songTitle, data.genre, data.songLength.minutes,
				data.songLength.seconds, data.numberOfTimesPlayed, data.rating);

			pHead = pHead->next;
		}

		// close the file
		fclose(dataFile);

	}

}

void print_record(struct record current) {
	printf("Artist : %s\n", current.artist);
	printf("Album title : %s\n", current.albumTitle);
	printf("Song title : %s\n", current.songTitle);
	printf("\n");
}

void read(char* buffer, int max_size, FILE* file) {
	fgets(buffer, max_size, file);
	buffer[strlen(buffer) - 1] = '\0';
}

void edit(struct Node * pHead) {
	char artist[256];
	char album[256];
	char songTitle[256];
	//Ask the user to enter the artist name
	fflush(stdin);
	printf("Enter the artist name for the record to be edited: ");
	read(artist, 256, stdin);

	//Now find the record
	struct Node* temp = pHead;
	struct Node *rec = NULL;
	int count = 0;
	while (temp != NULL) {
		if (_stricmp(temp->data.artist, artist) == 0) {
			count++;
			rec = temp;
		}
		temp = temp->next;
	}
	//If there is more than one record, ask the user to enter the album
	if (count > 1) {
		rec = NULL;
		printf("Multiple records found!\n");
		temp = pHead;
		while (temp != NULL) {
			if (_stricmp(artist, temp->data.artist) == 0) {
				print_record(temp->data);
			}
			temp = temp->next;
		}
		//Ask the user to enter the album and song title
		printf("Enter the album: ");
		read(album, 256, stdin);
		printf("Enter the song title: ");
		read(songTitle, 256, stdin);
		temp = pHead;
		while (temp != NULL) {
			//If the album and title match
			if (_stricmp(artist, temp->data.artist) == 0 &&
				_stricmp(album, temp->data.albumTitle) == 0 &&
				_stricmp(songTitle, temp->data.songTitle) == 0) {
				rec = temp;
				break;
			}
			temp = temp->next;
		}

	}
	//If record not found, print error
	if (rec == NULL) {
		printf("Record not found!\n");
	}
	else {
		printf("Record found!\n");
		printf("Set the artist name for the record: ");
		read(rec->data.artist, 256, stdin);
		printf("Set the album name for the record: ");
		read(rec->data.albumTitle, 256, stdin);
		printf("Set the song title for the record: ");
		read(rec->data.songTitle, 256, stdin);
		printf("Set the Genre for the record: ");
		read(rec->data.genre, 256, stdin);
		printf("Set the minutes for the song duration: ");
		scanf_s("%d", &rec->data.songLength.minutes);
		printf("Set the seconds for the song duration: ");
		scanf_s("%d", &rec->data.songLength.seconds);
		printf("Set the number of times played for the record: ");
		scanf_s("%d", &rec->data.numberOfTimesPlayed);
		printf("Set the rating for the record: ");
		scanf_s("%d", &rec->data.rating);
		printf("Recored edited successfully!\n");
	}

}

void rate(struct Node* pHead) {
	char artist[256];
	char album[256];
	char songTitle[256];
	//Ask the user to enter the artist name
	fflush(stdin);
	printf("Enter the artist name for the record to rate: ");
	read(artist, 256, stdin);
	//Ask the user to enter the album and song title
	printf("Enter the album: ");
	read(album, 256, stdin);
	printf("Enter the song title: ");
	read(songTitle, 256, stdin);
	struct Node *temp = pHead;
	struct Node *rec;
	while (temp != NULL) {
		//If the album and title match
		if (_stricmp(artist, temp->data.artist) == 0 &&
			_stricmp(album, temp->data.albumTitle) == 0 &&
			_stricmp(songTitle, temp->data.songTitle) == 0) {
			rec = temp;
			break;
		}
		temp = temp->next;
	}

	//If record not found, print error
	if (rec == NULL) {
		printf("Record not found!\n");
	}
	else {
		printf("Record found!\n");
		while (1) {
			printf("Set the rating for the record: ");
			scanf_s("%d", &rec->data.rating);
			if (rec->data.rating > 5 || rec->data.rating < 1) {
				printf("Rating must be between 1 and 5\n");
			}
			else {
				break;
			}
		}

		printf("Record rated successfully!\n");
	}

}

void play(struct Node* pHead) {
	
	struct Node *temp = pHead;
	
	if (temp)
	{

	while (temp != NULL) {
		printf("Now playing : %s\n", temp->data.songTitle);
		Sleep(5000);
		temp = temp->next;
	}

	}
	else
	{
		printf("Playlist empty!\n");
	}

	/*
	char artist[256];
	char album[256];
	char songTitle[256];
	
	//Ask the user to enter the artist name
	fflush(stdin);

	printf("Enter the artist name for the record to play: ");
	read(artist, 256, stdin);
	
	//Ask the user to enter the album and song title
	printf("Enter the album: ");
	read(album, 256, stdin);
	
	printf("Enter the song title: ");
	read(songTitle, 256, stdin);
	
	struct Node *rec;
	
	struct Node *temp = pHead;
	while (temp != NULL) {
		//If the album and title match
		if (_stricmp(artist, temp->data.artist) == 0 &&
			_stricmp(album, temp->data.albumTitle) == 0 &&
			_stricmp(songTitle, temp->data.songTitle) == 0) {
			rec = temp;
			break;
		}
		temp = temp->next;
	}

	//If record not found, print error
	if (rec == NULL) {
		printf("Record not found!\n");
	}
	else {
		while (rec != NULL) {
			system("cls");
			printf("Playing: \n");
 			print_record(rec->data);
			Sleep(5000);
			rec->data.numberOfTimesPlayed++;
			rec = rec->next;
		}

	}
	*/
}

void deleteNode(struct Node **head_ref, struct Node *del)
{
	/* base case */
	if (*head_ref == NULL || del == NULL)
		return;

	/* If node to be deleted is head node */
	if (*head_ref == del)
		*head_ref = del->next;

	/* Change next only if node to be deleted is NOT the last node */
	if (del->next != NULL)
		del->next->prev = del->prev;

	/* Change prev only if node to be deleted is NOT the first node */
	if (del->prev != NULL)
		del->prev->next = del->next;

	/* Finally, free the memory occupied by del*/
	free(del);

	return;
}

// function to insert a new node in sorted way in
// a sorted doubly linked list
void sortedInsert(struct Node** head_ref, struct Node* newNode, int key)
{
	struct Node* current;
	if (key == 1)
	{
		//artist

		// if list is empty
		if (*head_ref == NULL)
			*head_ref = newNode;
		// if the node is to be inserted at the beginning
		// of the doubly linked list
		else if (strcmp((*head_ref)->data.artist, newNode->data.artist) >= 0) {
			newNode->next = *head_ref;
			newNode->next->prev = newNode;
			*head_ref = newNode;
		}

		else {
			current = *head_ref;

			// locate the node after which the new node
			// is to be inserted
			while (current->next != NULL &&
				strcmp(current->next->data.artist, newNode->data.artist)<0)
				current = current->next;

			/*Make the appropriate links */

			newNode->next = current->next;

			// if the new node is not inserted
			// at the end of the list
			if (current->next != NULL)
				newNode->next->prev = newNode;

			current->next = newNode;
			newNode->prev = current;
		}
	}


	else if (key == 2)
	{
		//album

		// if list is empty
		if (*head_ref == NULL)
			*head_ref = newNode;
		// if the node is to be inserted at the beginning
		// of the doubly linked list
		else if (strcmp((*head_ref)->data.albumTitle, newNode->data.albumTitle) >= 0) {
			newNode->next = *head_ref;
			newNode->next->prev = newNode;
			*head_ref = newNode;
		}

		else {
			current = *head_ref;

			// locate the node after which the new node
			// is to be inserted
			while (current->next != NULL &&
				strcmp(current->next->data.albumTitle, newNode->data.albumTitle)<0)
				current = current->next;

			/*Make the appropriate links */

			newNode->next = current->next;

			// if the new node is not inserted
			// at the end of the list
			if (current->next != NULL)
				newNode->next->prev = newNode;

			current->next = newNode;
			newNode->prev = current;
		}
	}


	else if (key == 3)
	{
		//rating

		// if list is empty
		if (*head_ref == NULL)
			*head_ref = newNode;
		// if the node is to be inserted at the beginning
		// of the doubly linked list
		else if ((*head_ref)->data.rating >= newNode->data.rating) {
			newNode->next = *head_ref;
			newNode->next->prev = newNode;
			*head_ref = newNode;
		}

		else {
			current = *head_ref;

			// locate the node after which the new node
			// is to be inserted
			while (current->next != NULL &&
				current->next->data.rating < newNode->data.rating)
				current = current->next;

			/*Make the appropriate links */

			newNode->next = current->next;

			// if the new node is not inserted
			// at the end of the list
			if (current->next != NULL)
				newNode->next->prev = newNode;

			current->next = newNode;
			newNode->prev = current;
		}
	}

	else if (key == 4)
	{
		//playback

		// if list is empty
		if (*head_ref == NULL)
			*head_ref = newNode;
		// if the node is to be inserted at the beginning
		// of the doubly linked list
		else if ((*head_ref)->data.songLength.minutes > newNode->data.songLength.minutes) {
			newNode->next = *head_ref;
			newNode->next->prev = newNode;
			*head_ref = newNode;

		}
		else if ((*head_ref)->data.songLength.minutes == newNode->data.songLength.minutes) {
			if ((*head_ref)->data.songLength.seconds >= newNode->data.songLength.seconds)
			{
				newNode->next = *head_ref;
				newNode->next->prev = newNode;
				*head_ref = newNode;
			}
			else {
				current = *head_ref;

				// locate the node after which the new node
				// is to be inserted
				while (current->next != NULL &&
					current->next->data.songLength.seconds < newNode->data.songLength.seconds)
					current = current->next;

				/*Make the appropriate links */

				newNode->next = current->next;

				// if the new node is not inserted
				// at the end of the list
				if (current->next != NULL)
					newNode->next->prev = newNode;

				current->next = newNode;
				newNode->prev = current;
			}
		}
		else {
			current = *head_ref;

			// locate the node after which the new node
			// is to be inserted
			while (current->next != NULL &&
				current->next->data.songLength.minutes < newNode->data.songLength.minutes)
				current = current->next;

			/*Make the appropriate links */

			newNode->next = current->next;

			// if the new node is not inserted
			// at the end of the list
			if (current->next != NULL)
				newNode->next->prev = newNode;

			current->next = newNode;
			newNode->prev = current;
		}
	}

}

// function to sort a doubly linked list using insertion sort
void insertionSort(struct Node** head_ref, int key)
{
	// Initialize 'sorted' - a sorted doubly linked list
	struct Node* sorted = NULL;

	// Traverse the given doubly linked list and
	// insert every node to 'sorted'
	struct Node* current = *head_ref;
	while (current != NULL) {

		// Store next for next iteration
		struct Node* next = current->next;

		// removing all the links so as to create 'current'
		// as a new node for insertion
		current->prev = current->next = NULL;

		// insert current in 'sorted' doubly linked list
		sortedInsert(&sorted, current, key);

		// Update current
		current = next;
	}

	// Update head_ref to point to sorted doubly linked list
	*head_ref = sorted;
}

void reverse(struct Node **head_ref)
{
	struct Node *temp = NULL;
	struct Node *current = *head_ref;

	/* swap next and prev for all nodes of
	doubly linked list */
	while (current != NULL)
	{
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}

	/* Before changing head, check for the cases like empty
	list and list with only one node */
	if (temp != NULL)
		*head_ref = temp->prev;
}

//count no. of nodes in list
int length(struct Node* head)
{
	int count = 0;  // Initialize count
	struct Node* current = head;  // Initialize current
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return count;
}

int main(void) {
	int temp2 = 0;
	struct Node* head = NULL;
	char song[236];
	struct Node* Nodetemp = NULL;
	char songTitle;
	int value = 0;

	while (value != 11) 
	{
	
		//If the user chose 1, load the file
		printf("Select one of the following options\n");
		display_user_menu();
		scanf_s("%d", &value);

		if (value == 1) {
			load(&head);
		}

		else if (value == 2) {
			store(head);
		}
		else if (value == 3) {
			printf("What kind of printing do you want pls select from below\n");
			printf("1. Print all records.\n");
			printf("2. Print all records that match an artist.\n");
			int temp = 1;
			scanf_s("%d", &temp);
			if (temp == 1) {
				display_all(head);
			}
			else if (temp == 2) {
				printf("Enter artist name \n");
				char artist[20];
				scanf("%s", artist);
				display_matching_artist_playlist(head, artist);
			}
		}
		else if (value == 4) {
			Record data;

			printf("Enter the name of the artist \n");
			scanf("%s", data.artist);
			getchar();

			printf("Enter the title of the album \n");
			scanf("%s", data.albumTitle);
			getchar();

			printf("Enter the title of the song \n");
			scanf("%s", data.songTitle);
			getchar();

			printf("Enter the genre \n");
			scanf("%s", data.genre);
			getchar();

			printf("Enter the song length (minutes) \n");
			scanf("%d", &data.songLength.minutes);
			getchar();

			printf("Enter the song length (seconds) \n");
			scanf("%d", &data.songLength.seconds);
			getchar();

			printf("Enter the number of times played \n");
			scanf("%d", &data.numberOfTimesPlayed);
			getchar();

			printf("Enter the rating of song \n");
			scanf("%d", &data.rating);
			getchar();

			insert_in_front(&head, data);

		}

		else if (value == 5) {
			printf("Enter the song title you want to remove \n");
			getchar();
			fgets(song, 255, stdin);
			song[strlen(song)-1] = '\0';

			Node * temp = head;

			while (temp != NULL) 
			{
				struct record current = temp->data;
				if (compare_string(current.songTitle, song) == 0) {
					deleteNode(&head, temp);
					temp = NULL;
				}
				else
				{
					temp = temp->next;
				}
			}
		}
		else if (value == 6) {
			edit(head);
		}
		else if (value == 7) {

			printf("How do you want to sort? Select your basis: \n 1. Artist\n 2. Album\n 3. Rating]\n 4. Playback Times ");
			scanf("%d", temp2);
			insertionSort(&head, temp2);
			if (temp2 == 4)
			{
				// descending order
				reverse(&head);
			}
		}

		else if (value == 8) {
			rate(head);
		}
		else if (value == 9)
			play(head);

		else if (value == 10) {
			// shuffle
			int A = length(head);
			time_t t;
			/* Intializes random number generator */
			srand((unsigned)time(&t));
			int* temp = (int*)malloc(A * sizeof(int));
			for (int i = 0; i<A; i++) {
				temp[i] = rand() % A;
				// play those sequences stored in temp[i]
				struct Node *rec = head;
				int count = 0;
				while (rec != NULL) {
					count++;
					system("cls");
					if (count == temp[i])
					{

						printf("Playing: \n");
						print_record(rec->data);
						Sleep(5000);
						rec->data.numberOfTimesPlayed++;
					}
					rec = rec->next;
				}

			}
		}

	}
	printf("Select one of the following options\n");
	display_user_menu();
	scanf_s("%d", &value);

	store(head);
	return 0;
}






