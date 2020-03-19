#include "PID.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_, double sat_min_, double sat_max_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
    Kp = Kp_;
    Ki = Ki_;
    Kd = Kd_;

    prev_cte = 0.0;
    int_cte = 0.0;
    flag_first_it = false;
    flag_error_sat = false;

    sat_min = sat_min_;
    sat_max = sat_max_;

}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
    double diff_cte;
    if (!flag_first_it){
        prev_cte = cte;
        diff_cte = 0;
        flag_first_it = true;
    }else {
        diff_cte = cte - prev_cte;

    }
    // Anti wind up
    if (!flag_error_sat) int_cte += cte;
    p_error = Kp * cte;
    d_error = Kd * diff_cte;
    i_error = Ki * int_cte;
    prev_cte = cte;

}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
    double total_error = p_error+d_error+i_error;
    double total_error_abs = std::abs(p_error)+std::abs(d_error)+std::abs(i_error);
    double p_error_percentage = std::abs(p_error)/total_error_abs*100;
    double d_error_percentage = std::abs(d_error)/total_error_abs*100;
    double i_error_percentage = std::abs(i_error)/total_error_abs*100;
    printf("p: %5.2f d: %5.2f i: %5.2f\n", p_error_percentage,d_error_percentage,i_error_percentage);

    if(total_error<sat_min){
        total_error = sat_min;
        flag_error_sat = true;
    }else if (total_error>sat_max) {
        total_error = sat_max;
        flag_error_sat = true;
    }else {
            flag_error_sat = false;
    }
    std::cout<<"total_error: "<<total_error<<std::endl;
    return total_error;
}
