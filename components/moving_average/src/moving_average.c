#include "moving_average.h"

#define WINDOW_SIZE 4U

// Circular buffer to store the latest values
static uint16_t values[WINDOW_SIZE];

// The sum of the values in the window
static uint32_t sum;

// The index of the current value in the circular buffer
static uint8_t index;

// The count of values added (can be less than WINDOW_SIZE initially)
static uint8_t count;

// Initialize the moving average module
void movingAverageInit(void)
{
    for (uint8_t i = 0; i < WINDOW_SIZE; i++)
    {
        values[i] = 0U;
    }

    sum = 0U;
    index = 0U;
    count = 0U;
}

// Add a new value to the moving average calculation
void addNewValue(uint16_t new_value)
{
    // Subtract the old value from the sum
    if (count == WINDOW_SIZE)
    {
        sum -= values[index];
    }
    else
    {
        count++;
    }

    // Add the new value to the circular buffer and the sum
    values[index] = new_value;
    sum += new_value;

    // Move to the next index (circular behavior)
    index = (index + 1) % WINDOW_SIZE;
}

// Get the averaged value
int16_t getAveragedValue(void)
{
    int16_t average = 0;

    // In case there are no elements, average is 0
    if (count > 0)
    {
        average = (int16_t)(sum / count);
    }

    return average;
}
