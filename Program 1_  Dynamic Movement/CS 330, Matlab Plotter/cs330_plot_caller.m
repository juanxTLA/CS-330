%cs330_plot_caller
%Author: Gavin Mullis    Date: 02/12/20 (Last Updated)

%Input Vars

%Replace with your filename inclding the file extension
fileName = "test.txt";   

PVLO = [1, 1, 1, 1];    %[position, velocity, linear, orientation]
gifOn = 1;              %0 for NO gif; 1 for gif

%Replace the physics used, movement algorithm used
plotName = "PhysicsUsed, MovementAlgorithm";  

%Used to increase or decrease the length of vectors
vectorScaling = 6;      %Ex. 4 or 6 are good defaults.     

%Function Call
cs330_simple_plot(fileName, PVLO, gifOn, plotName, vectorScaling);