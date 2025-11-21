#include <iostream>
#include <cmath>
#include <cassert>
#include <random>
//Geomtric Brownian Motion Model variation developed by Kashan Khan

int main();
  
//Drift coefficient by calculating the mean change per unit time with logarithmic returns
double coefficient(double current, double initial, double time_between, double choice) {
    double r{0.0};
    r = (1/time_between) * (log(current/initial));
    return r;
}

//Calcualting the mean of the Stock Prices
double average(double array[], unsigned int capacity){
    double sum{0.0};
    for(int i{0}; i < capacity;++i) {
        sum += array[i];
    }
    return sum/capacity;
}

//The deviation from the stock price
double std_deviation(double array[],unsigned int capacity, double average) {
    double sum{0.0};
    for(int i{0}; i < capacity; ++i) {
        sum += (array[i] - average) * (array[i] - average);
    }
    return std::sqrt(sum/(capacity-1));
}


int main () {

    //Continuous random generator, using normal distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution <> d(0,1); //integers from -1 to 1

    //parameters
    double s_intial{};
    double s_current{};
    double volatility{};
    //The time between the initial and current stock price entered
    double time_between{}; 
    //The time from initial stock price to the prediction
    double t{};
    //Predicted Stock Price
    double s_final{};

while(true) {
    //options
    int option{};
        std::cout<<"Welcome to the Geomtric Brownian Motion Model." << std::endl;
        std::cout<<"Select the given time periods according to the desired prediction: "<<std::endl;
        std::cout<<"1) In a week/days" << std::endl;
        std::cout<<"2) In months" << std::endl;
        std::cout<<"3) In years" <<std::endl;
        std::cin>>option;
        
    //Assert for selecting the given options
    assert((option <= 3) && (option >= 1));

    //Inputing Parameters
    std::cout<<"Enter an initial stock price: ";
    std::cin>> s_intial;

    std::cout<<"Enter the current stock price: ";
    std::cin>> s_current;

    
    std::cout<<"Enter an annualized voltatility (as a decimal): ";
    std::cin>> volatility;

    

    //In terms of days
    if(option == 1) {

        std::cout<<"How many days is between the initial and current stock_price? ";
        std::cin>>time_between;

        std::cout<<"How many days is between the initial and predicted stock price? ";
        std::cin>>t;

        double daily_volatility {volatility/std::sqrt(252)};
        double dt {1/1};
        int capacity {1000};
        double monte_carlos[capacity] {0.0};
        double u {coefficient(s_current,s_intial,time_between,option)};
        for(int i{0}; i < capacity; ++i) {
            double z{d(gen)};
            s_final = s_intial*exp(u*t + daily_volatility*(std::sqrt(dt)*z));
            monte_carlos[i] = s_final;
        }
        double mean{average(monte_carlos,capacity)};
        std::cout<<"The expected value of the Stock is $" << mean <<std::endl;
        std::cout<<"The standard deviation of the Stock is $" <<std_deviation(monte_carlos,capacity,mean) <<std::endl;

    }
}
}
