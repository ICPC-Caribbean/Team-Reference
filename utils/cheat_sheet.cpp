/*
    Note:
        Useful tips for competitive programming
*/

// Measure current time
while (1. * clock() < 2.5 * CLOCKS_PER_SEC){
    // do something
}

// Lambda function example
function<bool(int, int)> divide = [&](int a, int b)
{
    if (a % b == 0)
        return true;
    else
        return false;
};