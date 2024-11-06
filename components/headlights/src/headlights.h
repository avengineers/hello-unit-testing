#ifndef HEADLIGHTS_H
#define HEADLIGHTS_H

typedef enum
{
    HIGH_BEAM,
    LOW_BEAM
} BeamType;

typedef enum
{
    TEST_PASSED,
    TEST_FAILED
} TestStatus;

/**
 * @brief Run diagnostic tests
 *
 * @param type BeamType: high or low beam diagnostic tests
 * @return TestStatus: TEST_PASSED - tests passed, TEST_FAILED - tests failed
 */
extern TestStatus runDiagnosticTest(BeamType type);

#endif /* HEADLIGHTS */
