#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>

#pragma warning(disable : 4996)

using namespace std;

struct date
{
    int day, month, year;
};
struct car
{
    int ID;
    char songname[100], singersname[30], category[10];
    struct date albumdate;
} song_directory[100];

FILE* myFile;
int song_size = 100;

struct Menu
{
    void add_song(struct car);
    void delete_song(int);
    void all_song();
    void search_song(const char[], const char[]);
    void update_song(int, const char[], const char[]);
    void sort_by_songname(char);
    void sort_by_singersname(char);
    void quit();
};
void get_song();
bool songname_comp_asc(car, car);
bool songname_comp_desc(car, car);
bool singername_comp_asc(car a, car b);
bool singername_comp_desc(car a, car b);



int main()
{
    cout << endl << "Design by => Muhammad Yahya, Student No. => 21809210" << endl;

    car newMusic;
    newMusic.ID = 5;
    strcpy(newMusic.songname, "The Guardiangel");
    strcpy(newMusic.singersname, "Jonas Gwangwa");
    strcpy(newMusic.category, "Jazz");
    newMusic.albumdate.day = 22;
    newMusic.albumdate.month = 5;
    newMusic.albumdate.year = 1959;
    
    struct Menu menu;
    //menu.add_song(newMusic);
    //menu.all_song();
    //menu.delete_song(5);
    //char songname[] = "Angel of my life";
    //menu.search_song("songname", songname);
    menu.search_song("singersname", "Celien Dion");
    //menu.update_song(1, "year", "1998");
    //menu.sort_by_songname('a');
    //menu.all_song();
    //menu.sort_by_singersname('a');
    //menu.all_song();
}


void Menu::add_song(struct car music) {
    myFile = fopen("song_directory.txt", "a");

    fprintf(myFile, "%d,%s,%s,%s,%d %d %d\n",
        music.ID, music.songname, music.singersname, music.category,
        music.albumdate.day, music.albumdate.month, music.albumdate.year);

    fclose(myFile);

    cout<< endl << "New song added => " << music.songname << " By " << music.singersname << endl;
}

void Menu::delete_song(int id) {
    get_song();
    struct car music;
    struct car songs[100];
    int j = 0;
    for (int i = 0; i < song_size; i++) {
        music = song_directory[i];
        if (music.ID != id) {
            songs[i] = music;
            j++;
        }
    }
    song_size = j;
    myFile = fopen("song_directory.txt", "w");
    for (int x = 0; x < song_size; x++) {
        music = songs[x];
        fprintf(myFile, "%d,%s,%s,%s,%d %d %d\n",
            music.ID, music.songname, music.singersname, music.category,
            music.albumdate.day, music.albumdate.month, music.albumdate.year);
    }
    fclose(myFile);

    cout << endl << "Song with ID: " << id << " deleted successfully";
}

void Menu::all_song() {
    get_song();
    struct car music;
    cout << endl << "All songs: " << endl;
    if (song_size > 0)
    {
        for (int x = 0; x < song_size; x++) {
            music = song_directory[x];
            cout << endl;

            printf("ID: %d, Song Name: %s, Singers Name: %s, Category: %s, Album Date: %d-%d-%d",
                music.ID, music.songname, music.singersname, music.category,
                music.albumdate.day, music.albumdate.month, music.albumdate.year);
            cout << endl;
        }
    }
    else {
        cout << "The directory is empty" << endl;
    }
}

void Menu::search_song(const char searchBy[], const char searchKey[]) {
    get_song();
    bool found = false;
    struct car music;
    cout << endl << "All songs: " << endl;
    for (int x = 0; x < song_size; x++) {
        music = song_directory[x];
        if (strcmp(searchBy, "songname") == 0 && strcmp(searchKey, music.songname) == 0) {
            found = true;
            break;
        }
        else if (strcmp(searchBy, "singersname") == 0 && strcmp(searchKey, music.singersname) == 0) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << endl << "Search by: " << searchBy << ", Search key: " << searchKey;
        printf("\nResult => ID: %d, Song Name: %s, Singers Name: %s, Category: %s, Album Date: %d-%d-%d\n",
            music.ID, music.songname, music.singersname, music.category,
            music.albumdate.day, music.albumdate.month, music.albumdate.year);
    }
    else {
        cout << endl << "Search by: " << searchBy << ", Search key: " << searchKey;
        cout << endl << "Not found!" << endl;
    }

    fclose(myFile);
}

