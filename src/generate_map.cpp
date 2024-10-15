#include <iostream>
#include <experimental>

using namespace std;

void generate_map(int n){

	cout<<n/2<<endl;
	vector<int> gen;
	for(int i = 0; i < n/2; i++){
		int choc = randint(97, 122);
		if(gen.find(choc) == gen.end()){
			cout<< i << " " << randint(1, n+1) << endl;
			gen.push_back(choc);
		}
	}

	cout<< n << " " << n;

	for(int i = 0; i < m->row; i++){
		for(int j = 0; j < m->col; j++){
			cout<<  << " ";
		}
		cout<<endl;
	}

	cout << "0 0" <<endl;
	cout<< n << " " << n << endl;
	return;
}