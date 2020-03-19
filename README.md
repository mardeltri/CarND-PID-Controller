# **PID controller** 

[//]: # (Image References)

[image1]: ./images/Simulator1.png "State machine"


### 1. Introduction
In this project, a PID controller is implemented in order to maneuver a car around a track. The simulator provide the cross track error (CTE) and the velocity (mph) in order to compute the appropiate steering angle.

First, the PID controller will be introduced. Later, the effect of each term of the PID controller will be discussed. Finally, how the hyperparameters were selected has been explained.
![State machine][image1]

### 2. PID controller
Two PID controllers have been tuned one for the steering angle control and other for the car speed. A C++ class have been implemented in order to include the PID controller. Particular parameters are set with the init method.

The initials parameters are:
* Kp: proportional gain.
* Ki: integral gain.
* Kd: derivative gain.
* max_sat_error: Maximum saturation value for the error.
* min_sat_error: Minimum saturation value for the error.

With the saturation values the steering angle and the throttle are saturated when they reach their maximum or minimum values. Furthermore, a anti-wind up algorithm has been implemented in order to stop computing the integral error when the control signal is saturated. This prevents the system from continuing increasing the integral error when the signal cannot be increased more.

#### 1. Effect of each term of the PID controller
The effect of each term is described below:
* Proportional term. This is the basic term, it is in charge of increasing or decrasing the control signal when the system distances itself from the reference, this is, when the error increases. The proportional gain should be set so that the system achives the reference quickly but without oscillations. If the value is too small, the car is not able to reach the reference or, if it reachs it, the oscillation is guaranteed. When the value is too high, the oscillations are given with a higher frequency.
* Derivative term. It takes into account the  variation of the error to compute the control signal. Thus, if the derivative of the error increases (the error is increasing) this term increases proportionally. This proportion is defined by the derivative gain. In real applications, the noise of the error signal affects considerably the output of this term.
* Integral term. To sum up, it can be said that the integral term is in charge of eliminating the error in steady state. For example, in this project, it is useful when following curves. As for the speed controller, it is essential, for example, consider that the car reference speed is 40mph and the current speed is 40mph, thus, the error is 0, so the proportional term is 0 also. Here, the integral term is in charge of setting the throttle when the proportional term is null.

#### 2. Tunning hyperparameters
The gains have been calculated by tunning. To compute the kp term, it was estimated how much steering angle was required for an specific error. In this case, it was innitially set to 0.1. It was observed that the car didn't have enough control effort to reach the reference. So, it was increased gradually. Later, the derivative gain was set to 0.1, but it was too small. This value was increased until 1.3. The ki value affects considerably during curved sections. A higher value of ki gave place to oscillations. Speed controller gains were found with the same procedure. It should be noted that values above those ones make the system unstable.

|    | Steering angle | Throttle |
|----|----------------|----------|
| Kp | 0.26           | 0.1      |
| Ki | 0.0015         | 0.01     |
| Kd | 1.3            | 0        |