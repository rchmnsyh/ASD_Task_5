#include "player.h"
#include <ctime>

int randomInt(int  max_int) {
    srand(time(NULL));
    return (rand() % max_int) + 1;
}

void printInfo(List L) {
    /**
    * PR : menampilkan informasi ID, nama, dan lokasi file
    */

    address Q = first(L);
    do {
        cout<<"name    : "<<info(Q).name<<endl
            <<"ID      : "<<info(Q).ID<<endl
            <<"Location: "<<info(Q).location<<endl<<endl;
        Q = next(Q);
    } while(Q!=first(L));
    cout<<"==============================================="<<endl;
}


void playMusic(address P) {
    /**
    * PR : memainkan lagu yang ditunjuk oleh pointer P
    */

    string filename = info(P).location+"/"+info(P).name;
    cout<<"playing "<<filename<<endl;
    PlaySound(TEXT(filename.c_str()), NULL, SND_FILENAME);
    _sleep(500); //delay 0.5 second
}


void shuffleList(List &L) {
    /**
    * PR : mengacak isi (elemen) dari list L
    * FS : isi (elemen) dari list teracak
    */
    //-------------your code here-------------
    address P = first(L);
    int x = randomInt(10);
    for(int i=0;i<=x;i++){
        P = next(P);
    }
    address Prec = prev(P);
    deleteAfter(L,Prec,P);
    insertFirst(L,P);
    cout<<"Music list shuffled."<<endl;
    //----------------------------------------
}

void sortListByID(List &L) {
    /**
    * PR : mengurutkan isi (elemen) dari list L berdasarkan ID
    * FS : isi (elemen) dari list L terurut
    */
    //-------------your code here-------------
    List new_L;
    createList(new_L);
    address P = first(L);
    address Prec = NULL;
    do{
        address Q = next(P);
        if((first(new_L) == NULL) || (info(P).ID < info(first(new_L)).ID)){
            insertFirst(new_L,P);
        }
        else if(info(P).ID >= info(last(new_L)).ID){
            insertLast(new_L,P);
        }
        else{
            Prec = first(new_L);
            while(info(next(Prec)).ID <= info(P).ID){
                Prec = next(Prec);
            }
            insertAfter(new_L,Prec,P);
        }
        P = Q;
    }while(P!=first(L));
    L = new_L;
    //----------------------------------------
}

void playRepeat(List &L, int n) {
    /**
    * PR : memainkan seluruh lagu di dalam list
    *      dari lagu pertama hingga terakhir sebanyak n kali
    */
    //-------------your code here-------------
    int i;
    address P;
    for(i=1;i<=n;i++){
        P = first(L);
        do{
            playMusic(P);
            P=next(P);
        }while(P!=first(L));
    }
    //----------------------------------------
}

void deleteMusicByID(List &L, infotype x) {
    /**
    * IS : list L mungkin kosong
    * PR : menerima input user untuk ID lagu yang ingin dihapus
    *      jika ID lagu ditemukan, hapus (deallocate) lagu dari list
    * FS : elemen dengan ID yang dicari dideallocate
    */
    //-------------your code here-------------
    if(first(L) != NULL){
        address P = findElmByID(L,x);
        if(P!=NULL){
            address Prec = prev(P);
            deleteAfter(L,Prec,P);
            deallocate(P);
            cout<<"Music with ID "<<x.ID<<" deleted."<<endl;
        }
        else{
            cout<<"ERROR: Music with ID "<<x.ID<<" not found!"<<endl;
        }
    }
    //----------------------------------------
}
