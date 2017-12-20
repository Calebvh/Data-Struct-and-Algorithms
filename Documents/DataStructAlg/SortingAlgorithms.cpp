using namespace std;
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <math.h>
int threshold;

////////////////////////
//Global Variables
std::vector<int> GlobalList;
int mergeCounter=0;
int quickCounter=0;
int insertCounter=0;

///////////////////////


vector<int> ask_parameters()
{
    int array_size; bool correct_array_size = 0; string ask_user_for_values;
		int temp; vector<int> users_Array; bool correct_threshold_value = 0;
		srand(time(NULL));

		cout << "Enter the Size of the Array" << endl;						//ask the user to enter the array size
		do{
				cin >> array_size;
				if (array_size < 0){						//if the array size is not above 0
						cout << "Enter an appropriate array size, over 0" << endl;
				}
				else{                      //else the array is the correct size
						correct_array_size = 1;										//set bool to get out of do while
				}
		}while (correct_array_size == 0);

    cout <<"Please enter a Threshhold value below, the threshold value determines" <<endl;
    cout <<"whether or not merge sort or insertion sort will be used, if the threshold" <<endl;
    cout <<"is above the list's size then the program will use insertion sort only" <<endl;
    cout <<"if the threshold is lower than the sample size then that number is the" <<endl;
    cout <<"smallest sub list that merge sort can create" << endl;
		cout << "Enter threshold value" << endl;							//ask the user to enter the array size
		do{
				cin >> threshold;
				if (array_size < 0){																	//if the array size is not above 0
						cout << "Enter an appropriate threshold value, over 0" << endl;
				}
				else{                                                //else the array is the correct size
						correct_threshold_value = 1;										//set bool to get out of do while
				}
		} while (correct_threshold_value == 0);

		if (array_size <= 100) {
				cout << "Do you want to enter your own values? (y/n)" << endl;
				cin >> ask_user_for_values;
				if (ask_user_for_values == "y"){
						for (int i = 0; i < array_size; i++) {
								cout << "Value " << (i + 1) << ":";
								cin >> temp;
								users_Array.push_back(temp);
								cout << endl;
						}
				}
				else{
						for (int i = 0; i < array_size; i++) {
						users_Array.push_back(rand() % 1000);
						}
				}
		}
		else{
				for (int i = 0; i < array_size; i++) {
						users_Array.push_back(rand() % 1000);
				}
		}
	return users_Array;
}

vector<int> insert_sort(vector<int> input, int min, int max){
		int temp;
		for (int i = min; i < input.size() - 1; i++){
				if (input[i] <= input[i + 1]){ insertCounter++;
				}
				else{
						temp = input[i];
						input[i] = input[i + 1];													//get i+1 and and put it into i
						input[i + 1] = temp;														//put temp into i+1
						return insert_sort(input, min, max);
				}
		}
	return input;
}

vector<int> merge_sort(vector<int> input) {
		int mid; vector<int> left; vector<int> right; vector<int> output;
		int max = input.size(); int L = 0; int R = 0;
		mid = (floor((max) / 2)) - 1;

		for (int i = 0; i < mid + 1; i++) {
				left.push_back(input[i]);
		}
		for (int i = mid+1; i < max; i++) {
				right.push_back(input[i]);
		}

		if (max <= threshold) {
				return insert_sort(input, 0, max);
		}
		else {
				left = merge_sort(left);
				right = merge_sort(right);
		}
		output.reserve(left.size() + right.size());

		for (int i = 0; i < output.capacity(); i++) {

				//If the left side counter has finished going through the left list
				if (L == left.capacity()) {
						output.push_back(right[R]); // fill in the rest of the right list
						R++;
				}
				//If the right side counter has finished going through the counter list
				else if (R == right.capacity()) {
						output.push_back(left[L]); //fill in the the rest of the left list
						L++;
				}
				else if (left[L] < right[R]) { //If the number in the Left list is < the number in the right
						output.push_back(left[L]); //Push the left number onto the list
						L++;
            mergeCounter++;
				}
				else if (left[L] > right[R]) { //If the number in the Right list is < the number in the left
						output.push_back(right[R]); //Push the right number onto the list
						R++;
            mergeCounter++;
				}
				else if (left[L] == right[R]) {	//If the compared numbers in each list are equal
						output.push_back(right[R]); //Push both numbers onto the list
						output.push_back(right[L]);
						i++; R++; L++; //i needs to be incremented because 2 numbers have been pushed
            mergeCounter++;
        }
		}
	return output;
}

