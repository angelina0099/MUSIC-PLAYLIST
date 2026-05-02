#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for each song
typedef struct Song {
    char title[100];
    char singer[100];
    char date[20];   // Format: DD/MM/YYYY
    float duration;  // in minutes

    struct Song *prev;
    struct Song *next;
} Song;

// Head and Tail pointers
Song *head = NULL;
Song *tail = NULL;

// Current song (like a pointer in a music player)
Song *current = NULL;

// Create a new song node
Song* createSong(char title[], char singer[], char date[], float duration) {
    Song *newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->title, title);
    strcpy(newSong->singer, singer);
    strcpy(newSong->date, date);
    newSong->duration = duration;
    newSong->next = NULL;
    newSong->prev = NULL;
    return newSong;
}

// Add song to end of playlist
void addSong() {
    char title[100], singer[100], date[20];
    float duration;

    printf("Enter song title: ");
    getchar(); // clear buffer
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0;

    printf("Enter singer name: ");
    fgets(singer, sizeof(singer), stdin);
    singer[strcspn(singer, "\n")] = 0;

    printf("Enter release date (DD/MM/YYYY): ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = 0;

    printf("Enter duration (in minutes): ");
    scanf("%f", &duration);

    Song *newSong = createSong(title, singer, date, duration);

    if (head == NULL) {
        head = tail = current = newSong;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }

    printf(" Song added successfully!\n");
}

// Display playlist forward
void displayPlaylistForward() {
    Song *temp = head;
    printf("\n Playlist (Forward):\n");
    while (temp) {
        printf(" Title: %s | Singer: %s | Date: %s | Duration: %.2f min\n", temp->title, temp->singer, temp->date, temp->duration);
        temp = temp->next;
    }
}

// Display playlist backward
void displayPlaylistBackward() {
    Song *temp = tail;
    printf("\n Playlist (Backward):\n");
    while (temp) {
        printf(" Title: %s | Singer: %s | Date: %s | Duration: %.2f min\n", temp->title, temp->singer, temp->date, temp->duration);
        temp = temp->prev;
    }
}

// Delete a song by title
void deleteSong() {
    char title[100];
    printf("Enter the title of the song to delete: ");
    getchar(); // clear buffer
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0;

    Song *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            if (temp == head)
                head = temp->next;
            if (temp == tail)
                tail = temp->prev;
            if (temp->prev)
                temp->prev->next = temp->next;
            if (temp->next)
                temp->next->prev = temp->prev;
            if (current == temp)
                current = temp->next ? temp->next : temp->prev;

            free(temp);
            printf(" Song deleted successfully.\n");
            return;
        }
        temp = temp->next;
    }

    printf(" Song not found.\n");
}

// Play current song
void playCurrentSong() {
    if (current == NULL) {
        printf(" No song currently selected.\n");
        return;
    }

    printf(" Now Playing: %s by %s | %s | %.2f min\n", current->title, current->singer, current->date, current->duration);
}

// Move to next song
void nextSong() {
    if (current && current->next) {
        current = current->next;
        playCurrentSong();
    } else {
        printf(" No next song.\n");
    }
}

// Move to previous song
void prevSong() {
    if (current && current->prev) {
        current = current->prev;
        playCurrentSong();
    } else {
        printf(" No previous song.\n");
    }
}

// Clear entire playlist
void clearPlaylist() {
    Song *temp = head;
    while (temp != NULL) {
        Song *toDelete = temp;
        temp = temp->next;
        free(toDelete);
    }
    head = tail = current = NULL;
    printf(" Playlist cleared.\n");
}

// Main menu
int main() {
    int choice;
    do {
        printf("\n======  MUSIC PLAYLIST MANAGER ======\n");
        printf("1. Add song\n");
        printf("2. Delete song\n");
        printf("3. Show playlist (forward)\n");
        printf("4. Show playlist (backward)\n");
        printf("5. Play current song\n");
        printf("6. Next song\n");
        printf("7. Previous song\n");
        printf("8. Clear playlist\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addSong(); break;
            case 2: deleteSong(); break;
            case 3: displayPlaylistForward(); break;
            case 4: displayPlaylistBackward(); break;
            case 5: playCurrentSong(); break;
            case 6: nextSong(); break;
            case 7: prevSong(); break;
            case 8: clearPlaylist(); break;
            case 0: printf(" Goodbye!\n"); break;
            default: printf(" Invalid choice.\n");
        }
    } while(choice != 0);

    clearPlaylist(); // free memory on exit
    return 0;
}
