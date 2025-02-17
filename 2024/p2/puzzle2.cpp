//one edge case which I couldn't figure out, so correct answer is apparently 689 and not 690

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;
using namespace std::chrono; 

bool check_level(const vector<int> &x, bool partTwo); 

int main(){
    string line; 
    string filePath = "data2.csv";
    vector<int> report; 
    int count = 0; 

    // set to false, to just get part one: 
    bool partTwo = true; 

    auto start = high_resolution_clock::now();

    try{
        ifstream file(filePath);
        if(!file.is_open()){
            cerr << "Error occured during file opening" << endl;
            return 1;
        }

        string line; 
        while(getline(file, line)){
            istringstream iss(line);
            int row; 
            while(iss >> row){                
                report.push_back(row);
            }                     
            count += check_level(report, partTwo);
            report.clear();                                                            
        }
    }
    catch(exception e){
        cerr << "Error during file reading" <<  e.what()  << endl;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << "time in milliseconds " << duration  << endl;   
    cout << "valid levels " << count << endl;

    return 0; 
}

bool check_level(const vector<int> &x, bool partTwo){

    int increasing_count = 0;
    int decreasing_count = 0;

    for (size_t i = 0; i < x.size() - 1 && i < 3; i++) {
        if (x[i] < x[i + 1]) {
            increasing_count++;
        } else if (x[i] > x[i + 1]) {
            decreasing_count++;
        }
    }
              
    bool flag = increasing_count > decreasing_count;
    //bool flag = x[0] < x[1];
    int error = 0; 


    for(int i = 0; i < x.size() -1; i++){                       
        if(flag){
            if(!(x[i] < x[i+1] && (abs(x[i] - x[i+1]) <= 3))){
                if(partTwo){
                    if(error < 1){
                       error++; 
                       continue; 
                    }
                    else{
                        return false; 
                    }
                }
                return false; 
            }        
        }

        if(!flag){
            if(!(x[i] > x[i+1] && (abs(x[i] - x[i+1]) <= 3))){                
                if(partTwo){
                    if(error < 1){
                        error++; 
                        continue; 
                    }
                    else{
                        return false; 
                    }
                }
                return false; 
            }        
        }
    }
    return true; 
}


//2 edge cases out of 1000 are handled wrong, dunno 
bool quick_check(const vector<int>& x){ 
    if(3 < (abs(x[0] - x[x.size()-1]) / x.size()-1)){
        return false; 
    }
    return true;    
}