int partition(vector<int> input, int left, int right){
    int wall = left-1;
    for(int i = left; i < right; i++){
        //cout << "Comparing if: " << input[i] <<" < " <<input[right]<<endl;
        if(input[i] <= input[right]){
            wall++;
            //cout<<"Here:Swapping: "<<wall<<" and "<<i<<endl;
            std::swap(input[wall], input[i]);
            //cout<<"Here:Now: "<<input[wall]<<" and "<<input[i]<<endl;
            quickCounter++;
        }
    }
    int checker = right - (wall +1);
    if(checker != 1){
      //cout<<"Pivot Swapping: "<<wall +1<<" and "<<right<<endl;
      std::swap(input[wall+1], input[right]);
      //cout<<"Pivot Now: "<<input[wall +1]<<" and "<<input[right]<<endl;
    }
    GlobalList = input;
    return(wall+1);

}


void quick_sort(vector<int> input, int left, int right) {

      if( left < right){
        int split = partition(GlobalList, left, right);

        quick_sort(GlobalList, left, split-1);
        quick_sort(GlobalList, split+1, right);
      }

      for(int i =0; i < GlobalList.size()-1; i++){
        if(GlobalList[i] > GlobalList[i+1]){
          std::swap(GlobalList[i], GlobalList[i+1]);
        }
      }
}


//Prints out all numbers in the inputted list
void print_list(vector<int> print) {

    vector<int> temp = print;
    int i = 0;
    int j = 0;
    int printlines = ceil(temp.size()/15);

    for(int x = 0; x<printlines; x++){
        int n = (x+1) * 15;
        if(n >= temp.size()){n = temp.size();}

        if(x==0){cout << "Position: ";}
        else{cout<< "          ";}
    		for (i; i < n; i++) {
    				cout << i << " ";
    				if(temp[i]>= 100 && i < 10){cout<<"  ";}
            else if(temp[i] < 100){cout<<" ";}
            else if(temp[i] >= 100){cout<<" ";}
    		}
    		cout<<endl;
    		if(x==0){cout << "Value:    ";}
        else{cout<< "          ";}
    		for (j; j < n; j++) {
    				cout << print[j]<< " ";
    		}
        cout<<endl;
        cout<<endl;

    }
    cout<<endl;
    cout<<endl;
}

void print_options(vector<int> input, vector<int> sorted_list) {
		string ask_user_to_print;
		if (sorted_list.size() <= 100) {
				cout << "Do you want to print your list? (y/n)" << endl;
				cin >> ask_user_to_print;
				if (ask_user_to_print == "y") {
						cout << "Unsorted: " << endl;
						print_list(input);
						cout << "Sorted: " << endl;
						print_list(sorted_list);
				}
				else{
						cout << "You have chosen not to print" << endl;
				}
		}
}

int main(){
		bool retry = 0; string ask_user_to_continue;
		do{
				vector<int> input; vector<int> sorted_list;

				input = ask_parameters();
				sorted_list = input;
        GlobalList = sorted_list;
				sorted_list = merge_sort(input);
        quick_sort(GlobalList, 0, input.size()-1);
        cout<<"Merge sort/Insertion Sort:"<<endl;
				print_options(input, sorted_list);
        cout<<endl;
        cout<<"Merge sort used: "<<mergeCounter<<" comparisions to complete the sorting" <<endl;
        cout<<endl;
        cout<<"Insertion sort used: "<<insertCounter<<" comparisions to complete the sorting" <<endl;

        cout<<"Quick Sort:"<<endl;
        print_options(input, GlobalList);
        cout<<endl;
        cout<<"Quicksort used: "<<quickCounter<<" comparisions to complete the sorting" <<endl;

				cout << "Do you want to start over? (y/n)" << endl;
				cin >> ask_user_to_continue;
				if (ask_user_to_continue == "n") { retry = 1;}
		} while (retry == 0);

	system("pause");
	return 0;
}