void Menu::update_song(int id, const char field[], const char value[]) {
    int rst = 0;
    get_song();
    struct car music;
    for (int x = 0; x < song_size; x++) {
        music = song_directory[x];
        if (music.ID == id) {
            if (field == "songname")
                strcpy(music.songname, value);
            else if (field == "singersname")
                strcpy(music.singersname, value);
            else if (field == "category")
                strcpy(music.category, value);
            else if (field == "day")
                rst = sscanf(value, "%d", &music.albumdate.day);
            else if (field == "month")
                rst = sscanf(value, "%d", &music.albumdate.month);
            else if (field == "year")
                rst = sscanf(value, "%d", &music.albumdate.year);
        }
        song_directory[x] = music;
    }

    myFile = fopen("song_directory.txt", "w");
    for (int x = 0; x < song_size; x++) {
        struct car music = song_directory[x];
        fprintf(myFile, "%d,%s,%s,%s,%d %d %d\n",
            music.ID, music.songname, music.singersname, music.category,
            music.albumdate.day, music.albumdate.month, music.albumdate.year);
    }
    fclose(myFile);
    cout << endl << "Song with ID: " << id << " updated successfully";
}
    
void Menu::sort_by_songname(char mode) {
    get_song();
    string msg = "The directory is empty";
    if (song_size > 0) {
        msg = "Song sorted by Song Name in Ascending Order";
        if (mode == 'a')
            sort(song_directory, song_directory + song_size, songname_comp_asc);
        else if (mode == 'd') {
            sort(song_directory, song_directory + song_size, songname_comp_desc);
            msg = "Song sorted by Song Name in Descending Order";
        }

        myFile = fopen("song_directory.txt", "w");
        for (int x = 0; x < song_size; x++) {
            struct car music = song_directory[x];
            fprintf(myFile, "%d,%s,%s,%s,%d %d %d\n",
                music.ID, music.songname, music.singersname, music.category,
                music.albumdate.day, music.albumdate.month, music.albumdate.year);
        }
        fclose(myFile);
    }

    cout << endl << msg;
}

void Menu::sort_by_singersname(char mode) {
    get_song();
    string msg = "The directory is empty";
    if (song_size > 0) {
        msg = "Song sorted by Singer Name in Ascending Order";
        if (mode == 'a')
            sort(song_directory, song_directory + song_size, singername_comp_asc);
        else if (mode == 'd') {
            sort(song_directory, song_directory + song_size, singername_comp_desc);
            msg = "Song sorted by Singer Name in Descending Order";
        }

        myFile = fopen("song_directory.txt", "w");
        for (int x = 0; x < song_size; x++) {
            struct car music = song_directory[x];
            fprintf(myFile, "%d,%s,%s,%s,%d %d %d\n",
                music.ID, music.songname, music.singersname, music.category,
                music.albumdate.day, music.albumdate.month, music.albumdate.year);
        }
        fclose(myFile);

        cout << endl << msg;
    }
    
}

void Menu::quit() {
    cout << endl << "Exit directory!!!";
}


void get_song() {
    if ((myFile = fopen("song_directory.txt", "r")) == NULL) {
        cout << "Song directory is empty";
        return;
    }
    struct car music;
    char buf[100];
    int j = 0;
    while (fgets(buf, 100, myFile) != NULL) {
        char* p;
        uint8_t i;
        char val[5][100];
        for (i = 0, p = strtok(buf, ","); p != NULL; p = strtok(NULL, ","), i++) {
            strcpy(val[i], p);
        }

        int rst = sscanf(val[0], "%d", &music.ID);
        strcpy(music.songname, val[1]);
        strcpy(music.singersname, val[2]);
        strcpy(music.category, val[3]);

        rst = sscanf(val[4], "%d %d %d",
            &music.albumdate.day, &music.albumdate.month, &music.albumdate.year);

        song_directory[j] = music;
        j++;

    }
    song_size = j;
    fclose(myFile);
}

bool songname_comp_asc(car a, car b){
    if (strcmp(a.songname, b.songname) < 0)
        return true;
    return false;
}

bool songname_comp_desc(car a, car b) {
    if (strcmp(a.songname, b.songname) > 0)
        return true;
    return false;
}

bool singername_comp_asc(car a, car b) {
    if (strcmp(a.singersname, b.singersname) < 0)
        return true;
    return false;
}

bool singername_comp_desc(car a, car b) {
    if (strcmp(a.singersname, b.singersname) > 0)
        return true;
    return false;
}
