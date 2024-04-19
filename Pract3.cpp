
#include<iostream>
#include<vector>
#include<climits>
#include<random>
#include<chrono>

using namespace std;
using namespace std::chrono;

void seq_min(const vector<int>& arr){
  int min_val=INT_MAX;
  for(int i=0; i<arr.size();i++){
    if(arr[i]<min_val){
      min_val=arr[i];
    }
  }
  cout<<"MIN val: "<<min_val<<endl;
}

void seq_max(const vector<int>& arr){
  int max_val=INT_MIN;
  for(int i=0; i<arr.size();i++){
    if(arr[i]>max_val){
      max_val=arr[i];
    }
  }
  cout<<"MAX val: "<<max_val<<endl;
}

void seq_sum(const vector<int>& arr){
  int sum=0;
  for(int i=0; i<arr.size();i++){
    sum+=arr[i];
  }
  cout<<"SUM val: "<<sum<<endl;
}

void seq_avg(const vector<int>& arr){
  int sum=0;
  for(int i=0; i<arr.size();i++){
    sum+=arr[i];
  }
  cout<<"AVG val: "<<sum/arr.size()<<endl;
}

void par_min(const vector<int>& arr){
  int min_val=INT_MAX;
  #pragma omp parallel for reduction(min:min_val)
  for(int i=0; i<arr.size();i++){
    if(arr[i]<min_val){
      min_val=arr[i];
    }
  }
  cout<<"MIN val: "<<min_val<<endl;
}

void par_max(const vector<int>& arr){
  int max_val=INT_MIN;
  #pragma omp parallel for reduction(max:max_val)
  for(int i=0; i<arr.size();i++){
    if(arr[i]>max_val){
      max_val=arr[i];
    }
  }
  cout<<"MAX val: "<<max_val<<endl;
}

void par_sum(const vector<int>& arr){
  int sum=0;
  #pragma omp parallel for reduction(+:sum)
  for(int i=0; i<arr.size();i++){
    sum+=arr[i];
  }
  cout<<"SUM val: "<<sum<<endl;
}

void par_avg(const vector<int>& arr){
  int sum=0;
  #pragma omp parallel for reduction(+:sum)
  for(int i=0; i<arr.size();i++){
    sum+=arr[i];
  }
  cout<<"AVG val: "<<sum/arr.size()<<endl;
}

int main() {
    int num_terms;
    cout << "Enter the number of terms: ";
    cin >> num_terms;

    // Generate random numbers for the array
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100); // Adjust the range as needed

    vector<int> arr(num_terms);
    cout << "Generated terms: ";
    for (int i = 0; i < num_terms; ++i) {
        arr[i] = dis(gen); // Generate a random number and assign to array
        cout << arr[i] << " ";
    }
    cout << endl;

    auto start = high_resolution_clock::now();
    seq_min(arr);
    seq_max(arr);
    seq_avg(arr);
    seq_sum(arr);
    auto stop = high_resolution_clock::now();
    auto seq_duration = duration_cast<milliseconds>(stop - start);

    cout << "Sequential Execution Time: " << seq_duration.count() << " ms" << endl;

    start = high_resolution_clock::now();
    par_min(arr);
    par_max(arr);
    par_avg(arr);
    par_sum(arr);
    stop = high_resolution_clock::now();
    auto par_duration = duration_cast<milliseconds>(stop - start);

    cout << "Parallel Execution Time: " << par_duration.count() << " ms" << endl;

    return 0;
}
