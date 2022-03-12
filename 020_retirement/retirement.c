#include <stdlib.h>
#include <stdio.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double calculator (int startAge, double balance, retire_info x){

  int month, year;
  month = startAge%12;
  year = startAge/12;
  for (int i=x.months;i>0;i--){
    printf("Age %3d month %2d you have $%.2lf\n", year, month, balance);
    balance = balance*(1 +x.rate_of_return)+x.contribution;
    month++;
    if (month ==12){
      year++;
      month = 0;
    }
  }

  return balance;
}

void retirement (int startAge,   //in months
		       double initial, //initial savings in dollars
		       retire_info working, //info about working
		       retire_info retired){ //info about being retired
  initial = calculator(startAge, initial, working);
  calculator(startAge+working.months, initial, retired);
  return;
}


int main(){
  retire_info working = {489,1000,0.045/12};
  retire_info retired = {384,-4000,0.01/12};
  retirement(327, 21345, working, retired);
  return 0;
}
