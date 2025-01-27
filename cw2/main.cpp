

 #include <stdio.h>
#include <stdlib.h>
#include <math.h>

//-------------------------------------------------------------
// Function to evaluate the fastest possible route from up 5 out of 10 preprogrammed locations.
//-------------------------------------------------------------

// Copyright Maria Stephen

// Input argument: The number of locations and the locations values

// Return value  : The fastest combination for these locations and the distance travelled for this route

// Required header files: stdlib.h, stdio.h


// The functions used in this programme are shown below:


// function that will calculate distance between two locations using Pythagorean theorem
float DistanceBetweenCoords (float FirstCoordX, float FirstCoordY, float SecondCoordX, float SecondCoordY);

// function that will calculate total distance of a route
float totalDistanceOfRoute(float xCoordOfPossibleLocations[], float yCoordOfPossibleLocations[], int orderedLocationsVisitedOnThisRoute[], int NumberOfLocations);


// function that will calculate the number of combinations for a given route using factorials
unsigned long int factorial(int n);


// function that will create all the combinations for a given route using permutation
void get_next_route(const int permutation,const int no_objects,int* const route);


//-------------------------------------------------------------
//-------------------------------------------------------------

// The main program

int main()
{
    int NumberOfLocations;

    float xCoordOfPossibleLocations[11] = {0,9,6,7,1,21,7,11,5,9,8};  // all x coordinate values
    float yCoordOfPossibleLocations[11] = {0,8,8,8,1,11,11,11,5,9,1}; // all y coordinate values

    do
    {
        printf("Enter the number of locations(1-5):");                // requests number of locations from user
        scanf("%d", &NumberOfLocations);

        if ((NumberOfLocations<=0) || (NumberOfLocations>5))
        {
            printf("\nThe value has to be an integer between 1-5 try again\n"); // do while loop is used to make sure input is valid
            // if the value is not valid "The value has to be an integer between 1-5 try again" is printed

        }

        fflush(stdin);

    }
    while ((NumberOfLocations<=0) || (NumberOfLocations>5));


    printf("\nThe number of locations is %d\n", NumberOfLocations);   // Displays value given by the user
    // variables being used --
    float currentPermutationDistance;
    float shortestDistance;
    int NumberOfPermutations;

    // arrays being used
    int FastestRoute[NumberOfLocations];        // this array stores the fastest combination of locations

    int route[NumberOfLocations];               // this pointer array stores the combinations of locations (used in get_next_route function)

    int orderedLocations[NumberOfLocations];    // this array stores locations inputted

    int currentRoute[NumberOfLocations];        // this array stores the current combination of locations




    for(int i=0; i<NumberOfLocations; i++)                                // for loop to gather location values
    {

        do
        {
            printf("\nEnter location %d (Between 1-10):", i+1);           // do while loop used to chedk validity of input
            scanf("%d", &orderedLocations[i]);                            // if input value is not within the range then "The value entered is not an integer between 1-10 try again" is printed
            route[i] = orderedLocations[i];

            if ((orderedLocations[i]<=0) || (orderedLocations[i]>10))
            {
                printf("\nThe value entered is not an integer between 1-10 try again\n");
            }
            fflush(stdin);


        }
        while ((orderedLocations[i]<=0) || (orderedLocations[i]>10));


    }



    shortestDistance = 50;  // setting initial value of shortest distance to a high number so the first loop on the if
                            // statement condition (currentPermutationDistance<shortestDistance) can be met


    NumberOfPermutations = factorial(NumberOfLocations); // calling the factorial function and equating what it returns to NumberOfPermutations


    currentPermutationDistance = 0;


    for (int i=0; i<NumberOfPermutations; i++)              // first for loop loops for every combination e.g 3! = 6 loops
    {
        get_next_route(i, NumberOfLocations, route);        // calling permutation function to generate a combination and assign it to the pointer array route

        for (int n=0; n<NumberOfLocations; n++)             // second for loop is used to extract the route combination from pointer array route and assign it to currentRoute

        {
            currentRoute[n] = orderedLocations[route[n]];
        }

                                                            // calling total distance function to calculate the total distance travelled for this combination
        currentPermutationDistance = totalDistanceOfRoute(xCoordOfPossibleLocations, yCoordOfPossibleLocations, currentRoute, NumberOfLocations);


        if (currentPermutationDistance<shortestDistance)    // if statement for storing the shortest route combination and its distance
        {
            shortestDistance = currentPermutationDistance;

            for (int j=0; j<NumberOfLocations; j++)         // for loop used to extract the values from currentRoute array to
                                                            // FastestRoute array if the if condition is met
            {
                FastestRoute[j] = currentRoute[j];
            }
        }

    }

    printf("\nThe shortest route is -- ");

    for (int i=0; i<NumberOfLocations; i++)
    {
        printf("%d ", FastestRoute[i]);
    }

    printf(" -- with a distance of %f", shortestDistance);



    return 0;
}

