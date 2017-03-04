#include <iostream>
#include <fstream>

using namespace std;

#define MIN 1000
#define MAX 30 // Nr maxim de orase

ifstream f("harta.txt");

void afisare_drum(int drum_scurt[100],int cost_min);

int dist[MAX][MAX]; //Matricea cu distantele dintre orase
int orase; //nr de orase
int drum[MAX]; //Drumul comis voiajorului, contine indexul oraselor vizitate
int vizitat[MAX]; //Vector care memoreaza ce orase am vizitat, vizitat[i]=1 daca orasul a fost vizitat altfel 0.

void alege(int ultim, int *min, int *j_min){
	int j;
	//Se cauta distanta minima pana la un oras ce nu a fost vizitat;
	*min=MIN; 
	*j_min=-1;
	for(j=0;j<orase;j++){
		if(!vizitat[j]){
			if (dist[ultim][j] != 0){
				if(dist[ultim][j+1] == 0 ){
					alege(ultim+1,min,j_min);
				}
				else{
					*min = dist[ultim][j];
					*j_min=j;
				}
			}
		}
	}
}

int deschide_fisier(){//verificam daca fisierul poate fi deschis
	if(!f){
		cout << "Fisierul nu poate fi deschis" << endl;
		return 0;
	}
	else{
		return 1;
	}
}

void citeste_din_fisier(){
	int i,j;
	if(deschide_fisier() ){//daca fisierul poate fi deschis citim primul rand din el, care ne spune cate orase sunt de parcurs.
		 f >> orase;
	}
	for(i=0;i<orase;i++){//citim din fisier matricea distantelor
		for(j=0;j<orase;j++){
			f >> dist[i][j];
		}
	}
}

void distante(){//afisam matricea ce am citit-o din fisier
	cout << "Distanta intre orase" << endl;
	for(int i=0;i<orase;i++){
		for(int j=0;j<orase;j++){
			cout << dist[i][j] << " ";
		}
		cout << endl;
	}
}

void traseu(){
	int index,min,j_min;
	int nr, cost;
	int cost_min=MIN;
	int drum_min[MAX];
	int destinatie = 21;
	for(index = 0;index<2;index++){
		cout << " Pornim din punctul " << index+1 << endl;
		min=MIN;
		j_min=MIN;
		for (int i=0;i<orase;i++){
			vizitat[i]=0; //Initial nici un punct nu a fost vizitat
			drum[i]=0;
		}//initial suntem in orasul cu nr 0.
		drum[0]=index;
		vizitat[index]=1;
		nr=1;
		cost=0;
		//parcurgem restul de n-1 orase
		for(int i=0;i<orase-1;i++){
			//alegem urmatorul oras;
			alege(drum[nr-1],&min,&j_min);
			//se parcurge drumul cel mai scurt gasit intre orase
			if (min > 0){
				cout << "Legatura intre " << drum[nr-1]+1 << " , " << j_min+1 << " cu costul " << min << endl;
			}
			drum[nr]=j_min;
			vizitat[j_min]=1;
			nr++;
			cost+=min;
		}
		cout << "----" << drum[nr] << "---" << endl;
		if (drum[nr] == 21 ){
			cout << "Am ajuns la destinatie" << endl;
		}
		else{
			cout << "Wrong route" << endl;
		}
		//Mergem de la ultimul oras vizitat la primul si contorizam costul total
		cost += dist[drum[orase-1]][index];
		//Afiseaza drumul ales
		cout << "Drumul are cost " << cost << " si este: " << endl;
		for(int i=0;i<orase;i++){
			cout << drum[i]+1 << " ";
		}
		cout << endl << endl << endl << index+1;
		if(cost< cost_min){
			for(int i=0;i<orase;i++){
				drum_min[i]=drum[i];
			}
			cost_min=cost;
		}
	}
	
	afisare_drum(drum_min,cost_min);
}

void afisare_drum(int drum_scurt[100],int cost_min){
	cout << "Cel mai scurt drum incepe la " << drum_scurt[0] << " are costul " << cost_min << " si este : " << endl;
	for(int i=0;i<orase;i++){
		cout << drum_scurt[i]+1 << " ";
	}	
}

int main(){
	citeste_din_fisier();
	distante();
	traseu();

	system("pause");
	return 0;
}