#include <iostream>
#include <fstream>
using namespace std;
// this creates everything that will be stored in CarType
struct CarType{
  enum {MAX_CHAR_LEN = 100};
  char carName[MAX_CHAR_LEN];
  double MPG;
  int Cylinders;
  double Displacement;
  double Horsepower;
  double Weight;
  double Acceleration;
  int Model;
  char Origin[MAX_CHAR_LEN];
  bool isValid;
  CarType();
    
};
// this defines everything in CarType
CarType::CarType() {
  MPG = 0;
  Displacement = 0;
  Cylinders = 0;
  Horsepower = 0;
  Weight = 0;
  Acceleration = 0;
  Model = 0;
  for(int index = 0; index < MAX_CHAR_LEN; index++){
    Origin[index] = 0;
    carName[index] = 0;
  }
  
  isValid = false;
}
const int MAX_CARS = 500;
// This function is connected with the readCars function to allow the program to read the description of the car
CarType readCarData(ifstream &inFile){
    CarType car; 
    int index = 0;
   
      
      inFile.get(car.carName, CarType::MAX_CHAR_LEN, ';');
      inFile.ignore(100,';');
      inFile >> car.MPG;
      inFile.ignore(100,';');
      inFile >> car.Cylinders;
      inFile.ignore(100,';');
      inFile >> car.Displacement;
      inFile.ignore(100,';');
      inFile >> car.Horsepower;
      inFile.ignore(100,';');
      inFile >> car.Weight;
      inFile.ignore(100,';');
      inFile >> car.Acceleration;
      inFile.ignore(100,';');
      inFile >> car.Model;
      inFile.ignore(100,';');
      inFile.get(car.Origin, CarType::MAX_CHAR_LEN);
      inFile.ignore(100,'\n');
    // If we reached the end of the file while reading, then the entry is not valid
        car.isValid = !inFile.eof();
          index++;
    return car;
}
// this function reads the cars in the file and stores it into the cars[] array
int readCars(CarType cars[]) {
    ifstream carFile("cars.txt");
    int numCars = 0;
    while(carFile.peek() != EOF && numCars < MAX_CARS) {
        cars[numCars] = readCarData(carFile);
        numCars++;
    }
    return numCars;
}
// this function gets the list of cars already stored into the cars[] array and shows the information to the user.
void printCars(CarType cars[]){
  
    for(int index = 0; index < MAX_CARS; index++){
      
      if(cars[index].isValid != false){
        cout << "Index " << index << ": ";
        cout << cars[index].carName << ";";
        cout << cars[index].MPG << ";";
        cout << cars[index].Cylinders << ";";
        cout << cars[index].Displacement << ";";
        cout << cars[index].Horsepower << ";";
        cout << cars[index].Weight << ";";
        cout << cars[index].Acceleration << ";";
        cout << cars[index].Model << ";";
        cout << cars[index].Origin << endl;
      
        
      }
      
    }
}
// this function prints the car based off of what the user entered the Origin as. the cars[index].Origin allows us to do this because it compares what the user entered with what is stored.
void printCarsByOrigin(CarType cars[]){
  string comparison = "";
  cout << "Type a requested region of Origin: ";
  cin >> comparison;
  for(int index = 0; index < MAX_CARS; index++){
    if(cars[index].Origin == comparison){
        cout << "Index " << index << ": ";
        cout << cars[index].carName << ";";
        cout << cars[index].MPG << ";";
        cout << cars[index].Cylinders << ";";
        cout << cars[index].Displacement << ";";
        cout << cars[index].Horsepower << ";";
        cout << cars[index].Weight << ";";
        cout << cars[index].Acceleration << ";";
        cout << cars[index].Model << ";";
        cout << cars[index].Origin << endl;
    }
  }
}
// used for promting the user for data but for doubles
int readDouble(const char prompt[]){
    double temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}
// used for promting the user for data but for ints
int readInt(const char prompt[]){
    int temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}
// removes a car from the cars[] array
void removeCar(CarType cars[]){
  int temp = readInt("Enter index to remove");
  cars[temp].isValid = false; 

}
// goes through all of the information stored in cars[] until it finds an unvalid car. Once it finds one it will  promt the user for the cars information and then break
int addCar(CarType cars[]){
  for(int index = 0; index <= MAX_CARS; index++){
    if(cars[index].isValid == false){
      cars[index].isValid = true;
      cout << "Enter the cars Name: ";
      cin.ignore(100, '\n');
      cin.get(cars[index].carName, CarType::MAX_CHAR_LEN);
      cars[index].MPG = readInt("Enter the cars MPG");
      cars[index].Cylinders = readInt("Enter the cars cylinders");

      cars[index].Displacement = readDouble("Enter the cars displacement");

      cars[index].Horsepower = readDouble("Enter the cars horsepower");

      cars[index].Weight = readDouble("Enter the cars weight");

      cars[index].Acceleration = readDouble("Enter the cars acceleration");

      cars[index].Model = readInt("Enter the cars model");
      cout << "Enter the cars origin";
      cin >> cars[index].Origin;
      break;
    }
    else if(index == 500){
      cout << "database is full";
      return 0;
    } 
  }
  return 0;
}
// where everything will end up being called and will display a menu for the user.
int main() {
    CarType cars[MAX_CARS]; 
    int num = readCars(cars);
    int enter = 1200231;
    cout << "Nums: " << num << endl;
    readCars(cars);
    while(enter != 5){
      cout << " Display the car list(1)\n Remove a car from the list(2)\n Add a car to the list(3)\n Display cars by origin(4)\n Quit(5)\n Enter: ";
      cin >> enter;
      
      if(enter == 2){
        removeCar(cars);
      }
      else if(enter == 1){
        printCars(cars);
      }
      else if(enter == 3){
        addCar(cars);
      }
      else if(enter == 4){
        printCarsByOrigin(cars);
      }
      else if(enter == 5){
        cout << endl << "Goodbye";
        return 0;
      }
      }
    return 0;
}