//-----------------------------------------------------------------------------------
// TEST DATA


// TEST 1 /----

// Enter the number of locations(1-5):3

// The number of locations is 3

// Enter location 1 (Between 1-10):1

// Enter location 2 (Between 1-10):2

// Enter location 3 (Between 1-10):3

// The shortest route is -- 1 3 2  -- with a distance of 25.041595


// TEST 2 /----

// Enter the number of locations(1-5):4

// The number of locations is 4

// Enter location 1 (Between 1-10):9

// Enter location 2 (Between 1-10):1

// Enter location 3 (Between 1-10):7

// Enter location 4 (Between 1-10):4

// The shortest route is -- 1 7 9 4  -- with a distance of 31.203493


// TEST 3 (testing if validation works for NumberOfLocations) /----

// Enter the number of locations(1-5):-1

// The value has to be an integer between 1-5 try again
// Enter the number of locations(1-5):15

// The value has to be an integer between 1-5 try again
// Enter the number of locations(1-5):g

// The value has to be an integer between 1-5 try again
// Enter the number of locations(1-5):!

// The value has to be an integer between 1-5 try again
// Enter the number of locations(1-5):@

// The value has to be an integer between 1-5 try again
// Enter the number of locations(1-5):


// TEST 4 (testing if validation for locations) /----

// Enter the number of locations(1-5):3

// The number of locations is 3

// Enter location 1 (Between 1-10):-1

// The value entered is not an integer between 1-10 try again

// Enter location 1 (Between 1-10):g

// The value entered is not an integer between 1-10 try again

// Enter location 1 (Between 1-10):2

// Enter location 2 (Between 1-10):-1

// The value entered is not an integer between 1-10 try again

// Enter location 2 (Between 1-10):f

// The value entered is not an integer between 1-10 try again

// Enter location 2 (Between 1-10):4

// Enter location 3 (Between 1-10):-3

// The value entered is not an integer between 1-10 try again

// Enter location 3 (Between 1-10):


//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------

// subtask A

float DistanceBetweenCoords (float FirstCoordX, float FirstCoordY, float SecondCoordX, float SecondCoordY)
{
    float DifferenceBetweenX = 0;
    float DifferenceBetweenY = 0;

    float Distance;

    DifferenceBetweenX = FirstCoordX - SecondCoordX;
    DifferenceBetweenY = FirstCoordY - SecondCoordY;

    Distance = sqrt((DifferenceBetweenX*DifferenceBetweenX) + (DifferenceBetweenY*DifferenceBetweenY));

    return Distance;


}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------


//subtask B

float totalDistanceOfRoute(float xCoordOfPossibleLocations[], float yCoordOfPossibleLocations[], int orderedLocations[], int NumberOfLocations)
{

    float totalDistance = 0;
    float distanceFromDepot = 0; // distanceFromDepot and distanceToDepot are used for the calculating the distance from (0,0) to the first location
    float distanceToDepot = 0;   // and the distance from the last location to (0,0) to be added on to the total distance




    for (int i=0; i<NumberOfLocations - 1; i++) // for loop used to calculate the distance between the locations
    {
        int j = orderedLocations[i];

        int k = orderedLocations[i+1];


                                                // DistanceBetweenCoords function is called to calculate the distance between two locations
        totalDistance= totalDistance + DistanceBetweenCoords(xCoordOfPossibleLocations[j], yCoordOfPossibleLocations[j], xCoordOfPossibleLocations[k],yCoordOfPossibleLocations[k]);


    }

    distanceFromDepot = DistanceBetweenCoords(xCoordOfPossibleLocations[0], yCoordOfPossibleLocations[0], xCoordOfPossibleLocations[orderedLocations[0]], yCoordOfPossibleLocations[orderedLocations[0]]);
    distanceToDepot = DistanceBetweenCoords(xCoordOfPossibleLocations[orderedLocations[NumberOfLocations-1]], yCoordOfPossibleLocations[orderedLocations[NumberOfLocations-1]], xCoordOfPossibleLocations[0], yCoordOfPossibleLocations[0]);

    totalDistance = totalDistance + distanceFromDepot + distanceToDepot;

    return totalDistance;



}

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------


// factorial function uses NumberOfLocations to return the number of possible combinations

unsigned long int factorial(int n)
{

    unsigned long int v = 1;

    for(int i=2; i<=n; i++) v*=i;

    return(v);
}

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------


// permutation function returns a unique combination of the locations
void get_next_route(const int permutation,const int no_objects,int *const route)
{
    for(unsigned int j=0; j<no_objects; j++)
    {
        route[j]=j;
    }
    unsigned long int ft=1;
    for(unsigned int j=2; j<=no_objects; j++)
    {
        ft=ft*(j-1);

        int s=j-((permutation/ft)%j);
        int tmp=route[s-1];

        route[s-1]=route[j-1];
        route[j-1]=tmp;
    }

}

